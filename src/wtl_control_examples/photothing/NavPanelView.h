#if !defined(AFX_NAVPANELVIEW_H__20071124_6783_43DF_E667_0080AD509054__INCLUDED_)
#define AFX_NAVPANELVIEW_H__20071124_6783_43DF_E667_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MiscControls.h"


class CNavPanelView : 
   public ATL::CWindowImpl<CNavPanelView>,
   public CVistaDwm
{
public:
   DECLARE_WND_CLASS(_T("WTL_PhotoNavPanel"))

   enum { CX_PANELSIDE = 210 };

   WTL::CBitmap m_bmpPanelLeft;
   WTL::CBitmap m_bmpPanelRight;
   WTL::CBitmap m_bmpPanelMiddle;
   WTL::CBitmap m_bmpPanelSide;

   CImageSizeSliderCtrl m_wndZoom;

   CFadeStateButtonCtrl m_ctrlBack;
   CFadeStateButtonCtrl m_ctrlRun;
   CFadeStateButtonCtrl m_ctrlForward;
   CFadeStateButtonCtrl m_ctrlReset;
   CFadeStateButtonCtrl m_ctrlDelete;
   CFadeStateButtonCtrl m_ctrlZoom;
   CFadeStateButtonCtrl m_ctrlRotateLeft;
   CFadeStateButtonCtrl m_ctrlRotateRight;

   BEGIN_MSG_MAP(CNavPanelView)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
      MESSAGE_HANDLER(WM_PAINT, OnPaint)
      MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
      MESSAGE_HANDLER(WM_SIZE, OnSize)
      MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
      COMMAND_HANDLER(IDC_IMAGE_ZOOM, BN_PUSHED, OnImageZoom)
      COMMAND_HANDLER(IDC_IMAGE_RESET, BN_CLICKED, OnImageReset)
      COMMAND_HANDLER(IDC_IMAGE_BACK, BN_CLICKED, OnImagePrev)
      COMMAND_HANDLER(IDC_IMAGE_FORWARD, BN_CLICKED, OnImageNext)      
   END_MSG_MAP()

   LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {
      m_bmpPanelLeft   = AtlLoadGdiplusImage(IDB_NAVPANEL_LEFT, _T("PNG"));
      m_bmpPanelRight  = AtlLoadGdiplusImage(IDB_NAVPANEL_RIGHT, _T("PNG"));
      m_bmpPanelSide   = AtlLoadGdiplusImage(IDB_NAVPANEL_SIDE, _T("PNG"));
      m_bmpPanelMiddle = AtlLoadGdiplusImage(IDB_NAVPANEL_MIDDLE, _T("PNG"));

      struct {
         CFadeStateButtonCtrl* pCtrl;
         UINT uID;
         DWORD dwStyle;
         UINT uBitmapID;
         UINT uToolTipText;
      } Buttons[] = 
      {
         { &m_ctrlBack,        IDC_IMAGE_BACK,     FSTBS_COMPOSITE | FSTBS_CAPTUREBKG | FSTBS_DOUBLEBUFFER, IDB_NAVBUTTONS_BACK,     IDS_IMAGEBACK },
         { &m_ctrlForward,     IDC_IMAGE_FORWARD,  FSTBS_COMPOSITE | FSTBS_CAPTUREBKG | FSTBS_DOUBLEBUFFER, IDB_NAVBUTTONS_FORWARD,  IDS_IMAGEFORWARD },
         { &m_ctrlRun,         IDC_NAV_RUN,        FSTBS_COMPOSITE | FSTBS_CAPTUREBKG | FSTBS_DOUBLEBUFFER, IDB_NAVBUTTONS_RUN,      IDS_RUN },
         { &m_ctrlDelete,      IDC_IMAGE_DELETE,   FSTBS_COMPOSITE | FSTBS_CAPTUREBKG | FSTBS_DOUBLEBUFFER, IDB_NAVBUTTONS_DELETE,   IDS_DELETE },
         { &m_ctrlReset,       IDC_IMAGE_RESET,    FSTBS_COMPOSITE | FSTBS_CAPTUREBKG | FSTBS_DOUBLEBUFFER, IDB_NAVBUTTONS_RESET,    IDS_RESET },
         { &m_ctrlZoom,        IDC_IMAGE_ZOOM,     FSTBS_COMPOSITE | FSTBS_CAPTUREBKG | FSTBS_DOUBLEBUFFER, IDB_NAVBUTTONS_ZOOM,     IDS_ZOOM },
         { &m_ctrlRotateLeft,  IDC_IMAGE_ROTLEFT,  FSTBS_COMPOSITE | FSTBS_CAPTUREBKG | FSTBS_DOUBLEBUFFER, IDB_NAVBUTTONS_ROTLEFT,  IDS_ROTLEFT },
         { &m_ctrlRotateRight, IDC_IMAGE_ROTRIGHT, FSTBS_COMPOSITE | FSTBS_CAPTUREBKG | FSTBS_DOUBLEBUFFER, IDB_NAVBUTTONS_ROTRIGHT, IDS_ROTRIGHT },
      };
      for( int i = 0; i < sizeof(Buttons) / sizeof(Buttons[0]); i++ ) {
         CFadeStateButtonCtrl* pCtrl = Buttons[i].pCtrl;
         pCtrl->Create(m_hWnd, rcDefault, _T(""), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_OWNERDRAW, 0, Buttons[i].uID);
         pCtrl->SetToolTipText(CString(MAKEINTRESOURCE(Buttons[i].uToolTipText)));
         pCtrl->SetFadeButtonStyle(Buttons[i].dwStyle);
         pCtrl->SetBitmap(Buttons[i].uBitmapID, _T("PNG"));
         pCtrl->SizeToBitmap();
      }

      bHandled = FALSE;
      return 0;
   }

   LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
   {
      CRect rcClient(0,0,LOWORD(lParam), HIWORD(lParam));
      CRect rcPanel = _GetPanelRect(rcClient);
      CPoint ptMid = rcPanel.CenterPoint();
      HDWP hdwp = ::BeginDeferWindowPos(8);
      hdwp = ::DeferWindowPos(hdwp, m_ctrlZoom,        NULL, rcPanel.left + 30, rcPanel.top + 4, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
      hdwp = ::DeferWindowPos(hdwp, m_ctrlReset,       NULL, rcPanel.left + 90, rcPanel.top + 4, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
      hdwp = ::DeferWindowPos(hdwp, m_ctrlBack,        NULL, rcPanel.left + 136, rcPanel.top + 4, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
      hdwp = ::DeferWindowPos(hdwp, m_ctrlRun,         NULL, rcPanel.left + 188, rcPanel.top - 8, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
      hdwp = ::DeferWindowPos(hdwp, m_ctrlForward,     NULL, rcPanel.left + 234, rcPanel.top + 4, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
      hdwp = ::DeferWindowPos(hdwp, m_ctrlRotateLeft,  NULL, rcPanel.left + 300, rcPanel.top + 4, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
      hdwp = ::DeferWindowPos(hdwp, m_ctrlRotateRight, NULL, rcPanel.left + 330, rcPanel.top + 4, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
      hdwp = ::DeferWindowPos(hdwp, m_ctrlDelete,      NULL, rcPanel.left + 370, rcPanel.top + 4, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
      ::EndDeferWindowPos(hdwp);
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

   LRESULT OnImageZoom(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      ::ReleaseCapture();
      if( m_wndZoom.IsWindow() ) m_wndZoom.DestroyWindow();
      POINT pt = { 0 };
      ::GetCursorPos(&pt);
      enum { CX_ZOOM = 30, CY_ZOOM = 100 };
      CRect rcZoom(pt.x - CX_ZOOM / 2, pt.y - CY_ZOOM / 2, pt.x + CX_ZOOM / 2, pt.y + CY_ZOOM / 2);
      ::OffsetRect(&rcZoom, 2, 10);
      m_wndZoom.Create(m_hWnd, rcZoom, NULL);
      return 0;
   }

   LRESULT OnImageReset(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      _Photos.SendChangeNotify(WM_USER_ZOOM_CHANGE, 1, 0L);
      return 0;
   }

   LRESULT OnImagePrev(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      _Photos.SendChangeNotify(WM_USER_IMAGE_NAVIGATE, 0, (LPARAM) -1L);
      return 0;
   }

   LRESULT OnImageNext(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      _Photos.SendChangeNotify(WM_USER_IMAGE_NAVIGATE, 0, 1L);
      return 0;
   }

   // Implementation

   CRect _GetPanelRect(CRect rcClient) const
   {
      if( rcClient.IsRectEmpty() ) return rcClient;
      rcClient.top = rcClient.top + 18;
      rcClient.bottom = rcClient.top + 33;
      CPoint ptMid = rcClient.CenterPoint();
      return CRect(ptMid.x - CX_PANELSIDE, rcClient.top, ptMid.x + CX_PANELSIDE, rcClient.bottom);
   }

   void DoPaint(CDCHandle dc)
   {    
      CRect rcClient;
      GetClientRect(&rcClient);

      COLORREF clrBack = RGB(185,209,239);
      if( IsCompositionEnabled() ) clrBack = RGB(0,0,0);
      dc.FillSolidRect(rcClient, clrBack);

      CRect rc = _GetPanelRect(rcClient);
      CPoint ptMid = rc.CenterPoint();

      CRect rcLeft(rc.left, rc.top, rc.left + 16, rc.bottom);
      CRect rcRight(rc.right - 16, rc.top, rc.right, rc.bottom);
      CRect rcSide(rc.left + 16, rc.top, rc.right - 16, rc.bottom);
      CRect rcMiddle(ptMid.x - 20, ptMid.y - 25, ptMid.x + 20, ptMid.y + 27);

      BLENDFUNCTION bf = { 0 };
      bf.BlendOp = AC_SRC_OVER; 
      bf.BlendFlags = 0; 
      bf.AlphaFormat = AC_SRC_ALPHA;
      bf.SourceConstantAlpha = 255;

      CDC dcCompat;
      dcCompat.CreateCompatibleDC(dc);
      HBITMAP hOldBitmap = dcCompat.SelectBitmap(m_bmpPanelLeft);
      dc.AlphaBlend(rcLeft.left, rcLeft.top, rcLeft.Width(), rcLeft.Height(), dcCompat, 0, 0, rcLeft.Width(), rcLeft.Height(), bf);
      dcCompat.SelectBitmap(m_bmpPanelRight);
      dc.AlphaBlend(rcRight.left, rcRight.top, rcRight.Width(), rcRight.Height(), dcCompat, 0, 0, rcRight.Width(), rcRight.Height(), bf);
      dcCompat.SelectBitmap(m_bmpPanelSide);
      dc.AlphaBlend(rcSide.left, rcSide.top, rcSide.Width(), rcSide.Height(), dcCompat, 0, 0, 5, rcSide.Height(), bf);
      dcCompat.SelectBitmap(m_bmpPanelMiddle);
      dc.AlphaBlend(rcMiddle.left, rcMiddle.top, rcMiddle.Width(), rcMiddle.Height(), dcCompat, 0, 0, rcMiddle.Width(), rcMiddle.Height(), bf);
      dcCompat.SelectBitmap(hOldBitmap);
   }
};


#endif // !defined(AFX_NAVPANELVIEW_H__20071124_6783_43DF_E667_0080AD509054__INCLUDED_)

