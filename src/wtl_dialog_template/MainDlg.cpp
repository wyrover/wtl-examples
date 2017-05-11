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
    HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
    SetIcon(hIcon, TRUE);
    HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
    SetIcon(hIconSmall, FALSE);
    DragAcceptFiles(TRUE);
    filename_ = L"img\\png-0070.png";
    this->SetWindowText(L"位图背景 使用StretchBlt贴图");
    this->SetWindowLong(GWL_STYLE, GetWindowLong(GWL_STYLE) | WS_SIZEBOX);
    h_bitmap_ = (HBITMAP)LoadImage(NULL, L"img\\005.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    if (h_bitmap_ == NULL) {
        exit(0);
    } else {
        /*
        HDC hdc;
        hdc = GetDC();
        hdcMem_ = CreateCompatibleDC(hdc);
        SelectObject(hdcMem_, hBitmap_);
        ReleaseDC(hdc);

        GetObject(hBitmap_, sizeof(bm_), &bm_);
        */
        h_bitmap_brush_ = CreatePatternBrush(h_bitmap_);
    }

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


LRESULT CMainDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    WTL::CPaintDC dc(m_hWnd);
    Graphics g(dc.m_hDC);
    DrawPic(dc.m_hDC, filename_);
    //draw_image(m_hWnd, filename_);
    return 0;
}

LRESULT CMainDlg::OnDropFiles(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    HDROP hDropInfo = (HDROP)wParam;
    wchar_t file[MAX_PATH];
    DragQueryFileW(hDropInfo, 0, file, sizeof(file) / sizeof(*file));
    filename_ = string16(file);
    draw_image(m_hWnd, filename_);
    DragFinish(hDropInfo);
    return 0;
}

LRESULT CMainDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    SendMessage(m_hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
    return 0;
}
LRESULT CMainDlg::OnCtlColorMsgDlg(HDC hdc, HWND hwndChild)
{
    /*
    // 这里贴图返回了空画刷
    GetClientRect(&rc_dialog_);
    SetStretchBltMode(hdc, COLORONCOLOR);
    StretchBlt(hdc, 0, 0, rc_dialog_.right, rc_dialog_.bottom, hdc_Mem_, 0, 0, bm_.bmWidth, bm_.bmHeight, SRCCOPY);
    return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
    */
    return (BOOL)h_bitmap_brush_;
}

LRESULT CMainDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    UINT state = (UINT)wParam;
    CSize Size = CSize(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    InvalidateRect(NULL, TRUE);
    return 0;
}

LRESULT CMainDlg::OnCtlColorStatic(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    HDC hdc = (HDC)wParam;
    HWND hwndChild = (HWND)lParam;
    // If an application processes this message, it must return the handle to a brush.
    // The system uses the brush to paint the background of the static control.
    SetBkMode(hdc, TRANSPARENT);
    return (BOOL)h_bitmap_brush_;
}
