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

// EZSkinIni.cpp: implementation of the CEZSkinIni class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EZSkinIni.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CEZSkinIni,IEZSkinIni,(UINT)-1)

CEZSkinIni::CEZSkinIni()
{

}

CEZSkinIni::~CEZSkinIni()
{

	m_strar.RemoveAll();

}


BOOL CEZSkinIni::Read(CString strFile)
{

	strFile+=_T("\\skin.ini");
	CStdioFile file;

	m_strar.RemoveAll();
	if(!file.Open(strFile,CFile::modeRead))
		return FALSE;
	CString strLine;
	while(file.ReadString(strLine))
	{
		int nLen = strLine.GetLength();
		strLine.TrimLeft();
		int nSemi = strLine.Find(TCHAR(';'));
		if(nSemi!=-1)
			strLine = strLine.Left(nSemi);
		strLine.TrimRight();

		m_strar.Add(strLine);
	}

	file.Close();

	return TRUE;
}


BOOL CEZSkinIni::GetValue(CString strSection, CString strKey, CString &strValue)
{

	int nSection = FindSection(strSection);
	if(nSection == -1 ) return FALSE;

	return(FindItem(nSection,strKey,strValue)!=-1);
	


}

BOOL CEZSkinIni::GetValue(CString strSection, CString strKey, int& nValue)
{

	int nSection = FindSection(strSection);
	if(nSection == -1 ) return FALSE;


	CString strValue;
	if(FindItem(nSection,strKey,strValue) == -1)
		return FALSE;

	nValue = atol((LPCTSTR)strValue);
	return TRUE;
	

}

BOOL CEZSkinIni::GetValue(CString strSection, CString strKey, COLORREF& clrValue)
{


	int nSection = FindSection(strSection);
	if(nSection == -1 ) return FALSE;

	CString strValue,strRGB[3];
	TCHAR ch = TCHAR(",");
	if(FindItem(nSection,strKey,strValue) == -1)
		return FALSE;

	BOOL bStatus=TRUE;
	int nCount=0;


	while(bStatus && nCount < 4)
	{
		bStatus=AfxExtractSubString(strRGB[nCount],strValue,nCount,TCHAR(','));
		
		nCount++;
	}
    
	if(nCount<4) return FALSE;

	int nRed = atol(strRGB[0]);
	int nGreen = atol(strRGB[1]);
	int nBlue = atol(strRGB[2]);
	clrValue = RGB(nRed,nGreen,nBlue);

	return TRUE;

}

BOOL CEZSkinIni::GetValue(CString strSection, CString strKey, CPoint& ptValue)
{


	int nSection = FindSection(strSection);
	if(nSection == -1 ) return FALSE;

	CString strValue,strpt[2];
	TCHAR ch = TCHAR(",");
	if(FindItem(nSection,strKey,strValue) == -1)
		return FALSE;

	BOOL bStatus=TRUE;
	int nCount=0;


	while(bStatus && nCount < 3)
	{
		bStatus=AfxExtractSubString(strpt[nCount],strValue,nCount,TCHAR(','));
		
		nCount++;
	}
    
	if(nCount<3) return FALSE;

	ptValue.x = atol(strpt[0]);
	ptValue.y = atol(strpt[1]);
	return TRUE;


}


int CEZSkinIni::FindSection(CString strSection, int nStartFrom)
{
	int nLine, nLines = m_strar.GetSize();
	CString strFmt;
	strFmt.Format(_T("[%s]"),strSection);
	for (nLine = nStartFrom; nLine < nLines; nLine++)
		if (!m_strar.GetAt(nLine).CompareNoCase(strFmt)) 
			return nLine;

	return -1;
}


int CEZSkinIni::FindItem(const int iSection, CString strItem, CString &strVal)
{

	ASSERT(iSection >= 0);
	ASSERT(!strItem.IsEmpty());

	int nmax = m_strar.GetSize(), nItem;
	CString  strLook;
	

	for (nItem = iSection; nItem < nmax; nItem++)
	{
		
			CString strLine = m_strar.GetAt(nItem);
			int nEquals = strLine.Find(TCHAR('='));
			if(nEquals == -1)
			{
				
				strLook= strLine.Left(nEquals);
				strLook.TrimLeft();
				strLook.TrimRight();
				if(!strLook.CompareNoCase(strItem))
					return nItem;
				continue;
			}
			strLook= strLine.Left(nEquals);
			strLook.TrimLeft();
			strLook.TrimRight();
			
				if (!strLook.CompareNoCase(strItem)) 
				{
					
					
						strVal = strLine.Right(strLine.GetLength()-nEquals-1);
						strVal.TrimLeft();
						strVal.TrimRight();
						return nItem;
				}
		
	}
	return -1;

}

BOOL CEZSkinIni::IsSection(int nSection)
{

	ASSERT(nSection >= 0 && nSection < m_strar.GetSize());
	if (nSection >= 0 && nSection < m_strar.GetSize())
	{
		CString strItem = m_strar.GetAt(nSection);
		if (strItem.GetLength() > 2 && strItem.Left(1) == '[' && strItem.Right(1) == ']') return true;
	}
	return false;
}
