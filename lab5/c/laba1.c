// #include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

LRESULT __stdcall WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == WM_DESTROY) PostQuitMessage(0);

    else if (message = WM_KEYDOWN) printf("code = %d\n", wparam);

    else if (message == WM_CHAR) printf("%c\n", wparam);

    else return DefWindowProcA(hwnd, message, wparam, lparam);
}

int main(int argc, char *argv[])
{
    // int g_array[127] = {0};
    WNDCLASSA wcl;
        memset(&wcl, 0, sizeof(WNDCLASSA));
        wcl.lpszClassName = "my Window";
        wcl.lpfnWndProc = WndProc;
    RegisterClassA(&wcl);

    HWND hwnd;
    hwnd = CreateWindow("my Window", "Window Name2", WS_OVERLAPPEDWINDOW,
    10, 10, 640, 480, NULL, NULL, NULL, NULL);

    ShowWindow(hwnd, SW_SHOWNORMAL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // if (argc == 2) show_stat(scan_text(argv[1], g_array), g_array);
    // else write(1, "Wrong number of params.\n", 24);

    return 0;
}