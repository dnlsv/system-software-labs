#include <windows.h>
#include <tchar.h>

bool headline = false, dblclick = false;

static TCHAR title[] = _T("DesktopApp");
static TCHAR g_szClassName[] = _T("WindowApplication");

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE ThisInstance, HINSTANCE PreviousInstance, LPSTR lpszArgument, int CommandShow)
{
    HWND FirstWindow;
    MSG Messages;
    WNDCLASS WindowClass;

    WindowClass.hInstance = ThisInstance;
    WindowClass.lpszClassName = g_szClassName;
    WindowClass.lpfnWndProc = WindowProcedure;
    WindowClass.lpszMenuName = NULL;
    WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    // перерисовка всего окна при изменении высоты и ширины окна,
    // а также перехват двойного клика
    WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    WindowClass.cbClsExtra = WindowClass.cbWndExtra = 0;
    WindowClass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    if (0 == RegisterClass(&WindowClass))
        return 0;

    // вычисление координат центра экрана
    INT x = (GetSystemMetrics(SM_CXSCREEN) - 600) / 2;
    INT y = (GetSystemMetrics(SM_CYSCREEN) - 375) / 2;

    FirstWindow = CreateWindow(g_szClassName, title, WS_OVERLAPPEDWINDOW, x, y, 600, 375, HWND_DESKTOP, NULL, ThisInstance, NULL);

    ShowWindow(FirstWindow, CommandShow);
    UpdateWindow(FirstWindow);

    while (GetMessage(&Messages, NULL, 0, 0))
    {
        TranslateMessage(&Messages);
        DispatchMessage(&Messages);
    }

    return Messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hWindow, UINT uMessage, WPARAM wFirstParameter, LPARAM lSecondParameter)
{
    switch (uMessage)
    {

        POINT pt;
        INPUT click;
        RECT rcClip;
        RECT* lprc;

        static LONG   xPosOldLeft;
        static LONG   xPosOldRight;
        static LONG   xPosNewLeft;
        static LONG   xPosNewRight;

        static LONG   xPosOld;

    case WM_NCMOUSEMOVE:
    {
        if (wFirstParameter == HTCAPTION)
        {
            GetWindowRect(hWindow, &rcClip);
            GetCursorPos(&pt);

            click.type = INPUT_MOUSE;
            click.mi.dx = pt.x;
            click.mi.dy = pt.y;
            click.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN;

            xPosOld = pt.x;

            xPosOldLeft = rcClip.left;
            xPosOldRight = rcClip.right;

            if (headline == false && dblclick == false)
            {
                SendInput(1, &click, sizeof(click));
                headline = true;
            }

        }

        if (wFirstParameter != HTCAPTION && headline == true && dblclick == true)
        {
            headline = false;
            dblclick = false;

        }

        return 0;
    }

    case WM_MOVING:
    {
        GetCursorPos(&pt);

        GetWindowRect(hWindow, &rcClip);

        xPosNewLeft = rcClip.bottom;
        xPosNewRight = rcClip.top;

        if ((xPosNewLeft >= xPosOldLeft || xPosNewLeft <= xPosOldLeft) && headline == true && dblclick == false)
        {
            lprc = (LPRECT)lSecondParameter;

            lprc->left = xPosOldLeft;
            lprc->right = xPosOldRight;

            SetCursorPos(xPosOld, pt.y);
        }

        return 0;
    }

    case WM_MOUSEMOVE:
    {
        if (wFirstParameter != HTCAPTION && headline == true && dblclick == true)
        {
            headline = false;
            dblclick = false;
        }
        return 0;
    }

    case WM_NCLBUTTONDBLCLK:
    {
        if (wFirstParameter == HTCAPTION)
            dblclick = true;
        return 0;
    }

    case WM_CLOSE:
    {
        DestroyWindow(hWindow);
        return 0;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hWindow, uMessage
            , wFirstParameter, lSecondParameter
        );
    }
    return 0;
}

//#include <windows.h>
//#include <tchar.h>
//
//static TCHAR window[] = _T("Okoshko");
//static TCHAR title[] = _T("Zagolovok okna");
//
//long CALLBACK WndProcedure(HWND Window, UINT Mess, UINT Parametr, long Prm)
//{
//	switch (Mess) {
//	case WM_PAINT:
//		return 0; 
//	case WM_CREATE:
//		return 0; 
//	case WM_CLOSE: 
//		DestroyWindow(Window); 
//		return 0;
//	case WM_DESTROY: 
//		PostQuitMessage(0); return 0;
//	}
//	return (DefWindowProc(Window, Mess, Parametr, Prm));
//
//}
//
//int WINAPI WinMain(HINSTANCE h, HINSTANCE hprev, char* CmdLine, int CmdShow)
//{
//	WNDCLASS WinClass;
//	MSG Mess;
//	HWND Window;
//	WinClass.lpfnWndProc = WndProcedure;
//	WinClass.lpszClassName = window;
//	WinClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	WinClass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	WinClass.style = CS_HREDRAW | CS_VREDRAW;
//	RegisterClass(&WinClass);
//	Window = CreateWindow(WinClass.lpszClassName, title, WS_OVERLAPPEDWINDOW, 0, 0, 600, 400, HWND_DESKTOP, NULL, h, NULL);
//	ShowWindow(Window, CmdShow);
//	UpdateWindow(Window);
//	while (GetMessage(&Mess, NULL, 0, 0)) {
//		TranslateMessage(&Mess);
//		DispatchMessage(&Mess);
//	}
//	return (Mess.wParam);
//}
