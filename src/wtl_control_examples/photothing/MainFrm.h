// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__4CE54B7F_350B_4FF5_8FB4_5B245CBD75BB__INCLUDED_)
#define AFX_MAINFRM_H__4CE54B7F_350B_4FF5_8FB4_5B245CBD75BB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "DarkCommandBar.h"
#include "NavPanelView.h"
#include "PhotoBrowserView.h"


class CMainFrame : 
   public WTL::CFrameWindowImpl<CMainFrame>, 
   public WTL::CUpdateUI<CMainFrame>,
   public WTL::CMessageFilter, 
   public WTL::CIdleHandler,
   public CVistaDwm
{
public:
   DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

   CDarkCommandBarCtrl m_ctrlCmdBar;
   CPhotoBrowserView m_viewClient;
   CNavPanelView m_viewNavPanel;
   UINT m_uViewType;
   BOOL m_bShowTOC;

   enum { NAVPANEL_HEIGHT = 60 };

   CMainFrame() : m_uViewType(ID_VIEW_THUMBNAILS), m_bShowTOC(TRUE)
   {
   }

   virtual BOOL PreTranslateMessage(MSG* pMsg)
   {
      if( CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg) ) return TRUE;
      if( m_viewClient.IsWindow() ) return m_viewClient.PreTranslateMessage(pMsg);
      return FALSE;
   }

   virtual BOOL OnIdle()
   {
      UISetCheck(ID_VIEW_CONTENTS,   m_bShowTOC);
      UISetCheck(ID_VIEW_TILES,      m_uViewType == ID_VIEW_TILES);
      UISetCheck(ID_VIEW_THUMBTEXT,  m_uViewType == ID_VIEW_THUMBTEXT);
      UISetCheck(ID_VIEW_THUMBNAILS, m_uViewType == ID_VIEW_THUMBNAILS);
      return FALSE;
   }

   BEGIN_UPDATE_UI_MAP(CMainFrame)
      UPDATE_ELEMENT(ID_VIEW_CONTENTS, UPDUI_MENUPOPUP)
      UPDATE_ELEMENT(ID_VIEW_TILES, UPDUI_MENUPOPUP)
      UPDATE_ELEMENT(ID_VIEW_THUMBTEXT, UPDUI_MENUPOPUP)
      UPDATE_ELEMENT(ID_VIEW_THUMBNAILS, UPDUI_MENUPOPUP)
   END_UPDATE_UI_MAP()

   BEGIN_MSG_MAP(CMainFrame)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
      MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
      MESSAGE_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo)
      MESSAGE_HANDLER(WM_PAINT, OnPaint)
      MESSAGE_HANDLER(WM_USER_SELECTION_CHANGE, OnSelectionChange)
      MESSAGE_HANDLER(WM_USER_VIEWMODE_CHANGE, OnViewModeChange)
      MESSAGE_HANDLER(WM_USER_TOC_CHANGE, OnViewTocChange)
      COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
      COMMAND_ID_HANDLER(ID_FILE_NEW, OnFileNew)
      COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
      CHAIN_MSG_MAP( CUpdateUI<CMainFrame> )
      CHAIN_MSG_MAP( CFrameWindowImpl<CMainFrame> )
   END_MSG_MAP()

   LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      _Photos.CollectList(m_hWnd);

      CMessageLoop* pLoop = _Module.GetMessageLoop();
      ATLASSERT(pLoop!=NULL);
      pLoop->AddMessageFilter(this);
      pLoop->AddIdleHandler(this);

      if( IsCompositionEnabled() ) {
         DWM_MARGINS margins = { 0 };
         margins.cyBottomHeight = NAVPANEL_HEIGHT;
         ExtendFrameIntoClientArea(m_hWnd, margins);
      }

      m_ctrlCmdBar.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPSIBLINGS, 0);
      m_viewClient.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CONTROLPARENT);
      m_viewNavPanel.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CONTROLPARENT);

      CDarkCommandBarCtrl::BUTTON Buttons[] = 
      { 
         { ID_BAR_FILE,  IDS_BAR_FILE,  IDB_BARITEM_FILE,  0, TRUE },
         { ID_BAR_EDIT,  IDS_BAR_EDIT,  IDB_BARITEM_EDIT,  0, FALSE },
         { ID_BAR_INFO,  IDS_BAR_INFO,  IDB_BARITEM_INFO,  0, FALSE },
         { ID_BAR_PRINT, IDS_BAR_PRINT, IDB_BARITEM_PRINT, 0, TRUE },
         { ID_BAR_EMAIL, IDS_BAR_EMAIL, IDB_BARITEM_EMAIL, 0, FALSE },
         { ID_BAR_BURN,  IDS_BAR_BURN,  IDB_BARITEM_BURN,  0, TRUE },
         { ID_BAR_MOVIE, IDS_BAR_MOVIE, IDB_BARITEM_MOVIE, 0, FALSE },
      };
      for( int i = 0; i< sizeof(Buttons) / sizeof(Buttons[0]); i++ ) m_ctrlCmdBar.AddItem(Buttons[i]);

      return 0;
   }

   LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {
      CMessageLoop* pLoop = _Module.GetMessageLoop();
      ATLASSERT(pLoop!=NULL);
      pLoop->RemoveMessageFilter(this);
      pLoop->RemoveIdleHandler(this);
      bHandled = FALSE;
      return 0;
   }

   LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      CPaintDC dc(m_hWnd);

      CRect rcClient;
      GetClientRect(&rcClient);

      // Paint the glass-area if needed so it becomes transparent
      if( IsCompositionEnabled() ) {
         rcClient.top = rcClient.bottom - NAVPANEL_HEIGHT;
         dc.FillSolidRect(rcClient, RGB(0,0,0));
      }

      return 0;
   }

   LRESULT OnSelectionChange(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      BOOL bHasSelection = (wParam > 0);
      m_ctrlCmdBar.SetItemEnabled(m_ctrlCmdBar.IndexFromCmdId(ID_BAR_EDIT), bHasSelection);
      m_ctrlCmdBar.SetItemEnabled(m_ctrlCmdBar.IndexFromCmdId(ID_BAR_BURN), bHasSelection);
      m_ctrlCmdBar.SetItemEnabled(m_ctrlCmdBar.IndexFromCmdId(ID_BAR_EMAIL), bHasSelection);
      m_ctrlCmdBar.SetItemEnabled(m_ctrlCmdBar.IndexFromCmdId(ID_BAR_PRINT), bHasSelection);
      m_ctrlCmdBar.SetItemEnabled(m_ctrlCmdBar.IndexFromCmdId(ID_BAR_MOVIE), bHasSelection);
      if( m_viewNavPanel.IsWindow() ) {
         m_viewNavPanel.m_ctrlDelete.EnableWindow(bHasSelection);
         m_viewNavPanel.m_ctrlRotateLeft.EnableWindow(bHasSelection);
         m_viewNavPanel.m_ctrlRotateRight.EnableWindow(bHasSelection);
      }
      return 0;
   }

   LRESULT OnViewModeChange(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      m_uViewType = wParam;
      return 0;
   }

   LRESULT OnViewTocChange(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      m_bShowTOC = !m_bShowTOC;
      return 0;
   }

   LRESULT OnGetMinMaxInfo(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
   {
      LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
      lpMMI->ptMinTrackSize.x = 680;
      lpMMI->ptMinTrackSize.y = 540;
      return 0;
   }

   LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      PostMessage(WM_CLOSE);
      return 0;
   }

   LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      // TODO: add code to initialize document
      return 0;
   }

   LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      CAboutDlg dlg;
      dlg.DoModal();
      return 0;
   }

   // Implementation

   void UpdateLayout(BOOL /*bResizeBars*/ = TRUE)
   {
      CRect rcClient;
      GetClientRect(&rcClient);

      CRect rcCmdBarWin;
      m_ctrlCmdBar.GetWindowRect(&rcCmdBarWin);
      CRect rcCmdBar = rcClient;
      rcCmdBar.bottom = rcCmdBar.top + rcCmdBarWin.Height();
      m_ctrlCmdBar.SetWindowPos(NULL, &rcCmdBar, SWP_NOZORDER | SWP_NOACTIVATE);
      rcClient.top = rcCmdBar.bottom;

      CRect rcNavPanel = rcClient;
      rcNavPanel.top = rcClient.bottom - NAVPANEL_HEIGHT;
      m_viewNavPanel.SetWindowPos(NULL, &rcNavPanel, SWP_NOZORDER | SWP_NOACTIVATE);
      rcClient.bottom = rcNavPanel.top;

      CRect rcView = rcClient;
      m_viewClient.SetWindowPos(NULL, &rcView, SWP_NOZORDER | SWP_NOACTIVATE);
   }
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__4CE54B7F_350B_4FF5_8FB4_5B245CBD75BB__INCLUDED_)
