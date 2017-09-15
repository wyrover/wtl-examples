#if !defined(AFX_COLLECT_H__20071124_9837_81C3_BCBC_0080AD509054__INCLUDED_)
#define AFX_COLLECT_H__20071124_9837_81C3_BCBC_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ShlObj.h>


enum
{
   WM_USER_SELECTION_CHANGE  = WM_APP + 6000,
   WM_USER_ZOOM_CHANGE,
   WM_USER_IMAGE_NAVIGATE,
   WM_USER_VIEWMODE_CHANGE,
   WM_USER_TOC_CHANGE,
};


typedef struct tagPHOTOINFO
{
   WTL::CString sFilename;
   Gdiplus::Image* pImage;
   WIN32_FIND_DATA FileData;
} PHOTOINFO;


class CPhotoEngine
{
public:
   ATL::CWindow m_wndMain;
   ATL::CSimpleValArray<PHOTOINFO*> m_aFiles;
   int m_iCurSel;

   void Init()
   {
      m_iCurSel = -1;
   }
   
   void Term()
   {
      for( int i = 0; i < m_aFiles.GetSize(); i++ ) {
         delete m_aFiles[i]->pImage;
         delete m_aFiles[i];
      }
   }

   PHOTOINFO* GetImageInfo(int iIndex) const
   {
      ATLASSERT(iIndex>=0 && iIndex<m_aFiles.GetSize());
      if( iIndex < 0 || iIndex >= m_aFiles.GetSize() ) return NULL;
      return m_aFiles[iIndex];
   }

   int GetImageCount() const
   {
      return m_aFiles.GetSize();
   }

   void SendChangeNotify(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0)
   {
      // A simple method to notify all views (child windows) of a selection change.
      // Just broadcast a private message to every window in the hierarchy.
      // BUG: Don't do stuff like this!
      m_wndMain.SendMessage(uMsg, wParam, lParam);
      m_wndMain.SendMessageToDescendants(uMsg, wParam, lParam);
   }

   // Implementation

   void CollectList(HWND hWnd)
   {
      ATLASSERT(::IsWindow(hWnd));
      m_wndMain = hWnd;
      // Collect images from system folders...
      TCHAR szPath[MAX_PATH] = { 0 };
      if( ::SHGetSpecialFolderPath(hWnd, szPath, CSIDL_MYPICTURES, FALSE) ) _PopulateList(hWnd, szPath);
      if( ::SHGetSpecialFolderPath(hWnd, szPath, CSIDL_COMMON_PICTURES, FALSE) ) _PopulateList(hWnd, szPath);
   }

   void _PopulateList(HWND hWnd, LPCTSTR pstrPath)
   {
      const int MAX_FILES = 16;  // THIS IS A SAMPLE; NOT AN APPLICATION     
      if( m_aFiles.GetSize() > MAX_FILES ) return;  
      BOOL bRes;
      CFindFile ff;
      CString sPattern;
      sPattern.Format(_T("%s\\*.jpg"), pstrPath);
      for( bRes = ff.FindFile(sPattern); bRes; bRes = ff.FindNextFile() )
      {
         if( ff.IsDirectory() ) continue;
         PHOTOINFO* pPhoto = new PHOTOINFO;
         if( pPhoto == NULL ) return;
         CComBSTR bstrFilename = ff.GetFilePath();
         pPhoto->sFilename = ff.GetFilePath();
         pPhoto->pImage = new Gdiplus::Image(bstrFilename); 
         pPhoto->FileData = ff.m_fd;
         m_aFiles.Add(pPhoto);
         if( m_aFiles.GetSize() > MAX_FILES ) return;
      }
      sPattern.Format(_T("%s\\*.*"), pstrPath);
      for( bRes = ff.FindFile(sPattern); bRes; bRes = ff.FindNextFile() )
      {
         if( ff.IsDots() ) continue;
         if( !ff.IsDirectory() ) continue;
         _PopulateList(hWnd, ff.GetFilePath());
      }
   }
};


extern CPhotoEngine _Photos;



#endif // !defined(AFX_COLLECT_H__20071124_9837_81C3_BCBC_0080AD509054__INCLUDED_)

