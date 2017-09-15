// CPPHtmlStatic_demo.h : main header file for the CPPHTMLSTATIC_DEMO application
//

#if !defined(AFX_CPPHTMLSTATIC_DEMO_H__16EFAA52_AE87_4A88_A445_62345332ABB7__INCLUDED_)
#define AFX_CPPHTMLSTATIC_DEMO_H__16EFAA52_AE87_4A88_A445_62345332ABB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPPHtmlStatic_demoApp:
// See CPPHtmlStatic_demo.cpp for the implementation of this class
//

class CPPHtmlStatic_demoApp : public CWinApp
{
public:
	CPPHtmlStatic_demoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPPHtmlStatic_demoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPPHtmlStatic_demoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPPHTMLSTATIC_DEMO_H__16EFAA52_AE87_4A88_A445_62345332ABB7__INCLUDED_)
