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

// EZSkin.cpp: implementation of the CEZSkin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EZSkin.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "EZRuntimeClass.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define S_SKIN _T("SKIN")

	#define K_NAME		_T("Name")
	#define K_AUTHOR	_T("Author")
	#define	K_COMMENT	_T("Comments")




CEZSkin::CEZSkin()
:m_pIni(0)
,m_bDefault(TRUE)
,m_strName(_T("Default"))
{
	
}

CEZSkin::~CEZSkin()
{

	ResetMap();
	delete m_pIni;
	
}

void CEZSkin::AddComponent(CString strClassName)
{
	
	m_mapComponents.SetAt(strClassName,NULL);

	
}

BOOL CEZSkin::LoadSkin(CString strSkin)
{

	if(!m_strCurrentSkin.CompareNoCase(strSkin))
		return TRUE;
	
	DestroyAllComponents();	
	if(!m_pIni) return FALSE;
	CString strPath;
	if(!GetSkinPath(strSkin,strPath))
		return FALSE;
	
	if(m_pIni->Read(strPath))
	{
		m_bDefault = FALSE;
		m_strCurrentSkin = strSkin;
		m_pIni->GetValue(S_SKIN,K_NAME,m_strName);
		m_pIni->GetValue(S_SKIN,K_AUTHOR,m_strAuthor);
		m_pIni->GetValue(S_SKIN,K_COMMENT,m_strComment);
		return TRUE;
	}
	return FALSE;
}

void CEZSkin::LoadDefault()
{
	m_strCurrentSkin.Empty();
	m_bDefault = TRUE;
	
}


BOOL CEZSkin::GetSkinPath(CString strSkin, CString &strPath)
{
	
	static const  CString strSlash = _T('\\');
	
	strPath.Empty();
	CString str = m_strSkinsDir+strSlash+strSkin;
	CFileFind ff;
	BOOL bFound;
	bFound = ff.FindFile(str);
	if(bFound) strPath = str;
	ff.Close();
	return bFound;
	
}

IEZSkinComponent* CEZSkin::GetComponent(CString strComponent)
{
	
	IEZSkinComponent* pComponent = NULL;
	
	if(!m_mapComponents.Lookup(strComponent,pComponent))
		return NULL;
	
	if(!pComponent)
	{
		pComponent = (IEZSkinComponent*)CEZRuntimeClass::CreateObject(strComponent);
		ASSERT(pComponent);
		m_mapComponents.SetAt(strComponent,pComponent);
		
	}
	
	if(m_bDefault)
	{
		
		if(!pComponent->IsDefault()) 
		{
			pComponent->Destroy();
			pComponent->LoadDefault();
		}
		
	}
	
	else if(!pComponent->IsLoaded())
		pComponent->Load(m_pIni);
	return pComponent;
	
}

void CEZSkin::DestroyAllComponents()
{
	
	POSITION pos = m_mapComponents.GetStartPosition();
	while( pos != NULL )
	{
		IEZSkinComponent* pComp;
		CString str;
		m_mapComponents.GetNextAssoc( pos, str, pComp);
		if(pComp)
		delete pComp;
		pComp = NULL;
		m_mapComponents.SetAt(str,NULL);
	}
	
	
	
}

void CEZSkin::SetIni(CString strClassName)
{
	ASSERT(!m_pIni);
	m_pIni = (IEZSkinIni*)CEZRuntimeClass::CreateObject(strClassName);
	ASSERT(m_pIni);
	
	
}


CEZSkin& CEZSkin::Instance()
{
	static CEZSkin  Instance;
	return Instance;

}

CString CEZSkin::GetCurrentSkinPath()
{
	
	CString strPath;
	GetSkinPath(m_strCurrentSkin,strPath);
	return strPath;
}

void CEZSkin::ResetMap()
{

	DestroyAllComponents();
	m_mapComponents.RemoveAll();
}
