// PageAlign.cpp : implementation file
//

#include "stdafx.h"
#include "CPPHtmlStatic_demo.h"
#include "CPPHtmlStatic_demoDlg.h"
#include "PageAlign.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageAlign property page

IMPLEMENT_DYNCREATE(CPageAlign, CPropertyPage)

CPageAlign::CPageAlign() : CPropertyPage(CPageAlign::IDD)
{
	//{{AFX_DATA_INIT(CPageAlign)
	m_horz_align = 0;
	m_vert_align = 0;
	m_word_wrap = FALSE;
	//}}AFX_DATA_INIT
}

CPageAlign::~CPageAlign()
{
}

void CPageAlign::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageAlign)
	DDX_Radio(pDX, IDC_RADIO1, m_horz_align);
	DDX_Radio(pDX, IDC_RADIO5, m_vert_align);
	DDX_Check(pDX, IDC_CHECK2, m_word_wrap);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageAlign, CPropertyPage)
	//{{AFX_MSG_MAP(CPageAlign)
	ON_BN_CLICKED(IDC_CHECK2, OnChangeWordWrapping)
	ON_BN_CLICKED(IDC_RADIO1, OnChangeAlign)
	ON_BN_CLICKED(IDC_RADIO2, OnChangeAlign)
	ON_BN_CLICKED(IDC_RADIO3, OnChangeAlign)
	ON_BN_CLICKED(IDC_RADIO4, OnChangeAlign)
	ON_BN_CLICKED(IDC_RADIO5, OnChangeAlign)
	ON_BN_CLICKED(IDC_RADIO6, OnChangeAlign)
	ON_BN_CLICKED(IDC_RADIO7, OnChangeAlign)
	ON_BN_CLICKED(IDC_RADIO8, OnChangeAlign)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageAlign message handlers
BOOL CPageAlign::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CPPHtmlStatic_demoDlg * pDlg = (CPPHtmlStatic_demoDlg*)GetParent()->GetParent();
	m_word_wrap = (pDlg->m_static.GetStyle() & SS_LEFTNOWORDWRAP) ? FALSE : TRUE;

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageAlign::OnChangeWordWrapping() 
{
	CPPHtmlStatic_demoDlg * pDlg = (CPPHtmlStatic_demoDlg*)GetParent()->GetParent();
	UpdateData();
	pDlg->m_static.SetWrapText(m_word_wrap);
	pDlg->m_static.RedrawWindow();
}

void CPageAlign::OnChangeAlign() 
{
	CPPHtmlStatic_demoDlg * pDlg = (CPPHtmlStatic_demoDlg*)GetParent()->GetParent();
	UpdateData();
	DWORD dwAlign = ((m_vert_align << 2) & 0xC) + (m_horz_align & 0x3);
	pDlg->m_static.SetAlign(dwAlign);
}
