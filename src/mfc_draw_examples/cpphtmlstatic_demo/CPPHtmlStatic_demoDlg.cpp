// CPPHtmlStatic_demoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CPPHtmlStatic_demo.h"
#include "CPPHtmlStatic_demoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPHtmlStatic_demoDlg dialog

CPPHtmlStatic_demoDlg::CPPHtmlStatic_demoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPPHtmlStatic_demoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPPHtmlStatic_demoDlg)
	m_type_static = 0;
	m_comments = _T("");
	m_mask = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPPHtmlStatic_demoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPHtmlStatic_demoDlg)
	DDX_Control(pDX, IDC_STATIC_INFO, m_info);
	DDX_Control(pDX, IDC_BUTTON1, m_mask_color);
	DDX_Control(pDX, IDC_CHECK2, m_mask_ctrl);
	DDX_Control(pDX, IDC_TEXT, m_comments_ctrl);
	DDX_Control(pDX, IDC_URL_LABEL, m_url_label);
	DDX_Control(pDX, IDC_STATIC_DEMO, m_static);
	DDX_Control(pDX, IDC_LINK_LABEL, m_link_label);
	DDX_Control(pDX, IDC_ID_LABEL, m_id_label);
	DDX_Control(pDX, IDC_FRAMERATE_LABEL, m_framerate_label);
	DDX_Control(pDX, IDC_EDIT_URL, m_url_ctrl);
	DDX_Control(pDX, IDC_EDIT_LINK, m_link_ctrl);
	DDX_Control(pDX, IDC_EDIT_FRAMERATE, m_framerate_ctrl);
	DDX_Control(pDX, IDC_COMBO_ID, m_idres_ctrl);
	DDX_Radio(pDX, IDC_RADIO1, m_type_static);
	DDX_Text(pDX, IDC_TEXT, m_comments);
	DDX_Check(pDX, IDC_CHECK2, m_mask);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPPHtmlStatic_demoDlg, CDialog)
	//{{AFX_MSG_MAP(CPPHtmlStatic_demoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, OnChangeTypeStatic)
	ON_BN_CLICKED(IDC_APPLY_BTN, OnApplyBtn)
	ON_BN_CLICKED(IDC_CHECK2, OnApplyBtn)
	ON_BN_CLICKED(IDC_RADIO2, OnChangeTypeStatic)
	ON_BN_CLICKED(IDC_RADIO3, OnChangeTypeStatic)
	ON_BN_CLICKED(IDC_RADIO4, OnChangeTypeStatic)
	ON_BN_CLICKED(IDC_RADIO5, OnChangeTypeStatic)
	ON_BN_CLICKED(IDC_RADIO6, OnChangeTypeStatic)
	ON_BN_CLICKED(IDC_RADIO7, OnChangeTypeStatic)
	ON_CBN_SELENDOK(IDC_COMBO_ID, OnApplyBtn)
	//}}AFX_MSG_MAP
	ON_MESSAGE (CPN_SELENDOK, OnChangeMaskColor)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPHtmlStatic_demoDlg message handlers

