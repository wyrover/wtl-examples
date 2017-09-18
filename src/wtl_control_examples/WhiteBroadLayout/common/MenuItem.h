
#pragma once
#include <CString>
#include <GdiPlus.h>
#include <memory>
#include <set>
#include <vector>
#include "common/sigslot.h"
#include<cmath>
#pragma comment(lib, "Gdiplus.lib")
#ifndef PI
#define PI 3.14159265
#endif //PI

class CDrawItem:public CDoubleBufferWindowImpl<CDrawItem>{
public:
  virtual void paintForground(Gdiplus::Graphics*){
  };

  virtual void paintBkg(Gdiplus::Graphics* g){
    RECT rc;
    this->GetClientRect(&rc);
    Gdiplus::SolidBrush brush(Gdiplus::Color(255, 255, 255, 255));
    g->FillRectangle(&brush, (float)(rc.left), (float)(rc.top), (float)(rc.right- rc.left), (float)(rc.bottom - rc.top));
  }
  virtual void doSize(Gdiplus::Rect& rc){
  };
  virtual void doCreate(BOOL& Handler ){
  };

  BEGIN_MSG_MAP(CDrawItem)
    MESSAGE_HANDLER(WM_PAINT, OnPaint)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBackground)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    CHAIN_MSG_MAP(CDoubleBufferWindowImpl<CDrawItem>)
  END_MSG_MAP()

  CDrawItem(){
    //init_gdiplus_flag++;
    //if(init_gdiplus_flag == 0 ){
      Gdiplus::GdiplusStartupInput starUp;
      Gdiplus::GdiplusStartup(&_gdi_token, &starUp, NULL);
    //}
  }
  virtual ~CDrawItem(){
    //init_gdiplus_flag--;
    //if(init_gdiplus_flag == 0){
      Gdiplus::GdiplusShutdown(_gdi_token);
    //}
  };

 /* void DoPaint(CDCHandle dc){

    RECT rc;
    this->GetClientRect(&rc);

    Gdiplus::Graphics g(dc);
    this->paintBkg(&g);
    this->paintForground(&g);
  }*/
protected:
  LRESULT OnEraseBackground(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/){
    return 1;
  }
  
  LRESULT OnCreate(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled){
    bHandled = FALSE;
    doCreate(bHandled);
    return 0;
  };
  LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/){
    RECT rc;
    this->GetClientRect(&rc);

    HDC real_dc = this->GetDC();

    if(wParam != NULL){
      CMemoryDC dc((HDC)wParam, rc);
      Gdiplus::Graphics g(dc.m_hDC);
      this->paintBkg(&g);
      this->paintForground(&g);
    } else  {
      CPaintDC dc(this->m_hWnd);
      CMemoryDC dcMem(dc.m_hDC, dc.m_ps.rcPaint);
      Gdiplus::Graphics g(dcMem.m_hDC);
      this->paintBkg(&g);
      this->paintForground(&g);
    }

    return 0;
  }

  LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled){
    RECT rc;
    this->GetClientRect(&rc);
    Gdiplus::Rect rt(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
    doSize(rt);

    this->UpdateWindow();
    return 0;
  }
protected:
  ULONG_PTR _gdi_token;
private:
  //static int init_gdiplus_flag;
};

//int CDrawItem::init_gdiplus_flag = -1;

class CDrawLine:public CDrawItem{
public:
  CDrawLine(){};
  CDrawLine(Gdiplus::Point start, Gdiplus::Point end)
    : _start(start), _end(end){
  };

  void setLine(Gdiplus::Point start, Gdiplus::Point end){
    _start = start;
    _end = end;
  };

  void setColor(Gdiplus::Color & c){
    _color = c;
  };

  void paintForground(Gdiplus::Graphics* g){
    Gdiplus::Pen p(_color, 2);
    p.SetLineCap(Gdiplus::LineCap::LineCapRound,Gdiplus::LineCap::LineCapRound,Gdiplus::DashCap::DashCapRound);
    p.SetLineJoin(Gdiplus::LineJoin::LineJoinRound);

    Gdiplus::GraphicsPath path;
    //path.AddArc(_start.X, _start.Y, 30, 30, 0, 90);

    int  cornerX = 5;
    int cornerY = 5;
    int width = 50;
    int height = 70;
    int x = _start.X;
    int y = _start.Y;
    INT elWid = 2*cornerX;
    INT elHei = 2*cornerY;

    path.AddArc(x,y,elWid,elHei,180,90); // ×óÉÏ½ÇÔ²»¡
    path.AddLine(x+cornerX,y,x+width-cornerX,y); // ÉÏ±ß

    path.AddArc(x+width-elWid,y, elWid,elHei,270,90); // ÓÒÉÏ½ÇÔ²»¡
    path.AddLine(x+width,y+cornerY, x+width,y+height-cornerY);// ÓÒ±ß

    path.AddArc(x+width-elWid,y+height-elHei, elWid,elHei,0,90); // ÓÒÏÂ½ÇÔ²»¡
    path.AddLine(x+width-cornerX,y+height, x+cornerX,y+height); // ÏÂ±ß

    path.AddArc(x,y+height-elHei, elWid,elHei,90,90); 
    path.AddLine(x,y+cornerY, x, y+height-cornerY);
    //g->DrawLine(&p, _start, _end);
    g->DrawPath(&p, &path);

  }

private:
  Gdiplus::Point _start;
  Gdiplus::Point _end;

