// CustomFrameTest.cpp : implementation file
//

#include "stdafx.h"
#include "CustomWindow.h"
#include "CustomFrameTest.h"


// CCustomFrameTest

IMPLEMENT_DYNCREATE(CCustomFrameTest, CCustomFrame)

CCustomFrameTest::CCustomFrameTest()
{

}

CCustomFrameTest::~CCustomFrameTest()
{
}


BEGIN_MESSAGE_MAP(CCustomFrameTest, CCustomFrame)
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


// CCustomFrameTest message handlers
BOOL CCustomFrameTest::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	CRect rect;
	GetClientRect(rect);
	rect.right -= 20;
	rect.bottom -= 20;
	rect.left = rect.right - 100;
	rect.top = rect.bottom - 50;
//	m_Btn.Create(L"Hello", WS_VISIBLE, rect, this, 1);
	return CCustomFrame::OnCreateClient(lpcs, pContext);
}

BOOL CCustomFrameTest::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
//	if (m_view.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	//	return TRUE;

	return CCustomFrame::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CCustomFrameTest::OnSetFocus(CWnd* pOldWnd)
{
//	m_view.SetFocus();
	CCustomFrame::OnSetFocus(pOldWnd);

	// TODO: Add your message handler code here
}

