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

// EZSkinManager.cpp: implementation of the CEZSkinManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EZSkinDemo.h"
#include "EZSkinManager.h"
#include "EZSkin_I.h"
#include "EZSkinIni.h "

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define HKEY_SKINS _T("Skins")
#define HKEY_DIR   _T("Dir")
#define HKEY_SKIN  _T("Current")

#include "EZSkin.h"
#include "EZRuntimeClass.h"

CEZSkinManager::CEZSkinManager()
:m_strCurrentSkin()
,m_strSkins()
{

}

CEZSkinManager::~CEZSkinManager()
{

	

}

void CEZSkinManager::Read()
{

	m_strSkins = AfxGetApp()->GetProfileString(HKEY_SKINS,HKEY_DIR,_T(""));
	CEZSkin::Instance().SetIni(_T("CEZSkinIni"));
	CFileFind ff;
	BOOL bLoaded = ff.FindFile(m_strSkins);
	if(bLoaded)
	{
		CEZSkin::Instance().SetSkinsDir(m_strSkins);
		m_strCurrentSkin =  AfxGetApp()->GetProfileString(HKEY_SKINS,HKEY_SKIN);
		ff.Close();
	}

	LoadSkin(m_strCurrentSkin);

	


}

void CEZSkinManager::Save()
{
	
	
	AfxGetApp()->WriteProfileString(HKEY_SKINS,HKEY_DIR,m_strSkins);
	AfxGetApp()->WriteProfileString(HKEY_SKINS,HKEY_SKIN,m_strCurrentSkin);

}

CString CEZSkinManager::GetCurrentSkinPath() const
{

	return m_strSkins+(CString)_T('\\')+m_strCurrentSkin;
}


int CEZSkinManager::EnumerateSkins(CStringArray *pstrar)
{

	BOOL bMoreSkins = TRUE;
	CFileFind  ff;
	if(!ff.FindFile(m_strSkins))
		return 0;
	ff.Close();
	bMoreSkins = ff.FindFile(GetSkinPath(_T("*.*"),FALSE));

	CEZSkinIni* pIni = (CEZSkinIni*)CEZRuntimeClass::CreateObject(_T("CEZSkinIni"));
	int nSkins = 0;
	while(bMoreSkins)
	{
		if(bMoreSkins)
		{
		
			bMoreSkins = ff.FindNextFile();
			if(ff.IsDirectory() && !ff.IsDots())
			{
				if(pIni->Read(ff.GetFilePath()))
				{
					pstrar->Add(ff.GetFileName());
					nSkins++;
				}

			}
		}

	}

	delete pIni;
	return nSkins;
}

CString CEZSkinManager::GetSkinPath(CString strName,BOOL bValidate)
{

	CString strPath = m_strSkins+(CString)_T("\\")+strName;
	
	if(bValidate)
	{
		CFileFind ff;
		if(!ff.FindFile(strPath))
		{	
			strPath.Empty();
			return strPath;
		}
	}

	return strPath;

}

void CEZSkinManager::LoadSkin(CString strSkin)
{

	if(strSkin.IsEmpty())
	{
		CEZSkin::Instance().LoadDefault();
		m_strCurrentSkin = _T("");
		return;
	}
	CFileFind ff;

	BOOL bLoaded = ff.FindFile(GetSkinPath(strSkin));
	if(bLoaded)
	{	
		m_strCurrentSkin = strSkin;		
		bLoaded = CEZSkin::Instance().LoadSkin(m_strCurrentSkin);

	}	
	ff.Close();
}


