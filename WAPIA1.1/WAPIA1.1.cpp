#include <windows.h>
#include <tchar.h>

HANDLE hIn;
HANDLE hOut;

void print(LPCWSTR str) {
    WriteConsole(hOut, str, _tcslen(str), nullptr, nullptr);
}

int main() {
    FlushConsoleInputBuffer(hIn);
    hIn = GetStdHandle(STD_INPUT_HANDLE);
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    print(_T("Input sting: "));

    const int buffer_size = 255;
    TCHAR buffer[buffer_size];
    DWORD len;

    ReadConsole(hIn, buffer, sizeof(buffer), &len, nullptr);

    DWORD sum = 0;
    for (DWORD i = 0; buffer[i] != ' ' && i < len; i++) {
        if (buffer[i] == 0x0041 || buffer[i] == 0x0061 || buffer[i] == 0x0430 || buffer[i] == 0x0410) {
            sum++;
        }
    }

    print(_T("Count of founded \'A|a\' letters in input string: "));
    _itot_s(sum, buffer, buffer_size, 10);

    print(buffer);
    print(_T("\n"));

    system("pause");

    CloseHandle(hIn);
    CloseHandle(hOut);

    return 0;
}
