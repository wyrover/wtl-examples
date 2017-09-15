/////////////////////////////////////////////////////////////////////
// This file was created by Ming(2013-05-30).
// You could reach me via 3099jo@163.com.
// Enjoy open source and WTL!
/////////////////////////////////////////////////////////////////////
#ifndef _THEMEDCLOCK_H_INCLUDE_
#define _THEMEDCLOCK_H_INCLUDE_
#pragma once
#include "GdiPlusHelper.h"
using namespace GdiPlusHelper;

class CThemedClock : public CWindowImpl<CThemedClock, CStatic>
{
    /////////////////////////////////////////////////////////////////////
    // Data members.
private:
    CImageHelpers       m_imgClockBkg;
    CImageHelpers       m_imgHour;
    CImageHelpers       m_imgMin;
    CImageHelpers       m_imgSec;
    int                 m_nHour;
    int                 m_nMin;
    int                 m_nSec;
    SYSTEMTIME          m_SysTime;
    float               m_fPointerX;
    float               m_fPointerY;
    Bitmap*             m_bmpPaint;
    CBrushHelper        m_brBack;


    CBrushHelper::GET_BRUSH_TYPE Brush_Type;

    CRITICAL_SECTION    m_Lock;
    enum { TIMER_THEMEDCLOCK };

    /////////////////////////////////////////////////////////////////////
    // Constructor and destructor.
public:
    CThemedClock()
    {
        InitializeCriticalSection(&m_Lock);
        m_nHour     = 0;
        m_nMin      = 0;
        m_nSec      = 0;
        m_fPointerX = 0.0;
        m_fPointerY = 0.0;
        m_bmpPaint  = NULL;
        Brush_Type  = CBrushHelper::GET_BY_WM_PAINT;
    }

    ~CThemedClock()
    {
        DeleteCriticalSection(&m_Lock);
    }

    /////////////////////////////////////////////////////////////////////
    // Operations.
public:
    // Set clock background image.
    BOOL SetClockImage(const int nIDClock)
    {
        if (nIDClock <= 0) {
            return FALSE;
        }

        m_imgClockBkg.Load_Image(nIDClock, _T("PNG"));
        ResizeClient(m_imgClockBkg.m_pImage->GetWidth(), m_imgClockBkg.m_pImage->GetHeight());
        return TRUE;
    }

    // Set clock hour and minute image.
    BOOL SetHourMinSecImage(const int nIDHour, const int nIDMin, const int nIDSec)
    {
        if (nIDHour <= 0 || nIDMin <= 0) {
            return FALSE;
        }

        m_imgHour.Load_Image(nIDHour, _T("PNG"));
        m_imgMin.Load_Image(nIDMin, _T("PNG"));
        m_imgSec.Load_Image(nIDSec, _T("PNG"));
        m_fPointerX = m_imgHour.m_pImage->GetWidth() / 2.0F;
        m_fPointerY = m_imgHour.m_pImage->GetHeight() / 2.0F;
        return TRUE;
    }

    void SetBackBrushType(CBrushHelper::GET_BRUSH_TYPE Type = CBrushHelper::GET_BY_WM_PAINT)
    {
        Brush_Type = Type;
        EnterCriticalSection(&m_Lock);
        m_brBack.DeleteOldBrush();
        LeaveCriticalSection(&m_Lock);
    }
private:
    // Draw clock.
    void DoPaint(Graphics& graphic)
    {
        if (::IsWindowVisible(m_hWnd) == FALSE || m_bmpPaint == NULL) {
            return;
        }

        EnterCriticalSection(&m_Lock);

        if (m_bmpPaint != NULL) {
            graphic.DrawImage(m_bmpPaint, 0, 0);
        }

        LeaveCriticalSection(&m_Lock);
    }

