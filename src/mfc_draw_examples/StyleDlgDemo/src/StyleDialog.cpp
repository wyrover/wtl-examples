//
// StyleDialog.cpp:
//
// Author:  Darren Sessions
//
//
// Description:
//
//      The StyleDialog class allows the use of transparency and layers
//      when implementing a dialog.
//
// History
//     Version 1.1 - 2008 August 1
//     - Initial release
//
// License:
//     This software is released under the Code Project Open License (CPOL),
//     which may be found here:  http://www.codeproject.com/info/eula.aspx
//     You are free to use this software in any way you like, except that you
//     may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "StyleDialog.h"

void StyleDialog::Init()
{
    m_bTransparent  = FALSE;
    m_TransState    = DISABLED;
    m_csTitle       = "";
    m_bIsDragging   = FALSE;
    m_Controls = 0;
    m_bBackgroundChanged = TRUE;
    CRect NullRect(0, 0, 0, 0);
    m_TitleRect     = NullRect;
    m_FrameRect     = NullRect;
    m_ClientRect    = NullRect;
    m_TransRect     = NullRect;
    m_FrameOffset.x = 0;
    m_FrameOffset.y = 0;
    m_OpaqueColor = GetSysColor(COLOR_BACKGROUND);
    m_bUseOpaqueStyle = 0;
}

StyleDialog::StyleDialog()
{
    Init();
}

StyleDialog::StyleDialog(UINT nIDTemplate, CWnd* pParentWnd)
    : CDialog(nIDTemplate, pParentWnd)
{
    Init();
}

StyleDialog::StyleDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
    : CDialog(lpszTemplateName, pParentWnd)
{
    Init();
}

StyleDialog::~StyleDialog()
{
}

BOOL StyleDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (m_Controls & CTRL_CLIENT) {
        CDialog::GetClientRect(m_FrameRect);
        m_cClient.GetWindowRect(m_ClientRect);
        ScreenToClient(m_ClientRect);
        m_TitleRect = m_FrameRect;
        m_TitleRect.bottom = m_ClientRect.top;
        m_TransRect = m_FrameRect;
    } else {
        CRect r(0, 0, 0, 0);
        CalcWindowRect(r, 0);
        m_FrameOffset.x = -r.left;
        m_FrameOffset.y = -r.top;
        GetWindowRect(m_FrameRect);
        ScreenToClient(m_FrameRect);
        m_FrameRect.OffsetRect(m_FrameOffset);
        CDialog::GetClientRect(m_ClientRect);
        m_TitleRect = m_FrameRect;
        m_TitleRect.bottom = m_FrameOffset.y;
        m_TransRect = m_FrameRect;
        m_TransRect.left -= r.left;
        m_TransRect.top -= r.top;
        m_TransRect.right -= r.right;
        m_TransRect.bottom -= r.bottom;
        GetClientRect(m_TransRect);
    }

#ifdef USE_LAYERED_WINDOWS

    if (m_bTransparent) {
        m_TransState = INACTIVE;
        SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
        SetLayeredWindowAttributes(0, 255, LWA_ALPHA);
    }

#endif

    // this will show up in the task bar
    if (m_csTitle.GetLength() > 0)
        SetWindowText(m_csTitle);

#ifdef USE_STYLE_TOOLKIT
#ifdef IDC_SD_CLIENT
    GetSystemMenu(FALSE)->RemoveMenu(SC_MOVE, MF_BYCOMMAND);
#endif
#ifdef IDC_SD_CANCEL

    if (m_Controls & CTRL_CANCEL)
        m_cCancel.LoadStdImage(IDR_CANCEL, _T("PNG"));

#endif
#ifdef IDC_SD_MINIMIZE

    if (m_Controls & CTRL_MINIMIZE)
        m_cMinimize.LoadStdImage(IDR_MINIMIZE, _T("PNG"));

#endif
#ifdef IDC_SD_ABOUT

    if (m_Controls & CTRL_ABOUT)
        m_cAbout.LoadStdImage(IDR_ABOUT, _T("PNG"));

