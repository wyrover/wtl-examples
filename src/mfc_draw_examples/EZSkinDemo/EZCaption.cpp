//----------------------------------------------------------------------------------------//
/******************************************************************************************
V. Lakshmi Narasimhan,ezlux@yahoo.com
This Code is a Part of the EZSkin Framework.

Feel free to use ,modify,twist,turn,digest or anything u want to do.
However if u find this code useful enough to be used in your great
commercial application an e-mail would be appreciated!

This code is provided "as is" without any warranty -express or implied
blah. blah.. blah...
********************************************************************************************/
//------------------------------------------------------------------------------------------//

// EZCaption.cpp : implementation file

#include "stdafx.h"
#include "EZCaption.h"
#include "EZWindowNC.h"
#include  "EZSkin.h"
#include "EZCaptionSkin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "SuppressStyle.h"

/////////////////////////////////////////////////////////////////////////////
// CEZCaption

IMPLEMENT_DYNAMIC(CEZCaption,CSubclassWnd)

CEZCaption::CEZCaption()
:m_hIcon(0)
,m_nLastHit(C_NONE)

{
	
	m_rcBtns[0]=CRect(-1,-1,-1,-1);
	m_rcBtns[1]=CRect(-1,-1,-1,-1);
	m_rcBtns[2]=CRect(-1,-1,-1,-1);
	CEZSkin& ezs = CEZSkin::Instance();
	ezs.AddComponent(_T("CEZCaptionSkin"));
}


CEZCaption::~CEZCaption()
{
}

//////////////////
// Install caption handler. 
//
BOOL CEZCaption::Install(CWnd* pWnd)
{
	
	return HookWindow(pWnd);
}


/////////////////
// Regenerate and display caption
//
void CEZCaption::Refresh()
{
	PaintCaption();
}

//////////////////
// Message handler handles caption-related messages
//
LRESULT CEZCaption::WindowProc(UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg) 
	{
	case WM_NCMOUSEMOVE:

		{
			
			POINTS PS =MAKEPOINTS(lp) ;
			CPoint pt(PS.x,PS.y);
			return OnNCMouseMove((UINT)wp,pt);

		}
			
	case WM_NCLBUTTONUP:
		{
			POINTS PS =MAKEPOINTS(lp) ;
			CPoint pt(PS.x,PS.y);
			return OnNCLButtonUp((UINT)wp,pt);
		}	//
	case WM_NCLBUTTONDOWN:
		{
			POINTS PS =MAKEPOINTS(lp) ;
			CPoint pt(PS.x,PS.y);
			return OnNCLButtonDown((UINT)wp,pt);
		}	
	case WM_NCPAINT:
		OnNcPaint(HRGN(wp));
		return 0;
		
	case WM_SIZE:
		  CalculateButtonRects();
		  return Default();
		
	case WM_NCACTIVATE:
		return OnNcActivate(wp);
		
	case WM_SETTEXT:
		OnSetText((LPCTSTR)lp);
		return 0;
		
	case WM_SYSCOLORCHANGE:
	case WM_SETTINGCHANGE:
		OnColorChange();
		return 0;
		
	case WM_NCHITTEST:
		{
			POINTS PS =MAKEPOINTS(lp) ;
			CPoint pt(PS.x,PS.y);
			return OnNCHitTest(pt);
		}
	}
	// We don't handle it: pass along
	return CSubclassWnd::WindowProc(msg, wp, lp);
}

