#ifndef __ALERT_HYPER_LINK_H__
#define __ALERT_HYPER_LINK_H__

#pragma once
#include "AlertLabel.h"
#include "AlertMessages.h"

namespace WTL
{

/*
 The alert hyper-link is an alert label that has the following features:
 - can have different colors for displaying the text when the mouse is on the control and not
 - can underline the text
 - can have a different cursor when the mouse is over the control
 - can automatically resize the window to fix the text
 - notifies its parent when it is clicked
*/
class CAlertHyperLink : public CAlertLabel
{

public:
    DECLARE_WND_SUPERCLASS(_T("ALERT_HYPER_LINK"), _T("STATIC"))

    BEGIN_MSG_MAP(CAlertHyperLink)
    MSG_OCM_CTLCOLORSTATIC(OnReflectedCtlColorStatic)
    MSG_WM_ERASEBKGND(OnEraseBkgnd)
    MSG_WM_SETCURSOR(OnSetCursor)
    MSG_WM_MOUSEMOVE(OnMouseMove)
    MSG_WM_NCHITTEST(OnNcHitTest)
    MSG_WM_LBUTTONDOWN(OnLButtonDown)
    CHAIN_MSG_MAP(CAlertLabel)
    END_MSG_MAP()


    CAlertHyperLink(HWND hWnd = NULL)
    {
        m_hWnd = hWnd;
        m_crTextColor        = RGB(0, 0, 238);
        m_crHoverColor       = RGB(85, 26, 139);
        m_fUnderline         = FALSE;
        m_fHoverUnderline    = TRUE;
        m_fAdjustToFit       = TRUE;
        m_fMouseOver         = FALSE;
        m_hDefaultCursor     = ::LoadCursor(NULL, IDC_HAND);
        m_hLinkCursor        = m_hDefaultCursor;
    }


public:
    virtual ~CAlertHyperLink()
    {
        ::DestroyCursor(m_hDefaultCursor);
    };

    // sets the color for the text when the mouse is over the control and not
    void SetColors(COLORREF crLink, COLORREF crHover, bool redraw = true)
    {
        m_crTextColor = crLink;
        m_crHoverColor = crHover;

        if (redraw)
            Invalidate();
    }


    // gets the color of the normal text (when the mouse is not over)
    COLORREF GetLinkColor() const
    {
        return GetTextColor();
    }

    // get the color of the hovered text (when the mouse is over the control)
    COLORREF GetHoverColor() const
    {
        return m_crHoverColor;
    }

    // sets flags for underlining the text
    void SetUnderline(bool fUnderline, bool fHoverUnderline, bool redraw = TRUE)
    {
        m_fUnderline = fUnderline;
        m_fHoverUnderline = fUnderline;

        if (redraw)
            Invalidate();
    }

    // indicates whether the normal text is highlighted
    bool GetUnderline() const
    {
        return m_fUnderline;
    }

    // indicates whether the hovered text is highlighted
    bool GetHoverUnderline() const
    {
        return m_fHoverUnderline;
    }


    // auto sizes the the window to fit the text
    void SetAutoSize(bool bAutoSize = TRUE)
    {
        m_fAdjustToFit = bAutoSize;
        PositionWindow();
    }

    // indicates whether the window is auto sized to fit the text
    bool GetAutoSize() const
    {
        return m_fAdjustToFit;
    }

