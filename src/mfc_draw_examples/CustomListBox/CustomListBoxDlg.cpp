// CustomListBoxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CustomListBox.h"
#include "CustomListBoxDlg.h"

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
    CC_Button   m_OK;
    //}}AFX_DATA

// Implementation
protected:
    // GUI eye candy
    CBrush*         m_pbBackground;

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnDestroy();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
    m_pbBackground = new CBrush(DLG_COLOR_BACKGROUND);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    DDX_Control(pDX, IDOK, m_OK);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
    ON_WM_CTLCOLOR()
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* /*pWnd*/, UINT /*nCtlColor*/)
{
    pDC->SetBkMode(TRANSPARENT);
    return (HBRUSH) * m_pbBackground;
}

void CAboutDlg::OnDestroy()
{
    CDialog::OnDestroy();
    delete m_pbBackground;
}

/////////////////////////////////////////////////////////////////////////////
// CCustomListBoxDlg dialog

CCustomListBoxDlg::CCustomListBoxDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CCustomListBoxDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CCustomListBoxDlg)
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_pbBackground = new CBrush(DLG_COLOR_BACKGROUND);
}

void CCustomListBoxDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CCustomListBoxDlg)
    DDX_Control(pDX, IDC_ST_ISSA, m_ST_Issa);
    DDX_Control(pDX, IDC_ST_GRASS, m_ST_Grass);
    DDX_Control(pDX, IDC_BT_TOOTLE, m_Tootle);
    DDX_Control(pDX, IDC_FR_GETSELECTED, m_FR_GetSeleted);
    DDX_Control(pDX, IDC_EF_S_GETSELECTED, m_EF_S_GetSelected);
    DDX_Control(pDX, IDC_EF_N_GETSELECTED, m_EF_N_GetSelected);
    DDX_Control(pDX, IDC_BT_GETSELECTED, m_BT_GetSelected);
    DDX_Control(pDX, IDC_EF_S_INSERT, m_EF_S_Insert);
    DDX_Control(pDX, IDC_EF_S_GET, m_EF_S_Get);
    DDX_Control(pDX, IDC_EF_S_CHANGE, m_EF_S_Change);
    DDX_Control(pDX, IDC_EF_S_ADD, m_EF_S_Add);
    DDX_Control(pDX, IDC_EF_N_REMOVE, m_EF_N_Remove);
    DDX_Control(pDX, IDC_EF_N_POPULATE, m_EF_N_Populate);
    DDX_Control(pDX, IDC_EF_N_INSERT, m_EF_N_Insert);
    DDX_Control(pDX, IDC_EF_N_GET, m_EF_N_Get);
    DDX_Control(pDX, IDC_EF_N_COLUMN_WIDTH, m_EF_N_ColumnWidth);
    DDX_Control(pDX, IDC_EF_N_CHANGE, m_EF_N_Change);
    DDX_Control(pDX, IDC_CB_TEXTCOLOR, m_CB_TextColor);
    DDX_Control(pDX, IDC_CB_INSERT, m_CB_Insert);
    DDX_Control(pDX, IDC_CB_CHANGE, m_CB_Change);
    DDX_Control(pDX, IDC_CB_ADD, m_CB_Add);
    DDX_Control(pDX, IDC_BT_ADD, m_BT_Add);
    DDX_Control(pDX, IDC_FR_BACKGROUND2, m_FR_Background2);
    DDX_Control(pDX, IDC_FR_BACKGROUND1, m_FR_Background1);
    DDX_Control(pDX, IDC_FR_ADD, m_FR_Add);
    DDX_Control(pDX, IDC_FR_TEXTCOLOR, m_FR_TextColor);
    DDX_Control(pDX, IDC_FR_SELECTION4, m_FR_Selection4);
    DDX_Control(pDX, IDC_FR_SELECTION3, m_FR_Selection3);
    DDX_Control(pDX, IDC_FR_SELECTION2, m_FR_Selection2);
    DDX_Control(pDX, IDC_FR_SELECTION1, m_FR_Selection1);
    DDX_Control(pDX, IDC_FR_SB4, m_FR_SB4);
    DDX_Control(pDX, IDC_FR_SB3, m_FR_SB3);
    DDX_Control(pDX, IDC_FR_SB2, m_FR_SB2);
    DDX_Control(pDX, IDC_FR_SB1, m_FR_SB1);
    DDX_Control(pDX, IDC_FR_INSERT, m_FR_Insert);
    DDX_Control(pDX, IDC_FR_GET, m_FR_Get);
    DDX_Control(pDX, IDC_FR_CHANGE, m_FR_Change);
    DDX_Control(pDX, IDC_FR_BORDER2, m_FR_Border2);
    DDX_Control(pDX, IDC_FR_BORDER1, m_FR_Border1);
    DDX_Control(pDX, IDC_BT_TEXTCOLOR, m_BT_TextColor);
    DDX_Control(pDX, IDC_BT_SELECTION, m_BT_SelectionColors);
    DDX_Control(pDX, IDC_BT_SB, m_BT_ScrollBarColors);
    DDX_Control(pDX, IDC_BT_REMOVEALL, m_BT_RemoveAll);
    DDX_Control(pDX, IDC_BT_REMOVE, m_BT_Remove);
    DDX_Control(pDX, IDC_BT_POPULATE, m_BT_Populate);
    DDX_Control(pDX, IDC_BT_INSERT, m_BT_Insert);
    DDX_Control(pDX, IDC_BT_GET, m_BT_Get);
    DDX_Control(pDX, IDC_BT_COLUMN_WIDTH, m_BT_ColumnWidth);
    DDX_Control(pDX, IDC_BT_CHANGE, m_BT_Change);
    DDX_Control(pDX, IDC_BT_BORDER, m_BT_Border);
    DDX_Control(pDX, IDC_BT_BACKGROUND, m_BT_Background);
    DDX_Control(pDX, IDC_CUSTOM1, m_CWindListBox);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCustomListBoxDlg, CDialog)
    //{{AFX_MSG_MAP(CCustomListBoxDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_DESTROY()
    ON_WM_CTLCOLOR()
    ON_BN_CLICKED(IDC_BT_ADD, OnBtAdd)
    ON_BN_CLICKED(IDC_BT_BACKGROUND, OnBtBackground)
    ON_BN_CLICKED(IDC_BT_BORDER, OnBtBorder)
    ON_BN_CLICKED(IDC_BT_CHANGE, OnBtChange)
    ON_BN_CLICKED(IDC_BT_COLUMN_WIDTH, OnBtColumnWidth)
    ON_BN_CLICKED(IDC_BT_GET, OnBtGet)
    ON_BN_CLICKED(IDC_BT_INSERT, OnBtInsert)
    ON_BN_CLICKED(IDC_BT_POPULATE, OnBtPopulate)
    ON_BN_CLICKED(IDC_BT_REMOVE, OnBtRemove)
    ON_BN_CLICKED(IDC_BT_REMOVEALL, OnBtRemoveall)
    ON_BN_CLICKED(IDC_BT_SB, OnBtSb)
    ON_BN_CLICKED(IDC_BT_SELECTION, OnBtSelection)
    ON_BN_CLICKED(IDC_BT_TEXTCOLOR, OnBtTextcolor)
    ON_BN_CLICKED(IDC_BT_GETSELECTED, OnBtGetselected)
    ON_BN_CLICKED(IDC_BT_TOOTLE, OnBtTootle)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomListBoxDlg message handlers

