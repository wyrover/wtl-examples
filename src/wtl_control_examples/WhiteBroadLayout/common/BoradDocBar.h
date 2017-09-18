
#pragma once
#include <set>
#include <vector>
#include <memory>
#include <time.h>
#include "sigslot.h"
#include "MenuItem.h"

class ShareBoradDocBarCall{
public:
  virtual void mouse() = 0;
  virtual void next() = 0;

  virtual void pen() = 0;
};

typedef std::shared_ptr<CDrawButton> DRAW_BTN_PTR;
typedef std::shared_ptr<CDrawSpace> DRAW_GRP_PTR;

template<class T>
class BarInfo{

protected:
  BarInfo(T* t, CString normal, CString select): _t(t), \
    _bkg_normal(normal), _bkg_select(select){};
  BarInfo(T* t):_t(t){};
  virtual ~BarInfo() {};

  DRAW_BTN_PTR mkBtn(CString normal, CString select, RECT& rc){
    DRAW_BTN_PTR bt(new CDrawButton);

    rc.top = rc.bottom + _item_space;
    rc.bottom = rc.top + _item_h;

    bt->Create(_t->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    bt->setBgColor(_bkg_normal, _bkg_select);
    bt->setIcon(normal, select, Gdiplus::Point(5, 4));

    _btn_set.insert(bt);
    return bt;
  };
  DRAW_GRP_PTR mkGroup(CString icon, RECT& rc){
    DRAW_GRP_PTR grp(new CDrawSpace);

    rc.top = rc.bottom + _item_space;
    rc.bottom = rc.top + _grp_h;

    grp->Create(_t->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    grp->setIcon(icon, _bkg_normal);

    _grp_set.insert(grp);
    return grp;
  };
protected:
  static const unsigned int _h_space = 10;
  static const unsigned int _x_space = 3;
  static const unsigned int _item_space = 5;
  static const unsigned int _item_h = 30;
  static const unsigned int _grp_h = 7;

  std::set<DRAW_BTN_PTR> _btn_set;
  std::set<DRAW_GRP_PTR> _grp_set;

  CString _bkg_normal;
  CString _bkg_select;

private:
  T* _t;
};

class MediaBar;

template<>
class BarInfo<MediaBar>{

protected:
  BarInfo(HWND t, CString normal, CString select): _t(t), \
    _bkg_normal(normal), _bkg_select(select){};
  virtual ~BarInfo() {};

  DRAW_BTN_PTR mkBtn(CString normal, CString select, RECT& rc){
    DRAW_BTN_PTR bt(new CDrawButton);

    rc.top = rc.bottom + _item_space;
    rc.bottom = rc.top + _item_h;

    bt->Create(_t, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    bt->setBgColor(_bkg_normal, _bkg_select);
    bt->setIcon(normal, select);

    _btn_set.insert(bt);
    return bt;
  };
protected:
  static const unsigned int _h_space = 10;
  static const unsigned int _x_space = 3;
  static const unsigned int _item_space = 5;
  static const unsigned int _item_h = 30;
  static const unsigned int _grp_h = 7;

  std::set<DRAW_BTN_PTR> _btn_set;
  std::set<DRAW_GRP_PTR> _grp_set;

  CString _bkg_normal;
  CString _bkg_select;
  HWND _t;
};

class CamerMediaBar;
template<>
class BarInfo<CamerMediaBar>{

protected:
  BarInfo(HWND t, CString normal, CString select): _t(t), \
    _bkg_normal(normal), _bkg_select(select){};
  virtual ~BarInfo() {};

  DRAW_BTN_PTR mkBtn(CString normal, CString select, RECT& rc){
    DRAW_BTN_PTR bt(new CDrawButton);

    rc.top = _h_space;
    rc.bottom = rc.top + _item_h;
    rc.left = rc.right + _item_space;
    rc.right = rc.left + _item_h;

    bt->Create(_t, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    bt->setBgColor(_bkg_normal, _bkg_select);
    bt->setIcon(normal, select);

    _btn_set.insert(bt);
    return bt;
  };
   DRAW_GRP_PTR mkGroup(CString icon, RECT& rc){
    DRAW_GRP_PTR grp(new CDrawSpace);

    rc.top = 0;
    rc.bottom = rc.top + _item_h;
    rc.left = rc.right + _item_space;
    rc.right = rc.left + _grp_h;

    grp->Create(_t, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    grp->setIcon(icon, _bkg_normal);

    _grp_set.insert(grp);
    return grp;
  };
protected:
  static const unsigned int _h_space = 3;
  static const unsigned int _x_space = 3;
  static const unsigned int _item_space = 5;
  static const unsigned int _item_h = 34;
  static const unsigned int _grp_h = 34;

  std::set<DRAW_BTN_PTR> _btn_set;
  std::set<DRAW_GRP_PTR> _grp_set;

  CString _bkg_normal;
  CString _bkg_select;
  HWND _t;
};

class ShareBoradDocBar
  :public CDocBar, public BarInfo<ShareBoradDocBar>, public sigslot::has_slots<>{
    DECLARE_WND_CLASS(_T("SHARE_DOC_BAR"))
    typedef BarInfo<ShareBoradDocBar> SUPER;
public:
  ShareBoradDocBar():BarInfo<ShareBoradDocBar>(this, CString(_T("res\\Toolbar-bg_1.png")), \
    CString(_T("res\\Tollbar-bg_2.png"))), _handler(NULL){};
  virtual ~ShareBoradDocBar(){};

  BEGIN_MSG_MAP(ShareBoradDocBar)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    CHAIN_MSG_MAP(CDocBar)
  END_MSG_MAP()

  LRESULT OnCreate(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled){
    LPCREATESTRUCT lpRect = (LPCREATESTRUCT)lParam;
    int width = lpRect->cx;
    int height = lpRect->cy;

    int x = SUPER::_item_space;
    int y = SUPER::_h_space;
    RECT rc = {x, 0, width - x,  0};

    DRAW_BTN_PTR btn = NULL;
    ///mouse
    btn = mkBtn(CString(_T("res\\Share_04.png")), CString(_T("res\\Share_04.png")), rc);
    btn->clickSignal.connect(this, &ShareBoradDocBar::mouse);
    mkGroup(CString(_T("res\\Toolbar-bg_3.png")), rc);

    ///next
    btn = mkBtn(CString(_T("res\\Share_05.png")), CString(_T("res\\Share_05.png")), rc);
    btn->clickSignal.connect(this, &ShareBoradDocBar::ferule);
    ///pen
    btn = mkBtn(CString(_T("res\\Share_07.png")), CString(_T("res\\Share_07.png")), rc);
    btn->clickSignal.connect(this, &ShareBoradDocBar::pen);
    mkGroup(CString(_T("res\\Toolbar-bg_3.png")), rc);

    ///line
    btn = mkBtn(CString(_T("res\\Share_09.png")), CString(_T("res\\Share_09.png")), rc);
    btn->clickSignal.connect(this, &ShareBoradDocBar::line);
    btn = mkBtn(CString(_T("res\\Share_11.png")), CString(_T("res\\Share_11.png")), rc);
    btn->clickSignal.connect(this, &ShareBoradDocBar::rect);
    btn = mkBtn(CString(_T("res\\Share_13.png")), CString(_T("res\\Share_13.png")), rc);
    btn->clickSignal.connect(this, &ShareBoradDocBar::ecllips);
    mkGroup(CString(_T("res\\Toolbar-bg_3.png")), rc);

    btn = mkBtn(CString(_T("res\\Share_15.png")), CString(_T("res\\Share_15.png")), rc);
    btn->clickSignal.connect(this, &ShareBoradDocBar::eraser);
    mkGroup(CString(_T("res\\Toolbar-bg_3.png")), rc);

    btn = mkBtn(CString(_T("res\\Share_17.png")), CString(_T("res\\Share_17.png")), rc);
    btn->clickSignal.connect(this, &ShareBoradDocBar::text);
    btn = mkBtn(CString(_T("res\\Share_19.png")), CString(_T("res\\Share_19.png")), rc);
    btn->clickSignal.connect(this, &ShareBoradDocBar::font);
    bHandled = FALSE;
    return 0;
  };

public:
  class Handler{
  public:
    virtual void choice() = 0;
    virtual void ferule() = 0;
    virtual void pen() = 0;
    
    virtual void line() = 0;
    virtual void rect() = 0;
    virtual void ecllips() = 0;
    virtual void eraser() = 0;
    virtual void text() = 0;
    virtual void font() = 0;
  };

  void handler(Handler* h){
    _handler = h;
  }
  Handler* handler(){
    return _handler;
  }

  virtual void mouse(CDrawItem*){
    if(_handler){
      _handler->choice();
    }
  }
  virtual void ferule(CDrawItem*) {
    if(_handler){
      _handler->ferule();
    }
  }
  virtual void pen(CDrawItem*) {
    if(_handler){
      _handler->pen();
    }
  }

   virtual void line(CDrawItem*){
    if(_handler){
      _handler->line();
    }
  }
  virtual void rect(CDrawItem*){
    if(_handler){
      _handler->rect();
    }
  }
  virtual void ecllips(CDrawItem*){
    if(_handler){
      _handler->ecllips();
    }
  }
  virtual void eraser(CDrawItem*){
    if(_handler){
      _handler->eraser();
    }
  }
  virtual void text(CDrawItem*){
    if(_handler){
      _handler->text();
    }
  }
  virtual void font(CDrawItem*){
    if(_handler){
      _handler->font();
    }
  }
private:
  Handler* _handler;
};

class WhitBroadBar
  :public CDocBar, public BarInfo<WhitBroadBar>, public sigslot::has_slots<>{
    DECLARE_WND_CLASS(_T("SHARE_DOC_BAR"))

    typedef  BarInfo<WhitBroadBar> SUPER;
public:
  WhitBroadBar():BarInfo<WhitBroadBar>(this, \
    CString(_T("res\\Toolbar-bg_1.png")), CString(_T("res\\Tollbar-bg_2.png"))),_handler(NULL){};
  virtual ~WhitBroadBar(){};

  BEGIN_MSG_MAP(WhitBroadBar)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    CHAIN_MSG_MAP(CDocBar)
  END_MSG_MAP()


  LRESULT OnCreate(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled){
    LPCREATESTRUCT lpRect = (LPCREATESTRUCT)lParam;
    int width = lpRect->cx;
    int height = lpRect->cy;

    int x = SUPER::_item_space;
    int y = SUPER::_h_space;
    RECT rc = {x, 0, width - x,  0};
    bHandled = FALSE;

    DRAW_BTN_PTR btn = NULL;

    ///mouse
    btn = mkBtn(CString(_T("res\\W-board_01.png")), CString(_T("res\\W-board_01.png")), rc);
    btn->clickSignal.connect(this, &WhitBroadBar::setting);
    mkGroup(CString(_T("res\\Toolbar-bg_3.png")), rc);

    ///next
    btn = mkBtn(CString(_T("res\\W-board_03.png")), CString(_T("res\\W-board_03.png")), rc);
    btn->clickSignal.connect(this, &WhitBroadBar::choice);
    mkGroup(CString(_T("res\\Toolbar-bg_3.png")), rc);

    ///line
    btn = mkBtn(CString(_T("res\\W-board_05.png")), CString(_T("res\\W-board_05.png")), rc);
    btn->clickSignal.connect(this, &WhitBroadBar::templat);
    btn = mkBtn(CString(_T("res\\W-board_07.png")), CString(_T("res\\W-board_07.png")), rc);
    btn->clickSignal.connect(this, &WhitBroadBar::fomula);
    btn = mkBtn(CString(_T("res\\W-board_09.png")), CString(_T("res\\W-board_09.png")), rc);
    btn->clickSignal.connect(this, &WhitBroadBar::text);
    mkGroup(CString(_T("res\\Toolbar-bg_3.png")), rc);

    btn = mkBtn(CString(_T("res\\W-board_11.png")), CString(_T("res\\W-board_11.png")), rc);
    btn->clickSignal.connect(this, &WhitBroadBar::resource);
    btn = mkBtn(CString(_T("res\\W-board_13.png")), CString(_T("res\\W-board_13.png")), rc);
    btn->clickSignal.connect(this, &WhitBroadBar::picture);
    btn = mkBtn(CString(_T("res\\W-board_15.png")), CString(_T("res\\W-board_15.png")), rc);
    btn->clickSignal.connect(this, &WhitBroadBar::highlight);
    mkGroup(CString(_T("res\\Toolbar-bg_3.png")), rc);

    btn = mkBtn(CString(_T("res\\W-board_17.png")), CString(_T("res\\W-board_17.png")), rc);
    btn->clickSignal.connect(this, &WhitBroadBar::line);
    btn = mkBtn(CString(_T("res\\W-board_19.png")), CString(_T("res\\W-board_19.png")), rc);
    btn->clickSignal.connect(this, &WhitBroadBar::dotted);
    btn = mkBtn(CString(_T("res\\W-board_21.png")), CString(_T("res\\W-board_21.png")), rc);
    btn->clickSignal.connect(this, &WhitBroadBar::handraw);
    return 0;
  };
public:
  class Handler{
  public:
    virtual void setting() = 0;
    virtual void choice() = 0;
    virtual void templat() = 0;

    virtual void fomula() = 0;
    virtual void text() = 0;

    virtual void resource() = 0;
    virtual void picture() = 0;
    virtual void highlight() = 0;
    virtual void line() = 0;
    virtual void dotted() = 0;
    virtual void handraw() = 0;
  };

  void handler(Handler* h){
    _handler = h;
  }
  Handler* handler(){
    return _handler;
  }

  void setting(CDrawItem*){
    if(_handler){
      _handler->setting();
    }
  }
  virtual void choice(CDrawItem*){
     if(_handler){
      _handler->choice();
    }
  }
  virtual void templat(CDrawItem*) {
     if(_handler){
      _handler->templat();
    }
  }

  virtual void fomula(CDrawItem*){
     if(_handler){
      _handler->fomula();
    }
  }
  virtual void text(CDrawItem*){
     if(_handler){
      _handler->text();
    }
  }
  virtual void resource(CDrawItem*){
     if(_handler){
      _handler->resource();
    }
  }
  virtual void picture(CDrawItem*){
     if(_handler){
      _handler->picture();
    }
  }
  virtual void highlight(CDrawItem*){
     if(_handler){
      _handler->highlight();
    }
  }
  virtual void line(CDrawItem*){
     if(_handler){
      _handler->line();
    }
  }
  virtual void dotted(CDrawItem*){
     if(_handler){
      _handler->dotted();
    }
  }
  virtual void handraw(CDrawItem*){
     if(_handler){
      _handler->handraw();
    }
  }
  virtual void add_page(CDrawItem*){
     if(_handler){
     // _handler->add_page();
    }
  }
private:
  Handler* _handler;
};


class MediaBar
  :public CDocBar, public BarInfo<MediaBar>, \
  public sigslot::has_slots<>{
    DECLARE_WND_CLASS(_T("SHARE_DOC_BAR"))

    typedef  BarInfo<MediaBar> SUPER;
public:
  class Handler{
  public:
    virtual void audio(bool status) = 0;
    virtual void video(bool status) = 0;
  };
public:
  MediaBar():BarInfo<MediaBar>(this->m_hWnd, \
    CString(_T("res\\Toolbar-bg_1.png")), CString(_T("res\\Tollbar-bg_2.png"))), \
    _audio_active(true), _vedio_active(true), _handler(NULL){};
  virtual ~MediaBar(){};

  BEGIN_MSG_MAP(MediaBar)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    CHAIN_MSG_MAP(CDocBar)
  END_MSG_MAP()


  LRESULT OnCreate(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled){
    LPCREATESTRUCT lpRect = (LPCREATESTRUCT)lParam;
    int width = lpRect->cx;
    int height = lpRect->cy;

    int x = SUPER::_item_space;
    int y = SUPER::_h_space;
    RECT rc = {x, 0, width - x,  0};

    BarInfo<MediaBar>::_t = this->m_hWnd;

    DRAW_BTN_PTR bt = mkBtn(CString(_T("res\\Voice_6.png")), CString(_T("res\\Voice_6.png")), rc);
    bt->clickSignal.connect(this, &MediaBar::audioActvie);
    bt = mkBtn(CString(_T("res\\Voice_2.png")), CString(_T("res\\Voice_2.png")), rc);
    bt->clickSignal.connect(this, &MediaBar::vidoActive);
    bHandled = FALSE;
    return 0;
  };

  void setHandler(Handler* h){
    this->_handler = h;
  };
public:
  void audioActvie(CDrawItem* item){
    CDrawButton* bt = dynamic_cast<CDrawButton*>(item);
    if(_audio_active){
      bt->setIcon(CString(_T("res\\Voice_1.png")), CString(_T("res\\Voice_1.png")));
    }else {
      bt->setIcon(CString(_T("res\\Voice_6.png")), CString(_T("res\\Voice_6.png")));
    }
    _audio_active = !_audio_active;
    if(_handler){
      _handler->audio(_audio_active);
    }
  };

  void vidoActive(CDrawItem* item){
    CDrawButton* bt = dynamic_cast<CDrawButton*>(item);
    if(_vedio_active){
      bt->setIcon(CString(_T("res\\Voice_3.png")), CString(_T("res\\Voice_3.png")));
    }else {
      bt->setIcon(CString(_T("res\\Voice_2.png")), CString(_T("res\\Voice_2.png")));
    }
    _vedio_active = !_vedio_active;
    if(_handler){
      _handler->video(_vedio_active);
    }
  }
private:
  bool _audio_active;
  bool _vedio_active;
  Handler* _handler;
};



class LastNextBar
  :public CDocBar, public sigslot::has_slots<>{
public:
  DECLARE_WND_CLASS(_T("SHARE_DOC_BAR"))

   BEGIN_MSG_MAP(LastNextBar)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    CHAIN_MSG_MAP(CDocBar)
  END_MSG_MAP()

  LastNextBar():_handler(NULL){
    this->setBkg(Gdiplus::Color::White);
    this->canMove(false);
  };
  virtual ~LastNextBar(){};
  LRESULT OnCreate(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/){
    RECT rc = {0, 0, _item_w,  _item_h};
    DRAW_BTN_PTR bt(new CDrawButton);

    bt->Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    bt->setIcon(CString(_T("res\\Page_01.png")), CString(_T("res\\Page_02.png")));
    bt->setBgColor(Gdiplus::Color::White, Gdiplus::Color::White);
    bt->ellipse(true);
    bt->clickSignal.connect(this, &LastNextBar::last);
    _btn_set.push_back(bt);

    bt.reset(new CDrawButton);
    bt->Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    bt->setIcon(CString(_T("res\\Page_03.png")), CString(_T("res\\Page_04.png")));
    bt->setBgColor(Gdiplus::Color::White, Gdiplus::Color::White);
    bt->ellipse(true);
    bt->clickSignal.connect(this, &LastNextBar::next);
    _btn_set.push_back(bt);
  

    return 0;
  }
  LRESULT OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/){
    RECT rc = {0, 0, 0,  _item_h};
    unsigned int i = 0;
    while(i < _btn_set.size()){
      mkBtn(_btn_set[i], rc, i);
      i++;
    }
    return 0;
  }
public:
  class Handler{
  public:
    virtual void next() = 0;
    virtual void last() = 0;
  };

  void next(CDrawItem* ){
    if(_handler){
      _handler->next();
    }
  };
  void last(CDrawItem* ){
    if(_handler){
      _handler->last();
    }
  };
protected:
  void mkBtn(DRAW_BTN_PTR bt, RECT& rc, int c){
     rc.left = rc.right + _item_space * c;
     rc.right = rc.left + _item_w;

     bt->MoveWindow(&rc);
  };

private:
  static const unsigned int _y_bottom = 15;
  static const unsigned int _total_w = 110;
  static const unsigned int _item_space = 10;
  static const unsigned int _item_w = 23;
  static const unsigned int _item_h = 26;

  std::vector<DRAW_BTN_PTR> _btn_set;
  Handler* _handler;
};

class PlayBar
  :public CDocBar, public sigslot::has_slots<>{
public:
  DECLARE_WND_CLASS(_T("PLAY_BAR"))

   BEGIN_MSG_MAP(PlayBar)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    CHAIN_MSG_MAP(CDocBar)
  END_MSG_MAP()
  PlayBar():_handler(NULL), _bPlay(false){};
  virtual ~PlayBar(){};

  LRESULT OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/){

    return 0;
  }

  LRESULT OnCreate(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled){
    bHandled = FALSE;
    RECT rc ={_bar_x, _bar_y, _btn_w + _bar_x, _bar_h + _bar_y};
    rc.top = 2;
    rc.bottom = rc.top + 27;
    _play.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    _play.setBgColor(CString(_T("res\\playbarbg_1.png")), CString(_T("res\\playbarbg_1.png")));
    _play.setIcon(CString(_T("res\\play_4.png")), CString(_T("res\\play_4_2.png")), Gdiplus::Point(0, 0));
    _play.clickSignal.connect(this, &PlayBar::play);

    rc.top = _bar_y;
    rc.bottom = rc.top + _bar_h;
    rc.left = rc.right + _bar_space;
    rc.right = rc.left + _bar_w;
    _bar.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    _bar.setBkg(CString(_T("res\\playbarbg_1.png")));
    _bar.setPen(CString(_T("res\\playbarbg_3.png")));
    _bar.setPlay(CString(_T("res\\playbarbg_2.png")));
    _bar.setCache(CString(_T("res\\playbarbg_4.png")));

    rc.left = rc.right + _bar_space;
    rc.right = rc.left + _audio_bar_w;
    _audio.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    _audio.setBkg(CString(_T("res\\playbarbg_1.png")));
    _audio.setEnable(CString(_T("res\\playbarbg_2.png")));
    _audio.setDisable(CString(_T("res\\playbarbg_4.png")));

    rc.top = 2;
    rc.bottom = rc.top + 27;
    rc.left = rc.right;
    rc.right = rc.left + _audio_bar_w;
    _add_audio.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    _add_audio.setBgColor(CString(_T("res\\playbarbg_1.png")), CString(_T("res\\playbarbg_1.png")));
    _add_audio.setIcon(CString(_T("res\\play_2.png")), CString(_T("res\\play_8.png")), Gdiplus::Point(0, 0));
    _add_audio.clickSignal.connect(this, &PlayBar::addVoice);

    rc.top = 2;
    rc.bottom = rc.top + 27;
    rc.left = rc.right;
    rc.right = rc.left + _audio_bar_w;
    _reduce_audio.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    _reduce_audio.setBgColor(CString(_T("res\\playbarbg_1.png")), CString(_T("res\\playbarbg_1.png")));
    _reduce_audio.setIcon(CString(_T("res\\play_7.png")), CString(_T("res\\play_9.png")), Gdiplus::Point(0, 0));
    _reduce_audio.clickSignal.connect(this, &PlayBar::reduceVoice);

    rc.top = 2;
    rc.bottom = rc.top + 27;
    rc.left = rc.right;
    rc.right = rc.left + _audio_bar_w;
    _full_win.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    _full_win.setBgColor(CString(_T("res\\playbarbg_1.png")), CString(_T("res\\playbarbg_1.png")));
    _full_win.setIcon(CString(_T("res\\play_3.png")), CString(_T("res\\play_6.png")), Gdiplus::Point(0, 0));
    _full_win.clickSignal.connect(this, &PlayBar::fullWin);

   return 0;
  }

public:
  
  void addVoice(CDrawItem* ){
    this->_audio.enable(this->_audio.enable() + 1);
    if(_handler){
      long v = (long)((double)this->_audio.enable() / (double)this->_audio.all() * 100);
      _handler->volume(v);
    }
  };

  void reduceVoice(CDrawItem* ){
    if(this->_audio.enable() > 0){
      this->_audio.enable(this->_audio.enable() - 1);
      if(_handler){
        long v = (long)((double)this->_audio.enable() / (double)this->_audio.all() * 100);
        _handler->volume(v);
      }
    }
  };
  void fullWin(CDrawItem* ){
    if(_handler){
      _handler->fullWin();
    }
  };
  
  void play(CDrawItem* ){
    if(_bPlay){
      _play.setIcon(CString(_T("res\\play_4.png")), CString(_T("res\\play_4_2.png")), Gdiplus::Point(0, 0));
    }else {
      _play.setIcon(CString(_T("res\\play_4_3.png")), CString(_T("res\\play_4_4.png")), Gdiplus::Point(0, 0));
    }
    _bPlay = !_bPlay;
    
    if(_handler){
      _bPlay ? _handler->play(): _handler->pause();
    }
  };
  
  void play(bool p){
    _bPlay = !p;
    play((CDrawItem*)NULL);
  }
  
  class Handler{
  public:
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void fullWin() = 0;
    virtual void volume(long ) = 0;
  };

  void setHandler(Handler* h){
    _handler = h;
  };
  void progress(float p){
    _bar.progress(p);
  }
  void cache(float c){
    _bar.cache(c);
  }
private:
  CProgressBar _bar;
  static const unsigned int _bar_x = 10;
  static const unsigned int _bar_y = 10;
  static const unsigned int _bar_w = 370;
  static const unsigned int _bar_h = 12;
  static const unsigned int _bar_space = 10;
  CAudioBar _audio;
  static const unsigned int _audio_bar_w = 33;

  CDrawButton _play;
  CDrawButton _add_audio;
  CDrawButton _reduce_audio;
  CDrawButton _full_win;
  static const unsigned int _btn_w = 34;
  bool _bPlay;

  Handler* _handler;
  
};

class CamerMediaBar :public CDocBar, public BarInfo<CamerMediaBar>, \
  public sigslot::has_slots<>{
  typedef  BarInfo<CamerMediaBar> SUPER;
public:
  class Handler{
  public:
    virtual void audio(bool status) = 0;
    virtual void video(bool status) = 0;
    virtual void microphone(bool status) = 0;
    virtual void docked(bool status) = 0;
  };
public:
  CamerMediaBar():BarInfo<CamerMediaBar>(this->m_hWnd, \
    CString(_T("res\\playbarbg_1.png")), CString(_T("res\\playbarbg_1.png"))), \
    _audio_active(true), _vedio_active(true), _handler(NULL), \
    _docked(false), _microphone(true){};
  virtual ~CamerMediaBar(){
    if(this->m_hWnd){
      this->KillTimer(TIMER_ID);
    }
  };

  BEGIN_MSG_MAP(MediaBar)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_TIMER, OnTimer)
    CHAIN_MSG_MAP(CDocBar)
  END_MSG_MAP()


  LRESULT OnCreate(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled){
    LPCREATESTRUCT lpRect = (LPCREATESTRUCT)lParam;
    int width = lpRect->cx;
    int height = lpRect->cy;

    int x = SUPER::_item_space;
    int y = SUPER::_h_space;
    RECT rc = {x, y, x + 65,  SUPER::_item_h + y};

    BarInfo<CamerMediaBar>::_t = this->m_hWnd;

    rc.bottom = rc.top + 30;
    _static.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN | SS_CENTER | SS_CENTERIMAGE );
    _static.SetWindowTextW(CString(_T("00:00:00")));
    mkGroup(CString(_T("res\\Live_6.png")), rc);

    DRAW_BTN_PTR bt = mkBtn(CString(_T("res\\Voice_6.png")), CString(_T("res\\Voice_6.png")), rc);
    bt->clickSignal.connect(this, &CamerMediaBar::microPhone);
    bt = mkBtn(CString(_T("res\\Live_18.png")), CString(_T("res\\Live_18.png")), rc);
    bt->clickSignal.connect(this, &CamerMediaBar::audioActvie);
    mkGroup(CString(_T("res\\Live_6.png")), rc);

    bt = mkBtn(CString(_T("res\\Live_19.png")), CString(_T("res\\Live_19.png")), rc);
    bt->clickSignal.connect(this, &CamerMediaBar::dock);
    bt = mkBtn(CString(_T("res\\Voice_2.png")), CString(_T("res\\Voice_2.png")), rc);
    bt->clickSignal.connect(this, &CamerMediaBar::videoActive);
    mkGroup(CString(_T("res\\Live_6.png")), rc);

    bt = mkBtn(CString(_T("res\\Live_21.png")), CString(_T("res\\Live_21.png")), rc);
    bHandled = FALSE;

    this->SetTimer(TIMER_ID, 1000);
    _start_time = time(NULL);
    return 0;
  };
  LRESULT OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled){

    time_t current_time = time(NULL);
    long time_used = (long)difftime(current_time, _start_time);

    char buf[128];
    sprintf(buf, "%02d:%02d:%02d", time_used /(60 * 60), time_used%(60*60)/60, ((long)time_used%60));
    this->_static.SetWindowTextW(CString(buf));
    return 0;
  };
public:
  