BOOL CPPHtmlStatic_demoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Initialize property pages
	CRect rcSheet;
	m_sheet.EnableStackedTabs(TRUE);
	m_sheet.AddPage(&m_page_colors);
	m_sheet.AddPage(&m_page_border);
	m_sheet.AddPage(&m_page_align);
	m_sheet.AddPage(&m_page_images);
	m_sheet.AddPage(&m_page_misc);
	m_sheet.AddPage(&m_page_styles);
	m_sheet.Create(this, WS_CHILD | WS_VISIBLE | WS_TABSTOP);//, WS_EX_CONTROLPARENT);
	m_sheet.ModifyStyleEx (0, WS_EX_CONTROLPARENT);
	GetDlgItem(IDC_STATIC1)->GetWindowRect( &rcSheet );
	ScreenToClient( &rcSheet );
	m_sheet.SetWindowPos( NULL, rcSheet.left-7, rcSheet.top-7, 0, 0, 
		SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
	
	m_link_ctrl.SetWindowText(_T("Go to Codeproject"));
	m_url_ctrl.SetWindowText(_T("http://www.codeproject.com"));

	m_crMaskColor = 0xFF000000;
	m_mask_color.SetColour(m_crMaskColor);
	m_mask_color.SetDefaultText(_T("Default"));

	m_static.SetMargins(5, 5);
	m_static.GetHtmlDrawer()->SetImageList(IDB_SMILES, 16, 16, 22);

	// TODO: Add extra initialization here
	UpdateData(FALSE);
	OnChangeTypeStatic();

	m_info.SetBkColor(::GetSysColor(COLOR_INFOBK));
	m_info.SetTextColor(::GetSysColor(COLOR_INFOTEXT));
	m_info.SetRoundRectRgn(20, 20);
	m_info.SetMargins(5, 5);
	m_info.SetBorder(::GetSysColor(COLOR_INFOTEXT));

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPPHtmlStatic_demoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPPHtmlStatic_demoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPPHtmlStatic_demoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPPHtmlStatic_demoDlg::OnChangeTypeStatic() 
{
	UpdateData();
	m_comments_ctrl.SetReadOnly(m_type_static != 6);
	CString str;
	switch (m_type_static)
	{
	case TYPE_ICON:
		//Icon
		m_id_label.ShowWindow(TRUE);
		m_idres_ctrl.ShowWindow(TRUE);
		m_framerate_label.ShowWindow(FALSE);
		m_framerate_ctrl.ShowWindow(FALSE);
		m_url_label.ShowWindow(FALSE);
		m_url_ctrl.ShowWindow(FALSE);
		m_link_label.ShowWindow(FALSE);
		m_link_ctrl.ShowWindow(FALSE);
		m_mask_ctrl.ShowWindow(FALSE);
		m_mask_color.ShowWindow(FALSE);
		m_idres_ctrl.ResetContent();
		str.Format(_T("%d - Frog"), IDI_FROG);
		m_idres_ctrl.AddString(str);
		str.Format(_T("%d - Help"), IDI_HELP);
		m_idres_ctrl.AddString(str);
		str.Format(_T("%d - Mail"), IDI_MAIL);
		m_idres_ctrl.AddString(str);
		str.Format(_T("%d - Stop"), IDI_STOP);
		m_idres_ctrl.AddString(str);
		m_idres_ctrl.SetCurSel(0);
		break;
	case TYPE_BITMAP:
		//Bitmap
		m_id_label.ShowWindow(TRUE);
		m_idres_ctrl.ShowWindow(TRUE);
		m_framerate_label.ShowWindow(FALSE);
		m_framerate_ctrl.ShowWindow(FALSE);
		m_url_label.ShowWindow(FALSE);
		m_url_ctrl.ShowWindow(FALSE);
		m_link_label.ShowWindow(FALSE);
		m_link_ctrl.ShowWindow(FALSE);
		m_mask_ctrl.ShowWindow(TRUE);
		m_mask_color.ShowWindow(TRUE);
		m_idres_ctrl.ResetContent();
		str.Format(_T("%d - Codeproject"), IDB_CODEPROJECT);
		m_idres_ctrl.AddString(str);
		str.Format(_T("%d - Dragon"), IDB_DRAGON);
		m_idres_ctrl.AddString(str);
		m_idres_ctrl.SetCurSel(0);
		break;
	case TYPE_IMAGELIST:
		//Image List
		m_id_label.ShowWindow(TRUE);
		m_idres_ctrl.ShowWindow(TRUE);
		m_framerate_label.SetWindowText(_T("Index :"));
		m_framerate_label.ShowWindow(TRUE);
		m_framerate_ctrl.ShowWindow(TRUE);
		m_url_label.ShowWindow(FALSE);
		m_url_ctrl.ShowWindow(FALSE);
		m_link_label.ShowWindow(FALSE);
		m_link_ctrl.ShowWindow(FALSE);
		m_mask_ctrl.ShowWindow(TRUE);
		m_mask_color.ShowWindow(TRUE);
		m_idres_ctrl.ResetContent();
		str.Format(_T("%d - Smiles"), IDB_SMILES);
		m_idres_ctrl.AddString(str);
		m_idres_ctrl.SetCurSel(0);
		m_framerate_ctrl.SetWindowText(_T("0"));
		break;
	case TYPE_ANIMATION:
		//Animation
		m_id_label.ShowWindow(TRUE);
		m_idres_ctrl.ShowWindow(TRUE);
		m_framerate_label.SetWindowText(_T("FrameRate :"));
		m_framerate_label.ShowWindow(TRUE);
		m_framerate_ctrl.ShowWindow(TRUE);
		m_url_label.ShowWindow(FALSE);
		m_url_ctrl.ShowWindow(FALSE);
		m_link_label.ShowWindow(FALSE);
		m_link_ctrl.ShowWindow(FALSE);
		m_mask_ctrl.ShowWindow(TRUE);
		m_mask_color.ShowWindow(TRUE);
		m_idres_ctrl.ResetContent();
		str.Format(_T("%d - Globe"), IDB_GLOBE);
		m_idres_ctrl.AddString(str);
		m_idres_ctrl.SetCurSel(0);
		m_framerate_ctrl.SetWindowText(_T("200"));
		break;
	case TYPE_HYPERLINK:
		//Hyperlink
		m_id_label.ShowWindow(FALSE);
		m_idres_ctrl.ShowWindow(FALSE);
		m_framerate_label.ShowWindow(FALSE);
		m_framerate_ctrl.ShowWindow(FALSE);
		m_url_label.ShowWindow(TRUE);
		m_url_ctrl.ShowWindow(TRUE);
		m_link_label.ShowWindow(TRUE);
		m_link_ctrl.ShowWindow(TRUE);
		m_mask_ctrl.ShowWindow(FALSE);
		m_mask_color.ShowWindow(FALSE);
		break;
	case TYPE_TEXT:
		//Text
		m_id_label.ShowWindow(TRUE);
		m_idres_ctrl.ShowWindow(TRUE);
		m_framerate_label.ShowWindow(FALSE);
		m_framerate_ctrl.ShowWindow(FALSE);
		m_url_label.ShowWindow(FALSE);
		m_url_ctrl.ShowWindow(FALSE);
		m_link_label.ShowWindow(FALSE);
		m_link_ctrl.ShowWindow(FALSE);
		m_mask_ctrl.ShowWindow(FALSE);
		m_mask_color.ShowWindow(FALSE);
		m_idres_ctrl.ResetContent();
		str.Format(_T("%d - About"), IDS_ABOUTBOX);
		m_idres_ctrl.AddString(str);
		m_idres_ctrl.SetCurSel(0);
		break;
	case TYPE_CUSTOMTEXT:
		//Custom Text
		m_id_label.ShowWindow(FALSE);
		m_idres_ctrl.ShowWindow(FALSE);
		m_framerate_label.ShowWindow(FALSE);
		m_framerate_ctrl.ShowWindow(FALSE);
		m_url_label.ShowWindow(FALSE);
		m_url_ctrl.ShowWindow(FALSE);
		m_link_label.ShowWindow(FALSE);
		m_link_ctrl.ShowWindow(FALSE);
		m_mask_ctrl.ShowWindow(FALSE);
		m_mask_color.ShowWindow(FALSE);
		break;
	} //switch

	OnApplyBtn();
}

void CPPHtmlStatic_demoDlg::OnApplyBtn() 
{
	UpdateData();
	m_mask_color.EnableWindow(m_mask);
	if (TYPE_ANIMATION != m_type_static)
		m_static.SetFrameRate(0);
	CString str;
	UINT nID = 0;
	if ((m_type_static != TYPE_CUSTOMTEXT) && (m_type_static != TYPE_HYPERLINK))
	{
		m_idres_ctrl.GetWindowText(str);
		nID = _ttoi(str);
	} //if
	UINT nIndex = 0;
	if ((m_type_static == TYPE_IMAGELIST) || (m_type_static == TYPE_ANIMATION))
	{
		m_framerate_ctrl.GetWindowText(str);
		nIndex = _ttoi(str);
	} //if

	switch (m_type_static)
	{
	case TYPE_ICON:
		//Icon
		str.Format(_T("<font color=red>SetIcon(nID)</font><br><hr color=blue width=280><br><span class=cpp-comment>For example:<br><t>SetIcon(%d)</span>"), nID);
		SetInfoText(str);
		m_static.SetIcon(nID);
		break;
	case TYPE_BITMAP:
		//Bitmap
		if (m_mask)
		{
			if (m_crMaskColor > 0xFFFFFF)
			{
				str.Format(_T("<font color=red>SetBitmap(nID)</font><br><hr color=blue width=280><br><span class=cpp-comment>For example:<br><t>SetBitmap(%d)</span>"), nID);
				SetInfoText(str);
				m_static.SetBitmap(nID);
			}
			else
			{
				str.Format(_T("<font color=red>SetBitmap(nID, crMaskColor)</font><br><hr color=blue width=280><br><span class=cpp-comment>For example:<br><t>SetBitmap(%d, 0x%06X)</span>"), nID, m_crMaskColor);
				SetInfoText(str);
				m_static.SetBitmap(nID, m_crMaskColor);
			}
		}
		else
		{
			str.Format(_T("<font color=red>SetBitmap(nID, -1)</font><br><hr color=blue width=280><br><span class=cpp-comment>For example:<br><t>SetBitmap(%d, -1)</span>"), nID);
			SetInfoText(str);
			m_static.SetBitmap(nID, -1);
		}
		break;
	case TYPE_IMAGELIST:
		//Image List
		if (m_mask)
		{
			if (m_crMaskColor > 0xFFFFFF)
			{
				str.Format(_T("<font color=red>SetImageList(nID, nIndex, szSize)</font><br><hr color=blue width=280><br><span class=cpp-comment>For example:<br><t>SetImageList(%d, %d)</span>"), nID, nIndex);
				SetInfoText(str);
				m_static.SetImageList(nID, nIndex);
			}
			else
			{
				str.Format(_T("<font color=red>SetImageList(nID, nIndex, szSize, crMaskColor)</font><br><hr color=blue width=280><br><span class=cpp-comment>For example:<br><t>SetImageList(%d, %d, NULL, 0x%06X)</span>"), nID, nIndex, m_crMaskColor);
				SetInfoText(str);
				m_static.SetImageList(nID, nIndex, NULL, m_crMaskColor);
			}
		}
		else
		{
			str.Format(_T("<font color=red>SetImageList(nID, nIndex, szSize, -1)</font><br><hr color=blue width=280><br><span class=cpp-comment>For example:<br><t>SetImageList(%d, %d, NULL, -1)</span>"), nID, nIndex);
			SetInfoText(str);
			m_static.SetImageList(nID, nIndex, NULL, -1);
		}
		break;
	case TYPE_ANIMATION:
		//Animation
		if (m_mask)
		{
			if (m_crMaskColor > 0xFFFFFF)
			{
				str.Format(_T("<font color=red>SetAnimation(nID, szSize)<br>SetFrameRate(nFrameRate)</font><br><hr color=blue width=280><br><span class=cpp-comment>For example:<br><t>SetAnimation(%d)<br><t>SetFrameRate(%d)</span>"), nID, nIndex);
				SetInfoText(str);
				m_static.SetAnimation(nID);
			}
			else
			{
				str.Format(_T("<font color=red>SetAnimation(nID, szSize, crMaskColor)<br>SetFrameRate(nFrameRate)</font><br><hr color=blue width=280><br><span class=cpp-comment>For example:<br><t>SetAnimation(%d, NULL, 0x%06X)<br><t>SetFrameRate(%d)</span>"), nID, m_crMaskColor, nIndex);
				SetInfoText(str);
				m_static.SetAnimation(nID, NULL, m_crMaskColor);
			}
		}
		else
		{
			str.Format(_T("<font color=red>SetAnimation(nID, szSize, -1)<br>SetFrameRate(nFrameRate)</font><br><hr color=blue width=280><br><span class=cpp-comment>For example:<br><t>SetAnimation(%d, NULL, -1)<br><t>SetFrameRate(%d)</span>"), nID, nIndex);
			SetInfoText(str);
			m_static.SetAnimation(nID, NULL, -1);
		}
		m_static.SetFrameRate(nIndex);
		break;
	case TYPE_HYPERLINK:
		//Hyperlink
		{
			CString sCaption, sUrl;
			m_link_ctrl.GetWindowText(sCaption);
			m_url_ctrl.GetWindowText(sUrl);
			str.Format(_T("<font color=red>SetHyperlink(sCaption, sURL)</font><br><hr color=blue width=280><br><span class=cpp-comment>For example:<br><t>SetHyperlink(\"%s\", \"%s\")</span>"), sCaption, sUrl);
			SetInfoText(str);
			m_static.SetHyperlink(sCaption, sUrl);
		}
		break;
	case TYPE_TEXT:
		//Text
		str.Format(_T("<font color=red>SetWindowText(\"<<string idres=nID>\")</font><br><hr color=blue width=280><br><span class=cpp-comment>For example:<br><t>SetWindowText(\"<<string idres=%d>\")</span>"), nID);
		SetInfoText(str);
		str.Format(_T("<string idres=%d>"), nID);
		m_static.SetWindowText(str);
		break;
	case TYPE_CUSTOMTEXT:
		//Custom Text
		m_comments_ctrl.GetWindowText(str);
		m_static.SetWindowText(str);
		SetInfoText(_T("<font color=red>SetWindowText(sHtmlString)</font><br><hr color=blue width=280><br><span class=cpp-comment>For example:<br><t>SetWindowText(\"Example\")</span>"));
		break;
	} //switch
}

LONG CPPHtmlStatic_demoDlg::OnChangeMaskColor(UINT lParam /*= 0*/, LONG wParam /*= 0*/)
{
	m_crMaskColor = m_mask_color.GetColour();
	OnApplyBtn();
	return 0L;
}

void CPPHtmlStatic_demoDlg::SetInfoText(CString str)
{
	CString sInfo;
	//sInfo.Format(_T("<table><tr><td><icon idres=%d></td><td><font face=Verdana size=90%%>%s</font></td></tr></table>"), IDI_HELP, str);
	sInfo.Format(_T("<font face=Verdana size=90%%>%s</font>"), str);
	m_info.SetWindowText(sInfo);
}
