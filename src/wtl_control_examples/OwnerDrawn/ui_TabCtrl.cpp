//////////////////////////////////////////////////////////////////////////////////////////
//      Project: PinkYeti
//   $Workfile:: ui_TabCtrl.cpp                                        $   - Title
//
//  Description: This class implements an owner drawn tab control that will allow
//               colors to be set for the background, the selected tab, the unselected
//               tab, and the text. You can also set a font, point size, and if it is bold
//
//       Author: Jay Giganti
// Date Created: 2/17/2001
//     $Author:: Jay                                                   $   - Reviewer
//    $Modtime:: 3/07/01 2:51p                                         $   - Date Reviewed
//
//     $Archive:: /Code/Pkgs/UI/ui_TabCtrl.cpp                                           $
//
//  This code may be used in compiled form in any way you desire. This
//  file may be redistributed unmodified by any means PROVIDING it is
//  not sold for profit without the authors written consent, and
//  providing that this notice and the authors name and all copyright
//  notices remains intact.
//
//  Email JGiganti@hotmail.com letting him know how you are using it would be nice as well.
//
//  Most of this code has been modified from other exaples on Code Project to do what I
//  need it to do and/or ported to use WTL
//
//  This file is provided "as is" with no expressed or implied warranty.
//  The author accepts no liability for any damage/loss of business that
//  this product may cause.
//
//////////////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ui_TabCtrl.h"
#include "ui_Helpers.h"

