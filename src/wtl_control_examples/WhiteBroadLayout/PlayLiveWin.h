
#pragma once

class PlayLiveWin :public CWindowImpl<PlayLiveWin>, public CDoubleBufferImpl< PlayLiveWin >{
public:
   BEGIN_MSG_MAP(PlayLiveWin)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    CHAIN_MSG_MAP(CDoubleBufferImpl< PlayLiveWin >)
  END_MSG_MAP()


  void DoPaint(CDCHandle dc)
  {
    CString drawText = "TEXT";
    RECT rt;

    this->GetClientRect(&rt);

    dc.Rectangle(&rt);
    dc.DrawTextW(drawText, drawText.GetLength(), &rt, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

  }
  LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
  {
    return 0;
  }
  LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/){
    this->Invalidate();
    return 0;
  }

};

class PicInPic: public PlayLiveWin{
public:
   BEGIN_MSG_MAP(PicInPic)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    CHAIN_MSG_MAP(PlayLiveWin)
  END_MSG_MAP()

  void DoPaint(CDCHandle dc)
  {
    PlayLiveWin::DoPaint(dc);
  }
  LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
  {
    PlayLiveWin::OnCreate(uMsg, wParam, lParam, bHandled);

    RECT rc;
    rc.left = 0;
    rc.top = 50;
    rc.bottom = rc.top + 37;
    rc.right = rc.left + 385;
    _bar6.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    _bar6.setBkg(_T("res\\playbarbg_1.png"));

    _in_pic.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    return 0;
  }
  LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled){
    PlayLiveWin::OnSize(uMsg, wParam, lParam, bHandled);

    RECT rc;
    this->GetClientRect(&rc);
    rc.right = rc.right - rc.left;
    rc.bottom = rc.bottom - rc.top;
    
    //center bar
    RECT bar;
    _bar6.GetClientRect(&bar);
    bar.right = bar.right - bar.left;
    bar.bottom =bar.bottom - bar.top;
    bar.left = (rc.right -bar.right) /2;
    bar.top = 5;
    _bar6.MoveWindow(bar.left, bar.top, bar.right, bar.bottom);

    //bottom in picture
    static int in_pic_w = 128;
    static int in_pic_h = 128;

    _in_pic.MoveWindow(rc.right + rc.left - in_pic_w, rc.bottom + rc.top - in_pic_h,  in_pic_w - 2, in_pic_h - 2);
    _in_pic.BringWindowToTop();

    this->Invalidate();
    return 0;
  }

  HWND outPicHwnd(){
    return this->m_hWnd;
  };
  HWND inPicHwnd(){
    return _in_pic.m_hWnd;
  };

  void hidInPic(bool hide){
    _in_pic.ShowWindow(hide ? SW_SHOW : SW_HIDE);
  }
  bool hidInPic(){
    return _in_pic.IsWindowVisible() > 0;
  }
  void inPic(int w, int h){
  }
private:
  CamerMediaBar _bar6;

  PlayLiveWin _in_pic;
};