// TransparentBltTest.h : main header file for the TRANSPARENTBLTTEST application
//

#if !defined(AFX_TRANSPARENTBLTTEST_H__62A98489_A83F_46B1_B69B_60F35EEDEF38__INCLUDED_)
#define AFX_TRANSPARENTBLTTEST_H__62A98489_A83F_46B1_B69B_60F35EEDEF38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTransparentBltTestApp:
// See TransparentBltTest.cpp for the implementation of this class
//

class CTransparentBltTestApp : public CWinApp
{
public:
	CTransparentBltTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentBltTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTransparentBltTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSPARENTBLTTEST_H__62A98489_A83F_46B1_B69B_60F35EEDEF38__INCLUDED_)
