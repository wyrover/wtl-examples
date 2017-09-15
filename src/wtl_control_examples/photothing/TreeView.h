#if !defined(AFX_TREEVIEW_H__20071124_EA30_AFD8_C67D_0080AD509054__INCLUDED_)
#define AFX_TREEVIEW_H__20071124_EA30_AFD8_C67D_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef TVS_EX_MULTISELECT
   #define TVS_EX_MULTISELECT    0x0002  
   #define TVS_EX_DOUBLEBUFFER   0x0004 
   #define TVS_EX_NOINDENTSTATE  0x0008 
   #define TVS_EX_RICHTOOLTIP    0x0010 
   #define TVS_EX_AUTOHSCROLL    0x0020 
#endif // TVS_EX_MULTISELECT


class CPhotoTreeView : 
   public CWindowImpl<CPhotoTreeView, CTreeViewCtrl>,
   public CCustomDraw<CPhotoTreeView>,
   public CTheme
{
public:
   DECLARE_WND_CLASS(_T("WTL_PhotoTree"))

   enum { CXY_ICON = 16 };

   CImageList m_TreeImages;
   CFont m_fontItalic;

   BEGIN_MSG_MAP(CPhotoTreeView)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
      MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
      CHAIN_MSG_MAP_ALT( CCustomDraw<CPhotoTreeView>, 1 )
   END_MSG_MAP()

   LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      LRESULT lRes = DefWindowProc();

      CBitmap bmpImages = AtlLoadBitmapImage(IDB_TREEIMAGES, LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
      CBitmap bmpMask = AtlLoadBitmapImage(IDB_TREEIMAGES_MASK, LR_MONOCHROME);
      m_TreeImages.Create(CXY_ICON, CXY_ICON, ILC_COLOR24 | ILC_MASK, 16, 0);
      m_TreeImages.Add(bmpImages, bmpMask);

      CLogFont lf = GetFont();
      lf.lfItalic = 1;
      m_fontItalic.CreateFontIndirect(&lf);

      SetBkColor(RGB(238,243,250));
      SetImageList(m_TreeImages);
#ifndef TVM_SETEXTENDEDSTYLE
	  const UINT TVM_SETEXTENDEDSTYLE = 4396;
#endif // TVM_SETEXTENDEDSTYLE
      SendMessage(TVM_SETEXTENDEDSTYLE, TVS_EX_AUTOHSCROLL | TVS_EX_MULTISELECT | TVS_EX_DOUBLEBUFFER, TVS_EX_MULTISELECT | TVS_EX_DOUBLEBUFFER);
      if( IsThemingSupported() ) SetWindowTheme(m_hWnd, L"Explorer", NULL);

      _PopulateTree();

      return lRes;
   }

   LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {
      m_TreeImages.Destroy();
      bHandled = FALSE;
      return 0;
   }

   // Custom Draw support

   DWORD OnPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
   {
      return CDRF_NOTIFYITEMDRAW;
   }

   DWORD OnItemPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW lpNMCustomDraw)
   {
      switch( lpNMCustomDraw->lItemlParam ) {
      case 1: // Show with italic font
         ::SelectObject(lpNMCustomDraw->hdc, m_fontItalic);
         return CDRF_NEWFONT;
      case 2:
      case 3:
      case 4:
      case 5: // Show stars
         return CDRF_NOTIFYPOSTPAINT;
      }
      return CDRF_DODEFAULT;
   }

   DWORD OnItemPostPaint(int /*idCtrl*/, LPNMCUSTOMDRAW lpNMCustomDraw)
   {
      HTREEITEM hItem = (HTREEITEM) lpNMCustomDraw->dwItemSpec;
      CRect rc = lpNMCustomDraw->rc;
      CDCHandle dc = lpNMCustomDraw->hdc;
      switch( lpNMCustomDraw->lItemlParam ) {
      case 2:
      case 3:
      case 4:
      case 5:
         {
            RECT rcItem = { 0 };
            GetItemRect(hItem, &rcItem, TRUE);
            int nStars = lpNMCustomDraw->lItemlParam;
            POINT pt = { rcItem.left - 2, rcItem.top + 1 };
            for( int i = 1; i < nStars; i++ ) {
               m_TreeImages.Draw(dc, 10, pt, ILD_TRANSPARENT);
               pt.x += CXY_ICON + 1;
            }
            return CDRF_DODEFAULT;
         }
      }
      return CDRF_DODEFAULT;
   }

   // Implementation

   // Returns string of "empty spaces" to match the size of the icons
   CString _GetStarFillerText(int nStars) const
   {      
      CString sText;
      const int cxIcons = nStars * (CXY_ICON + 1);
      CClientDC dc = m_hWnd;
      HFONT hOldFont = dc.SelectFont(GetFont());
      for( int i = 1; true; i++ ) {
         CString sEmpty(' ', i);
         SIZE sizeText = { 0 };
         dc.GetTextExtent(sEmpty, sEmpty.GetLength(), &sizeText);
         if( sizeText.cx >= cxIcons ) { sText = sEmpty; break; }
      }
      dc.SelectFont(hOldFont);
      return sText;
   }

   void _PopulateTree()
   {
#define STR(nRes) CString(MAKEINTRESOURCE(nRes))

      HTREEITEM hItem;
      UINT uItemStyle = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
      hItem = InsertItem(uItemStyle, STR(IDS_TREE_PICTURESVIDEOS),    0, 0, 0, 0, 0L, TVI_ROOT, TVI_LAST);
              InsertItem(uItemStyle, STR(IDS_TREE_PICTURES),          1, 1, 0, 0, 0L, hItem, TVI_LAST);
              InsertItem(uItemStyle, STR(IDS_TREE_VIDEO),             2, 2, 0, 0, 0L, hItem, TVI_LAST);
              InsertItem(uItemStyle, STR(IDS_TREE_RECENTLYIMPORTED),  3, 3, 0, 0, 0L, TVI_ROOT, TVI_LAST);
              Expand(hItem, TVE_EXPAND);
      hItem = InsertItem(uItemStyle, STR(IDS_TREE_TAGS),              4, 4, 0, 0, 0L, TVI_ROOT, TVI_LAST);
              InsertItem(uItemStyle, STR(IDS_TREE_CREATETAG),         5, 5, 0, 0, 1L, hItem, TVI_LAST);
              InsertItem(uItemStyle, STR(IDS_TREE_NOTTAGGED),         6, 6, 0, 0, 0L, hItem, TVI_LAST);
              InsertItem(uItemStyle, _T("Flowers"),                   7, 7, 0, 0, 0L, hItem, TVI_LAST);
              InsertItem(uItemStyle, _T("Landscape"),                 7, 7, 0, 0, 0L, hItem, TVI_LAST);
              InsertItem(uItemStyle, _T("Ocean"),                     7, 7, 0, 0, 0L, hItem, TVI_LAST);
              InsertItem(uItemStyle, _T("Sample"),                    7, 7, 0, 0, 0L, hItem, TVI_LAST);
              Expand(hItem, TVE_EXPAND);
      hItem = InsertItem(uItemStyle, STR(IDS_TREE_DATETAKEN),         8, 8, 0, 0, 0L, TVI_ROOT, TVI_LAST);
              InsertItem(uItemStyle, _T("2004"),                      9, 9, 0, 0, 0L, hItem, TVI_LAST);
              InsertItem(uItemStyle, _T("2005"),                      9, 9, 0, 0, 0L, hItem, TVI_LAST);
              InsertItem(uItemStyle, _T("2006"),                      9, 9, 0, 0, 0L, hItem, TVI_LAST);
              InsertItem(uItemStyle, _T("2007"),                      9, 9, 0, 0, 0L, hItem, TVI_LAST);
              Expand(hItem, TVE_EXPAND);
      hItem = InsertItem(uItemStyle, STR(IDS_TREE_RATINGS),           10, 10, 0, 0, 0L, TVI_ROOT, TVI_LAST);
              InsertItem(uItemStyle, _GetStarFillerText(4),           10, 10, 0, 0, 5L, hItem, TVI_LAST);
              InsertItem(uItemStyle, _GetStarFillerText(3),           10, 10, 0, 0, 4L, hItem, TVI_LAST);
              InsertItem(uItemStyle, _GetStarFillerText(2),           10, 10, 0, 0, 3L, hItem, TVI_LAST);
              InsertItem(uItemStyle, _GetStarFillerText(1),           10, 10, 0, 0, 2L, hItem, TVI_LAST);
              InsertItem(uItemStyle, _T(""),                          10, 10, 0, 0, 0L, hItem, TVI_LAST);
              InsertItem(uItemStyle, STR(IDS_TREE_NOTRATED),          15, 15, 0, 0, 0L, hItem, TVI_LAST);
              Expand(hItem, TVE_EXPAND);
      hItem = InsertItem(uItemStyle, STR(IDS_TREE_FOLDERS),           11, 11, 0, 0, 0L, TVI_ROOT, TVI_LAST);
              InsertItem(uItemStyle, STR(IDS_TREE_FOLDER_PICTURE),    12, 12, 0, 0, 0L, hItem, TVI_LAST);
              InsertItem(uItemStyle, STR(IDS_TREE_FOLDER_VIDEO),      13, 13, 0, 0, 0L, hItem, TVI_LAST);
              InsertItem(uItemStyle, STR(IDS_TREE_FOLDER_PUBPICTURE), 14, 14, 0, 0, 0L, hItem, TVI_LAST);
              InsertItem(uItemStyle, STR(IDS_TREE_FOLDER_PUBVIDEO),   14, 14, 0, 0, 0L, hItem, TVI_LAST);
              Expand(hItem, TVE_EXPAND);
   }
};


#endif // !defined(AFX_TREEVIEW_H__20071124_EA30_AFD8_C67D_0080AD509054__INCLUDED_)

