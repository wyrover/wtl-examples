#ifndef __ALERT_STYLE_H__
#define __ALERT_STYLE_H__

#pragma once

namespace WTL
{

/*
Interface for the alert styles used to customize the alert windows.
*/
class CAlertStyle
{
public:
    virtual ~CAlertStyle() {}

    // handles the WM_NCPAINT event for a window
    virtual void HandleNcPaint(CWindow* wnd, CDC* dc) = 0;
    // handles the WM_ERASEBKGND event for a window
    virtual bool HandleEraseBkgnd(CWindow* wnd, CDC* dc) = 0;
    // can perform additional initialization
    virtual void OnInitialize(CWindow* wnd) = 0;
};

};

#endif //__ALERT_STYLE_H__
