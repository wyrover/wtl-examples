// PageBorder.cpp : implementation file
//

#include "stdafx.h"
#include "CPPHtmlStatic_demo.h"
#include "CPPHtmlStatic_demoDlg.h"
#include "PageBorder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageBorder property page

IMPLEMENT_DYNCREATE(CPageBorder, CPropertyPage)

CPageBorder::CPageBorder() : CPropertyPage(CPageBorder::IDD)
{
	//{{AFX_DATA_INIT(CPageBorder)
	m_border = 0;
	m_width = 1;
	m_height = 1;
	//}}AFX_DATA_INIT
}

CPageBorder::~CPageBorder()
{
}

void CPageBorder::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageBorder)
	DDX_Control(pDX, IDC_BUTTON1, m_border_color);
	DDX_Radio(pDX, IDC_RADIO1, m_border);
	DDX_Text(pDX, IDC_EDIT1, m_width);
	DDX_Text(pDX, IDC_EDIT2, m_height);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageBorder, CPropertyPage)
	//{{AFX_MSG_MAP(CPageBorder)
	ON_BN_CLICKED(IDC_RADIO1, OnChangeBorder)
	ON_BN_CLICKED(IDC_RADIO2, OnChangeBorder)
	ON_BN_CLICKED(IDC_RADIO3, OnChangeBorder)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeSizes)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeSizes)
	//}}AFX_MSG_MAP
	ON_MESSAGE (CPN_SELENDOK, OnChangeBorderColor)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageBorder message handlers

BOOL CPageBorder::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_border_color.SetColour(RGB(0, 0, 0));
	UpdateData(FALSE);
	OnChangeSizes();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageBorder::OnChangeBorder() 
{
	CPPHtmlStatic_demoDlg * pDlg = (CPPHtmlStatic_demoDlg*)GetParent()->GetParent();
	pDlg->m_static.SetRgn(NULL);
	OnChangeSizes();
	switch (m_border)
	{
	case 1:
		pDlg->m_static.SetRectRgn();
		break;
	case 2:
		pDlg->m_static.SetRoundRectRgn(20, 20);
		break;
	}
}

LRESULT CPageBorder::OnChangeBorderColor(WPARAM wParam, LPARAM lParam)
{
	OnChangeSizes();
	return 0L;
}

void CPageBorder::OnChangeSizes() 
{
	UpdateData();
	CPPHtmlStatic_demoDlg * pDlg = (CPPHtmlStatic_demoDlg*)GetParent()->GetParent();
	if (m_border)
		pDlg->m_static.SetBorder(m_border_color.GetColour(), m_width, m_height);
	else
		pDlg->m_static.SetBorder((HBRUSH)NULL);
}
