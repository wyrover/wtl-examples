// TestWindow.h : main header file for the TestWindow application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTestWindowApp:
// See TestWindow.cpp for the implementation of this class
//

class CCustomWindowApp : public CWinApp
{
public:
	CCustomWindowApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCustomWindowApp theApp;