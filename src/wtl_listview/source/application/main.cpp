/*
    @author Ilnaz Nizametdinov

    @project HelloYandex

    @description
        Main source file for application.
 */

#include "stdafx.h"

#include "resource/resource.h"
#include "gui/main/main_dlg.h"

CAppModule _Module;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpstrCmdLine, int nCmdShow)
{
    HRESULT hResult = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
    ATLASSERT(SUCCEEDED(hResult));
    ::DefWindowProc(NULL, 0, 0, 0L);
    AtlInitCommonControls(ICC_BAR_CLASSES);
    hResult = _Module.Init(NULL, hInstance);
    ATLASSERT(SUCCEEDED(hResult));
    int nRet = 0;
    {
        CMainDlg dlgMain;
        nRet = dlgMain.DoModal();
    }
    _Module.Term();
    ::CoUninitialize();
    return nRet;
}
