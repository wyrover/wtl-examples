// CWinListBox.cpp : implementation file
//

#include "stdafx.h"
#include "CustomListBox.h"
#include "CWinListBox.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCWinListBox

CCWinListBox::CCWinListBox()
{
    RegisterWindowClass();  // Register custom control
    m_iTotalItems       = 0;
    m_iItemHeight       = -1;
    m_iDisplayColumn    = 0;
    m_iColumnWidth      = -1;
    // odd defaults in case initialization is not properly done
    m_Font.CreatePointFont(160, _T("Arial Unicode MS"));     // in case SetTextFont is not called
    m_crText        = RGB(255, 145, 200);
    m_crSelText     = RGB(255, 145, 200);
    m_crSelTextBk   = RGB(128, 255, 128);
    m_crBorder1     = RGB(255, 0, 0);
    m_crBorder2     = RGB(255, 0, 0);
    m_crBkFrom      = RGB(255, 0, 0);
    m_crBkTo        = RGB(255, 0, 0);
    m_crSB_Text     = RGB(255, 145, 200);
    m_crSB_Bk       = RGB(255, 255, 0);
    m_crSB_Border1  = RGB(128, 128, 192);
    m_crSB_Border2  = RGB(128, 128, 192);
    // scrollbar divisions need to be calculated
    m_bCalculateSB_Div  = TRUE;

    // create 5 elements in the array that will hold the subdivision of the scrollbar
    for (int i = 0; i < 5; i++) {
        m_tpaSB.SetAtGrow(i, new CScrollBarDiv());

        switch (i) {
        case 0:
            m_tpaSB[ 0 ]->csLabel = "<<";
            break;

        case 1:
            m_tpaSB[ 1 ]->csLabel = "<";
            break;

        case 3:
            m_tpaSB[ 3 ]->csLabel = ">";
            break;

        case 4:
            m_tpaSB[ 4 ]->csLabel = ">>";
            break;
        }
    }
}

CCWinListBox::~CCWinListBox()
{
    // clear item array
    RemoveAll(FALSE);

    // clear scrollbar array
    for (int i = 0; i < 5; i++)
        delete m_tpaSB[ i ];

    m_tpaSB.RemoveAll();
}

BEGIN_MESSAGE_MAP(CCWinListBox, CWnd)
    //{{AFX_MSG_MAP(CCWinListBox)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_ERASEBKGND()
    ON_WM_LBUTTONUP()
    ON_WM_TIMER()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//  PUBLIC METHODS

CCWinListBox& CCWinListBox::SetColumnWidth(int iNumberOfCharacters, BOOL bInvalidate /* = TRUE  */)
{
    CDC*    pDC         = GetDC();
    CFont   *pPrevFont  = pDC->SelectObject(&m_Font);
    TCHAR   strWidestText[ 100 ];
    memset(strWidestText, 0, 100);
    // Let's use a character likely to be wide
    memset(strWidestText, 'X', (iNumberOfCharacters < 100) ? iNumberOfCharacters : 100);
    // Calculate the lenght of the string under this font plus 4 pixel padding
    m_iColumnWidth = (pDC->GetTextExtent(strWidestText)).cx + 4;
    pDC->SelectObject(pPrevFont);
    ReleaseDC(pDC);

    if (bInvalidate)
        Invalidate();

    return *this;
}

int CCWinListBox::GetSelectedItem()
{
    int iSelectedIndex = -1;

    for (int iIndex = 0; iIndex < m_iTotalItems && iSelectedIndex == -1; iIndex++)
        if (m_tpaItems[ iIndex ]->bSelected)
            iSelectedIndex = iIndex;

    return iSelectedIndex;
}

int CCWinListBox::GetCount()
{
    return m_iTotalItems;
}

CString CCWinListBox::GetStringAt(int iIndex)
{
    if (iIndex >= 0 && iIndex < m_iTotalItems)
        return m_tpaItems[ iIndex ]->csLabel;
    else
        return "";
}

COLORREF CCWinListBox::GetColorAt(int iIndex)
{
    if (iIndex >= 0 && iIndex < m_iTotalItems)
        return m_tpaItems[ iIndex ]->crFace;
    else
        return m_crText;    // m_crText acts as default
}

void CCWinListBox::AddString(CString csLabel)
{
    AddStringWithColor(csLabel, m_crText);
}

