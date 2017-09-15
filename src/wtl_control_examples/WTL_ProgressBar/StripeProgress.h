/////////////////////////////////////////////////////////////////////
// This file was created by Ming(2013-06-09).
#ifndef _STRIPEPROGRESS_H_INCLUDE_
#define _STRIPEPROGRESS_H_INCLUDE_

#pragma once
#include "GdiPlusHelper.h"
using namespace GdiPlusHelper;

class CStripeProgress : public CWindowImpl<CStripeProgress, CStatic>
{
    /////////////////////////////////////////////////////////////////////
    // Data members.
private:
    CImageHelper        m_imgProgBkg;       // Progress bar background.
    CImageHelper        m_imgProg;          // Progress bar image.
    CImageHelper        m_imgStripe;        // Progress bar image.
    CGraphicsHelper     m_GraphHelper;      // The helper for stretch drawing.
    Bitmap*             m_bmpProg;          // The progress bar canvas.
    CBrushHelper        m_brBack;           // The brush of background.
    CWindow             m_wndParent;        // Parent window.
    CRITICAL_SECTION    m_Lock;             // The lock of drawing images.
    Rect                m_rcProg;           // Progress bar drawing area.
    CPathHelper         m_pathProg;         // Progress bar image path.
    int                 m_nBarLength;       // Progress bar length.
    int                 m_nPercent;         // Progress bar percentage(int).
    float               m_fPercent;         // Progress bar percentage(float).
    int                 m_nOffset;          // Progress bar offset between left and right.
    int                 m_nMiniLength;      // Progress bar minimum length.
    int                 m_nCorner;          // Progress bar corner.
    int                 m_nStripeSpace;     // Two stripe image space.
    int                 m_nBackCorner;      // Progress background image corner.
    int                 m_nLeftIndex;       // The left position of drawing stripe.
    BOOL                m_bStartAnim;       // Indicate animation is started or not.
    int                 m_nMaxAnimOffset;   // The animation maximum moving area, it should equal stripe space width.

    enum { ANIMATED_STRIPE = 200 };     // The timer for display animated stripe.

    /////////////////////////////////////////////////////////////////////
    // Constructor and destructor.
public:
    CStripeProgress() : m_rcProg(0, 0, 0, 0)
    {
        InitializeCriticalSection(&m_Lock);
        m_bmpProg           = NULL;
        m_wndParent         = NULL;
        m_nBarLength        = 0;
        m_nOffset           = 1;
        m_nMiniLength       = 1;
        m_nCorner           = 1;
        m_nStripeSpace      = 1;
        m_nBackCorner       = 1;
        m_nLeftIndex        = 0;
        m_bStartAnim        = FALSE;
        m_nMaxAnimOffset    = 1;
        m_nPercent          = 0;
        m_fPercent          = 0.0F;
    }

    ~CStripeProgress()
    {
        DeleteCriticalSection(&m_Lock);

        if (m_bmpProg != NULL) {
            delete m_bmpProg;
            m_bmpProg = NULL;
        }
    }

    /////////////////////////////////////////////////////////////////////
    // Operations.
public:
    // Set theme parent.
    BOOL SetThemeParent(const HWND wndParent)
    {
        if (::IsWindow(wndParent)) {
            m_wndParent = wndParent;
            return TRUE;
        }

        return FALSE;
    }

    // Set progress bar and its background and stripe image.
    BOOL SetProgressImage(const int nIDBkg, const int nIDProg, const int nIDStripe)
    {
        if (nIDBkg <= 0 || nIDProg <= 0 || nIDStripe <= 0) {
            return FALSE;
        }

        m_imgProgBkg.Load_Image(nIDBkg, _T("PNG"));
        m_imgProg.Load_Image(nIDProg, _T("PNG"));
        m_imgStripe.Load_Image(nIDStripe, _T("PNG"));

        if (::IsWindow(m_hWnd)) {
            CRect rcClient;
            GetClientRect(&rcClient);
            DrawProgress();
            InvalidateRect(&rcClient);
        }

        return TRUE;
    }

    // Set progress bar percentage.
    void SetPercent(UINT nCurrent)
    {
        ATLASSERT(nCurrent <= 100);
        m_nPercent = nCurrent;
        // Calculate progress bar length;
        float fScale = 0.0f;

        if (nCurrent >= 100) {
            fScale = 1.0f;
        } else if (nCurrent == 0) {
            fScale = 0.0f;
        } else {
            fScale = (float)((float)nCurrent / 100.0F);
        }

        m_fPercent = fScale * 100;
        // Progress bar length should not include offset length(both left and right) and minimum length.
        CRect rcClient;
        GetClientRect(&rcClient);
        m_nBarLength = (int)((rcClient.Width() - 2 * m_nOffset - m_nMiniLength) * fScale) ;
        DrawProgress();
        InvalidateRect(&rcClient);
    };

    // Set progress position.
    void SetProgressPos(int nOffset = 1, int nCorner = 1, int nStripeSpace = 1)
    {
        m_nOffset           = nOffset;
        m_nMiniLength       = nOffset;
        m_nCorner           = nCorner;
        m_nStripeSpace      = nStripeSpace;
        m_nMaxAnimOffset    = nStripeSpace;
    }

