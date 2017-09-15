#ifndef __ALERT_STYLE_DEFAULT_H__
#define __ALERT_STYLE_DEFAULT_H__

#pragma once

#include "AlertStyle.h"
#include <GdiPlus.h>
using namespace Gdiplus;

namespace WTL
{

/*
 A simple style implementation that does not handle the background erasing and
 draws a simple edge around the alert window.
*/
class CAlertStyleDefault : public CAlertStyle
{
public:
    CAlertStyleDefault() {}
    virtual ~CAlertStyleDefault() {}

    virtual void HandleNcPaint(CWindow* wnd, CDC* dc)
    {
        ATLASSERT(wnd != NULL && wnd->IsWindow());
        CRect rc;
        wnd->GetWindowRect(&rc);
        wnd->ScreenToClient(&rc);
        Color color(128, 128, 128);
        Pen pen(color);
        Graphics g((HDC)*dc);
        g.DrawRectangle(&pen, 0, 0, rc.Width(), rc.Height());
    }
    virtual bool HandleEraseBkgnd(CWindow* wnd, CDC* dc)
    {
        ATLASSERT(wnd != NULL && wnd->IsWindow());
        CRect rc;
        wnd->GetWindowRect(&rc);
        wnd->ScreenToClient(&rc);
        Graphics g((HDC)*dc);
        Color contentColor(212, 208, 200);
        SolidBrush brush(contentColor);
        g.FillRectangle(&brush, 0, 0, rc.Width(), rc.Height());
        HandleNcPaint(wnd, dc);
        return false;
    }

    virtual void OnInitialize(CWindow* wnd)
    {
        ATLASSERT(wnd != NULL && wnd->IsWindow());
    }
};

};
#endif // __ALERT_STYLE_DEFAULT_H__