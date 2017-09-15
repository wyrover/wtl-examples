//
// MemDC.h : Version 1.0
//
// Author:  Darren Sessions
//
//
// Description:
//      MemDC is a memory DC class based on the one written by Keith Rule.  The primary
//      difference is the copy first option and the storage option.  Copy first should be set
//      to true when working with objects that have transparency.  The storage type DC is
//      defined but not created until the Create function is called.  The storage type does
//      not attempt to copy anything on destruction.
//
// History
//     Version 1.0 - 2008 June 20
//     - Initial public release
//
// License:
//     This software is released under the Code Project Open License (CPOL),
//     which may be found here:  http://www.codeproject.com/info/eula.aspx
//     You are free to use this software in any way you like, except that you
//     may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#define ENABLE_GDIP_FUNTION

class MemDC : public CDC
{

private:
    CDC*        m_pDC;          // CDC of passed in constructor
    CRect       m_rect;         // Rectangle of drawing area.
    BOOL        m_bPrintDC;     // True if printing
    BOOL        m_bCopyFirst;   // Copy existing on construction
    BOOL        m_bStorageDC;   // True if used for storing a bitmap
    CBitmap*    m_pOld;         // passed DC's bitmap
    CBitmap     m_bitmap;       // Offscreen bitmap
    BOOL        m_bCreated;     // TRUE after creation

public:

    // default constructor - requires subsequent create call
    MemDC()
    {
        m_bStorageDC = TRUE;
        m_bPrintDC = FALSE;
        m_bCreated = FALSE;
    };

    // constructor
    MemDC(CDC* pDC, CRect rect, BOOL bCopyFirst = FALSE)
        : CDC(), m_pDC(pDC), m_rect(rect), m_bCopyFirst(bCopyFirst)
    {
        // NULL dc not allowed
        ASSERT(m_pDC != NULL);
        m_bStorageDC = FALSE;
        Init();
    }

    // create a MemDC and copy the data
    void Create(CDC* pDC, CRect rect)
    {
        // NULL dc not allowed
        ASSERT(pDC != NULL);
        m_pDC = pDC;
        m_rect = rect;
        m_bCopyFirst = TRUE;
        m_bStorageDC = TRUE;
        Init();
    }

    void Init()
    {
        // true if printing
        m_bPrintDC = m_pDC->IsPrinting();

        if (!m_bPrintDC) {
            // Create a compatible DC
            CreateCompatibleDC(m_pDC);
            // create a compatible bitmap
            m_bitmap.CreateCompatibleBitmap(m_pDC, m_rect.Width(), m_rect.Height());
            // select bitmap into dc
            m_pOld = SelectObject(&m_bitmap);
            // set window origin
            SetWindowOrg(m_rect.left, m_rect.top);

            // needed for transparency support
            if (m_bCopyFirst) {
                this->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
                             m_pDC, m_rect.left, m_rect.top, SRCCOPY);
            }
        } else {
            // Make a copy of the relevent parts of the current DC for printing
            m_bPrinting = m_pDC->m_bPrinting;
            m_hAttribDC = m_pDC->m_hAttribDC;
            m_hDC       = m_pDC->m_hDC;
        }

        m_bCreated = TRUE;
    }

#ifdef ENABLE_GDIP_FUNTION
    Bitmap* GetBitmap()
    {
        CPalette* pPalette = m_pDC->GetCurrentPalette();
        return  Bitmap::FromHBITMAP((HBITMAP)m_bitmap.GetSafeHandle(),
                                    (HPALETTE)pPalette->GetSafeHandle());
    }
#endif

    // destructor
    ~MemDC()
    {
        if (!m_bPrintDC && !m_bStorageDC) {
            // Copy the offscreen bitmap onto the screen
            m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
                          this, m_rect.left, m_rect.top, SRCCOPY);
            // Swap back the original bitmap.
            SelectObject(m_pOld);
        } else if (m_bPrintDC) {
            // All we need to do is replace the DC with an illegal value,
            // this keeps us from accidently deleting the handles associated with
            // the CDC that was passed to the constructor.
            m_hDC = m_hAttribDC = NULL;
        }
    }

    // pointer operators
    MemDC* operator->()
    {
        return this;
    }
    operator MemDC*()
    {
        return this;
    }
};


