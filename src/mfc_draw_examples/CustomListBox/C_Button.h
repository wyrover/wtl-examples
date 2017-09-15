#if !defined(AFX_C_BUTTON_H__3D5BB853_ED68_46B0_A849_432456B3AE19__INCLUDED_)
#define AFX_C_BUTTON_H__3D5BB853_ED68_46B0_A849_432456B3AE19__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000
// C_Button.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CC_Button window

class CC_Button : public CButton
{
// Construction
public:
    CC_Button();

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CC_Button)
protected:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CC_Button();

    // Generated message map functions
protected:
    //{{AFX_MSG(CC_Button)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_C_BUTTON_H__3D5BB853_ED68_46B0_A849_432456B3AE19__INCLUDED_)
