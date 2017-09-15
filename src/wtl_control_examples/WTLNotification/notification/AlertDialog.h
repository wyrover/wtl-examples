#ifndef __ALERT_DIALOG_H__
#define __ALERT_DIALOG_H__

#pragma once

#include "AlertMessages.h"

#define TIMER_VISIBLE   444
#define TIMER_SHOWING   445
#define TIMER_HIDING    446

#define ALPHA_INCREMENT 5

namespace WTL
{

class CAlertStyle;

/*
 Base class for alert dialogs that provides the following features:
 - can show a dialog on top of the task bar with blending animation for showing and hiding
 - use custom animation and visibility time and transparency level
 - can stay active for an indefinite period of time when the mouse is over
   (in which case whenever the mouse hovers the window the visibility elapsed time is reseted)
 - can move the window with the mouse in the screen bounds (regardless the number of monitors)
 - can be parameterized with an alert style for painting the background and the non-client area
*/
template <class T>
class CAlertDialog : public CDialogImpl<T>
{

public:

    BEGIN_MSG_MAP(CAlertDialog)
    MSG_WM_INITDIALOG(OnInitDialog)
    MSG_WM_TIMER(OnTimer)
    MSG_WM_MOUSEMOVE(OnMouseMove)
    MSG_WM_LBUTTONUP(OnLButtonUp)
    MSG_WM_LBUTTONDOWN(OnLButtonDown)
    MSG_WM_NCPAINT(OnNcPaint)
    MSG_WM_ERASEBKGND(OnEraseBkgnd)
    MSG_WM_MOUSEHOVER(OnMouseHover)
    MSG_WM_MOUSELEAVE(OnMouseLeave)
    MSG_WM_CTLCOLORDLG(OnCtlColorDlg)
    REFLECT_NOTIFICATIONS();
    END_MSG_MAP()

private:
    DWORD m_dwTimerVisible;          // timer used for the starting the hiding process
    DWORD m_dwTimerShowing;          // timer used for showing the window
    DWORD m_dwTimerHiding;           // timer used for hiding the window

    DWORD m_dwShowTime;              // interval in milliseconds for showing and hiding the window
    DWORD m_dwLifetime;              // interval in milliseconds for showing the window

    unsigned char m_alpha;           // current alpha-blending value
    unsigned char m_maxAlpha;        // maximum alpha-blending value (maximum opacity)
    bool m_fStayActiveOnMouseHover;  // flag that indicates whether the visibility elapse time should be reseted each time the mouse enters the window area

    CAlertStyle* m_pAlertStyle;      // pointer to an alert style object (does not have ownership)

    bool m_fMouseIsOver;             // indicates whether the mouse is over the window
    bool m_fLeftButtonDown;          // indicates whether the left mouse button is down
    CPoint m_ptDown;                 // point on the screen where the cursor was then the left mouse button was pressed
    CBrush m_hDialogBrush;
private:
    // mouse entered the window area, window opacity is set to the maximum (255)
    void MouseIn()
    {
        // should remain active
        if (m_fStayActiveOnMouseHover) {
            // if dialog is showing stop the animation
            if (m_dwTimerShowing != 0) {
                KillTimer(m_dwTimerShowing);
                m_dwTimerShowing = 0;
            }
            // if the dialog is visible and did not start hiding yet keep it on hold
            else if (m_dwTimerVisible != 0) {
                KillTimer(m_dwTimerVisible);
                m_dwTimerVisible = 0;
            }
            // if the dialog is hiding stop it
            else if (m_dwTimerHiding) {
                KillTimer(m_dwTimerHiding);
                m_dwTimerHiding = 0;
            }

            // show the dialog fully opaque
            m_alpha = 255;
            SetLayeredWindowAttributes(m_hWnd, RGB(0, 0, 0), m_alpha, LWA_ALPHA);
        }
    }
    // mouse left the window area, window opacity is set to the custom maximum value and visibility timer is restarted
    void MouseOut()
    {
        if (m_fStayActiveOnMouseHover) {
            // show the dialog with the max opacity
            m_alpha = m_maxAlpha;
            SetLayeredWindowAttributes(m_hWnd, RGB(0, 0, 0), m_alpha, LWA_ALPHA);
            // start the visibility timer again
            m_dwTimerVisible = SetTimer(TIMER_VISIBLE, m_dwLifetime, NULL);
        }
    }
    // adjusts a rectangle to be bounded into the desktop margins, regardless the number of monitors
    void RectToDesktop(CRect& rect)
    {
        CRect rcdesk;
        SystemParametersInfo(
            SPI_GETWORKAREA,
            0,
            &rcdesk,
            0);

        if (rect.top < rcdesk.top) {
            if (MakeCorrection(rect, TOP, rcdesk)) {
                int diff = rcdesk.top - rect.top;
                rect.top += diff;
                rect.bottom += diff;
            }
        } else if (rect.bottom > rcdesk.bottom) {
            if (MakeCorrection(rect, BOTTOM, rcdesk)) {
                int diff = rect.bottom - rcdesk.bottom;
                rect.top -= diff;
                rect.bottom -= diff;
            }
        } else if (rect.left < rcdesk.left) {
            if (MakeCorrection(rect, LEFT, rcdesk)) {
                int diff = rcdesk.left - rect.left;
                rect.left += diff;
                rect.right += diff;
            }
        } else if (rect.right > rcdesk.right) {
            if (MakeCorrection(rect, RIGHT, rcdesk)) {
                int diff = rect.right - rcdesk.right;
                rect.left -= diff;
                rect.right -= diff;
            }
        }
    }

