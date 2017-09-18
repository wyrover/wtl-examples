#pragma once

#include <wmp.h>
#include <sigslot.h>
class PlayerEvent:public IWMPEvents
{
public:
  virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject) {
      if(riid == __uuidof(IWMPEvents)){
        *ppvObject = this;
        return S_OK;
      }
      return S_FALSE;
  };

  virtual ULONG STDMETHODCALLTYPE AddRef( void) {
    return 1;
  };

  virtual ULONG STDMETHODCALLTYPE Release( void) {
    return 1;
  };
  void STDMETHODCALLTYPE OpenStateChange( 
    /* [in] */ long NewState){
  };

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE PlayStateChange( 
    /* [in] */ long NewState) {
  };

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE AudioLanguageChange( 
    /* [in] */ long LangID) {
  };

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE StatusChange( void){
  };

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE ScriptCommand( 
    /* [in] */ BSTR scType,
    /* [in] */ BSTR Param) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE NewStream( void) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE Disconnect( 
    /* [in] */ long Result) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE Buffering( 
    /* [in] */ VARIANT_BOOL Start) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE Error( void){};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE Warning( 
    /* [in] */ long WarningType,
    /* [in] */ long Param,
    /* [in] */ BSTR Description) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE EndOfStream( 
    /* [in] */ long Result) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE PositionChange( 
    /* [in] */ double oldPosition,
    /* [in] */ double newPosition) {
      return ;
  };

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE MarkerHit( 
    /* [in] */ long MarkerNum){};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE DurationUnitChange( 
    /* [in] */ long NewDurationUnit) {
      
  };

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE CdromMediaChange( 
    /* [in] */ long CdromNum) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE PlaylistChange( 
    /* [in] */ IDispatch *Playlist,
    /* [in] */ WMPPlaylistChangeEventType change){};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE CurrentPlaylistChange( 
    /* [in] */ WMPPlaylistChangeEventType change) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE CurrentPlaylistItemAvailable( 
    /* [in] */ BSTR bstrItemName){};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE MediaChange( 
    /* [in] */ IDispatch *Item) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE CurrentMediaItemAvailable( 
    /* [in] */ BSTR bstrItemName) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE CurrentItemChange( 
    /* [in] */ IDispatch *pdispMedia) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE MediaCollectionChange( void) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE MediaCollectionAttributeStringAdded( 
    /* [in] */ BSTR bstrAttribName,
    /* [in] */ BSTR bstrAttribVal) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE MediaCollectionAttributeStringRemoved( 
    /* [in] */ BSTR bstrAttribName,
    /* [in] */ BSTR bstrAttribVal) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE MediaCollectionAttributeStringChanged( 
    /* [in] */ BSTR bstrAttribName,
    /* [in] */ BSTR bstrOldAttribVal,
    /* [in] */ BSTR bstrNewAttribVal){};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE PlaylistCollectionChange( void) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE PlaylistCollectionPlaylistAdded( 
    /* [in] */ BSTR bstrPlaylistName) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE PlaylistCollectionPlaylistRemoved( 
    /* [in] */ BSTR bstrPlaylistName) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE PlaylistCollectionPlaylistSetAsDeleted( 
    /* [in] */ BSTR bstrPlaylistName,
    /* [in] */ VARIANT_BOOL varfIsDeleted) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE ModeChange( 
    /* [in] */ BSTR ModeName,
    /* [in] */ VARIANT_BOOL NewValue) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE MediaError( 
    /* [in] */ IDispatch *pMediaObject) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE OpenPlaylistSwitch( 
    /* [in] */ IDispatch *pItem) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE DomainChange( 
    /* [in] */ BSTR strDomain) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE SwitchedToPlayerApplication( void){};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE SwitchedToControl( void) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE PlayerDockedStateChange( void){};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE PlayerReconnect( void) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE Click( 
    /* [in] */ short nButton,
    /* [in] */ short nShiftState,
    /* [in] */ long fX,
    /* [in] */ long fY) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE DoubleClick( 
    /* [in] */ short nButton,
    /* [in] */ short nShiftState,
    /* [in] */ long fX,
    /* [in] */ long fY) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE KeyDown( 
    /* [in] */ short nKeyCode,
    /* [in] */ short nShiftState) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE KeyPress( 
    /* [in] */ short nKeyAscii) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE KeyUp( 
    /* [in] */ short nKeyCode,
    /* [in] */ short nShiftState) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE MouseDown( 
    /* [in] */ short nButton,
    /* [in] */ short nShiftState,
    /* [in] */ long fX,
    /* [in] */ long fY) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE MouseMove( 
    /* [in] */ short nButton,
    /* [in] */ short nShiftState,
    /* [in] */ long fX,
    /* [in] */ long fY) {};

  virtual /* [helpstring][id] */ void STDMETHODCALLTYPE MouseUp( 
    /* [in] */ short nButton,
    /* [in] */ short nShiftState,
    /* [in] */ long fX,
    /* [in] */ long fY) {};

  HRESULT Invoke(
    DISPID  dispIdMember,      
    REFIID  riid,              
    LCID  lcid,                
    WORD  wFlags,              
    DISPPARAMS FAR*  pDispParams,  
    VARIANT FAR*  pVarResult,  
    EXCEPINFO FAR*  pExcepInfo,  
    unsigned int FAR*  puArgErr ){
      return 0;
  }

  virtual void progress(double ){
  };
};
class PlayCtrl :public CWindowImpl<PlayCtrl>, \
  public CDoubleBufferImpl< PlayCtrl >, \
  public PlayerEvent{
public:
  BEGIN_MSG_MAP(PlayCtrl)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    MESSAGE_HANDLER(WM_DESTROY, OnDestory)
    MESSAGE_HANDLER(WM_TIMER, OnTimer)
    CHAIN_MSG_MAP(CDoubleBufferImpl< PlayCtrl >)
  END_MSG_MAP()

  PlayCtrl():_advise_cookie(0), _event(this){
  }
  virtual ~PlayCtrl(){
  }

  void DoPaint(CDCHandle /*dc*/)
  {
  }
  LRESULT OnDestory(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/){
     if(play()){
      this->stop();
    }

    unregister_event();

    _wmp_window.DestroyWindow();
    return 0;
  }
  LRESULT OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/){
    if(wParam== PLAY_TIMER){
      double p = this->position() / this->length();
      this->progress(p);
    }

    return 0;
  }
  LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
  {
    RECT rc;
    this->GetClientRect(&rc);

    HWND hnd =_wmp_window.Create(this->m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD);
    HRESULT hr = _wmp_window.CreateControl(CString(_T("{6BF52A52-394A-11d3-B153-00C04F79FAA6}")));
    if(FAILED(hr)) return 0;

    _wmp_window.QueryControl(&m_spWMPPlayer);

    BSTR mode = ::SysAllocString(_T("none"));
    m_spWMPPlayer->put_uiMode(mode);
    ::SysFreeString(mode);

    m_spWMPPlayer->get_controls(&m_spWMPCtrler);
    m_spWMPPlayer->get_settings(&m_spSetting);

    VARIANT_BOOL vaBool = FALSE;
    m_spSetting->put_autoStart(vaBool);

    if(_event){
      regist_event();
    }
    return 0;
  }
  LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/){
    RECT rc;
    this->GetClientRect(&rc);
    _wmp_window.MoveWindow(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
    this->Invalidate();
    return 0;
  }

public:
  void play(CString & url){
    BSTR url_ = url.AllocSysString();
    m_spWMPPlayer->put_URL(url_);
    SysFreeString(url_);

    this->stop();

    m_spCurrentMeida.Release();

    m_spWMPPlayer->get_currentMedia(&m_spCurrentMeida);
    m_spWMPCtrler->play();
  };

  bool play(){
    WMPPlayState state;
    m_spWMPPlayer->get_playState(&state);
    return state == WMPPlayState::wmppsPlaying;
  };

  double position(){
    double pos = 0;
    m_spWMPCtrler->get_currentPosition(&pos);
    return pos;
  };

  double length(){
    double len = 0;
    m_spCurrentMeida->get_duration(&len);
    return len;
  }
  void volume(long v){
    m_spSetting->put_volume(v);
  }
  long volume(){
    long v = 0;
    HRESULT hr = m_spSetting->get_volume(&v);
    return SUCCEEDED(hr) ? v : 0;
  }

  void pause(bool p){
    if(p){
      m_spWMPCtrler->pause();
    }else {
      m_spWMPCtrler->play();
    }
  };
  bool pause(){
    WMPPlayState state;
    m_spWMPPlayer->get_playState(&state);
    return state == WMPPlayState::wmppsPaused;
  };
  void stop(){
    m_spWMPCtrler->stop();
  };
  bool full_win(){
    VARIANT_BOOL b = FALSE;
    m_spWMPPlayer->get_fullScreen(&b);
    return b > 0;
  };
  void full_win(bool f){
    VARIANT_BOOL b = f ? VARIANT_TRUE : VARIANT_FALSE;
    HRESULT hr = m_spWMPPlayer->put_enableContextMenu(TRUE);

    full_win();
    hr = m_spWMPPlayer->put_fullScreen(b);
  }
public:
    void STDMETHODCALLTYPE PlayStateChange( 
    /* [in] */ long NewState) {
      switch(NewState){
      case wmppsPlaying:{
        SetTimer(PLAY_TIMER, 1000);
        break;
                        }
      case wmppsStopped:{
        KillTimer(PLAY_TIMER);
        break;
                        }
      case wmppsPaused:{
        KillTimer(PLAY_TIMER);
        break;
                       }
      };
  };

  void progress(double p){
  };
protected:
  void regist_event(){
    HRESULT hr = S_OK;
    CComPtr<IConnectionPointContainer> container;

    hr = m_spWMPPlayer->QueryInterface(&container);
    if(FAILED(hr)) return;

    hr = container->FindConnectionPoint(__uuidof(IWMPEvents), &this->_connection_point);
    if(FAILED(hr)) return;

    hr = _connection_point->Advise(_event, &_advise_cookie);
   
  };

  void unregister_event(){
    if(_connection_point){
      if (_advise_cookie != 0)
        _connection_point->Unadvise(_advise_cookie);

      _connection_point.Release();
    }
  };
protected:
  CAxWindow  _wmp_window;
  CComPtr<IWMPPlayer>  m_spWMPPlayer;
  CComPtr<IWMPControls> m_spWMPCtrler;
  CComPtr<IWMPSettings> m_spSetting;
  CComPtr<IWMPMedia> m_spCurrentMeida;

  PlayerEvent* _event;
  DWORD _advise_cookie;
  CComPtr<IConnectionPoint> _connection_point;
  static const unsigned int PLAY_TIMER = 102;
};