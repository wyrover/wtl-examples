// PageImages.cpp : implementation file
//

#include "stdafx.h"
#include "cpphtmlstatic_demo.h"
#include "CPPHtmlStatic_demoDlg.h"
#include "PageImages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageImages property page

IMPLEMENT_DYNCREATE(CPageImages, CPropertyPage)

CPageImages::CPageImages() : CPropertyPage(CPageImages::IDD)
{
	//{{AFX_DATA_INIT(CPageImages)
	m_width = 1;
	m_height = 1;
	m_width_per = 100;
	m_height_per = 100;
	//}}AFX_DATA_INIT
}

CPageImages::~CPageImages()
{
}

void CPageImages::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageImages)
	DDX_Radio(pDX, IDC_RADIO1, m_width);
	DDX_Radio(pDX, IDC_RADIO3, m_height);
	DDX_Text(pDX, IDC_EDIT1, m_width_per);
	DDX_Text(pDX, IDC_EDIT2, m_height_per);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageImages, CPropertyPage)
	//{{AFX_MSG_MAP(CPageImages)
	ON_BN_CLICKED(IDC_RADIO1, OnChangeWidth)
	ON_BN_CLICKED(IDC_RADIO2, OnChangeWidth)
	ON_BN_CLICKED(IDC_RADIO3, OnChangeHeight)
	ON_BN_CLICKED(IDC_RADIO4, OnChangeHeight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageImages message handlers

BOOL CPageImages::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageImages::OnChangeWidth() 
{
	OnChangeHeight();
	
}

void CPageImages::OnChangeHeight() 
{
	CPPHtmlStatic_demoDlg * pDlg = (CPPHtmlStatic_demoDlg*)GetParent()->GetParent();
	UpdateData();
	UINT nWidth = m_width ? m_width_per : 0;
	UINT nHeight = m_height ? m_height_per : 0;
	pDlg->m_static.SetImageZoom(nWidth, nHeight);
}