///////////////////////////////////////////////////////////////////////////////////////////
// Function name : ui_TabCtrl
// Description   :
// Return type   :
///////////////////////////////////////////////////////////////////////////////////////////
ui_TabCtrl::ui_TabCtrl() : m_bBoldFont(false), m_nTabH(0), m_nAdjY(0),   m_nPointSize(0)
{
    m_crText        = GetSysColor(COLOR_BTNTEXT);
    m_crBack        = GetSysColor(COLOR_BTNFACE);
    m_crSelected    = GetSysColor(COLOR_BTNFACE);
    m_crUnselected  = GetSysColor(COLOR_BTNFACE);
    m_crHiLight     = GetSysColor(COLOR_BTNFACE);
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name : ui_TabCtrl::~ui_TabCtrl
// Description   :
// Return type   :
///////////////////////////////////////////////////////////////////////////////////////////
ui_TabCtrl::~ui_TabCtrl()
{
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: SubclassWindow
// Description  :
// Return type  : BOOL
// Argument     : HWND hWnd
///////////////////////////////////////////////////////////////////////////////////////////
BOOL ui_TabCtrl::SubclassWindow(HWND hWnd)
{
    BOOL    bRet = CWindowImpl<ui_TabCtrl, CTabCtrl>::SubclassWindow(hWnd);
    Init();
    return  bRet;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: Init
// Description  :
// Return type  : void
///////////////////////////////////////////////////////////////////////////////////////////
void ui_TabCtrl::Init()
{
    HDC         hDC = GetDC();
    TEXTMETRIC  tm;
    GetTextMetrics(hDC, &tm);
    ReleaseDC(hDC);
    m_nAdjY = GetSystemMetrics(SM_CYFRAME);
    m_nTabH = tm.tmHeight + GetSystemMetrics(SM_CYDLGFRAME) * 2 + m_nAdjY;
    ModifyStyle(0, TCS_OWNERDRAWFIXED);
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: SetColors
// Description  :
// Return type  :
// Argument     : const COLORREF    crSelected
// Argument     : const COLORREF    crUnselected
// Argument     : const COLORREF    crBack
// Argument     : const COLORREF    crText
// Argument     : const COLORREF    crHiLight
///////////////////////////////////////////////////////////////////////////////////////////
void ui_TabCtrl::SetColors(const COLORREF crSelected,   const COLORREF crUnselected,
                           const COLORREF crBack,           const COLORREF crText,
                           const COLORREF crHiLight)
{
    m_crSelected        = crSelected;
    m_crUnselected      = crUnselected;
    m_crBack            = crBack;
    m_crText            = crText;
    m_crHiLight         = crHiLight;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: SetFont
// Description  :
// Return type  :
// Argument     : const char * szFont
// Argument     : const bool bBoldFont
// Argument     : const int nPointSize
///////////////////////////////////////////////////////////////////////////////////////////
void ui_TabCtrl::SetFont(const char * szFont, const bool bBoldFont, const int nPointSize)
{
    m_FontName      = szFont;
    m_bBoldFont     = bBoldFont;
    m_nPointSize    = nPointSize;
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
LRESULT ui_TabCtrl::OnDrawItem(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
    UINT                uiCtrlId    = wParam;
    LPDRAWITEMSTRUCT    pInfo       = (LPDRAWITEMSTRUCT)lParam;
    TC_ITEM Item;
    char    Text[256];
    Item.mask       = TCIF_TEXT | TCIF_IMAGE;
    Item.pszText    = Text;
    Item.cchTextMax = 255;

    if (pInfo->CtlType == ODT_TAB && pInfo->hDC && pInfo->itemID >= 0 && GetItem(pInfo->itemID, &Item)) {
        CFont   Font;
        BOOL    bSelected = (pInfo->itemID == (UINT)GetCurSel());
        CRect   rc(pInfo->rcItem);
        int nSavedDC = SaveDC(pInfo->hDC);
        const char * szName =  NULL;

        if (!m_FontName.IsEmpty()) {
            szName = (const char *)m_FontName;
        }

        ui_CreateFont(Font, szName, m_nPointSize, m_bBoldFont);
        SetBkMode(pInfo->hDC, TRANSPARENT);
        SetTextColor(pInfo->hDC, m_crText);
        ui_FillSolidRect(pInfo->hDC, rc, bSelected ? m_crSelected : m_crUnselected);
        // Draw image
        CImageList ImageList = GetImageList();

        if (ImageList && Item.iImage >= 0) {
            SIZE szExt;
            GetTextExtentPoint32(pInfo->hDC, _T(" "), 1, &szExt);
            rc.left += szExt.cx; // Margin
            // Get height of image
            IMAGEINFO info;
            ImageList.GetImageInfo(Item.iImage, &info);
            CRect rcImage(info.rcImage);
            int nYpos = rc.top;
            ImageList.Draw(pInfo->hDC, Item.iImage, CPoint(rc.left, nYpos), ILD_TRANSPARENT);
            rc.left += rcImage.Width();
        }

        {
            ui_PushGDI<HFONT> PushFont(pInfo->hDC, Font);
            DrawText(pInfo->hDC, Text, strlen(Text), rc, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
        }

        RestoreDC(pInfo->hDC, nSavedDC);
    }

    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: PaintArea
// Description  :
// Return type  : void
// Argument     : HDC hDC
///////////////////////////////////////////////////////////////////////////////////////////
void ui_TabCtrl::PaintArea(HDC hDC)
{
    if (hDC) {
        CRect   rcTop;
        GetClientRect(rcTop);
        CRect rcBottom(rcTop);
        int nAdjY       = m_nTabH - m_nAdjY;
        rcTop.bottom    = nAdjY;
        rcBottom.top    = nAdjY;
        ui_FillSolidRect(hDC, rcTop,    m_crBack);
        ui_FillSolidRect(hDC, rcBottom, m_crHiLight);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: OnEraseBkgnd
// Return type  : LRESULT
// Argument     : UINT      uMsg
// Argument     : WPARAM    wParam
// Argument     : LPARAM    lParam
// Argument     : BOOL&     bHandled
///////////////////////////////////////////////////////////////////////////////////////////
LRESULT ui_TabCtrl::OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    bHandled = TRUE;
    return bHandled;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: OnPaint
// Description  : Fill top with the actual tab data with one color and the tab area which
//                  is occupied by something with another
// Return type  : LRESULT
// Argument     : UINT uMsg
// Argument     : WPARAM wParam
// Argument     : LPARAM lParam
// Argument     : BOOL& bHandled
///////////////////////////////////////////////////////////////////////////////////////////
LRESULT ui_TabCtrl::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    PAINTSTRUCT ps;
    HDC         hDC     = (HDC)wParam;
    bool        bCreate = hDC == NULL;

    if (bCreate) {
        hDC = BeginPaint(&ps);
    }

    PaintArea(hDC);
    LRESULT lResult = DefWindowProc(uMsg, WPARAM(hDC), lParam);

    if (bCreate) {
        EndPaint(&ps);
    }

    return lResult;
}