void CCWinListBox::AddStringWithColor(CString csLabel, COLORREF crFace)
{
    m_tpaItems.SetAtGrow(m_iTotalItems, new CListBoxItem());
    m_tpaItems[ m_iTotalItems ]->csLabel    = csLabel;
    m_tpaItems[ m_iTotalItems ]->crFace     = crFace;
    m_iTotalItems++;
    m_tpaSB[ 2 ]->csLabel.Format(_T("%d"), m_iTotalItems);
    Invalidate();
}

void CCWinListBox::RemoveAt(int iIndex)
{
    if (iIndex >= 0 && iIndex < m_iTotalItems) {
        m_tpaItems.RemoveAt(iIndex);
        m_iTotalItems--;
        m_tpaSB[ 2 ]->csLabel.Format(_T("%d"), m_iTotalItems);
        Invalidate();
    }
}

void CCWinListBox::ChangeStringAt(int iIndex, CString csLabel)
{
    ChangeStringAndColorAt(iIndex, csLabel, m_tpaItems[ iIndex ]->crFace);
}

void CCWinListBox::ChangeColorAt(int iIndex, COLORREF crFace)
{
    ChangeStringAndColorAt(iIndex, m_tpaItems[ iIndex ]->csLabel, crFace);
}

void CCWinListBox::ChangeStringAndColorAt(int iIndex, CString csLabel, COLORREF crFace)
{
    if (iIndex >= 0 && iIndex < m_iTotalItems) {
        m_tpaItems[ iIndex ]->csLabel   = csLabel;
        m_tpaItems[ iIndex ]->crFace    = crFace;
        Invalidate();
    }
}

void CCWinListBox::InsertString(int iIndex, CString csLabel)
{
    InsertStringWithColor(iIndex, csLabel, m_crText);
}

void CCWinListBox::InsertStringWithColor(int iIndex, CString csLabel, COLORREF crFace)
{
    // iIndex == m_ITotalItems is ok, will go in last position
    if (iIndex >= 0 && iIndex <= m_iTotalItems) {
        m_tpaItems.InsertAt(iIndex, new CListBoxItem());
        m_tpaItems[ iIndex ]->csLabel   = csLabel;
        m_tpaItems[ iIndex ]->crFace    = crFace;
        m_iTotalItems++;
        m_tpaSB[ 2 ]->csLabel.Format(_T("%d"), m_iTotalItems);
        Invalidate();
    }
}

void CCWinListBox::RemoveAll(BOOL bInvalidate /* = TRUE  */)
{
    for (int iIndex = 0; iIndex < m_iTotalItems; iIndex++)
        delete m_tpaItems[ iIndex ];

    m_tpaItems.RemoveAll();
    m_iTotalItems = 0;
    m_tpaSB[ 2 ]->csLabel.Format(_T("%d"), m_iTotalItems);

    if (bInvalidate)
        Invalidate();
}

CCWinListBox& CCWinListBox::SetTextFont(LONG nHeight, bool bBold, bool bItalic, CString csFaceName)
{
    LOGFONT lgfnt;
    lgfnt.lfHeight          = -MulDiv(nHeight, GetDeviceCaps(GetDC()->m_hDC, LOGPIXELSY), 72);
    lgfnt.lfWidth           = 0;
    lgfnt.lfEscapement      = 0;
    lgfnt.lfOrientation     = 0;
    lgfnt.lfWeight          = (bBold) ? FW_BOLD : FW_DONTCARE;
    lgfnt.lfUnderline       = FALSE;
    lgfnt.lfStrikeOut       = FALSE;
    lgfnt.lfCharSet         = DEFAULT_CHARSET;
    lgfnt.lfOutPrecision    = OUT_DEFAULT_PRECIS;
    lgfnt.lfClipPrecision   = CLIP_DEFAULT_PRECIS;
    lgfnt.lfQuality         = DEFAULT_QUALITY;
    lgfnt.lfPitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;
#if defined( _UNICODE )
    lgfnt.lfItalic      = (CHAR)((bItalic) ? TRUE : FALSE);
    wcscpy(lgfnt.lfFaceName, csFaceName);
#else
    lgfnt.lfItalic      = (TCHAR)((bItalic) ? TRUE : FALSE);
    strcpy(lgfnt.lfFaceName, csFaceName);
#endif
    m_Font.DeleteObject();
    m_Font.CreateFontIndirect(&lgfnt);
    // flag the item height so that it is recalculated
    m_iItemHeight   = -1;
    // redraw the listbox with the new font
    Invalidate();
    return *this;
}

