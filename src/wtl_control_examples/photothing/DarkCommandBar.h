#if !defined(AFX_DARKCOMMANDBAR_H__20071124_8D3B_B2B7_F9DF_0080AD509054__INCLUDED_)
#define AFX_DARKCOMMANDBAR_H__20071124_8D3B_B2B7_F9DF_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FadeStateButton.h"


//////////////////////////////////////////////////////////////////////
// CDarkCommandButton
//

class CDarkCommandButtonCtrl : public CFadeStateButtonCtrl
{
public:
   enum 
   { 
      CX_EDGE_PADDING = 4,
      CX_TEXT_PADDING = 4,
      CX_DROPARROW = 10,
      CX_FILL_EDGE = 6,
      CX_FILL_MIDDLE = 122,
      CY_BUTTON = 29,
   };

   WTL::CBitmap m_bmpButton;

   BOOL GenerateImages(UINT uIconRes, UINT uTextRes, BOOL bHasDropdown)
   {
      ATLASSERT(m_bmpButton.IsNull());

      SetFadeButtonStyle(FSTBS_CAPTUREBKG);

      CBitmap bmpIcon;
      if( uIconRes > 0 ) bmpIcon = AtlLoadGdiplusImage(uIconRes, _T("PNG"));

      CString sText;
      if( uTextRes > 0 ) sText.LoadString(uTextRes);

      CDC dc;
      dc.CreateCompatibleDC();

      int cx = _CalculateButtonWidth(dc.m_hDC, bmpIcon.m_hBitmap, sText, bHasDropdown);

      static CBitmap bmpBtnLeft = AtlLoadGdiplusImage(IDB_BARBUTTON_LEFT, _T("PNG"));
      static CBitmap bmpBtnMiddle = AtlLoadGdiplusImage(IDB_BARBUTTON_MIDDLE, _T("PNG"));
      static CBitmap bmpBtnRight = AtlLoadGdiplusImage(IDB_BARBUTTON_RIGHT, _T("PNG"));

      CRect rcButton(0, 0, cx, CY_BUTTON);

      BITMAPINFO bmi = { 0 };
      bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      bmi.bmiHeader.biWidth = rcButton.Width() * NUM_STATES;
      bmi.bmiHeader.biHeight = rcButton.Height();
      bmi.bmiHeader.biPlanes = 1;
      bmi.bmiHeader.biBitCount = 32;
      bmi.bmiHeader.biCompression = BI_RGB;
      LPVOID pData = NULL;
      m_bmpButton.CreateDIBSection(dc, &bmi, DIB_RGB_COLORS, &pData, NULL, 0);
      if( m_bmpButton.IsNull() ) return FALSE;

      HBITMAP hOldBitmap = dc.SelectBitmap(m_bmpButton);

      CPoint ptMiddle = rcButton.CenterPoint();

      CDC dcCompat;
      dcCompat.CreateCompatibleDC();
      for( int iPart = 0; iPart < NUM_STATES; iPart++ )
      {
         int xoffset = iPart * cx;

         HBITMAP hOldBitmapC = dcCompat.SelectBitmap(bmpBtnLeft);

         // Paint background (2 edges and a stretced middle image)
         dc.SetStretchBltMode(COLORONCOLOR);
         dc.BitBlt(xoffset, 0, CX_FILL_EDGE, rcButton.Height(), dcCompat, CX_FILL_EDGE * iPart, 0, SRCCOPY);
         dcCompat.SelectBitmap(bmpBtnMiddle);
         dc.StretchBlt(xoffset + CX_FILL_EDGE, 0, cx - (CX_FILL_EDGE * 2), rcButton.Height(), dcCompat, CX_FILL_MIDDLE * iPart, 0, CX_FILL_MIDDLE, rcButton.Height(), SRCCOPY);
         dcCompat.SelectBitmap(bmpBtnRight);
         dc.BitBlt(xoffset + cx - CX_FILL_EDGE, 0, CX_FILL_EDGE, rcButton.Height(), dcCompat, CX_FILL_EDGE * iPart, 0, SRCCOPY);
         
         xoffset += CX_FILL_EDGE + CX_EDGE_PADDING;

         COLORREF clrText = RGB(255,255,255);
         if( iPart == IMAGE_DISABLED ) clrText = RGB(119,119,119);

         // Paint icon...
         if( !bmpIcon.IsNull() ) 
         {
            BITMAP bm = { 0 };
            bmpIcon.GetBitmap(&bm);
            int cxBmp = bm.bmWidth / NUM_STATES;
            dcCompat.SelectBitmap(bmpIcon);
            BLENDFUNCTION bf = { 0 };
            bf.BlendOp = AC_SRC_OVER; 
            bf.BlendFlags = 0; 
            bf.AlphaFormat = AC_SRC_ALPHA;
            bf.SourceConstantAlpha = 255;
            dc.AlphaBlend(xoffset, ptMiddle.y - (bm.bmHeight / 2), cxBmp, bm.bmHeight, dcCompat, iPart * cxBmp, 0, cxBmp, bm.bmHeight, bf);
            xoffset += cxBmp;
         }

         // Draw text...
         if( !sText.IsEmpty() ) 
         {
            HFONT hOldFont = dc.SelectFont(GetFont());
            SIZE sizeText = { 0 };
            dc.GetTextExtent(sText, sText.GetLength(), &sizeText);
            dc.SetTextColor(clrText);
            dc.SetBkMode(TRANSPARENT);
            BOOL bRes = dc.ExtTextOut(xoffset, ptMiddle.y - (sizeText.cy / 2) - 1, 0, NULL, sText);
            dc.SelectFont(hOldFont);
            xoffset += sizeText.cx;
            if( !bmpIcon.IsNull() ) xoffset += CX_TEXT_PADDING;
         }

         // Paint dropdown arrow...
         if( bHasDropdown ) 
         {
            POINT points[] =
            {
               { xoffset + 2, ptMiddle.y - 2 },
               { xoffset + 8, ptMiddle.y - 2 },
               { xoffset + 5, ptMiddle.y + 1 },
            };
            CPen pen;
            CBrush brush;
            pen.CreatePen(PS_SOLID, 1, clrText);
            brush.CreateSolidBrush(clrText);
            HPEN hOldPen = dc.SelectPen(pen);
            HBRUSH hOldBrush = dc.SelectBrush(brush);
            dc.Polygon(points, sizeof(points) / sizeof(points[0]));
            dc.SelectBrush(hOldBrush);
            dc.SelectPen(hOldPen);
            xoffset += CX_DROPARROW;
         }

         dcCompat.SelectBitmap(hOldBitmapC);
      }

      dc.SelectBitmap(hOldBitmap);

      SetBitmap(m_bmpButton);
      SizeToBitmap();

      return TRUE;
   }

