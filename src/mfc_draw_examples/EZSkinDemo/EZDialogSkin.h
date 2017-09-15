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

#ifndef __EZDIALOGSKIN_H__
#define __EZDIALOGSKIN_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// EZDialogSkin.h : header file
//

#include "EZGenericSkin.h"
/////////////////////////////////////////////////////////////////////////////
// CEZDialogSkin window

class CEZDialogSkin : public CEZGenericSkin
{
// Construction
	DECLARE_SERIAL(CEZDialogSkin)
public:
	CEZDialogSkin();
	
// Attributes
public:

// Operations
public:
// Overrides

protected:
	virtual void LoadDefaultTextColor();
	virtual void LoadDefaultFont();
	virtual void LoadDefaultBmp();
	virtual void LoadDefaultBackColor();
	virtual CString GetSection();

	


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEZDialogSkin)
	public:

	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CEZDialogSkin();

private:
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //__EZDIALOGSKIN_H__