  Gdiplus::Color _color;

};

class CDrawSpace: public CDrawItem{
public:

  void paintForground(Gdiplus::Graphics* g){
    RECT rc;
    this->GetClientRect(&rc);

    if(!_icon) return;
    int x = (rc.right - rc.left - _icon->GetWidth())/2;
    int y = (rc.bottom - rc.top - _icon->GetHeight()) /2;

    g->DrawImage(_icon.get(),  x, y);
  };
  void paintBkg(Gdiplus::Graphics* g){
    RECT rc;
    this->GetClientRect(&rc);

    g->FillRectangle(_bkg_brush.get(), rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
  };
  void setIcon(CString icon, CString bkg){
    (icon.IsEmpty() == FALSE) ?this->_icon.reset(new Gdiplus::Bitmap(icon)) : 0;
    if (bkg.IsEmpty() == FALSE) {
      Gdiplus::Bitmap img(bkg);
      _bkg_brush.reset(new Gdiplus::TextureBrush(&img));
    };
  };
  void setbkg(Gdiplus::Color& c){
    _bkg_brush.reset(new Gdiplus::SolidBrush(c));
  };
 
protected:
  std::unique_ptr<Gdiplus::Bitmap> _icon;
  std::unique_ptr<Gdiplus::Brush> _bkg_brush;
};

class CDrawTip:public CDrawItem{
public:
  CDrawTip():_active(false){};
  virtual ~CDrawTip(){};
  BEGIN_MSG_MAP(CDrawTip)
    MESSAGE_HANDLER(WM_TIMER, OnTimer)
    CHAIN_MSG_MAP(CDrawItem)
  END_MSG_MAP()
public:
  void paintForground(Gdiplus::Graphics* g){
    Gdiplus::SolidBrush brush(Gdiplus::Color::Black);
    Gdiplus::Pen p(Gdiplus::Color::Gray, 2);
    
    RECT rc;
    this->GetClientRect(&rc);

    Gdiplus::Font font(&Gdiplus::FontFamily(L"Arial"), 10);
    Gdiplus::RectF rect(rc.left, (float)rc.top, (float)_width, _rect_h);

    Gdiplus::StringFormat sf;
    sf.SetAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
    sf.SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);

    g->DrawString(_str, _str.GetLength(), \
      &font, rect, &sf, &brush );
    g->DrawPath(&p, _path.get());
  }

  void doCreate(BOOL& Handler ){
    _x_pos = 0;
    _y_pos = 0;
    mkWin();
    this->BringWindowToTop();
  };

  void mkWin(){
    RECT rc;
    this->GetClientRect(&rc);

    _rect_h = rc.bottom - rc.top ;//+ _space_w/2 * atan(60 *PI/180);
    _width = rc.right - rc.left;
    _rect_h -= _space_w/2 * tan(60 *PI/180);

    Gdiplus::GraphicsPath path;
    path.AddLine(_x_pos, _y_pos, _x_pos +_width, _y_pos);
    path.AddLine(_x_pos + _width, _y_pos, _x_pos + _width, _y_pos + _rect_h);

    path.AddLine(_x_pos + _width, _y_pos + _rect_h, \
      _x_pos + (_width + _space_w)/2, _y_pos + _rect_h);
    
    path.AddLine(_x_pos + (_width + _space_w) /2, _y_pos + _rect_h, \
      _x_pos + _width /2, _space_w/2 * tan(60 *PI/180) + _y_pos + _rect_h);

    path.AddLine(_x_pos + _width /2, _space_w/2 * tan(60 *PI/180) + _y_pos + _rect_h, \
      _x_pos + _width/2 -_space_w/2, _y_pos + _rect_h);

    path.AddLine( _x_pos + _width/2 -_space_w/2, _y_pos + _rect_h, \
      _x_pos, _y_pos + _rect_h);

    path.AddLine(_x_pos, _y_pos + _rect_h, _x_pos, _y_pos);

    _path.reset( path.Clone());
    Gdiplus::Region rg(&path);
    Gdiplus::Graphics g(this->m_hWnd);
    this->SetWindowRgn(rg.GetHRGN(&g));
  }

  LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled){
    if(_active){
      this->ShowWindow(SW_HIDE);
      _active = false;
      KillTimer(TIMER_ID);
    }
    return 0;
  }
  void str(CString& str){
    _str = str;
    this->Invalidate();
  };

  void active(bool a){
    if(a){
      chgWinPos();
      _active = true;
      this->ShowWindow(SW_SHOW);
      this->SetTimer(TIMER_ID, 1000);
    }else{
      //delay 3 second, hide windows
      
    }
  };
