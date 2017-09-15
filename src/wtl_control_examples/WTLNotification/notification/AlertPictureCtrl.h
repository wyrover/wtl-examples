#ifndef __ALERT_PICTURE_CTRL_H__
#define __ALERT_PICTURE_CTRL_H__

#pragma once

#include "AlertLabel.h"
#include "GraphicUtils.h"
#include <GdiPlus.h>

using namespace Gdiplus;

namespace WTL
{

/*
 The alert picture control displays an image that can be transparent. Has the following features:
 - can display either an icon or a bitmap
 - can use a transparent color for drawing the image
*/
class CAlertPictureCtrl : public CAlertLabel
{

public:
    DECLARE_WND_SUPERCLASS(_T("ALERT_PICTURE_CTRL"), _T("STATIC"))

    BEGIN_MSG_MAP(CAlertPictureCtrl)
    MSG_WM_PAINT(OnPaint)
    CHAIN_MSG_MAP(CAlertLabel)
    END_MSG_MAP()

    CAlertPictureCtrl(HWND hWnd = NULL) : m_crTransparent(192, 192, 192)
    {
        m_hWnd = hWnd;
        m_fIconOwnership = false;
        m_hIcon = NULL;
        m_hBitmap = NULL;
        m_fBitmapOwnership = false;
    }

    virtual ~CAlertPictureCtrl() {};

    // loads an icon from the resources and assumes ownership
    void SetIcon(UINT id, int cx, int cy, bool redraw = TRUE)
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
        SetWindowPos(NULL, 0, 0, m_cxImage, m_cyImage, SWP_NOMOVE | SWP_NOOWNERZORDER);
        ChangeWindowStyle(SS_BITMAP, SS_ICON | SS_CENTERIMAGE);
        CAlertLabel::SetIcon(m_hIcon);

        if (redraw)
            Invalidate();
    }

    // uses a specified icon on which the button does not have ownership
    void SetIcon(HICON icon, int cx, int cy, bool redraw = TRUE)
    {
        if (m_hBitmap != NULL && m_fBitmapOwnership) {
            ::DeleteObject(m_hBitmap);
            m_hBitmap = NULL;
        }

        if (m_hIcon != NULL && m_fIconOwnership) {
            ::DestroyIcon(m_hIcon);
        }

        m_hIcon = icon;
        m_cxImage = cx;
        m_cyImage = cy;
        m_fIconOwnership = false;
        SetWindowPos(NULL, 0, 0, m_cxImage, m_cyImage, SWP_NOMOVE | SWP_NOOWNERZORDER);
        ChangeWindowStyle(SS_BITMAP, SS_ICON | SS_CENTERIMAGE);
        CAlertLabel::SetIcon(m_hIcon);

        if (redraw) {
            Invalidate();
            RedrawWindow();
        }
    }

    // loads a bitmap from the resources and assumes ownership
    void SetBitmap(UINT id, bool redraw = TRUE)
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
        ChangeWindowStyle(SS_ICON, SS_BITMAP | SS_CENTERIMAGE);
        CAlertLabel::SetBitmap(m_hBitmap);
        SetWindowPos(NULL, 0, 0, m_cxImage, m_cyImage, SWP_NOMOVE | SWP_NOOWNERZORDER);

        if (redraw) {
            Invalidate();
            RedrawWindow();
        }
    }

    // uses a specified bitmap on which the button does not have ownership
    void SetBitmap(HBITMAP bitmap, bool redraw = TRUE)
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
        SetWindowPos(NULL, 0, 0, m_cxImage, m_cyImage, SWP_NOMOVE | SWP_NOOWNERZORDER);
        ChangeWindowStyle(SS_ICON, SS_BITMAP | SS_CENTERIMAGE);
        CAlertLabel::SetBitmap(m_hBitmap);

        if (redraw) {
            Invalidate();
            RedrawWindow();
        }
    }

    // sets the transparent color for drawing the image
    void SetTransparentColor(COLORREF color, bool redraw = TRUE)
    {
        m_crTransparent.SetFromCOLORREF(color);

        if (redraw) {
            Invalidate();
            RedrawWindow();
        }
    }

protected:
    void OnPaint(CDCHandle /*dc*/)
    {
        CBitmapHandle hBitmap = GetBitmap();
        HICON hIcon = GetIcon();

        if ((HBITMAP)hBitmap == NULL && hIcon == NULL) {
            DefWindowProc();
            return;
        }

        CPaintDC dc(m_hWnd);
        CRect rc;
        GetClientRect(&rc);

        if (hBitmap != NULL) {
            Bitmap bmp((HBITMAP)hBitmap, AtlGetStockPalette(DEFAULT_PALETTE));
            Graphics g((HDC)dc);
            Rect rect(rc.left, rc.top, rc.Width(), rc.Height());
            ImageAttributes attributes;
            attributes.SetColorKey(m_crTransparent, m_crTransparent);
            g.DrawImage(&bmp, rect, 0, 0, bmp.GetWidth(), bmp.GetHeight(), UnitPixel, &attributes);
        } else if (hIcon != NULL) {
            Bitmap bmp(rc.Width(), rc.Height());
            Graphics gMem(&bmp);
            Bitmap icon(hIcon);
            gMem.DrawImage(&icon,
                           (rc.Width() - m_cxImage) / 2,
                           (rc.Height() - m_cyImage) / 2,
                           m_cxImage, m_cyImage);
            Graphics g((HDC)dc);
            Rect rect(rc.left, rc.top, rc.Width(), rc.Height());
            ImageAttributes attributes;
            attributes.SetColorKey(m_crTransparent, m_crTransparent);
            g.DrawImage(&bmp, rect, 0, 0, bmp.GetWidth(), bmp.GetHeight(), UnitPixel, &attributes);
        }
    }

private:
    // transparent color of the image
    Color m_crTransparent;

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

    void ChangeWindowStyle(DWORD removeStyle, DWORD addStyle)
    {
        DWORD style = GetWindowLong(GWL_STYLE);
        style &= ~ removeStyle;
        style |= addStyle;
        SetWindowLong(GWL_STYLE, style);
    }

} ;

};
#endif // __ALERT_PICTURE_CTRL_H__