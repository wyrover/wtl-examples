//
// StyleDialog.h: header file for the StyleDialog class.
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

#pragma once

#include "..\resource.h"

// comment out this line if Style Toolkit is not used
#define USE_STYLE_TOOLKIT

// comment out this line if layered windows is not supported - needed for transparency
#define USE_LAYERED_WINDOWS

#ifdef USE_STYLE_TOOLKIT
    #include "StyleButton.h"
#endif

class StyleDialog : public CDialog
{
public:
    StyleDialog();
    StyleDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);
    StyleDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);

    ~StyleDialog(void);

    void    Init();

    void    SetTitle(CString Title)
    {
        m_csTitle = Title;
    }

    void    SetTransparent(BOOL bTransparent = TRUE);
    void    GetFrameRect(LPRECT lpRect);
    void    GetTitleRect(LPRECT lpRect);
    void    SetClientRect(CRect rect);
    void    SetTransparentRect(CRect rect);

    void    GetClientRect(LPRECT lpRect);

    COLORREF    m_OpaqueColor;
    void        SetOpaqueColor(COLORREF clr)
    {
        m_OpaqueColor = clr;
    }

    int         m_bUseOpaqueStyle;

#ifdef USE_STYLE_TOOLKIT
    Style       m_BackGroundStyle;
    Style       m_OpaqueStyle;
    void        AddOpaqueStyle(Style style);
    void        AddBackGroundStyle(Style style);

    StyleButton m_cCancel;
    StyleButton m_cMinimize;
    StyleButton m_cAbout;
#endif

    afx_msg void OnSdClose()
    {
        OnCancel();
    }
    afx_msg void OnSdMinimize()
    {
        ShowWindow(SW_MINIMIZE);
    }
    afx_msg void OnSdAbout()
    {
        SendMessage(WM_SYSCOMMAND, IDM_ABOUTBOX, 0);
    }

#define CTRL_CLIENT         (1 << 0)
#define CTRL_CANCEL         (1 << 1)
#define CTRL_MINIMIZE       (1 << 2)
#define CTRL_ABOUT          (1 << 3)
#define ALL_CONTROLS        (CTRL_CLIENT | CTRL_CANCEL | CTRL_MINIMIZE | CTRL_ABOUT)

    int     m_Controls;
    void    SetControls(int ctrls)
    {
        m_Controls = ctrls;
    }


protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


private:

    void UpdateFrameControls(CDC* pDC);

    BOOL        m_bTransparent;

    BOOL        m_bIsDragging;
    BOOL        m_bBackgroundChanged;

    CRect       m_TitleRect;
    CRect       m_FrameRect;
    CRect       m_ClientRect;
    CRect       m_TransRect;

    CPoint      m_FrameOffset;

    CString     m_csTitle;
    CStatic     m_cClient;

    int         m_TransState;
    CPoint      m_GrabPoint;

    enum TransparentState {
        DISABLED        = 0,
        ACTIVE,
        INACTIVE
    };

public:
    DECLARE_MESSAGE_MAP()
    virtual BOOL OnInitDialog();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
    afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
};
