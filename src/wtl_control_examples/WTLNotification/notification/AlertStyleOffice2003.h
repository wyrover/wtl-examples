#ifndef __ALERT_STYLE_OFFICE2003_H__
#define __ALERT_STYLE_OFFICE2003_H__

#pragma once
#include "AlertStyle.h"
#include <GdiPlus.h>
using namespace Gdiplus;

namespace WTL
{

/*
 Office 2003 like alert style. Displays a blue gradient background, a black rectangle around the window and
 has a small dark blue bar on top of the window.
*/
class CAlertStyleOffice2003 : public CAlertStyle
{
private:
    Pen m_penBlack;
    SolidBrush m_BrushWhite;
    SolidBrush m_BrushBlue;

public:
    CAlertStyleOffice2003() :
        m_penBlack(Color(0, 0, 0)),
        m_BrushWhite(Color(255, 255, 255)),
        m_BrushBlue(Color(52, 67, 90))
    {
    }

    virtual ~CAlertStyleOffice2003(void) {}

    // handles the WM_NCPAINT event for a window
    virtual void HandleNcPaint(CWindow* wnd, CDC* dc)
    {
        ATLASSERT(wnd != NULL && wnd->IsWindow());
        CRect rc;
        wnd->GetWindowRect(&rc);
        wnd->ScreenToClient(&rc);
        // determine the bar rectangle
        CRect bar(rc.left + 1, rc.top + 1, rc.right - 1, rc.top + 7 + 1);
        // draw the bar background
        CGraphicUtils::GradientFillVertical(*dc, &bar, RGB(16, 65, 150), RGB(115, 160, 236), true);
        // draw the bar grip
        int x = (bar.Width() - 32) / 2;
        int y = bar.top + 1;
        Graphics g((HDC)*dc);

        // draw bar handler
        for (int i = 0; i < 8; ++i) {
            // draw the white square
            g.FillRectangle(&m_BrushWhite, x + (i * 6) + 1, y + 1, 3, 3);
            // draw the blue square over the white one
            g.FillRectangle(&m_BrushBlue, x + (i * 6), y, 2, 2);
        }

        g.DrawRectangle(&m_penBlack, rc.left, rc.top, rc.Width(), rc.Height());
    }

    // handles the WM_ERASEBKGND event for a window
    virtual bool HandleEraseBkgnd(CWindow* wnd, CDC* dc)
    {
        ATLASSERT(wnd != NULL && wnd->IsWindow());
        CRect rc;
        wnd->GetWindowRect(&rc);
        wnd->ScreenToClient(&rc);
        rc.DeflateRect(1, 1, 1, 1);
        CGraphicUtils::GradientFillVertical(*dc, &rc, RGB(225, 236, 254), RGB(159, 191, 240));
        HandleNcPaint(wnd, dc);
        return TRUE;
    }
    // can perform additional initialization
    virtual void OnInitialize(CWindow* wnd)
    {
        ATLASSERT(wnd != NULL && wnd->IsWindow());
    }
};

};

#endif // __ALERT_STYLE_OFFICE2003_H__