protected:
  void chgWinPos(){

    POINT pos;
    ::GetCursorPos(&pos);

    _mouse_pos.X = pos.x;
    _mouse_pos.Y = pos.y;

    _x_pos = pos.x;
    _y_pos = pos.y;

    RECT rc;
    this->GetClientRect(&rc);

    rc.right = rc.right - rc.left;
    rc.bottom = rc.bottom - rc.top;
    rc.left = _x_pos - rc.right /2;
    rc.top = _y_pos - rc.bottom;
    rc.right = rc.right + rc.left;
    rc.bottom = rc.bottom + rc.top;

    this->MoveWindow(&rc);
  }
protected:
  float _x_pos;
  float _y_pos;
  float _rect_h;
  float _width;
  float _hight;
  static const int _space_w = 10;
  static const int TIMER_ID = 10;

  std::unique_ptr<Gdiplus::GraphicsPath> _path;

  CString _str;
  bool _active;
  Gdiplus::Point _mouse_pos;
};


class CProgressBar:public CDrawItem{
public:
  BEGIN_MSG_MAP(CProgressBar)
    MESSAGE_RANGE_HANDLER(WM_MOUSEFIRST, WM_MOUSELAST, OnMouseMessage)
    MESSAGE_HANDLER(WM_MOUSEHOVER, OnMouseHover)
    MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
    CHAIN_MSG_MAP(CDrawItem)
  END_MSG_MAP()
  CProgressBar():_cache_len((float)0.8), _play_len((float)0.5){};
  virtual ~CProgressBar(){};
public:
  void paintForground(Gdiplus::Graphics* g){
    Gdiplus::Rect ct(_content);
    ct.Width = (int)(_content.Width * this->_cache_len);

    _cache ? g->FillRectangle(_cache.get(), ct) : 0;

    ct.Width = (int)(_content.Width * this->_play_len);
    _play ? g->FillRectangle(_play.get(), ct) : 0;
  }
  void paintBkg(Gdiplus::Graphics* g){
    //CDrawItem::paintBkg(g);
    RECT rc;
    this->GetClientRect(&rc);

    _pen->SetWidth(2);
    Gdiplus::Rect rt(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
    _pen ? g->DrawRectangle(_pen.get(), rt) : 0;

    rt.X += 1;
    rt.Y += 1;
    rt.Width -= 2;
    rt.Height -= 2;
    _brush ? g->FillRectangle(_brush.get(), rt) : 0;


    rt.X += 1;
    rt.Y += 1;
    rt.Width -= 2;
    rt.Height -= 2;
    _content = rt;
  }
  void doCreate(BOOL& Handler ){
    RECT rc1 ={2, 2, 50, 30};
    _tip.Create(this->m_hWnd, rc1, NULL,  WS_POPUP);
  };

 
  LRESULT OnMouseMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled){
    bHandled = FALSE;
    return 1;
  }
  LRESULT OnMouseHover(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled){
    CString str(_T("00:00"));
    bool show = true;
    _mouseHover(show, str);
    if(show){
      _tip.str(str);
      _tip.active(true);
    }

    return 0;
  }
  LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled){
    TRACKMOUSEEVENT te = {0};
    te.cbSize = sizeof(te);
    te.hwndTrack = this->m_hWnd;
    te.dwFlags = TME_HOVER;
    te.dwHoverTime = 1000;

    BOOL re = ::_TrackMouseEvent(&te);

    _tip.active(false);
    return 0;
  }
  void setBkg(Gdiplus::Color c){
    _brush.reset(new Gdiplus::SolidBrush(c));
  };
  void setBkg(CString& img){
    Gdiplus::Image bitmap(img);
    _brush.reset(new Gdiplus::TextureBrush(&bitmap));
  }

   void setPen(Gdiplus::Color c){
    _pen.reset(new Gdiplus::Pen(c));
  };
  void setPen(CString& img){
    Gdiplus::Image bitmap(img);
    Gdiplus::TextureBrush brush(&bitmap);
    _pen.reset(new Gdiplus::Pen(&brush));
  }

  void setPlay(CString& play){
     Gdiplus::Image bitmap(play);
    _play.reset(new Gdiplus::TextureBrush(&bitmap));
  }
  void setCache(CString& cache){
     Gdiplus::Image bitmap(cache);
    _cache.reset(new Gdiplus::TextureBrush(&bitmap));
  }

  ///progress 0 ~ 1
  void cache(float len){
    if(len > 1 || len < 0) return;
    _cache_len = len;
    this->Invalidate();
  };
  void progress(float len){
    if(len > 1 || len < 0 || len > _cache_len) return;
    _play_len = len;
    this->Invalidate();
  }
public:
  sigslot::signal2<bool&, CString&> _mouseHover;
private:
  std::unique_ptr<Gdiplus::Brush> _brush;
  std::unique_ptr<Gdiplus::Pen> _pen;

  std::unique_ptr<Gdiplus::Brush> _play;
  std::unique_ptr<Gdiplus::Brush> _cache;

  Gdiplus::Rect _content;
  float _cache_len;
  float _play_len;

  CDrawTip _tip;
};


