#include "stdafx.h"
#include "MainDlg.h"
#include "TestDlg.h"
#include "AboutDlg.h"

CMainDlg::CMainDlg()
{
    m_pMailAlert = NULL;
    m_pMailAlertStyle = NULL;
    m_pFirefoxAlert = NULL;
    m_pFirefoxAlertStyle = new CAlertStyleFirefox();
    m_pWinampAlertStyle = new CAlertStyleWinamp();
}

CMainDlg::~CMainDlg()
{
    delete m_pMailAlert;
    delete m_pFirefoxAlert;
    delete m_pWinampAlert;
    delete m_pMailAlertStyle;
    delete m_pFirefoxAlertStyle;
    delete m_pWinampAlertStyle;
}

BOOL CMainDlg::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
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
    // register object for message filtering and idle updates
    CMessageLoop* pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->AddMessageFilter(this);
    pLoop->AddIdleHandler(this);
    UIAddChildWindowContainer(m_hWnd);
    m_pMailAlert = new CMailAlert(this);
    m_pMailAlert->Create(m_hWnd);
    m_pFirefoxAlert = new CFirefoxAlert(this);
    m_pFirefoxAlert->Create(m_hWnd);
    m_pFirefoxAlert->SetAlertStyle(m_pFirefoxAlertStyle);
    m_pWinampAlert = new CWinampAlert(this);
    m_pWinampAlert->Create(m_hWnd);
    m_pWinampAlert->SetAlertStyle(m_pWinampAlertStyle);
    m_cbStyle = GetDlgItem(IDC_COMBO_STYLE);
    m_cbStyle.AddString(_T("Default"));
    m_cbStyle.AddString(_T("Office 2003"));
    m_cbStyle.SetCurSel(0);
    m_slAnimation = GetDlgItem(IDC_SLIDER_ANIM);
    m_slAnimation.SetRange(1, 5);
    m_slAnimation.SetTicFreq(1);
    m_slAnimation.SetPos(2);
    SetDlgItemInt(IDC_STATIC_ANIM_TIME, 1000, FALSE);
    m_slVisibility = GetDlgItem(IDC_SLIDER_VISIBILITY);
    m_slVisibility.SetRange(1, 10);
    m_slVisibility.SetTicFreq(1);
    m_slVisibility.SetPos(6);
    SetDlgItemInt(IDC_STATIC_VISIBILITY_TIME, 3000, FALSE);
    m_slOpacity = GetDlgItem(IDC_SLIDER_OPACITY);
    m_slOpacity.SetRange(1, 100);
    m_slOpacity.SetTicFreq(1);
    m_slOpacity.SetPos(80);
    SetDlgItemInt(IDC_STATIC_OPACITY, 80, FALSE);
    m_opaque_button = GetDlgItem(IDC_CHECK_FULLY_OPAQUE);
    m_opaque_button.SetCheck(BST_CHECKED);
    return TRUE;
}

LRESULT CMainDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    // unregister message filtering and idle updates
    CMessageLoop* pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->RemoveMessageFilter(this);
    pLoop->RemoveIdleHandler(this);
    return 0;
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    CloseDialog(wID);
    return 0;
}


void CMainDlg::CloseDialog(int nVal)
{
    DestroyWindow();
    ::PostQuitMessage(nVal);
}

LRESULT CMainDlg::OnBnClickedButtonShowMail(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    int sel = m_cbStyle.GetCurSel();
    delete m_pMailAlertStyle;

    switch (sel) {
    case 0:
        m_pMailAlertStyle = new CAlertStyleDefault();
        break;

    case 1:
        m_pMailAlertStyle = new CAlertStyleOffice2003();
        break;

    default:
        ATLASSERT(0);
        break;
    }

    m_pMailAlert->SetAlertStyle(m_pMailAlertStyle);
    m_pMailAlert->Show(
        m_slAnimation.GetPos() * 500,
        m_slVisibility.GetPos() * 500,
        (m_slOpacity.GetPos() * 255) / 100,
        m_opaque_button.GetCheck() == BST_CHECKED);
    return 0;
}

LRESULT CMainDlg::OnBnClickedButtonShowFirefox(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    m_pFirefoxAlert->Show(
        m_slAnimation.GetPos() * 500,
        m_slVisibility.GetPos() * 500,
        (m_slOpacity.GetPos() * 255) / 100,
        m_opaque_button.GetCheck() == BST_CHECKED);
    return 0;
}

LRESULT CMainDlg::OnBnClickedButtonShowWinamp(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    m_pWinampAlert->Show(
        m_slAnimation.GetPos() * 500,
        m_slVisibility.GetPos() * 500,
        (m_slOpacity.GetPos() * 255) / 100,
        m_opaque_button.GetCheck() == BST_CHECKED);
    return 0;
}

void CMainDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar pScrollBar)
{
    if (pScrollBar.m_hWnd == m_slAnimation.m_hWnd) {
        SetDlgItemInt(IDC_STATIC_ANIM_TIME, m_slAnimation.GetPos() * 500, FALSE);
    } else if (pScrollBar.m_hWnd == m_slVisibility.m_hWnd) {
        SetDlgItemInt(IDC_STATIC_VISIBILITY_TIME, m_slVisibility.GetPos() * 500, FALSE);
    } else if (pScrollBar.m_hWnd == m_slOpacity.m_hWnd) {
        SetDlgItemInt(IDC_STATIC_OPACITY, m_slOpacity.GetPos(), FALSE);
    }
}