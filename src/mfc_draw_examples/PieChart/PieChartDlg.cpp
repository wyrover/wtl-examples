// PieChartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PieChart.h"
#include "PieChartDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPieChartDlg dialog




CPieChartDlg::CPieChartDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CPieChartDlg::IDD, pParent)
    , m_Value(0)
    , m_Item(_T(""))
    , m_Label(_T(""))
    , m_LabelUpd(_T(""))
    , m_ValueUpd(0)
    , m_TitleStr(_T(""))
    , m_Height(0)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPieChartDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_VALUE, m_Value);
    DDX_Text(pDX, IDC_ITEM, m_Item);
    DDX_Text(pDX, IDC_LABEL, m_Label);
    DDX_Text(pDX, IDC_LBUPD, m_LabelUpd);
    DDX_Text(pDX, IDC_VALUPD, m_ValueUpd);
    DDX_Control(pDX, IDC_GRLIGHT, m_GrLight);
    DDX_Control(pDX, IDC_GRDARK, m_GrDark);
    DDX_Control(pDX, IDC_SLIDER1, m_SliderGrLight);
    DDX_Control(pDX, IDC_SLIDER2, m_SliderGrDark);
    DDX_Control(pDX, IDC_SLIDER3, m_SliderStAngle);
    DDX_Control(pDX, IDC_SLIDER4, m_SliderIncAngle);
    DDX_Control(pDX, IDC_COLOR, m_ClrPicker);
    DDX_Control(pDX, IDC_FONT, m_FntPicker);
    DDX_Control(pDX, IDC_TITLE, m_Title);
    DDX_Control(pDX, IDC_STYLE, m_Styles);
    DDX_Control(pDX, IDC_SORT, m_Sort);
    DDX_Text(pDX, IDC_TITLE, m_TitleStr);
    DDX_Text(pDX, IDC_HEIGHT, m_Height);
    DDX_Control(pDX, IDC_ITMSEPERATE, m_ItmSeperate);
    DDX_Control(pDX, IDC_ITMTRANSPARENT, m_ItmTransparent);
    DDX_Control(pDX, IDC_SEPERATE, m_Seperate);
    DDX_Control(pDX, IDC_TRANSPARENT, m_Transparent);
    DDX_Control(pDX, IDC_TRANSPARENT2, m_HorizontalPos);
}

