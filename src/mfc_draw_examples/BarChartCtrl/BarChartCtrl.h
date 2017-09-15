// BarChartCtrl.h : main header file for the BARCHARTCTRL application
//

#if !defined(AFX_BARCHARTCTRL_H__CEEC0CEF_217B_4250_B7BD_F28CCB63A30E__INCLUDED_)
#define AFX_BARCHARTCTRL_H__CEEC0CEF_217B_4250_B7BD_F28CCB63A30E__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBarChartCtrlApp:
// See BarChartCtrl.cpp for the implementation of this class
//

class CBarChartCtrlApp : public CWinApp
{
public:
    CBarChartCtrlApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CBarChartCtrlApp)
public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation

    //{{AFX_MSG(CBarChartCtrlApp)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BARCHARTCTRL_H__CEEC0CEF_217B_4250_B7BD_F28CCB63A30E__INCLUDED_)
