// MyListBoxCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "mylistbox.h"
#include "MyListBoxCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListBoxCtrl

CMyListBoxCtrl::CMyListBoxCtrl()
{
}

CMyListBoxCtrl::~CMyListBoxCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListBoxCtrl, CListBox)
	//{{AFX_MSG_MAP(CMyListBoxCtrl)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListBoxCtrl message handlers

HBRUSH CMyListBoxCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CListBox::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CMyListBoxCtrl::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CListBox::OnEraseBkgnd(pDC);
}