BEGIN_MESSAGE_MAP(CPieChartDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(ID_COLORITEM, &CPieChartDlg::OnBnClickedColoritem)
    ON_BN_CLICKED(ID_COLORITEM2, &CPieChartDlg::OnBnClickedColoritem)
    ON_BN_CLICKED(ID_ADD, &CPieChartDlg::OnBnClickedAdd)
    ON_WM_SIZE()
    ON_BN_CLICKED(IDC_UPDLABEL, &CPieChartDlg::OnBnClickedUpdlabel)
    ON_BN_CLICKED(IDC_UPDVALUE, &CPieChartDlg::OnBnClickedUpdvalue)
    ON_BN_CLICKED(IDC_UPDCOLOR, &CPieChartDlg::OnBnClickedUpdcolor)
    ON_WM_HSCROLL()
    ON_BN_CLICKED(IDC_COLORSET, &CPieChartDlg::OnBnClickedColorset)
    ON_BN_CLICKED(IDC_FONTSET, &CPieChartDlg::OnBnClickedFontset)
    ON_BN_CLICKED(IDC_TITLESET, &CPieChartDlg::OnBnClickedTitleset)
    ON_BN_CLICKED(IDC_SAVE, &CPieChartDlg::OnBnClickedSave)
    ON_CBN_SELCHANGE(IDC_STYLE, &CPieChartDlg::OnCbnSelchangeStyle)
    ON_CBN_SELCHANGE(IDC_SORT, &CPieChartDlg::OnCbnSelchangeSort)
    ON_BN_CLICKED(ID_HEIGHTSET, &CPieChartDlg::OnBnClickedHeightset)
    ON_BN_CLICKED(IDC_REMOVE, &CPieChartDlg::OnBnClickedRemove)
    ON_CBN_SELCHANGE(IDC_GRDARK, &CPieChartDlg::OnCbnSelchangeGrdark)
    ON_CBN_SELCHANGE(IDC_GRLIGHT, &CPieChartDlg::OnCbnSelchangeGrlight)
END_MESSAGE_MAP()


// CPieChartDlg message handlers

BOOL CPieChartDlg::OnInitDialog()
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
    CRect rect;
    GetClientRect(rect);
    rect.left = 250;
    rect.top = 10;
    rect.bottom -= 250;
    rect.right -= 10;
    m_pieChart.Create(L"Pie Chart", rect, this, 1);
    m_GrLight.AddString(L"Background");
    m_GrLight.AddString(L"All Items");
    m_SliderGrLight.SetRange(0, 255);
    m_GrDark.AddString(L"Background");
    m_GrDark.AddString(L"All Items");
    m_SliderGrDark.SetRange(0, 255);
    m_SliderIncAngle.SetRange(0, 89);
    m_SliderStAngle.SetRange(0, 360);
    m_ClrPicker.AddString(L"Background");
    m_ClrPicker.AddString(L"Chart Text");
    m_ClrPicker.AddString(L"Label Box");
    m_ClrPicker.AddString(L"Highlight color");
    m_FntPicker.AddString(L"Label text");
    m_FntPicker.AddString(L"Chart title");
    m_Styles.AddString(L"3-D style");
    m_Styles.AddString(L"2-D style");
    m_Styles.AddString(L"Doughnut style");
    m_Sort.AddString(L"Clockwise");
    m_Sort.AddString(L"Anticlockwise");
    m_Sort.AddString(L"Added order");
    m_Seperate.SetRange(0, 100);
    m_Transparent.SetRange(0, 100);
    m_ItmSeperate.AddString(L"All Items");
    m_ItmTransparent.AddString(L"All Items");
    m_HorizontalPos.SetRange(0, 200);
    // TODO: Add extra initialization here
    m_pieChart.SetParentWindowColor(::GetSysColor(COLOR_3DFACE));
    AddTestItems();
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPieChartDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPieChartDlg::OnPaint()
{
    if (IsIconic()) {
        CPaintDC dc(this); // device context for painting
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
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
        CPaintDC dc(this);
        CRect rectClr(100, 100, 142, 120);
        dc.FillSolidRect(rectClr, m_ItemColor);
        rectClr.top += 145;
        rectClr.bottom += 145;
        dc.FillSolidRect(rectClr, m_ItemColor);
        CDialog::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPieChartDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void CPieChartDlg::OnBnClickedColoritem()
{
    CColorDialog dlg;

    if (dlg.DoModal() == IDOK) {
        m_ItemColor = dlg.GetColor();
        Invalidate();
    }
}

void CPieChartDlg::OnBnClickedAdd()
{
    UpdateData(TRUE);
    Color m_ItemClr;
    m_ItemClr.SetFromCOLORREF(m_ItemColor);

    if (m_pieChart.InsertItem(m_Item, m_Label, m_Value, m_ItemClr)) {
        m_GrLight.AddString(m_Item);
        m_GrDark.AddString(m_Item);
        m_ItmSeperate.AddString(m_Item);
        m_ItmTransparent.AddString(m_Item);
    }
}

void CPieChartDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);
    CRect rect;
    GetClientRect(rect);
    rect.left = 250;
    rect.top = 10;
    rect.bottom -= 250;
    rect.right -= 10;

    if (m_pieChart) {
        m_pieChart.MoveWindow(rect);
    }
}

void CPieChartDlg::OnBnClickedUpdlabel()
{
    UpdateData();
    PIECHARTITEM item = m_pieChart.GetSelectedElement();

    if (item)
        m_pieChart.UpdateItemLabel(item, m_LabelUpd);
}

void CPieChartDlg::OnBnClickedUpdvalue()
{
    UpdateData();
    PIECHARTITEM item = m_pieChart.GetSelectedElement();

    if (item)
        m_pieChart.UpdateItemValue(item, m_ValueUpd);
}

void CPieChartDlg::OnBnClickedUpdcolor()
{
    UpdateData();
    PIECHARTITEM item = m_pieChart.GetSelectedElement();
    Color itemClr;
    itemClr.SetFromCOLORREF(m_ItemColor);

    if (item)
        m_pieChart.UpdateItemColor(item, itemClr);
}

void CPieChartDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    if (pScrollBar == GetDlgItem(IDC_SLIDER1)) {
        CString sType;
        int iSelect = m_GrLight.GetCurSel();

        if (iSelect != -1)
            m_GrLight.GetLBText(iSelect, sType);

        int pos = m_SliderGrLight.GetPos();

        if (!sType.Compare(L"Background"))
            m_pieChart.SetBackGroundGradientLight((float)pos);
        else if (!sType.Compare(L"All Items"))
            m_pieChart.SetPieElementGradientLightAll((float)pos);
        else {
            PIECHARTITEM item = m_pieChart.GetPieChartItem(sType);

            if (item)
                m_pieChart.SetPieElementGradientLight(item, (float)pos);
        }
    }

    if (pScrollBar == GetDlgItem(IDC_SLIDER2)) {
        CString sType;
        int iSelect = m_GrDark.GetCurSel();

        if (iSelect != -1)
            m_GrDark.GetLBText(iSelect, sType);

        int pos = m_SliderGrDark.GetPos();

        if (!sType.Compare(L"Background"))
            m_pieChart.SetBackGroundGradientDark((float)pos);
        else if (!sType.Compare(L"All Items"))
            m_pieChart.SetPieElementGradientDarkAll((float)pos);
        else {
            PIECHARTITEM item = m_pieChart.GetPieChartItem(sType);

            if (item)
                m_pieChart.SetPieElementGradientDark(item, (float)pos);
        }
    }

    if (pScrollBar == GetDlgItem(IDC_TRANSPARENT)) {
        CString sType;
        int iSelect = m_ItmTransparent.GetCurSel();

        if (iSelect != -1)
            m_ItmTransparent.GetLBText(iSelect, sType);

        int pos = m_Transparent.GetPos();

        if (!sType.Compare(L"All Items"))
            m_pieChart.SetElementTransparencyAll((float)pos);
        else {
            PIECHARTITEM item = m_pieChart.GetPieChartItem(sType);

            if (item)
                m_pieChart.SetElementTransparency(item, (float)pos);
        }
    }

    if (pScrollBar == GetDlgItem(IDC_SEPERATE)) {
        CString sType;
        int iSelect = m_ItmSeperate.GetCurSel();

        if (iSelect != -1)
            m_ItmSeperate.GetLBText(iSelect, sType);

        int pos = m_Seperate.GetPos();

        if (!sType.Compare(L"All Items"))
            m_pieChart.SetDistanceIndexAll(pos);
        else {
            PIECHARTITEM item = m_pieChart.GetPieChartItem(sType);

            if (item)
                m_pieChart.SetDistanceIndex(item, pos);
        }
    }

    if (pScrollBar == GetDlgItem(IDC_TRANSPARENT2)) {
        int pos = m_HorizontalPos.GetPos();
        m_pieChart.SetHorizontalOffset(pos);
    }

    if (pScrollBar == GetDlgItem(IDC_SLIDER3)) {
        int Pos = m_SliderStAngle.GetPos();
        m_pieChart.SetStartAngle((float)Pos);
    }

    if (pScrollBar == GetDlgItem(IDC_SLIDER4)) {
        int Pos = m_SliderIncAngle.GetPos();
        m_pieChart.SetInclineAngle((float)Pos);
    }

    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CPieChartDlg::OnBnClickedColorset()
{
    UpdateData();
    CString sType;
    CColorDialog dlg;

    if (dlg.DoModal() == IDOK) {
        int iSelect = m_ClrPicker.GetCurSel();
        Color mClr;
        mClr.SetFromCOLORREF(dlg.GetColor());

        if (iSelect != -1)
            m_ClrPicker.GetLBText(iSelect, sType);

        if (!sType.Compare(L"Background"))
            m_pieChart.SetBackgrndColor(mClr);
        else if (!sType.Compare(L"Chart Text"))
            m_pieChart.SetLabelColor(mClr);
        else if (!sType.Compare(L"Label Box"))
            m_pieChart.SetLabelBoxColor(mClr);
        else if (!sType.Compare(L"Highlight color"))
            m_pieChart.SetItemHighlightColor(mClr);
    }
}

void CPieChartDlg::OnBnClickedFontset()
{
    UpdateData();
    CString sType;
    CFontDialog dlg;

    if (dlg.DoModal() == IDOK) {
        LOGFONT lf;
        dlg.GetCurrentFont(&lf);
        lf.lfHeight = dlg.GetSize();
        lf.lfStrikeOut = dlg.IsStrikeOut();
        lf.lfWeight = dlg.IsBold();
        lf.lfItalic = dlg.IsItalic();
        lf.lfUnderline = dlg.IsUnderline();
        int iSelect = m_FntPicker.GetCurSel();

        if (iSelect != -1)
            m_FntPicker.GetLBText(iSelect, sType);

        if (!sType.Compare(L"Chart title"))
            m_pieChart.SetTitleFont(lf);
        else if (!sType.Compare(L"Label text"))
            m_pieChart.SetLabelFont(lf);
    }
}

void CPieChartDlg::OnBnClickedTitleset()
{
    UpdateData();
    m_pieChart.SetPieChartTitle(m_TitleStr);
}

void CPieChartDlg::OnBnClickedSave()
{
    CFileDialog dlg(FALSE, L".jpeg", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                    L"JPEG Files (*.jpeg)|*.jpeg |GIF Files (*.gif)|*.gif |PNG Files (*.png)|*.png ||");

    if (dlg.DoModal() == IDOK) {
        CString sP = dlg.GetFileExt();
        m_pieChart.SaveImage(dlg.GetPathName());
    }
}

void CPieChartDlg::OnCbnSelchangeStyle()
{
    CString sType;
    m_Styles.GetLBText(m_Styles.GetCurSel(), sType);

    if (!sType.Compare(L"Doughnut style"))
        m_pieChart.SetPieChartStyle(CPieChartWnd::DoughnutStyle);
    else if (!sType.Compare(L"2-D style"))
        m_pieChart.SetPieChartStyle(CPieChartWnd::TwoDStyle);
    else if (!sType.Compare(L"3-D style"))
        m_pieChart.SetPieChartStyle(CPieChartWnd::ThreeDStyle);
}

void CPieChartDlg::OnCbnSelchangeSort()
{
    CString sType;
    m_Sort.GetLBText(m_Sort.GetCurSel(), sType);

    if (!sType.Compare(L"Clockwise"))
        m_pieChart.sortPiechartElements(true);

    if (!sType.Compare(L"Anticlockwise"))
        m_pieChart.sortPiechartElements(false);

    if (!sType.Compare(L"Added order"))
        m_pieChart.SortToOrginalOrder();
}

void CPieChartDlg::OnBnClickedHeightset()
{
    UpdateData();
    m_pieChart.SetDepth(m_Height);
}

void CPieChartDlg::OnBnClickedRemove()
{
    UpdateData();
    PIECHARTITEM item = m_pieChart.GetSelectedElement();

    if (item) {
        CString sName = m_pieChart.GetElementName(item);
        m_pieChart.RemoveItem(item);
        m_GrLight.DeleteString(m_GrLight.FindString(0, sName));
        m_GrDark.DeleteString(m_GrDark.FindString(0, sName));
        m_ItmSeperate.DeleteString(m_ItmSeperate.FindString(0, sName));
        m_ItmTransparent.DeleteString(m_ItmTransparent.FindString(0, sName));
    }
}

void CPieChartDlg::AddTestItems(void)
{
    double dVal = 0;
    Color mClr[] = {Color::Red, Color::Blue, Color::BlueViolet, Color::Brown, Color::Olive,
                    Color::Crimson, Color::DarkGreen, Color::DarkOrange
                   };
    srand((int)time(NULL));
    float Val = 0.037f;

    for (int i = 0; i < 8; ++i) {
        CString sVal;
        CString sName = L"Item";
        sVal.Format(L"%d", (i + 1));
        sName.Append(sVal);
        dVal = rand();

        if (dVal > 100)
            dVal = dVal / 100;

        Color itemColor(i + 100, i * 20, 20);
        m_pieChart.InsertItem(sName, sName,  dVal, mClr[i % 8]);
        m_GrLight.AddString(sName);
        m_GrDark.AddString(sName);
        m_ItmSeperate.AddString(sName);
        m_ItmTransparent.AddString(sName);
        Val = 100 - 0.37f;
    }

    m_pieChart.SetBackgrndColor(Color(180, 180, 180));
    m_pieChart.SetLabelBoxColor(Color(220, 220, 200));
}

void CPieChartDlg::OnCbnSelchangeGrdark()
{
    CString sType;
    int iSelect = m_GrDark.GetCurSel();
    int Pos = 0;

    if (iSelect != -1)
        m_GrDark.GetLBText(iSelect, sType);

    if (!sType.Compare(L"Background")) {
        Pos = (int)m_pieChart.GetBackgroundGrDark();
    } else {
        PIECHARTITEM item = m_pieChart.GetPieChartItem(sType);

        if (item) {
            Pos = (int)m_pieChart.GetElementGrDark(item);
        }
    }

    m_SliderGrDark.SetPos(Pos);
}

void CPieChartDlg::OnCbnSelchangeGrlight()
{
    CString sType;
    int iSelect = m_GrLight.GetCurSel();
    int Pos = 0;

    if (iSelect != -1)
        m_GrLight.GetLBText(iSelect, sType);

    if (!sType.Compare(L"Background")) {
        Pos = (int)m_pieChart.GetBackGroungGrLight();
    } else {
        PIECHARTITEM item = m_pieChart.GetPieChartItem(sType);

        if (item) {
            Pos = (int)m_pieChart.GetElementGrLight(item);
        }
    }

    m_SliderGrLight.SetPos(Pos);
}
