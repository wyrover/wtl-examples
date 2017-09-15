// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "CustomFont.h"
#include "ThemedLabel.h"

class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
    public CMessageFilter, public CIdleHandler
{
private:
    CThemedLabel m_LabelGreen;
    CThemedLabel m_LabelBlue;
    CCustomFont m_Font;

public:
    enum { IDD = IDD_MAINDLG };

    virtual BOOL PreTranslateMessage(MSG* pMsg)
    {
        return CWindow::IsDialogMessage(pMsg);
    }

    virtual BOOL OnIdle()
    {
        UIUpdateChildWindows();
        return FALSE;
    }

    BEGIN_UPDATE_UI_MAP(CMainDlg)
    END_UPDATE_UI_MAP()

    BEGIN_MSG_MAP(CMainDlg)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
    MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
    MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
    MESSAGE_HANDLER(WM_PAINT, OnPaint)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
    COMMAND_ID_HANDLER(IDOK, OnOK)
    COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
    REFLECT_NOTIFICATIONS()
    END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//  LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//  LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//  LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        // center the dialog on the screen
        CenterWindow();
        // set icons
        HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
        SetIcon(hIcon, TRUE);
        HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
        SetIcon(hIconSmall, FALSE);
        // register object for message filtering and idle updates
        CMessageLoop* pLoop = _Module.GetMessageLoop();
        ATLASSERT(pLoop != NULL);
        pLoop->AddMessageFilter(this);
        pLoop->AddIdleHandler(this);
        UIAddChildWindowContainer(m_hWnd);
        m_Font.SetFont(_T("微软雅黑"), -14, FW_NORMAL);
        CRect rc(0, 0, 172, 27);
        m_LabelBlue.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD, NULL, IDC_BLUE_BUBBLE);
        m_LabelBlue.SetThemeParent(m_hWnd);
        m_LabelBlue.SetBackgroundImage(IDB_BLUE_BUBBLE);
        m_LabelBlue.SetWindowText(_T("自定义标签"));
        m_LabelBlue.SetTextAlign(StringAlignmentCenter);
        m_LabelBlue.SetFont(m_Font.GetCurFont()->m_hFont);
        m_LabelGreen.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD, NULL, IDC_GREEN_BUBBLE);
        m_LabelGreen.SetThemeParent(m_hWnd);
        m_LabelGreen.SetBackgroundImage(IDB_GREEN_BUBBLE);
        m_LabelGreen.SetWindowText(_T("Customized Label"));
        m_LabelGreen.SetTextAlign(StringAlignmentCenter);
        m_LabelGreen.SetFont(m_Font.GetCurFont()->m_hFont);
        return TRUE;
    }

    LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        return 1;
    }

    LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        // wParam not NULL means some sub window want get its background brush.
        if (wParam != NULL) {
            Graphics g((HDC)wParam);
            DoPaint(g);
        } else {
            CPaintDC dc(m_hWnd);
            Graphics g(dc.m_hDC);
            DoPaint(g);
        }

        return 0;
    }

    LRESULT OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        if (m_LabelBlue.m_hWnd) {
            CRect rcLabBlue;
            m_LabelBlue.GetClientRect(&rcLabBlue);
            rcLabBlue.MoveToXY(75, 75);
            m_LabelBlue.MoveWindow(rcLabBlue);
            CRect rcLabGreen;
            m_LabelGreen.GetClientRect(&rcLabGreen);
            rcLabGreen.MoveToXY(50, 140);
            m_LabelGreen.MoveWindow(rcLabGreen);
        }

        return 0;
    }

    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        // unregister message filtering and idle updates
        CMessageLoop* pLoop = _Module.GetMessageLoop();
        ATLASSERT(pLoop != NULL);
        pLoop->RemoveMessageFilter(this);
        pLoop->RemoveIdleHandler(this);
        return 0;
    }

    LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CAboutDlg dlg;
        dlg.DoModal();
        return 0;
    }

    LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        // TODO: Add validation code
        CloseDialog(wID);
        return 0;
    }

    LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CloseDialog(wID);
        return 0;
    }

    void CloseDialog(int nVal)
    {
        DestroyWindow();
        ::PostQuitMessage(nVal);
    }

    void DoPaint(Graphics& g)
    {
        CRect rcClient;
        GetClientRect(&rcClient);
        Rect rc(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height());
        SolidBrush br(Color::DarkGray);
        g.FillRectangle(&br, rc);
    }
};