/////////////////
// Handle WM_NCPAINT for main window
//
void CEZCaption::OnNcPaint(HRGN hRgn)
{
	ASSERT_VALID(m_pWndHooked);
	CWnd& wnd = *m_pWndHooked;
	
	CEZWindowNC nc(m_pWndHooked); 
	CRect rc = nc.GetCaptionRect();	// caption rectangle in window coords
	CRect rcWin;					
	wnd.GetWindowRect(&rcWin);		// .. get window rect
	rc += rcWin.TopLeft();			// convert caption rect to screen coords
	
	// Don't bother painting if the caption doesn't lie within the region.
	//
	if ((WORD)hRgn > 1 && !::RectInRegion(hRgn, &rc)) 
	{
		Default();					// just do default thing
		return;						// and quit
	}
	
	// Exclude caption from update region
	//
	HRGN hRgnCaption = ::CreateRectRgnIndirect(&rc);
	HRGN hRgnNew     = ::CreateRectRgnIndirect(&rc);
	
	if ((WORD)hRgn > 1) 
	{
		// wParam is a valid region: subtract caption from it
		//
		::CombineRgn(hRgnNew, hRgn, hRgnCaption, RGN_DIFF);
	} 
	else 
	{
		// wParam is not a valid region: create one that's the whole
		// window minus the caption bar
		//
		HRGN hRgnAll = ::CreateRectRgnIndirect(&rcWin);
		CombineRgn(hRgnNew, hRgnAll, hRgnCaption, RGN_DIFF);
		DeleteObject(hRgnAll);
	}
	
	// Call Windows to do WM_NCPAINT with altered update region
	//
	MSG& msg = AfxGetThreadState()->m_lastSentMsg;
	WPARAM savewp = msg.wParam;		// save original wParam
	msg.wParam = (WPARAM)hRgnNew;	// set new region for DefWindowProc
	
	Default();						// Normal message handling
	
	DeleteObject(hRgnCaption);		// clean up
	DeleteObject(hRgnNew);			// ...
	msg.wParam = savewp;			// restore original wParam
	
	PaintCaption();					// Now paint our special caption
}

//////////////////
// Handle WM_NCACTIVATE for main window
//
BOOL CEZCaption::OnNcActivate(BOOL bActive)
{
	ASSERT_VALID(m_pWndHooked);
	CWnd* pWnd = m_pWndHooked;
	
	
	
	if(pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)))
	{
		
		
		CFrameWnd& frame = (CFrameWnd&)*DYNAMIC_DOWNCAST(CFrameWnd,pWnd);
		// Mimic MFC kludge to stay active if WF_STAYACTIVE bit is on
		//
		if (frame.m_nFlags & WF_STAYACTIVE)
			bActive = TRUE;
		
		if (!frame.IsWindowEnabled())			// but not if disabled
			bActive = FALSE;
		
		if (bActive == m_bActive)
			return TRUE;						// nothing to do
		
		// In case this is a MDI app, manually activate/paint active MDI child
		// window, because Windows won't do it if parent frame is invisible.
		// Must do this BEFORE calling Default, or it will not work.
		//
		CFrameWnd* pActiveFrame = frame.GetActiveFrame();
		
		if (pActiveFrame != &frame) 
		{		
			pActiveFrame->SendMessage(WM_NCACTIVATE, bActive);
			pActiveFrame->SendMessage(WM_NCPAINT);
		}
		
		// Turn WS_VISIBLE off before calling DefWindowProc,
		// so DefWindowProc won't paint and thereby cause flicker.
		//
		{
			SuppressStyle ss(frame.GetSafeHwnd(), WS_VISIBLE);
			
			MSG& msg = AfxGetThreadState()->m_lastSentMsg;
			msg.wParam = bActive;
			
			Default();						// Normal message handling
		}
		// At this point, nothing has happened (since WS_VISIBLE was off).
		// Now it's time to paint.
		//
		m_bActive = bActive;				// update state
		frame.SendMessage(WM_NCPAINT);		// paint non-client area (frame too)
	}
	else
	{
		
		// Turn WS_VISIBLE off before calling DefWindowProc,
		// so DefWindowProc won't paint and thereby cause flicker.
		//
		{
			SuppressStyle ss(pWnd->GetSafeHwnd(), WS_VISIBLE);
			
			MSG& msg = AfxGetThreadState()->m_lastSentMsg;
			msg.wParam = bActive;
			
			Default();						// Normal message handling
		}
		
		pWnd->SendMessage(WM_NCPAINT);
		
	}
	return TRUE;						// done OK
}

//////////////////
// Handle WM_SETTEXT for main window
//
void CEZCaption::OnSetText(LPCTSTR)
{
	ASSERT_VALID(m_pWndHooked);
	CWnd& wnd = *m_pWndHooked;
	
	// Turn WS_VISIBLE style off before calling Windows to
	// set the text. Reset to visible afterwards
	{
		SuppressStyle ss(wnd.GetSafeHwnd(), WS_VISIBLE);
		
		Default();						// Normal message handling
	}
	//	wnd.SendMessage(WM_NCPAINT);		// paint non-client (frame)
	Refresh();
}

//////////
// Ensure caption is repainted when system colors change
//
void CEZCaption::OnColorChange()
{	 
	Default();							 // Normal message handling
	Refresh();
}

