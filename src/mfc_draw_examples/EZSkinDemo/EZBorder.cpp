// EZBorder.cpp : implementation file
#include "stdafx.h"
#include "EZBorder.h"
#include "EZWindowNC.h"
#include  "EZSkin.h"
#include "EZCaptionSkin.h"
#include "SuppressStyle.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEZBorder

IMPLEMENT_DYNAMIC(CEZBorder,CSubclassWnd)

CEZBorder::CEZBorder()
{

}


CEZBorder::~CEZBorder()
{
}



LRESULT CEZBorder::WindowProc(UINT msg, WPARAM wp, LPARAM lp)
{
	
	switch (msg) 
	{
		
	case WM_NCACTIVATE:
		Default();
		Refresh();
		return 0;
		
		
	case WM_SYSCOLORCHANGE:
	case WM_SETTINGCHANGE:
		OnColorChange();
		return 0;
		
	case WM_NCPAINT:
		OnNCPaint(HRGN(wp));
		return 0;
		
		
	}
	// We don't handle it: pass along
	return CSubclassWnd::WindowProc(msg, wp, lp);
	
	
}

void CEZBorder::OnNCPaint(HRGN hRgn)
{
	
	ASSERT_VALID(m_pWndHooked);
	CWnd& wnd = *m_pWndHooked;
	
	CEZWindowNC nc(m_pWndHooked); 
	
	CRect rcWin;					
	wnd.GetWindowRect(&rcWin);		// .. get window rect
	
	HRGN hRgnBorder = nc.GetBorderRGN();
	HRGN hRgnNew     = ::CreateRectRgnIndirect(&rcWin);
	
	if ((WORD)hRgn > 1) 
	{
		// wParam is a valid region: subtract caption from it
		//
		::CombineRgn(hRgnNew, hRgn, hRgnBorder, RGN_DIFF);
	} 
	else 
	{
		// wParam is not a valid region: create one that's the whole
		// window minus the caption bar
		//
		HRGN hRgnAll = ::CreateRectRgnIndirect(&rcWin);
		CombineRgn(hRgnNew, hRgnAll, hRgnBorder, RGN_DIFF);
		DeleteObject(hRgnAll);
	}
	
	// Call Windows to do WM_NCPAINT with altered update region
	//
	MSG& msg = AfxGetThreadState()->m_lastSentMsg;
	WPARAM savewp = msg.wParam;		// save original wParam
	msg.wParam = (WPARAM)hRgnNew;	// set new region for DefWindowProc
	
	Default();						// Normal message handling
	
	DeleteObject(hRgnBorder);		// clean up
	DeleteObject(hRgnNew);			// ...
	msg.wParam = savewp;			// restore original wParam
	
	PaintBorder();					// Now paint our special caption
		
}


void CEZBorder::OnColorChange()
{
	
	Refresh();
}


BOOL CEZBorder::Install(CWnd *pWnd)
{

	ASSERT(pWnd);
	ASSERT(::IsWindow(pWnd->m_hWnd));
	return HookWindow(pWnd);
}

void CEZBorder::Refresh()
{
	OnNCPaint(NULL);

}

void CEZBorder::PaintBorder()
{

	ASSERT(m_pWndHooked);
	CEZWindowNC wndNC(m_pWndHooked);

	CEZSkin& ezs = CEZSkin::Instance();
	CEZCaptionSkin* pSkin  = DYNAMIC_DOWNCAST(CEZCaptionSkin,ezs.GetComponent(_T("CEZCaptionSkin")));
	ASSERT(pSkin);


	CWindowDC dc(m_pWndHooked);

	CRgn rgnBorder;
	rgnBorder.Attach(wndNC.GetBorderRGN());
	CBrush brush;
	brush.CreateSolidBrush(pSkin->GetBackColor());
	dc.FillRgn(&rgnBorder,&brush);
	
	
}
