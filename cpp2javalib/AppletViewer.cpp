/**
 * @file
 *
 * $Id: cpp2java.AppletViewer.cpp,v 1.5 2008/03/11 16:57:48 matsushima Exp $
 *
 * cpp2java.AppletViewer.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/19 matsushima cpp2javalib
 * @version $Revision: 1.5 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: cpp2java.AppletViewer.cpp,v $
 * Revision 1.5  2008/03/11 16:57:48  matsushima
 * スレッド同期 Object.wait(), notify()
 *
 * Revision 1.4  2007/11/30 22:42:27  matsushima
 * 再登録
 *
 * Revision 1.3  2007/05/09 12:41:09  matsushima
 * Component.repaint() の同期
 *
 * Revision 1.2  2007/04/23 17:06:33  matsushima
 * リプレース
 *
 * Revision 1.1.1.1  2006/08/17 20:26:00  matsushima
 * new
 *
 */

#include "stdafx.h"
#include "AppletViewer.h"
#include "java/lang/System"
#include "java/awt/Graphics"
#include <windows.h>
#include <commctrl.h>
#include "afxres.h"

void ap_split()
{
	char path[_MAX_PATH];
	_makepath_s(path, "C:", "test", "test", NULL);
}

/*------------------------------------------------------------*/

#define APP_NAME            "TER_NAME"     // 内部名
#define APP_TITLE           "TER_TITLE"    // タイトルバーなど

static HINSTANCE g_hInstance;
static HWND g_hWnd;
static HWND g_hWndStatusBar;

static LRESULT on_create(HWND hWnd, CREATESTRUCT* cs) // 0 or -1
{
    AppletViewer* _this = (AppletViewer*)cs->lpCreateParams;
    SetWindowLong(hWnd, GWL_USERDATA, (LPARAM)_this);
    HWND hwnd_applet = (HWND)_this->applet->hwnd;
    SetWindowLong(hwnd_applet, GWL_STYLE,
        (LPARAM)(WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS));
    SetParent((HWND)hwnd_applet, hWnd);
    _ASSERTE(SetWindowPos(hwnd_applet, NULL, 0, 0, 0, 0,
        SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_SHOWWINDOW));
    RECT rc;
    GetWindowRect(hwnd_applet, &rc);
    AdjustWindowRectEx(&rc, cs->style, FALSE, cs->dwExStyle);
    _ASSERTE(SetWindowPos(hWnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
        SWP_NOACTIVATE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_SHOWWINDOW));
    _this->applet->init();
    _this->applet->start();
    return 0;
}

static LRESULT on_close(HWND hWnd, bool no_prompt = false) // WM_ENDSESSION では終了確認メッセージを表示しない
{
    return 0;
}

volatile boolean in_destroy, in_update;
static LRESULT on_destroy(HWND hWnd, AppletViewer* _this = NULL)
{
    in_destroy = true;
/*
    AppletViewer* _this;
*/
if(NULL == _this)
    _ASSERTE(_this = (AppletViewer*)GetWindowLong(hWnd, GWL_USERDATA));
    _this->applet->stop();
    Object::term_events();
extern int thread_cnt;
while (thread_cnt > 0)
{
Sleep(100);
}
    _this->applet->destroy();
    return 0;
}

static LRESULT on_paint(HWND hWnd, HDC hdc, PAINTSTRUCT* ps)
{
    return 0;
}

static LRESULT on_command(HWND hWnd, int id, int code, HWND hctl, WPARAM wParam, LPARAM lParam)
{
    switch (id)
    {
    case ID_APP_EXIT:
        {
            in_destroy = true;
            SendMessage(hWnd, WM_CLOSE, 0, 0);
            break;
        }
    }
    return 0;
}

