//////////////////////////////////////////////////////////////////////////////////////////
//      Project: PinkYeti
//   $Workfile:: ui_Button.cpp                                         $   - Title
//
//  Description: This class allows the drawing of a text button with a specific color
//               for the button, the button text
//
//       Author: Jay Giganti
// Date Created: 2/19/2001
//     $Author:: Jay                                                   $   - Reviewer
//    $Modtime:: 2/20/01 11:12a                                        $   - Date Reviewed
//
//     $Archive:: /Code/Pkgs/UI/ui_Button.cpp                                            $
//
//  This code may be used in compiled form in any way you desire. This
//  file may be redistributed unmodified by any means PROVIDING it is
//  not sold for profit without the authors written consent, and
//  providing that this notice and the authors name and all copyright
//  notices remains intact.
//
//  Most of this code has been modified from other exaples on Code Project to do what I
//  need it to do and/or ported to use WTL
//
//  Email JGiganti@hotmail.com letting him know how you are using it would be nice as well.
//
//  This file is provided "as is" with no expressed or implied warranty.
//  The author accepts no liability for any damage/loss of business that
//  this product may cause.
//
//////////////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ui_Button.h"
#include "ui_Helpers.h"

///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ui_Button
// Description  :
// Return type  :
///////////////////////////////////////////////////////////////////////////////////////////
ui_Button::ui_Button() : m_bDefault(false), m_bShowMenu(false), m_uiMenuId(-1)
{
    SetColors(GetSysColor(COLOR_BTNTEXT), GetSysColor(COLOR_BTNFACE));
    SetBorderColors(GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DHILIGHT));
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ~ui_Button
// Description  :
// Return type  :
///////////////////////////////////////////////////////////////////////////////////////////
ui_Button::~ui_Button()
{
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: operator=
// Description  :
// Return type  : ui_Button::ui_Button&
// Argument     : HWND hWnd
///////////////////////////////////////////////////////////////////////////////////////////
ui_Button & ui_Button::operator=(HWND hWnd)
{
    if (m_hWnd) {
        DestroyWindow();
        m_hWnd = NULL;
    }

    SubclassWindow(hWnd);
    return *this;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: SubclassWindow
// Description  :
// Return type  : BOOL
// Argument     : HWND hWnd
///////////////////////////////////////////////////////////////////////////////////////////
BOOL ui_Button::SubclassWindow(HWND hWnd)
{
    BOOL bRet = CWindowImpl<ui_Button, CButton, CControlWinTraits>::SubclassWindow(hWnd);

    if (bRet) {
        Init();
    }

    return bRet;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: Init
// Description  : Check for default button status and make sure we are owner drawn so
//                windows does not draw anything
// Return type  : void
///////////////////////////////////////////////////////////////////////////////////////////
void ui_Button::Init()
{
    GetAccelFromText();
    m_bDefault  = GetButtonStyle() == BS_DEFPUSHBUTTON;
    SetButtonStyle(BS_OWNERDRAW);
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: GetAccelFromText
// Description  :
// Return type  : void
///////////////////////////////////////////////////////////////////////////////////////////
void ui_Button::GetAccelFromText()
{
    if (GetWindowTextLength() > 0) {
        char szText[256];
        GetWindowText(szText, 256);
        char * pAccel = strchr(szText, '&');

        if (pAccel) {
            pAccel++;
            SetAccel(tolower(*pAccel));
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: SetMenuID
// Description  :
// Return type  : void
// Argument     : UINT nMenuId
///////////////////////////////////////////////////////////////////////////////////////////
void ui_Button::SetMenuID(UINT uiMenuId)
{
    m_uiMenuId = uiMenuId;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: SetColors
// Description  :
// Return type  : void
// Argument     : const COLORREF crText
// Argument     : const COLORREF crButton
///////////////////////////////////////////////////////////////////////////////////////////
void ui_Button::SetColors(const COLORREF crText, const COLORREF crButton)
{
    m_crText    = crText;
    m_crButton  = crButton;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: SetBorderColors
// Description  :
// Return type  : void
// Argument     : const COLORREF crShadow
// Argument     : const COLORREF crDarkShadow
// Argument     : const COLORREF crHiLight
///////////////////////////////////////////////////////////////////////////////////////////
void ui_Button::SetBorderColors(const COLORREF crShadow, const COLORREF crDarkShadow,
                                const COLORREF crHiLight)
{
    m_crShadow      = crShadow;
    m_crDarkShadow  = crDarkShadow;
    m_crHiLight     = crHiLight;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: OnCreate
// Description  :
// Return type  : LRESULT
// Argument     : UINT      uMsg
// Argument     : WPARAM    wParam
// Argument     : LPARAM    lParam
// Argument     : BOOL&     bHandled
///////////////////////////////////////////////////////////////////////////////////////////
LRESULT ui_Button::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    Init();
    bHandled = FALSE;
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: OnSetStyle
// Description  :
// Return type  : LRESULT
// Argument     : UINT      uMsg
// Argument     : WPARAM    wParam
// Argument     : LPARAM    lParam
// Argument     : BOOL&     bHandled
///////////////////////////////////////////////////////////////////////////////////////////
LRESULT ui_Button::OnSetStyle(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    //ATLTRACE("ui_Button::OnSetStyle\n");
    if (BS_DEFPUSHBUTTON == wParam || BS_PUSHBUTTON == wParam) {
        m_bDefault = BS_DEFPUSHBUTTON == wParam;

        if (lParam) {
            RedrawWindow();
        }
    } else {
        bHandled = FALSE;
    }

    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: OnGetDlgCode
// Description  :
// Return type  : LRESULT
// Argument     : UINT      uMsg
// Argument     : WPARAM    wParam
// Argument     : LPARAM    lParam
// Argument     : BOOL&     bHandled
///////////////////////////////////////////////////////////////////////////////////////////
LRESULT ui_Button::OnGetDlgCode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    LRESULT BaseReturn = DLGC_WANTARROWS;

    if (lParam == 0) {
        return BaseReturn | (m_bDefault ? DLGC_DEFPUSHBUTTON : DLGC_UNDEFPUSHBUTTON);
    }

    //ATLTRACE("OnGetDlgCode : %lu - State: %X Id: %d\n", lParam, GetState(), GetDlgCtrlID());
    MSG *pMsg = (MSG*)lParam;

    if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_DOWN || pMsg->wParam == VK_UP) &&
        (BST_FOCUS & GetState())) {
        CRect rect;
        GetClientRect(rect);
        ShowMenu(CPoint(rect.left, rect.bottom));
    } else if (pMsg->message == WM_SYSCHAR) {
        //ATLTRACE("ui_Button-- WM_SYSCHAR -- Our Accel: %X  WParam: %X\n", m_wpAccel, pMsg->wParam);
        if ((m_wpAccel != -1) && (m_wpAccel == pMsg->wParam)) {
            int nID = GetDlgCtrlID();
            //ATLTRACE("ui_Button-- Posting Click for %d\n", nID);
            ::PostMessage(GetParent(), WM_COMMAND, MAKEWPARAM(nID, BN_CLICKED), (LPARAM)m_hWnd);
        } else {
            bHandled = FALSE;
        }
    } else {
        //ATLTRACE("Not Handled -- Message : %X -- WP: %X -- LP: %X\n", pMsg->message, pMsg->wParam, pMsg->lParam);
        bHandled = FALSE;
    }

    return BaseReturn;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: OnLButtonDown
// Description  :
// Return type  : LRESULT
// Argument     : UINT      uMsg
// Argument     : WPARAM    wParam
// Argument     : LPARAM    lParam
// Argument     : BOOL&     bHandled
///////////////////////////////////////////////////////////////////////////////////////////
LRESULT ui_Button::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    //ATLTRACE("ui_Button::OnLButtonDown\n");
    int     xPos    = GET_X_LPARAM(lParam);
    DWORD   dwState = GetState();
    CRect   rect;
    GetClientRect(rect);
    bHandled = FALSE;

    if (m_uiMenuId != -1) {
        if (rect.right - GetSystemMetrics(SM_CXHSCROLL) < xPos && 0 == (BST_PUSHED & dwState)) {
            if (0 == (BST_FOCUS & dwState)) {
                SetFocus();
            }

            ShowMenu(CPoint(rect.left, rect.bottom));
            bHandled = TRUE;
        }
    }

    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: DrawBorder
// Description  :
// Return type  : void
// Argument     : CDC &         dc
// Argument     : const CRect & rc
// Argument     : const bool    bSelected
// Argument     : const bool    bThin
///////////////////////////////////////////////////////////////////////////////////////////
void ui_Button::DrawBorder(CDC & dc, const CRect & rc, const bool bSelected, const bool bThin)
{
    if (bSelected) {                                //Draw a light shadow all the way around
        if (bThin) {
            dc.Draw3dRect(rc, m_crShadow, m_crShadow);
        } else {
            dc.Draw3dRect(rc, m_crDarkShadow, m_crHiLight);
            CRect rcBorder(rc);
            rcBorder.DeflateRect(1, 1);
            dc.Draw3dRect(rcBorder, m_crShadow, m_crButton);
        }
    } else {
        dc.Draw3dRect(rc, m_crHiLight, m_crDarkShadow);
        CRect rcBorder(rc);
        rcBorder.DeflateRect(1, 1);
        dc.Draw3dRect(rcBorder, m_crButton, m_crShadow);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: OnDrawItem
// Description  :
// Return type  : LRESULT
// Argument     : UINT      uMsg
// Argument     : WPARAM    wParam
// Argument     : LPARAM    lParam
// Argument     : BOOL&     bHandled
///////////////////////////////////////////////////////////////////////////////////////////
LRESULT ui_Button::OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    DRAWITEMSTRUCT* lpDIS = (DRAWITEMSTRUCT*)lParam;
    ATLASSERT(lpDIS->CtlType == ODT_BUTTON);
    CRect       rect(lpDIS->rcItem);
    const int   nArrowWidth = GetSystemMetrics(SM_CXHSCROLL);
    const bool  bDisabled   = (ODS_DISABLED & lpDIS->itemState) == ODS_DISABLED;
    const bool  bSelected   = (ODS_SELECTED & lpDIS->itemState) == ODS_SELECTED;
    const bool  bHasFocus   = (ODS_FOCUS    & lpDIS->itemState) == ODS_FOCUS;
    CDC         dc          = lpDIS->hDC;

    //ATLTRACE("ui_Button::OnDrawItem -- Focus : %d  Selected: %d  DrawMenu: %d\n", bHasFocus, bSelected, m_bShowMenu);

    if (bHasFocus || m_bDefault) {  //Draw focus border
        dc.Draw3dRect(rect, m_crDarkShadow, m_crDarkShadow);
        rect.DeflateRect(1, 1);
    }

    ui_FillSolidRect(dc.m_hDC, rect, m_crButton);   //Fill in the button
    DrawBorder(dc, rect, bSelected, true);

    if (m_uiMenuId != -1) {     // Drop down Arrow to show a menu is attached
        CRect rcArrow(rect.right - nArrowWidth - 2, rect.top, rect.right - 2, rect.bottom - 2);
        ui_DrawSplitter(dc.m_hDC, rcArrow, m_crDarkShadow, m_crHiLight);
        rcArrow.DeflateRect(2, 1);
        rcArrow.OffsetRect(1, 0);

        if (bSelected) {
            rcArrow.OffsetRect(1, 0);
            rcArrow.InflateRect(1, 0);
        }

        if (m_bShowMenu) {
            dc.Draw3dRect(rcArrow, m_crDarkShadow, m_crHiLight);
        }

        if (bSelected) {
            rcArrow.DeflateRect(1, 0);
            rcArrow.OffsetRect(0, 1);
        }

        ui_DrawArrow(dc.m_hDC, rcArrow, bDisabled ? m_crShadow : m_crDarkShadow, true);
    }

    TCHAR szCaption[MAX_PATH];

    if (GetWindowText(szCaption, MAX_PATH) > 0) {
        CSize szExtent;
        dc.GetTextExtent(szCaption, -1, &szExtent);
        CPoint ptCenter(rect.CenterPoint());
        CPoint pt;

        if (m_uiMenuId != -1) {
            pt = CPoint(ptCenter.x - szExtent.cx / 2 - nArrowWidth / 2, ptCenter.y - szExtent.cy / 2);
        } else {
            pt = CPoint(ptCenter.x - szExtent.cx / 2, ptCenter.y - szExtent.cy / 2);
        }

        if (bSelected) {
            pt.Offset(1, 1);
        }

        dc.SetBkMode(TRANSPARENT);
        dc.SetTextColor(m_crText);
        dc.DrawState(pt, szExtent, szCaption, bDisabled ? DSS_DISABLED : DSS_NORMAL);
    }

    if (bHasFocus && !m_bShowMenu) {
        CRect rcFocus(rect);

        if (m_uiMenuId != -1) {
            rcFocus.right = rcFocus.right - nArrowWidth - 1;
        }

        rcFocus.DeflateRect(3, 3);
        ui_DrawFocusRect(dc.m_hDC, rcFocus, m_crDarkShadow);
    }

    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ShowMenu
// Description  :
// Return type  : BOOL
// Argument     : CPoint& pt
///////////////////////////////////////////////////////////////////////////////////////////
BOOL ui_Button::ShowMenu(CPoint& pt)
{
    //ATLTRACE("ui_Button::ShowMenu\n");
    BOOL bRet = FALSE;

    if (m_uiMenuId != -1) {
        m_bShowMenu = true;
        RedrawWindow();
        CMenu menu;
        menu.LoadMenu(m_uiMenuId);
        CMenuHandle menuPopup = menu.GetSubMenu(0);
        ClientToScreen(&pt);
        bRet = menuPopup.TrackPopupMenu(0, pt.x, pt.y, GetParent());
        MSG msg;

        while (PeekMessage(&msg, m_hWnd, WM_LBUTTONDOWN, WM_LBUTTONDOWN, PM_REMOVE)) {
            ;
        }

        m_bShowMenu = false;
        RedrawWindow();
    }

    return bRet;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: CreateTip
// Description  :
// Return type  : bool
///////////////////////////////////////////////////////////////////////////////////////////
bool ui_Button::CreateTip()
{
    if (m_Tip.IsWindow() == FALSE) {
        m_Tip.Create(m_hWnd);
        m_Tip.Activate(TRUE);
    }

    bool bReturn = m_Tip.IsWindow() != FALSE;
    ATLASSERT(bReturn);
    return bReturn;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: LoadTipText
// Description  :
// Return type  : void
///////////////////////////////////////////////////////////////////////////////////////////
void ui_Button::LoadTipText()
{
    if (CreateTip()) {
        m_Tip.AddTool(m_hWnd, GetDlgCtrlID());
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: SetTipText
// Description  :
// Return type  : void
// Argument     : const char * szTip
///////////////////////////////////////////////////////////////////////////////////////////
void ui_Button::SetTipText(const char * szTip)
{
    if (CreateTip()) {
        if (szTip == NULL) {
            m_Tip.Activate(FALSE);
        } else {
            m_Tip.Activate(TRUE);
            m_Tip.AddTool(m_hWnd, szTip);
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: OnMouseMessage
// Description  :
// Return type  : LRESULT
// Argument     : UINT uMsg
// Argument     : WPARAM wParam
// Argument     : LPARAM lParam
// Argument     : BOOL& bHandled
///////////////////////////////////////////////////////////////////////////////////////////
LRESULT ui_Button::OnMouseMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    MSG Msg = { m_hWnd, uMsg, wParam, lParam };

    if (m_Tip.IsWindow()) {
        m_Tip.RelayEvent(&Msg);
    }

    bHandled = FALSE;
    return 1;
}
