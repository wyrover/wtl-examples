// BarChartCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BarChartCtrl.h"
#include "BarChartCtrlDlg.h"

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
// CBarChartCtrlDlg dialog

CBarChartCtrlDlg::CBarChartCtrlDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CBarChartCtrlDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CBarChartCtrlDlg)
    m_bShowGrid = FALSE;
    m_bShowText = FALSE;
    m_bShowLabel = FALSE;
    m_bScale = FALSE;
    m_nRemIndex = 0;
    m_szLabel = _T("");
    m_szValue = _T("");
    m_bShowTip = FALSE;
    m_nGridHor = 0;
    m_nGridVer = 0;
    //}}AFX_DATA_INIT
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBarChartCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CBarChartCtrlDlg)
    DDX_Check(pDX, IDC_SHOW_GRID, m_bShowGrid);
    DDX_Check(pDX, IDC_SHOW_BAR_TEXT, m_bShowText);
    DDX_Check(pDX, IDC_SHOW_LABELS, m_bShowLabel);
    DDX_Check(pDX, IDC_SCALE, m_bScale);
    DDX_Text(pDX, IDC_REM_INDEX, m_nRemIndex);
    DDX_Text(pDX, IDC_ADD_LABEL, m_szLabel);
    DDX_Text(pDX, IDC_ADD_VALUE, m_szValue);
    DDX_Check(pDX, IDC_SHOW_TOOLTIP, m_bShowTip);
    DDX_Text(pDX, IDC_GRID_HOR, m_nGridHor);
    DDX_Text(pDX, IDC_GRID_VER, m_nGridVer);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBarChartCtrlDlg, CDialog)
    //{{AFX_MSG_MAP(CBarChartCtrlDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_CREATE, OnCreate)
    ON_BN_CLICKED(IDC_RANDOM, OnRandom)
    ON_BN_CLICKED(IDC_SHOW_GRID, OnShowGrid)
    ON_BN_CLICKED(IDC_SHOW_BAR_TEXT, OnShowBarText)
    ON_BN_CLICKED(IDC_SHOW_LABELS, OnShowLabels)
    ON_BN_CLICKED(IDC_SCALE, OnScale)
    ON_WM_SIZE()
    ON_BN_CLICKED(IDC_VALUE, OnValue)
    ON_BN_CLICKED(IDC_PERCENT, OnPercent)
    ON_BN_CLICKED(IDC_CLEAR_ALL, OnClearAll)
    ON_BN_CLICKED(IDC_REMOVE_AT, OnRemoveAt)
    ON_BN_CLICKED(IDC_ADD_BAR, OnAddBar)
    ON_WM_CTLCOLOR()
    ON_BN_CLICKED(IDC_PRINT, OnPrint)
    ON_BN_CLICKED(IDC_SHOW_TOOLTIP, OnShowTooltip)
    ON_BN_CLICKED(IDC_READ_FROM_DATABASE, OnReadFromDatabase)
    ON_BN_CLICKED(IDC_SAVE, OnSave)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_GRID_VER, OnDeltaposSpinGridVer)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_GRID_HOR, OnDeltaposSpinGridHor)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBarChartCtrlDlg message handlers

void CBarChartCtrlDlg::OnOK()
{
//  CDialog::OnOK();
}

BOOL CBarChartCtrlDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
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

    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    // Need random colors
    srand((unsigned)time(NULL));
    m_brushBK.CreateSolidBrush(RGB(255, 255, 255));
    ((CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_GRID_HOR))->SetRange(1, 1000);
    ((CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_GRID_VER))->SetRange(1, 1000);
    ((CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_GRID_HOR))->SetPos(30);
    ((CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_GRID_VER))->SetPos(40);
    m_nGridHor = 30;
    m_nGridVer = 40;
    m_chart.SetGridLines(0, 0, TRUE);
    m_bScale = FALSE;
    m_bShowGrid = TRUE;
    m_bShowLabel = TRUE;
    m_bShowText = TRUE;
    m_bShowTip = TRUE;
    CheckRadioButton(IDC_VALUE, IDC_VALUE, IDC_VALUE);
    UpdateData(FALSE);
    return TRUE;
}

void CBarChartCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBarChartCtrlDlg::OnPaint()
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

HCURSOR CBarChartCtrlDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

void CBarChartCtrlDlg::OnCreate()
{
    CRect rcClient;
    GetClientRect(&rcClient);

    if (!m_chart.Create(CRect(110, 50,
                              rcClient.Width() - 10,
                              rcClient.Height() - 50), this, 1050)) {
        if (!m_chart.GetSafeHwnd()) {
            AfxMessageBox(TEXT("Unable to create the chart control"));
            return;
        }

        m_chart.Reset();
        m_chart.SetAutoScale(FALSE);
    }

    m_chart.SetTitle("A test chart, displaying some dummy data...");
    m_chart.SetBKColor(RGB(255, 255, 240));
    m_chart.ShowTooltip(TRUE);
    m_chart.AddBar(1600.356, "Jan", RGB(255, 255, 0));
    m_chart.AddBar(2841.5468, "Feb", RGB(255, 0, 0));
    m_chart.AddBar(1045.3258, "Mar", RGB(100, 100, 200));
    m_chart.AddBar(1502.215, "Apr", RGB(0, 255, 0));
    m_chart.AddBar(1467, "MAY", RGB(255, 255, 255));
    m_chart.AddBar(1678.354, "JUN", RGB(200, 255, 255));
    m_chart.AddBar(1785.689, "JUL", RGB(255, 240, 40));
    m_chart.AddBar(1283.099, "AUG", RGB(255, 60, 130));
    m_chart.AddBar(1554.879, "SEP", RGB(255, 255, 200));
    m_chart.AddBar(1400.10, "OCT", RGB(130, 235, 250));
    m_chart.AddBar(1600.556, "NOV", RGB(100, 150, 200));
    m_chart.AddBar(1900.3546, "DES", RGB(150, 240, 80), TRUE);
}

void CBarChartCtrlDlg::OnRandom()
{
    CRect rcClient;
    GetClientRect(&rcClient);

    if (!m_chart.GetSafeHwnd()) {
        m_chart.Create(CRect(110, 50,
                             rcClient.Width() - 10,
                             rcClient.Height() - 50), this, 0);
    } else {
        m_chart.Reset();
    }

    m_chart.SetTitle("The same control using some random data and colors...");
    m_chart.SetBKColor(RGB(240, 240, 240));

    for (int i = 0; i < 15; i++) {
        m_chart.AddBar(rand() % 500, "Rand", RGB(rand() % 255, rand() % 255, rand() % 255), FALSE);
    }

    m_chart.Refresh();
}

void CBarChartCtrlDlg::OnShowGrid()
{
    UpdateData(TRUE);
    m_chart.ShowGrid(m_bShowGrid, TRUE);
}

void CBarChartCtrlDlg::OnShowBarText()
{
    UpdateData(TRUE);
    m_chart.ShowBarText(1, m_bShowText, TRUE);
}

void CBarChartCtrlDlg::OnShowLabels()
{
    UpdateData(TRUE);
    m_chart.ShowLabel(m_bShowLabel, TRUE);
}

void CBarChartCtrlDlg::OnShowTooltip()
{
    UpdateData(TRUE);
    m_chart.ShowTooltip(m_bShowTip);
}

void CBarChartCtrlDlg::OnScale()
{
    UpdateData(TRUE);
    CRect rcClient;
    GetClientRect(&rcClient);
    m_chart.SetAutoScale(m_bScale);
    m_chart.SetWindowPos(0, 0, 0, rcClient.Width() - 120, rcClient.Height() - 60, SWP_NOMOVE);
    m_chart.Refresh();
    Invalidate();
}

void CBarChartCtrlDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    if (m_chart.GetSafeHwnd()) {
        m_chart.SetWindowPos(0, 0, 0, cx - 120, cy - 60, SWP_NOMOVE);
    }
}

void CBarChartCtrlDlg::OnValue()
{
    m_chart.ShowBarText(1, m_bShowText);
    m_chart.Refresh();
}

void CBarChartCtrlDlg::OnPercent()
{
    m_chart.ShowBarText(0, m_bShowText);
    m_chart.Refresh();
}

void CBarChartCtrlDlg::OnClearAll()
{
    m_chart.RemoveAll();
}

void CBarChartCtrlDlg::OnRemoveAt()
{
    UpdateData(TRUE);
    m_chart.RemoveAt(m_nRemIndex);
}

void CBarChartCtrlDlg::OnAddBar()
{
    UpdateData(TRUE);
    m_chart.AddBar(atof(m_szValue), m_szLabel,
                   RGB(rand() % 255, rand() % 255, rand() % 255), TRUE);
}

HBRUSH CBarChartCtrlDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
    return hbr;
//  if (nCtlColor==CTLCOLOR_DLG) {
    pDC->SetBkColor(RGB(255, 255, 255));
    pDC->SetBkMode(TRANSPARENT);
    return m_brushBK;
//  }
}

void CBarChartCtrlDlg::OnCancel()
{
    m_brushBK.DeleteObject();
    CDialog::OnCancel();
}

void CBarChartCtrlDlg::OnPrint()
{
    if (m_chart.GetSafeHwnd()) {
        m_chart.Print();
    }
}

void CBarChartCtrlDlg::OnReadFromDatabase()
{
    // First create or reset the chart
    CRect rcClient;
    GetClientRect(&rcClient);

    if (!m_chart.GetSafeHwnd()) {
        m_chart.Create(CRect(110, 50,
                             rcClient.Width() - 10,
                             rcClient.Height() - 50), this, 0);
    } else {
        m_chart.Reset();
    }

    m_chart.SetTitle("These data are result records of a call to a StoredProcedure");
    m_chart.SetBKColor(RGB(255, 255, 240));

    // CAUTION : JUST one of the ReadFromDatabase must be used, or there will be
    //           an assertion error.

    // Comment one of the following calls

    // A call that shows how to create a chart using a table

    /*
    if you are un-commenting this, please comment the other first.
    m_chart.ReadFromDatabase("CHTst", "TableConnectionTest", "", "Month", "SaleRate",
        RGB(0, 0, 0) , "Admin", "hamed");
    */

    // A call that shows how to execute a stored procedure.
    // REMEMBER Stored procedure must return at least 2 parameteres.
    // First parameter MUST be a LABEL of type Text or char with maximum length of 50
    // and second a double value
    if (!m_chart.ReadFromDatabase("CHTst", "SpChartGetSale", "1, 12",
                                  RGB(0, 0, 0), "Admin", "hamed")) {
        AfxMessageBox(m_chart.GetLastDatabaseErrMessage());
    };
}

void CBarChartCtrlDlg::OnSave()
{
    if (!m_chart.SaveToFile()) {
        AfxMessageBox(m_chart.GetLastErrorMessage());
    };
}

void CBarChartCtrlDlg::OnDeltaposSpinGridVer(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    int nCurrent = pNMUpDown->iPos;

    if (pNMUpDown->iDelta > 0) {
        nCurrent++;
    } else {
        if (nCurrent > 1) nCurrent --;
    }

    m_chart.SetGridLines(0, nCurrent);
    m_chart.Refresh();
    *pResult = 0;
}

void CBarChartCtrlDlg::OnDeltaposSpinGridHor(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    int nCurrent = pNMUpDown->iPos;

    if (pNMUpDown->iDelta > 0) {
        nCurrent++;
    } else {
        if (nCurrent > 1) nCurrent --;
    }

    m_chart.SetGridLines(nCurrent, 0);
    m_chart.Refresh();
    *pResult = 0;
}
