/////////////////////////////////////////////////////////////////////
// This file was created by Ming(2013-05-30)
// Last edit: 2013-07-01 by Ming
#ifndef _GDIPLUSHELPER_H_INCLUDE_
#define _GDIPLUSHELPER_H_INCLUDE_

#pragma once
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

namespace GdiPlusHelper
{
/////////////////////////////////////////////////////////////////////
// Defined class for GDI Plus graphic.
class CGraphicsHelper
{
    // Constructor and destructor.
public:
    CGraphicsHelper()
    {
    }

    ~CGraphicsHelper()
    {
    }

    // Operations.
public:
    void StretchWidthImage(Graphics& g, Image* pImage, Rect& rcDest, REAL nCorner = 1.0F)
    {
        if (pImage == NULL || rcDest.Width <= 0 || nCorner <= 0) {
            return;
        }

        // rcDest's X and Y is relative coordinate.
        REAL nImageWidth    = (REAL)pImage->GetWidth();
        REAL nImageHeight   = (REAL)pImage->GetHeight();
        REAL nStretchLength = (REAL)(nImageWidth - 2 * nCorner);
        REAL X              = (REAL)rcDest.X;
        REAL Y              = (REAL)rcDest.Y;
        REAL nLength        = (REAL)(rcDest.Width - 2 * nCorner);
        // Draw left corner.
        g.DrawImage(pImage, RectF(X, Y, nCorner, nImageHeight),
                    0, 0, nCorner, nImageHeight, UnitPixel);
        // If rect length less than image length,
        // Using rect length for real drawing length.
        REAL nRealLength = nStretchLength;

        if (nLength < nStretchLength) {
            nRealLength = nLength;
        }

        // Draw middle, stretch the length.
        REAL nLeftIndex     = nCorner + X;
        REAL nRightIndex    = nCorner + nRealLength + X;
        REAL nDrawLength    = nRealLength;

        while (TRUE) {
            g.DrawImage(pImage, RectF(nLeftIndex, Y, nDrawLength, nImageHeight),
                        nCorner, 0, nStretchLength, nImageHeight, UnitPixel);
            // If length equal 0 means all middle image has finished drawing.
            nLength -= nDrawLength;

            if (nLength <= 0) {
                break;
            }

            if (nLength < nDrawLength) {
                nDrawLength = nLength;
            }

            // Move drawing left Index.
            nLeftIndex  = nRightIndex;
            nRightIndex += nDrawLength;
        }

        // Draw right corner.
        g.DrawImage(pImage, RectF(nRightIndex, Y, nCorner, nImageHeight),
                    nImageWidth - nCorner, 0, nCorner, nImageHeight, UnitPixel);
    }
};

/////////////////////////////////////////////////////////////////////
// Defined class for GDI Plus Image.
class CImageHelper
{
    // Constructor, destructor and operators.
public:
    CImageHelper() : m_pImage(NULL)
    {
    }

    ~CImageHelper()
    {
        if (m_pImage) {
            delete m_pImage;
            m_pImage = NULL;
        }
    }

    CImageHelper& operator= (const CImageHelper& img)
    {
        if (this == &img) {
            return *this;
        }

        delete m_pImage;
        m_pImage = img.m_pImage->Clone();
        return *this;
    }

    // Data members.
public:
    Image*  m_pImage;

    // Operations.
public:
    // Load image from resource manager.
    Image* Load_Image(ATL::_U_STRINGorID resource, ATL::_U_STRINGorID type = (UINT) 0)
    {
        if (m_pImage) {
            delete m_pImage;
        }

        if (HIWORD(resource.m_lpstr) != NULL) {
            m_pImage = new Image(resource.m_lpstr);
            return m_pImage;
        } else {
            CResource res;

            if (!res.Load(type, resource)) return NULL;

            DWORD dwSize    = res.GetSize();
            HANDLE hMemory  = ::GlobalAlloc(GMEM_MOVEABLE, dwSize);

            if (hMemory == NULL) return NULL;

            // Copy resource to memory.
            memcpy(GlobalLock(hMemory), res.Lock(), dwSize);
            GlobalUnlock(hMemory);
            // Create stream that write to image.
            IStream* pStream = NULL;
            CreateStreamOnHGlobal(hMemory, TRUE, &pStream);
            m_pImage = new Image(pStream);
            pStream->Release();
        }

        return m_pImage;
    }

    inline float GetWidth()
    {
        return (float)m_pImage->GetWidth();
    }

    inline float GetHeight()
    {
        return (float)m_pImage->GetHeight();
    }
};

/////////////////////////////////////////////////////////////////////
// Defined class for GDI Plus Brush.
class CBrushHelper
{
    // Constructor and destructor.
public:
    CBrushHelper() : m_pBrush(NULL), m_pBitmap(NULL)
    {
    }

