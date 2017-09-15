#pragma once

#define _WTL_NO_WTYPES

#include <atlstr.h>
#include <atlimage.h>
#include <atlbase.h>
#include <atlapp.h>
#include <atlwin.h>
#include <atlcrack.h>
#include <atlmisc.h>

#include <gdiplus.h>

class CEllipseWindow : public CWindowImpl<CEllipseWindow>
{
public:
    BEGIN_MSG_MAP_EX(CEllipseWindow)
    MSG_WM_CREATE(OnCreate)
    MSG_WM_NCHITTEST(OnNcHitTest)
    MSG_WM_KEYDOWN(OnKeyDown)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
        // Add style WS_EX_LAYERED to the window
        ModifyStyleEx(0, WS_EX_LAYERED);
        CRect rectClient;
        GetClientRect(&rectClient);
        // Use ATL::CImage class to create a 32-bit bitmap with alpha channel
        CImage img;

        if (img.Create(rectClient.Width(), rectClient.Height(), 32, CImage::createAlphaChannel)) {
            Gdiplus::Graphics graphics(img.GetDC());
            graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
            Gdiplus::Rect rect(0, 0, img.GetWidth() - 1, img.GetHeight() - 1);
            Gdiplus::LinearGradientBrush brush(rect,
                                               Gdiplus::Color(0, 0, 0, 0),
                                               Gdiplus::Color(255, 0, 0, 255),
                                               Gdiplus::LinearGradientModeForwardDiagonal);
            // Fill the ellipse with the linear brush, GDI+ will take care of alpha blending
            graphics.FillEllipse(&brush, rect);
            // Dig a "hole" with a smaller ellipse by using a solid transparent brush (alpha is 0) and set composite mode
            // to source copy instead of source over
            rect.Inflate(-rect.Width / 4, -rect.Height / 4);
            graphics.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
            Gdiplus::SolidBrush brush2(Gdiplus::Color(0, 0, 0, 0));
            graphics.FillEllipse(&brush2, rect);
        }

        img.ReleaseDC();
        /* Following code can be used to fine tune the bitmap pixel by pixel if needed
        LPDWORD pdwbits = (LPDWORD)img.GetPixelAddress(0, rectClient.Height() ¨C 1);
        for(LONG ny = 0; ny < rectClient.Height(); ++ny)
        {
        for(LONG nx = 0; nx < rectClient.Width(); ++nx)
        {
        DWORD& dwPixel = pdwbits[ny * rectClient.Width() + nx]; // dwPixel is in ARGB format
        }
        }
        */
        POINT pt = { 0, 0 };
        SIZE size = { rectClient.Width(), rectClient.Height() };
        BLENDFUNCTION bf = { 0 };
        bf.BlendOp = AC_SRC_OVER;
        bf.BlendFlags = 0;
        bf.AlphaFormat = AC_SRC_ALPHA;
        bf.SourceConstantAlpha = 178;    // in addition to alpha channel in bitmap, this adds additional transparency
        // supply the bitmap to Windows for rendering the window
        UpdateLayeredWindow(m_hWnd, 0, 0, &size, img.GetDC(), &pt, 0, &bf, ULW_ALPHA);
        img.ReleaseDC();
        return 0;
    }

    UINT OnNcHitTest(CPoint point)
    {
        return HTCAPTION;
    }

    void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
    {
        if (VK_ESCAPE == nChar)
            DestroyWindow();
    }

    virtual void OnFinalMessage(HWND)
    {
        PostQuitMessage(0);
    }
};



CAppModule _Module;

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
    CMessageLoop theLoop;
    _Module.AddMessageLoop(&theLoop);
    RECT rect = { 100, 100, 300, 200 };
    CEllipseWindow wnd;

    if (NULL != wnd.Create(0, rect, 0, WS_POPUP | WS_VISIBLE)) {
        wnd.ShowWindow(nCmdShow);
        theLoop.Run();
    }

    _Module.RemoveMessageLoop();
    return 0;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
    HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
    ::DefWindowProc(NULL, 0, 0, 0L);
    AtlInitCommonControls(ICC_BAR_CLASSES);    // add flags to support other controls
    ULONG_PTR token = 0;
    Gdiplus::GdiplusStartupInput input;
    Gdiplus::GdiplusStartup(&token, &input, 0);
    hRes = _Module.Init(NULL, hInstance);
    int nRet = Run(lpstrCmdLine, nCmdShow);
    _Module.Term();
    Gdiplus::GdiplusShutdown(token);
    ::CoUninitialize();
    return nRet;
}