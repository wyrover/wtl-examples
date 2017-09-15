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

#include "stdafx.h"
#include "EZWindowNC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BOOL CEZWindowNC::HasSysMenu()
{

	UINT nStyle = ::GetWindowLong(m_pWnd->GetSafeHwnd(),GWL_STYLE);
	return (nStyle&WS_SYSMENU) ;
}

BOOL CEZWindowNC::HasBorder()
{
	
	UINT nStyle = ::GetWindowLong(m_pWnd->GetSafeHwnd(),GWL_STYLE);
	return (nStyle&WS_BORDER  || nStyle||WS_THICKFRAME) ;
}

BOOL CEZWindowNC::HasCaption()
{

	UINT nStyle = ::GetWindowLong(m_pWnd->GetSafeHwnd(),GWL_STYLE);
	return (nStyle&WS_CAPTION) ;
	
}

CRect CEZWindowNC::GetCaptionRect()
{

	if(!HasCaption())
		return CRect(0,0,0,0);

	CRect rcBorderL = GetLeftBorderRect();
	CRect rcBorderR = GetRightBorderRect();
	CRect rcBorderT= GetTopBorderRect();


	CRect rcCap;
	
	rcCap.top	=	rcBorderT.bottom;
	rcCap.bottom = rcCap.top+GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CXBORDER);
	rcCap.left = rcBorderL.right;
	rcCap.right =rcBorderR.left;
	return rcCap;
}

CRect CEZWindowNC::GetLeftBorderRect()
{
	
	if(!HasBorder())
		return CRect(0,0,0,0);

	CEZWindowRect rcWnd(m_pWnd);

	UINT nStyle = ::GetWindowLong(m_pWnd->GetSafeHwnd(),GWL_STYLE);

	int nCx = nStyle&WS_THICKFRAME|WS_OVERLAPPEDWINDOW?GetSystemMetrics(SM_CXSIZEFRAME):GetSystemMetrics(SM_CXBORDER);
	int nCy = nStyle&WS_THICKFRAME|WS_OVERLAPPEDWINDOW?GetSystemMetrics(SM_CYSIZEFRAME):GetSystemMetrics(SM_CYBORDER);

	rcWnd-=rcWnd.TopLeft();
	CRect rcBorderL(rcWnd);
	rcBorderL.right=rcBorderL.left+nCx;
	return rcBorderL;

}

CRect CEZWindowNC::GetRightBorderRect()
{
	if(!HasBorder())
		return CRect(0,0,0,0);
	CEZWindowRect rcWnd(m_pWnd);
	

	UINT nStyle = ::GetWindowLong(m_pWnd->GetSafeHwnd(),GWL_STYLE);
	int nCx = nStyle&WS_THICKFRAME|WS_OVERLAPPEDWINDOW?GetSystemMetrics(SM_CXSIZEFRAME):GetSystemMetrics(SM_CXBORDER);
	int nCy = nStyle&WS_THICKFRAME|WS_OVERLAPPEDWINDOW?GetSystemMetrics(SM_CYSIZEFRAME):GetSystemMetrics(SM_CYBORDER);

	rcWnd-=rcWnd.TopLeft();
	CRect rcBorderR(rcWnd);
	rcBorderR.left=rcBorderR.right-nCx;
	return rcBorderR;

}

CRect CEZWindowNC::GetTopBorderRect()
{
	if(!HasBorder())
		return CRect(0,0,0,0);
	
	CEZWindowRect rcWnd(m_pWnd);
	

	UINT nStyle = ::GetWindowLong(m_pWnd->GetSafeHwnd(),GWL_STYLE);
	int nCx = nStyle&WS_THICKFRAME|WS_OVERLAPPEDWINDOW?GetSystemMetrics(SM_CXSIZEFRAME):GetSystemMetrics(SM_CXBORDER);
	int nCy = nStyle&WS_THICKFRAME|WS_OVERLAPPEDWINDOW?GetSystemMetrics(SM_CYSIZEFRAME):GetSystemMetrics(SM_CYBORDER);

	rcWnd-=rcWnd.TopLeft();
	CRect rcBorderT(rcWnd);
	
	rcBorderT.bottom= rcBorderT.top+nCy;
	
	return rcBorderT;


}

CRect CEZWindowNC::GetBottomBorderRect()
{
	if(!HasBorder())
		return CRect(0,0,0,0);
	
	CEZWindowRect rcWnd(m_pWnd);
	
	UINT nStyle = ::GetWindowLong(m_pWnd->GetSafeHwnd(),GWL_STYLE);
	int nCx = nStyle&WS_THICKFRAME|WS_OVERLAPPEDWINDOW?GetSystemMetrics(SM_CXSIZEFRAME):GetSystemMetrics(SM_CXBORDER);
	int nCy = nStyle&WS_THICKFRAME|WS_OVERLAPPEDWINDOW?GetSystemMetrics(SM_CYSIZEFRAME):GetSystemMetrics(SM_CYBORDER);

	rcWnd-=rcWnd.TopLeft();
	CRect rcBorderB(rcWnd);
	
	rcBorderB.top = rcBorderB.bottom-nCy;
	
	return rcBorderB;

}

BOOL CEZWindowNC::HasMaximize()
{

	UINT nStyle = ::GetWindowLong(m_pWnd->GetSafeHwnd(),GWL_STYLE);
	return (nStyle&WS_MAXIMIZEBOX) ;

}

BOOL CEZWindowNC::HasMinimize()
{

	UINT nStyle = ::GetWindowLong(m_pWnd->GetSafeHwnd(),GWL_STYLE);
	return (nStyle&WS_MINIMIZEBOX) ;

}

HRGN CEZWindowNC::GetBorderRGN()
{

	if(!HasBorder())
		return NULL;
	CRect rcL = GetLeftBorderRect();
	CRect rcR = GetRightBorderRect();
	CRect rcT= GetTopBorderRect();
	CRect rcB = GetBottomBorderRect();
	CRgn rgnL,rgnR,rgnT,rgnB;
	rgnL.CreateRectRgnIndirect(rcL);
	rgnR.CreateRectRgnIndirect(rcR);
	rgnT.CreateRectRgnIndirect(rcT);
	rgnB.CreateRectRgnIndirect(rcB);
	rgnL.CombineRgn(&rgnL,&rgnR,RGN_OR);
	rgnT.CombineRgn(&rgnT,&rgnB,RGN_OR);

	rgnL.CombineRgn(&rgnL,&rgnT,RGN_OR);
	return (HRGN)rgnL.Detach();
}
