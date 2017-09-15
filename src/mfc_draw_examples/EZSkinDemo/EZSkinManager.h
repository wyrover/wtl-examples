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

// EZSkinManager.h: interface for the CEZSkinManager class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_EZSKINMANAGER_H__83D1518B_F412_411F_9D7B_897A4A1270DC__INCLUDED_)
#define AFX_EZSKINMANAGER_H__83D1518B_F412_411F_9D7B_897A4A1270DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/*
<CLASS Name = CEZSkinManager>

  A Manager class which is redundant as the 
  CEZSkin class does seem self-reliant and
  quite independant. 
  
</CLASS>
*/
class CEZSkinManager  
{
public:
	void LoadSkin(CString strSkin = _T(""));
	CString GetSkinPath(CString strName,BOOL bValidate =TRUE);
	int EnumerateSkins(CStringArray* pstrar);

	CString GetCurrentSkinPath() const;
	virtual void Save();
	virtual void Read();
	CEZSkinManager();
	virtual ~CEZSkinManager();
private:
	CString m_strSkins;
	CString m_strCurrentSkin;

};

#endif // !defined(AFX_EZSKINMANAGER_H__83D1518B_F412_411F_9D7B_897A4A1270DC__INCLUDED_)
