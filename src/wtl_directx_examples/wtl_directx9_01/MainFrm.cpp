// MainFrm.cpp : implmentation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "MainFrm.h"
#include <MMSystem.h>

#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

#ifndef V_RETURN
    #define V_RETURN(x)    { hr = (x); if( FAILED(hr) ) { return hr; } }
#endif

BOOL CMainFrame::PreTranslateMessage(MSG * pMsg)
{
    return CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
    m_dCurrentTime = timeGetTime();
    m_dElpasedFrameTime = m_dCurrentTime - m_dLastTime;
    m_dElpasedAppTime += m_dElpasedFrameTime;
    m_dLastTime = m_dCurrentTime;
    Render();
    return FALSE;
}

LRESULT CMainFrame::OnCreate(UINT/*uMsg*/, WPARAM/*wParam*/, LPARAM/*lParam*/, BOOL&/*bHandled*/)
{
    if (FAILED(InitD3D()))
        return FALSE;

    InitVB();
    m_dLastTime = timeGetTime();
    // register object for message filtering and idle updates
    CMessageLoop * pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->AddMessageFilter(this);
    pLoop->AddIdleHandler(this);
    return 0;
}

LRESULT CMainFrame::OnDestroy(UINT/*uMsg*/, WPARAM/*wParam*/, LPARAM/*lParam*/, BOOL & bHandled)
{
    // unregister message filtering and idle updates
    CMessageLoop * pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->RemoveMessageFilter(this);
    pLoop->RemoveIdleHandler(this);
    ShutDown();
    bHandled = FALSE;
    return 1;
}

LRESULT CMainFrame::OnFileExit(WORD/*wNotifyCode*/, WORD/*wID*/, HWND/*hWndCtl*/, BOOL&/*bHandled*/)
{
    PostMessage(WM_CLOSE);
    return 0;
}

LRESULT CMainFrame::OnFileNew(WORD/*wNotifyCode*/, WORD/*wID*/, HWND/*hWndCtl*/, BOOL&/*bHandled*/)
{
// TODO: add code to initialize document
    return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD/*wNotifyCode*/, WORD/*wID*/, HWND/*hWndCtl*/, BOOL&/*bHandled*/)
{
    CAboutDlg dlg;
    dlg.DoModal();
    return 0;
}

CMainFrame::CMainFrame() : m_pD3D(NULL), m_pd3dDevice(NULL), m_pd3dBackSurface(
        NULL), m_pd3dxFont(NULL), m_pTexture(NULL), m_pVertexBuffer(NULL), m_dCurrentTime(
            0.0f), m_dLastTime(0.0f), m_dElpasedFrameTime(0.0f), m_dElpasedAppTime(0.0f)
{
}

CMainFrame::~CMainFrame()
{
}

HRESULT CMainFrame::InitD3D()
{
    HRESULT hr;
    m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

    if (m_pD3D == NULL) {
        return E_FAIL;
    }

    D3DDISPLAYMODE d3ddm;
    V_RETURN(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm));
    this->m_colorFormat = d3ddm.Format;

    if (FAILED(hr = m_pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3ddm.Format, D3DUSAGE_DEPTHSTENCIL,
                    D3DRTYPE_SURFACE,   D3DFMT_D16))) {
        if (hr == D3DERR_NOTAVAILABLE)
            // POTENTIAL PROBLEM: We need at least a 16-bit z-buffer!
            return E_FAIL;
    }

    //
    // Do we support hardware vertex processing? if so, use it.
    // If not, downgrade to software.
    //
    D3DCAPS9 d3dCaps;

    if (FAILED(m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps))) {
        // TO DO: Respond to failure of GetDeviceCaps
        return E_FAIL;
    }

    DWORD dwBehaviorFlags = 0;

    if (d3dCaps.VertexProcessingCaps != 0)
        dwBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING; // 支持硬件顶点运算
    else
        dwBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING; // 不支持硬件顶点运算，采用软件顶点运算

    //
    // Everything checks out - create a simple, windowed device.
    //
    D3DPRESENT_PARAMETERS d3dpp;
    memset(&d3dpp, 0, sizeof(d3dpp));
    d3dpp.BackBufferFormat = d3ddm.Format;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.Windowed = TRUE;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->m_hWnd, dwBehaviorFlags, &d3dpp,
                                    &m_pd3dDevice))) {
        // TO DO: Respond to failure of CreateDevice
        return E_FAIL;
    }

    m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    CreateFont();
    return S_OK;
}

void CMainFrame::ShutDown()
{
    SAFE_RELEASE(m_pTexture);
    SAFE_RELEASE(m_pVertexBuffer);
    SAFE_RELEASE(m_pd3dBackSurface);
    SAFE_RELEASE(m_pd3dDevice);
    SAFE_RELEASE(m_pD3D);
}

