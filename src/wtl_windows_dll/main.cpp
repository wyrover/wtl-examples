// wtl_windows_dll.cpp : 定义 DLL 应用程序的入口点。
//

#include "wtl_windows_dll/wtl_common.h"
#include "wtl_windows_dll/dlg/dlg_main.h"

CAppModule _Module;

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved
                     )
{
    return TRUE;
}


CMainDlg* g_maindlg;


BOOL ScreenToClient(HWND hwnd, LPRECT lpRect)
{
    ATLASSERT(::IsWindow(hwnd));

    if (!::ScreenToClient(hwnd, (LPPOINT)lpRect))
        return FALSE;

    return ::ScreenToClient(hwnd, ((LPPOINT)lpRect) + 1);
}

BOOL ClientToScreen(HWND hwnd, LPRECT lpRect)
{
    ATLASSERT(::IsWindow(hwnd));

    if (!::ClientToScreen(hwnd, (LPPOINT)lpRect))
        return FALSE;

    return ::ClientToScreen(hwnd, ((LPPOINT)lpRect) + 1);
}

extern "C" __declspec(dllexport) HWND __stdcall init_maindlg(HWND parent, int x, int y, int width, int height)
{
    CRect rect(x, y, x + width, y + height);
    /*CRect rect;
    ::GetWindowRect(parent, &rect);
    ClientToScreen(parent, &rect);
    rect.OffsetRect(x, y);
    LPCRECT rect2 = LPCRECT(rect);
    rect.SetRect(rect2->left, rect2->top, rect2->left + width, rect2->top + height);*/
    //ScreenToClient(parent, &rect);
    //ScreenToClient(parent, &rect);
    //::MessageBox(NULL, L"test1", L"test_dlg", MB_OK);
    g_maindlg = new CMainDlg();
    HWND maindlg_hwnd = g_maindlg->Create(parent, NULL);
    g_maindlg->MoveWindow(&rect);
    g_maindlg->ShowWindow(SW_SHOW);
    return maindlg_hwnd;
}