#endif
#endif
    // maximize could be supported but code would have to be added
    SetWindowLong(m_hWnd, GWL_STYLE, GetWindowLong(m_hWnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
    return TRUE;
}

void StyleDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
#ifdef USE_STYLE_TOOLKIT
#ifdef IDC_SD_CLIENT

    if (m_Controls & CTRL_CLIENT)
        DDX_Control(pDX, IDC_SD_CLIENT, m_cClient);

#endif
#ifdef IDC_SD_CANCEL

    if (m_Controls & CTRL_CANCEL)
        DDX_Control(pDX, IDC_SD_CANCEL, m_cCancel);

#endif
#ifdef IDC_SD_MINIMIZE

    if (m_Controls & CTRL_MINIMIZE)
        DDX_Control(pDX, IDC_SD_MINIMIZE, m_cMinimize);

#endif
#ifdef IDC_SD_ABOUT

    if (m_Controls & CTRL_ABOUT)
        DDX_Control(pDX, IDC_SD_ABOUT, m_cAbout);

#endif
#endif
}

BEGIN_MESSAGE_MAP(StyleDialog, CDialog)
#ifdef IDC_SD_CANCEL
    ON_BN_CLICKED(IDC_SD_CANCEL, OnSdClose)
#endif
#ifdef IDC_SD_MINIMIZE
    ON_BN_CLICKED(IDC_SD_MINIMIZE, OnSdMinimize)
#endif
#ifdef IDC_SD_ABOUT
    ON_BN_CLICKED(IDC_SD_ABOUT, OnSdAbout)
#endif
    ON_WM_WINDOWPOSCHANGING()
    ON_WM_ERASEBKGND()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_MOVE()
    ON_WM_ACTIVATE()
    ON_WM_RBUTTONDOWN()
    ON_WM_NCLBUTTONDOWN()
END_MESSAGE_MAP()

void StyleDialog::SetTransparent(BOOL bTransparent)
{
#ifdef USE_LAYERED_WINDOWS
    m_bTransparent = bTransparent;

    if (bTransparent) {
        m_TransState = ACTIVE;

        if (m_hWnd) {
            SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
            SetLayeredWindowAttributes(0, 255, LWA_ALPHA);
        }
    } else {
        m_TransState = DISABLED;

        if (m_hWnd) {
            SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) & ~WS_EX_LAYERED);
        }
    }

#endif
}

void StyleDialog::GetClientRect(LPRECT lpRect)
{
    lpRect->top = m_ClientRect.top;
    lpRect->left = m_ClientRect.left;
    lpRect->right = m_ClientRect.right;
    lpRect->bottom = m_ClientRect.bottom;
}

void StyleDialog::SetClientRect(CRect rect)
{
    m_ClientRect = rect;
}

void StyleDialog::SetTransparentRect(CRect rect)
{
    m_TransRect = rect;
}

void StyleDialog::GetFrameRect(LPRECT lpRect)
{
    lpRect->top = m_FrameRect.top;
    lpRect->left = m_FrameRect.left;
    lpRect->right = m_FrameRect.right;
    lpRect->bottom = m_FrameRect.bottom;
}

void StyleDialog::GetTitleRect(LPRECT lpRect)
{
    lpRect->top = m_TitleRect.top;
    lpRect->left = m_TitleRect.left;
    lpRect->right = m_TitleRect.right;
    lpRect->bottom = m_TitleRect.bottom;
}

void StyleDialog::OnRButtonDown(UINT nFlags, CPoint point)
{
#ifdef IDC_SD_CLIENT
    CMenu* pMenu = GetSystemMenu(FALSE);
    pMenu->EnableMenuItem(SC_MOVE, MF_BYCOMMAND | MF_DISABLED);
#endif
    SendMessage(WM_SYSCOMMAND, SC_KEYMENU, LPARAM(' '));
    CDialog::OnRButtonDown(nFlags, point);
}

void StyleDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (m_TitleRect.PtInRect(point)) {
        SetCapture();
        m_GrabPoint = point;
        m_bIsDragging = TRUE;
    }

    CDialog::OnLButtonDown(nFlags, point);
}

void StyleDialog::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
    if (m_bTransparent && nHitTest == HTCAPTION) {
        ReleaseCapture();
        CDialog::ScreenToClient(&point);
        CRect r(0, 0, 0, 0);
        CalcWindowRect(r, 0);
        point.x -= r.left;
        point.y -= r.top;
        OnLButtonDown(nHitTest, point);
    } else {
        CDialog::OnNcLButtonDown(nHitTest, point);
    }
}

