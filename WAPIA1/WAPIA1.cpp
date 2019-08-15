#include <windows.h>

DWORD  StrLen(const WCHAR str[]);

HANDLE	hIn,
hOut;
SHORT CONST bufSize = 255;

DWORD ConsoleIn(LPVOID str) {
    DWORD strLen;
    ReadConsole(hIn, str, bufSize, &strLen, nullptr);
    return strLen;
}

void ConsoleOut(LPVOID str, DWORD len) {
    WriteConsole(hOut, str, len, nullptr, nullptr);
}

void ConsoleOut(WCHAR* str) {
    ConsoleOut(str, StrLen(str));
}

DWORD  StrLen(const WCHAR str[]) {
    DWORD len = 0;

    while (str[len] != NULL) {
        len++;
    }

    return len;
}

int main() {
    hIn = GetStdHandle(STD_INPUT_HANDLE);
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    WCHAR inputValue[bufSize];
    const DWORD dwNumRead = ConsoleIn(inputValue);

    ConsoleOut(inputValue, dwNumRead);

    system("pause");

    return 0;
}
