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

#ifndef __EZSKIN_I_H__
#define __EZSKIN_I_H__


/////////////////////////////////////////////////////////////////////////////////
//  IEZSkinIni  
///////////////////////////////////////////////////////////////////////////////////
class IEZSkinIni :public CObject 
{
DECLARE_SERIAL(IEZSkinIni)
public:

	virtual BOOL GetValue(CString strSection,CString strKey,COLORREF& clrValue)
	
	{
		ASSERT(FALSE);
		return FALSE;
	}
	virtual BOOL GetValue(CString strSection, CString strKey, int& nValue)
	
	{
		ASSERT(FALSE);
		return FALSE;
	}
	
	virtual BOOL GetValue(CString strSection,CString strKey, CString& strValue)
	
	{
		ASSERT(FALSE);
		return FALSE;
	}
	
	virtual BOOL GetValue(CString strSection, CString strKey, CPoint& ptValue)
	
	{
		ASSERT(FALSE);
		return FALSE;

	}
	virtual BOOL Read(CString strPath)
	
	{
		ASSERT(FALSE);
		return FALSE;
	}


};

/////////////////////////////////////////////////////////////////////////////////
// IEZSkinComponent
//
/////////////////////////////////////////////////////////////////////////////////

class IEZSkinComponent : public CObject
{

	DECLARE_SERIAL(IEZSkinComponent)

public:

	virtual BOOL Load(IEZSkinIni* pIni,BOOL bLoadDefaultOnFailure  = TRUE) 

	{
		ASSERT(FALSE);
		return FALSE;
	}

	virtual BOOL LoadDefault() 
	
	{
		ASSERT(FALSE);
		return FALSE;
	}
	virtual void Destroy() 

	{
		ASSERT(FALSE);
	}

	virtual BOOL IsLoaded()

	{
		ASSERT(FALSE);
		return FALSE;
	}
	virtual BOOL IsDefault()

	{
		ASSERT(FALSE);
		return TRUE;
	}

};





#endif //#ifndef __EZSKIN_I_H__
