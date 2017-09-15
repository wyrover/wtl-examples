// PageColors.cpp : implementation file
//

#include "stdafx.h"
#include "CPPHtmlStatic_demo.h"
#include "CPPHtmlStatic_demoDlg.h"
#include "PageColors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageColors property page

IMPLEMENT_DYNCREATE(CPageColors, CPropertyPage)

CPageColors::CPageColors() : CPropertyPage(CPageColors::IDD)
{
	//{{AFX_DATA_INIT(CPageColors)
	m_granularity = 5;
	m_effect_bk = 0;
	m_theme_bk_color = 0;
	//}}AFX_DATA_INIT
}

CPageColors::~CPageColors()
{
}

void CPageColors::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageColors)
	DDX_Control(pDX, IDC_TEXT_COLOR, m_text_color);
	DDX_Control(pDX, IDC_END_BK_COLOR, m_end_color);
	DDX_Control(pDX, IDC_MID_BK_COLOR, m_mid_color);
	DDX_Control(pDX, IDC_START_BK_COLOR, m_start_color);
	DDX_Text(pDX, IDC_EDIT1, m_granularity);
	DDX_CBIndex(pDX, IDC_EFFECT_BK, m_effect_bk);
	DDX_CBIndex(pDX, IDC_THEME_BK_COLOR, m_theme_bk_color);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageColors, CPropertyPage)
	//{{AFX_MSG_MAP(CPageColors)
	ON_CBN_SELENDOK(IDC_THEME_BK_COLOR, OnChangeThemeBkColor)
	ON_CBN_SELENDOK(IDC_EFFECT_BK, OnChangeEffectBk)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEffectBk)
	//}}AFX_MSG_MAP
	ON_MESSAGE (CPN_SELENDOK, OnChangeBkColor)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageColors message handlers

BOOL CPageColors::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageColors::OnChangeThemeBkColor() 
{
	UpdateData();
	switch(m_theme_bk_color)
	{
	case 0:
		//Standard
		m_start_color.SetColour(RGB(255, 255, 223));
		m_mid_color.SetColour(RGB(192, 192, 172));
		m_end_color.SetColour(RGB(128, 128, 112));
		break;
	case 1:
		//Silver
		m_start_color.SetColour(RGB(255, 255, 255));
		m_mid_color.SetColour(RGB(240, 247, 255));
		m_end_color.SetColour(RGB(192, 192, 208));
		break;
	case 2:
		//Button
		m_start_color.SetColour(RGB(223, 223, 223));
		m_mid_color.SetColour(RGB(191, 191, 191));
		m_end_color.SetColour(RGB(127, 127, 127));
		break;
	case 3:
		//Exotic
		m_start_color.SetColour(RGB(0, 255, 255));
		m_mid_color.SetColour(RGB(255, 255, 0));
		m_end_color.SetColour(RGB(0, 255, 0));
		break;
	case 4:
		//Aqua
		m_start_color.SetColour(RGB(123, 158, 198));
		m_mid_color.SetColour(RGB(173, 207, 247));
		m_end_color.SetColour(RGB(198, 239, 255));
		break;
	case 5:
		//Chrome
		m_start_color.SetColour(RGB(231, 251, 255));
		m_mid_color.SetColour(RGB(214, 211, 214));
		m_end_color.SetColour(RGB(165, 162, 173));
		break;
	case 6:
		//Gold
		m_start_color.SetColour(RGB(255, 255, 148));
		m_mid_color.SetColour(RGB(255, 231, 132));
		m_end_color.SetColour(RGB(255, 207, 0));
		break;
	case 7:
		//Sunny
		m_start_color.SetColour(RGB(255, 248, 229));
		m_mid_color.SetColour(RGB(255, 209, 115));
		m_end_color.SetColour(RGB(255, 156, 0));
		break;
	case 8:
		//Jungle
		m_start_color.SetColour(RGB(214, 250, 183));
		m_mid_color.SetColour(RGB(148, 236, 104));
		m_end_color.SetColour(RGB(4, 202, 0));
		break;
	case 9:
		//Sky
		m_start_color.SetColour(RGB(203, 233, 254));
		m_mid_color.SetColour(RGB(88, 175, 241));
		m_end_color.SetColour(RGB(0, 67, 202));
		break;
	case 10:
		//Fire
		m_start_color.SetColour(RGB(255, 255, 0));
		m_mid_color.SetColour(RGB(255, 104, 32));
		m_end_color.SetColour(RGB(194, 3, 0));
		break;
	}
	OnChangeBkColor(0, 0);
}

LRESULT CPageColors::OnChangeBkColor(WPARAM wParam, LPARAM lParam)
{
	CPPHtmlStatic_demoDlg * pDlg = (CPPHtmlStatic_demoDlg*)GetParent()->GetParent();
	if (LOWORD(lParam) != IDC_TEXT_COLOR)
		pDlg->m_static.SetBkColor(m_start_color.GetColour(), m_mid_color.GetColour(), m_end_color.GetColour());
	else
		pDlg->m_static.SetTextColor(m_text_color.GetColour());
	
	return 0L;
}

void CPageColors::OnChangeEffectBk() 
{
	UpdateData();
	CPPHtmlStatic_demoDlg * pDlg = (CPPHtmlStatic_demoDlg*)GetParent()->GetParent();
	pDlg->m_static.SetBkEffect(m_effect_bk, m_granularity);
}
