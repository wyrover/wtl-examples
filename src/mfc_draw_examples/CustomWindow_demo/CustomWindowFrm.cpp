// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CustomWindow.h"

#include "CustomWindowFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame
#define WINDOW_STATIC	200
IMPLEMENT_DYNAMIC(CCustomFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CCustomFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_GETMINMAXINFO()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CCustomFrame::CCustomFrame():b_maximized(FALSE)
{
	//Set the windows frame parameters
	winStats.bdr_wdth =13;
	winStats.frm_clp_wdth = 5;
	winStats.titlb_sz = 43;
	winStats.ico_size = 20;
	cr_bkgnd = RGB(120,23,33);
	cr_frm = RGB(84,23,34);
}

CCustomFrame::~CCustomFrame()
{
		m_CustomRgn.Detach();
}


int CCustomFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CCustomFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CCustomFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG



BOOL CCustomFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	CRect rect;
	GetClientRect(rect);
	
	m_CustomRgn.CreateRoundRectRgn(rect.left + winStats.frm_clp_wdth, 
		rect.top + winStats.frm_clp_wdth
		, rect.right - winStats.frm_clp_wdth, rect.bottom - winStats.frm_clp_wdth, 20,20);
    VERIFY(SetWindowRgn(m_CustomRgn , TRUE ));
	st_winNm.Create(L"Custom Window", WS_CHILD | WS_VISIBLE, 
	CRect(rect.left + winStats.bdr_wdth + winStats.ico_size + 4, 
	rect.top  + 15 , 
	rect.left + 150, 
	rect.top + 30), this, WINDOW_STATIC);
	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

BOOL CCustomFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle , CWnd* pParentWnd , CCreateContext* pContext)
{
	BOOL bRet = CFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext);
	if(bRet)
	{
		ModifyStyle(WS_CAPTION, WS_CLIPCHILDREN); //Remove the titilebar from the frame using the ModifyStyle
		ModifyStyleEx(WS_EX_CLIENTEDGE,0);			//Remove the border
	}
	
	return true;
}

void CCustomFrame::OnPaint()
{
	CPaintDC dc(this); 
	CRect rect;
	CRect rectD;
	CRect rectL,rectR, rectT, rectB;
	GetClientRect(rect);
	rectL.CopyRect(CRect(rect.left, rect.top, rect.left + winStats.bdr_wdth, rect.bottom));
	rectR.CopyRect(CRect(rect.right - winStats.bdr_wdth, rect.top, rect.right, rect.bottom));
	rectT.CopyRect(CRect(rect.left, rect.top, rect.right, rect.top + winStats.titlb_sz));
	rectB.CopyRect(CRect(rect.left, rect.bottom - winStats.bdr_wdth, rect.right, rect.bottom));
	
	rectD.CopyRect(CRect(rect.left + winStats.bdr_wdth, 
										rect.top + winStats.titlb_sz, 
						rect.right - winStats.bdr_wdth, 
						rect.bottom - winStats.bdr_wdth));
	
	//Paint the frame
	dc.FillSolidRect(rectL, cr_frm);
	dc.FillSolidRect(rectR, cr_frm);
	dc.FillSolidRect(rectT, cr_frm);
	dc.FillSolidRect(rectB, cr_frm);

	//Draw system icons
	HICON icon = AfxGetApp()->LoadIcon(IDI_CLOSE);
	DrawIconEx(dc.m_hDC, rect.right - winStats.ico_size - winStats.bdr_wdth, 
		rect.top + winStats.bdr_wdth, icon, 
		winStats.ico_size, winStats.ico_size, 0,
						   NULL, DI_NORMAL | DI_COMPAT);

	icon = AfxGetApp()->LoadIcon(IDI_MAXIMIZE);
	DrawIconEx(dc.m_hDC, rect.right - winStats.ico_size * 2 - winStats.bdr_wdth, 
		rect.top + winStats.bdr_wdth, icon, winStats.ico_size, 
		winStats.ico_size, 0,
						   NULL, DI_NORMAL | DI_COMPAT);

	icon = AfxGetApp()->LoadIcon(IDI_MINIMIZE);
	DrawIconEx(dc.m_hDC, rect.right - winStats.ico_size * 3 - winStats.bdr_wdth, 
		rect.top + winStats.bdr_wdth, icon, 
		winStats.ico_size, winStats.ico_size, 0,
						   NULL, DI_NORMAL | DI_COMPAT);

	icon = AfxGetApp()->LoadIcon(IDI_APP);
	DrawIconEx(dc.m_hDC, rect.left + winStats.bdr_wdth, 
		rect.top + winStats.bdr_wdth, icon, winStats.ico_size, 
		winStats.ico_size, 0,
					  NULL, DI_NORMAL | DI_COMPAT);
	
	dc.FillSolidRect(rectD, cr_bkgnd); 
	
}

