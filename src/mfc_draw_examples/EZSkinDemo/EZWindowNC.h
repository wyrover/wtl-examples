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

// EZWindowNC.h: interface and implementation of the CEZWindowNC class.
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef __EZWINDOWDC_H__
#define __EZWINDOWDC_H__

class CEZWindowNC  
{
	
public:
	HRGN GetBorderRGN();
	BOOL HasMinimize();
	BOOL HasMaximize();
	
	CEZWindowNC(CWnd* pWnd)
	{
		ASSERT(pWnd);
		m_pWnd = pWnd;
	}
	
	BOOL HasBorder();
	BOOL HasSysMenu();
	BOOL HasCaption();
	CRect GetCaptionRect();
	CRect GetLeftBorderRect();
	CRect GetRightBorderRect();
	CRect GetTopBorderRect();
	CRect GetBottomBorderRect();
	
	
	
private:
	CWnd* m_pWnd;	
	
};





#endif //#ifndef __EZWINDOWDC_H__