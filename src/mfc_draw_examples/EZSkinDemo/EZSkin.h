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

// EZSkin.h: interface for the CEZSkin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EZSKIN_H__74A45F5A_337C_4AA9_8F6A_EFD706E076B8__INCLUDED_)
#define AFX_EZSKIN_H__74A45F5A_337C_4AA9_8F6A_EFD706E076B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EZSkin_I.h"
#include <afxTempl.h>
/*
<CLASS Name = CEZSkin >


  The Backbone of the whole framework!

  This is a singleton class that takes components 
  by their names and performs Just in time initialization and
  loading.

<CLASS>
*/

class CEZSkin : public CObject  
{

//Construction - Destruction
public:

	virtual ~CEZSkin();


//Operations
public:
	static CEZSkin& Instance();
	virtual void SetIni(CString strClassName);
	virtual IEZSkinComponent* GetComponent(CString strComponent);
	
	virtual void LoadDefault();
	virtual BOOL LoadSkin(CString strSkin);
	virtual void AddComponent(CString strClassName);

//Helpers
protected:
	virtual void DestroyAllComponents();
	BOOL GetSkinPath(CString strSkin,CString& strPath );
	CEZSkin();
	

//Component Map
private:
	
	CTypedPtrMap<CMapStringToOb,CString,IEZSkinComponent*> m_mapComponents;
	IEZSkinIni* m_pIni;

//Attributes
public:
	CString GetCurrentSkinPath();

	const CString GetName() const{return m_strName;}
	const CString GetAuthor() const{return m_strAuthor;}
	const CString GetComment() const{return m_strComment;}

	const CString GetSkinsDir() const{return m_strSkinsDir;}
	void SetSkinsDir(const CString& strDir){m_strSkinsDir = strDir;}

//Skin Details
private:

	CString 
				m_strName,
				m_strAuthor,
				m_strComment;

//Skin Management
protected:
	void ResetMap();

	
	CString m_strSkinsDir;
	CString m_strCurrentSkin;
	BOOL m_bDefault;

};




#endif // !defined(AFX_EZSKIN_H__74A45F5A_337C_4AA9_8F6A_EFD706E076B8__INCLUDED_)