void StyleDialog::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_bIsDragging) {
        if (m_TransState == ACTIVE) {
            m_TransState = INACTIVE;
            m_bBackgroundChanged = TRUE;
            Invalidate();
        }

        ClientToScreen(&point);
        SetWindowPos(NULL, point.x - m_GrabPoint.x, point.y - m_GrabPoint.y, 0, 0,
                     SWP_NOZORDER | SWP_NOSIZE);
    }
}

void StyleDialog::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (m_bIsDragging) {
        ReleaseCapture();
        m_bIsDragging = FALSE;

        if (m_TransState == INACTIVE) {
            m_TransState = ACTIVE;
            m_bBackgroundChanged = TRUE;
            Invalidate();
        }
    }

    CDialog::OnLButtonUp(nFlags, point);
}

BOOL StyleDialog::OnEraseBkgnd(CDC* pDC)
{
    if (!m_bTransparent) {
        CDialog::OnEraseBkgnd(pDC);
    }

    if (m_TransState == INACTIVE) {
        if (m_bUseOpaqueStyle) {
#ifdef USE_STYLE_TOOLKIT
            m_OpaqueStyle.PaintStyle(pDC, m_TransRect);
#endif
        } else {
            CBrush br;
            br.CreateSolidBrush(m_OpaqueColor);
            pDC->FillRect(m_TransRect, &br);
        }
    } else if (m_TransState == ACTIVE) {
        CRect wr;
        GetWindowRect(wr);
        wr.OffsetRect(m_FrameOffset);
        int dstx = m_TransRect.left;
        int dsty = m_TransRect.top;
        int width = m_TransRect.Width();
        int height = m_TransRect.Height();
        int srcx = wr.left + dstx;
        int srcy = wr.top + dsty;
        CDC* pDesk = GetDesktopWindow()->GetDC();
        pDC->BitBlt(dstx, dsty, width, height, pDesk, srcx, srcy, SRCCOPY);
        GetDesktopWindow()->ReleaseDC(pDesk);
    }

#ifdef USE_STYLE_TOOLKIT

    if (m_bBackgroundChanged) {
        UpdateFrameControls(pDC);
        m_bBackgroundChanged = FALSE;
        m_BackGroundStyle.Regenerate();
    }

    m_BackGroundStyle.PaintStyle(pDC, m_FrameRect);
#endif
    return TRUE;
}

void StyleDialog::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
    if ((lpwndpos->flags & SWP_FRAMECHANGED) == SWP_FRAMECHANGED) {
        m_bBackgroundChanged = TRUE;
    }

    CDialog::OnWindowPosChanging(lpwndpos);
}

void StyleDialog::UpdateFrameControls(CDC* pDC)
{
#ifdef USE_STYLE_TOOLKIT
#ifdef IDC_SD_CANCEL

    if (m_Controls & CTRL_CANCEL)
        m_cCancel.SetBkGnd(pDC);

#endif
#ifdef IDC_SD_MINIMIZE

    if (m_Controls & CTRL_MINIMIZE)
        m_cMinimize.SetBkGnd(pDC);

#endif
#ifdef IDC_SD_ABOUT

    if (m_Controls & CTRL_ABOUT)
        m_cAbout.SetBkGnd(pDC);

#endif
#endif
}

#ifdef USE_STYLE_TOOLKIT
void StyleDialog::AddBackGroundStyle(Style style)
{
    m_BackGroundStyle = style;
}

void StyleDialog::AddOpaqueStyle(Style style)
{
    m_OpaqueStyle = style;
    m_bUseOpaqueStyle = TRUE;
}
#endif

void StyleDialog::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
    if (m_TransState != DISABLED) {
        if (nState == WA_INACTIVE) {
            m_TransState = INACTIVE;
        } else if (nState == WA_CLICKACTIVE) {
            m_TransState = ACTIVE;
        } else {
            m_TransState = ACTIVE;
        }

        if (bMinimized == 0) {
            m_bBackgroundChanged = TRUE;
            Invalidate();
        }
    }

    CDialog::OnActivate(nState, pWndOther, bMinimized);
}
