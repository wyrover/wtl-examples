

#pragma once
#include "MenuItem.h"

class CDocBar
  :public CDrawItem{
public:
  CDocBar():_color(255, 0,0,0){};
  virtual ~CDocBar(){
  };

  DECLARE_WND_CLASS(_T("DOC_BAR"))
  /*BEGIN_MSG_MAP(CDocBar)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_PAINT, OnPaint)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
  END_MSG_MAP()*/

public:
  void paintForground(Gdiplus::Graphics*  g){
    RECT rc;
    this->GetClientRect(&rc);
    Gdiplus::SolidBrush brush(_color);
    Gdiplus::Status s = g->FillRectangle(&brush,  \
      (float)rc.left, (float)rc.top, (float)(rc.right - rc.left), (float)(rc.bottom - rc.top));
  };

  void setBkg(Gdiplus::Color clr){
    _color = clr;
  }

private:
  Gdiplus::Color _color;
};