CCWinListBox& CCWinListBox::SetSBColors(COLORREF crText, COLORREF crBk, COLORREF crBorder1, COLORREF crBorder2)
{
    m_crSB_Text     = crText;
    m_crSB_Bk       = crBk;
    m_crSB_Border1  = crBorder1;
    m_crSB_Border2  = crBorder2;
    Invalidate();
    return *this;
}

CCWinListBox& CCWinListBox::SetBkColor(COLORREF crBkFrom, COLORREF crBkTo)
{
    m_crBkFrom  = crBkFrom;
    m_crBkTo    = crBkTo;
    Invalidate();
    return *this;
}

CCWinListBox& CCWinListBox::SetBorderColor(COLORREF crBorder1, COLORREF crBorder2)
{
    m_crBorder1 = crBorder1;
    m_crBorder2 = crBorder2;
    Invalidate();
    return *this;
}

CCWinListBox& CCWinListBox::SetDefaultTextColor(COLORREF crText)
{
    m_crText = crText;

    for (int iIndex = 0; iIndex < m_iTotalItems; iIndex++)
        m_tpaItems[ iIndex ]->crFace = crText;

    Invalidate();
    return *this;
}

CCWinListBox& CCWinListBox::SetSelectedColors(COLORREF crSelText, COLORREF crSelTextBk,
        COLORREF crSelBorder1, COLORREF crSelBorder2)
{
    m_crSelText         = crSelText;
    m_crSelBorder1      = crSelBorder1;
    m_crSelBorder2      = crSelBorder2;
    m_crSelTextBk       = crSelTextBk;
    Invalidate();
    return *this;
}

/////////////////////////////////////////////////////////////////////////////
//  PROTECTED METHODS

BOOL CCWinListBox::RegisterWindowClass()
{
    WNDCLASS    wndcls;
    HINSTANCE   hInst = AfxGetInstanceHandle();

    if (!(::GetClassInfo(hInst, C_CWINLISTBOX_CLASSNAME, &wndcls))) {    // Already registered?
        wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
        wndcls.lpfnWndProc      = ::DefWindowProc;
        wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
        wndcls.hInstance        = hInst;
        wndcls.hIcon            = NULL;
        wndcls.hCursor          = AfxGetApp()->LoadCursor(IDC_CURSOR1);
        wndcls.hbrBackground    = (HBRUSH)(COLOR_3DFACE + 1);
        wndcls.lpszMenuName     = NULL;
        wndcls.lpszClassName    = C_CWINLISTBOX_CLASSNAME;

        if (!AfxRegisterClass(&wndcls)) {
            AfxThrowResourceException();
            return FALSE;
        }
    }

    return TRUE;
}

void CCWinListBox::DrawGradientBackground(CDC* pDC, CRect rRect, COLORREF crFrom, COLORREF crTo)
{
    int iHeight = rRect.Height();
    int iWidth  = rRect.Width();
    int iR  = GetRValue(crFrom);
    int iG  = GetGValue(crFrom);
    int iB  = GetBValue(crFrom);
    int idR = 256 * (GetRValue(crTo) - iR) / iWidth;
    int idG = 256 * (GetGValue(crTo) - iG) / iWidth;
    int idB = 256 * (GetBValue(crTo) - iB) / iWidth;
    iR *= 256;
    iG *= 256;
    iB *= 256;

    for (int i = rRect.top; i <= iHeight; i++, iR += idR, iG += idG, iB += idB)
        pDC->FillSolidRect(rRect.left, i, iWidth, 1, RGB(iR / 256, iG / 256, iB / 256));
}

void CCWinListBox::CalculateSBDivisions(CRect rSBRect)
{
    m_bCalculateSB_Div = FALSE;
    int iWidth  = rSBRect.Width() / 5;
    int iAddum  = rSBRect.Width() % 5; // extra pixels?

    for (int i = 0; i < 5; i++) {
        m_tpaSB[ i ]->rItem = CRect(rSBRect.left + (i * iWidth), rSBRect.top, 1 + (i + 1) * iWidth, rSBRect.bottom);

        switch (i) {
        case 2:
            m_tpaSB[ 2 ]->rItem.right += iAddum; // add extra pixels to the center division
            break;

        case 3:
            m_tpaSB[ 3 ]->rItem.OffsetRect(iAddum, 0);   // shift position to account for extra pixels
            break;

        case 4:
            m_tpaSB[ 4 ]->rItem.OffsetRect(iAddum, 0);   // shift position to account for extra pixels
            break;
        }
    }
}