void CCustomFrame::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(!HandleCutomeFrame(point))
		return ;
	CFrameWnd::OnLButtonDown(nFlags, point);
}

void CCustomFrame::OnMouseMove(UINT nFlags, CPoint point)
{
	HandleCustomeFrameCursor(point);
	CFrameWnd::OnMouseMove(nFlags, point);
}

void CCustomFrame::OnSize(UINT nType, int cx, int cy)
{
	CRect rect;
	GetClientRect(rect);

	m_CustomRgn.Detach();
	m_CustomRgn.CreateRoundRectRgn(rect.left + winStats.frm_clp_wdth, 
		rect.top + winStats.frm_clp_wdth
		, rect.right- winStats.frm_clp_wdth, 
		rect.bottom - winStats.frm_clp_wdth, 30, 30);

	SetWindowRgn(m_CustomRgn, TRUE);
	//Set the frame rects!
	SetWindowRects();
	CFrameWnd::OnSize(nType, cx, cy);
	
}

int CCustomFrame::ProcessResize(CPoint point)
{
	int Val = -1;
	LPCTSTR cursor;
	if (r_windRects.r_Lrect.PtInRect(point)){
		Val = 1;
		cursor = IDC_SIZEWE;
	}
	if (r_windRects.r_Rrect.PtInRect(point)){
		Val = 2;
		cursor = IDC_SIZEWE;
	}if (r_windRects.r_Trect.PtInRect(point)){
		Val = 3;
		cursor = IDC_SIZENS;
	}if (r_windRects.r_Brect.PtInRect(point)){
		Val = 6;
		cursor = IDC_SIZENS;
	}
	if (r_windRects.r_TLrect.PtInRect(point)){
		Val = 4;
		cursor = IDC_SIZENWSE;
	}
	if (r_windRects.r_TRrect.PtInRect(point)){
		Val = 5;
		cursor = IDC_SIZENESW;
	}if (r_windRects.r_BLrect.PtInRect(point)){
		Val = 7;
		cursor = IDC_SIZENESW;
	}
	if (r_windRects.r_BRrect.PtInRect(point)){
		Val = 8;
		cursor = IDC_SIZENWSE;
	}
	if (r_windRects.r_Move.PtInRect(point)){
		DefWindowProc(WM_SYSCOMMAND, SC_MOVE + 1 ,MAKELPARAM(point.x,point.y));
		return 0;
	}
	if (Val == -1)
		return 0;

	::SetCursor(AfxGetApp()->LoadStandardCursor(cursor));
	//Send the resize messages
	DefWindowProc(WM_SYSCOMMAND, SC_SIZE + Val ,MAKELPARAM(point.x ,point.y));
	return 0;
}

BOOL CCustomFrame::OnEraseBkgnd(CDC* pDC)
{
	//return CFrameWnd::OnEraseBkgnd(pDC); Returns without painting the background
	return TRUE;
	
}

int CCustomFrame::maximize(void)
{
	//The custom maximize function. This is needed since we clipped the frame and the border.
	CRect rect,rectD, rect1;
	GetClientRect(rect);	
	GetWindowRect(m_PrevRect);
	
	int scrWidth  = GetSystemMetrics(SM_CXSCREEN);
	int scrHeight = GetSystemMetrics(SM_CYSCREEN);
	
	rect.right = scrWidth + winStats.frm_clp_wdth;
	rect.bottom = scrHeight + winStats.frm_clp_wdth;
	rect.left -= winStats.frm_clp_wdth;
	rect.top -= winStats.frm_clp_wdth;
	//Get the taskbar rect and set the bottom to taskbar rect top parameter
	CWnd* pTray = FindWindow(_T("Shell_TrayWnd"), _T(""));
	pTray->GetWindowRect(&rectD);
	rect.bottom = rectD.top + winStats.frm_clp_wdth;
	MoveWindow(rect);
	b_maximized = TRUE;
	return 0;
}

void CCustomFrame::restore(void)
{
	MoveWindow(m_PrevRect);
	b_maximized = FALSE;
}

void CCustomFrame::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (r_windRects.r_Move.PtInRect(point)){
		if (!b_maximized)
			maximize();
		else
			restore();
	}

	CFrameWnd::OnLButtonDblClk(nFlags, point);
}

void CCustomFrame::close_window(void)
{
	DestroyWindow();
}

