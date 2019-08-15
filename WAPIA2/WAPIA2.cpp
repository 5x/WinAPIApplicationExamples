#include <windows.h>
#include <tchar.h>
#include <iostream>
#include "strsafe.h"

using namespace std;

BOOL CreateTreeDirectory(const wchar_t* path) {
    TCHAR tPath[MAX_PATH];
    _tcsncpy_s(tPath, path, sizeof(tPath));
    for (TCHAR* p = tPath; *p; p++) {
        if (*p == '\\') {
            *p = 0;
            CreateDirectory(tPath, nullptr);
            *p = '\\';
        }
    }

    return !CreateDirectory(tPath, nullptr);
}

HANDLE hIn;
HANDLE hOut;

void print(LPCWSTR str) {
    WriteConsole(hOut, str, _tcslen(str), nullptr, nullptr);
}

int main(int argc, TCHAR* argv[]) {
    SetConsoleTitle(_T("Lab2"));
    FlushConsoleInputBuffer(hIn);
    hIn = GetStdHandle(STD_INPUT_HANDLE);
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    WIN32_FIND_DATA FileData;
    HANDLE          hSearch;
    DWORD           dwAttrs;
    TCHAR           szNewPath[MAX_PATH];

    BOOL            fFinished = FALSE;

    if (argc != 2) {
        _tprintf(_T("Usage: %s\n"), argv[0]);
    }

    print(_T("Enter folder name: "));

    TCHAR buffer[255];
    DWORD len;

    ReadConsole(hIn, buffer, sizeof(buffer), &len, nullptr);

    LPTSTR b;

    lstrcat(b, _T("D:\\Temp\\"));
    lstrcat(b, buffer);

    // Create a new directory. 
    if (CreateTreeDirectory(b)) {
        printf("CreateDirectory failed (%d)\n", GetLastError());
    }

    MessageBox(nullptr, _T("Copied successfully"), _T("Succses"), MB_OK | MB_ICONINFORMATION);

    // Start searching for text files in the current directory.
    hSearch = FindFirstFile(TEXT("*.txt"), &FileData);
    if (hSearch == INVALID_HANDLE_VALUE) {
        printf("No text files found.\n");

        system("pause");
        return 1;
    }

    // Copy each .TXT file to the new directory
    // and change it to read only, if not already.
    while (!fFinished) {
        StringCchPrintf(szNewPath, sizeof(szNewPath) / sizeof(szNewPath[0]), TEXT("%s\\%s"), argv[1], FileData.cFileName);

        if (CopyFile(FileData.cFileName, szNewPath, FALSE)) {
            dwAttrs = GetFileAttributes(FileData.cFileName);
            if (dwAttrs == INVALID_FILE_ATTRIBUTES);//return;

            if (!(dwAttrs & FILE_ATTRIBUTE_READONLY)) {
                SetFileAttributes(szNewPath,
                    dwAttrs | FILE_ATTRIBUTE_READONLY);
            }
        } else {
            printf("Could not copy file.\n");
        }

        if (!FindNextFile(hSearch, &FileData)) {
            if (GetLastError() == ERROR_NO_MORE_FILES) {
                _tprintf(TEXT("Copied *.txt to %s\n"), argv[1]);
                fFinished = TRUE;
            } else {
                printf("Could not find next file.\n");
            }
        }
    }

    // Close the search handle. 
    FindClose(hSearch);

    system("pause");

    return 0;
}