class CAudioBar:public CDrawItem{
public:
  CAudioBar(): _current_count(3){};
  virtual ~CAudioBar(){};

  void paintBkg(Gdiplus::Graphics* g){
    RECT rc;
    this->GetClientRect(&rc);
    Gdiplus::Rect rt(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
    g->FillRectangle(_brush.get(), rt);
  };

  void paintForground(Gdiplus::Graphics* g){
    RECT rc;
    this->GetClientRect(&rc);
    Gdiplus::Rect rt(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);

    Gdiplus::Rect en(rc.left, rc.top, 0, 0);
    en.Width = (rt.Width - (_audio_count - 1) * _space) / _audio_count;
    en.Height = rt.Height;

    register unsigned int i = 0;
    while(i < _audio_count){
      if(i < _current_count){
        _enable ? g->FillRectangle(_enable.get(), en) : 0;
      } else {
        _disable ? g->FillRectangle(_disable.get(), en) : 0;
      }

      en.X = en.X + en.Width + _space;
      i++;
    }
  };

  void setBkg(Gdiplus::Color c){
    _brush.reset(new Gdiplus::SolidBrush(c));
  };
  void setBkg(CString& img){
    Gdiplus::Image bitmap(img);
    _brush.reset(new Gdiplus::TextureBrush(&bitmap));
  }
  void setEnable(Gdiplus::Color c){
    _enable.reset(new Gdiplus::SolidBrush(c));
  };
  void setEnable(CString& img){
    Gdiplus::Image bitmap(img);
    _enable.reset(new Gdiplus::TextureBrush(&bitmap));
  }

   void setDisable(Gdiplus::Color c){
    _disable.reset(new Gdiplus::SolidBrush(c));
  };
  void setDisable(CString& img){
    Gdiplus::Image bitmap(img);
    _disable.reset(new Gdiplus::TextureBrush(&bitmap));
  }

  void enable(unsigned int c){
    int change = c;
    if(c > _audio_count) change = _audio_count;
    
    if(change != _current_count){
      _current_count = change;
      this->Invalidate();
      _valueChange(this);
    }
  };
  unsigned int enable(){
    return _current_count;
  }

  unsigned int all(){
    return _audio_count;
  }
public:
  sigslot::signal1<CDrawItem*> _valueChange;

protected:
  static const unsigned int _audio_count = 7;
  static const unsigned int _space = 2;
  std::unique_ptr<Gdiplus::Brush> _brush;
  std::unique_ptr<Gdiplus::Brush> _enable;
  std::unique_ptr<Gdiplus::Brush> _disable;

  unsigned int _current_count;
};

class CDrawButton:public CDrawItem{
public:
  CDrawButton():_normal_color(Gdiplus::Color::DarkBlue), _select_color(Gdiplus::Color::LightGray),\
    _left_bt_down(false), _ellipse(false), _pos_align(0, 0){
  };
  CDrawButton(CString normalIcon, CString selectIcon):_normal_color(Gdiplus::Color::DarkBlue),\
    _select_color(Gdiplus::Color::LightGray), _bitmap_normal(std::unique_ptr<Gdiplus::Bitmap>(new Gdiplus::Bitmap(normalIcon))), \
    _bitmap_select(std::unique_ptr<Gdiplus::Bitmap>(new Gdiplus::Bitmap(selectIcon))),
    _left_bt_down(false), _ellipse(false), _pos_align(0, 0){

  };
  BEGIN_MSG_MAP(CDrawButton)
    CHAIN_MSG_MAP(CDrawItem)
    MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
    MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
    MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDBClick)
  END_MSG_MAP()
  virtual ~CDrawButton(){
  };

  void setIcon(CString normal, CString select, Gdiplus::Point p = Gdiplus::Point()){

    (normal.IsEmpty() == FALSE) ?this->_bitmap_normal.reset(new Gdiplus::Bitmap(normal)) : 0;
    (select.IsEmpty() == FALSE) ?this->_bitmap_select.reset(new Gdiplus::Bitmap(select)) : 0;
    this->_pos_align = p;
  }
  void setBgColor(CString normal, CString select){
    Gdiplus::Bitmap n(normal);
    Gdiplus::Bitmap s(select);
    //(normal.IsEmpty() == FALSE) ?this->_bkg_normal.reset(new Gdiplus::Bitmap(normal)) : 0;
    //(select.IsEmpty() == FALSE) ?this->_bkg_select.reset(new Gdiplus::Bitmap(select)) : 0;

    _bkg_normal.reset(new Gdiplus::TextureBrush(&n));
    _bkg_select.reset(new Gdiplus::TextureBrush(&s));
  };
  void setBgColor(Gdiplus::Color normal, Gdiplus::Color select){
    //_select_color = select;
    //_normal_color = normal;
    _bkg_normal.reset(new Gdiplus::SolidBrush(normal));
    _bkg_select.reset(new Gdiplus::SolidBrush(select));
  }

  LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/){
    _left_bt_down = true;
    this->Invalidate();
    this->SetCapture();
    return 0;
  }
  LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/){

    if(_left_bt_down) 
      //send click signal
        clickSignal(this);
    _left_bt_down = false;
    this->Invalidate();
    
    ::ReleaseCapture();
    return 0;
  }
  bool ellipse(){
    return _ellipse;
  };

  void ellipse(bool el){
    _ellipse = el;
  };
  LRESULT OnLButtonDBClick(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/){
    dbClickSignal(this);
    return 0;
  }
  void paintBkg(Gdiplus::Graphics* g){
    CDrawItem::paintBkg(g);
    RECT rc;
    this->GetClientRect(&rc);

    Gdiplus::Rect gdi_rc(rc.left, rc.top, rc.right - rc.left, rc.bottom -rc.top);
    Gdiplus::Brush* brush = _left_bt_down ? _bkg_select.get() : _bkg_normal.get();

    _ellipse ? g->FillEllipse(brush, gdi_rc) : \
      g->FillRectangle(brush, gdi_rc);
  };
  void paintForground(Gdiplus::Graphics* g){

    RECT rc;
    this->GetClientRect(&rc);

    Gdiplus::Rect gdi_rc(rc.left, rc.top, rc.right - rc.left, rc.bottom -rc.top);
    std::unique_ptr<Gdiplus::SolidBrush> brush;
    Gdiplus::Bitmap* icon = NULL;

    if(_left_bt_down){
      icon = _bitmap_select.get();
    }else {
      icon = _bitmap_normal.get();
    }

    ///second draw image
    if(icon){
      g->DrawImage(icon, _pos_align.X, _pos_align.Y, icon->GetWidth(), icon->GetHeight());
    }
  };

public:
  sigslot::signal1<CDrawItem*> clickSignal;
  sigslot::signal1<CDrawItem*> dbClickSignal;

protected:
  Gdiplus::Color _normal_color;
  Gdiplus::Color _select_color;

  std::unique_ptr<Gdiplus::Bitmap> _bitmap_normal;
  std::unique_ptr<Gdiplus::Bitmap> _bitmap_select;

  std::unique_ptr<Gdiplus::Brush> _bkg_normal;
  std::unique_ptr<Gdiplus::Brush> _bkg_select;

  CString _text;
  Gdiplus::Size _size;
  bool _left_bt_down;

  bool _ellipse;
  Gdiplus::Point _pos_align;
};




class CDocBar
  :public CDrawItem{
public:
  CDocBar():_left_push(false), _can_move(true){};
  virtual ~CDocBar(){
  };

  DECLARE_WND_CLASS(_T("DOC_BAR"))

  BEGIN_MSG_MAP(CDocBar)
    MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
    MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
    MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    CHAIN_MSG_MAP(CDrawItem)
  END_MSG_MAP()
public:
  void paintForground(Gdiplus::Graphics*  g){
    
  };
  void paintBkg(Gdiplus::Graphics* g){
    CDrawItem::paintBkg(g);

    Gdiplus::Region region;
    region.GetHRGN(g);

    g->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeHighQuality);
    g->FillRegion(_brush.get(), &region);
  }
  void doSize(Gdiplus::Rect& rc){

  };
  void canMove(bool mv){
    _can_move = mv;
  };
  bool canMove(){
    return _can_move;
  };
  void setBkg(Gdiplus::Color clr){
    _brush.reset(new Gdiplus::SolidBrush(clr));
  }
  void setBkg(CString image){
    Gdiplus::ColorMatrix cm;
    float m[5][5] = {{1, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0}, \
    {0, 0, 1, 0, 0}, \
    {0, 0, 0, 0.5f, 0}, \
    {0, 0, 0, 0, 1}};

    memcpy(&cm.m, m, sizeof(cm.m));
    Gdiplus::Image im(image);
    Gdiplus::ImageAttributes ia;
    ia.SetColorMatrix(&cm);//, Gdiplus::ColorMatrixFlags::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustType::ColorAdjustTypeBitmap);

    Gdiplus::Rect rc(0, 0, im.GetWidth(), im.GetHeight());
    _brush.reset(new Gdiplus::TextureBrush(&im));//, rc, &ia));
  }
  LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/){

    if(MK_LBUTTON == wParam && _left_push && _can_move){
      POINTS position = MAKEPOINTS(lParam);
      _window_rc.left = _window_rc.left + (position.x - _last_position.x);
      _window_rc.top = _window_rc.top + (position.y - _last_position.y);
      this->MoveWindow(_window_rc.left, _window_rc.top , \
        _window_rc.right, _window_rc.bottom, true);
    }

    return 0;
  }
  LRESULT OnCreate(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/){
    RECT rc;
    this->GetClientRect(&rc);

    Gdiplus::Graphics g(this->m_hWnd);
    Gdiplus::GraphicsPath path;
    int cornerX = 5;
    int cornerY = 5;
    int width = rc.right - rc.left;
    int height = rc.bottom - rc.top;
    int x = rc.left;
    int y = rc.top;
    INT elWid = 2*cornerX;
    INT elHei = 2*cornerY;

    path.AddArc(x,y,elWid,elHei,180,90); // ×óÉÏ½ÇÔ²»¡
    path.AddLine(x+cornerX,y,x+width-cornerX,y); // ÉÏ±ß

    path.AddArc(x+width-elWid,y, elWid,elHei,270,90); // ÓÒÉÏ½ÇÔ²»¡
    path.AddLine(x+width,y+cornerY, x+width,y+height-cornerY);// ÓÒ±ß

    path.AddArc(x+width-elWid,y+height-elHei, elWid,elHei,0,90); // ÓÒÏÂ½ÇÔ²»¡
    path.AddLine(x+width-cornerX,y+height, x+cornerX,y+height); // ÏÂ±ß

    path.AddArc(x,y+height-elHei, elWid,elHei,90,90); 
    path.AddLine(x,y+cornerY, x, y+height-cornerY);

    Gdiplus::Region region(&path);
    this->SetWindowRgn(region.GetHRGN(&g), TRUE);
    return 0;
  };
  LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/){
    _last_position = MAKEPOINTS(lParam);
    _left_push = true;

    RECT rc;
    this->GetWindowRect(&rc);

    _window_rc.right = rc.right - rc.left;
    _window_rc.bottom = rc.bottom - rc.top;
    _window_rc.top = rc.top;
    _window_rc.left = rc.left;

    ::SetCapture(this->m_hWnd);
    return 0;
  }
  LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/){

    ::ReleaseCapture();
    this->Invalidate();
    return 0;
  }

