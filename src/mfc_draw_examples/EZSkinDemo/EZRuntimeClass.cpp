#include "stdafx.h"
#include "EZRuntimeClass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CObject* CEZRuntimeClass::CreateObject(CString strClassName)
{

	CRuntimeClass* pClass = FindRuntimeClass(strClassName);
	if(!pClass) return NULL;
	return pClass->CreateObject();

	 
}

CRuntimeClass* CEZRuntimeClass::FindRuntimeClass( const char *szClass )
{
#if _MSC_VER != 1200
#pragma message( "Check if this code is still correct" )
#endif
  bool bFound=false;

  //>> Undocumented MFC, can break in next version, copy/paste from arccore.cpp line 315
  void AFXAPI AfxLockGlobals(int nLockType);
  void AFXAPI AfxUnlockGlobals(int nLockType);
  #define CRIT_RUNTIMECLASSLIST 0
	#define CRIT_DYNLINKLIST    0

  // Alleen voor Declare_serials
  AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
	AfxLockGlobals(CRIT_RUNTIMECLASSLIST);
	for ( CRuntimeClass *pClass = pModuleState->m_classList; pClass != NULL;
		pClass = pClass->m_pNextClass)
	{
		if ( lstrcmpA( szClass, pClass->m_lpszClassName) == 0 )
		{
	  bFound = true;
			break;
		}
	}
	AfxUnlockGlobals(CRIT_RUNTIMECLASSLIST);

  if ( !bFound )
  {
// This code is to check for the class in loaded DLL's
#ifdef _AFXDLL
	  // search classes in shared DLLs
	  AfxLockGlobals(CRIT_DYNLINKLIST);
	  for (CDynLinkLibrary* pDLL = pModuleState->m_libraryList; pDLL != NULL;
		  pDLL = pDLL->m_pNextDLL)
	  {
		  for (pClass = pDLL->m_classList; pClass != NULL;
			  pClass = pClass->m_pNextClass)
		  {
			  if (lstrcmpA(szClass, pClass->m_lpszClassName) == 0)
			  {
	      bFound = true;
				  break;
			  }
		  }

	 if ( bFound )
	    break;
	  }
	  AfxUnlockGlobals(CRIT_DYNLINKLIST);
#endif
  }

  //<< Undocumented MFC

  return pClass;
}

