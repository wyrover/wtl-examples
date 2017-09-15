//////////////////////////////////////////////////////////////////////////////////////////
//      Project: Pink Yeti
//   $Workfile:: ui_ColorLabel.cpp                                     $   - Title
//
//  Description: This will allow labels to change the foreground color and will draw it
//               transparently. You can also set the Font Name and Point Size along with
//               Bold, Italic, Underline, and PointSize
//
//       Author: Jay Giganti
// Date Created: 11/04/2000
//     $Author:: Jay                                                   $   - Reviewer
//    $Modtime:: 3/07/01 2:11p                                         $   - Date Reviewed
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
//     $Archive:: /Code/Pkgs/UI/ui_ColorLabel.cpp                                        $
//
//////////////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ui_ColorLabel.h"
#include "ui_Helpers.h"

///////////////////////////////////////////////////////////////////////////////////////////
// Function name : ui_ColorLabel
// Description   :
// Return type   :
///////////////////////////////////////////////////////////////////////////////////////////
ui_ColorLabel::ui_ColorLabel()
{
    m_crText        = GetSysColor(COLOR_BTNTEXT);
    m_crBack        = GetSysColor(COLOR_BTNFACE);
    m_bTransparent  = false;
    LOGFONT lf;
    ::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT), sizeof(lf), &lf);
    CreateFont(lf, false);
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name : ~ui_ColorLabel
// Description   :
// Return type   :
///////////////////////////////////////////////////////////////////////////////////////////
ui_ColorLabel::~ui_ColorLabel()
{
    if (m_Font.m_hFont != NULL) {
        m_Font.DeleteObject();
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: SubclassWindow
// Description  : Grab Text if any. We now use our own text and make sure the window text
//                is empty so button does not draw twice in some situations
// Return type  : void
// Argument     : HWND hWnd
///////////////////////////////////////////////////////////////////////////////////////////
void ui_ColorLabel::SubclassWindow(HWND hWnd)
{
    CWindowImpl<ui_ColorLabel, CWindow>::SubclassWindow(hWnd);

    if (::IsWindow(hWnd)) {
        int nStrLen = GetWindowTextLength();

        if (nStrLen) {
            char szText[256];
            GetWindowText(szText, 255);
            m_Text = szText;
            SetWindowText("");
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: OnPaint
// Description  :
// Return type  : LRESULT
// Argument     : UINT      uMsg
// Argument     : WPARAM    wParam
// Argument     : LPARAM    lParam
// Argument     : BOOL&     bHandled
///////////////////////////////////////////////////////////////////////////////////////////
LRESULT ui_ColorLabel::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    ATLASSERT(m_hWnd);
    CRect       rc;
    CPaintDC    dcMem(m_hWnd);
    int         nStrLen = m_Text.size();
    GetClientRect(rc);

    if (!m_bTransparent) {
        ui_FillSolidRect(dcMem, rc, m_crBack);
    } else {
        //I have not figured out why the parent will not fill the background of
        //So if you update the text something needs to go here to force the parent
        //to repaint the background
    }

    ATLTRACE("ui_ColorLabel::OnPaint -- StrLen: %d - %s\n", nStrLen, m_Text.c_str());

    if (nStrLen > 0) {
        DWORD   dwFlags = DT_LEFT | DT_WORDBREAK;
        DWORD   dwStyle = GetStyle();

        if (dwStyle & SS_RIGHT) {
            dwFlags = DT_RIGHT;
        } else if (dwStyle & SS_CENTER) {
            dwFlags = DT_CENTER;
        }

        if (dwStyle & SS_CENTERIMAGE) {
            dwFlags |= DT_VCENTER;
            dwFlags |= DT_SINGLELINE;
        }

        COLORREF    crOldBk     = 0xFFFFFFFF;
        UINT        nOldMode    = -1;

        if (!m_bTransparent) {
            crOldBk = dcMem.SetBkColor(m_crBack);
        } else {
            nOldMode = dcMem.SetBkMode(TRANSPARENT);
        }

        COLORREF    crOldText   = dcMem.SetTextColor(m_crText);
        HFONT       hOldFont    = dcMem.SelectFont(m_Font.m_hFont);
        dcMem.DrawText(m_Text.c_str(), nStrLen, rc, dwFlags);
        dcMem.SelectFont(hOldFont);
        dcMem.SetTextColor(crOldText);

        if (!m_bTransparent) {
            dcMem.SetBkColor(crOldBk);
        } else {
            dcMem.SetBkMode(nOldMode);
        }
    }

    return TRUE;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: SetBackColor
// Description  :
// Return type  : void
// Argument     : const COLORREF crBack
// Argument     : const bool bRedraw
///////////////////////////////////////////////////////////////////////////////////////////
void ui_ColorLabel::SetBackColor(const COLORREF crBack, const bool bRedraw)
{
    m_crBack = crBack;

    if (bRedraw) {
        RedrawWindow();
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name : ui_ColorLabel::SetTextColor
// Description   :
// Return type   : void
// Argument      : const COLORREF   crText
// Argument      : const bool       bRedraw
///////////////////////////////////////////////////////////////////////////////////////////
void ui_ColorLabel::SetTextColor(const COLORREF crText, const bool bRedraw)
{
    m_crText = crText;

    if (bRedraw) {
        RedrawWindow();
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: SetTransparent
// Description  :
// Return type  : void
// Argument     : const bool bTransparent
// Argument     : const bool bRedraw
///////////////////////////////////////////////////////////////////////////////////////////
void ui_ColorLabel::SetTransparent(const bool bTransparent, const bool bRedraw)
{
    m_bTransparent      = bTransparent;
    DWORD   dwStyle     = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
    DWORD   dwNewStyle  = bTransparent ? dwStyle | WS_EX_TRANSPARENT : dwStyle & ~WS_EX_TRANSPARENT;
    ::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwNewStyle);

    if (bRedraw) {
        RedrawWindow();
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name : ui_ColorLabel::SetText
// Description   :
// Return type   : void
// Argument      : const char * Text
// Argument      : const bool bRedraw
///////////////////////////////////////////////////////////////////////////////////////////
void ui_ColorLabel::SetText(const char * Text, const bool bRedraw)
{
    m_Text = Text;
    ATLTRACE("ui_ColorLabel::SetText -- %s\n", m_Text.c_str());

    if (bRedraw) {
        RedrawWindow();
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name : ui_ColorLabel::CreateFont
// Description   :
// Return type   : void
// Argument      : const LOGFONT & lf
// Argument      : const bool bRedraw
///////////////////////////////////////////////////////////////////////////////////////////
bool ui_ColorLabel::CreateFont(const LOGFONT & lf, const bool bRedraw)
{
    ATLTRACE("ui_ColorLabel::CreateFont -- Redraw: %d -Face (%s)  Height: %d  Width: %d  Weight: %d\n",
             bRedraw, lf.lfFaceName, lf.lfHeight, lf.lfWidth, lf.lfWeight);

    if (m_Font.m_hFont != NULL) {
        m_Font.DeleteObject();
    }

    bool bCreated = (m_Font.CreateFontIndirect(&lf) != NULL);
    ATLASSERT(bCreated);

    if (bRedraw) {
        RedrawWindow();
    }

    return bCreated;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name : ui_ColorLabel::SetFontName
// Description   :
// Return type   : void
// Argument      : const char * FontName
// Argument      : const bool bRedraw
///////////////////////////////////////////////////////////////////////////////////////////
void ui_ColorLabel::SetFontName(const char * FontName, const bool bRedraw)
{
    LOGFONT lf;
    m_Font.GetLogFont(&lf);
    strcpy(lf.lfFaceName, FontName);
    lf.lfCharSet = DEFAULT_CHARSET;
    CreateFont(lf, bRedraw);
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name : ui_ColorLabel::SetFontSize
// Description   :
// Return type   : void
// Argument      : const int nSize
// Argument      : const bool bRedraw
///////////////////////////////////////////////////////////////////////////////////////////
void ui_ColorLabel::SetFontSize(const int nSize, const bool bRedraw)
{
    if (nSize > 0) {
        LOGFONT lf;
        m_Font.GetLogFont(&lf);
        HDC hDC         = GetDC();
        int nLogPixY    = GetDeviceCaps(hDC, LOGPIXELSY);
        ReleaseDC(hDC);
        lf.lfHeight = -MulDiv(nSize, nLogPixY, 72); //Standard conversion
        CreateFont(lf, bRedraw);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name : ui_ColorLabel::SetBold
// Description   :
// Return type   : void
// Argument      : const bool bBold
// Argument      : const bool bRedraw
///////////////////////////////////////////////////////////////////////////////////////////
void ui_ColorLabel::SetBold(const bool bBold, const bool bRedraw)
{
    ATLTRACE("ui_ColorLabel::SetBold -- Redraw: %d\n", bRedraw);
    LOGFONT lf;
    m_Font.GetLogFont(&lf);
    lf.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
    CreateFont(lf, bRedraw);
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name : ui_ColorLabel::SetUnderline
// Description   :
// Return type   : void
// Argument      : const bool bUnderline
// Argument      : const bool bRedraw
///////////////////////////////////////////////////////////////////////////////////////////
void ui_ColorLabel::SetUnderline(const bool bUnderline, const bool bRedraw)
{
    LOGFONT lf;
    m_Font.GetLogFont(&lf);
    lf.lfUnderline = bUnderline;
    CreateFont(lf, bRedraw);
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name : ui_ColorLabel::SetItalic
// Description   :
// Return type   : void
// Argument      : const bool bItalic
// Argument      : const bool bRedraw
///////////////////////////////////////////////////////////////////////////////////////////
void ui_ColorLabel::SetItalic(const bool bItalic, const bool bRedraw)
{
    LOGFONT lf;
    m_Font.GetLogFont(&lf);
    lf.lfItalic = bItalic;
    CreateFont(lf, bRedraw);
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: OnEraseBackground
// Description  :
// Return type  : LRESULT
// Argument     : UINT      uMsg
// Argument     : WPARAM    wParam
// Argument     : LPARAM    lParam
// Argument     : BOOL&     bHandled
///////////////////////////////////////////////////////////////////////////////////////////
LRESULT ui_ColorLabel::OnEraseBackground(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    ATLTRACE("ui_ColorLabel::OnEraseBackground\n");
    bHandled = TRUE;
    return bHandled;
}
