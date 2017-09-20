// wtl_dialog_template.cpp : main source file for wtl_dialog_template.exe
//

#include "stdafx.h"

#include "resource.h"

#include "MainDlg.h"

#include <GdiPlus.h>
#pragma comment(lib, "GdiPlus.lib")

using namespace Gdiplus;



class CApplication : public WTL::CAppModule
{
public:
    HRESULT Init(HINSTANCE hInstance);
    void Term();
public:
    static CApplication& GetInstance();
   
private:
    ULONG_PTR gdiplus_token_;
    

};

HRESULT CApplication::Init(HINSTANCE hInstance)
{
    HRESULT hRes = ::CoInitialize(NULL);
    // If you are running on NT 4.0 or higher you can use the following call instead to
    // make the EXE free threaded. This means that calls come in on a random RPC thread.
    //  HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
    ATLASSERT(SUCCEEDED(hRes));
    GdiplusStartupInput gdiplusStartupInput;    
    GdiplusStartup(&gdiplus_token_, &gdiplusStartupInput, NULL);
    // this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
    ::DefWindowProc(NULL, 0, 0, 0L);
    AtlInitCommonControls(ICC_BAR_CLASSES); // add flags to support other controls

    hRes =  CAppModule::Init(NULL, hInstance);

    AtlAxWinInit();

    return hRes;
}

void CApplication::Term()
{
    CAppModule::Term();
    // Ð¶ÔØGDI+
    GdiplusShutdown(gdiplus_token_);

    ::CoUninitialize();
    
}

CApplication& CApplication::GetInstance()
{    
    static CApplication module_;
    return module_;
}




int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{    
    
    CApplication::GetInstance().Init(hInstance);    
    
    int nRet = 0;    
    {
        CMainDlg dlgMain;
        nRet = dlgMain.DoModal();
    }
    CApplication::GetInstance().Term();    
    
    return nRet;
}
