#ifndef __ALERT_BUTTON_H__
#define __ALERT_BUTTON_H__

#pragma once

#include "AlertMessages.h"

namespace WTL
{


/*
 The alert button has the following features:
 - is always flat
 - can have a bitmap or icon, which is always displayed in the middle of the client area
 - can specify a transparent color for drawing the image
 - can specify a highlighting color for drawing the background when mouse if over the control
 - notifies its parent when it is clicked
*/
class CAlertButton;
typedef CWindowImpl < CAlertButton, CButton, CWinTraits < WS_CHILD | WS_VISIBLE | BS_OWNERDRAW >> CBaseButton;
class CAlertButton : public CBaseButton , public COwnerDraw<CAlertButton>
{

public:
    DECLARE_WND_SUPERCLASS(_T("ALERT_BUTTON"), _T("BUTTON"))

    BEGIN_MSG_MAP(CAlertButton)
    MSG_WM_MOUSEMOVE(OnMouseMove)
    MSG_WM_LBUTTONDOWN(OnLButtonDown)
    MSG_WM_ERASEBKGND(OnEraseBkgnd)
    CHAIN_MSG_MAP_ALT(COwnerDraw<CAlertButton>, 1)
    DEFAULT_REFLECTION_HANDLER()
    END_MSG_MAP()

    CAlertButton(HWND hWnd = NULL) :
        m_crHighlightColor(255, 0, 0),
        m_brHighlight(m_crHighlightColor),
        m_crTransparent(192, 192, 192)
    {
        m_hWnd = hWnd;
        m_fMouseOver = false;
        m_fHighlightBackground = true;
        m_fIconOwnership = false;
        m_hIcon = NULL;
        m_hBitmap = NULL;
        m_fBitmapOwnership = false;
    }

protected:
    // indicates whether the mouse is over the control
    bool m_fMouseOver;
    // indicates whether the background should be highlighted when the mouse is over
    bool m_fHighlightBackground;

    // handle to the icon resource
    HICON m_hIcon;
    // if true then the icon was loaded by the object and must be freed here
    bool m_fIconOwnership;

    // handle to the bitmap resource
    HBITMAP m_hBitmap;
    // if true then the bitmap was loaded by the object and must be freed here
    bool m_fBitmapOwnership;

    // width of the image (icon or bitmap)
    int m_cxImage;
    // height of the image (icon or bitmap)
    int m_cyImage;

    // transparent color for drawing the image
    Color m_crTransparent;

    // color to use for the background when the mouse is over the control
    Color m_crHighlightColor;
    // brush created from the highlight color
    SolidBrush m_brHighlight;

    // cached bitmap of the parent background on the client area of the button
    CBitmap m_bmpCached;

    // mouse is out of the client area of the button
    void CancelHover()
    {
    }

public:
    virtual ~CAlertButton()
    {
        if (m_hIcon != NULL && m_fIconOwnership) {
            ::DestroyIcon(m_hIcon);
        }

        if (m_hBitmap != NULL && m_fBitmapOwnership) {
            ::DeleteObject(m_hBitmap);
        }
    }

    // loads an icon from the resources and assumes ownership
    void SetIcon(UINT id, int cx, int cy, bool redraw = true)
    {
        if (m_hBitmap != NULL && m_fBitmapOwnership) {
            ::DeleteObject(m_hBitmap);
            m_hBitmap = NULL;
        }

        if (m_hIcon != NULL && m_fIconOwnership) {
            ::DestroyIcon(m_hIcon);
            m_hIcon = NULL;
        }

        m_hIcon = AtlLoadIconImage(id, LR_DEFAULTCOLOR);
        ATLASSERT(m_hIcon != NULL);
        m_cxImage = cx;
        m_cyImage = cy;
        m_fIconOwnership = true;

        if (redraw) {
            Invalidate();
            RedrawWindow();
        }
    }
    // uses a specified icon on which the button does not have ownership
    void SetIcon(HICON icon, int cx, int cy, bool redraw = true)
    {
        if (m_hBitmap != NULL && m_fBitmapOwnership) {
            ::DeleteObject(m_hBitmap);
            m_hBitmap = NULL;
        }

        if (m_hIcon != NULL && m_fIconOwnership) {
            ::DestroyIcon(m_hIcon);
            m_hIcon = NULL;
        }

        m_hIcon = icon;
        m_cxImage = cx;
        m_cyImage = cy;
        m_fIconOwnership = false;

        if (redraw) {
            Invalidate();
            RedrawWindow();
        }
    }

