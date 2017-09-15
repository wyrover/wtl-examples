#if !defined(AFX_C_FRAME_H__30EC4973_74C9_433B_B4DF_5A8DD4B19092__INCLUDED_)
#define AFX_C_FRAME_H__30EC4973_74C9_433B_B4DF_5A8DD4B19092__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000
// C_Frame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CC_Frame window

class CC_Frame : public CStatic
{
// Construction
public:
    CC_Frame();

// Attributes
protected:
    COLORREF    m_cr;

// Operations
public:
    void        SetColor(COLORREF cr);
    COLORREF    GetColor();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CC_Frame)
protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CC_Frame();

    // Generated message map functions
protected:
    //{{AFX_MSG(CC_Frame)
    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_C_FRAME_H__30EC4973_74C9_433B_B4DF_5A8DD4B19092__INCLUDED_)
