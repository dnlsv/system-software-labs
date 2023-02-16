#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("WindowApplication");

bool flag = false;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
        return 1;

    INT x = (GetSystemMetrics(SM_CXSCREEN) - 500) / 2;
    INT y = (GetSystemMetrics(SM_CYSCREEN) - 400) / 2;

    HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZE, x,
        y, 500, 400, NULL, NULL, hInstance, NULL);

    if (!hWnd)
        return 1;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    TCHAR greeting[] = _T("Hello, Windows desktop!");

    int width = 0, height = 0;

    POINT cp;

    INT y = (GetSystemMetrics(SM_CYSCREEN) - 400) / 2;

    RECT w, c;
    GetWindowRect(hWnd, &w);
    GetClientRect(hWnd, &c);

    INPUT click;

    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_NCMOUSEMOVE:
        width = LOWORD(lParam);
        GetCursorPos(&cp);
        if (cp.x >= w.left && cp.x <= w.left + width && cp.y >= w.top && cp.y <= w.top + w.bottom - w.top - c.bottom + c.top && flag == false)
        {
            click.type = INPUT_MOUSE;
            click.mi.dx = cp.x;
            click.mi.dy = cp.y;
            click.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN;

            SendInput(1, &click, sizeof(click));
        }
        break;
    case WM_MOVING:
        GetCursorPos(&cp);
        SetCursorPos(cp.x, y);
        break;
    case WM_NCLBUTTONDBLCLK:
        flag = true;
        break;
    case WM_MOUSEMOVE:
        if (flag == true)
            flag = false;
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}