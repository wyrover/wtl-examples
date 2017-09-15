#if !defined(AFX_PHOTOINFOPANEL_H__20071124_FB1B_E65B_F727_0080AD509054__INCLUDED_)
#define AFX_PHOTOINFOPANEL_H__20071124_FB1B_E65B_F727_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MiscControls.h"


//////////////////////////////////////////////////////////////////////
// CPhotoInfoView
//

class CPhotoInfoView : 
   public ATL::CWindowImpl<CPhotoInfoView>
{
public:
   DECLARE_WND_CLASS(_T("WTL_PhotoInfo"))

   enum
   {
      UPDATE_TIMERID = 40,
      CX_PREVIEW = 90,
      CY_PREVIEW = 90,
   };

   CInfoButtonCtrl m_ctrlName;
   CInfoButtonCtrl m_ctrlDate;
   CInfoButtonCtrl m_ctrlTime;
   CInfoButtonCtrl m_ctrlSize;
   CStarRatingCtrl m_ctrlRating;
   CInfoButtonCtrl m_ctrlAddKeyword;
   CSeparatorCtrl m_ctrlSep1;
   CSeparatorCtrl m_ctrlSep2;
   CKeywordListCtrl m_ctrlKeywords;
   CSeparatorCtrl m_ctrlSep3;
   CInfoButtonCtrl m_ctrlDescription;

   CPhotoInfoView() : m_pPicture(NULL)
   {
   }

   Gdiplus::Bitmap* m_pPicture;
   WTL::CBitmap m_bmpEmptyPicture;
   WTL::CBitmap m_bmpShadow;

   ATL::CSimpleArray<PHOTOINFO*> m_aSelected;

   BEGIN_MSG_MAP(CPhotoInfoView)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
      MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
      MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
      MESSAGE_HANDLER(WM_PAINT, OnPaint)
      MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
      MESSAGE_HANDLER(WM_USER_SELECTION_CHANGE, OnSelectionChange)
      MESSAGE_HANDLER(WM_TIMER, OnTimer)
      MESSAGE_HANDLER(WM_SIZE, OnSize)
      REFLECT_NOTIFICATIONS()
   END_MSG_MAP()

   LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {
      ModifyStyleEx(0, WS_EX_COMPOSITED);
      
      m_bmpShadow = AtlLoadGdiplusImage(IDB_INFOSHADOW, _T("PNG"));
      m_bmpEmptyPicture = AtlLoadGdiplusImage(IDB_EMPTYSELECTION, _T("PNG"));

      m_ctrlName.Create(m_hWnd, rcDefault, _T(""),        WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, IDC_INFONAME);
      m_ctrlDate.Create(m_hWnd, rcDefault, _T(""),        WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, IDC_INFODATE);
      m_ctrlTime.Create(m_hWnd, rcDefault, _T(""),        WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, IDC_INFOTIME);
      m_ctrlSize.Create(m_hWnd, rcDefault, _T(""),        WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, IDC_INFOSIZE);
      m_ctrlRating.Create(m_hWnd, rcDefault, _T(""),      WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, IDC_RATING);
      m_ctrlAddKeyword.Create(m_hWnd, rcDefault, _T(""),  WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, IDC_ADDKEYWORD);
      m_ctrlSep1.Create(m_hWnd, rcDefault, NULL,          WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, (UINT) IDC_STATIC);
      m_ctrlSep2.Create(m_hWnd, rcDefault, NULL,          WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, (UINT) IDC_STATIC);
      m_ctrlKeywords.Create(m_hWnd, rcDefault, NULL,      WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | LVS_REPORT, 0, IDC_KEYWORDS);
      m_ctrlSep3.Create(m_hWnd, rcDefault, NULL,          WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, (UINT) IDC_STATIC);
      m_ctrlDescription.Create(m_hWnd, rcDefault, _T(""), WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, IDC_INFODESCRIPTION);

      bHandled = FALSE;
      return 0;
   }

   LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {  
      _ClearThumbnail();
      bHandled = FALSE;
      return 0;
   }

   LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      return 1;
   }

   LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      if( wParam != NULL )
      {
         DoPaint((HDC) wParam);
      }
      else
      {
         CPaintDC dc(m_hWnd);
         DoPaint(dc.m_hDC);
      }
      return 0;
   }

   LRESULT OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
   {
      bHandled = FALSE;
      if( wParam != UPDATE_TIMERID ) return 0;
      KillTimer(UPDATE_TIMERID);
     
      _GenerateThumbnail();
      _UpdateInfoFields();
     
      Invalidate();
      return 0;
   }

   LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
   {
      CRect rcClient(0,0,LOWORD(lParam), HIWORD(lParam));
      _UpdateLayout(rcClient);
      return 0;
   }

   LRESULT OnSelectionChange(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
   {
      PHOTOINFO** ppInfo = (PHOTOINFO**) lParam;
      int nCount = (int) wParam;
      // We'll delay the rendering of the thumbnails a bit because the ListView might be
      // firing multiple selection-changes.
      m_aSelected.RemoveAll();
      for( int i = 0; i < nCount; i++ ) m_aSelected.Add(ppInfo[i]);
      SetTimer(UPDATE_TIMERID, 100UL);
      return 0;
   }

   // Implementation

   void DoPaint(CDCHandle dc)
   {

      CRect rcClient;
      GetClientRect(&rcClient);
      POINT ptMiddle = rcClient.CenterPoint();

      const int cyShadeHalf = 200;
      COLORREF clrFirst = RGB(207,218,231);
      COLORREF clrSecond = RGB(238,243,250);
      TRIVERTEX triv[2] = {
         { rcClient.left,  rcClient.top,               (WORD)(GetRValue(clrFirst) << 8),  (WORD)(GetGValue(clrFirst) << 8),  (WORD)(GetBValue(clrFirst) << 8), 0xFF00 },
         { rcClient.right, rcClient.top + cyShadeHalf, (WORD)(GetRValue(clrSecond) << 8), (WORD)(GetGValue(clrSecond) << 8), (WORD)(GetBValue(clrSecond) << 8), 0xFF00 }
      };
      GRADIENT_RECT grc = { 0, 1 };
      dc.GradientFill(triv, sizeof(triv) / sizeof(triv[0]), &grc, 1, GRADIENT_FILL_RECT_V);
      CRect rcBottom(rcClient.left, rcClient.top + cyShadeHalf, rcClient.right, rcClient.bottom);
      dc.FillSolidRect(&rcBottom, clrSecond);

      rcClient.top += 40;

      // Display the thumbnail thingy...
      if( m_pPicture != NULL ) {
         Gdiplus::Graphics g(dc);
         g.DrawImage(m_pPicture, ptMiddle.x - (m_pPicture->GetWidth() / 2) + 10, rcClient.top, m_pPicture->GetWidth(), m_pPicture->GetHeight());
         rcClient.top += m_pPicture->GetWidth() - 26;
      }

      // Display standard "select stuff" text when no image selection was
      // made in the list.
      if( m_aSelected.GetSize() == 0 ) {
         CString sText;
         sText.Format(IDS_NOIMAGES, _Photos.GetImageCount());
         CRect rcText(rcClient.left + 10, rcClient.top, rcClient.right - 10, rcClient.bottom);
         HFONT hOldFont = dc.SelectFont(AtlGetDefaultShellFont());
         dc.SetBkMode(TRANSPARENT);
         dc.SetTextColor(RGB(0,0,0));
         dc.DrawText(sText, sText.GetLength(), &rcText, DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
         dc.SelectFont(hOldFont);
      }

      if( !m_ctrlName.m_bitmap.IsNull() )
      {
         CDC dcCompat;
         dcCompat.CreateCompatibleDC();
         HBITMAP hOldBmp = dcCompat.SelectBitmap(m_ctrlName.m_bitmap);
         BLENDFUNCTION bf = { 0 };
         bf.BlendOp = AC_SRC_OVER; 
         bf.BlendFlags = 0; 
         bf.AlphaFormat = AC_SRC_ALPHA;
         bf.SourceConstantAlpha = 255;      
         CRect rc(40,200,170,300);
         dc.AlphaBlend(rc.left, rc.top, rc.Width(), rc.Height(), dcCompat, 0, 0,130,100, bf);      
         dcCompat.SelectBitmap(hOldBmp);
      }
   }

   void _UpdateLayout(CRect rcClient)
   {
      if( m_aSelected.GetSize() == 0 ) return;
      int cxMiddle = rcClient.left + (rcClient.Width() / 2);
      _PlaceControl(m_ctrlName, cxMiddle, 108);
      _PlaceControl(m_ctrlDate, cxMiddle - 30, 132);
      _PlaceControl(m_ctrlTime, cxMiddle + 36, 132);
      _PlaceControl(m_ctrlSize, cxMiddle, 156);
      _PlaceControl(m_ctrlRating, cxMiddle, 181);
      _PlaceControl(m_ctrlSep1, cxMiddle, 206);
      _PlaceControl(m_ctrlAddKeyword, cxMiddle, 216);
      _PlaceControl(m_ctrlSep2, cxMiddle, 246);
      _PlaceControl(m_ctrlKeywords, cxMiddle, 256);
      _PlaceControl(m_ctrlSep3, cxMiddle, rcClient.bottom - 54);
      _PlaceControl(m_ctrlDescription, cxMiddle,rcClient.bottom - 45);
   }

   void _UpdateInfoFields()
   {
      // Place child windows - unless there is no selection and we
      // just hide them all.
      if( m_aSelected.GetSize() == 0 || m_pPicture == NULL )
      {
         m_ctrlName.ShowWindow(SW_HIDE);
         m_ctrlDate.ShowWindow(SW_HIDE);
         m_ctrlTime.ShowWindow(SW_HIDE);
         m_ctrlSize.ShowWindow(SW_HIDE);
         m_ctrlRating.ShowWindow(SW_HIDE);
         m_ctrlAddKeyword.ShowWindow(SW_HIDE);
         m_ctrlSep1.ShowWindow(SW_HIDE);
         m_ctrlSep2.ShowWindow(SW_HIDE);
         m_ctrlKeywords.ShowWindow(SW_HIDE);
         m_ctrlSep3.ShowWindow(SW_HIDE);
         m_ctrlDescription.ShowWindow(SW_HIDE);
      }
      else
      {
         CRect rcClient;
         GetClientRect(&rcClient);

         PHOTOINFO* pInfo = m_aSelected[0];

         LPCTSTR pstrFileName = pInfo->FileData.cFileName;

         SYSTEMTIME stFileTime = { 0 };
         ::FileTimeToSystemTime(&pInfo->FileData.ftCreationTime, &stFileTime);
         CString sImageDate;
         if( sImageDate.IsEmpty() ) GdipGetBitmapProperty(pInfo->pImage, PropertyTagExifDTOrig, sImageDate);
         if( sImageDate.IsEmpty() ) GdipGetBitmapProperty(pInfo->pImage, PropertyTagDateTime, sImageDate);         
         if( !sImageDate.IsEmpty() && sImageDate.GetLength() >= 18 ) {
            LPCTSTR pstrDate = sImageDate;
            stFileTime.wYear = (WORD) _ttoi(pstrDate);
            stFileTime.wMonth = (WORD) _ttoi(pstrDate + 5);
            stFileTime.wDay = (WORD) _ttoi(pstrDate + 8);
            stFileTime.wHour = (WORD) _ttoi(pstrDate + 11);
            stFileTime.wMinute = (WORD) _ttoi(pstrDate + 14);
            stFileTime.wSecond = (WORD) _ttoi(pstrDate + 18);
         }
         TCHAR szDate[20] = { 0 };
         TCHAR szTime[20] = { 0 };
         ::GetDateFormat(LOCALE_USER_DEFAULT, DATE_SHORTDATE, &stFileTime, NULL, szDate, sizeof(szDate) / sizeof(TCHAR));
         ::GetTimeFormat(LOCALE_USER_DEFAULT, TIME_NOSECONDS, &stFileTime, NULL, szTime, sizeof(szTime) / sizeof(TCHAR));         

         LONGLONG llFileSize = pInfo->FileData.nFileSizeLow;
         WCHAR szwTemp[30] = { 0 };
         ::StrFormatByteSizeW(llFileSize, szwTemp, sizeof(szwTemp) / sizeof(TCHAR));
         CString sSize;
         sSize.Format(_T("%ls (%ldx%ld)"), szwTemp, pInfo->pImage->GetWidth(), pInfo->pImage->GetHeight());

         CString sDescription;
         if( sDescription.IsEmpty() ) GdipGetBitmapProperty(pInfo->pImage, PropertyTagImageDescription, sDescription);
         if( sDescription.IsEmpty() ) GdipGetBitmapProperty(pInfo->pImage, PropertyTagExifMakerNote, sDescription);
         if( sDescription.IsEmpty() ) GdipGetBitmapProperty(pInfo->pImage, PropertyTagExifUserComment, sDescription);
         if( sDescription.IsEmpty() ) GdipGetBitmapProperty(pInfo->pImage, PropertyTagImageTitle, sDescription);

         /*
         ULONG aIDs[200] = { 0 };
         pInfo->pImage->GetPropertyIdList(pInfo->pImage->GetPropertyCount(), aIDs);
         for( UINT i = 0; i< pInfo->pImage->GetPropertyCount(); i++ ) ATLTRACE("ExifID: %d %04X\n", aIDs[i], aIDs[i]);
         */

         m_ctrlName.GenerateImages(pstrFileName);
         m_ctrlName.SizeToBitmap();
         m_ctrlDate.GenerateImages(szDate);
         m_ctrlDate.SizeToBitmap();
         m_ctrlTime.GenerateImages(szTime);
         m_ctrlTime.SizeToBitmap();
         m_ctrlSize.GenerateImages(sSize);
         m_ctrlSize.SizeToBitmap();
         m_ctrlSize.EnableWindow(FALSE);
         m_ctrlAddKeyword.GenerateImages(CString(MAKEINTRESOURCE(IDS_ADDKEYWORD)), IDB_ADDKEYWORD, 180);
         m_ctrlAddKeyword.SizeToBitmap();
         m_ctrlSep1.ResizeClient(rcClient.Width() - 30, 6);
         m_ctrlSep2.ResizeClient(rcClient.Width() - 30, 6);
         int cyList = rcClient.Height() - 246 - 60;
         m_ctrlKeywords.ResizeClient(rcClient.Width() - 20, cyList);
         m_ctrlSep3.ResizeClient(rcClient.Width() - 30, 6);
         m_ctrlDescription.GenerateImages(sDescription, 0, rcClient.Width() - 30, 40);
         m_ctrlDescription.SizeToBitmap();
         
         // Place controls now...
         _UpdateLayout(rcClient);
      }
   }

   BOOL _PlaceControl(HWND hWnd, int x, int y)
   {
      ATLASSERT(::IsWindow(hWnd));
      CRect rcControl;
      ::GetWindowRect(hWnd, &rcControl);
      CRect rcWin;
      GetWindowRect(&rcWin);
      CRect rcNew;
      rcNew.left = rcWin.left + x - (rcControl.Width() / 2);         
      rcNew.right = rcNew.left + rcControl.Width();
      rcNew.top = rcWin.top + y;
      rcNew.bottom = rcNew.top + rcControl.Height();
      ::MapWindowPoints(NULL, m_hWnd, (LPPOINT) &rcNew, 2);
      return ::SetWindowPos(hWnd, NULL, rcNew.left, rcNew.top, rcNew.Width(), rcNew.Height(), SWP_NOACTIVATE | SWP_SHOWWINDOW);
   }

   void _ClearThumbnail()
   {
      delete m_pPicture; 
      m_pPicture = NULL;
   }

   void _GenerateThumbnail()
   {
      const int CX_ICON = 72;
      const int CY_ICON = 60;

      _ClearThumbnail();
     
      int nSel = m_aSelected.GetSize();

      // The thumbnail portraits a stack of images. No more than
      // 3 images are shown though.
      int nStack = nSel;
      if( nStack > 3 ) nStack = 3;
      if( nStack <= 0 ) nStack = 1;

      Gdiplus::Status s;
      Gdiplus::Bitmap bm24bpp(CX_ICON + 12, CY_ICON + 12);
      Gdiplus::Graphics g(&bm24bpp);
      Gdiplus::Pen penGrey(Gdiplus::Color(228,228,228));
      Gdiplus::Pen penWhite(Gdiplus::Color(255,255,255));
      Gdiplus::Pen penShadow1(Gdiplus::Color(183,187,192));
      for( int i = nStack - 1; i >= 0; --i ) {
         const INT CXY_FRAME = 3;
         POINT ptOffset = { i * CXY_FRAME, (CXY_FRAME * 3) - (i * CXY_FRAME) };
         int cyFrame = CY_ICON - 8;
         g.DrawRectangle(&penShadow1, ptOffset.x + 2, ptOffset.y + 1, CX_ICON - 3, cyFrame);
         if( i == 0 ) {
            Gdiplus::Image* pImage = NULL;
            Gdiplus::Image* pTempImage = NULL;
            if( nSel > 0 ) pImage = m_aSelected[i]->pImage;
            else pImage = pTempImage = Gdiplus::Bitmap::FromHBITMAP(m_bmpEmptyPicture, NULL);
            if( pImage == NULL ) break;
            Gdiplus::Image* pThumb = pImage->GetThumbnailImage(CX_ICON, CY_ICON - 4);
            if( pThumb == NULL ) break;
            s = g.DrawImage(pThumb, ptOffset.x, ptOffset.y, CX_ICON - 2, CY_ICON - 2); 
            delete pTempImage;
         }
         g.DrawRectangle(&penGrey, ptOffset.x, ptOffset.y, CX_ICON - 2, cyFrame);
         g.DrawRectangle(&penWhite, ptOffset.x + 1, ptOffset.y + 1, CX_ICON - 4, cyFrame - 2);
         g.DrawRectangle(&penWhite, ptOffset.x + 2, ptOffset.y + 2, CX_ICON - 6, cyFrame - 4);
      }

      Gdiplus::TextureBrush brIcon(&bm24bpp, Gdiplus::WrapModeTile);
      Gdiplus::Bitmap bmIcon(CX_PREVIEW, CY_PREVIEW);
      Gdiplus::Graphics gIcon(&bmIcon);

      //Gdiplus::Image* pShadowImage = Gdiplus::Bitmap::FromHBITMAP(m_bmpShadow, NULL);
      //gIcon.DrawImage(pShadowImage, 69 + (nStack * CXY_FRAME), 49 - (nStack * CXY_FRAME));

      Gdiplus::Matrix matrix(1, 0, 0, -1, 0, 0);  // Flip shadow
      brIcon.SetTransform(&matrix);
      gIcon.TranslateTransform(0.0f, 42.0f);

      Gdiplus::Bitmap bmGrad(90, 50);
      Gdiplus::Graphics gGrad(&bmGrad);
      Gdiplus::Rect rcGrad(0, 5, 90, 35);
      Gdiplus::LinearGradientBrush lgb(rcGrad, Gdiplus::Color(210, 255,255,255), Gdiplus::Color(0, 255,255,255), Gdiplus::LinearGradientModeVertical);
      s = gGrad.FillRectangle(&lgb, rcGrad);
  
      Gdiplus::Bitmap bmShadow(90, 50);
      Gdiplus::Graphics gShadow(&bmShadow);
      Gdiplus::GraphicsPath gp2;
      gp2.AddLine(0,  12,      80, 12 + 4);
      gp2.AddLine(80, 12 + 4,  80, 40);
      gp2.AddLine(80, 40,      0, 40);
      gp2.AddLine(0,  40,      0, 0);
      s = gShadow.FillPath(&brIcon, &gp2);

      // Extract alpha-channel from gradient brush bitmap and transfer
      // to shadow bitmap...
      Gdiplus::BitmapData bmdB;
      Gdiplus::BitmapData bmdA;
      bmShadow.LockBits(&rcGrad, Gdiplus::ImageLockModeWrite, PixelFormat32bppARGB, &bmdB);
      bmGrad.LockBits(&rcGrad, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bmdA);
      DWORD* pPixelsB = (DWORD*) bmdB.Scan0;
      DWORD* pPixelsA = (DWORD*) bmdA.Scan0;
      for( int x = 0; x < 90; x++ ) {
         for( int y = 5; y < 45; y++ ) {
            DWORD c = pPixelsB[y * bmdB.Stride / 4 + x];
            if( c == 0 ) continue;
            DWORD a = pPixelsA[y * bmdA.Stride / 4 + x];
            c &= 0x00FFFFFF;
            c |= (a & 0xFF000000);
            pPixelsB[y * bmdB.Stride / 4 + x] = c;
         }
      }
      bmGrad.UnlockBits(&bmdA);
      bmShadow.UnlockBits(&bmdB);

      gIcon.DrawImage(&bmShadow, 0, 0);

      brIcon.ResetTransform();
      gIcon.TranslateTransform(0.0f, -42.0f);

      Gdiplus::GraphicsPath gp1;
      gp1.AddLine(0,  0,       80, 0);
      gp1.AddLine(80, 0,       80, 60);
      gp1.AddLine(80, 60,      0,  60 - 8);
      gp1.AddLine(0,  60 - 8,  0,  0);
      s = gIcon.FillPath(&brIcon, &gp1);

      // FIX: Gdiplus::FillPath wouldn't skew the bitmap brush; sadly even GDI
      //      can do this. We'll have to compensate with manual smoothing...
      gIcon.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
      gIcon.DrawLine(&penWhite, 2, CY_ICON - 7, CX_ICON - 4, CY_ICON - 1);
      gIcon.DrawLine(&penWhite, 2, CY_ICON - 6, CX_ICON - 4, CY_ICON);
      gIcon.SetSmoothingMode(Gdiplus::SmoothingModeDefault);

      m_pPicture = bmIcon.Clone(0,0,CX_PREVIEW,CY_PREVIEW, PixelFormat32bppARGB);
   }
};


#endif // !defined(AFX_PHOTOINFOPANEL_H__20071124_FB1B_E65B_F727_0080AD509054__INCLUDED_)

