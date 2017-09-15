// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "CustomButton.h"

class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
		public CMessageFilter, public CIdleHandler
{
private:
	CCustomButton	m_BtnBlue;
	CCustomButton	m_BtnCheck;
	CCustomButton	m_BtnFont;

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
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

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

		CRect rc(0, 0, 124, 63);
		m_BtnBlue.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE, 0, IDC_BLUE_BUTTON);
		m_BtnBlue.SetThemeParent(m_hWnd);
		m_BtnBlue.LoadBitmap(IDB_BLUE_BTN, 3);
		m_BtnBlue.SetImages(0, 2, 1, 2);

		rc.SetRect(0, 0, 193, 59);
		m_BtnCheck.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE, 0, IDC_CHECK);
		m_BtnCheck.SetThemeParent(m_hWnd);
		m_BtnCheck.LoadBitmap(IDB_CHECK, 3);
		m_BtnCheck.SetImages(0, 2, 1, 2);
		m_BtnCheck.EnableCheckStyle();

		rc.SetRect(0, 0, 124, 63);
		m_BtnFont.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE, 0, IDC_FONT_BUTTON);
		m_BtnFont.SetThemeParent(m_hWnd);
		m_BtnFont.LoadBitmap(IDB_FONT_BUTTON, 3);
		m_BtnFont.SetImages(0, 2, 1, 2);
		m_BtnFont.SetWindowText(_T("自定义文字"));

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

	LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		return 1;
	}

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// wParam not NULL means some sub window want get its background brush.
		if (wParam != NULL)
		{
			Graphics g( (HDC)wParam );
			DoPaint(g);
		}
		else
		{
			CPaintDC dc(m_hWnd);
			Graphics g(dc.m_hDC);
			DoPaint(g);
		}
		return 0;
	}

	LRESULT OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if (m_BtnBlue.m_hWnd)
		{
			CRect rc1;
			m_BtnBlue.GetClientRect(&rc1);
			rc1.MoveToXY(30, 30);
			m_BtnBlue.MoveWindow(rc1);

			CRect rc2;
			m_BtnCheck.GetClientRect(&rc2);
			rc2.MoveToY(rc1.bottom + 20);
			rc2.MoveToX(rc1.left);
			m_BtnCheck.MoveWindow(rc2);

			CRect rc3;
			m_BtnFont.GetClientRect(&rc3);
			rc3.MoveToX(rc2.left);
			rc3.MoveToY(rc2.bottom + 20);
			m_BtnFont.MoveWindow(rc3);
		}
		return 0;
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