  void setHandler(Handler* h){
    this->_handler = h;
  };

  void microPhone(CDrawItem* item){
    CDrawButton* bt = dynamic_cast<CDrawButton*>(item);
    if(_microphone){
      bt->setIcon(CString(_T("res\\Voice_1.png")), CString(_T("res\\Voice_1.png")));
    }else {
      bt->setIcon(CString(_T("res\\Voice_6.png")), CString(_T("res\\Voice_6.png")));
    }
    _microphone = !_microphone;
    if(_handler){
      _handler->microphone(_microphone);
    }
  };

  void audioActvie(CDrawItem* item){
    CDrawButton* bt = dynamic_cast<CDrawButton*>(item);
    if(_audio_active){
      bt->setIcon(CString(_T("res\\Live_17.png")), CString(_T("res\\Live_17.png")));
    }else {
      bt->setIcon(CString(_T("res\\Live_18.png")), CString(_T("res\\Live_18.png")));
    }
    _audio_active = !_audio_active;
    if(_handler){
      _handler->audio(_audio_active);
    }
  };

  void dock(CDrawItem* item){
    CDrawButton* bt = dynamic_cast<CDrawButton*>(item);
    if(_docked){
      bt->setIcon(CString(_T("res\\Live_19.png")), CString(_T("res\\Live_19.png")));
    }else {
      bt->setIcon(CString(_T("res\\Live_20.png")), CString(_T("res\\Live_20.png")));
    }
    _docked = !_docked;
    if(_handler){
      _handler->docked(_docked);
    }
  };

