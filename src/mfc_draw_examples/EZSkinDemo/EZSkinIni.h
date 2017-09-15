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

// Built On CIni class by Iuri Apollonio
//------------------------------------------------------------------------------------------//

// EZSkinIni.h: interface for the CEZSkinIni class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_EZSKININI_H__8FE39045_5DD1_4765_BCAD_1C0FAAA0BC62__INCLUDED_)
#define AFX_EZSKININI_H__8FE39045_5DD1_4765_BCAD_1C0FAAA0BC62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include  "EZSkin_I.h"

/*<CLASS Name = CEZSkinIni>
	
Implementation of IEZSkinIni Interface
This class uses an Inifile toimplement the
serialization interface of EZSkin

</CLASS>*/
class CEZSkinIni  :public IEZSkinIni
{
DECLARE_SERIAL(CEZSkinIni)
public:


	CEZSkinIni();
	virtual ~CEZSkinIni();


public:
//IEZSkinIni	
//{
	
	virtual BOOL GetValue(CString strSection,CString strKey,COLORREF& clrValue);
	virtual BOOL GetValue(CString strSection, CString strKey, int& nValue);
	virtual BOOL GetValue(CString strSection,CString strKey, CString& strValue);
	virtual BOOL GetValue(CString strSection, CString strKey, CPoint& ptValue);

	virtual BOOL Read(CString strFile);
//}

protected:

	//{Helpers
	BOOL IsSection(int nSection);
	int FindItem(const int iSection, CString  strItem, CString &strVal);
	int FindSection(CString strSection,int nStartFrom = 0);
	//}	

private:
	CStringArray m_strar;

};

#endif // !defined(AFX_EZSKININI_H__8FE39045_5DD1_4765_BCAD_1C0FAAA0BC62__INCLUDED_)