BOOL CCustomListBoxDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    // Add "About..." menu item to system menu.
    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);
    CMenu* pSysMenu = GetSystemMenu(FALSE);

    if (pSysMenu != NULL) {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);

        if (!strAboutMenu.IsEmpty()) {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    // Eye candy
    CFont fGrass;
    fGrass.CreatePointFont(70, _T("Arial Black"));
    m_ST_Grass.SetFont(&fGrass);
    fGrass.Detach();
    fGrass.CreatePointFont(70, _T("Arial Black"));
    m_ST_Issa.SetFont(&fGrass);
    fGrass.Detach();
    m_FR_Border1.SetColor(RGB(0, 77, 113));
    m_FR_Border2.SetColor(RGB(255, 255, 255));
    m_FR_Background1.SetColor(RGB(183, 235, 255));
    m_FR_Background2.SetColor(RGB(255, 255, 11));
    m_FR_TextColor.SetColor(RGB(0, 77, 113));
    m_FR_Selection1.SetColor(RGB(255, 255, 255));
    m_FR_Selection2.SetColor(RGB(70, 136, 136));
    m_FR_Selection3.SetColor(RGB(0, 0, 0));
    m_FR_Selection4.SetColor(RGB(128, 128, 128));
    m_FR_SB1.SetColor(RGB(0, 80, 80));
    m_FR_SB2.SetColor(RGB(223, 239, 255));
    m_FR_SB3.SetColor(RGB(0, 0, 0));
    m_FR_SB4.SetColor(RGB(128, 128, 128));
    // Listbox make sure to initialize it with these methods, default values are set on 'annoy'
    m_CWindListBox
    .SetBorderColor(m_FR_Border1.GetColor(), m_FR_Border2.GetColor())
    .SetBkColor(m_FR_Background1.GetColor(), m_FR_Background2.GetColor())
    .SetDefaultTextColor(m_FR_TextColor.GetColor())
    .SetSelectedColors(m_FR_Selection1.GetColor(), m_FR_Selection2.GetColor(),
                       m_FR_Selection3.GetColor(), m_FR_Selection4.GetColor())
    .SetSBColors(m_FR_SB1.GetColor(), m_FR_SB2.GetColor(), m_FR_SB3.GetColor(), m_FR_SB4.GetColor())
#if defined( _UNICODE )
    .SetTextFont(8, TRUE, FALSE, _T("Arial Unicode MS"))
#else
    .SetTextFont(8, TRUE, FALSE, _T("Verdana"))
#endif
    .SetColumnWidth(9);
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCustomListBoxDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    } else {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCustomListBoxDlg::OnPaint()
{
    if (IsIconic()) {
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
    } else {
        CDialog::OnPaint();
    }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCustomListBoxDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

HBRUSH CCustomListBoxDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    if (nCtlColor == CTLCOLOR_EDIT)
        return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
    else {
        pDC->SetBkMode(TRANSPARENT);
        return (HBRUSH) * m_pbBackground;
    }
}

void CCustomListBoxDlg::OnDestroy()
{
    CDialog::OnDestroy();
    delete m_pbBackground;
}

// ListBox Appearance ----------------------------------------------

void CCustomListBoxDlg::OnBtBorder()
{
    m_CWindListBox.SetBorderColor(m_FR_Border1.GetColor(), m_FR_Border2.GetColor());
}

void CCustomListBoxDlg::OnBtBackground()
{
    m_CWindListBox.SetBkColor(m_FR_Background1.GetColor(), m_FR_Background2.GetColor());
}

void CCustomListBoxDlg::OnBtTextcolor()
{
    if (m_CB_TextColor.GetCheck()) {
        srand((unsigned)time(NULL));

        for (int i = 0; i < m_CWindListBox.GetCount(); i++)
            m_CWindListBox.ChangeColorAt(i, RGB(rand() % 250, rand() % 250, rand() % 250));
    } else
        m_CWindListBox.SetDefaultTextColor(m_FR_TextColor.GetColor());
}

void CCustomListBoxDlg::OnBtSelection()
{
    m_CWindListBox.SetSelectedColors(m_FR_Selection1.GetColor(), m_FR_Selection2.GetColor(),
                                     m_FR_Selection3.GetColor(), m_FR_Selection4.GetColor());
}

void CCustomListBoxDlg::OnBtColumnWidth()
{
    CString csTemp;
    m_EF_N_ColumnWidth.GetWindowText(csTemp);

    if (csTemp.GetLength() > 0)
#if defined( _UNICODE )
        m_CWindListBox.SetColumnWidth(_wtoi(csTemp));

#else
        m_CWindListBox.SetColumnWidth(atoi(csTemp));
#endif
}

// Scrollbar -------------------------------------------------------

void CCustomListBoxDlg::OnBtSb()
{
    m_CWindListBox.SetSBColors(m_FR_SB1.GetColor(), m_FR_SB2.GetColor(), m_FR_SB3.GetColor(), m_FR_SB4.GetColor());
}

// Item Operations -------------------------------------------------

void CCustomListBoxDlg::OnBtPopulate()
{
    CString csTemp;
    m_EF_N_Populate.GetWindowText(csTemp);
#if defined( _UNICODE )
    int     iItems = _wtoi(csTemp);
#else
    int     iItems = atoi(csTemp);
#endif
    srand((unsigned)time(NULL));

    for (int i = 0; i < iItems; i++) {
        csTemp.Format(_T("Item %c%c"), 65 + rand() % 26, 65 + rand() % 26);

        if (rand() % 4 == 0)
            m_CWindListBox.AddStringWithColor(csTemp, RGB(rand() % 250, rand() % 250, rand() % 250));
        else
            m_CWindListBox.AddString(csTemp);
    }
}

void CCustomListBoxDlg::OnBtAdd()
{
    CString csLabel;
    m_EF_S_Add.GetWindowText(csLabel);

    if (csLabel.GetLength() > 0) {
        if (m_CB_Add.GetCheck())
            m_CWindListBox.AddStringWithColor(csLabel, m_FR_Add.GetColor());
        else
            m_CWindListBox.AddString(csLabel);
    }
}

void CCustomListBoxDlg::OnBtInsert()
{
    CString csLabel, csTemp;
    m_EF_N_Insert.GetWindowText(csTemp);
    m_EF_S_Insert.GetWindowText(csLabel);

    if (csLabel.GetLength() > 0 && csTemp.GetLength() > 0) {
        if (m_CB_Insert.GetCheck())
#if defined( _UNICODE )
            m_CWindListBox.InsertStringWithColor(_wtoi(csTemp), csLabel, m_FR_Insert.GetColor());

#else
            m_CWindListBox.InsertStringWithColor(atoi(csTemp), csLabel, m_FR_Insert.GetColor());
#endif
        else
#if defined( _UNICODE )
            m_CWindListBox.InsertString(_wtoi(csTemp), csLabel);

#else
            m_CWindListBox.InsertString(atoi(csTemp), csLabel);
#endif
    }
}

void CCustomListBoxDlg::OnBtChange()
{
    CString csLabel, csTemp;
    m_EF_N_Change.GetWindowText(csTemp);
    m_EF_S_Change.GetWindowText(csLabel);

    if (csTemp.GetLength() > 0) {
        if (csLabel.GetLength() > 0) {
            if (m_CB_Change.GetCheck())
#if defined( _UNICODE )
                m_CWindListBox.ChangeStringAndColorAt(_wtoi(csTemp), csLabel, m_FR_Change.GetColor());

#else
                m_CWindListBox.ChangeStringAndColorAt(atoi(csTemp), csLabel, m_FR_Change.GetColor());
#endif
            else
#if defined( _UNICODE )
                m_CWindListBox.ChangeStringAt(_wtoi(csTemp), csLabel);

#else
                m_CWindListBox.ChangeStringAt(atoi(csTemp), csLabel);
#endif
        } else
#if defined( _UNICODE )
            m_CWindListBox.ChangeColorAt(_wtoi(csTemp), m_FR_Change.GetColor());

#else
            m_CWindListBox.ChangeColorAt(atoi(csTemp), m_FR_Change.GetColor());
#endif
    }
}

void CCustomListBoxDlg::OnBtGet()
{
    CString csTemp;
    m_EF_N_Get.GetWindowText(csTemp);

    if (csTemp.GetLength() > 0) {
#if defined( _UNICODE )
        m_EF_S_Get.SetWindowText(m_CWindListBox.GetStringAt(_wtoi(csTemp)));
        m_FR_Get.SetColor(m_CWindListBox.GetColorAt(_wtoi(csTemp)));
#else
        m_EF_S_Get.SetWindowText(m_CWindListBox.GetStringAt(atoi(csTemp)));
        m_FR_Get.SetColor(m_CWindListBox.GetColorAt(atoi(csTemp)));
#endif
    }
}

void CCustomListBoxDlg::OnBtGetselected()
{
    int iSelected = m_CWindListBox.GetSelectedItem();

    if (iSelected == -1) {
        m_EF_N_GetSelected.SetWindowText(_T(""));
        m_EF_S_GetSelected.SetWindowText(_T("Nothing selected!!"));
        m_FR_GetSeleted.SetColor(DLG_COLOR_BACKGROUND);
    } else {
        CString csTemp;
        csTemp.Format(_T("%d"), iSelected);
        m_EF_N_GetSelected.SetWindowText(csTemp);
        m_EF_S_GetSelected.SetWindowText(m_CWindListBox.GetStringAt(iSelected));
        m_FR_GetSeleted.SetColor(m_CWindListBox.GetColorAt(iSelected));
    }
}

void CCustomListBoxDlg::OnBtRemove()
{
    CString csTemp;
    m_EF_N_Remove.GetWindowText(csTemp);

    if (csTemp.GetLength() > 0)
#if defined( _UNICODE )
        m_CWindListBox.RemoveAt(_wtoi(csTemp));

#else
        m_CWindListBox.RemoveAt(atoi(csTemp));
#endif
}

void CCustomListBoxDlg::OnBtRemoveall()
{
    m_CWindListBox.RemoveAll();
}

void CCustomListBoxDlg::OnBtTootle()
{
    CDialog::OnOK();
}