void CCWinListBox::DrawSB_ShiftColumn(CDC *pDC, CRect rSBArea)
{
    pDC->FillSolidRect(rSBArea, m_crSB_Bk);

    for (int i = 0; i < 5; i++) { // draw the scrollbar
        CRect rItem(m_tpaSB[ i ]->rItem);

        // display or button section
        if (i == 2) {
            pDC->Draw3dRect(rItem, m_crSB_Border1, m_crSB_Border1);
            rItem.DeflateRect(2, 2, 2, 2);
            pDC->Draw3dRect(rItem, m_crSB_Border2, m_crSB_Border2);
        } else
            pDC->Draw3dRect(rItem,
                            (m_tpaSB[ i ]->bPressed) ? m_crSB_Border1 : m_crSB_Border2,
                            (m_tpaSB[ i ]->bPressed) ? m_crSB_Border2 : m_crSB_Border1);

        pDC->SetTextColor(m_crSB_Text);
        pDC->DrawText(m_tpaSB[ i ]->csLabel, rItem, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

        // if a scrollbar division is currently clicked on, modify the display column
        if (m_tpaSB[ i ]->bPressed)
            switch (i) {
            case 0:
                m_iDisplayColumn = 0;
                break;

            case 1:
                m_iDisplayColumn -= (m_iDisplayColumn == 0) ? 0 : 1;

                if (m_iDisplayColumn == 0)
                    KillTimer(1);   // no need to continue repainting

                break;

            case 3:
                m_iDisplayColumn += (m_iDisplayColumn == m_iMaxColumn) ? 0 : 1;

                if (m_iDisplayColumn == m_iMaxColumn)
                    KillTimer(1);   // no need to continue repainting

                break;

            case 4:
                m_iDisplayColumn = m_iMaxColumn;
                break;
            }
    }
}

/////////////////////////////////////////////////////////////////////////////
// CCWinListBox message handlers

BOOL CCWinListBox::OnEraseBkgnd(CDC* /*pDC*/)
{
    return TRUE;
}

void CCWinListBox::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // Paint off-screen
    CDC*        pDCMem      = new CDC;
    CBitmap*    pPrevBitmap = NULL;
    CBitmap     bmpCanvas;
    CRect       rArea;
    GetClientRect(rArea);
    pDCMem->CreateCompatibleDC(&dc);
    bmpCanvas.CreateCompatibleBitmap(&dc, rArea.Width(), rArea.Height());
    pPrevBitmap = pDCMem->SelectObject(&bmpCanvas);
    // DRAWING BEGINS --------------------------------
    CRect rClient(rArea);
    // Leave room for the border
    rClient.DeflateRect(1, 1, 1, 1);
    // Draw gradient background
    DrawGradientBackground(pDCMem, rClient, m_crBkFrom, m_crBkTo);

    // Are there any items to draw?
    if (m_iTotalItems > 0) {
        CFont* pPrevFont = pDCMem->SelectObject(&m_Font);

        if (m_iItemHeight == - 1)
            m_iItemHeight = pDCMem->GetTextExtent(m_tpaItems[ 0 ]->csLabel).cy + 4;   // add 4 pixels for vertical padding

        // Deal with the scrollbar first
        CRect rSB(rClient);
        rSB.top         = rSB.bottom - m_iItemHeight;
        rClient.bottom  -= m_iItemHeight + 2;   // adjust client area so that items are not drawn over the scrollbar

        if (m_bCalculateSB_Div)  // need to calculate scrollbar divisions?
            CalculateSBDivisions(rSB);

        int         iPrevMode   = pDCMem->SetBkMode(TRANSPARENT);
        COLORREF    crPrevText  = pDCMem->SetTextColor(m_crText);
        DrawSB_ShiftColumn(pDCMem, rSB);     // adjust shift and draw scrollbar

        // A default value of 10 characters in case no column width was set
        if (m_iColumnWidth == -1)
            SetColumnWidth(10, FALSE);

        // Now draw the contents of the listbox
        CRect rItem;
        rItem.left      = rClient.left + 2; // left padding
        rItem.top       = rClient.top;
        rItem.right     = rItem.left + m_iColumnWidth;
        rItem.bottom    = rItem.top + m_iItemHeight;
        int     iCurrentColumn  = 0;
        BOOL    bStopDrawing    = FALSE;

        // Loop through items and draw them
        for (int iIndex = 0; iIndex < m_iTotalItems; iIndex++) {
            // Next column?
            if (rItem.bottom > rClient.bottom) {
                iCurrentColumn++;

                // Once the column to display has been reached
                // positions are advanced as usual
                // otherwise, reset the left position each time
                if (iCurrentColumn > m_iDisplayColumn)
                    rItem.left  += m_iColumnWidth + 2;
                else
                    rItem.left  = rClient.left + 2;

                rItem.top       = rClient.top;
                rItem.right     = rItem.left + m_iColumnWidth;
                rItem.bottom    = rItem.top + m_iItemHeight;

                if (rItem.right > rClient.right)         // Just prettier
                    rItem.right = rClient.right - 3;

                // out of sight?
                if (rItem.left > rClient.right)
                    bStopDrawing = TRUE;
            }

            // Only draw the items that can be seen
            // otherwise set the items' rectangles to 0
            if (iCurrentColumn >= m_iDisplayColumn && !bStopDrawing) {
                // Is the item selected?
                if (m_tpaItems[ iIndex ]->bSelected) {
                    pDCMem->FillSolidRect(rItem.left, rItem.top + 2, rItem.Width(), rItem.Height() - 4,
                                          m_crSelTextBk);
                    pDCMem->Draw3dRect(rItem.left, rItem.top + 2, rItem.Width(), rItem.Height() - 4,
                                       m_crSelBorder1, m_crSelBorder2);
                    pDCMem->SetTextColor(m_crSelText);
                } else
                    pDCMem->SetTextColor(m_tpaItems[ iIndex ]->crFace);

                // Now the text
                pDCMem->DrawText(m_tpaItems[ iIndex ]->csLabel,
                                 CRect(rItem.left + 2, rItem.top, rItem.right, rItem.bottom),
                                 DT_LEFT | DT_SINGLELINE | DT_VCENTER);
                // Record item rectangle
                m_tpaItems[ iIndex ]->rItem = rItem;
            } else
                m_tpaItems[ iIndex ]->rItem.SetRectEmpty();

            // Next item's rectangle
            rItem.top       = rItem.bottom;
            rItem.bottom    = rItem.top + m_iItemHeight;
        }

        pDCMem->SelectObject(pPrevFont);
        pDCMem->SetBkMode(iPrevMode);
        pDCMem->SetTextColor(crPrevText);
        m_iMaxColumn = iCurrentColumn;
    }

    // Draw the border
    pDCMem->Draw3dRect(rArea, m_crBorder1, m_crBorder2);
    // DRAWING ENDS --------------------------------
    // Copy from memory to the screen
    dc.BitBlt(0, 0, rArea.Width(), rArea.Height(), pDCMem, 0, 0, SRCCOPY);
    pDCMem->SelectObject(pPrevBitmap);
    delete pDCMem;
}

