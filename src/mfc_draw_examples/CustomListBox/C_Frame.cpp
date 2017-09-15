// C_Frame.cpp : implementation file
//

#include "stdafx.h"
#include "CustomListBox.h"
#include "C_Frame.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CC_Frame

CC_Frame::CC_Frame()
{
    m_cr = DLG_COLOR_BACKGROUND;
}

CC_Frame::~CC_Frame()
{
}


BEGIN_MESSAGE_MAP(CC_Frame, CStatic)
    //{{AFX_MSG_MAP(CC_Frame)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PROTECTED METHODS

void CC_Frame::SetColor(COLORREF cr)
{
    m_cr = cr;
    Invalidate();
}

COLORREF CC_Frame::GetColor()
{
    return m_cr;
}

/////////////////////////////////////////////////////////////////////////////
// CC_Frame message handlers

void CC_Frame::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();
    ModifyStyle(0, SS_NOTIFY);
}

void CC_Frame::OnPaint()
{
    CPaintDC    dc(this); // device context for painting
    CRect       rFrame;
    GetClientRect(rFrame);
    dc.FillSolidRect(rFrame, m_cr);
    dc.Draw3dRect(rFrame, RGB(128, 128, 128), RGB(128, 128, 128));
}

void CC_Frame::OnLButtonDown(UINT nFlags, CPoint point)
{
    CColorDialog dlg(m_cr, CC_FULLOPEN | CC_ANYCOLOR);

    if (dlg.DoModal() == IDOK) {
        m_cr = dlg.GetColor();
        Invalidate();
    }

    CStatic::OnLButtonDown(nFlags, point);
}