    // Draw clock.
    BOOL DrawClock()
    {
        if (::IsWindowVisible(m_hWnd) == FALSE) {
            return FALSE;
        }

        EnterCriticalSection(&m_Lock);
        CRect rcClient;
        GetClientRect(&rcClient);
        Rect rc(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);

        // Create canvas.
        if (m_bmpPaint != NULL) {
            delete m_bmpPaint;
            m_bmpPaint = NULL;
        }

        m_bmpPaint = new Bitmap(rc.Width, rc.Height);
        Graphics g(m_bmpPaint);

        if (m_brBack.m_pBrush == NULL) {
            m_brBack.GetBackGroundBrush(m_hWnd, GetParent(), Brush_Type);
        }

        g.FillRectangle(m_brBack.m_pBrush, rc);
        // Draw clock background.
        g.DrawImage(m_imgClockBkg.m_pImage, rc);
        // Draw hour.
        g.TranslateTransform(rc.X + rc.Width / 2.0F, rc.Y + rc.Height / 2.0F);
        g.RotateTransform(m_nHour / 12.0F * 360 + m_nMin / 60.0F * 360.0F / 12.0F);
        g.DrawImage(m_imgHour.m_pImage, -m_fPointerX, -m_fPointerY,
                    m_imgHour.GetWidth(), m_imgHour.GetHeight());
        // Draw minute.
        g.ResetTransform();
        g.TranslateTransform(rc.X + rc.Width / 2.0F, rc.Y + rc.Height / 2.0F);
        g.RotateTransform(m_nMin / 60.0F * 360);
        g.DrawImage(m_imgMin.m_pImage, -m_fPointerX, -m_fPointerY,
                    m_imgMin.GetWidth(), m_imgMin.GetHeight());
        // Draw seconds.
        g.ResetTransform();
        g.TranslateTransform(rc.X + rc.Width / 2.0F, rc.Y + rc.Height / 2.0F);
        g.RotateTransform(m_nSec / 60.0F * 360);
        g.DrawImage(m_imgSec.m_pImage, -m_fPointerX, -m_fPointerY,
                    m_imgSec.GetWidth(), m_imgSec.GetHeight());
        LeaveCriticalSection(&m_Lock);
        return TRUE;
    }

    // Get local time.
    void GetClockTime()
    {
        GetLocalTime(&m_SysTime);
        m_nHour = (int)m_SysTime.wHour;
        m_nMin  = (int)m_SysTime.wMinute;
        m_nSec  = (int)m_SysTime.wSecond;
        DrawClock();
    }

    /////////////////////////////////////////////////////////////////////
    // Message mapping.
public:
    BEGIN_MSG_MAP(CThemedClock)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
    MESSAGE_HANDLER(WM_PAINT, OnPaint)
    MESSAGE_HANDLER(WM_TIMER, OnTimer)
    MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    MESSAGE_HANDLER(WM_MOVE, OnMove)
    END_MSG_MAP()

    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        GetClockTime();
        SetTimer(TIMER_THEMEDCLOCK, 1000);
        return 0;
    }

    LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        return 1;
    }

    LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        CPaintDC dcPaint(m_hWnd);
        Graphics graphic(dcPaint.m_hDC);
        DoPaint(graphic);
        return 0;
    }

    LRESULT OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        if (wParam == TIMER_THEMEDCLOCK) {
            GetClockTime();
            CRect rcClient;
            GetClientRect(&rcClient);
            InvalidateRect(rcClient);
        }

        return 0;
    }

    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        KillTimer(TIMER_THEMEDCLOCK);
        bHandled = FALSE;
        return 0;
    }

    LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        EnterCriticalSection(&m_Lock);
        m_brBack.DeleteOldBrush();
        LeaveCriticalSection(&m_Lock);
        bHandled = FALSE;
        return 0;
    }

    LRESULT OnMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        EnterCriticalSection(&m_Lock);
        m_brBack.DeleteOldBrush();
        LeaveCriticalSection(&m_Lock);
        bHandled = FALSE;
        return 0;
    }
};

#endif // _THEMEDCLOCK_H_INCLUDE_