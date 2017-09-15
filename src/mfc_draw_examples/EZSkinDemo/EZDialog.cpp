//----------------------------------------------------------------------------------------//
/******************************************************************************************
V. Lakshmi Narasimhan,ezlux@yahoo.com
This Code is a Part of the EZSkin Framework.

Feel free to use ,modify,twist,turn,digest or anything u want to do.
However if u find this code useful enough to be used in your great
commercial application an e-mail would be appreciated!

This code is provided "as is" without any warranty -express or implied
blah. blah.. blah...
********************************************************************************************/
//------------------------------------------------------------------------------------------//

// EZDialog.cpp : implementation file
//

#include "stdafx.h"
#include "EZDialog.h"
#include "EZSkin.h"
#include "EZDialogSkin.h"
#include "EZCaption.h"
#include "EZWindowNC.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CEZDialog dialog
CEZDialog::CEZDialog()
{
	
	Init();
}

CEZDialog::CEZDialog(UINT uResource, CWnd* pParent /*=NULL*/)
: CDialog(uResource, pParent)
{
	//{{AFX_DATA_INIT(CEZDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	Init();
}


void CEZDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEZDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEZDialog, CDialog)
//{{AFX_MSG_MAP(CEZDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEZDialog message handlers

HBRUSH CEZDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{	

	CEZSkin& ezs = CEZSkin::Instance();
	CEZDialogSkin* pSkin  = DYNAMIC_DOWNCAST(CEZDialogSkin,ezs.GetComponent(_T("CEZDialogSkin")));
	ASSERT(pSkin);
	CBrush brush(pSkin->GetBackColor());
	
	switch(nCtlColor) 
	{
			case CTLCOLOR_STATIC:
				// The Slider Control has CTLCOLOR_STATIC, but doesn't let
				// the background shine through,
				TCHAR lpszClassName[255];
				GetClassName(pWnd->m_hWnd, lpszClassName, 255);
				if(_tcscmp(lpszClassName, TRACKBAR_CLASS) == 0)
					return (HBRUSH)brush;

			case CTLCOLOR_BTN:
				// let static controls shine through
				pDC->SetBkMode(TRANSPARENT);
				return HBRUSH(m_brushHollow);

			default:
				break;
		};
	
	return (HBRUSH)brush;
	
}

BOOL CEZDialog::OnEraseBkgnd(CDC* pDC) 
{

	CEZSkin& ezs = CEZSkin::Instance();
	CEZDialogSkin* pSkin  = DYNAMIC_DOWNCAST(CEZDialogSkin,ezs.GetComponent(_T("CEZDialogSkin")));
	ASSERT(pSkin);
	const CEZDib& bmp = pSkin->GetBackgroundBitmap();
	CEZClientRect rcClient(this);
	bmp.Draw(pDC,rcClient);
	return TRUE; 
	//	return CDialog::OnEraseBkgnd(pDC);
}

void CEZDialog::Init()
{

	
	CEZSkin& ezs = CEZSkin::Instance();
	ezs.AddComponent(_T("CEZDialogSkin"));
	VERIFY(m_brushHollow.CreateStockObject(HOLLOW_BRUSH));


}


BOOL CEZDialog::OnQueryNewPalette() 
{
	// TODO: Add your message handler code here and/or call default
	CEZSkin& ezs = CEZSkin::Instance();
	CEZDialogSkin* pSkin  = DYNAMIC_DOWNCAST(CEZDialogSkin,ezs.GetComponent(_T("CEZDialogSkin")));
	ASSERT(pSkin);
	const CEZDib& bmp = pSkin->GetBackgroundBitmap();

	CPalette* pPal = bmp.GetPalette();
	if( pPal != NULL && GetSafeHwnd() != 0 ) 
	{
		CClientDC dc(this);
		CPalette * pOldPalette = dc.SelectPalette(pPal, FALSE);
		UINT nChanged = dc.RealizePalette();
		dc.SelectPalette(pOldPalette, TRUE);

		if (nChanged == 0)
			return FALSE;

		Invalidate();
		return TRUE;
	}
	return CDialog::OnQueryNewPalette();
}

void CEZDialog::OnPaletteChanged(CWnd* pFocusWnd) 
{
	
	CEZSkin& ezs = CEZSkin::Instance();
	CEZDialogSkin* pSkin  = DYNAMIC_DOWNCAST(CEZDialogSkin,ezs.GetComponent(_T("CEZDialogSkin")));
	ASSERT(pSkin);
	const CEZDib& bmp = pSkin->GetBackgroundBitmap();

	CPalette* pPal = bmp.GetPalette();
	if( pPal != NULL && GetSafeHwnd() != 0 && pFocusWnd != this && ! IsChild(pFocusWnd) ) 
	{
		CClientDC dc(this);
		CPalette * pOldPalette = dc.SelectPalette(pPal, TRUE);
		UINT nChanged = dc.RealizePalette();
		dc.SelectPalette(pOldPalette, TRUE);

		if( nChanged )
			Invalidate();
	} else
		CDialog::OnPaletteChanged(pFocusWnd);
}



BOOL CEZDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_Caption.Install(this);	
	m_Border.Install(this);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