void CCustomFrame::SetWindowRects(void)
{
	//Set the custom frame rect areas. Done in each frame area changes
	CRect rect;
	GetClientRect(rect);
	r_windRects.r_Lrect.CopyRect(CRect(rect.left, rect.top + winStats.bdr_wdth, rect.left + winStats.bdr_wdth, rect.bottom -winStats.bdr_wdth));
	r_windRects.r_Rrect.CopyRect(CRect(rect.right - winStats.bdr_wdth, rect.top + winStats.bdr_wdth, rect.right, rect.bottom -winStats.bdr_wdth));
	r_windRects.r_Trect.CopyRect(CRect(rect.left + winStats.bdr_wdth, rect.top , rect.right - winStats.bdr_wdth, rect.top + winStats.bdr_wdth));
	r_windRects.r_Brect.CopyRect(CRect(rect.left + winStats.bdr_wdth, rect.bottom - winStats.bdr_wdth, rect.right - winStats.bdr_wdth, rect.bottom));
	r_windRects.r_TLrect.CopyRect(CRect(rect.left, rect.top, rect.left + winStats.bdr_wdth, rect.top + winStats.bdr_wdth));
	r_windRects.r_TRrect.CopyRect(CRect(rect.right - winStats.bdr_wdth, rect.top , rect.right, rect.top + winStats.bdr_wdth));
	r_windRects.r_BLrect.CopyRect(CRect(rect.left, rect.bottom -winStats.bdr_wdth , rect.left + winStats.bdr_wdth, rect.bottom ));
	r_windRects.r_BRrect.CopyRect(CRect(rect.right - winStats.bdr_wdth, rect.bottom - winStats.bdr_wdth, rect.right, rect.bottom));
	r_windRects.r_Move.CopyRect(CRect(rect.left + 45, rect.top + winStats.bdr_wdth, rect.right - winStats.bdr_wdth, rect.top + winStats.titlb_sz));
	
	r_windRects.r_Close.CopyRect(CRect(rect.right - winStats.ico_size - winStats.bdr_wdth, 
								rect.top + winStats.bdr_wdth, 
								rect.right - winStats.bdr_wdth, 
								rect.top + winStats.ico_size + winStats.bdr_wdth));
	r_windRects.r_Maximize.CopyRect(CRect(rect.right - 2 * winStats.ico_size - winStats.bdr_wdth, 
									rect.top + winStats.bdr_wdth, 
									rect.right - winStats.ico_size - winStats.bdr_wdth , 
									rect.top + winStats.ico_size + winStats.bdr_wdth));
	r_windRects.r_Minimize.CopyRect(CRect(rect.right - 3 * winStats.ico_size - winStats.bdr_wdth, 
									rect.top + winStats.bdr_wdth, 
									rect.right - 2 * winStats.ico_size - winStats.bdr_wdth, 
									rect.top + winStats.ico_size + winStats.bdr_wdth));
	r_windRects.r_Mrect.CopyRect(rect);
	
}

bool CCustomFrame::HandleCutomeFrame(CPoint point)
{
	CRect rect, rRect;
	GetClientRect(rect);
	//Handles close, minimize, maximize and resize events for custome frame
	if (r_windRects.r_Close.PtInRect(point)){
		close_window();
		return false;
	}
	if (r_windRects.r_Maximize.PtInRect(point)){
		if(!b_maximized)
			maximize();
		else
			restore();

	}
	if (r_windRects.r_Minimize.PtInRect(point)){
		ShowWindow(SW_SHOWMINIMIZED);
		return true;
	}
	if (rect.PtInRect(point) && !rRect.PtInRect(point) && !b_maximized)
		ProcessResize(point);
	return true;
}

void CCustomFrame::HandleCustomeFrameCursor(CPoint point)
{
	//If the mouse was pointed to the custome frame, set the appropriate cursor for resizing
	if (b_maximized)
		return;
	if (r_windRects.r_Lrect.PtInRect(point))
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
	if (r_windRects.r_Rrect.PtInRect(point))
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
	if (r_windRects.r_Trect.PtInRect(point))
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENS));
	if (r_windRects.r_Brect.PtInRect(point))
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENS));
	if (r_windRects.r_BLrect.PtInRect(point))
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENESW));
	if (r_windRects.r_BRrect.PtInRect(point))
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE));
	if (r_windRects.r_TLrect.PtInRect(point))
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE));
	if (r_windRects.r_TRrect.PtInRect(point))
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENESW));
}

void CCustomFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// Set the minimum  resized area
	lpMMI->ptMinTrackSize.x = 220;
    lpMMI->ptMinTrackSize.y = 100;
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

HBRUSH CCustomFrame::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//Handle the static title 
	HBRUSH hbr = CFrameWnd::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == WINDOW_STATIC){
	 pDC->SetTextColor(RGB(255,255,255));
	 pDC->SetBkMode(TRANSPARENT);
	 
	 return (HBRUSH)CreateSolidBrush(cr_frm);
	}
	return hbr;
}
