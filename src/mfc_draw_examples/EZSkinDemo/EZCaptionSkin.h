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
#ifndef __EZCAPTIONSKIN_H__
#define __EZCAPTIONSKIN_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// EZCaptionSkin.h : header file
//

#include "EZGenericSkin.h"
/////////////////////////////////////////////////////////////////////////////
// CEZCaptionSkin window

class CEZCaptionSkin : public CEZGenericSkin
{
// Construction
public:
	CEZCaptionSkin();
	DECLARE_SERIAL(CEZCaptionSkin)

// Attributes
public:
	const CRect& GetMinRect() const{return m_rectBtns[0];}
	const CRect& GetMaxRect() const{return m_rectBtns[1];}
	const CRect& GetCloseRect() const{return m_rectBtns[2];}

	const CEZDib& GetNormalButtonBitmap() const{return m_DibBtnNormal;}
	const CEZDib& GetHighlightButtonBitmap() const{return m_DibBtnHilight;}

	COLORREF GetTransparentColor() const{return m_clrTransparent;}
// Operations
public:
// Overrides

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEZCaptionSkin)
	protected:
	virtual void LoadDefaultTextColor();
	virtual void LoadDefaultFont();
	virtual void LoadDefaultBmp();
	virtual void LoadDefaultBackColor();
	public:
	virtual BOOL LoadDefault();
	virtual BOOL Load(IEZSkinIni* pIni,BOOL bLoadDefaultOnFailure  = TRUE);
	protected:
	virtual CString GetSection();
	public:
	virtual void Destroy();
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CEZCaptionSkin();

protected:
	virtual BOOL LoadButtons(IEZSkinIni* pIni);
	virtual void  LoadDefaultButtons();
	CEZDib		m_DibBtnNormal;
	CEZDib		m_DibBtnHilight;
	CRect		m_rectBtns[3];
	COLORREF	m_clrTransparent;	 

};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //__EZCAPTIONSKIN_H__
