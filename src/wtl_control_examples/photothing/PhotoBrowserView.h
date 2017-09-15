// PhotoThingView.h : interface of the CPhotoThingView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PHOTOTHINGVIEW_H__41231CBF_C4DD_403D_92B3_A9E4D1ECF6ED__INCLUDED_)
#define AFX_PHOTOTHINGVIEW_H__41231CBF_C4DD_403D_92B3_A9E4D1ECF6ED__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TreeView.h"
#include "InfoView.h"
#include "SearchView.h"
#include "ListPanelView.h"


class CPhotoBrowserView : 
   public ATL::CWindowImpl<CPhotoBrowserView>
{
public:
   DECLARE_WND_CLASS(_T("WTL_PhotoBrowser"))

   CPhotoTreeView m_wndTree;
   CPhotoInfoView m_wndInfo;
   CPhotoSearchView m_wndSearch;
   CFillerCtrl m_wndFiller;
   CListPanelView m_wndListPanel;
   CPhotoStatusBarCtrl m_wndStatusBar;

   BOOL m_bShowInfo;

   BOOL PreTranslateMessage(MSG* pMsg)
   {
      pMsg;
      return FALSE;
   }

   BEGIN_MSG_MAP(CPhotoBrowserView)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
      MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
      MESSAGE_HANDLER(WM_SIZE, OnSize)
      REFLECT_NOTIFICATIONS()
   END_MSG_MAP()

   LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      m_bShowInfo = TRUE;

      m_wndFiller.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, 0, (UINT) IDC_STATIC);
      m_wndTree.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | TVS_INFOTIP | TVS_TRACKSELECT | TVS_SHOWSELALWAYS | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_DISABLEDRAGDROP, 0, IDC_TREE);
      m_wndStatusBar.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, 0, IDC_STATUSBAR);
      m_wndSearch.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, 0, IDC_INFO);
      m_wndInfo.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE, 0, IDC_INFO);
      m_wndListPanel.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, 0, (UINT) IDC_STATIC);

      return 0;
   }

   LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      return 1;  // Clients fill the entire area
   }

   LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
   {
      if( !m_wndListPanel.IsWindow() ) return 0;
      const INT CX_TREEVIEW = 192;
      const INT CX_INFOVIEW = 200;
      const INT CY_SEARCHVIEW = 40;
      const INT CY_STATUSBAR = 18;
      CRect rcClient(0, 0, LOWORD(lParam), HIWORD(lParam));
      CRect rcTreeFiller(0, 0, CX_TREEVIEW, 4);
      m_wndFiller.SetWindowPos(NULL, rcTreeFiller, SWP_NOACTIVATE | SWP_NOZORDER);
      CRect rcTree(0, 4, CX_TREEVIEW, rcClient.Height() - CY_STATUSBAR);
      m_wndTree.SetWindowPos(NULL, rcTree, SWP_NOACTIVATE | SWP_NOZORDER);
      CRect rcStatusBar(0, rcClient.Height() - CY_STATUSBAR, CX_TREEVIEW, rcClient.Height());
      m_wndStatusBar.SetWindowPos(NULL, rcStatusBar, SWP_NOACTIVATE | SWP_NOZORDER);
      rcClient.left += CX_TREEVIEW;
      if( m_bShowInfo ) {
         CRect rcInfo(rcClient.right - CX_INFOVIEW, 0, rcClient.right, rcClient.Height());
         m_wndInfo.SetWindowPos(NULL, rcInfo, SWP_NOACTIVATE | SWP_NOZORDER);
      }
      rcClient.right -= CX_INFOVIEW;
      CRect rcSearch(rcClient.left, rcClient.top, rcClient.right, rcClient.top + CY_SEARCHVIEW);
      m_wndSearch.SetWindowPos(NULL, rcSearch, SWP_NOACTIVATE | SWP_NOZORDER);
      rcClient.top += CY_SEARCHVIEW;
      m_wndListPanel.SetWindowPos(NULL, rcClient, SWP_NOACTIVATE | SWP_NOZORDER);
      return 0;
   }
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHOTOTHINGVIEW_H__41231CBF_C4DD_403D_92B3_A9E4D1ECF6ED__INCLUDED_)
