//
// StyleEdit.h : Version 1.0 - see article at CodeProject.com
//
// Author:  Darren Sessions
//
//
// Description:
//     StyleEdit is a CEdit derived control that uses the Style class
//     and GDI+ to support different styles
//
// History
//      Version 1.1 - 2008 July 25
//      - Fixed incorrect string in OnNcPaint during some repaint operations
//
//      Version 1.0 - 2008 June 20
//      - Initial public release
//
// License:
//     This software is released under the Code Project Open License (CPOL),
//     which may be found here:  http://www.codeproject.com/info/eula.aspx
//     You are free to use this software in any way you like, except that you
//     may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Style.h"

/////////////////////////////////////////////////////////////////////////////
// StyleEdit window

class StyleEdit : public CEdit
{
// Construction
public:
    StyleEdit();
    virtual ~StyleEdit();

    void SetStack(Stack stack);
    void SetTextClr(COLORREF clr);

    CRect m_rectNCBottom;
    CRect m_rectNCTop;

protected:

    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnUpdate();

    DECLARE_MESSAGE_MAP()

private:

    Style       m_Style;
    CRect       m_EditRect;
    int         m_OffsetY;
    CRect       m_NCRect;
    CBrush      m_HollowBrush;
    COLORREF    m_TextColor;

public:
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
    virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
    afx_msg void OnNcPaint();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
