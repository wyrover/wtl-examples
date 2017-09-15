// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "MainDlg.h"



LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    // center the dialog on the screen
    CenterWindow();
    // set icons
    HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME),
                                     IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
    SetIcon(hIcon, TRUE);
    HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME),
                                          IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
    SetIcon(hIconSmall, FALSE);
    return TRUE;
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
    dlg.DoModal();
    return 0;
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: Add validation code
    EndDialog(wID);
    return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    EndDialog(wID);
    return 0;
}

LRESULT CMainDlg::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    //CDCHandle dc = (HDC)wParam;
    //TRACE_SEND_A("绘制背景");
    return 1;
}

LRESULT CMainDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    //CDCHandle dc = (HDC)wParam;
    CPaintDC dc(m_hWnd);
    // 绘制背景， 16 进制颜色， b,g,r
    CRect rc;
    rc.CopyRect(window_rc_);
    ScreenToClient(rc);
    TRACE_SEND_FORMAT("窗口矩形: %d, %d, %d, %d", rc.left, rc.top, rc.right, rc.bottom);
    CBrush brush;
    brush.CreateSolidBrush(0xffff00);
    dc.FillRect(rc, brush);
    return 0;
}

LRESULT CMainDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    //UINT nType = (UINT)wParam;
    //CSize size = _WTYPES_NS::CSize(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
    this->GetClientRect(client_rc_);
    TRACE_SEND_FORMAT("客户区矩形: %d, %d, %d, %d", client_rc_.left, client_rc_.top, client_rc_.right, client_rc_.bottom);
    this->GetWindowRect(window_rc_);
    TRACE_SEND_FORMAT("窗口矩形: %d, %d, %d, %d", window_rc_.left, window_rc_.top, window_rc_.right, window_rc_.bottom);
    return 0;
}
