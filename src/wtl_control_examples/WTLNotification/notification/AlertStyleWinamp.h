#ifndef __ALERT_STYLE_WINAMP_H__
#define __ALERT_STYLE_WINAMP_H__

#pragma once
#include "AlertStyle.h"
#include <GdiPlus.h>

using namespace Gdiplus;

namespace WTL
{


/*
 Creates a window look similar to the Winamp new track notification window,
 with a round black border and a grayscale gradient on the background.
*/
class CAlertStyleWinamp : public CAlertStyle
{
    Pen m_penEdge;
    LinearGradientBrush* m_brBackground;
    Color colorFrom;
    Color colorTo;
    float radius;
public:
    CAlertStyleWinamp() :
        colorFrom(182, 182, 182),
        colorTo(44, 44, 44),
        m_penEdge(Color(0, 0, 0)),
        radius(5)
    {
        m_penEdge.SetAlignment(PenAlignmentInset);
    }

    virtual ~CAlertStyleWinamp()
    {
        delete m_brBackground;
    }

    // handles the WM_NCPAINT event for a window
    virtual void HandleNcPaint(CWindow* wnd, CDC* pDC)
    {
        ATLASSERT(wnd != NULL && wnd->IsWindow());
    }
    // handles the WM_ERASEBKGND event for a window
    virtual bool HandleEraseBkgnd(CWindow* wnd, CDC* dc)
    {
        ATLASSERT(wnd != NULL && wnd->IsWindow());
        CRect rc;
        wnd->GetWindowRect(&rc);
        wnd->ScreenToClient(&rc);
        rc.DeflateRect(0, 0, 1, 1);
        float x = static_cast<float>(rc.left);
        float y = static_cast<float>(rc.top);
        float width = static_cast<float>(rc.Width());
        float height = static_cast<float>(rc.Height());
        GraphicsPath path(FillModeWinding);
        GetRoundedRectanglePath(path, x, y, width, height);
        Graphics g((HDC)*dc);
        g.SetSmoothingMode(SmoothingModeAntiAlias);
        g.FillPath(m_brBackground, &path);
        g.DrawPath(&m_penEdge, &path);
        return TRUE;
    }
    // can perform additional initialization
    virtual void OnInitialize(CWindow* wnd)
    {
        ATLASSERT(wnd != NULL && wnd->IsWindow());
        CRect rc;
        wnd->GetWindowRect(&rc);
        wnd->ScreenToClient(&rc);
        float x = static_cast<float>(rc.left);
        float y = static_cast<float>(rc.top);
        float width = static_cast<float>(rc.Width());
        float height = static_cast<float>(rc.Height());
        Graphics g(wnd->GetDC());
        // Round corner Rectangle
        GraphicsPath path(FillModeWinding);
        GetRoundedRectanglePath(path, x, y, width, height);
        Region rgn(&path);
        wnd->SetWindowRgn(rgn.GetHRGN(&g), TRUE);
        m_brBackground = new LinearGradientBrush(RectF(x, y, width, height), colorFrom, colorTo, LinearGradientModeVertical);
    }

    void GetRoundedRectanglePath(GraphicsPath &path, float x, float y, float width, float height)
    {
        path.AddLine(PointF(x + radius, y), PointF(x + width - (radius * 2), y));
        path.AddArc(x + width - (radius * 2), y, radius * 2, radius * 2, 270.0f, 90.0f);
        path.AddLine(PointF(x + width, y + radius), PointF(x + width, y + height - (radius * 2)));
        path.AddArc(x + width - (radius * 2), y + height - (radius * 2), radius * 2, radius * 2, 0.0f, 90.0f);
        path.AddLine(PointF(x + width - (radius * 2), y + height), PointF(x + radius, y + height));
        path.AddArc(x, y + height - (radius * 2), radius * 2, radius * 2, 90.0f, 90.0f);
        path.AddLine(PointF(x, y + height - (radius * 2)), PointF(x, y + radius));
        path.AddArc(x, y, radius * 2, radius * 2, 180.0f, 90.0f);
        path.CloseFigure();
    }

};

};

#endif // __ALERT_STYLE_WINAMP_H__