// CustomTabView.h - CCustomTabView class

#pragma once
#include <atlctrlx.h>

#include <map>
#include <memory>

class CCustomTabView : public CTabViewImpl<CCustomTabView>
{
public:
  DECLARE_WND_CLASS_EX(_T("TabBrowser_CustomTabView"), 0, COLOR_APPWORKSPACE)

  //BEGIN_MSG_MAP(CCustomTabView)
  //  CHAIN_MSG_MAP(CTabViewImpl<CCustomTabView>)
  //  MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
  //  DEFAULT_REFLECTION_HANDLER()
  //  ALT_MSG_MAP(1)
  //  MESSAGE_HANDLER(OCM_DRAWITEM, OnDrawItem)
  //END_MSG_MAP()
  CCustomTabView(){}

  //LRESULT OnDrawItem(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled){
  //  lParam;
  //  bHandled;
  //  return 0;
  //};
  // Overrideables - add a toolbar next to the tab control
  bool CreateTabControl()
  {
    bool bRet = CTabViewImpl<CCustomTabView>::CreateTabControl();

    CString pageTitle;
    pageTitle.Format(_T("µÚ%dÒ³"), _page_no);

    CContainerWithBar* pBar = new CContainerWithBar;
    HWND hWnd= pBar->Create(this->m_hWnd, rcDefault, pageTitle, \
      WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);

    if(this->AddPage(hWnd, pageTitle)){
      int itemId = this->GetActivePage();
      this->_white_broades.insert(std::make_pair(itemId, std::shared_ptr<CContainerWithBar>(pBar)));
      _page_no++;
    }

    pageTitle.Format(_T("µÚ%dÒ³"), _page_no);
    pBar = new CContainerWithBar;
    hWnd= pBar->Create(this->m_hWnd, rcDefault, pageTitle, \
      WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);

    if(this->AddPage(hWnd, pageTitle)){
      int itemId = this->GetActivePage();
      this->_white_broades.insert(std::make_pair(itemId, std::shared_ptr<CContainerWithBar>(pBar)));
      _page_no++;
    }
    return bRet;
  }

  void UpdateLayout()
  {
    RECT rect;
    GetClientRect(&rect);

    if(m_tab.IsWindow() && m_tab.IsWindowVisible())
      m_tab.SetWindowPos(NULL, 0, 0, rect.right - rect.left, m_cyTabHeight, SWP_NOZORDER);

    /*if(m_wndTB.IsWindow() && m_tab.IsWindowVisible())
    m_wndTB.SetWindowPos(NULL, rect.right - m_cxTB, 0, m_cxTB, m_cyTabHeight, SWP_NOZORDER);*/

    if(m_nActivePage != -1)
      ::SetWindowPos(GetPageHWND(m_nActivePage), NULL, 0, m_cyTabHeight, rect.right - rect.left, rect.bottom - rect.top - m_cyTabHeight, SWP_NOZORDER);


  }

  void ShowTabControl(bool bShow)
  {
    m_tab.ShowWindow(bShow ? SW_SHOWNOACTIVATE : SW_HIDE);
  }

  void UpdateTooltipText(LPNMTTDISPINFO pTTDI)
  {
    ATLASSERT(pTTDI != NULL);

    /*		m_strTooltip = GetPageTitle(pTTDI->hdr.idFrom);

    CAxWindow wnd = GetPageHWND(pTTDI->hdr.idFrom);
    CComPtr<IWebBrowser2> spWebBrowser;
    HRESULT hRet = wnd.QueryControl(IID_IWebBrowser2, (void**)&spWebBrowser);
    hRet;   // avoid level 4 warning
    ATLASSERT(SUCCEEDED(hRet));
    if(spWebBrowser != NULL)
    {
    BSTR bstrURL;
    spWebBrowser->get_LocationURL(&bstrURL);
    m_strTooltip += _T("\n");
    m_strTooltip += bstrURL;
    }

    pTTDI->lpszText = (LPTSTR)(LPCTSTR)m_strTooltip;*/
  }

private:
  std::map<unsigned int, std::shared_ptr<CContainerWithBar>> _white_broades;
  static unsigned int _page_no ;
};


unsigned int CCustomTabView::_page_no = 1;