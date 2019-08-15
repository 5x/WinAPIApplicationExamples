#include <windows.h>
#include <conio.h>
#include <iostream>

#define N 4
#define notSelected 7
#define titleY 10

HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

void setCarret(int x, int y, int color) {
    COORD Coord = { x, y };
    SetConsoleCursorPosition(hOut, Coord);
    SetConsoleTextAttribute(hOut, color);
}

typedef LPTSTR(__cdecl* Class1)();

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleTitle(L"WAPIA3");

    HANDLE hConsoleOutput;
    CONSOLE_CURSOR_INFO structCursorInfo;

    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hConsoleOutput, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsoleOutput, &structCursorInfo);

    setCarret(2, 1, notSelected);
    printf("Select menu item:");

    const char* menu_list[N] = {
             "About", "GetWindowsDirectory", "DeviceIoControl",
             "Quit"
    },
        * menu_desc[N] = {
            "Application info",
            "The path to the directory where Windows is installed",
            "Disk Physical Structure", "Exit"
    };

    int i, x = 1;
    for (i = 0; i < N; ++i) {
        setCarret(x, i + 3, notSelected);
        printf(" %s ", menu_list[i]);
        setCarret(24, i + 3, notSelected);
        printf(" %s", menu_desc[i]);
    }

    i = 0;
    HINSTANCE hMyDll = LoadLibrary(L"ClassLibrary3");
    Class1 GetWinDirectory, DeviceIOContrSTR;

    if (!hMyDll) {
        setCarret(0, 0, 47);
        printf("Cant connect to DLL");

        system("pause");
        return -1;
    }

    GetWinDirectory = (Class1)GetProcAddress(hMyDll, "GetWinDirectory");
    DeviceIOContrSTR = (Class1)GetProcAddress(hMyDll, "DeviceIOContr");

    if (!GetWinDirectory || !DeviceIOContrSTR) {
        setCarret(0, 0, 47);
        printf("Cant load function");
        system("pause");
        return -1;
    }

    while (true) {
        setCarret(x, i + 3, 47);
        printf(" %s ", menu_list[i]);

        switch (_getch()) {
        case 72:
            if (i > 0) {
                setCarret(x, i + 3, notSelected);
                printf(" %s ", menu_list[i]);
                --i;
            }
            break;
        case 80:
            if (i < N - 1) {
                setCarret(x, i + 3, notSelected);
                printf(" %s ", menu_list[i]);
                ++i;
            }
            break;
        case 13:
            switch (i) {
            case 0:
                setCarret(2, titleY, notSelected);
                printf("%s", menu_list[i]);
                setCarret(0, titleY + 2, notSelected);
                printf("%s%s%s%s%s", "WAPIA Task #3\n",
                    "Subject:\tlibrary research\n");
                break;
            case 1:
                setCarret(2, titleY, notSelected);
                printf("%s: ", menu_desc[i]);
                setCarret(2, titleY + 2, 47);
                printf("%s", GetWinDirectory());
                break;
            case 2:
                setCarret(2, titleY, notSelected);
                printf("%s", menu_desc[i]);
                setCarret(0, titleY + 2, notSelected);
                printf("%s", DeviceIOContrSTR());
                break;
            case 3:
                FreeLibrary(hMyDll);
                return 0;
            default:
                break;
            }
        }
    }
}
