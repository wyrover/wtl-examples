#if !defined(AFX_TABLEOFCONTENTSVIEW_H__20071124_88BC_66A4_AAC7_0080AD509054__INCLUDED_)
#define AFX_TABLEOFCONTENTSVIEW_H__20071124_88BC_66A4_AAC7_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTabelOfContentsView : 
   public ATL::CWindowImpl<CTabelOfContentsView>
{
public:
   DECLARE_WND_CLASS(_T("WTL_TableOfContents"))

   CTabelOfContentsView() : m_iHoverItem(-1), m_bTracking(false)
   {
   }

   typedef struct tagCONTENTITEM
   {
      CString sName;                    // Name of group
      int nDots;                        // Dots shown below group
      RECT rcText;                      // Text position and area
   } CONTENTITEM;

   bool m_bTracking;                    // Is tracking mouse?
   int m_iHoverItem;                    // Currently highlighted (hot) item
   CSimpleArray<CONTENTITEM> m_aItems;  // Content Groups

   BEGIN_MSG_MAP(CTabelOfContentsView)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
      MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
      MESSAGE_HANDLER(WM_PAINT, OnPaint)
      MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
      MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
      MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
   END_MSG_MAP()

   LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      ModifyStyleEx(0, WS_EX_COMPOSITED);

      _PopulateList();

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

   LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
   {
      if( !m_bTracking ) {
         _StartTrackMouseLeave();
         m_bTracking = true;
      }
      CPoint pt(lParam);
      int iHoverItem = -1;
      for( int i = 0; i < m_aItems.GetSize(); i++ ) {
         if( ::PtInRect(&m_aItems[i].rcText, pt) ) iHoverItem = i;
      }
      if( iHoverItem != m_iHoverItem ) {
         m_iHoverItem = iHoverItem;
         Invalidate();
      }
      return 0;
   }

   LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      m_bTracking = false;
      m_iHoverItem = -1;
      Invalidate();
      return 0;
   }

   void DoPaint(CDCHandle dc)
   {
      CRect rcClient;
      GetClientRect(&rcClient);

      dc.FillSolidRect(&rcClient, RGB(238,243,250));

      rcClient.right -= 5;

      // Gradient border on the right side
      CRect rcBorder(rcClient.right, rcClient.top + 30, rcClient.right, rcClient.bottom - 30);
      int cyHalf = rcBorder.CenterPoint().y;
      COLORREF clrBorder1 = RGB(238,243,250);
      COLORREF clrBorder2 = RGB(162,162,162);
      TRIVERTEX triv1[] = {
         { rcBorder.right - 1,  rcBorder.top,     (WORD)(GetRValue(clrBorder1) << 8), (WORD)(GetGValue(clrBorder1) << 8), (WORD)(GetBValue(clrBorder1) << 8), 0xFF00 },
         { rcBorder.right,      cyHalf,           (WORD)(GetRValue(clrBorder2) << 8), (WORD)(GetGValue(clrBorder2) << 8), (WORD)(GetBValue(clrBorder2) << 8), 0xFF00 },
         { rcBorder.right - 1,  rcBorder.bottom,  (WORD)(GetRValue(clrBorder1) << 8), (WORD)(GetGValue(clrBorder1) << 8), (WORD)(GetBValue(clrBorder1) << 8), 0xFF00 },
      };
      GRADIENT_RECT grc1[] = { {0, 1}, {1, 2} };
      dc.GradientFill(triv1, sizeof(triv1) / sizeof(triv1[0]), grc1, sizeof(grc1) / sizeof(grc1[0]), GRADIENT_FILL_RECT_V);
      rcClient.right -= 1;

      // Scroll area indicator
      CRect rcStripe(rcClient.left, rcClient.top + 40, rcClient.right, rcClient.top + 80);
      COLORREF clrStripe1 = RGB(238,243,250);
      COLORREF clrStripe2 = RGB(182,217,251);
      TRIVERTEX triv2[] = {
         { rcStripe.left,  rcStripe.top,         (WORD)(GetRValue(clrStripe1) << 8), (WORD)(GetGValue(clrStripe1) << 8), (WORD)(GetBValue(clrStripe1) << 8), 0xFF00 },
         { rcStripe.right, rcStripe.top + 10,    (WORD)(GetRValue(clrStripe2) << 8), (WORD)(GetGValue(clrStripe2) << 8), (WORD)(GetBValue(clrStripe2) << 8), 0xFF00 },
         { rcStripe.left,  rcStripe.bottom - 10, (WORD)(GetRValue(clrStripe2) << 8), (WORD)(GetGValue(clrStripe2) << 8), (WORD)(GetBValue(clrStripe2) << 8), 0xFF00 },
         { rcStripe.right, rcStripe.bottom,      (WORD)(GetRValue(clrStripe1) << 8), (WORD)(GetGValue(clrStripe1) << 8), (WORD)(GetBValue(clrStripe1) << 8), 0xFF00 },
      };
      GRADIENT_RECT grc2[] = { {0, 1}, {1, 2}, {2, 3} };
      dc.GradientFill(triv2, sizeof(triv2) / sizeof(triv2[0]), grc2, sizeof(grc2) / sizeof(grc2[0]), GRADIENT_FILL_RECT_V);

      // Scroll arrows (not functional in this demo)
      POINT ptTop = { rcClient.CenterPoint().x, rcClient.top + 3 };
      POINT ptBottom = { rcClient.CenterPoint().x, rcClient.bottom - 12 };
      POINT ptUpArrow[] = 
      {
         { ptTop.x - 5, ptTop.y + 5 },
         { ptTop.x,     ptTop.y },
         { ptTop.x + 5, ptTop.y + 5 },
      };
      POINT ptDownArrow[] = 
      {
         { ptBottom.x - 5, ptBottom.y - 5 },
         { ptBottom.x,     ptBottom.y },
         { ptBottom.x + 5, ptBottom.y - 5 },
      };
      COLORREF clrArrow = RGB(178,182,187);
      CPen penArrow;
      CBrush brArrow;
      penArrow.CreatePen(PS_SOLID, 2, clrArrow);
      brArrow.CreateSolidBrush(clrArrow);
      HPEN hOldPen = dc.SelectPen(penArrow);
      HBRUSH hOldBrush = dc.SelectBrush(brArrow);
      dc.Polyline(ptUpArrow, sizeof(ptUpArrow) / sizeof(ptUpArrow[0]));
      dc.Polyline(ptDownArrow, sizeof(ptDownArrow) / sizeof(ptDownArrow[0]));

      rcClient.top += 20;
      rcClient.bottom -= 20;

      HFONT hOldFont = dc.SelectFont( AtlGetDefaultShellFont() );
      TEXTMETRIC tm = { 0 };
      dc.GetTextMetrics(&tm);
      dc.SetBkMode(TRANSPARENT);
      POINT pt = { rcClient.left, rcClient.top };
      for( int iItem = 0; iItem < m_aItems.GetSize(); iItem++ ) 
      {
         CONTENTITEM& Item = m_aItems[iItem];
         
         COLORREF clrText = RGB(0,0,0);
         if( iItem == m_iHoverItem ) clrText = RGB(0,102,204);
         dc.SetTextColor(clrText);
         CRect rcText(pt.x, pt.y, pt.x + rcClient.Width() - 10, pt.y + 20);
         dc.DrawText(Item.sName, -1, &rcText, DT_RIGHT | DT_SINGLELINE);
         CRect rcSize = rcText;
         dc.DrawText(Item.sName, -1, &rcSize, DT_RIGHT | DT_SINGLELINE | DT_CALCRECT);
         Item.rcText = rcText;
         Item.rcText.left = Item.rcText.right - rcSize.Width();
         Item.rcText.bottom = Item.rcText.top + rcSize.Height();

         POINT ptBlock = { pt.x + rcClient.Width() - 10 - 3, pt.y + tm.tmHeight + 4 };
         for( int x = 0; x < Item.nDots; x++ ) {
            CRect rcBlock(ptBlock.x, ptBlock.y, ptBlock.x + 3, ptBlock.y + 5);
            COLORREF clrBlock = RGB(107,179,254);
            dc.FillSolidRect(rcBlock, clrBlock);
            ptBlock.x -= 4;
         }

         pt.y += tm.tmHeight + 25;
      }

      dc.SelectBrush(hOldBrush);
      dc.SelectPen(hOldPen);
      dc.SelectFont(hOldFont);
   }

   // Implementation

   void _PopulateList()
   {
      m_aItems.RemoveAll();

      CONTENTITEM Item;
      Item.sName = _T("2006"); Item.nDots = 5; m_aItems.Add(Item);
      Item.sName = _T("2005"); Item.nDots = 3; m_aItems.Add(Item);
      Item.sName = _T("2004"); Item.nDots = 2; m_aItems.Add(Item);
   }

   BOOL _StartTrackMouseLeave()
   {
      TRACKMOUSEEVENT tme = { 0 };
      tme.cbSize = sizeof(tme);
      tme.dwFlags = TME_LEAVE;
      tme.hwndTrack = m_hWnd;
      return _TrackMouseEvent(&tme);
   }
};


#endif // !defined(AFX_TABLEOFCONTENTSVIEW_H__20071124_88BC_66A4_AAC7_0080AD509054__INCLUDED_)
