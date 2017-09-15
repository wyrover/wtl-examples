#ifndef __ALERT_LABEL_H__
#define __ALERT_LABEL_H__

#pragma once

/*
 The alert label has a transparent background and uses a cached bitmap for achieving this.
 When the background is changed, the cache must be invalidated.
 You can set a custom color for the text. By default this color is black.
*/
namespace WTL
{

class CAlertLabel : public CWindowImpl<CAlertLabel, CStatic>
{
public:
    DECLARE_WND_SUPERCLASS(_T("ALERT_LABEL"), _T("STATIC"))

    BEGIN_MSG_MAP(CAlertLabel)
    MSG_OCM_CTLCOLORSTATIC(OnReflectedCtlColorStatic)
    MSG_WM_SETTEXT(OnSetText)
    MSG_WM_ERASEBKGND(OnEraseBkgnd)
    END_MSG_MAP()

    CAlertLabel(HWND hWnd = NULL)
    {
        m_hWnd = hWnd;
        m_crTextColor = RGB(0, 0, 0);
    }

protected:
    COLORREF m_crTextColor;    // color of the text

public:
    virtual ~CAlertLabel() {};

    // invalidates the cached bitmap
    void InvalidateCachedBitmap()
    {
        if (!m_Bmp.IsNull()) {
            m_Bmp.DeleteObject();
        }
    }

    // set the color for the text
    void SetTextColor(COLORREF color, BOOL redraw = TRUE)
    {
        m_crTextColor = color;

        if (redraw)
            Invalidate();
    }

    // get the color of the text
    COLORREF GetTextColor() const
    {
        return m_crTextColor;
    }

protected:

    HBRUSH OnReflectedCtlColorStatic(CDCHandle dc, HWND wndStatic)
    {
        if (m_hWnd != wndStatic) {
            return (HBRUSH)GetStockObject(NULL_BRUSH);
        }

        dc.SetBkMode(TRANSPARENT);
        dc.SetTextColor(m_crTextColor);
        return (HBRUSH)GetStockObject(NULL_BRUSH);
    }

    LRESULT OnSetText(LPCTSTR lpstrText)
    {
        LRESULT result = DefWindowProc();
        Invalidate();
        UpdateWindow();
        return result;
    }

    BOOL OnEraseBkgnd(CDCHandle dc)
    {
        if ((HBITMAP)m_Bmp == NULL) {
            CRect rect;
            GetWindowRect(&rect);
            CWindow parentWnd = GetParent();
            //convert our coordinates to our parents
            parentWnd.ScreenToClient(&rect);
            //copy what's on the parents at this point
            CDC parentDC = parentWnd.GetDC();
            CDC memDC;
            memDC.CreateCompatibleDC(parentDC);
            m_Bmp.CreateCompatibleBitmap(parentDC, rect.Width(), rect.Height());
            CBitmap oldBmp = memDC.SelectBitmap(m_Bmp);
            memDC.BitBlt(0, 0, rect.Width(), rect.Height(), parentDC , rect.left, rect.top, SRCCOPY);
            memDC.SelectBitmap(oldBmp);
        } else {
            //copy what we copied off the parent the first time back onto the parent
            CRect rect;
            GetClientRect(&rect);
            CDC memDC;
            memDC.CreateCompatibleDC(dc);
            CBitmap oldBmp = memDC.SelectBitmap(m_Bmp);
            dc.BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
            memDC.SelectBitmap(oldBmp);
        }

        return TRUE;
    }

protected:
    // the cached bitmap
    CBitmap m_Bmp;
};

}; // END NAMESPACE

#endif // __ALERT_LABEL_H__