    // enumeration of edges
    enum Edge {
        TOP       = 1,
        BOTTOM    = 2,
        LEFT      = 3,
        RIGHT     = 4,
    };

    // helper method for adjusting the rectangle into the bounds of the nearest monitor working area
    bool MakeCorrection(const CRect& rect, Edge edge, CRect& rcdesk)
    {
        bool makeCorection = true;
        HMONITOR hMonitor = MonitorFromRect(rect, MONITOR_DEFAULTTONEAREST);

        if (hMonitor != NULL) {
            MONITORINFO mi;
            mi.cbSize = sizeof(mi);
            GetMonitorInfo(hMonitor, &mi);
            rcdesk = mi.rcWork;

            switch (edge) {
            case TOP:
                return (rect.top < rcdesk.top);

            case BOTTOM:
                return (rect.bottom > rcdesk.bottom);

            case LEFT:
                return (rect.left < rcdesk.left);

            case RIGHT:
                return (rect.right > rcdesk.right);
            }
        }

        return false;
    }

public:
    // standard constructor
    CAlertDialog(UINT id, CWindow* pParent = NULL)
    {
        m_fMouseIsOver = FALSE;
        m_fLeftButtonDown = FALSE;
        m_dwTimerVisible = 0;
        m_dwTimerShowing = 0;
        m_dwTimerHiding = 0;
        m_fStayActiveOnMouseHover = FALSE;
        m_wndParent = pParent;
        m_pAlertStyle = NULL;
        m_hDialogBrush.CreateSolidBrush(RGB(0, 0, 255));
    }

    virtual ~CAlertDialog() {};

    // Shows the dialog
    //   showtime - interval in milliseconds for showing/hiding the window
    //   lifespan - interval in milliseconds for the visibility of the window
    //   transparency - maximum opacity value for the window
    //   stayActiveOnMouseHover - indicates whether the visibility elapse time should be reseted when the mouse enters the window area
    void Show(
        DWORD showtime,
        DWORD lifespan,
        unsigned char transparency = 255,
        bool stayActiveOnMouseHover = false)
    {
        unsigned int nDesktopHeight;
        unsigned int nDesktopWidth;
        unsigned int nScreenWidth;
        unsigned int nScreenHeight;
        CRect rcDesktop;
        ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcDesktop, 0);
        nDesktopWidth = rcDesktop.right - rcDesktop.left;
        nDesktopHeight = rcDesktop.bottom - rcDesktop.top;
        nScreenWidth =::GetSystemMetrics(SM_CXSCREEN);
        nScreenHeight =::GetSystemMetrics(SM_CYSCREEN);
        CRect rc;
        GetWindowRect(&rc);
        ScreenToClient(&rc);
        unsigned int m_nStartPosX = rcDesktop.right - rc.Width() - 1;
        unsigned int m_nStartPosY = rcDesktop.bottom - rc.Height();
        m_maxAlpha = transparency;
        m_alpha = 0;
        SetLayeredWindowAttributes(m_hWnd, RGB(0, 0, 0), m_alpha, LWA_ALPHA);
        ShowWindow(SW_SHOW);
        SetWindowPos(
            FindWindow(_T("Shell_TrayWnd"), _T("")),
            m_nStartPosX,
            m_nStartPosY,
            rc.Width(),
            rc.Height(),
            SWP_NOOWNERZORDER | SWP_NOACTIVATE);
        m_dwLifetime = lifespan;
        m_dwShowTime = showtime;
        m_fStayActiveOnMouseHover = stayActiveOnMouseHover;
        m_dwTimerShowing = SetTimer(TIMER_SHOWING, m_dwShowTime / (m_maxAlpha / ALPHA_INCREMENT), NULL);
    }

    // Hides the dialog immediately with no animation.
    void Hide()
    {
        CloseDialog();
    }

    // Sets the pointer to the alert style object used to handle the background and non-client painting.
    void SetAlertStyle(CAlertStyle* handler)
    {
        ATLASSERT(handler != NULL);
        m_pAlertStyle = handler;
        ATLASSERT(this->IsWindow());
        m_pAlertStyle->OnInitialize(this);
        OnInvalidate();
        // invalidate the window with the framework
        Invalidate();
    }

    void OnFinalMessage(HWND /*hWnd*/)
    {
    }

protected:
    CWindow* m_wndParent;

protected:
    //virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
    {
        SetWindowLong(GWL_EXSTYLE, GetWindowLong(GWL_EXSTYLE) | WS_EX_LAYERED);
        return 0;
    }

