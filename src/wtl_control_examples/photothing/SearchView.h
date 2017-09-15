#if !defined(AFX_SEARCHVIEW_H__20071124_5958_4978_A454_0080AD509054__INCLUDED_)
#define AFX_SEARCHVIEW_H__20071124_5958_4978_A454_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MiscControls.h"


class CPhotoSearchView : 
   public CWindowImpl<CPhotoSearchView>
{
public:
   DECLARE_WND_CLASS(_T("WTL_PhotoSearch"))

   CSearchEditCtrl m_ctrlSearch;
   CWinXPButton m_ctrlOptions;

   BEGIN_MSG_MAP(CPhotoSearchView)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
      MESSAGE_HANDLER(WM_SIZE, OnSize)
      MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
      MESSAGE_HANDLER(WM_INITMENUPOPUP, OnInitMenuPopup)
      COMMAND_ID_HANDLER(ID_VIEW_OPTIONS, OnViewOptions)
      COMMAND_ID_HANDLER(ID_VIEW_THUMBNAILS, OnViewModeChange)
      COMMAND_ID_HANDLER(ID_VIEW_THUMBTEXT, OnViewModeChange)
      COMMAND_ID_HANDLER(ID_VIEW_TILES, OnViewModeChange)
      COMMAND_ID_HANDLER(ID_VIEW_CONTENTS, OnViewTocChange)
   END_MSG_MAP()

   LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      m_ctrlSearch.Create(m_hWnd, rcDefault, _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, IDC_SEARCHFILTER);

      m_ctrlOptions.Create(m_hWnd, rcDefault, _T(""), WS_CHILD | WS_VISIBLE, 0, ID_VIEW_OPTIONS);
      m_ctrlOptions.SetBkColor(RGB(238,243,250));
      m_ctrlOptions.GenerateImages(_T(""), IDB_RESET, TRUE);

      return 0;
   }

   LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      CClientDC dc = m_hWnd;
      CRect rcClient;
      dc.GetClipBox(&rcClient);
      dc.FillSolidRect(&rcClient, RGB(238,243,250));
      return 1;
   }

   LRESULT OnInitMenuPopup(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
   {
      CWindow wndTop = GetTopLevelWindow();
      wndTop.SendMessage(uMsg, wParam, lParam);  // Allow MainFrm to UI-update the menu
      return 0;
   }

   LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
   {
      const INT CX_SIZEFIELD = 180;
      const INT CY_SEARCH = 22;
      CClientDC dc = m_hWnd;
      CRect rcClient(0,0,LOWORD(lParam), HIWORD(lParam));
      INT cxEdit = rcClient.Width() - 50;
      if( cxEdit > CX_SIZEFIELD ) cxEdit = CX_SIZEFIELD;
      CRect rcSearch(rcClient.right - 10 - cxEdit, rcClient.top + 10, rcClient.right - 10, rcClient.top + 10 + CY_SEARCH);
      m_ctrlSearch.SetWindowPos(NULL, &rcSearch, SWP_NOACTIVATE);
      CRect rcOptionsWin;
      m_ctrlOptions.GetWindowRect(&rcOptionsWin);
      CRect rcOptions(rcSearch.left - 10 - rcOptionsWin.Width(), rcSearch.CenterPoint().y - (rcOptionsWin.Height() / 2), rcSearch.left - 10, rcSearch.CenterPoint().y + (rcOptionsWin.Height() / 2));
      m_ctrlOptions.SetWindowPos(NULL, &rcOptions, SWP_NOACTIVATE);
      return 0;
   }

   LRESULT OnViewOptions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      CRect rcButton;
      m_ctrlOptions.GetWindowRect(&rcButton);
      TPMPARAMS tpmp = { sizeof(tpmp) };
      rcButton.bottom -= 1;
      tpmp.rcExclude = rcButton;
      CMenu menu;
      menu.LoadMenu(IDM_OPTIONS);
      CMenuHandle submenu = menu.GetSubMenu(0);
      m_ctrlOptions.EnableWindow(FALSE);
      TrackPopupMenuEx(submenu, TPM_LEFTBUTTON, rcButton.left, rcButton.bottom, m_hWnd, &tpmp);
      m_ctrlOptions.EnableWindow(TRUE);
      return 0;
   }

   LRESULT OnViewModeChange(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      _Photos.SendChangeNotify(WM_USER_VIEWMODE_CHANGE, wID);
      return 0;
   }

   LRESULT OnViewTocChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      _Photos.SendChangeNotify(WM_USER_TOC_CHANGE);
      return 0;
   }
};


#endif // !defined(AFX_SEARCHVIEW_H__20071124_5958_4978_A454_0080AD509054__INCLUDED_)
