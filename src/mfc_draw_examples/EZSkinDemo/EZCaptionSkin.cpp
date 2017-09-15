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
// EZCaptionSkin.cpp : implementation file
#include "stdafx.h"
#include "EZCaptionSkin.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEZCaptionSkin
#define S_BTNS ("Buttons")
	#define BK_NORMAL		_T("BtnsNormal")
	#define BK_HIGHLIGHT	_T("BtnsHilight")
	#define BK_TRANS		_T("TransColor")
	#define BK_POS			_T("BtnPos")
	#define BK_WIDTH		_T("BtnWidth")

IMPLEMENT_SERIAL(CEZCaptionSkin,CEZGenericSkin,(UINT)-1)

CEZCaptionSkin::CEZCaptionSkin()
{
}


CEZCaptionSkin::~CEZCaptionSkin()
{
	Destroy();
}



void CEZCaptionSkin::Destroy()
{
	// TODO: Add your specialized code here and/or call the base class
	CEZGenericSkin::Destroy();
	m_DibBtnHilight.DeleteObject();
	m_DibBtnNormal.DeleteObject();
		
}

CString CEZCaptionSkin::GetSection()
{
	
	return _T("Caption");
}

BOOL CEZCaptionSkin::Load(IEZSkinIni* pIni,BOOL bLoadDefaultOnFailure  )
{
		if(!CEZGenericSkin::Load(pIni,bLoadDefaultOnFailure))
		{
			LoadDefaultButtons();
			return FALSE;
		}
		if(!LoadButtons(pIni))
		{
			LoadDefaultButtons();
			return FALSE;
		}

		return TRUE;
}

BOOL CEZCaptionSkin::LoadDefault()
{
	CEZGenericSkin::LoadDefault();
	LoadDefaultButtons();
	return TRUE;
}

void CEZCaptionSkin::LoadDefaultBackColor()
{
	
	m_clrBk = RGB(0,0,0);
}

void CEZCaptionSkin::LoadDefaultBmp()
{
	m_Dib.Load(IDB_CAPTION);
	m_Dib.SetType(CEZDib::BMP_TILE);
}

void CEZCaptionSkin::LoadDefaultFont()
{
	
	LoadFont(_T("Arial Black"),"B",24);

	
}

void CEZCaptionSkin::LoadDefaultTextColor()
{
	
	m_clrTxt = RGB(255,255,255);
}


void CEZCaptionSkin::LoadDefaultButtons()
{

	m_DibBtnHilight.Load(IDB_BTNSH);
	m_DibBtnNormal.Load(IDB_BTNS);
	m_clrTransparent = RGB(192,224,64);
	m_rectBtns[0] = CRect(7,0,27,20);
	m_rectBtns[1] = CRect(27,0,47,20);
	m_rectBtns[2] = CRect(47,0,67,20);
	


}

BOOL CEZCaptionSkin::LoadButtons(IEZSkinIni *pIni)
{

	CString strBtn,strBtnh;
	if(!pIni->GetValue(GetSection(),BK_NORMAL,strBtn))
	{
		
		return FALSE;
	}

	if(!pIni->GetValue(GetSection(),BK_HIGHLIGHT,strBtnh))
	{
		return FALSE;
	}

	COLORREF clrHack;
	
	if(!pIni->GetValue(GetSection(),BK_TRANS,m_clrTransparent))
	{
		
		return FALSE;
	}

	if(!pIni->GetValue(GetSection(),BK_POS,clrHack))
	{
		
		return FALSE;
	}
	
	int nWidth;
	if(!pIni->GetValue(GetSection(),BK_WIDTH,nWidth))
	{
		
		return FALSE;
	}

	CString strPathN = GetCurrentSkinPath()+(CString)_T('\\')+strBtn;
	CString strPathH = GetCurrentSkinPath()+(CString)_T('\\')+strBtnh;

	if(strPathN.IsEmpty() || strPathH.IsEmpty())
	{

		return FALSE;
	}
	if(!m_DibBtnNormal.Load(strPathN))
		return FALSE;
	m_DibBtnNormal.SetType(CEZDib::BMP_NORMAL);
	if(!m_DibBtnHilight.Load(strPathH))
		return FALSE;
	m_DibBtnHilight.SetType(CEZDib::BMP_NORMAL);

	int nMin = GetRValue(clrHack);
	int nMax = GetGValue(clrHack);
	int nClose = GetBValue(clrHack);

	CSize size(m_DibBtnHilight.GetWidth(),m_DibBtnHilight.GetHeight());
	m_rectBtns[0] = CRect(nMin,0,nMin+nWidth,size.cy);
	m_rectBtns[1] = CRect(nMax,0,nMax+nWidth,size.cy);
	m_rectBtns[2] = CRect(nClose,0,nClose+nWidth,size.cy);

	return TRUE;

}