    // sets a new cursor displayed when the mouse hovers the control; does not assume ownership
    void SetLinkCursor(HCURSOR hCursor)
    {
        m_hLinkCursor = hCursor;
    }

private:
    // auto sizes the window
    void PositionWindow()
    {
        if (!m_fAdjustToFit)
            return;

        // Get the current window position
        CRect rect;
        GetWindowRect(&rect);
        CWindow parent = GetParent();
        parent.ScreenToClient(&rect);
        // Get the size of the window text
        int nBufferLen = GetWindowTextLength() + 1;
        LPTSTR strWndText = new TCHAR[nBufferLen];
        ZeroMemory(strWndText, nBufferLen);
        GetWindowText(strWndText, nBufferLen);
        CDC dc = GetDC();
        CSize extent;
        dc.GetTextExtent(strWndText, nBufferLen - 1, &extent);
        dc.DeleteDC();
        delete[] strWndText;
        // Get the text justification via the window style
        DWORD dwStyle = GetStyle();

        // Recalculate the window size and position based on the text justification
        if (dwStyle & SS_CENTERIMAGE)
            rect.DeflateRect(0, (rect.Height() - extent.cy) / 2);
        else
            rect.bottom = rect.top + extent.cy;

        if (dwStyle & SS_CENTER)
            rect.DeflateRect((rect.Width() - extent.cx) / 2, 0);
        else if (dwStyle & SS_RIGHT)
            rect.left  = rect.right - extent.cx;
        else // SS_LEFT = 0, so we can't test for it explicitly
            rect.right = rect.left + extent.cx;

        // Move the window
        SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOZORDER);
    }

    HBRUSH OnReflectedCtlColorStatic(CDCHandle dc, HWND wndStatic)
    {
        if (m_hWnd != wndStatic) {
            return (HBRUSH)GetStockObject(NULL_BRUSH);
        }

        if (m_fMouseOver) {
            dc.SetTextColor(m_crHoverColor);
        } else {
            dc.SetTextColor(m_crTextColor);
        }

        if ((!m_fMouseOver && m_fUnderline) || (m_fMouseOver && m_fHoverUnderline)) {
            if (!(HFONT)m_Font) {
                CFontHandle f = GetFont();
                LOGFONT lf;
                f.GetLogFont(&lf);
                lf.lfUnderline = TRUE;
                m_Font.CreateFontIndirect(&lf);
            }

            dc.SelectFont(m_Font);
        }

        // transparent text.
        dc.SetBkMode(TRANSPARENT);
        return (HBRUSH)GetStockObject(NULL_BRUSH);
    }

    bool OnSetCursor(CWindow wnd, UINT nHitTest, UINT message)
    {
        m_hOldCursor = ::SetCursor(m_hLinkCursor);
        return true;
    }

    void OnMouseMove(UINT nFlags, CPoint point)
    {
        if (m_fMouseOver) {
            CRect rect;
            GetClientRect(&rect);

            if (!rect.PtInRect(point)) {
                m_fMouseOver = false;
                ReleaseCapture();
                Invalidate();
                // restore the old cursor
                ::SetCursor(m_hOldCursor);
            }
        } else {
            m_fMouseOver = true;
            Invalidate();
            SetCapture();
        }
    }

    UINT OnNcHitTest(CPoint point)
    {
        return HTCLIENT;
    }

    void OnLButtonDown(UINT nFlags, CPoint point)
    {
        CWindow parent = GetParent();

        if ((HWND)parent != NULL) {
            parent.PostMessage(WMA_HYPERLINKCLICKED, GetDlgCtrlID(), 0);
            parent.PostMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), 0), 0);
        }

        m_fMouseOver = FALSE;
        ReleaseCapture();
        Invalidate();
    }

private:
    // color of the text when the mouse is over it
    COLORREF m_crHoverColor;
    // indicates whether the text should be normally underlined
    bool m_fUnderline;
    // indicates whether the text should be underlined when the mouse is over
    bool m_fHoverUnderline;
    // indicates that the mouse is over the control
    bool m_fMouseOver;
    // resize the window to fit the text
    bool m_fAdjustToFit;

    // font used for the underlined text
    CFont m_Font;

    // user defined link cursor
    HCURSOR  m_hLinkCursor;
    // default link cursor
    HCURSOR  m_hDefaultCursor;
    // previous cursor
    HCURSOR  m_hOldCursor;

};

};
#endif // __ALERT_LABEL_H__