    ~CBrushHelper()
    {
        DeleteOldBrush();
    }

    // Data members.
public:
    TextureBrush*   m_pBrush;
    Bitmap*         m_pBitmap;

    // The sub window will get background brush via parent window painting types.
    enum GET_BRUSH_TYPE {
        GET_BY_WM_ERASEBKGND,
        GET_BY_WM_PRINTCLIENT,
        GET_BY_WM_PAINT,
    };

    // Operations.
public:
    // Delete old brush.
    void DeleteOldBrush()
    {
        if (m_pBrush) {
            delete m_pBrush;
            m_pBrush = NULL;
        }

        if (m_pBitmap) {
            delete m_pBitmap;
            m_pBitmap = NULL;
        }
    }

    // Get background brush.
    TextureBrush* GetBackGroundBrush(CWindow Window, CWindow ParentWindow, GET_BRUSH_TYPE brush_type = GET_BY_WM_PAINT)
    {
        if (Window.m_hWnd == NULL || ParentWindow.m_hWnd == NULL) {
            return NULL;
        }

        // Delete old brush.
        DeleteOldBrush();
        // Get parent window hdc.
        CRect rcParent;
        ParentWindow.GetWindowRect(&rcParent);
        CClientDC dcParent = ParentWindow;
        CDC dcCompat;
        dcCompat.CreateCompatibleDC(dcParent);
        CBitmap bmpParent;
        bmpParent.CreateCompatibleBitmap(dcParent, rcParent.Width(), rcParent.Height());
        dcCompat.SelectBitmap(bmpParent);

        switch (brush_type) {
        default:
        case GET_BY_WM_ERASEBKGND:  {
            ParentWindow.SendMessage(WM_ERASEBKGND, (WPARAM)(HDC) dcCompat, 0);
            break;
        }

        case GET_BY_WM_PAINT:   {
            ParentWindow.SendMessage(WM_PAINT, (WPARAM)(HDC) dcCompat, (LPARAM)(PRF_ERASEBKGND | PRF_CLIENT | PRF_NONCLIENT));
            break;
        }

        case GET_BY_WM_PRINTCLIENT: {
            ParentWindow.SendMessage(WM_PRINTCLIENT, (WPARAM)(HDC) dcCompat, (LPARAM)(PRF_ERASEBKGND | PRF_CLIENT | PRF_NONCLIENT));
            break;
        }
        }

        // Draw parent window image to bitmap.
        CRect rcWindow;
        Window.GetWindowRect(&rcWindow);
        CDC dcWindow;
        dcWindow.CreateCompatibleDC();
        CBitmap bmpWidnow;
        bmpWidnow.CreateCompatibleBitmap(dcCompat, rcWindow.Width(), rcWindow.Height());
        dcWindow.SelectBitmap(bmpWidnow);
        CRect rcSnap = rcWindow;
        ::MapWindowPoints(NULL, ParentWindow.m_hWnd, (LPPOINT)(LPRECT) &rcSnap, 2);
        dcWindow.BitBlt(0, 0, rcWindow.Width(), rcWindow.Height(), dcCompat, rcSnap.left, rcSnap.top, SRCCOPY);
        // Create Brush via bitmap.
        m_pBitmap   = Bitmap::FromHBITMAP(bmpWidnow.m_hBitmap, NULL);
        m_pBrush    = new TextureBrush(m_pBitmap);
        return m_pBrush;
    }
};

/////////////////////////////////////////////////////////////////////
// Defined class for GDI Plus Path.
class CPathHelper
{
    // Constructor and destructor.
public:
    CPathHelper() : m_pPath(NULL)
    {
    }

    ~CPathHelper()
    {
        DeleteOldPath();
    }

    // Data members.
public:
    GraphicsPath*   m_pPath;

    // Operations.
public:
    // Delete old path.
    void DeleteOldPath()
    {
        if (m_pPath != NULL) {
            delete m_pPath;
            m_pPath = NULL;
        }
    }

