// EZWndStyle.h: interface for the CEZWndStyle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EZWNDSTYLE_H__A1638D5D_E0C9_4B01_9C95_9FD258393A20__INCLUDED_)
#define AFX_EZWNDSTYLE_H__A1638D5D_E0C9_4B01_9C95_9FD258393A20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEZWndStyle  
{
public:
	UINT GetStyle();
	BOOL HasStyle(UINT nStyle);
	CEZWndStyle(CWnd* pWnd);

	virtual ~CEZWndStyle();
private:
	CWnd* m_pWnd;

};

#endif // !defined(AFX_EZWNDSTYLE_H__A1638D5D_E0C9_4B01_9C95_9FD258393A20__INCLUDED_)
