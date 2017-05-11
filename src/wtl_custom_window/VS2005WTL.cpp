// VS2005WTL.cpp : main source file for VS2005WTL.exe
//

#include "stdafx.h"

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>

#include "resource.h"

#include "MainDlg.h"
#include "MyWindow.h"


CAppModule _Module;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
    HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//  HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
    ATLASSERT(SUCCEEDED(hRes));
    // this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
    ::DefWindowProc(NULL, 0, 0, 0L);
    AtlInitCommonControls(ICC_BAR_CLASSES); // add flags to support other controls
    hRes = _Module.Init(NULL, hInstance);
    ATLASSERT(SUCCEEDED(hRes));
    CMyWindow mywindow;
    MSG msg;

    if (NULL == mywindow.Create(NULL, CWindow::rcDefault, _T("My First ATL Window"))) {
        ::MessageBox(NULL, _T("创建失败"), _T("创建失败"), MB_OK);
    }

    mywindow.ShowWindow(SW_SHOW);
    mywindow.UpdateWindow();

    // Run the message loop
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    int nRet = 0;
    /*

    // BLOCK: Run application
    {
        CMainDlg dlgMain;
        nRet = dlgMain.DoModal();
    }

    */
    _Module.Term();
    ::CoUninitialize();
    return nRet;
}
