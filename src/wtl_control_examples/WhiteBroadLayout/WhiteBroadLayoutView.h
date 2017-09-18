// WhiteBroadLayoutView.h : interface of the CWhiteBroadLayoutView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include <atlsplit.h>

class CtrlConfig
{
};

class CWhiteBroadLayoutView : public CWindowImpl<CWhiteBroadLayoutView>
{
public:
  DECLARE_WND_CLASS(NULL)

  BOOL PreTranslateMessage(MSG* pMsg)
  {
    pMsg;
    return FALSE;
  }

  BEGIN_MSG_MAP(CWhiteBroadLayoutView)
    MESSAGE_HANDLER(WM_PAINT, OnPaint)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
  END_MSG_MAP()

  // Handler prototypes (uncomment arguments if needed):
  //	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
  //	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
  //	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

  LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
  {
    CPaintDC dc(m_hWnd);

    //TODO: Add your drawing code here

    return 0;
  }

  LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
  {
    RECT rect;
    GetClientRect(&rect);
    m_wndSplitter.ResizeClient(rect.right - rect.left, rect.bottom - rect.top);
    m_wndSplitter.SetSplitterPos((rect.right - rect.left)/2);
    //this->UpdateWindow();

    //_ctrl->ReSize(rect);
    return 0;
  }

  LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
  {
    CString title = _T("");
    m_hWndClient = m_wndSplitter.Create(m_hWnd, rcDefault, NULL, \
      WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

    _hLeft = _left.Create(m_hWndClient, rcDefault, title, \
      WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    _hRigt = _right.Create(m_hWndClient, rcDefault, title, \
      WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

    m_wndSplitter.SetSplitterPanes(_hLeft, _hRigt);
    
    //_ctrl = new CWhiteBoardShow;
    //_ctrl->CreatorCtrl(&_config);

    //CString name(_T("abc"));
    //_ctrl->CreateEx(name, this->m_hWnd);
    //_ctrl->ShowWindow(SW_SHOW);
    return 0;
  }

private:
  CSplitterWindow m_wndSplitter;
  CCustomTabView _left;
  CCustomTabView _right;
  HWND m_hWndClient;
  HWND _hLeft;
  HWND _hRigt;

 /* ICtrlBase* _ctrl;

  CtrlConfig _config;*/
};


class PlayCtrlView : public CWindowImpl<CWhiteBroadLayoutView>,
  public PlayBar::Handler
{
public:
  DECLARE_WND_CLASS(NULL)

  BOOL PreTranslateMessage(MSG* pMsg)
  {
    pMsg;
    return FALSE;
  }

  BEGIN_MSG_MAP(CWhiteBroadLayoutView)
    MESSAGE_HANDLER(WM_PAINT, OnPaint)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
  END_MSG_MAP()

  // Handler prototypes (uncomment arguments if needed):
  //	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
  //	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
  //	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

  LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
  {
    CPaintDC dc(m_hWnd);

    //TODO: Add your drawing code here

    return 0;
  }

  LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
  {
   
    return 0;
  }

  LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
  {
    RECT rc = {10, 10, 566 + 10, 330};      
    _play_ctrl.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

    rc.top = rc.bottom;
    rc.bottom = rc.top + 32;
    rc.right = rc.left + 566;
    _bar.canMove(false);
    _bar.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD|WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    _bar.setBkg(_T("res\\playbarbg_1.png"));
    _bar.setHandler(this);
    return 0;
  }
  virtual void play(){
    _play_ctrl.play(CString(_T("D:\\a\\a.wmv")));
  }
  virtual void pause(){
    _play_ctrl.pause(true);
  }
  virtual void stop(){
  }
  virtual void fullWin(){
    _play_ctrl.full_win(true);
  }
  virtual void volume(long v){
    _play_ctrl.volume(v);
  }
protected:
  PlayCtrl _play_ctrl;

  PlayBar _bar;
};