  void videoActive(CDrawItem* item){
    CDrawButton* bt = dynamic_cast<CDrawButton*>(item);
    if(_vedio_active){
      bt->setIcon(CString(_T("res\\Voice_3.png")), CString(_T("res\\Voice_3.png")));
    }else {
      bt->setIcon(CString(_T("res\\Voice_2.png")), CString(_T("res\\Voice_2.png")));
    }
    _vedio_active = !_vedio_active;
    if(_handler){
      _handler->audio(_vedio_active);
    }
  };
private:
  bool _audio_active;
  bool _microphone;
  bool _docked;
  bool _vedio_active;
  Handler* _handler;
  CStatic _static;

  static const unsigned int TIMER_ID = 0x003;
  time_t _start_time;
};

class LineInfoPanel:public CDocBar, \
  public sigslot::has_slots<>{
public:
  BEGIN_MSG_MAP(LineInfoPanel)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_TIMER, OnTimer)
    CHAIN_MSG_MAP(CDocBar)
  END_MSG_MAP()

  LRESULT OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled){
    return 0;
  };
  LRESULT OnCreate(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled){
    LPCREATESTRUCT lpRect = (LPCREATESTRUCT)lParam;
    int width = lpRect->cx;
    int height = lpRect->cy;

    this->setBkg(Gdiplus::Color::Gray);
    RECT rc = {_bar_x, (height - _item_h)/2, _bar_x + _item_w, height - _item_h/2};

    _bt1.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    _bt1.setBgColor(Gdiplus::Color::Gray, Gdiplus::Color::Gray);
    _bt1.setIcon(CString(_T("res\\1.png")), CString(_T("res\\5.png")));

    rc.left = rc.right;
    rc.right = rc.left + _item_w;
    _bt2.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    _bt2.setBgColor(Gdiplus::Color::Gray, Gdiplus::Color::Gray);
    _bt2.setIcon(CString(_T("res\\2.png")), CString(_T("res\\4.png")));

    rc.left = rc.right;
    rc.right = rc.left + _item_w;
    _bt3.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    _bt3.setBgColor(Gdiplus::Color::Gray, Gdiplus::Color::Gray);
    _bt3.setIcon(CString(_T("res\\3.png")), CString(_T("res\\6.png")));

    rc.left = rc.right;
    rc.right = rc.left + 150;
    rc.top = 5;
    rc.bottom = rc.top + 25;
    _box.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    return 0;
  }

