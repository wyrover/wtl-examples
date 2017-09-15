// Hover.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Hover.h"
#include "HoverDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHoverApp

BEGIN_MESSAGE_MAP(CHoverApp, CWinApp)
    //{{AFX_MSG_MAP(CHoverApp)
    //}}AFX_MSG
    ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHoverApp construction

CHoverApp::CHoverApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHoverApp object

CHoverApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHoverApp initialization

BOOL CHoverApp::InitInstance()
{
    // Standard initialization
#ifdef _AFXDLL
    Enable3dControls();         // Call this when using MFC in a shared DLL
#else
    Enable3dControlsStatic();   // Call this when linking to MFC statically
#endif
    CHoverDlg dlg;
    m_pMainWnd = &dlg;
    int nResponse = dlg.DoModal();

    if (nResponse == IDOK) {
    } else if (nResponse == IDCANCEL) {
    }

    // Since the dialog has been closed, return FALSE so that we exit the
    //  application, rather than start the application's message pump.
    return FALSE;
}
