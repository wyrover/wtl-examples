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
// EZDialogSkin.cpp : implementation file
#include "stdafx.h"
#include "resource.h"
#include "EZSkin.h"
#include "EZDialogSkin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEZDialogSkin
IMPLEMENT_SERIAL(CEZDialogSkin,IEZSkinComponent,(UINT)-1)

CEZDialogSkin::CEZDialogSkin()
{
}


CEZDialogSkin::~CEZDialogSkin()
{
	
}




CString CEZDialogSkin::GetSection()
{
	// TODO: Add your specialized code here and/or call the base class

	return _T("Main");
}

void CEZDialogSkin::LoadDefaultBackColor()
{
	// TODO: Add your specialized code here and/or call the base class
	m_clrBk= RGB(0,0,255);
	
}

void CEZDialogSkin::LoadDefaultBmp()
{
	// TODO: Add your specialized code here and/or call the base class
	m_Dib.Load(IDB_BACK);
	m_Dib.SetType(CEZDib::BMP_TILE);
	
}

void CEZDialogSkin::LoadDefaultFont()
{
	// TODO: Add your specialized code here and/or call the base class
	LoadFont(_T("Times New Roman"),_T("B"),20);
	
}

void CEZDialogSkin::LoadDefaultTextColor()
{
	
	m_clrTxt= RGB(255,0,0);

	
}