//////////////////
// Paint custom caption. m_bActive flag tells whether frame is active or not. 
// Just blast the bitmap to the title bar.
//
void CEZCaption::PaintCaption()
{
	ASSERT(m_pWndHooked);
	CWnd& wnd = *m_pWndHooked;
	
	// Get caption DC and rectangle
	//
	CWindowDC dcWin(&wnd);				// window DC
	CEZWindowNC nc(m_pWndHooked);
	
	CRect rc = nc.GetCaptionRect();			// get caption rectangle
	
	
	CEZMemDC memDC(&dcWin,&rc);
	PaintBitmap(&memDC);
	
	
	
}

/////////
// Paint the caption bitmap. Override for custom caption painters.
// Note: SDK DrawCaption() method not used, so as to provide useful 
// virtual functions for derived caption painters
//
void CEZCaption::PaintBitmap(CDC* pDC)
{
	PaintBackground(pDC);
	
	PaintIcon(pDC);
	
	PaintButtons(pDC);
	
	PaintText(pDC);
}

///////////

//
void CEZCaption::PaintBackground(CDC* pDC)
{
	
	CEZSkin& ezs = CEZSkin::Instance();
	CEZCaptionSkin* pSkin  = DYNAMIC_DOWNCAST(CEZCaptionSkin,ezs.GetComponent(_T("CEZCaptionSkin")));
	ASSERT(pSkin);
	
	ASSERT(m_pWndHooked);
	CEZWindowNC nc(m_pWndHooked);
	const CEZDib& dib = pSkin->GetBackgroundBitmap();
	
	dib.Draw(pDC,nc.GetCaptionRect());
	
}

///////
// Calculate the caption text clipping rect
//
CRect CEZCaption::GetTextRect()
{
	ASSERT(m_pWndHooked);
	CEZWindowNC nc(m_pWndHooked);
	CRect textRect = nc.GetCaptionRect();
	textRect.left += GetIconWidth();
	textRect.right -= GetButtonsWidth() + 4;
	textRect.top -= 2;
	return textRect;
}

///////////
// Draw the caption text onto the bitmap
//
void CEZCaption::PaintText(CDC* pDC)
{
	
	
	pDC->SetBkMode(TRANSPARENT);			// draw on top of our background
	
	CEZSkin& ezs = CEZSkin::Instance();
	CEZCaptionSkin* pSkin  = DYNAMIC_DOWNCAST(CEZCaptionSkin,ezs.GetComponent(_T("CEZCaptionSkin")));
	ASSERT(pSkin);
	
	
	
	CString text;
	ASSERT(m_pWndHooked);
	CWnd& wnd = *m_pWndHooked;
	
	wnd.GetWindowText(text);
	
	// Set text color
	COLORREF textColor = pSkin->GetTextColor();
	
	pDC->SetTextColor(textColor);
	
	// Get caption font	and select into DC
	CEZSelector a(pDC, (CFont*)&pSkin->GetFont());
	
	CRect textRect = GetTextRect();
	
	pDC->DrawText(text, textRect, DT_LEFT|DT_VCENTER|DT_END_ELLIPSIS);
}

////////////////
// Draw caption icon if valid DC is provided. Returns effective width of icon.
//
int CEZCaption::PaintIcon(CDC* pDC)
{
	
	if(!m_hIcon)
		return 0;
	ASSERT(m_pWndHooked);
	CWnd& wnd = *m_pWndHooked;
	
	////////////
	// If there's no icon or system menu, don't draw one
	//
	if (!(wnd.GetStyle() & WS_SYSMENU))
		return 0;
	
	//////////////
	// Within the basic button rectangle, Windows 95 uses a 1 or 2 pixel border
	// Icon has 2 pixel border on left, 1 pixel on top/bottom, 0 right
	//
	int cxIcon = GetSystemMetrics(SM_CXSIZE);
	CEZWindowNC nc(m_pWndHooked);
	CRect rcCap = nc.GetCaptionRect();
	CRect rc(rcCap.left+2, rcCap.top+2, cxIcon+2, GetSystemMetrics(SM_CYSIZE)+2);
	if (pDC != 0)
	{
		DrawIconEx(pDC->m_hDC, rc.left, rc.top, 
			m_hIcon,
			rc.Width(), rc.Height(), 0, NULL, DI_NORMAL);
	}
	return cxIcon;
}

