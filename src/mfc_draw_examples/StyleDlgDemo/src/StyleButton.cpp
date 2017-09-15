//
// StyleButton.cpp :
//
// Author:  Darren Sessions
//
//
// Description:
//     StyleButton is a CButton derived control that uses GDI+
//     to support painting and images
//
// History
//      Version 1.1 - 2008 July 25
//      - Changed all button types to styles
//
//      Version 1.0 - 2008 July 1
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
#include "StyleButton.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StyleButton

StyleButton::StyleButton()
{
    m_pCurBtn = NULL;
    m_bIsDisabled = FALSE;
    m_bIsToggle = FALSE;
    m_bIsHovering = FALSE;
    m_bIsTracking = FALSE;
    m_bHaveAltStyle = FALSE;
    m_nCurState = STD_STATE;
    m_pToolTip = NULL;
}

StyleButton::~StyleButton()
{
    if (m_pToolTip)  delete m_pToolTip;
}

BEGIN_MESSAGE_MAP(StyleButton, CButton)
    //{{AFX_MSG_MAP(StyleButton)
    ON_WM_DRAWITEM()
    ON_WM_ERASEBKGND()
    ON_WM_MOUSEMOVE()
    ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
    ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//=============================================================================
//
// LoadStdImage()
//
// Purpose:     The LoadStdImage() Loads the image for the button.  This
//              function (or LoadStdStyle()) must be called at a minimum.
//              Automatically generates the other standard states.
//
// Parameters:
//      [IN]    id
//              resource id, one of the resources already imported with the
//              resource editor, usually begins with IDR_
//
//      [IN]    pType
//              pointer to string describing the resource type
//
// Returns:     BOOL
//              Non zero if successful, otherwise zero
//
//=============================================================================
BOOL StyleButton::LoadStdImage(UINT id, LPCTSTR pType)
{
    CRect rect;
    GetClientRect(rect);
    Stack Std(rect);
    Std.AddImage(CPoint(0, 0), id, pType);
    m_StdStyle.AddStack(Std);
    Stack Press(rect);
    Press.AddImage(CPoint(1, 1), id, pType);
    m_StdPStyle.AddStack(Press);
    Stack Hot(rect);
    Hot.AddImage(CPoint(0, 0), id, pType, FALSE, LIGHTEN);
    m_StdHStyle.AddStack(Hot);
    Stack Gray(rect);
    Gray.AddImage(CPoint(0, 0), id, pType, FALSE, GRAYSCALE);
    m_StdGStyle.AddStack(Gray);
    // create background
    Stack Back(rect);
    Back.FillSolid(CLEAR);
    m_Background.AddStack(Back);
    return TRUE;
}

//=============================================================================
//
// LoadAltImage()
//
// Purpose:     The LoadAltImage() Loads the alternate image for the button.
//              This function call is optional
//              Automatically generates the other alternate states.
//
// Parameters:
//      [IN]    id
//              resource id, one of the resources already imported with the
//              resource editor, usually begins with IDR_
//
//      [IN]    pType
//              pointer to string describing the resource type
//
// Returns:     BOOL
//              Non zero if successful, otherwise zero
//
//=============================================================================
BOOL StyleButton::LoadAltImage(UINT id, LPCTSTR pType)
{
    CRect rect;
    GetClientRect(rect);
    Stack Std(rect);
    Std.AddImage(CPoint(0, 0), id, pType);
    m_AltStyle.AddStack(Std);
    Stack Press(rect);
    Press.AddImage(CPoint(1, 1), id, pType);
    m_AltPStyle.AddStack(Press);
    Stack Hot(rect);
    Hot.AddImage(CPoint(0, 0), id, pType, FALSE, LIGHTEN);
    m_AltHStyle.AddStack(Hot);
    m_bHaveAltStyle = TRUE;
    return TRUE;
}

//=============================================================================
void StyleButton::LoadStdStyle(Style style)
//=============================================================================
{
    // load the standard style
    m_StdStyle = style;
    // create background
    CRect rect;
    GetClientRect(rect);
    Stack Back(rect);
    Back.FillSolid(CLEAR);
    m_Background.AddStack(Back);
    m_StdPStyle = m_StdStyle;
    m_StdPStyle.SetPosition(1, 1);
    m_StdHStyle = m_StdStyle;
    m_StdHStyle.m_Stacks[m_StdHStyle.GetTopIndex()].ApplyTransform(LIGHTEN);
    m_StdGStyle = m_StdStyle;
    m_StdGStyle.m_Stacks[m_StdGStyle.GetTopIndex()].ApplyTransform(GRAYSCALE);
}

