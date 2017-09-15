// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "ThemedClock.h"

class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
    public CMessageFilter, public CIdleHandler
{
private:
    CThemedClock m_FlowerClock;
    CThemedClock m_ModernClock;

    void DoPaint(Graphics& g)
    {
        CRect rcClient;
        GetClientRect(&rcClient);
        Rect rc(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height());
        SolidBrush br(Color::Orange);
        g.FillRectangle(&br, rc);
    }

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
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    //MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
    //MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
    //MESSAGE_HANDLER(WM_PAINT, OnPaint)
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
        SetWindowText(_T("Ming's WTL Clock"));
        m_FlowerClock.Create(m_hWnd, NULL, NULL, WS_VISIBLE | WS_CHILD, NULL, IDC_FLOWER_CLOCK);
        m_FlowerClock.SetClockImage(IDB_FLOWER_BKG);
        m_FlowerClock.SetHourMinSecImage(IDB_FLOWER_HOUR, IDB_FLOWER_MIN, IDB_FLOWER_SEC);
        m_FlowerClock.SetBackBrushType(CBrushHelper::GET_BY_WM_ERASEBKGND);
        m_ModernClock.Create(m_hWnd, NULL, NULL, WS_VISIBLE | WS_CHILD, NULL, IDC_MODERN_CLOCK);
        m_ModernClock.SetClockImage(IDB_MODERN_BKG);
        m_ModernClock.SetHourMinSecImage(IDB_MODERN_HOUR, IDB_MODERN_MIN, IDB_MODERN_SEC);
        m_ModernClock.SetBackBrushType(CBrushHelper::GET_BY_WM_ERASEBKGND);
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
        return TRUE;
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

    LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        if (m_FlowerClock.m_hWnd) {
            CRect rcFlower;
            m_FlowerClock.GetClientRect(&rcFlower);
            rcFlower.MoveToX(150);
            m_FlowerClock.MoveWindow(rcFlower);
        }

        return 0;
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
};
