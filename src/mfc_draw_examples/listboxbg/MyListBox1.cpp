// MyListBox1.cpp : implementation file
//

#include "stdafx.h"
#include "mylistbox.h"
#include "MyListBox1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListBox

CMyListBox::CMyListBox()
{
		m_brHollow.CreateStockObject(HOLLOW_BRUSH);	
		iSelectChange = FALSE;
}

CMyListBox::~CMyListBox()
{
}


BEGIN_MESSAGE_MAP(CMyListBox, CListBox)
	//{{AFX_MSG_MAP(CMyListBox)
	ON_CONTROL_REFLECT(LBN_SELCHANGE, OnSelchange)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListBox message handlers

void CMyListBox::OnSelchange() 
{
	iSelectChange = TRUE;
	Invalidate(TRUE);
}

HBRUSH CMyListBox::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(64,32,0));
	return m_brHollow;	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return NULL;
}



void CMyListBox::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();	
	CListBox::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMyListBox::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();
	CListBox::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CMyListBox::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	BITMAP bm;
	m_bmp.GetBitmap(&bm);
	m_pbmCurrent = &m_bmp;
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dcMem.SelectObject(m_pbmCurrent);
	pDC->BitBlt(0,0,bm.bmWidth,bm.bmHeight,&dcMem,0,0,SRCCOPY);
	dcMem.SelectObject(pOldBitmap);
	
	return CListBox::OnEraseBkgnd(pDC);
}

void CMyListBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(iSelectChange)
	{
		iSelectChange= FALSE;
		Invalidate();	
	}
	CListBox::OnLButtonDown(nFlags, point);
}
