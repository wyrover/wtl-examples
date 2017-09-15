// Kibbles.cpp : main source file for Kibbles.exe
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Kibbles.h"
#include "KibblesView.h"
#include "aboutdlg.h"
#include "MainFrm.h"

CAppModule _Module;

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
    CMessageLoop theLoop;
    _Module.AddMessageLoop(&theLoop);
    CMainFrame wndMain;

    if (wndMain.CreateEx() == NULL) {
        ATLTRACE(_T("Main window creation failed!\n"));
        return 0;
    }

    wndMain.ShowWindow(nCmdShow);
    int nRet = theLoop.Run();
    _Module.RemoveMessageLoop();
    return nRet;
}


//////////////////////////////////////////////////////////////////////
// WinMain() - app entry point

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
    HRESULT hr;
    // Init OLE and join an STA.
    hr = OleInitialize(NULL);

    if (FAILED(hr)) {
        CString sMsg;
        sMsg.Format(IDS_COMINIT_FAILED, _E(hr));
        AtlMessageBox(NULL, (LPCTSTR) sMsg, IDS_MSGBOX_TITLE, MB_ICONERROR);
        return 1;   // uh-oh, something Bad happened
    }

    // The impersonation level must be at least RPC_C_IMP_LEVEL_IMPERSONATE.
    hr = CoInitializeSecurity(NULL, -1, NULL, NULL,
                              RPC_C_AUTHN_LEVEL_CONNECT,
                              RPC_C_IMP_LEVEL_IMPERSONATE,
                              NULL, EOAC_NONE, 0);

    if (FAILED(hr)) {
        // Again, something Bad.
        CString sMsg;
        sMsg.Format(IDS_COINITSECURITY_FAILED, _E(hr));
        AtlMessageBox(NULL, (LPCTSTR) sMsg, IDS_MSGBOX_TITLE, MB_ICONERROR);
        CoUninitialize();
        return 1;
    }

    AtlInitCommonControls(ICC_WIN95_CLASSES);
    srand(GetTickCount());
#if _ATL_VER < 0x0700
    _Module.Init(NULL, hInstance);
#else
    _Module.Init(NULL, hInstance, &LIBID_ATLLib);
#endif
    int nRet = Run(lpstrCmdLine, nCmdShow);
    _Module.Term();
    OleUninitialize();
    return nRet;
}


//////////////////////////////////////////////////////////////////////
// JobStateToString() - return a string description of a job state value

LPCTSTR JobStateToString(const BG_JOB_STATE state)
{
    static std::map<BG_JOB_STATE, CString> m;
    static bool s_bFirstCall = true;

    // The first time this function is called, set up the map with descriptions
    // of all the job states.
    if (s_bFirstCall) {
        s_bFirstCall = false;
        m[BG_JOB_STATE_QUEUED].LoadString(IDS_JOB_STATE_QUEUED);
        m[BG_JOB_STATE_CONNECTING].LoadString(IDS_JOB_STATE_CONNECTING);
        m[BG_JOB_STATE_TRANSFERRING].LoadString(IDS_JOB_STATE_TRANSFERRING);
        m[BG_JOB_STATE_SUSPENDED].LoadString(IDS_JOB_STATE_SUSPENDED);
        m[BG_JOB_STATE_ERROR].LoadString(IDS_JOB_STATE_ERROR);
        m[BG_JOB_STATE_TRANSIENT_ERROR].LoadString(IDS_JOB_STATE_TRANSIENT_ERROR);
        m[BG_JOB_STATE_TRANSFERRED].LoadString(IDS_JOB_STATE_TRANSFERRED);
        m[BG_JOB_STATE_ACKNOWLEDGED].LoadString(IDS_JOB_STATE_ACKNOWLEDGED);
        m[BG_JOB_STATE_CANCELLED].LoadString(IDS_JOB_STATE_CANCELLED);
    }

    std::map<BG_JOB_STATE, CString>::const_iterator it;
    it = m.find(state);

    if (it != m.end())
        return it->second;

    CString sRet;
    sRet.Format(IDS_JOB_STATE_UNKNOWN, state);
    return sRet;
}
