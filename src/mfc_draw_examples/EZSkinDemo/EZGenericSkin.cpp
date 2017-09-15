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

// EZGenericSkin.cpp : implementation file
#include "stdafx.h"
#include "EZSkin.h"
#include "EZGenericSkin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEZGenericSkin
#define K_BMP		_T("Bmp") 
#define K_DRAW		_T("Draw") 
#define K_BCOLOR	_T("BackColor")
#define K_TFONT		_T("TextFont") 
#define K_TCOLOR	_T("TextColor") 

IMPLEMENT_SERIAL(CEZGenericSkin,IEZSkinComponent,UINT(-1))


CEZGenericSkin::CEZGenericSkin()
:m_bDefault(FALSE)
,m_bLoaded(FALSE)
{
}


void CEZGenericSkin::Destroy()
{
	
	m_Dib.DeleteObject();
	m_bDefault = m_bLoaded = FALSE;
	if(m_font.m_hObject)
		m_font.DeleteObject();
}



BOOL CEZGenericSkin::Load(IEZSkinIni* pIni,BOOL bLoadDefaultOnFailure  )
{
	
	ASSERT(pIni);
	Destroy();
	CString strSection = GetSection();
	
	CString strBmp;
	CString strType;
	CString strFont;
	CString strFontOptions;
	int nFontSize;

	BOOL bSuxs = TRUE;
		
	if(!pIni->GetValue(strSection,K_BMP,strBmp))
	{
		if(bLoadDefaultOnFailure)
			LoadDefaultBmp();
		bSuxs = FALSE;
		
		
	}
	
	if(!pIni->GetValue(strSection,K_DRAW,strType))
	{
		if(bLoadDefaultOnFailure)
			LoadDefaultBmp();
		
		bSuxs =FALSE;
	}
	
	if(!pIni->GetValue(strSection,K_BCOLOR,m_clrBk))
	{
		if(bLoadDefaultOnFailure)
			LoadDefaultBackColor();
		
		bSuxs = FALSE;
	}
	
	if(!pIni->GetValue(strSection,K_TFONT,strFont))
	{
		if(bLoadDefaultOnFailure)
			LoadDefaultFont();
		bSuxs =FALSE;
	}
	
	if(!pIni->GetValue(strSection,K_TCOLOR,m_clrTxt))
	{
		if(bLoadDefaultOnFailure)
			LoadDefaultTextColor();
		bSuxs =FALSE;
	}
	
	
	BOOL bStatus=TRUE;
	int nCount=0;
	
	CString strRGB[3];	
	while(bStatus && nCount < 3)
	{
		bStatus=AfxExtractSubString(strRGB[nCount],strFont,nCount,TCHAR(','));
		nCount++;
	}
    
	if(nCount== 3) 
	{
		
		strFont = strRGB[0];
		strFont.TrimLeft();
		strFont.TrimRight();
		
		strFontOptions = strRGB[1];
		strFontOptions.TrimLeft();
		strFontOptions.TrimRight();
		nFontSize =atol(strRGB[2]);
		
	}
	
	if(!LoadFont(strFont,strFontOptions,nFontSize))
	{
		if(bLoadDefaultOnFailure)
			LoadDefaultFont();
		bSuxs =FALSE;
	}

	strBmp = GetCurrentSkinPath()+(CString)_T('\\')+strBmp;
	if(!m_Dib.Load(strBmp))
	{
		LoadDefaultBmp();
		bSuxs =FALSE;
	}
	else
		m_Dib.SetType(GetDrawTypeFromString(strType));

	m_bLoaded = TRUE;
	return bSuxs;
	
}

BOOL CEZGenericSkin::LoadDefault()
{
	
	LoadDefaultBmp();
	LoadDefaultBackColor();
	LoadDefaultTextColor();
	LoadDefaultFont();
	
	m_bDefault = TRUE;
	m_bLoaded = TRUE;
	return TRUE;
	
}

BOOL CEZGenericSkin::LoadFont(CString strFont, CString strStyle, int nHeight)
{
	
	BOOL bItalic = strStyle.FindOneOf(_T("Ii"))!= -1;
	
	BOOL bUnderline = strStyle.FindOneOf(_T("Uu"))!= -1;
	
	int nWeight = strStyle.FindOneOf(_T("Bb"))==-1?FW_NORMAL:FW_DEMIBOLD;
	
	
	
	return m_font.CreateFont(
		nHeight,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		nWeight,                 // nWeight
		bItalic,                     // bItalic
		bUnderline,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		strFont);      
	
	
}

UINT CEZGenericSkin::GetDrawTypeFromString(CString strType)
{
	int nDrawType = CEZDib::BMP_TILE;

	if(!strType.CompareNoCase(_T("Stretch")))
		nDrawType = CEZDib::BMP_STRETCH;
	else if(!strType.CompareNoCase(_T("Normal")))
		nDrawType = CEZDib::BMP_NORMAL;

	return nDrawType;
}

CString CEZGenericSkin::GetCurrentSkinPath()
{

	return CEZSkin::Instance().GetCurrentSkinPath();
}
