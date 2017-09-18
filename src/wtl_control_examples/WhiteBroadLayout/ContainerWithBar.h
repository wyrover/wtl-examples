
#pragma once

#include <assert.h>

class CContainerWithBar:public CWindowImpl< CContainerWithBar>{
public:
  DECLARE_WND_CLASS(_T("Control_Container"))

  CContainerWithBar():_bar_hight(366), _bar_width(45){};
  virtual ~CContainerWithBar(){};

  BOOL PreTranslateMessage(MSG* pMsg)
  {
    pMsg;
    return FALSE;
  }
  BEGIN_MSG_MAP(CContainerWithBar)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    COMMAND_CODE_HANDLER(EN_CHANGE, OnChange)
  END_MSG_MAP()

public:
  LRESULT OnChange(UINT /*uMsg*/, WPARAM wParam, HWND lParam, BOOL& /*bHandled*/){
    //this->ModifyStyleEx(0, WS_EX_STATICEDGE, 0);
    return 0;
  }
  LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/){
    RECT rc = {50, 50, 150, 150};
    //_line.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    //_line.setLine(Gdiplus::Point(30, 30), Gdiplus::Point(50, 50));

    rc.left = 10;
    rc.top = 200;
    rc.bottom = rc.top + this->_bar_hight;
    rc.right = rc.left + _bar_width;
    _bar.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    _bar.setBkg(_T("res\\Toolbar-bg_1.png"));

    rc.left = rc.right + 20;
    rc.top = 200;
    rc.bottom = rc.top + 436;
    rc.right = rc.left + _bar_width;
    _bar2.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    _bar2.setBkg(_T("res\\Toolbar-bg_1.png"));

    rc.left = rc.right + 20;
    rc.top = 200;
    rc.bottom = rc.top + 70;
    rc.right = rc.left + _bar_width;
    _bar4.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    _bar4.setBkg(_T("res\\Toolbar-bg_1.png"));

    rc.left = 0;
    rc.top = 10;
    rc.bottom = rc.top + 32;
    rc.right = rc.left + 566;
    _bar5.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    _bar5.setBkg(_T("res\\playbarbg_1.png"));

    _bar3.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

    RECT rc1 ={2, 2, 50, 30};

    rc.left = 0;
    rc.top = 50;
    rc.bottom = rc.top + 37;
    rc.right = rc.left + 385;
    _bar6.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    _bar6.setBkg(_T("res\\playbarbg_1.png"));

    rc.left = 10;
    rc.top = 150;
    rc.bottom = rc.top + 185;
    rc.right = rc.left + 45;
    _tmp_bar.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    _tmp_bar.setBkg(Gdiplus::Color(210, 210, 210));
    return 0;
  }

  LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/){
    RECT rc;
    this->GetClientRect(&rc);

    rc.left = (rc.right - rc.left - _total_w) /2;
    rc.bottom = rc.bottom - _y_bottom;
    rc.top = rc.bottom - _item_h;
    rc.right = rc.left + _total_w;

    _bar3.MoveWindow(&rc);
    this->UpdateWindow();
    return 0;
  }
public:
  void setBarSize(unsigned int w, unsigned int h){
    _bar_width =w;
    _bar_hight= h;
  };
  void BarSize(unsigned int* w, unsigned int* h){
    if(!w || !h) {assert(w || h); return ;}
    *w = _bar_width;
    *h = _bar_hight;
  }


private:
  CDrawLine _line;
  ShareBoradDocBar _bar;
  WhitBroadBar _bar2;
  LastNextBar _bar3;
  MediaBar _bar4;
  PlayBar _bar5;
  CamerMediaBar _bar6;
  CDrawTip _tip;

  unsigned int _bar_width;
  unsigned int _bar_hight;

  static const unsigned int _y_bottom = 15;
  static const unsigned int _total_w = 110;
  static const unsigned int _item_h = 26;

  CDrawEdit _edit;

  TmpBar _tmp_bar;
};