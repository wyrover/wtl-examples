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

// EZRects.h: interface for the CEZClientRect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EZRECTS_H__CB2FF073_710C_482A_BD4C_56E6310617FB__INCLUDED_)
#define AFX_EZRECTS_H__CB2FF073_710C_482A_BD4C_56E6310617FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEZClientRect : public CRect  
{
public:
	CEZClientRect(CWnd* pWnd);
	CEZClientRect(HWND hWnd);
	virtual ~CEZClientRect(){}

protected:
	void GetClientRect(HWND hWnd);
};



class CEZWindowRect : public CRect  
{
public:
	CEZWindowRect(CWnd* pWnd);
	CEZWindowRect(HWND hWnd);
	virtual ~CEZWindowRect(){}

protected:
	void GetWindowRect(HWND hWnd);
};


class CEZClipRect : public CRect  
{
public:
	CEZClipRect(CDC* pDC);
	CEZClipRect(HDC hDC);
	virtual ~CEZClipRect(){}

protected:
	void GetClipBox(HDC hDC);
};

#endif // !defined(AFX_EZRECTS_H__CB2FF073_710C_482A_BD4C_56E6310617FB__INCLUDED_)