private:
   static const unsigned int _bar_x = 2;
   static const unsigned int _bar_y = 2;

   static const unsigned int _item_w = 12;
   static const unsigned int _item_h = 12;

   CDrawButton _bt1;
   CDrawButton _bt2;
   CDrawButton _bt3;

   ColorBox _box;
};

class TmpBar:public CDocBar, \
  public sigslot::has_slots<>, public BarInfo<TmpBar>{
    typedef BarInfo<TmpBar> SUPER;
    public:
  BEGIN_MSG_MAP(TmpBar)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_TIMER, OnTimer)
    CHAIN_MSG_MAP(CDocBar)
  END_MSG_MAP()
  TmpBar(): BarInfo<TmpBar>(this), _pen_or_mouse(true), _handler(NULL){
  }
  LRESULT OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled){
    return 0;
  };
  LRESULT OnCreate(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled){
    int x = SUPER::_item_space;
    int y = SUPER::_h_space;

    LPCREATESTRUCT lpRect = (LPCREATESTRUCT)lParam;
    int width = lpRect->cx;
    int height = lpRect->cy;

    RECT rc = {x, 0, width - x,  0};
    bHandled = FALSE;

    DRAW_GRP_PTR grp = NULL;

    _pen_mouse = mkBtn(CString(_T("res\\pen_black.png")), CString(_T("res\\Share_07.png")), rc);
    _pen_mouse->setBgColor(Gdiplus::Color(210, 210, 210), Gdiplus::Color(67, 67, 67));
    _pen_mouse->clickSignal.connect(this, &TmpBar::pen);
    grp = mkGroup(CString(_T("res\\Toolbar-bg_3.png")), rc);
    grp->setbkg(Gdiplus::Color(210, 210, 210));

    rc.top = rc.bottom + SUPER::_h_space;
    rc.bottom = 95 + rc.top;
    _box.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    _box.bkg(Gdiplus::Color(210, 210, 210));
    _box.clickSignal.connect(this, &TmpBar::color);

    rc.top = rc.bottom + SUPER::_h_space;
    rc.bottom = 15 + rc.top;
    _size_box.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    _size_box.bkg(Gdiplus::Color(210, 210, 210));
    _size_box.clickSignal.connect(this, &TmpBar::size);

    pen(NULL);
    return 0;
  }
  class Handler{
  public:
    virtual void infoChange(int pen, COLORREF color, int size) = 0;

    static const unsigned short DEVICE_PEN = 1;
    static const unsigned short DEVICE_MOUSE = 2;
  };
  void handler(Handler* h){
    _handler = h;
  }