void CMainFrame::Render()
{
    /*
    LPDIRECT3DSURFACE9 pd3dSurface;

    if (FAILED(m_pd3dDevice->GetRenderTarget(0, &pd3dSurface)))
        return;
    */
    // 背景红色
    /*m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
        D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,1.0f), 1.0f, 0 );*/
    m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 45, 50, 170), 1.0f, 0);

    if (SUCCEEDED(m_pd3dDevice->BeginScene())) {
        SetupMatrices();
        // Render geometry here...
        m_pd3dDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(CUSTOMVERTEX));
        m_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
        m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
        int charCount = swprintf_s(m_strFPS, 20, _T("FPS:%0.3f"), GetFPS());
        SetRect(&m_FontPosition, 5, 5, 0, 0);
        m_pd3dxFont->DrawText(NULL, m_strFPS, -1, &m_FontPosition, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
        m_FontPosition.top = 100;
        m_pd3dxFont->DrawText(0, _T("游戏开发的世界~！"), -1, &m_FontPosition, DT_NOCLIP, D3DCOLOR_XRGB(68, 139, 256));
        m_FontPosition.top = 200;
        m_pd3dxFont->DrawText(0, _T("游戏开发的世界~！"), -1, &m_FontPosition, DT_NOCLIP,
                              D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256));
        m_pd3dDevice->EndScene();
    }

    m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

void CMainFrame::CreateFont()
{
    HRESULT hr;
    HDC hDC;
    //HFONT hFont;
    int nHeight;
    int nPointSize = 9;
    //char strFontName[] = "Arial";
    hDC = ::GetDC(NULL);
    nHeight = -(MulDiv(nPointSize, GetDeviceCaps(hDC, LOGPIXELSY), 72));
    ::ReleaseDC(NULL, hDC);
    // Create a font for statistics and help output
    hr = D3DXCreateFont(m_pd3dDevice,    nHeight,                     0,               FW_BOLD,
                        0,               FALSE,                       DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"),   &m_pd3dxFont);

    if (FAILED(hr))
        ::MessageBox(NULL, L"Call to D3DXCreateFont failed!", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
}

LRESULT CMainFrame::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
    Render();
    return 0;
}

LRESULT CMainFrame::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
    bHandled = TRUE;
    return 0;
}

LRESULT CMainFrame::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
    UINT nChar = (TCHAR)wParam;

    //UINT nRepCnt = (UINT)lParam & 0xFFFF;
    //UINT nFlags = (UINT)((lParam & 0xFFFF0000) >> 16);
    if (nChar == VK_ESCAPE)
        DestroyWindow();

    return 0;
}

float CMainFrame::GetFPS()
{
    //定义四个静态变量
    static float fps = 0;                 //我们需要计算的FPS值
    static int frameCount = 0;            //帧数
    static float currentTime = 0.0f;      //当前时间
    static float lastTime = 0.0f;         //持续时间
    frameCount++;                         //每调用一次Get_FPS()函数，帧数自增1
    currentTime = timeGetTime() * 0.001f; //获取系统时间，其中timeGetTime函数返回的是以毫秒为单位的系统时间，所以需要乘以0.001，得到单位为秒的时间

    //如果当前时间减去持续时间大于了1秒钟，就进行一次FPS的计算和持续时间的更新，并将帧数值清零
    if (currentTime - lastTime > 1.0f) {                    //将时间控制在1秒钟
        fps = (float)frameCount / (currentTime - lastTime); //计算这1秒钟的FPS值
        lastTime = currentTime;                             //将当前时间currentTime赋给持续时间lastTime，作为下一秒的基准时间
        frameCount = 0;                                     //将本次帧数frameCount值清零
    }

    return fps;
}

void CMainFrame::PrepareBackSurface()
{
    // 释放老的后台表面
    SAFE_RELEASE(m_pd3dBackSurface);
    RECT rcClient;
    GetClientRect(&rcClient);
    int width = rcClient.right - rcClient.left;
    int height = rcClient.bottom - rcClient.top;

    if (FAILED(m_pd3dDevice->CreateOffscreenPlainSurface(width,              height, m_colorFormat, D3DPOOL_SYSTEMMEM,
               &m_pd3dBackSurface, NULL))) {
        return;
    }

    HDC hDC = NULL;

    if (FAILED(m_pd3dBackSurface->GetDC(&hDC))) {
        return;
    }

    ::SendMessage(m_hWnd, WM_PRINTCLIENT, (WPARAM)hDC, PRF_CHECKVISIBLE |
                  PRF_CLIENT | PRF_ERASEBKGND | PRF_CHILDREN);
    m_pd3dBackSurface->ReleaseDC(hDC);
}
HRESULT CMainFrame::InitVB()
{
    CUSTOMVERTEX vertices [] = {
        { 150.0f, 50.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), }, // x, y, z, rhw, color
        { 250.0f, 250.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { 50.0f, 250.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },
    };

    if (FAILED(m_pd3dDevice->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT,
               &m_pVertexBuffer,         NULL))) {
        return E_FAIL;
    }

    void* pVertices;

    if (FAILED(m_pVertexBuffer->Lock(0, sizeof(vertices), (void **)&pVertices, 0))) {
        return E_FAIL;
    }

    memcpy(pVertices, vertices, sizeof(vertices));
    m_pVertexBuffer->Unlock();
    return S_OK;
}

void CMainFrame::SetupMatrices()
{
    // For our world matrix, we will just rotate the object about the y-axis.
    D3DXMATRIXA16 matWorld;
    // 根据时间，改变角度旋转
    UINT  iTime  = timeGetTime() % 1000;
    FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 1000.0f;
    D3DXMatrixRotationY(&matWorld, fAngle);
    m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
    // 定义摄像头的位置
    D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);
    D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
    D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
    m_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);
    // 定义视锥体的大小
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 640 / 480, 1.0f, 100.0f);
    m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}