//=============================================================================
void StyleButton::LoadAltStyle(Style style)
//=============================================================================
{
    m_AltStyle = style;
    m_AltPStyle = m_AltStyle;
    m_AltPStyle.SetPosition(1, 1);
    m_AltHStyle = m_AltStyle;
    m_AltHStyle.m_Stacks[m_AltHStyle.GetTopIndex()].ApplyTransform(LIGHTEN);
    m_bHaveAltStyle = TRUE;
}

//=============================================================================
void StyleButton::LoadHotStyle(Style style)
//=============================================================================
{
    m_StdHStyle = style;
}

//=============================================================================
void StyleButton::LoadPressedStyle(Style style)
//=============================================================================
{
    m_StdPStyle = style;
}

//=============================================================================
void StyleButton::LoadAltHotStyle(Style style)
//=============================================================================
{
    m_AltHStyle = style;
}

//=============================================================================
void StyleButton::LoadAltPressedStyle(Style style)
//=============================================================================
{
    m_AltPStyle = style;
}

//=============================================================================
// paint the style currently pointed to with m_pCurBtn
//=============================================================================
void StyleButton::PaintBtn(CDC *pDC)
{
    CRect rect;
    GetClientRect(rect);
    // paint the background
    m_Background.PaintStyle(pDC, rect);
    // paint the style
    m_pCurBtn->PaintStyle(pDC, rect);
}

//=============================================================================
// enables the toggle mode
// returns if it doesn't have the alternate image
//=============================================================================
void StyleButton::EnableToggle(BOOL bEnable)
{
    // this only applies when there is an alternate style
    ASSERT(m_bHaveAltStyle);
    m_bIsToggle = bEnable;

    // this actually makes it start in the std state since toggle is called before paint
    if (bEnable) m_pCurBtn = &m_AltStyle;
    else        m_pCurBtn = &m_StdStyle;
}

//=============================================================================
// sets the image type and disabled state then repaints
//=============================================================================
void StyleButton::SetImage(int type)
{
    m_nCurState = type;
    (type == DIS_STATE) ? m_bIsDisabled = TRUE : m_bIsDisabled = FALSE;
    Invalidate();
}

//=============================================================================
// set the control to owner draw
//=============================================================================
void StyleButton::PreSubclassWindow()
{
    // Set control to owner draw
    ModifyStyle(0, BS_OWNERDRAW, SWP_FRAMECHANGED);
    CButton::PreSubclassWindow();
}

//=============================================================================
// disable double click
//=============================================================================
BOOL StyleButton::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_LBUTTONDBLCLK)
        pMsg->message = WM_LBUTTONDOWN;

    if (m_pToolTip != NULL) {
        if (::IsWindow(m_pToolTip->m_hWnd)) {
            m_pToolTip->RelayEvent(pMsg);
        }
    }

    return CButton::PreTranslateMessage(pMsg);
}


//=============================================================================
// overide the erase function
//=============================================================================
BOOL StyleButton::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;
}

//=============================================================================
// Paint the button depending on the state of the mouse
//=============================================================================
void StyleButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
    CDC* pDC = CDC::FromHandle(lpDIS->hDC);

    // handle disabled state
    if (m_bIsDisabled) {
        m_pCurBtn = &m_StdGStyle;
        PaintBtn(pDC);
        return;
    }

    BOOL bIsPressed = (lpDIS->itemState & ODS_SELECTED);

    // handle toggle button
    if (m_bIsToggle && bIsPressed) {
        (m_nCurState == STD_STATE) ? m_nCurState = ALT_STATE : m_nCurState = STD_STATE;
    }

    // determine which style to copy
    if (bIsPressed) {
        if (m_nCurState == STD_STATE)
            m_pCurBtn = &m_StdPStyle;
        else
            m_pCurBtn = &m_AltPStyle;
    } else if (m_bIsHovering) {
        if (m_nCurState == STD_STATE)
            m_pCurBtn = &m_StdHStyle;
        else
            m_pCurBtn = &m_AltHStyle;
    } else {
        if (m_nCurState == STD_STATE)
            m_pCurBtn = &m_StdStyle;
        else
            m_pCurBtn = &m_AltStyle;
    }

    // paint the button
    PaintBtn(pDC);
}

