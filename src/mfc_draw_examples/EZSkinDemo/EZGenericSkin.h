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

#ifndef __EZGENERICSKIN_H__
#define __EZGENERICSKIN_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// EZGenericSkin.h : header file
//

#include "EZSkin_I.h"
#include "EZDib.h"
/////////////////////////////////////////////////////////////////////////////
// CEZGenericSkin window
/*
<CLASS Name = CEZGenericSkin>
This class provides a default implementation of @IEZSkinComponent interface 

In general a window needs a Background bitmap/color,Text color&font to have
a customlook.

This default implementation is given by this.

Though  I call it as an implementation it is still a proxy abstract class
since loading the default attributes is left for the derived ones.

</CLASS>
*/
class CEZGenericSkin : public IEZSkinComponent
{

DECLARE_SERIAL(CEZGenericSkin)
// Construction
public:

	CEZGenericSkin();

// Attributes
public:

	const CEZDib&	GetBackgroundBitmap() const{return m_Dib;}
	const COLORREF	GetBackColor() const{return m_clrBk;}
	const COLORREF	GetTextColor() const{return m_clrTxt;}
	const CFont&	GetFont(){return m_font;}
// Operations

public:
// Overrides

public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEZGenericSkin)
	public:
	virtual BOOL LoadDefault();
	virtual BOOL Load(IEZSkinIni* pIni,BOOL bLoadDefaultOnFailure  = TRUE);
	virtual BOOL IsDefault(){return m_bDefault;}
	virtual void Destroy();
	virtual BOOL IsLoaded(){return m_bLoaded;}
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CEZGenericSkin(){Destroy();}

//Helpers
protected:
	//Creates a font by Face Name , size & style
	virtual BOOL LoadFont(CString strFont, CString strStyle, int nHeight);
	
	//{Pseudo Pure virtual functions
	virtual CString GetSection()
	{ASSERT(FALSE);return _T("");}
	virtual void LoadDefaultBmp(){ASSERT(FALSE);}
	virtual void LoadDefaultFont(){ASSERT(FALSE);}
	virtual void LoadDefaultBackColor(){ASSERT(FALSE);}
	virtual void LoadDefaultTextColor(){ASSERT(FALSE);}
	//}

protected:
	CString GetCurrentSkinPath();

	//Nothing Much - converts e.g, Stretched to CEZDib::BMP_STRETCHED
	virtual UINT  GetDrawTypeFromString(CString strType);
	BOOL m_bDefault;
	BOOL m_bLoaded;
	COLORREF m_clrTxt;
	COLORREF m_clrBk;
	CEZDib m_Dib;
	CFont m_font;

	
	

};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //__EZGENERICSKIN_H__