//////////////
// Helper
//
int CEZCaption::GetIconWidth()
{
	return PaintIcon();
}

////////////////
// Draw min, max/restore, close buttons.
// Returns total width of buttons drawn.
//
int CEZCaption::PaintButtons(CDC* pDC)
{
	ASSERT(m_pWndHooked);
	CWnd& wnd = *m_pWndHooked;
	
	CEZWindowNC nc(&wnd);
	if(!nc.HasCaption())
		return 0;
	
	
	CEZSkin& ezs = CEZSkin::Instance();
	CEZCaptionSkin* pSkin  = DYNAMIC_DOWNCAST(CEZCaptionSkin,ezs.GetComponent(_T("CEZCaptionSkin")));
	ASSERT(pSkin);
	
	const CEZDib& dibH = pSkin->GetHighlightButtonBitmap();
	const CEZDib& dibN = pSkin->GetNormalButtonBitmap();
	
	COLORREF clrTrans = pSkin->GetTransparentColor();
	
	int cxIcon = GetSystemMetrics(SM_CXSIZE);
	int cyIcon = GetSystemMetrics(SM_CYSIZE);
	
	
	CRect rcCap  = nc.GetCaptionRect();
	
	CRect rcClose,rcMin,rcMax;
	
	CRect rcCloseSrc =  pSkin->GetCloseRect();
	CRect rcMinSrc =pSkin->GetMinRect();
	CRect rcMaxSrc = pSkin->GetMaxRect();
	
	rcClose = CRect(rcCap.right-rcCloseSrc.Width(),rcCap.top,rcCap.right,rcCap.bottom);
	rcMax    =  CRect(rcClose.left-rcMaxSrc.Width(),rcClose.top,rcClose.left,rcClose.bottom);
	rcMin   =  CRect(rcMax.left-rcMinSrc.Width(),rcMax.top,rcMax.left,rcMax.bottom);
	
	
	
	if(pDC && pDC->m_hDC)
	{
		CRect rcBtns(rcMin.left,rcCap.top,rcClose.right,rcCap.bottom);
		CRect rcBtnsSrc(rcMinSrc.left,rcCap.top,rcCloseSrc.right,rcCap.bottom);
		
		if(m_nLastHit == C_CLOSE)
			dibH.DrawTransparent(pDC,clrTrans,rcClose,rcCloseSrc);
		else
			dibN.DrawTransparent(pDC,clrTrans,rcClose,rcCloseSrc);
		
		if(m_nLastHit == C_MIN)
			dibH.DrawTransparent(pDC,clrTrans,rcMin,rcMinSrc);
		else
			dibN.DrawTransparent(pDC,clrTrans,rcMin,rcMinSrc);
		
		
		if(m_nLastHit == C_MAX)
			dibH.DrawTransparent(pDC,clrTrans,rcMax,rcMaxSrc);
		else
			dibN.DrawTransparent(pDC,clrTrans,rcMax,rcMaxSrc);
		
		
	}
	return rcClose.Width()+rcMin.Width()+rcMax.Width();
}

int CEZCaption::GetButtonsWidth()
{
	return PaintButtons();
}

HICON CEZCaption::SetIcon(HICON hIcon)
{
	
	ASSERT(hIcon);
	HICON hTemp = m_hIcon;
	m_hIcon = hIcon;
	
	return hTemp;
	
}

CRect CEZCaption::GetCloseRect() 
{
	if(m_rcBtns[2] == CRect(-1,-1,-1,-1))
		CalculateButtonRects();
	return m_rcBtns[2];
}

CRect CEZCaption::GetMinRect() 
{
	
	if(m_rcBtns[1] == CRect(-1,-1,-1,-1))
		CalculateButtonRects();
	return m_rcBtns[0];
	
}

CRect CEZCaption::GetMaxRect() 
{
	
	if(m_rcBtns[0] == CRect(-1,-1,-1,-1))
		CalculateButtonRects();
	return m_rcBtns[1];
	
}