static LRESULT on_notify(HWND hWnd, int id, int code, HWND hctl, NMHDR* nmhdr, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

static LRESULT CALLBACK WindowProc(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        {
System::out.println("<- WindowProc(WM_CREATE)");
            g_hWnd = hWnd;
            return on_create(hWnd, (CREATESTRUCT*)lParam);
System::out.println("-> WindowProc(WM_CREATE)");
        }
    case WM_CLOSE:
        {
            in_destroy = true;
            if (0 == on_close(hWnd))
            {
                DestroyWindow(hWnd);
            }
            return 0;
        }
    case WM_ENDSESSION:
        {
            on_close(hWnd, true); // WM_ENDSESSION では終了確認メッセージを表示しない
            break;
        }
    case WM_DESTROY:
        {
            if (0 == on_destroy(hWnd))
            {
                PostQuitMessage(0);
            }
            return 0;
        }
    case WM_NCDESTROY:
        {
char buf[100];
sprintf(buf, "-> WindowProc(WM_NCDESTROY):"
"hWnd=%08x,GWL_WNDPROC=%08x,WindowProc=%08x",
hWnd, GetWindowLong(hWnd, GWL_WNDPROC), WindowProc);
System::out.println(buf);
            break;
        }
    case WM_SIZE:
        {
            INT widths[] = { LOWORD(lParam) - 200, -1 };
            SendMessage(g_hWndStatusBar, SB_SETPARTS, (WPARAM)2, (LPARAM)widths);
            SendMessage(g_hWndStatusBar, uMsg, wParam, lParam);
#ifdef APP_DOCKWND
            SendMessage(g_hWndDockWnd, uMsg, wParam, lParam);
#elif defined(APP_TOOLBAR)
            SendMessage(g_hWndToolbar, uMsg, wParam, lParam);
#endif
            return 0;
        }
    case WM_SETFOCUS:
        {
            AppletViewer* _this;
            _ASSERTE(_this = (AppletViewer*)GetWindowLong(hWnd, GWL_USERDATA));
            SetFocus((HWND)_this->applet->hwnd);
            break;
        }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            LRESULT result = on_paint(hWnd, hdc, &ps);
            EndPaint(hWnd, &ps);
            return result;
        }/*
    case WM_ERASEBKGND:
        {
            return (LRESULT)NULL;
        }*/
    case WM_COMMAND:
        {
            int id = LOWORD(wParam);
            int code = HIWORD(wParam);
            HWND hctl = (HWND)lParam;
            on_command(hWnd, id, code, hctl, wParam, lParam);
#ifdef APP_MDI
            break; // MDI Frame のデフォルトのコマンド処理
#else
            return 0;
#endif
        }
    case WM_NOTIFY:
        {
            int id = (int)wParam;
            NMHDR* nmhdr = (NMHDR*)lParam;
            HWND hctl = nmhdr->hwndFrom;
            int code = nmhdr->code;
            on_notify(hWnd, id, code, hctl, nmhdr, wParam, lParam);
            break;
        }
    case WM_MENUSELECT:
        {
            //on_menuselect(hWnd, LOWORD(wParam), HIWORD(wParam), (HMENU)lParam);
            break;
        }
#ifdef APP_TIMER_SPAN
    case WM_TIMER:
        {
            return on_timer(hWnd, uMsg, wParam, lParam);
        }
#endif
    }
#ifdef APP_MDI
    return LibWin_DockWnd_DefWindowProc(hWnd, g_hWndDockWnd, uMsg, wParam, lParam);
#else
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
#endif
}

static int WINAPI _WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow,
    AppletViewer* _this)
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
//LIBDEBUG_UNLINK;
    g_hInstance = hInstance;

    // Init application
    WNDCLASSEX wc;
    memset(&wc, 0, sizeof(wc));
    wc.cbSize        = sizeof(wc);
    wc.style         = CS_VREDRAW | CS_HREDRAW;
    wc.lpfnWndProc   = WindowProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    //_ASSERTE(wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP)));
    _ASSERTE(wc.hCursor       = LoadCursor(NULL, IDC_ARROW));
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.lpszMenuName  = NULL;//MAKEINTRESOURCE(IDR_MENU);
    wc.lpszClassName = APP_NAME;
    //_ASSERTE(wc.hIconSm       = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_APP), IMAGE_ICON,
    //    GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR)*/);
    ATOM atom;
    _ASSERTE(atom = RegisterClassEx(&wc));
    if (0 == atom)
    {
        return -1;
    }

    // Init instance
    HWND hWnd;
    _ASSERTE(hWnd = CreateWindowEx(
        0,
        APP_NAME, APP_TITLE,
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, _this));
    if (NULL == hWnd)
    {
        return -1;
    }
    ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);

    // Init resources
#ifdef APP_ACCELERATOR
    HACCEL haccel;
    _ASSERTE(haccel = LoadAccelerators(g_hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR)));
#endif
#ifdef APP_TIMER_SPAN
    UINT timer_id;
    _ASSERTE(timer_id = SetTimer(hWnd, 1, APP_TIMER_SPAN, NULL));
#endif

    // Message loop
    MSG msg;
    BOOL res_msg;
    while ((res_msg = GetMessage(&msg, NULL, 0, 0)) > 0)
    {
#ifdef APP_MDI
        if (FALSE == LibWin_DockWnd_IsDockWndMessage(g_hWndDockWnd, &msg))
#endif
#ifdef APP_ACCELERATOR
        if (FALSE == TranslateAccelerator(hWnd, haccel, &msg))
#endif
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    _ASSERTE((-1 != res_msg/* = GetMessage(&msg, NULL, 0, 0)*/));

    // Terminate application
#ifdef APP_TIMER_SPAN
    KillTimer(hWnd, timer_id);
#endif
//on_destroy(hWnd, _this);
    return msg.wParam;
}

AppletViewer::AppletViewer(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow,
    Applet* applet,
    int width,
    int height)
{
#ifdef _DEBUG
    System::out.stream = PrintStream::OUT_OUTPUTDEBUGSTRING;
#else
    System::out.stream = PrintStream::OUT_WINDOW;
#endif

    this->applet = applet;
    applet->setSize(width, height);
    _WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow, this);
}