    // Set background corner.
    void SetBackgroundCorner(int nCorner = 1)
    {
        m_nBackCorner = nCorner;
    }

    // Start drawing stripe dynamically.
    void StartProgressAnimate(BOOL bStart = TRUE)
    {
        if (!m_bStartAnim && bStart) {
            m_bStartAnim = TRUE;
            SetTimer(ANIMATED_STRIPE, 30);
            return;
        }

        m_bStartAnim = FALSE;
        KillTimer(ANIMATED_STRIPE);
    }

private:
    // Draw all the images.
    void DoPaint(Graphics& graphic)
    {
        if (m_wndParent == NULL) {
            return;
        }

        EnterCriticalSection(&m_Lock);

        if (m_bmpProg != NULL) {
            graphic.DrawImage(m_bmpProg, 0, 0);
        }

        LeaveCriticalSection(&m_Lock);
    }

    // Draw progress bar background.
    BOOL DrawBackground(Graphics& g)
    {
        EnterCriticalSection(&m_Lock);
        CRect rcClient;
        GetClientRect(&rcClient);
        Rect rc(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);

        // Preserve parent background.
        if (m_brBack.m_pBrush == NULL) {
            m_brBack.GetBackGroundBrush(m_hWnd, m_wndParent);
        }

        g.FillRectangle(m_brBack.m_pBrush, rc);
        m_GraphHelper.StretchWidthImage(g, m_imgProgBkg.m_pImage, rc, (float)m_nBackCorner);
        LeaveCriticalSection(&m_Lock);
        return TRUE;
    }

    // Draw progress bar.
    BOOL DrawProgress()
    {
        if (m_wndParent == NULL) {
            return FALSE;
        }

        EnterCriticalSection(&m_Lock);

        // Create canvas.
        if (m_bmpProg != NULL) {
            delete m_bmpProg;
            m_bmpProg = NULL;
        }

        CRect rcClient;
        GetClientRect(&rcClient);
        m_bmpProg = new Bitmap(rcClient.Width(), rcClient.Height());
        Graphics g(m_bmpProg);
        // If percentage equal 0, just draw background.
        DrawBackground(g);

        if (m_nBarLength == 0) {
            LeaveCriticalSection(&m_Lock);
            return TRUE;
        }

        m_rcProg.X = m_nOffset;
        m_rcProg.Y = m_nOffset;
        m_rcProg.Width  = m_nBarLength + m_nMiniLength;
        m_rcProg.Height = rcClient.Height();
        // Set clip region for drawing area via progress bar image rect.
        Rect rcStripe = m_rcProg;
        rcStripe.Inflate(-1, -1);
        m_pathProg.CreateRoundRect(rcStripe, 1);
        // Draw progress bar.
        m_GraphHelper.StretchWidthImage(g, m_imgProg.m_pImage, m_rcProg, (float)m_nCorner);
        // Draw stripe.
        DrawStripe(g);
        LeaveCriticalSection(&m_Lock);
        return TRUE;
    }

    // Draw progress bar stripe.
    BOOL DrawStripe(Graphics& g)
    {
        if (m_rcProg.Width <= 0) {
            return FALSE;
        }

        g.SetClip(m_pathProg.m_pPath);
        int nLeftIndex = (int)(-(m_imgStripe.GetWidth()) + m_nLeftIndex);

        // Draw stripe.
        for (int nIndex = nLeftIndex; nIndex < m_rcProg.Width; nIndex += m_nStripeSpace) {
            Rect rc(nIndex, m_rcProg.Y, (int)m_imgStripe.GetWidth(), (int)m_imgStripe.GetHeight());
            g.DrawImage(m_imgStripe.m_pImage, rc);
        }

        return TRUE;
    }

    /////////////////////////////////////////////////////////////////////
    // Message mapping.
public:
    BEGIN_MSG_MAP(CStripeProgress)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
    MESSAGE_HANDLER(WM_PAINT, OnPaint)
    MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    MESSAGE_HANDLER(WM_MOVE, OnSize)
    MESSAGE_HANDLER(WM_TIMER, OnTimer)
    END_MSG_MAP()

    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        return 0;
    }

    LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        return 1;
    }

    LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        if (wParam != NULL) {
            Graphics graphics((HDC) wParam);
            DoPaint(graphics);
        } else {
            CPaintDC dc(m_hWnd);
            Graphics graphics(dc.m_hDC);
            DoPaint(graphics);
        }

        return 0;
    }

    LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        // If progress bar size changed, we need calculate progress bar length.
        m_brBack.DeleteOldBrush();

        if (m_nPercent != 0) {
            SetPercent(m_nPercent);
        }

        bHandled = FALSE;
        return 0;
    }

    LRESULT OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        if (wParam != ANIMATED_STRIPE) {
            return 0;
        }

        if ((int)m_imgStripe.GetWidth() <= 0 || m_rcProg.Width <= 0) {
            return 0;
        }

        m_nLeftIndex++;

        if (m_nLeftIndex >= m_nMaxAnimOffset) {
            m_nLeftIndex = 0;
        }

        DrawProgress();
        CRect rcClient;
        GetClientRect(&rcClient);
        InvalidateRect(rcClient);
        return 0;
    }
};
#endif
