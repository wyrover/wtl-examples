
#include "stdafx.h"
#include "MainFrm.h"

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	return CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
	return FALSE;
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	HRESULT hResult;
	CString _filter;
	CSimpleArray<GUID> _guid_file_types;

	hResult = image_.GetExporterFilterString(_filter, _guid_file_types, L"All Image Files");
	if (FAILED(hResult))
	{
		return 0;
	}
	CFileDialog dlg(TRUE, NULL, NULL, OFN_SHAREAWARE, L".png");
	if (IDOK != dlg.DoModal())
		return 0;

	image_.Destroy();
	hResult = image_.Load(dlg.m_ofn.lpstrFile);
	if (FAILED(hResult))
	{
		return 0;
	}

	CString _title;
	_title.LoadString(IDR_MAINFRAME);
	SetWindowText(_title + " - " + CString(dlg.m_ofn.lpstrFile));
	
	return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	bHandled = FALSE;
	return 1;
}

LRESULT CMainFrame::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	WTL::CPaintDC dc(m_hWnd);
	//WTL::CMemoryDC memdc(&dc, &rect_client_);
	WTL::CDC _memdc;
	_memdc.CreateCompatibleDC(dc.m_hDC);

	WTL::CBitmap _bitmap;
	WTL::CBitmap _oldbitmap;
	if (_bitmap.CreateCompatibleBitmap(dc.m_hDC,rect_client_.Width(),rect_client_.Height()))  
	{  		
		_oldbitmap = _memdc.SelectBitmap(_bitmap.Detach());  
	}  

	
	CBrush back;
	back.CreateSolidBrush(RGB(220,215,254));
	HBRUSH pold = _memdc.SelectBrush(HBRUSH(back));
	CRect rect;
	_memdc.GetClipBox(&rect);
	_memdc.PatBlt (rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	_memdc.SelectBrush(pold);
	
	

	if (!image_.IsNull())
	{
		//image_.Draw(dc.m_hDC, 0, 0);
		image_.TransparentBlt(_memdc.m_hDC,0,0,image_.GetWidth(),image_.GetHeight(),RGB(255,255,255));
		dc.BitBlt(0, 0, rect_client_.Width(), rect_client_.Height(), _memdc, 0, 0, SRCCOPY);
	}

	_memdc.SelectBitmap(_oldbitmap);

	bHandled = TRUE;

	return 0;
}

LRESULT CMainFrame::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	// π”√OnEraseBkgnd¥∞ø⁄…¡À∏
	/*
	WTL::CClientDC dc(m_hWnd);
	CBrush back;
	back.CreateSolidBrush(RGB(220,215,254));
	HBRUSH pold = dc.SelectBrush(HBRUSH(back));
	CRect rect;
	dc.GetClipBox(&rect);
	dc.PatBlt (rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	dc.SelectBrush(pold);
	*/

	bHandled = TRUE;
	return 0;
}

LRESULT CMainFrame::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	GetClientRect(rect_client_);
	return 0;
}



