// PageStyles.cpp : implementation file
//

#include "stdafx.h"
#include "cpphtmlstatic_demo.h"
#include "CPPHtmlStatic_demoDlg.h"
#include "PageStyles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageStyles property page

IMPLEMENT_DYNCREATE(CPageStyles, CPropertyPage)

CPageStyles::CPageStyles() : CPropertyPage(CPageStyles::IDD)
{
	//{{AFX_DATA_INIT(CPageStyles)
	m_border = FALSE;
	m_client_edge = FALSE;
	m_static_edge = FALSE;
	m_modal_frame = FALSE;
	//}}AFX_DATA_INIT
}

CPageStyles::~CPageStyles()
{
}

void CPageStyles::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageStyles)
	DDX_Check(pDX, IDC_CHECK3, m_border);
	DDX_Check(pDX, IDC_CHECK4, m_client_edge);
	DDX_Check(pDX, IDC_CHECK5, m_static_edge);
	DDX_Check(pDX, IDC_CHECK6, m_modal_frame);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageStyles, CPropertyPage)
	//{{AFX_MSG_MAP(CPageStyles)
	ON_BN_CLICKED(IDC_CHECK1, OnChangeStyles)
	ON_BN_CLICKED(IDC_CHECK3, OnChangeStyles)
	ON_BN_CLICKED(IDC_CHECK4, OnChangeStyles)
	ON_BN_CLICKED(IDC_CHECK5, OnChangeStyles)
	ON_BN_CLICKED(IDC_CHECK6, OnChangeStyles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageStyles message handlers

BOOL CPageStyles::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageStyles::OnChangeStyles() 
{
	CPPHtmlStatic_demoDlg * pDlg = (CPPHtmlStatic_demoDlg*)GetParent()->GetParent();
	UpdateData();

	if (m_border) pDlg->m_static.ModifyStyle(0, WS_BORDER, SWP_DRAWFRAME);
	else pDlg->m_static.ModifyStyle(WS_BORDER, 0, SWP_DRAWFRAME);

	if (m_client_edge) pDlg->m_static.ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_DRAWFRAME);
	else pDlg->m_static.ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_DRAWFRAME);

	if (m_modal_frame) pDlg->m_static.ModifyStyleEx(0, WS_EX_DLGMODALFRAME, SWP_DRAWFRAME);
	else pDlg->m_static.ModifyStyleEx(WS_EX_DLGMODALFRAME, 0, SWP_DRAWFRAME);

	if (m_static_edge) pDlg->m_static.ModifyStyleEx(0, WS_EX_STATICEDGE, SWP_DRAWFRAME);
	else pDlg->m_static.ModifyStyleEx(WS_EX_STATICEDGE, 0, SWP_DRAWFRAME);
}