    // Create round rect path.
    GraphicsPath* CreateRoundRect(Rect rect, int cornerRadius)
    {
        DeleteOldPath();
        m_pPath = new GraphicsPath();
        m_pPath->AddArc(rect.X, rect.Y, cornerRadius * 2, cornerRadius * 2, 180, 90);
        m_pPath->AddLine(rect.X + cornerRadius, rect.Y, rect.GetRight() - cornerRadius * 2, rect.Y);
        m_pPath->AddArc(rect.X + rect.Width - cornerRadius * 2, rect.Y, cornerRadius * 2, cornerRadius * 2, 270, 90);
        m_pPath->AddLine(rect.GetRight(), rect.Y + cornerRadius * 2, rect.GetRight(), rect.Y + rect.Height - cornerRadius * 2);
        m_pPath->AddArc(rect.X + rect.Width - cornerRadius * 2, rect.Y + rect.Height - cornerRadius * 2, cornerRadius * 2, cornerRadius * 2, 0, 90);
        m_pPath->AddLine(rect.GetRight() - cornerRadius * 2, rect.GetBottom(), rect.X + cornerRadius * 2, rect.GetBottom());
        m_pPath->AddArc(rect.X, rect.GetBottom() - cornerRadius * 2, cornerRadius * 2, cornerRadius * 2, 90, 90);
        m_pPath->AddLine(rect.X, rect.GetBottom() - cornerRadius * 2, rect.X, rect.Y + cornerRadius * 2);
        m_pPath->CloseFigure();
        return m_pPath;
    }
};

/////////////////////////////////////////////////////////////////////
// Defined class for GDI Plus Font.
class CFontHelper
{
    // Constructor, destructor and operator.
public:
    CFontHelper() : m_Font(NULL)
    {
    }

    ~CFontHelper()
    {
        DeleteOldFont();
    }

    // Data members.
public:
    Font*   m_Font;
private:
    PrivateFontCollection   m_FontCollection;
    FontFamily              m_FontFamily;

    // Operations.
public:
    void DeleteOldFont()
    {
        if (m_Font != NULL) {
            delete m_Font;
            m_Font = NULL;
        }
    }

    // Load font from resource manager.
    BOOL LoadFont(ATL::_U_STRINGorID resource, ATL::_U_STRINGorID type = _T("ttf"))
    {
        CResource res;

        if (!res.Load(type, resource)) {
            ATLASSERT(FALSE);
            return FALSE;
        }

        int nSize   = (int)res.GetSize();
        void* data  = res.Lock();
        Gdiplus::Status nResults = m_FontCollection.AddMemoryFont(data, nSize);

        if (nResults != Gdiplus::Ok) {
            ATLASSERT(FALSE);
            return FALSE;
        }

        SetFontStyle();
        return TRUE;
    }

    // Modify font style.
    BOOL SetFontStyle(Gdiplus::FontStyle fontstyle = FontStyleRegular, REAL nFontSize = 14.0F)
    {
        int nNumFound = 0;
        m_FontCollection.GetFamilies(1, &m_FontFamily, &nNumFound);

        if (nNumFound <= 0) {
            // You need load font first.
            ATLASSERT(FALSE);
            return FALSE;
        }

        // Delete old font.
        DeleteOldFont();
        m_Font = new Font(&m_FontFamily, nFontSize, fontstyle, UnitPixel);

        if (m_Font != NULL) {
            return TRUE;
        }

        ATLASSERT(FALSE);
        return FALSE;
    }

    // Turn GDI+ Font to HFONT (ANSI).
    HFONT FontToHFONT_A(HWND m_hWnd)
    {
        if (m_Font == NULL || m_hWnd == NULL) {
            ATLASSERT(FALSE);
            return NULL;
        }

        Graphics g(m_hWnd);
        LOGFONTA logFont;
        m_Font->GetLogFontA(&g, &logFont);
        logFont.lfQuality           = CLEARTYPE_QUALITY;
        logFont.lfOutPrecision      = OUT_DEVICE_PRECIS;
        logFont.lfClipPrecision     = CLIP_CHARACTER_PRECIS;
        logFont.lfCharSet           = ANSI_CHARSET;
        logFont.lfPitchAndFamily    = DEFAULT_PITCH;
        return ::CreateFontIndirectA(&logFont);
    }

    // Turn GDI+ Font to HFONT (Unicode).
    HFONT FontToHFONT_W(HWND m_hWnd)
    {
        if (m_Font == NULL || m_hWnd == NULL) {
            ATLASSERT(FALSE);
            return NULL;
        }

        Graphics g(m_hWnd);
        LOGFONTW logFont;
        m_Font->GetLogFontW(&g, &logFont);
        logFont.lfQuality           = CLEARTYPE_QUALITY;
        logFont.lfOutPrecision      = OUT_DEVICE_PRECIS;
        logFont.lfClipPrecision     = CLIP_CHARACTER_PRECIS;
        logFont.lfCharSet           = ANSI_CHARSET;
        logFont.lfPitchAndFamily    = DEFAULT_PITCH;
        return ::CreateFontIndirectW(&logFont);
    }
};
}

#endif // _GDIPLUSHELPER_H_INCLUDE_