//=============================================================================
LRESULT StyleButton::OnMouseHover(WPARAM wparam, LPARAM lparam)
//=============================================================================
{
    m_bIsHovering = TRUE;
    Invalidate();
    DeleteToolTip();
    // Create a new Tooltip with new Button Size and Location
    SetToolTipText(m_tooltext);

    if (m_pToolTip != NULL) {
        if (::IsWindow(m_pToolTip->m_hWnd)) {
            //Display ToolTip
            m_pToolTip->Update();
        }
    }

    return 0;
}


//=============================================================================
LRESULT StyleButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
//=============================================================================
{
    m_bIsTracking = FALSE;
    m_bIsHovering = FALSE;
    Invalidate();
    return 0;
}

//=============================================================================
void StyleButton::OnMouseMove(UINT nFlags, CPoint point)
//=============================================================================
{
    if (!m_bIsTracking) {
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.hwndTrack = m_hWnd;
        tme.dwFlags = TME_LEAVE | TME_HOVER;
        tme.dwHoverTime = 1;
        m_bIsTracking = _TrackMouseEvent(&tme);
    }

    CButton::OnMouseMove(nFlags, point);
}

//=============================================================================
//
//  Call this member function with a memory DC from the code that paints
//  the parents background.  Passing the screen DC defeats the purpose of
//  using this function.
//
//=============================================================================
void StyleButton::SetBkGnd(CDC* pDC)
{
    CRect rect, rectS;
    CBitmap bmp, *pOldBitmap;
    GetClientRect(rect);
    GetWindowRect(rectS);
    GetParent()->ScreenToClient(rectS);
    m_dcBk.DeleteDC();
    m_dcBk.CreateCompatibleDC(pDC);
    bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
    pOldBitmap = m_dcBk.SelectObject(&bmp);
    m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, rectS.left, rectS.top, SRCCOPY);
    bmp.DeleteObject();
    Regenerate();
}


//=============================================================================
// Set the tooltip with a string resource
//=============================================================================
void StyleButton::SetToolTipText(UINT nId, BOOL bActivate)
{
    // load string resource
    m_tooltext.LoadString(nId);

    // If string resource is not empty
    if (m_tooltext.IsEmpty() == FALSE) {
        SetToolTipText(m_tooltext, bActivate);
    }
}

//=============================================================================
// Set the tooltip with a CString
//=============================================================================
void StyleButton::SetToolTipText(CString spText, BOOL bActivate)
{
    // We cannot accept NULL pointer
    if (spText.IsEmpty()) return;

    // Initialize ToolTip
    InitToolTip();
    m_tooltext = spText;

    // If there is no tooltip defined then add it
    if (m_pToolTip->GetToolCount() == 0) {
        CRect rectBtn;
        GetClientRect(rectBtn);
        m_pToolTip->AddTool(this, m_tooltext, rectBtn, 1);
    }

    // Set text for tooltip
    m_pToolTip->UpdateTipText(m_tooltext, this, 1);
    m_pToolTip->SetDelayTime(2000);
    m_pToolTip->Activate(bActivate);
}

//=============================================================================
void StyleButton::InitToolTip()
//=============================================================================
{
    if (m_pToolTip == NULL) {
        m_pToolTip = new CToolTipCtrl;
        // Create ToolTip control
        m_pToolTip->Create(this);
        m_pToolTip->Activate(TRUE);
    }
}

//=============================================================================
void StyleButton::DeleteToolTip()
//=============================================================================
{
    // Destroy Tooltip incase the size of the button has changed.
    if (m_pToolTip != NULL) {
        delete m_pToolTip;
        m_pToolTip = NULL;
    }
}

//=============================================================================
void StyleButton::Regenerate()
//=============================================================================
{
    m_Background.Regenerate();
    m_StdStyle.Regenerate();
    m_StdPStyle.Regenerate();
    m_StdHStyle.Regenerate();
    m_StdGStyle.Regenerate();

    if (m_bHaveAltStyle) {
        m_AltStyle.Regenerate();
        m_AltPStyle.Regenerate();
        m_AltHStyle.Regenerate();
    }
}