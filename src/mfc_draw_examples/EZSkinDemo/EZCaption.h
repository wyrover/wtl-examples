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
#ifndef __EZCAPTION_H__
#define __EZCAPTION_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// EZCaption.h : header file
//

#include "Subclass.h"
/////////////////////////////////////////////////////////////////////////////
// CEZCaption window

class CEZCaption : public CSubclassWnd
{
// Construction

public:
	CEZCaption();
	DECLARE_DYNAMIC(CEZCaption)


	BOOL Install			(CWnd* pFrameWnd);
	void Uninstall			();
	
	virtual void Refresh();
 
protected:

	BOOL	m_bActive;			// active/inactive state

	enum tHITTEST {C_NONE = HTNOWHERE,C_ICON =HTSYSMENU,C_MIN = HTMINBUTTON,C_MAX = HTMAXBUTTON,C_CLOSE = HTCLOSE};
	// Helpers
	//

	int		GetIconWidth	();
	int		GetButtonsWidth	();

	// Override these in derived classes if necessary
	//
	virtual void	PaintCaption();
	virtual void	PaintBitmap		(CDC* pDC);
	virtual void	PaintBackground	(CDC* pDC);
	virtual int		PaintIcon		(CDC* pDC = 0);
	virtual int		PaintButtons	(CDC* pDC = 0);
	virtual void	PaintText		(CDC* pDC);
	virtual CRect	GetTextRect		();

	// Paul DiLascia says:
	// "These are similar to, but NOT the same as the equivalent CWnd fns. Don't
	// override unless you're a guru, and even THEN I wouldn't recommend it."
	
	
	virtual void	OnNcPaint		(HRGN hUpdateRgn);
	virtual BOOL	OnNcActivate	(BOOL bActive);
	virtual void	OnSetText		(LPCTSTR lpText);
	virtual void	OnColorChange	();


protected:
	virtual LRESULT OnNCMouseMove(UINT nHitTest,CPoint ptHit);
	virtual LRESULT OnNCLButtonUp(UINT nHitTest,CPoint ptHit);
	virtual LRESULT OnNCLButtonDown(UINT nHitTest,CPoint ptHit);
	void CalculateButtonRects();

	
	CRect GetMinRect();
	CRect GetMaxRect();
	CRect GetCloseRect() ;
	virtual LRESULT  OnNCHitTest(CPoint point);
	HICON m_hIcon;
	UINT m_nLastHit; //None,Min,Max,Close
	CRect m_rcBtns[3];

	virtual LRESULT WindowProc(UINT msg, WPARAM wp, LPARAM lp);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEZCaption)
	//}}AFX_VIRTUAL
// Implementation
public:
	
	HICON SetIcon(HICON hIcon);
	HICON GetIcon(){return m_hIcon;}
	virtual ~CEZCaption();

private:
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //__EZCAPTION_H__
