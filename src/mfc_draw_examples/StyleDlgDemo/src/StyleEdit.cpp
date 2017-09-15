//
// StyleEdit.cpp : Version 1.0 - see article at CodeProject.com
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

#include "stdafx.h"
#include "StyleEdit.h"

#include "colors.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StyleEdit

StyleEdit::StyleEdit()
    : m_EditRect(0, 0, 0, 0)
{
    m_OffsetY = -1;
    m_HollowBrush.CreateStockObject(HOLLOW_BRUSH);
    m_TextColor = Black;
}

StyleEdit::~StyleEdit()
{
}

void StyleEdit::SetStack(Stack stack)
{
    Rect r(stack.Frame.frect);
    CRect cr(r.X, r.Y, r.X + r.Width, r.Y + r.Height);
    m_EditRect = cr;
    m_Style.AddStack(stack);
}
void StyleEdit::SetTextClr(COLORREF clr)
{
    m_TextColor = clr;
}

BEGIN_MESSAGE_MAP(StyleEdit, CEdit)
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_ERASEBKGND()
    ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
    ON_WM_NCCALCSIZE()
    ON_WM_NCPAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// StyleEdit message handlers

HBRUSH StyleEdit::CtlColor(CDC* pDC, UINT nCtlColor)
{
    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextColor(m_TextColor);
    return (HBRUSH)m_HollowBrush;
}

BOOL StyleEdit::OnEraseBkgnd(CDC* pDC)
{
    m_Style.SetPosition(0, m_OffsetY);
    m_Style.PaintStyle(pDC, m_EditRect);
    return TRUE;
}

void StyleEdit::OnUpdate()
{
    Invalidate();
}

// center text vertically
void StyleEdit::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
    CRect rectWnd, rectClient;
    //calculate client area height needed for a font
    CFont *pFont = GetFont();
    CRect rectText;
    rectText.SetRectEmpty();
    CDC *pDC = GetDC();
    CFont *pOld = pDC->SelectObject(pFont);
    pDC->DrawText(_T("Eb"), rectText, DT_CALCRECT | DT_LEFT);
    UINT uiVClientHeight = rectText.Height();
    pDC->SelectObject(pOld);
    ReleaseDC(pDC);
    //calculate NC area to center text.
    GetClientRect(rectClient);
    GetWindowRect(rectWnd);
    ClientToScreen(rectClient);
    UINT uiCenterOffset = (rectClient.Height() - uiVClientHeight) / 2;
    UINT uiCY = (rectWnd.Height() - rectClient.Height()) / 2;
    UINT uiCX = (rectWnd.Width() - rectClient.Width()) / 2;
    m_OffsetY = -(int)uiCenterOffset;
    lpncsp->rgrc[0].top += uiCenterOffset;
    lpncsp->rgrc[0].bottom -= uiCenterOffset;
    lpncsp->rgrc[0].left += uiCX;
    lpncsp->rgrc[0].right -= uiCY;
}

BOOL StyleEdit::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
    if (m_OffsetY == -1) {
        SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
    }

    return CEdit::OnChildNotify(message, wParam, lParam, pLResult);
}

void StyleEdit::OnNcPaint()
{
    Default();
    CWindowDC dc(this);
    CString str;
    GetWindowText(str);
    m_Style.SetPosition(0, 0);
    m_Style.PaintStyle(&dc, m_EditRect);
    SetWindowText(str);
}
