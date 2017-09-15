// EZWndStyle.cpp: implementation of the CEZWndStyle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EZWndStyle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEZWndStyle::CEZWndStyle(CWnd* pWnd)
:m_pWnd(pWnd)
{

	ASSERT(pWnd);
	ASSERT(::IsWindow(pWnd->m_hWnd));
}

CEZWndStyle::~CEZWndStyle()
{

}

BOOL CEZWndStyle::HasStyle(UINT nStyle)
{

	return GetStyle()&nStyle;

}

UINT CEZWndStyle::GetStyle()
{


	return ::GetWindowLong(m_pWnd->GetSafeHwnd(),GWL_STYLE);
}