void CCWinListBox::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (point.y > m_tpaSB[ 0 ]->rItem.top) {
        for (int i = 0; i < 5; i++)
            if (i != 2 && m_tpaSB[ i ]->rItem.PtInRect(point)) {
                m_tpaSB[ i ]->bPressed = TRUE;

                if (i == 1 || i == 3)
                    SetTimer(1, 250, NULL);

                break;
            }
    } else {
        for (int iIndex = 0; iIndex < m_iTotalItems; iIndex++)
            if (m_tpaItems[ iIndex ]->rItem.PtInRect(point))
                m_tpaItems[ iIndex ]->bSelected = !m_tpaItems[ iIndex ]->bSelected;
            else
                m_tpaItems[ iIndex ]->bSelected = FALSE;
    }

    Invalidate();
    CWnd::OnLButtonDown(nFlags, point);
}


void CCWinListBox::OnLButtonUp(UINT nFlags, CPoint point)
{
    for (int i = 0; i < 5; i++)
        if (m_tpaSB[ i ]->bPressed) {
            m_tpaSB[ i ]->bPressed = FALSE;
            Invalidate();

            if (i == 1 || i == 3)
                KillTimer(1);

            break;
        }

    CWnd::OnLButtonUp(nFlags, point);
}

void CCWinListBox::OnTimer(UINT nIDEvent)
{
    switch (nIDEvent) {
    case 1:
        Invalidate();
        break;
    }

    CWnd::OnTimer(nIDEvent);
}
