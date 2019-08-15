#include <windows.h>
#include <tchar.h>

struct WndAttr {
    LPCWSTR windowClassName;
    LPCWSTR windowTitleName;
    UINT    style;
    SIZE    size;
    POINT   startPosition;
};

//Forward declarations of functions
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
HWND                CreateWnd(HINSTANCE, WNDPROC, int, HWND, WndAttr);

HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    SIZE size = { LONG(500), LONG(500) };
    WndAttr mainWndAttr = {
        _T("mainWindow"),
        _T("Window application title name"),
        WS_OVERLAPPEDWINDOW,
        size, {
            (GetSystemMetrics(SM_CXSCREEN) - size.cx) / 2,
            (GetSystemMetrics(SM_CYSCREEN) - size.cy) / 2
        }
    };

    if (!CreateWnd(hInstance, WndProc, nCmdShow, NULL, mainWndAttr)) {
        return 0;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

//Processes messages for the main window.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR text[] = _T("Hello world");

    switch (message) {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        SetTextColor(hdc, RGB(255, 255, 255));
        SetBkColor(hdc, RGB(0, 0, 0));
        TextOut(hdc, 5, 5, text, _tcslen(text));
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

HWND CreateWnd(HINSTANCE hInstance, WNDPROC wndProc, int nCmdShow,
    HWND hWndParent, WndAttr wndAttr) {
    WNDCLASS wndc = {
        CS_HREDRAW | CS_VREDRAW,               //class style(s)
        wndProc,                                    //pointer to the window procedure
        0, 0,                     //numof extra bytes to alloc win class struct | inst
        hInstance,                                  //handle to instance -> window procedure
        LoadIcon(NULL, IDI_APPLICATION),    //icon class
        LoadCursor(NULL, IDC_ARROW),        //cursor class
        (HBRUSH)GetStockObject(BLACK_BRUSH),      //background brush
        NULL,                            //Menu class name
        wndAttr.windowClassName                    //Window class name
    };

    if (!RegisterClass(&wndc)) {
        MessageBox(NULL, _T("RegisterClass failed!"), _T("Error #1"), NULL);
        return NULL;
    }

    hInst = hInstance;  //Store instance handle in our global variable

    HWND hWnd = CreateWindow(
        wndAttr.windowClassName,            //the name of the application
        wndAttr.windowTitleName,            //the text that appears in the title bar
        wndAttr.style,                      //the type of window to create
        wndAttr.startPosition.x,            //initial position (x, y)
        wndAttr.startPosition.y,
        wndAttr.size.cx,                    //initial size (width, height)
        wndAttr.size.cy,
        hWndParent,                         //the parent of this window
        NULL,                               //this application does not have a menu bar
        hInstance,                          //the first parameter from WinMain
        NULL                                //not used in this application
    );

    if (!hWnd) {
        MessageBox(NULL, _T("CreateWindow failed!"), _T("Error #2"), NULL);
        return NULL;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return hWnd;
}
