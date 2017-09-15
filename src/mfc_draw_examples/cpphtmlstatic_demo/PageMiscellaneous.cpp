// PageMiscellaneous.cpp : implementation file
//

#include "stdafx.h"
#include "CPPHtmlStatic_demo.h"
#include "CPPHtmlStatic_demoDlg.h"
#include "PageMiscellaneous.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageMiscellaneous property page

IMPLEMENT_DYNCREATE(CPageMiscellaneous, CPropertyPage)

CPageMiscellaneous::CPageMiscellaneous() : CPropertyPage(CPageMiscellaneous::IDD)
{
	//{{AFX_DATA_INIT(CPageMiscellaneous)
	m_enable_ctrl = TRUE;
	//}}AFX_DATA_INIT
	m_bOrgSizes = TRUE;
}

CPageMiscellaneous::~CPageMiscellaneous()
{
}

void CPageMiscellaneous::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageMiscellaneous)
	DDX_Check(pDX, IDC_CHECK1, m_enable_ctrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageMiscellaneous, CPropertyPage)
	//{{AFX_MSG_MAP(CPageMiscellaneous)
	ON_BN_CLICKED(IDC_CHECK1, OnEnableControl)
	ON_BN_CLICKED(IDC_BUTTON1, OnToggleSizes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageMiscellaneous message handlers

BOOL CPageMiscellaneous::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CPPHtmlStatic_demoDlg * pDlg = (CPPHtmlStatic_demoDlg*)GetParent()->GetParent();
	pDlg->m_static.GetWindowRect(&m_rcOrg);
	pDlg->ScreenToClient(&m_rcOrg);
	m_rcSmall = m_rcOrg;
	m_rcSmall.DeflateRect(0, 0, 50, 50);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageMiscellaneous::OnEnableControl() 
{
	UpdateData();
	CPPHtmlStatic_demoDlg * pDlg = (CPPHtmlStatic_demoDlg*)GetParent()->GetParent();
	pDlg->m_static.EnableWindow(m_enable_ctrl);
	
}

void CPageMiscellaneous::OnToggleSizes() 
{
	CPPHtmlStatic_demoDlg * pDlg = (CPPHtmlStatic_demoDlg*)GetParent()->GetParent();
	m_bOrgSizes = m_bOrgSizes ? FALSE : TRUE;
	pDlg->m_static.MoveWindow(m_bOrgSizes ? m_rcOrg : m_rcSmall);
}