   int _CalculateButtonWidth(CDCHandle dc, CBitmapHandle bmpIcon, CString sText, BOOL bHasDropdown) const
   {
      int cx = (CX_FILL_EDGE * 2) + (CX_EDGE_PADDING * 2);
      if( !bmpIcon.IsNull() ) {
         BITMAP bm = { 0 };
         bmpIcon.GetBitmap(&bm);
         cx += bm.bmWidth / NUM_STATES;
      }
      if( !sText.IsEmpty() ) {
         HFONT hOldFont = dc.SelectFont(GetFont());
         SIZE sizeText = { 0 };
         dc.GetTextExtent(sText, sText.GetLength(), &sizeText);
         dc.SelectFont(hOldFont);
         cx += sizeText.cx;
         if( !bmpIcon.IsNull() ) cx += CX_TEXT_PADDING;
      }
      if( bHasDropdown ) {
         cx += CX_DROPARROW;
      }
      return cx;
   }
};


//////////////////////////////////////////////////////////////////////
// CDarkCommandBar
//

class CDarkCommandBarCtrl : public CWindowImpl<CDarkCommandBarCtrl>
{
public:
   DECLARE_WND_CLASS(_T("WTL_DarkCommandBar"))

   CFadeStateButtonCtrl m_ctrlBack;
   CFadeStateButtonCtrl m_ctrlForward;
   CFadeStateButtonCtrl m_ctrlHelp;
   CDarkCommandButtonCtrl m_ctrlChevron;

   CFont m_fontMenu;
   TEXTMETRIC m_tmMenu;
   SIZE m_szPadding;

   typedef struct tagBUTTON
   {
      UINT uCmdID;             // WM_COMMAND ID
      UINT uTextRes;           // Label String resource ID
      UINT uIconRes;           // PNG Bitmap resource ID
      UINT uToolTipRes;        // Tooltip String resource ID
      BOOL bHasDropdown;       // Has dropdown box?
      //
      HWND hwnd;               // Handle to control
      int cx;                  // Width
      RECT rc;                 // Position
   } BUTTON;

   CSimpleValArray<BUTTON> m_aButtons;

   // Operations

   BOOL RemoveAllItems()
   {
      ATLASSERT(::IsWindow(m_hWnd));
      for( int i = 0; i < m_aButtons.GetSize(); i++ ) ::DestroyWindow(m_aButtons[i].hwnd);
      m_aButtons.RemoveAll();
      _UpdateLayout();
      return TRUE;
   }

