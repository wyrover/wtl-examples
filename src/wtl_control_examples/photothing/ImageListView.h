#if !defined(AFX_IMAGELISTVIEW_H__20071124_F900_7525_9162_0080AD509054__INCLUDED_)
#define AFX_IMAGELISTVIEW_H__20071124_F900_7525_9162_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPhotoImageListView : 
   public ATL::CWindowImpl<CPhotoImageListView, WTL::CListViewCtrl>,
   public WTL::CTheme
{
public:
   DECLARE_WND_CLASS(_T("WTL_PhotoList"))

   enum { CX_ICON_DEFAULT = 102 };

   WTL::CImageList m_Images;
   UINT m_uViewType;
   int m_cxIcon;

   CPhotoImageListView() : m_cxIcon(CX_ICON_DEFAULT), m_uViewType(ID_VIEW_THUMBNAILS)
   {
   }

   ~CPhotoImageListView()
   {
      m_Images.Destroy();
   }

   BEGIN_MSG_MAP(CPhotoImageListView)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
      MESSAGE_HANDLER(WM_INITMENUPOPUP, OnInitMenuPopup)
      MESSAGE_HANDLER(WM_USER_ZOOM_CHANGE, OnZoomChange)      
      MESSAGE_HANDLER(WM_USER_IMAGE_NAVIGATE, OnImageNavigate)
      MESSAGE_HANDLER(WM_USER_VIEWMODE_CHANGE, OnViewModeChange)      
      COMMAND_ID_HANDLER(ID_VIEW_THUMBNAILS, OnViewModeChange)
      COMMAND_ID_HANDLER(ID_VIEW_THUMBTEXT, OnViewModeChange)
      COMMAND_ID_HANDLER(ID_VIEW_TILES, OnViewModeChange)
      COMMAND_ID_HANDLER(ID_VIEW_CONTENTS, OnViewTocChange)
      COMMAND_ID_HANDLER(ID_VIEW_SELECTALL, OnViewSelectAll)
      REFLECTED_NOTIFY_CODE_HANDLER(LVN_ITEMCHANGED, OnItemChanged)
      REFLECTED_NOTIFY_CODE_HANDLER(NM_RCLICK, OnRightClick)
   END_MSG_MAP()

   LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      LRESULT lRes = DefWindowProc();

      ModifyStyle(0, LVS_ALIGNTOP | LVS_SHAREIMAGELISTS);

      SetBkColor(RGB(238,243,250));
      SetTextBkColor(RGB(238,243,250));
      SetViewType(LV_VIEW_ICON);
      SetExtendedListViewStyle(LVS_EX_DOUBLEBUFFER, LVS_EX_DOUBLEBUFFER);
      if( IsThemingSupported() ) SetWindowTheme(m_hWnd, L"Explorer", NULL);

      _PopulateList(TRUE);

      return lRes;
   }

   LRESULT OnInitMenuPopup(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
   {
      CWindow wndTop = GetTopLevelWindow();
      wndTop.SendMessage(uMsg, wParam, lParam);  // Allow MainFrm to UI-update the menu
      return 0;
   }

   LRESULT OnZoomChange(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
   {
      int iZoom = (int) lParam;
      BOOL bHighQuality = (wParam == 1);
      _SetIconSize(iZoom);
      _PopulateList(bHighQuality);
      return 0;
   }

   LRESULT OnViewModeChange(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      UINT uViewType = wParam;
      SetFocus();
      _SetViewType(uViewType);
      _PopulateList(TRUE);
      return 0;
   }

   LRESULT OnImageNavigate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
   {
#ifndef LVNI_VISIBLEORDER
      const UINT LVNI_VISIBLEORDER     = 0x0010;
      const UINT LVNI_PREVIOUS         = 0x0020;
#endif // LVNI_VISIBLEORDER
      SetFocus();
      int iItem = GetNextItem(-1, LVNI_SELECTED);
      iItem = GetNextItem(iItem, lParam == 1 ? LVNI_ALL|LVNI_VISIBLEORDER : LVNI_ALL|LVNI_VISIBLEORDER|LVNI_PREVIOUS);
      SetItemState(-1, 0, LVIS_SELECTED | LVIS_FOCUSED);
      SetItemState(iItem, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVIS_FOCUSED);
      EnsureVisible(iItem, FALSE);
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

   LRESULT OnViewSelectAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      SetItemState(-1, LVIS_SELECTED, LVIS_SELECTED);
      return 0;
   }

   LRESULT OnItemChanged(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
   {
      CSimpleValArray<PHOTOINFO*> list;
      for( int iItem = GetNextItem(-1, LVNI_SELECTED); iItem != -1; iItem = GetNextItem(iItem, LVNI_SELECTED) ) {
         PHOTOINFO* pInfo = (PHOTOINFO*) GetItemData(iItem);
         if( pInfo == NULL ) continue;
         list.Add(pInfo);
      }
      _Photos.SendChangeNotify(WM_USER_SELECTION_CHANGE, (WPARAM) list.GetSize(), (LPARAM) list.GetData());
      return 0;
   }

   LRESULT OnRightClick(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
   {
      CMenu menu;
      menu.LoadMenu(IDM_LISTVIEW);
      CMenuHandle submenu = menu.GetSubMenu(0);
      CPoint pt(::GetMessagePos());
      TrackPopupMenu(submenu, TPM_LEFTBUTTON, pt.x, pt.y, 0, m_hWnd, NULL);
      return 0;
   }

   // Implementation

   void _SetViewType(UINT uType)
   {
      if( uType == 0 ) uType = ID_VIEW_THUMBNAILS;
      m_uViewType = uType;
   }

   void _SetIconSize(int cx)
   {
      if( cx <= 0 ) cx = CX_ICON_DEFAULT;
      m_cxIcon = cx;
   }

   void _PopulateList(BOOL bHighQualityThumbnails = TRUE)
   {
      USES_CONVERSION;

      bHighQualityThumbnails;

      int cyIcon = 18 + (int)(m_cxIcon * 0.7);                                        // Height is proportionally less
      int cyOffset = 16;                                                              // Nice large gap at top
      double dblScale = 1.0;                                                          // Thumb is full scale
      if( m_uViewType == ID_VIEW_THUMBTEXT ) dblScale = 0.8;                          // Thumb with text is slightly smaller
      if( m_uViewType == ID_VIEW_TILES ) dblScale = 0.7, cyIcon -= 16, cyOffset = 2;  // Tiled mode have compact look

      SetRedraw(FALSE);

      DeleteAllItems();
      RemoveAllGroups();
      while( DeleteColumn(0) ) /* */;
      
      if( !m_Images.IsNull() ) m_Images.Destroy();
      m_Images.Create(m_cxIcon, cyIcon, ILC_COLOR32, _Photos.GetImageCount(), 0);
      SetImageList(m_Images, LVSIL_NORMAL);

      SetIconSpacing(m_cxIcon + 20, cyIcon + 26);

      for( int iGroupId = 2020; iGroupId >= 1990; --iGroupId ) {
         CString sGroup;
         sGroup.Format(_T("%d"), iGroupId);
         LVGROUP group;
         group.cbSize = sizeof(LVGROUP);
         group.mask = LVGF_HEADER | LVGF_GROUPID | LVGF_STATE;
         group.pszHeader = const_cast<LPWSTR>(T2CW(sGroup));
#ifndef LVGS_COLLAPSIBLE
         const UINT LVGS_COLLAPSIBLE = 8;
#endif // LVGS_COLLAPSIBLE
         group.state = LVGS_COLLAPSIBLE;
         group.stateMask = LVGS_COLLAPSIBLE;
         group.iGroupId = iGroupId;
         InsertGroup(-1, &group);
      }

      LVGROUPMETRICS gm = { 0 };
      gm.cbSize = sizeof(gm);
      gm.mask = LVGMF_TEXTCOLOR;
      GetGroupMetrics(&gm);
      gm.mask = LVGMF_TEXTCOLOR;
      gm.crHeader = RGB(145,148,152);
      SetGroupMetrics(&gm);

      EnableGroupView(TRUE);

      if( m_uViewType == ID_VIEW_TILES ) {
         InsertColumn(0, _T("Title"));
         InsertColumn(1, _T("Date"));
         InsertColumn(2, _T("Size"));
         SetView(LV_VIEW_TILE);
         LVTILEVIEWINFO lvtvi = { 0 };
         lvtvi.cbSize = sizeof(LVTILEVIEWINFO);
         lvtvi.dwMask = LVTVIM_COLUMNS | LVTVIM_TILESIZE;
         lvtvi.dwFlags = LVTVIF_AUTOSIZE;
         lvtvi.cLines = 2;
         SetTileViewInfo(&lvtvi);
      }
      else {
         SetView(LV_VIEW_ICON);
      }

      for( int iIndex = 0; iIndex < _Photos.GetImageCount(); iIndex++ ) 
      {
         PHOTOINFO* pInfo = _Photos.GetImageInfo(iIndex);

         // Create thumbnail icon for imagelist
         CIcon icon;
         int cxThumb = (int)(m_cxIcon * dblScale);
         int cyThumb = (int)(cyIcon * dblScale);
         Gdiplus::Image* pThumb = pInfo->pImage->GetThumbnailImage(cxThumb, cyIcon);
         if( pThumb != NULL ) {
            Gdiplus::Bitmap bm24bpp(cxThumb, cyThumb); 
            Gdiplus::Graphics g(&bm24bpp);
            Gdiplus::Pen penShadow1(Gdiplus::Color(183,187,192));
            Gdiplus::SolidBrush brBack(Gdiplus::Color(0,238,243,250));
            Gdiplus::Rect rcThumb(0, 0, cxThumb, cyIcon);
            g.FillRectangle(&brBack, rcThumb);
            g.DrawRectangle(&penShadow1, 2, cyOffset + 1, cxThumb - 3, cyThumb - cyOffset - 2);
            g.DrawImage(pThumb, 0, cyOffset, cxThumb - 2, cyThumb - cyOffset - 2); 
            Gdiplus::Pen penWhite(Gdiplus::Color(255,255,255));
            Gdiplus::Pen penGrey(Gdiplus::Color(228,228,228));
            g.DrawRectangle(&penGrey, 0, cyOffset, cxThumb - 2, cyThumb - cyOffset - 2);
            g.DrawRectangle(&penWhite, 1, cyOffset + 1, cxThumb - 4, cyThumb - cyOffset - 4);
            g.DrawRectangle(&penWhite, 2, cyOffset + 2, cxThumb - 6, cyThumb - cyOffset - 6);
            bm24bpp.GetHICON(&icon.m_hIcon);
            delete pThumb;
         }
         m_Images.AddIcon(icon);

         // Extract creation-time (fallback to filetime if no Exif data found)
         SYSTEMTIME stFileTime = { 0 };
         ::FileTimeToSystemTime(&pInfo->FileData.ftCreationTime, &stFileTime);
         CString sImageDate;
         if( sImageDate.IsEmpty() ) GdipGetBitmapProperty(pInfo->pImage, PropertyTagExifDTOrig, sImageDate);
         if( sImageDate.IsEmpty() ) GdipGetBitmapProperty(pInfo->pImage, PropertyTagDateTime, sImageDate);         
         if( sImageDate.IsEmpty() ) sImageDate.Format(_T("%02d:%02d:%02d %02d:%02d:%02d"), (int) stFileTime.wYear, (int) stFileTime.wMonth, (int) stFileTime.wDay, (int) stFileTime.wHour, (int) stFileTime.wMinute, (int) stFileTime.wSecond);

         int iGroupId = (int) stFileTime.wYear;
         if( !sImageDate.IsEmpty() ) iGroupId = _ttoi(sImageDate);

         // Insert list item...
         LVITEM item = { 0 };
         item.iItem = iIndex;
         item.mask = LVIF_IMAGE | LVIF_PARAM | LVIF_GROUPID;
         item.iImage = iIndex;
         if( m_uViewType == ID_VIEW_THUMBTEXT ) {
            item.mask |= LVIF_TEXT;
            item.pszText = (LPTSTR) static_cast<LPCTSTR>(sImageDate);
         }
         if( m_uViewType == ID_VIEW_TILES ) {
            item.mask |= LVIF_TEXT;
            item.pszText = pInfo->FileData.cFileName;
         }
         item.lParam = (LPARAM) pInfo;
         item.iGroupId = iGroupId;
         InsertItem(&item);
      
         if( m_uViewType == ID_VIEW_TILES ) {
            LONGLONG llFileSize = pInfo->FileData.nFileSizeLow;
            WCHAR szwSize[30] = { 0 };
            ::StrFormatByteSizeW(llFileSize, szwSize, sizeof(szwSize) / sizeof(TCHAR));
            SetItemText(item.iItem, 1, sImageDate);
            SetItemText(item.iItem, 2, CString(szwSize));
            UINT aCols[] = { 2, 1 };
            LVTILEINFO lvti = { sizeof(LVTILEINFO), item.iItem, sizeof(aCols) / sizeof(aCols[0]), aCols };
            SetTileInfo(&lvti);
         }
      }

      SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
      SetRedraw(TRUE);
      Invalidate();
   }
};


#endif // !defined(AFX_IMAGELISTVIEW_H__20071124_F900_7525_9162_0080AD509054__INCLUDED_)

