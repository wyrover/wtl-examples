// PhotoThing.cpp : main source file for PhotoThing.exe
//

#include "stdafx.h"

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlctrlw.h>

#include "resource.h"

#include "aboutdlg.h"
#include "MainFrm.h"


CAppModule _Module;
CPhotoEngine _Photos;


int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
   CMessageLoop theLoop;
   _Module.AddMessageLoop(&theLoop);

   CMainFrame wndMain;
   if(wndMain.CreateEx() == NULL) {
      ATLTRACE(_T("Main window creation failed!\n"));
      return 0;
   }
   wndMain.ShowWindow(nCmdShow);

   int nRet = theLoop.Run();

   _Module.RemoveMessageLoop();
   return nRet;
}


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
   HRESULT hRes = ::CoInitialize(NULL);
   ATLASSERT(SUCCEEDED(hRes));

   ::DefWindowProc(NULL, 0, 0, 0L);

   AtlInitCommonControls(ICC_LISTVIEW_CLASSES | ICC_TREEVIEW_CLASSES | ICC_BAR_CLASSES);

   hRes = _Module.Init(NULL, hInstance);
   ATLASSERT(SUCCEEDED(hRes));

   ULONG uToken = 0;
   Gdiplus::GdiplusStartupInput gsi;
   Gdiplus::GdiplusStartupOutput gso;
   Gdiplus::GdiplusStartup(&uToken, &gsi, &gso);

   _Photos.Init();

   int nRet = Run(lpstrCmdLine, nCmdShow);

   _Photos.Term();

   Gdiplus::GdiplusShutdown(uToken);

   _Module.Term();
   ::CoUninitialize();

   return nRet;
}
