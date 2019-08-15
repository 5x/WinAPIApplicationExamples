#include <windows.h>
#include <tchar.h>

int main() {
    SetConsoleTitle(_T("WAPIA1.2"));

    STARTUPINFO SupIn;
    PROCESS_INFORMATION PrIn;

    ZeroMemory(&SupIn, sizeof(SupIn));
    SupIn.cb = sizeof(SupIn);
    ZeroMemory(&PrIn, sizeof(PrIn));

    WCHAR path[] = _T("WAPIA1.1");

    SupIn.lpTitle = _T("WAPIA1.1");
    SupIn.dwFillAttribute = 240;
    SupIn.dwFlags = STARTF_USEFILLATTRIBUTE;

    if (CreateProcess(nullptr, path, nullptr, nullptr, FALSE,
        CREATE_NEW_CONSOLE, nullptr, nullptr, &SupIn, &PrIn)) {
        _tcprintf(_T("Creating new process.\n"));
        _tcprintf(_T("Process ID:\t%d\n"), PrIn.dwProcessId);
        _tcprintf(_T("Thread  ID:\t%d\n"), PrIn.dwThreadId);
        WaitForSingleObject(PrIn.hProcess, INFINITE);
        _tcprintf(_T("The process has completed.\n"));
    } else {
        _tcprintf(_T("Can\'t create process.\n"));
    }

    system("pause");

    return 0;
}
