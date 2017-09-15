#ifndef _THEMEDLABEL_H_INCLUDE_
#define _THEMEDLABEL_H_INCLUDE_
#pragma once
#include "GdiPlusHelper.h"
#include <memory>
using namespace GdiPlusHelper;
using namespace std;

class CThemedLabel : public CWindowImpl<CThemedLabel, CStatic>
{
private:
    CWindow         m_wndParent;            // Parent window.
    CBrushHelper    m_brBack;               // Background brush.
    CString         m_strText;              // Label text.
    CImageHelper    m_imgBack;              // Background image.
    int             m_nWidth;               // Window width.
    int             m_nHeight;              // Window height.
    Color           m_clrText;              // Text color.
    StringAlignment m_TextAlign;            // Text format.
    CFontHelper     m_Font;                 // Font.
    int             m_nTextLeft;            // Text left position.
    int             m_nTextTop;             // Text top position.

    typedef auto_ptr<Bitmap>  AUTO_BITMAP;  // Auto dispose Bitmap.
    AUTO_BITMAP     m_bmpCanvas;            // The canvas for drawing background image and text.

    CRITICAL_SECTION    m_Lock;             // Lock.

    // Constructor and destructor.
public:
    CThemedLabel()
    {
        InitializeCriticalSection(&m_Lock);
        // Initializing font.
        FontFamily   fontFamily(L"Arial");
        m_Font.m_Font = new Font(&fontFamily, 10, FontStyleRegular, UnitPoint);
        m_wndParent     = NULL;
        m_nWidth        = 0;
        m_nHeight       = 0;
        m_nTextLeft     = 0;
        m_nTextTop      = 0;
        m_clrText       = Color(255, 0, 0, 0);
        m_TextAlign     = StringAlignmentNear;
    }

    ~CThemedLabel()
    {
        DeleteCriticalSection(&m_Lock);
    }

    // Operations.
public:
    // Set parent hwnd.
    void SetThemeParent(const HWND hWnd)
    {
        ATLASSERT(::IsWindow(hWnd));
        m_wndParent = hWnd;
    }

    // Set background image.
    void SetBackgroundImage(const int nImageID)
    {
        ATLASSERT(nImageID > 0);
        m_imgBack.Load_Image(nImageID, _T("PNG"));
        DrawLabel();
    }

    // Set text format.
    void SetTextAlign(const StringAlignment align)
    {
        m_TextAlign = align;
        DrawLabel();
    }

    // Set text.
    void SetWindowText(const CString strText)
    {
        m_strText = strText;
        DrawLabel();
    }

    // Adjust text position.
    void AdjustTextPos(const int nTop, const int nLeft)
    {
        m_nTextTop  = nTop;
        m_nTextLeft = nLeft;
        DrawLabel();
    }

// Drawing operations.
private:
    // Draw Label.
    BOOL DrawLabel()
    {
        CRect rcClient;
        GetClientRect(&rcClient);
        RectF rc  = RectF(0.0F, 0.0F, (float)rcClient.Width(), (float)rcClient.Height());

        // client is null, do nothing.
        if (rcClient.Width() == 0) {
            return FALSE;
        }

        EnterCriticalSection(&m_Lock);
        // Create canvas.
        m_bmpCanvas = AUTO_BITMAP(new Bitmap(rcClient.Width(), rcClient.Height()));
        Graphics g(m_bmpCanvas.get());
        // Draw background.
        DrawBackground(g);
        // Draw image and text.
        DrawImageAndText(g, rc);
        // Refresh area.
        InvalidateRect(rcClient);
        LeaveCriticalSection(&m_Lock);
        return TRUE;
    }

    // Get and draw button's background.
    BOOL DrawBackground(Graphics& g)
    {
        CRect rcClient;
        GetClientRect(&rcClient);
        Rect rc(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);

        // Preserve parent background.
        if (m_brBack.m_pBrush == NULL) {
            m_brBack.GetBackGroundBrush(m_hWnd, m_wndParent);
        }

        g.FillRectangle(m_brBack.m_pBrush, rc);
        return TRUE;
    }

    // Draw image and text.
    void DrawImageAndText(Graphics& g, RectF& rc)
    {
        // Draw background image.
        if (m_imgBack.m_pImage != NULL) {
            g.DrawImage(m_imgBack.m_pImage, rc);
        }

        // Draw text.
        RectF rcText  = RectF((float)m_nTextLeft, (float)m_nTextTop, rc.Width, rc.Height);
        SolidBrush solidBrush(m_clrText);
        StringFormat stringFormat;
        stringFormat.SetAlignment(m_TextAlign);
        stringFormat.SetLineAlignment(m_TextAlign);
        g.SetTextRenderingHint(TextRenderingHintAntiAlias);
        g.DrawString(m_strText, -1, m_Font.m_Font, rcText, &stringFormat, &solidBrush);
    }

    // Paint all.
    void DoPaint(Graphics& g)
    {
        EnterCriticalSection(&m_Lock);

        if (m_bmpCanvas.get() != NULL) {
            g.DrawImage(m_bmpCanvas.get(), 0, 0);
        }

        LeaveCriticalSection(&m_Lock);
    }

protected:
    BEGIN_MSG_MAP(CThemedLabel)
    MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    MESSAGE_HANDLER(WM_SETFONT, OnSetFont)
    MESSAGE_HANDLER(WM_PAINT, OnPaint)
    MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
    END_MSG_MAP()

    LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        return 1;
    }

    LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
    {
        int nWidth  = LOWORD(lParam);
        int nHeight = HIWORD(lParam);

        if (m_nWidth != nWidth || m_nHeight != nHeight) {
            EnterCriticalSection(&m_Lock);
            m_nWidth    = nWidth;
            m_nHeight   = nHeight;
            m_brBack.DeleteOldBrush();
            LeaveCriticalSection(&m_Lock);
        }

        return TRUE;
    }

    LRESULT OnSetFont(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
    {
        m_Font.DeleteOldFont();
        CPaintDC dc(m_hWnd);
        m_Font.m_Font = new Font(dc, (HFONT) wParam);
        DrawLabel();
        bHandled = FALSE;
        return 0;
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
};

#endif