protected:
  friend class sigslot::has_slots<>;

  void pen(CDrawItem*){
    if(_pen_or_mouse){
      _pen_mouse->setIcon(CString(_T("res\\mouse2.png")), CString(_T("res\\mouse1.png")), Gdiplus::Point(5, 4));
    }else {
      _pen_mouse->setIcon(CString(_T("res\\pen_black.png")), CString(_T("res\\Share_07.png")), Gdiplus::Point(5, 4));
    }

    _pen_or_mouse = !_pen_or_mouse;
    if(_handler){
      Gdiplus::Color c = _box.get_color();
      _handler->infoChange( _pen_or_mouse ? Handler::DEVICE_PEN : Handler::DEVICE_MOUSE, \
        c.ToCOLORREF(), _size_box.get_select());
    }
  };
  void color(CDrawItem*){
    if(_handler){
      Gdiplus::Color c = _box.get_color();
      _handler->infoChange( _pen_or_mouse ? Handler::DEVICE_PEN : Handler::DEVICE_MOUSE, \
        c.ToCOLORREF(), _size_box.get_select());
    }
  }
  void size(CDrawItem*){
    if(_handler){
      Gdiplus::Color c = _box.get_color();
      _handler->infoChange( _pen_or_mouse ? Handler::DEVICE_PEN : Handler::DEVICE_MOUSE, \
        c.ToCOLORREF(), _size_box.get_select());
    }
  };
private:
   ColorBox _box;
   SizeBox _size_box;
   DRAW_BTN_PTR _pen_mouse;

   bool _pen_or_mouse;
   Handler* _handler;
};