    // Function called before the window is invalidated.
    // Derived classes that use controls that cache a bitmap should override this and invalidate the cache.
    virtual void OnInvalidate() {}

    // Hides the dialog, killing current timer.
    void CloseDialog()
    {
        if (m_dwTimerShowing != 0) {
            KillTimer(m_dwTimerShowing);
            m_dwTimerShowing = 0;
        }

        if (m_dwTimerHiding != 0) {
            KillTimer(m_dwTimerHiding);
            m_dwTimerHiding = 0;
        }

        if (m_dwTimerVisible != 0) {
            KillTimer(m_dwTimerVisible);
            m_dwTimerVisible = 0;
        }

        m_fMouseIsOver = FALSE;
        ShowWindow(SW_HIDE);
    }

    void OnMouseMove(UINT nFlags, CPoint point)
    {
        if (m_fLeftButtonDown) {
            CPoint ptDiff;
            ptDiff = point - m_ptDown;
            CRect rcWnd;
            GetWindowRect(&rcWnd);
            rcWnd.OffsetRect(ptDiff);
            RectToDesktop(rcWnd);
            MoveWindow(rcWnd);
        } else {
            TRACKMOUSEEVENT t_MouseEvent;
            t_MouseEvent.cbSize      = sizeof(TRACKMOUSEEVENT);
            t_MouseEvent.dwFlags     = TME_LEAVE | TME_HOVER;
            t_MouseEvent.hwndTrack   = m_hWnd;
            t_MouseEvent.dwHoverTime = 1;
            ::_TrackMouseEvent(&t_MouseEvent);
        }
    }

    void OnLButtonUp(UINT nFlags, CPoint point)
    {
        if (m_fLeftButtonDown) {
            ReleaseCapture();
            m_fLeftButtonDown = false;
        }
    }

    void OnLButtonDown(UINT nFlags, CPoint point)
    {
        if (!m_fLeftButtonDown) {
            m_ptDown = point;
            SetCapture();
            m_fLeftButtonDown = true;
        }
    }

    void OnTimer(UINT_PTR nIDEvent)
    {
        if (m_dwTimerShowing == nIDEvent) {
            if (m_alpha + ALPHA_INCREMENT <= m_maxAlpha) {
                m_alpha += ALPHA_INCREMENT;
                SetLayeredWindowAttributes(m_hWnd, RGB(0, 0, 0), m_alpha, LWA_ALPHA);
            } else {
                m_alpha = m_maxAlpha;
                SetLayeredWindowAttributes(m_hWnd, RGB(0, 0, 0), m_alpha, LWA_ALPHA);
                KillTimer(m_dwTimerShowing);
                m_dwTimerShowing = 0;
                m_dwTimerVisible = SetTimer(TIMER_VISIBLE, m_dwLifetime, NULL);
            }
        } else if (m_dwTimerVisible == nIDEvent) {
            KillTimer(m_dwTimerVisible);
            m_dwTimerVisible = 0;
            m_dwTimerHiding = SetTimer(TIMER_HIDING, m_dwShowTime / (m_maxAlpha / ALPHA_INCREMENT), NULL);
        } else if (m_dwTimerHiding) {
            if (m_alpha - ALPHA_INCREMENT >= 0) {
                m_alpha -= ALPHA_INCREMENT;
                SetLayeredWindowAttributes(m_hWnd, RGB(0, 0, 0), m_alpha, LWA_ALPHA);
            } else {
                m_alpha = 0;
                SetLayeredWindowAttributes(m_hWnd, RGB(0, 0, 0), m_alpha, LWA_ALPHA);
                KillTimer(m_dwTimerHiding);
                m_dwTimerHiding = 0;
                CloseDialog();
            }
        }
    }

    void OnMouseHover(WPARAM wParam, CPoint ptPos)
    {
        if (!m_fMouseIsOver) {
            m_fMouseIsOver = TRUE;
            MouseIn();
        }
    }

    void OnMouseLeave()
    {
        if (m_fMouseIsOver) {
            CRect rect;
            GetWindowRect(&rect);
            CPoint point;
            GetCursorPos(&point);

            if (!rect.PtInRect(point)) {
                m_fMouseIsOver = FALSE;
                MouseOut();
            }
        }
    }

    void OnNcPaint(CRgn rgn)
    {
        ATLASSERT(m_hWnd != NULL);
        CPaintDC dc(m_hWnd);
        ATLASSERT(m_pAlertStyle != NULL);
        m_pAlertStyle->HandleNcPaint(this, &dc);
    }

    bool OnEraseBkgnd(HDC hdc)
    {
        CDC dc;
        dc.Attach(hdc);
        ATLASSERT(m_pAlertStyle != NULL);
        bool result = m_pAlertStyle->HandleEraseBkgnd(this, &dc);
        dc.Detach();
        return result;
    }

    HBRUSH OnCtlColorDlg(CDCHandle dc, CWindow wnd)
    {
        return (HBRUSH) m_hDialogBrush;
    }

};

};
#endif // __ALERT_DIALOG_H__