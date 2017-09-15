#ifndef __EZBORDER_H__
#define __EZBORDER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// EZBorder.h : header file
//

#include "Subclass.h"
/////////////////////////////////////////////////////////////////////////////
// CEZBorder window

class CEZBorder : public CSubclassWnd
{
// Construction
public:
	CEZBorder();
	DECLARE_DYNAMIC(CEZBorder)

// Attributes
public:

// Operations
public:
// Overrides

protected:
	virtual void  PaintBorder();
	virtual void OnColorChange();
	virtual void OnNCPaint(HRGN hRgn);
	virtual LRESULT WindowProc(UINT msg, WPARAM wp, LPARAM lp);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEZBorder)
	//}}AFX_VIRTUAL
// Implementation
public:
	void Refresh();
	BOOL Install(CWnd* pWnd);
	virtual ~CEZBorder();

private:
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //__EZBORDER_H__