protected:
  std::unique_ptr<Gdiplus::Brush> _brush;

  POINTS _last_position;

  ///window client in the world coordinates 
  RECT _window_rc;
  bool _left_push;

  bool _can_move;
};



class CDrawEdit:public CWindowImpl<CDrawEdit, CEdit, CControlWinTraits>{
public:
  BEGIN_MSG_MAP(CDrawEdit)
    MESSAGE_HANDLER(WM_NCPAINT, OnNcPaint)
    COMMAND_CODE_HANDLER(EN_CHANGE, OnCreate)
  END_MSG_MAP()

  LRESULT OnCreate(UINT /*uMsg*/, WPARAM wParam, HWND lParam, BOOL& /*bHandled*/){
    //this->ModifyStyleEx(0, WS_EX_STATICEDGE, 0);
    return 0;
  }
  LRESULT OnNcPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/){
    RECT rc;
    this->GetClientRect(&rc);
    Gdiplus::Region rg((HRGN)wParam);

    
    Gdiplus::Graphics g(this->m_hWnd);
    Gdiplus::Pen p(Gdiplus::Color::Black);

    //g.Draw
    g.DrawRectangle(&p, Gdiplus::Rect(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top));
    
    return 0;
  };
};

class ColorBox:public CDrawItem{
public:
  BEGIN_MSG_MAP(ColorBox)
    CHAIN_MSG_MAP(CDrawItem)
    MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
    MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
    //MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDBClick)
  END_MSG_MAP()
  ColorBox():_bkg_brush(new Gdiplus::SolidBrush(Gdiplus::Color::Gray)), \
    _left_bt_down(false), _item_color(_item_count), _item_rect(_item_count), \
  _align(ALING_H){
    init_item_color();
  };
  virtual ~ColorBox(){};
  LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/){
    _click_pos.X = GET_X_LPARAM(lParam);
    _click_pos.Y = GET_Y_LPARAM(lParam);
    this->_left_bt_down = true;
    this->Invalidate();
    this->SetCapture();
    return 0;
  }

  LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/){
    if(_left_bt_down){
      int i = get_push_item();
      if(i != -1 && i != 0)
        _select_color = _item_color[i];
    }
    this->_left_bt_down = false;
    this->Invalidate();
    ::ReleaseCapture();
    clickSignal(this);
    return 0;
  }
  void paintBkg(Gdiplus::Graphics* g){
    RECT rc;
    this->GetClientRect(&rc);

    g->FillRectangle(this->_bkg_brush.get(), rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
  }
  void paintForground(Gdiplus::Graphics* g){
    int i = 0;
    int push_item = -1;

    std::unique_ptr<Gdiplus::Brush> brush; 
    Gdiplus::RectF rect;
    Gdiplus::RectF rect1;

    while(i < _item_count){
      if(_left_bt_down){
        push_item = get_push_item();
      }

      brush.reset(new Gdiplus::SolidBrush(_item_color[i]));

      rect = _item_rect[i];
      
      if(push_item == i && push_item != 0){
        draw_click_item(rect, brush.get(), g);
      }else if(i == 0){
        Gdiplus::SolidBrush b(_select_color);
        draw_click_item(rect, &b, g);
      }else {
        draw_item(rect, brush.get(), g);
      }
      i++;
    }
  }
  void doSize(Gdiplus::Rect& rc){
    init_item_rect(Gdiplus::RectF(rc.X, rc.Y, rc.Width, rc.Height));
  }
  void bkg(CString& file){
    Gdiplus::Image image(file);
    this->_bkg_brush.reset(new Gdiplus::TextureBrush(&image));
  };
  void bkg(Gdiplus::Color& c){
    this->_bkg_brush.reset(new Gdiplus::SolidBrush(c));
  }

  void align(int a){
    _align = a/2;
  };

  void draw_item(Gdiplus::RectF rect, Gdiplus::Brush* brush, Gdiplus::Graphics* g){
    Gdiplus::Pen blue_pen_(Gdiplus::Color::Black);
    Gdiplus::Pen white_pen_(Gdiplus::Color::White);

    rect = minus_rect_1(rect);
    g->DrawRectangle(&blue_pen_, rect);

    rect = minus_1(rect);
    g->FillRectangle(brush,rect);
  };
  void draw_click_item(Gdiplus::RectF rect, Gdiplus::Brush* brush, Gdiplus::Graphics* g){
    Gdiplus::Pen blue_pen_(Gdiplus::Color::Black, 1);
    Gdiplus::Pen white_pen_(Gdiplus::Color::White, 1);

    rect = minus_rect_1(rect);
    g->DrawRectangle(&blue_pen_, rect);

    rect = minus_2(rect);
    g->DrawRectangle(&white_pen_, rect);
    rect = minus_1(rect);
    g->FillRectangle(brush,rect);
  };
  Gdiplus::Color get_color(){
    return _select_color;
  };
public:
  sigslot::signal1<CDrawItem*> clickSignal;

protected:
  void init_item_color(){
    int i = 0;
    _item_color[i++] = Gdiplus::Color::White;
    _item_color[i++] = Gdiplus::Color::Black;
    _item_color[i++] = Gdiplus::Color::Gray;
    _item_color[i++] = Gdiplus::Color::Red;
    _item_color[i++] = Gdiplus::Color::Yellow;
    _item_color[i++] = Gdiplus::Color::White;
    _item_color[i++] = Gdiplus::Color::Blue;
    _item_color[i++] = Gdiplus::Color::Purple;
    _item_color[i++] = Gdiplus::Color::Orange;

    _select_color = Gdiplus::Color::Black;
  };

  void init_item_rect(Gdiplus::RectF& rc){
    Gdiplus::RectF rect(rc);
    Gdiplus::RectF rect1;
    int i = 0;

    
    if(_align == ALING_H){
      _item_rect[i++] = rect = Gdiplus::RectF((rect.Width - _big_w)/2, rect.Y, _big_w, _big_h);
      _item_rect[i++] = rect = Gdiplus::RectF(rect.X , rect.Y +_item_space +_big_h, _small_w, _small_h);
      _item_rect[i + 3] = rect1 = Gdiplus::RectF(rect.X + _item_space + _small_w, rect.Y, _small_w, _small_h);
    }else {
      _item_rect[i++] = rect = Gdiplus::RectF(rect.X, (rect.Height - (float)_big_h)/2, _big_w, _big_h);
      _item_rect[i++] = rect = Gdiplus::RectF(rect.X + rect.Width + 2 * _item_space , rect.Y, _small_w, _small_h);
      _item_rect[i + 3] = rect1 = Gdiplus::RectF(rect.X, rect.Y + _small_h + _item_space, _small_w, _small_h);
    }
    
    int count = 0;
    while(count < 3){
      if(_align == ALING_H){
        _item_rect[i++] = rect = Gdiplus::RectF(rect.X , rect.Y + _small_h + _item_space, _small_w, _small_h);
        _item_rect[i + 3] = rect1 = Gdiplus::RectF(rect1.X , rect1.Y + _small_h + _item_space, _small_w, _small_h);
      }else {
        _item_rect[i++] = rect = Gdiplus::RectF(rect.X + rect.Width + _item_space , rect.Y, _small_w, _small_h);
        _item_rect[i + 3] = rect1 = Gdiplus::RectF(rect1.X + rect1.Width + _item_space , rect1.Y, _small_w, _small_h);
      }
      count++;
    }
  }
  int get_push_item(){
    int i = 0;
    while(i < _item_count){
      if(_item_rect[i].Contains(_click_pos))
        break;
      i++;
    }
    if(i >= 0 && i < _item_count) return i;
    return -1;
  };

  Gdiplus::RectF minus_2(Gdiplus::RectF & rc){
    return Gdiplus::RectF(rc.X + 1, rc.Y + 1, rc.Width - 2, rc.Height - 2);
  }
  Gdiplus::RectF minus_1(Gdiplus::RectF & rc){
    return Gdiplus::RectF(rc.X + 1, rc.Y + 1, rc.Width - 1, rc.Height - 1);
  }

  Gdiplus::RectF minus_rect_1(Gdiplus::RectF & rc){
    return Gdiplus::RectF(rc.X, rc.Y, rc.Width - 1, rc.Height - 1);
  }
private:
  bool _left_bt_down;
  std::vector<Gdiplus::Color> _item_color;
  std::vector<Gdiplus::RectF> _item_rect;
  std::unique_ptr<Gdiplus::Brush> _bkg_brush;

  static const int _item_count = 9;
  static const int _big_h = 31;
  static const int _big_w = 31;
  static const int _small_w = 15;
  static const int _small_h = 15;
  static const int _item_space = 1;

  int _align;
  static const int ALING_V = 0;
  static const int ALING_H = 1;
  Gdiplus::PointF _click_pos;
  Gdiplus::Color _select_color;
};
class SizeBox:public CDrawItem {
public:
  BEGIN_MSG_MAP(SizeBox)
    CHAIN_MSG_MAP(CDrawItem)
    MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
    MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
    //MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDBClick)
  END_MSG_MAP()
  SizeBox():_bkg_brush(new Gdiplus::SolidBrush(Gdiplus::Color::Gray)), \
    _left_bt_down(false), _item_rect(_item_count), _item_icon(_item_count),\
  _select_item(0){
  };
  virtual ~SizeBox(){};
  LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/){
    _click_pos.X = GET_X_LPARAM(lParam);
    _click_pos.Y = GET_Y_LPARAM(lParam);
    this->_left_bt_down = true;
    this->Invalidate();
    this->SetCapture();
    return 0;
  }
  LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/){
    if(_left_bt_down){
      int i = get_push_item();
      if(i != -1)
        _select_item = i;
    }
    this->_left_bt_down = false;

    this->Invalidate();
    ::ReleaseCapture();
    clickSignal(this);
    return 0;
  }
  void paintBkg(Gdiplus::Graphics* g){
    RECT rc;
    this->GetClientRect(&rc);

    g->FillRectangle(this->_bkg_brush.get(), rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
  };
  void paintForground(Gdiplus::Graphics* g){
    int i = 0;
    int push_item = -1;
    if(_left_bt_down){
      push_item = get_push_item();
    }
    Gdiplus::SolidBrush brush(Gdiplus::Color::Black);
    while(i < _item_count){
      if(_select_item == i){
        draw_select_item(_item_rect[i], g);
      }
      
      g->FillRectangle(&brush, _item_icon[i]);
      i++;
    }
  }
  void doSize(Gdiplus::Rect& rc){
    init_item(rc);
  }

  void bkg(CString& file){
    Gdiplus::Image image(file);
    this->_bkg_brush.reset(new Gdiplus::TextureBrush(&image));
  };
  void bkg(Gdiplus::Color& c){
    this->_bkg_brush.reset(new Gdiplus::SolidBrush(c));
  }

  void icon(CString& file){
    Gdiplus::Image image(file);
    this->_bkg_brush.reset(new Gdiplus::TextureBrush(&image));
  };
  void icon(Gdiplus::Color& c){
    this->_bkg_brush.reset(new Gdiplus::SolidBrush(c));
  }
  int get_select(){
    return _select_item;
  };
public:
  sigslot::signal1<CDrawItem*> clickSignal;

protected:
  void init_item(Gdiplus::Rect& rc, int select = 0){
    Gdiplus::Point pos(rc.Width/3 + rc.X, rc.Height/2);
    Gdiplus::REAL item_w = rc.Width/3;
    
    int i = 0;
    Gdiplus::RectF rect(0, 0, item_w, rc.Height);
    Gdiplus::RectF icon_rect;
    while(i < _item_count){
      _item_rect[i] = rect;
      rect.X = rect.X + rect.Width;
      
      icon_rect.Width = (i + 1) * 2;
      icon_rect.Height = icon_rect.Width;
      icon_rect.X = (i + 1) * pos.X - item_w /2 - icon_rect.Width/2;
      icon_rect.Y = pos.Y - icon_rect.Height/2;
      _item_icon[i] = icon_rect;
      i++;
    }
  };

  int get_push_item(){
    int i = 0;
    while(i < _item_count){
      if(_item_rect[i].Contains(_click_pos))
        break;
      i++;
    }
    if(i >= 0 && i < _item_count) return i;
    return -1;
  };

  void draw_select_item(Gdiplus::RectF rect, Gdiplus::Graphics* g){
    //Gdiplus::Pen p(Gdiplus::Color::White, 1);
    Gdiplus::Pen p(Gdiplus::Color(67, 67, 67), 1);
    //Gdiplus::SolidBrush bkg_brush(Gdiplus::Color(67, 67, 67));
    Gdiplus::SolidBrush bkg_brush(Gdiplus::Color::White);

    rect.Width -= 1;
    rect.Height -= 1;
    g->DrawRectangle(&p, rect);
    rect.X += 1;
    rect.Y += 1;
    rect.Width -= 1;
    rect.Height -= 1;

    g->FillRectangle(&bkg_brush, rect);
  };
private:
  bool _left_bt_down;
  std::unique_ptr<Gdiplus::Brush> _bkg_brush;
  std::unique_ptr<Gdiplus::Brush> _icon_brush;
  std::vector<Gdiplus::RectF> _item_rect;
  std::vector<Gdiplus::RectF> _item_icon;

  static const int _item_count = 3;
  static const int _item_space = 1;
  static const int _enlarge = 3;
  Gdiplus::PointF _click_pos;
  int _select_item;
};