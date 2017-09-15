#ifndef __ALERT_STYLE_FIREFOX_H__
#define __ALERT_STYLE_FIREFOX_H__

#pragma once
#include "AlertStyle.h"
#include <GdiPlus.h>

using namespace Gdiplus;

namespace WTL
{

/*
 Creates a window look similar to the Firefox download notification window,
 with a blue rectangle and a background in the system color COLOR_BTNFACE.
*/
class CAlertStyleFirefox : public CAlertStyle
{
    Pen m_penEdge;
    SolidBrush m_brBackground;
public:
    CAlertStyleFirefox() : m_penEdge(Color(123, 150, 156), 2), m_brBackground(Color())
    {
        m_penEdge.SetAlignment(PenAlignmentInset);
        Color crBackground;
        crBackground.SetFromCOLORREF(GetSysColor(COLOR_BTNFACE));
        m_brBackground.SetColor(crBackground);
    }
    virtual ~CAlertStyleFirefox()
    {
    }

    // handles the WM_NCPAINT event for a window
    virtual void HandleNcPaint(CWindow* wnd, CDC* dc)
    {
        ATLASSERT(wnd != NULL && wnd->IsWindow());
        CRect rc;
        wnd->GetWindowRect(rc);
        wnd->ScreenToClient(rc);
        Graphics g((HDC)*dc);
        Rect rect(rc.left, rc.top, rc.Width(), rc.Height());
        g.DrawRectangle(&m_penEdge, rect);
    }
    // handles the WM_ERASEBKGND event for a window
    virtual bool HandleEraseBkgnd(CWindow* wnd, CDC* dc)
    {
        ATLASSERT(wnd != NULL && wnd->IsWindow());
        CRect rc;
        wnd->GetWindowRect(&rc);
        wnd->ScreenToClient(&rc);
        Graphics g((HDC)*dc);
        Rect rect(rc.left, rc.top, rc.Width(), rc.Height());
        g.FillRectangle(&m_brBackground, rect);
        return true;
    }
    // can perform additional initialization
    virtual void OnInitialize(CWindow* wnd)
    {
        ATLASSERT(wnd != NULL && wnd->IsWindow());
    }
};

};
#endif // __ALERT_STYLE_FIREFOX_H__