// EZRuntimeClass.h: interface and implementation of the CEZRuntimeClass class.
//
/////////////////////////////////////////////////////////////////////////////////
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



//Uses Code in RClass by
// Author: Ernst Versteeg, ernst@asit.ch
//and fix suggested by ... whom?



#ifndef __EZRUNTIMECLASS_H__
#define __EZRUNTIMECLASS_H__
#include "stdafx.h"



class CEZRuntimeClass 
{
public:
	static CObject* CreateObject(CString strClassName);
	static CRuntimeClass* FindRuntimeClass( const char *szClass );

};


#endif//#ifndef __EZRUNTIMECLASS_H__