   BOOL AddItem(BUTTON Button)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      int nItems = m_aButtons.GetSize();
      CRect rcPos(70, 4, 80, 4 + 29);
      if( nItems > 0 ) rcPos.left = m_aButtons[nItems - 1].rc.right + m_szPadding.cx;
      CDarkCommandButtonCtrl* pCtrl = new CDarkCommandButtonCtrl();
      if( pCtrl == NULL ) return FALSE;
      pCtrl->Create(m_hWnd, rcPos, _T(""), WS_CHILD, 0, Button.uCmdID);
      ATLASSERT(pCtrl->IsWindow());
      pCtrl->SetDeleteOnDestroy();
      pCtrl->SetFont(m_fontMenu);
      if( !pCtrl->GenerateImages(Button.uIconRes, Button.uTextRes, Button.bHasDropdown) ) {
         pCtrl->DestroyWindow();
         return FALSE;
      }
      if( Button.uToolTipRes > 0 ) {
         CString sText(MAKEINTRESOURCE(Button.uToolTipRes));
         pCtrl->SetToolTipText(sText);
      }
      RECT rcButton = { 0 };
      ::GetWindowRect(pCtrl->m_hWnd, &rcButton);
      ::MapWindowPoints(NULL, m_hWnd, (LPPOINT) &rcButton, 2);
      Button.hwnd = pCtrl->m_hWnd;
      Button.cx = (rcButton.right - rcButton.left) + 1;
      Button.rc = rcButton;
      m_aButtons.Add(Button);
      if( IsWindowVisible() ) _UpdateLayout();
      return TRUE;
   }

   BOOL GetItem(int iIndex, BUTTON& Button) const
   {
      if( iIndex < 0 || iIndex >= m_aButtons.GetSize() ) return FALSE;
      Button = m_aButtons[iIndex];
      return TRUE;
   }

   int GetItemCount() const
   {
      return m_aButtons.GetSize();
   }

   int IndexFromCmdId(UINT nCmdID) const
   {
      for( int i = 0; i < m_aButtons.GetSize(); i++ ) if( m_aButtons[i].uCmdID == nCmdID ) return i;
      return -1;
   }

   void SetItemEnabled(int iIndex, BOOL bEnabled)
   {
      if( iIndex < 0 || iIndex >= m_aButtons.GetSize() ) return;
      ::EnableWindow(m_aButtons[iIndex].hwnd, bEnabled);
   }

   void SetPadding(SIZE szPadding)
   {
      ATLASSERT(m_aButtons.GetSize()==0);  // Better this way
      m_szPadding = szPadding;
   }

   // Message map and handlers

   BEGIN_MSG_MAP(CDarkCommandBarCtrl)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
      MESSAGE_HANDLER(WM_PAINT, OnPaint)
      MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
      MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
      MESSAGE_HANDLER(WM_SIZE, OnSize)
      MESSAGE_HANDLER(WM_COMMAND, OnCommand)
   END_MSG_MAP()

   LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {
      ModifyStyleEx(0, WS_EX_COMPOSITED);

      // We'll grab the system font used in menus and use that as text font.
      // We should interrogate the size and stuff also.
      CLogFont lf;
      lf.SetMenuFont();
      m_fontMenu.CreateFontIndirect(&lf);
      CClientDC dc = m_hWnd;
      SetFont(m_fontMenu);
      dc.SelectFont(m_fontMenu);
      dc.GetTextMetrics(&m_tmMenu);

      CRect rcBack(2, 2, 2 + 30, 2 + 29);
      m_ctrlBack.Create(m_hWnd, rcBack, _T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 0, IDC_NAV_BACK);
      m_ctrlBack.SetFadeButtonStyle(FSTBS_CAPTUREBKG);
      m_ctrlBack.SetBitmap(IDB_BAR_LEFT, _T("PNG"));
      m_ctrlBack.SetToolTipText(CString(MAKEINTRESOURCE(IDS_NAVBACK)));
      m_ctrlBack.SizeToBitmap();

      CRect rcForward(32, 2, 32 + 30, 2 + 29);
      m_ctrlForward.Create(m_hWnd, rcForward, _T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 0, IDC_NAV_FORWARD);
      m_ctrlForward.SetFadeButtonStyle(FSTBS_CAPTUREBKG);
      m_ctrlForward.SetBitmap(IDB_BAR_RIGHT, _T("PNG"));
      m_ctrlForward.SetToolTipText(CString(MAKEINTRESOURCE(IDS_NAVFORWARD)));
      m_ctrlForward.EnableWindow(FALSE);
      m_ctrlForward.SizeToBitmap();

      m_ctrlChevron.Create(m_hWnd, rcDefault, _T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 0, IDC_NAV_CHEVRON);
      m_ctrlChevron.GenerateImages(IDB_BAR_CHEVRON, 0, FALSE);

      m_ctrlHelp.Create(m_hWnd, rcDefault, _T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 0, IDC_NAV_HELP);
      m_ctrlHelp.SetFadeButtonStyle(FSTBS_CAPTUREBKG);
      m_ctrlHelp.SetBitmap(IDB_BAR_HELP, _T("PNG"));
      m_ctrlHelp.SetToolTipText(CString(MAKEINTRESOURCE(IDS_HELP)));
      m_ctrlHelp.SizeToBitmap();

      int cyMin = m_tmMenu.tmHeight + 8;
      if( cyMin < 36 ) cyMin = 36;
      ResizeClient(-1, cyMin);

      m_szPadding.cx = 8;
      m_szPadding.cy = 2;

      bHandled = FALSE;
      return 0;
   }

   LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {
      _UpdateLayout();
      bHandled = FALSE;
      return 0;
   }

   LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
   {
      if( lParam != 0 && ::GetParent((HWND) lParam) == m_hWnd ) ::SendMessage(GetParent(), uMsg, wParam, lParam);
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

   void DoPaint(CDCHandle dc)
   {
      CRect rcClient;
      GetClientRect(&rcClient);
      dc.Draw3dRect(rcClient, RGB(133,133,133), RGB(133,133,133));
      rcClient.DeflateRect(1, 1);
      CRect rc = rcClient;
      int cyMiddle = ((rc.bottom - rc.top) / 2) + rc.top - 2;
      COLORREF clr1 = RGB(90,100,130);
      COLORREF clr2 = RGB(53,58,69);
      COLORREF clr3 = RGB(0,0,0);
      COLORREF clr4 = RGB(76,94,139);
      TRIVERTEX triv[] = {
         { rc.left,  rc.top,            (WORD)(GetRValue(clr1) << 8), (WORD)(GetGValue(clr1) << 8), (WORD)(GetBValue(clr1) << 8), 0xFF00 },
         { rc.right, rc.top + cyMiddle, (WORD)(GetRValue(clr2) << 8), (WORD)(GetGValue(clr2) << 8), (WORD)(GetBValue(clr2) << 8), 0xFF00 },
         { rc.left,  rc.top + cyMiddle, (WORD)(GetRValue(clr3) << 8), (WORD)(GetGValue(clr3) << 8), (WORD)(GetBValue(clr3) << 8), 0xFF00 },
         { rc.right, rc.bottom - 9,     (WORD)(GetRValue(clr3) << 8), (WORD)(GetGValue(clr3) << 8), (WORD)(GetBValue(clr3) << 8), 0xFF00 },
         { rc.left,  rc.bottom - 9,     (WORD)(GetRValue(clr3) << 8), (WORD)(GetGValue(clr3) << 8), (WORD)(GetBValue(clr3) << 8), 0xFF00 },
         { rc.right, rc.bottom,         (WORD)(GetRValue(clr4) << 8), (WORD)(GetGValue(clr4) << 8), (WORD)(GetBValue(clr4) << 8), 0xFF00 }
      };
      GRADIENT_RECT grc[] = { {0, 1}, {2, 3}, {4, 5} };
      dc.GradientFill(triv, sizeof(triv) / sizeof(triv[0]), &grc, sizeof(grc) / sizeof(grc[0]), GRADIENT_FILL_RECT_V);
   }

   // Implementation

   void _UpdateLayout()
   {
      if( !m_ctrlHelp.IsWindow() ) return;
      CRect rcClient;
      GetClientRect(&rcClient);
      // Place Help and Chevron button. We'll show/hide the chevron if we determine
      // that any button exceeds the commandbar width.
      CRect rcChevron(rcClient.right - 70, rcClient.top + 5, 0, 0);
      m_ctrlChevron.SetWindowPos(NULL, rcChevron, SWP_NOSIZE | SWP_NOACTIVATE);
      CRect rcHelp(rcClient.right - 30, rcClient.top + 8, 0, 0);
      m_ctrlHelp.SetWindowPos(NULL, rcHelp, SWP_NOSIZE | SWP_NOACTIVATE);
      bool bShowChevron = false;
      for( int i = 0; i < m_aButtons.GetSize(); i++ ) {
         ATLASSERT(::IsWindow(m_aButtons[i].hwnd));
         bool bShowButton = m_aButtons[i].rc.right < rcChevron.left - 5;
         ::ShowWindow(m_aButtons[i].hwnd, bShowButton ? SW_SHOWNOACTIVATE : SW_HIDE);
         if( !bShowButton ) bShowChevron = true;
      }
      m_ctrlChevron.ShowWindow(bShowChevron ? SW_SHOWNOACTIVATE : SW_HIDE);
   }
};


#endif // !defined(AFX_DARKCOMMANDBAR_H__20071124_8D3B_B2B7_F9DF_0080AD509054__INCLUDED_)