void CEZCaption::CalculateButtonRects() 
{
	
	CEZSkin& ezs = CEZSkin::Instance();
	CEZCaptionSkin* pSkin  = DYNAMIC_DOWNCAST(CEZCaptionSkin,ezs.GetComponent(_T("CEZCaptionSkin")));
	ASSERT(pSkin);
	
	CEZWindowNC nc(m_pWndHooked);
	CRect rcCap  = nc.GetCaptionRect();
	
	CRect rcCloseSrc =  pSkin->GetCloseRect();
	CRect rcMinSrc =pSkin->GetMinRect();
	CRect rcMaxSrc = pSkin->GetMaxRect();
	
	m_rcBtns[2]= CRect(rcCap.right-rcCloseSrc.Width(),rcCap.top,rcCap.right,rcCap.bottom);
	m_rcBtns[1]   =  CRect(m_rcBtns[2].left-rcMinSrc.Width(),m_rcBtns[2].top,m_rcBtns[2].left,m_rcBtns[2].bottom);
	m_rcBtns[0]=  CRect(m_rcBtns[1].left-rcMaxSrc.Width(),m_rcBtns[1].top,m_rcBtns[1].left,m_rcBtns[1].bottom);
}


LRESULT CEZCaption::OnNCHitTest(CPoint point)
{
	
	CPoint ptClient(point);
	
	
	CEZWindowRect rcWnd(m_pWndHooked);
	CEZWindowNC nc(m_pWndHooked);
	
	CRect rcCaption(nc.GetCaptionRect());
	rcCaption+=rcWnd.TopLeft();
	
	if(!rcCaption.PtInRect(point))
		return Default();
	
	
	CRect rcClose(GetCloseRect());
	rcClose+=rcWnd.TopLeft();
	if(rcClose.PtInRect(point))
		return HTCLOSE;
	
	CRect rcMin(GetMinRect());
	rcMin+=rcWnd.TopLeft();
	if(rcMin.PtInRect(point))
		return HTMINBUTTON;
	
	CRect rcMax(GetMaxRect());
	rcMax+=rcWnd.TopLeft();
	if(rcMax.PtInRect(point))
		return HTMAXBUTTON;
	
	CRect rcIcon(0,0,GetSystemMetrics(SM_CXICON),GetSystemMetrics(SM_CYICON));
	rcIcon+=rcWnd.TopLeft();
	if(rcIcon.PtInRect(point))
		return HTSYSMENU;
	
	return HTCAPTION;
	
	
}




LRESULT CEZCaption::OnNCLButtonDown(UINT nHitTest, CPoint ptHit)
{
	
	switch(nHitTest)
	{
	case HTCAPTION:
	case HTNOWHERE:
		return Default();
		
	case HTMAXBUTTON:
		{
	
			m_nLastHit = C_MAX;
			CWindowDC dcWin(m_pWndHooked);
			PaintButtons(&dcWin);
			return 0;
		}
	case HTMINBUTTON:
		{
	
			m_nLastHit = C_MIN;
			CWindowDC dcWin(m_pWndHooked);
			PaintButtons(&dcWin);
			return 0;
		}
	case HTCLOSE:
		{
	
			m_nLastHit = C_CLOSE;
			CWindowDC dcWin(m_pWndHooked);
			PaintButtons(&dcWin);
			return 0;
		}
		
		
	}
	return Default();
}

LRESULT CEZCaption::OnNCLButtonUp(UINT nHitTest, CPoint ptHit)
{
	
	
	ReleaseCapture();
	m_nLastHit = C_NONE;
	ASSERT(m_pWndHooked);
	switch(nHitTest)
	{
		
	case HTMAXBUTTON:
		{
			
			if(!m_pWndHooked->IsZoomed())
				m_pWndHooked->ShowWindow(SW_SHOWMAXIMIZED);
			else
				m_pWndHooked->ShowWindow(SW_SHOWNORMAL);

			return 0;
		}
	case HTMINBUTTON:
		{

			m_pWndHooked->ShowWindow(SW_SHOWMINIMIZED);
			return 0;
		}
	case HTCLOSE:
		{
			m_pWndHooked->SendMessage(WM_CLOSE);
			return 0;
		}
		
		
	}
	CWindowDC dc(m_pWndHooked);
	PaintButtons(&dc);
	return Default();
	
}

LRESULT CEZCaption::OnNCMouseMove(UINT nHitTest, CPoint ptHit)
{

	if(m_nLastHit == C_NONE )
		return Default();

	if(m_nLastHit == nHitTest)
		return 0;

	m_nLastHit = C_NONE;
	CWindowDC dc(m_pWndHooked);
	PaintButtons(&dc);
	return 0;

}
