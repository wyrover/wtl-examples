///////////////////////////////////////////////////////////////////////////
// TreeTest.cpp : Implementation of Class TreeTest
///////////////////////////////////////////////////////////////////////////
//
// Copyright(C) 2005 Jim Alsup  All rights reserved
//
// License: You may use, or derive works from this file without any
//          restrictions except those listed below.
//
//        - This original header must be kept in the derived work.
//
//        - If your derived work is distributed in any form, you must notify
//          the author via the email address above and provide a short
//          description of the product and intended audience.  Offering
//          the author a free licensed copy of the product is not required,
//          but does endear you with good karma points.
//
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VividTree.h"
#include "TreeTest.h"
#include "TreeTestDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif


// CTreeTestApp

BEGIN_MESSAGE_MAP(CTreeTestApp, CWinApp)
    ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTreeTestApp construction

CTreeTestApp::CTreeTestApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}


// The one and only CTreeTestApp object

CTreeTestApp theApp;


// CTreeTestApp initialization

BOOL CTreeTestApp::InitInstance()
{
    // InitCommonControls() is required on Windows XP if an application
    // manifest specifies use of ComCtl32.dll version 6 or later to enable
    // visual styles.  Otherwise, any window creation will fail.
    InitCommonControls();
    CWinApp::InitInstance();
    // Standard initialization
    // If you are not using these features and wish to reduce the size
    // of your final executable, you should remove from the following
    // the specific initialization routines you do not need
    // Change the registry key under which our settings are stored
    // TODO: You should modify this string to be something appropriate
    // such as the name of your company or organization
    SetRegistryKey(_T("Local AppWizard-Generated Applications"));
    CTreeTestDlg dlg;
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();

    if (nResponse == IDOK) {
        // TODO: Place code here to handle when the dialog is
        //  dismissed with OK
    } else if (nResponse == IDCANCEL) {
        // TODO: Place code here to handle when the dialog is
        //  dismissed with Cancel
    }

    // Since the dialog has been closed, return FALSE so that we exit the
    //  application, rather than start the application's message pump.
    return FALSE;
}