    // loads a bitmap from the resources and assumes ownership
    void SetBitmap(UINT id, bool redraw = true)
    {
        if (m_hBitmap != NULL && m_fBitmapOwnership) {
            ::DeleteObject(m_hBitmap);
            m_hBitmap = NULL;
        }

        if (m_hIcon != NULL && m_fIconOwnership) {
            ::DestroyIcon(m_hIcon);
            m_hIcon = NULL;
        }

        // load with the default size
        m_hBitmap = AtlLoadBitmapImage(id, LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
        ATLASSERT(m_hBitmap != NULL);
        Bitmap bmp(m_hBitmap, AtlGetStockPalette(DEFAULT_PALETTE));
        m_cxImage = bmp.GetWidth();
        m_cyImage = bmp.GetHeight();
        m_fBitmapOwnership = true;

        if (redraw) {
            Invalidate();
            RedrawWindow();
        }
    }

    // uses a specified bitmap on which the button does not have ownership
    void SetBitmap(HBITMAP bitmap, bool redraw = true)
    {
        if (m_hBitmap != NULL && m_fBitmapOwnership) {
            ::DeleteObject(m_hBitmap);
            m_hBitmap = NULL;
        }

        if (m_hIcon != NULL && m_fIconOwnership) {
            ::DestroyIcon(m_hIcon);
            m_hIcon = NULL;
        }

        m_hBitmap = bitmap;
        Bitmap bmp(m_hBitmap, AtlGetStockPalette(DEFAULT_PALETTE));
        m_cxImage = bmp.GetWidth();
        m_cyImage = bmp.GetHeight();
        m_fBitmapOwnership = false;

        if (redraw) {
            Invalidate();
            RedrawWindow();
        }
    }

    // sets the transparent color for drawing the image
    void SetTransparentColor(COLORREF color, bool redraw = true)
    {
        m_crTransparent.SetFromCOLORREF(color);

        if (redraw) {
            Invalidate();
            RedrawWindow();
        }
    }

    // sets the color of the background when the mouse is over the control
    void SetHighlightColor(COLORREF color, bool redraw = true)
    {
        m_crHighlightColor.SetFromCOLORREF(color);
        m_brHighlight.SetColor(m_crHighlightColor);

        if (redraw) {
            Invalidate();
            RedrawWindow();
        }
    }

    // sets the flag for highlighting the background
    void SetHighlightBackground(bool highlight)
    {
        m_fHighlightBackground = highlight;
    }

    // invalidates the cached bitmap for the parent background
    void InvalidateCachedBitmap()
    {
        if (!m_bmpCached.IsNull()) {
            m_bmpCached.DeleteObject();
        }
    }

    BOOL SubclassWindow(HWND hWnd)
    {
        BOOL bRet = CBaseButton::SubclassWindow(hWnd);

        // Switch to owner-draw
        if (bRet)
            ModifyStyle(BS_TYPEMASK, BS_OWNERDRAW, SWP_FRAMECHANGED);

        return bRet;
    }

    void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
    {
        OnDrawItem(lpDrawItemStruct);
    }
protected:
    virtual void OnDrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
    {
        CDCHandle dc = lpDrawItemStruct->hDC;
        CRect rc(lpDrawItemStruct->rcItem);
        Graphics g((HDC)dc);

        if (m_hIcon == NULL && m_hBitmap == NULL) {
            DefWindowProc();
            return;
        }

        if (m_fMouseOver && m_fHighlightBackground) {
            g.FillRectangle(&m_brHighlight, rc.left, rc.top, rc.Width(), rc.Height());
        }

        if (m_hBitmap != NULL) {
            Bitmap bmp(m_hBitmap, AtlGetStockPalette(DEFAULT_PALETTE));
            Rect boundRect(rc.left, rc.top, rc.Width(), rc.Height());
            Rect rect(
                (rc.Width() - m_cxImage) / 2,
                (rc.Height() - m_cyImage) / 2,
                m_cxImage,
                m_cyImage);
            ImageAttributes attributes;
            attributes.SetColorKey(m_crTransparent, m_crTransparent);
            g.DrawImage(&bmp, rect, 0, 0, m_cxImage, m_cyImage, UnitPixel, &attributes);
        } else if (m_hIcon != NULL) {
            Bitmap bmp(rc.Width(), rc.Height());
            Graphics gMem(&bmp);
            Bitmap icon(m_hIcon);
            gMem.DrawImage(&icon,
                           (rc.Width() - m_cxImage) / 2,
                           (rc.Height() - m_cyImage) / 2,
                           m_cxImage, m_cyImage);
            Rect rect(0, 0, rc.Width(), rc.Height());
            ImageAttributes attributes;
            attributes.SetColorKey(m_crTransparent, m_crTransparent);
            g.DrawImage(&bmp, rect, 0, 0, m_cxImage, m_cyImage, UnitPixel, &attributes);
        }

        if (m_fMouseOver) {
            Pen pen(Color(0, 0, 0));
            pen.SetAlignment(PenAlignmentInset);
            g.DrawRectangle(&pen, rc.left, rc.top, rc.Width() - 1, rc.Height() - 1);
        }
    }

    void OnMouseMove(UINT nFlags, CPoint point)
    {
        // If the mouse enter the button with the left button pressed then do nothing
        if (nFlags & MK_LBUTTON && m_fMouseOver == false) return;

        if (m_fMouseOver) {
            CRect rect;
            GetClientRect(&rect);

            if (!rect.PtInRect(point)) {
                m_fMouseOver = false;
                ReleaseCapture();
                Invalidate();
                RedrawWindow();
            }
        } else {
            m_fMouseOver = true;
            Invalidate();
            RedrawWindow();
            SetCapture();
        }
    }

    void OnLButtonDown(UINT nFlags, CPoint point)
    {
        CWindow parent = GetParent();

        if (parent.IsWindow()) {
            parent.PostMessage(WMA_BUTTONCLICKED, GetDlgCtrlID(), 0);
            parent.PostMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), 0), 0);
        }
    }

    bool OnEraseBkgnd(CDCHandle dc)
    {
        if (m_bmpCached.IsNull()) {
            CRect rect;
            GetWindowRect(&rect);
            CWindow parent = GetParent();
            ATLASSERT(parent.IsWindow());
            //convert our coordinates to our parents
            parent.ScreenToClient(&rect);
            //copy what's on the parents at this point
            HDC parentDC = parent.GetDC();
            CDC MemDC;
            MemDC.CreateCompatibleDC(parentDC);
            m_bmpCached.CreateCompatibleBitmap(parentDC, rect.Width(), rect.Height());
            CBitmapHandle oldBmp = MemDC.SelectBitmap(m_bmpCached);
            MemDC.BitBlt(0, 0, rect.Width(), rect.Height(), parentDC, rect.left, rect.top, SRCCOPY);
            MemDC.SelectBitmap(oldBmp);
            parent.ReleaseDC(parentDC);
        } else {
            //copy what we copied off the parent the first time back onto the parent
            CRect rect;
            GetClientRect(&rect);
            CDC MemDC;
            MemDC.CreateCompatibleDC(dc);
            CBitmapHandle oldBmp = MemDC.SelectBitmap(m_bmpCached);
            dc.BitBlt(0, 0, rect.Width(), rect.Height(), MemDC, 0, 0, SRCCOPY);
            MemDC.SelectBitmap(oldBmp);
        }

        return true;
    }
};

};
#endif // __ALERT_BUTTON_H__