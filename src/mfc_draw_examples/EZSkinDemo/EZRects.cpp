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

// EZRects.cpp: implementation of the CEZClientRect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EZRects.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



CEZClientRect::CEZClientRect(CWnd* pWnd)
{
	ASSERT(pWnd);
	ASSERT(::IsWindow(pWnd->GetSafeHwnd()));
	GetClientRect(pWnd->GetSafeHwnd());
}

CEZClientRect::CEZClientRect(HWND hWnd)
{
	ASSERT(hWnd);
	ASSERT(::IsWindow(hWnd));
	GetClientRect(hWnd);
}



void CEZClientRect::GetClientRect(HWND hWnd)
{

	::GetClientRect(hWnd,this);
}



CEZWindowRect::CEZWindowRect(CWnd* pWnd)
{
	ASSERT(pWnd);
	ASSERT(::IsWindow(pWnd->GetSafeHwnd()));
	GetWindowRect(pWnd->GetSafeHwnd());
}


CEZWindowRect::CEZWindowRect(HWND hWnd)
{
	ASSERT(hWnd);
	ASSERT(::IsWindow(hWnd));
	GetWindowRect(hWnd);

}



void CEZWindowRect::GetWindowRect(HWND hWnd)
{

	::GetWindowRect(hWnd,this);
}



CEZClipRect::CEZClipRect(CDC* pDC)
{

	ASSERT(pDC);
	ASSERT(pDC->GetSafeHdc());
	GetClipBox(pDC->GetSafeHdc());

}

CEZClipRect::CEZClipRect(HDC hDC)
{

	ASSERT(hDC);
	GetClipBox(hDC);
}

void CEZClipRect::GetClipBox(HDC hDC)
{

	::GetClipBox(hDC,this);

}
