//////////////////////////////////////////////////////////////////////////////////////////
//      Project: PinkYeti
//   $Workfile:: ui_Helpers.cpp                                        $   - Title
//
//  Description: Routines to help wrap global functions
//
//       Author: Jay Giganti
// Date Created: 11/09/2000
//     $Author:: Jay                                                   $   - Reviewer
//    $Modtime:: 3/07/01 2:33p                                         $   - Date Reviewed
//
//     $Archive:: /Code/Pkgs/UI/ui_Helpers.cpp                                           $
//
//  This code may be used in compiled form in any way you desire. This
//  file may be redistributed unmodified by any means PROVIDING it is
//  not sold for profit without the authors written consent, and
//  providing that this notice and the authors name and all copyright
//  notices remains intact.
//
//  Email JGiganti@hotmail.com letting him know how you are using it would be nice as well.
//
//  Most of this code has been modified from other exaples on Code Project to do what I
//  need it to do and/or ported to use WTL
//
//  This file is provided "as is" with no expressed or implied warranty.
//  The author accepts no liability for any damage/loss of business that
//  this product may cause.
//
//////////////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ui_Helpers.h"
#include "ui_Button.h"

///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ui_PlaySoundResource
// Description  :
// Return type  : BOOL
// Argument     : int   nResID
// Argument     : bool  bAsynch = true
///////////////////////////////////////////////////////////////////////////////////////////
BOOL ui_PlaySoundResource(int nResID, bool bAsynch)
{
    LPCSTR  szResName   = MAKEINTRESOURCE(nResID);
    DWORD   dwFlags     = SND_RESOURCE;

    if (bAsynch)
        dwFlags |= SND_ASYNC;

    return PlaySound(szResName, _Module.GetResourceInstance(), dwFlags);
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ui_CreateImageList
// Description  : This method will create an images list and then load a bitmap specified
//                by the resource ID.  The method used to load the bitmap will re-map the
//                color 255, 0, 255 to the specified color. This helps with routines that
//                do not draw the images transparently.
// Return type  : CImageList
// Argument     : const UINT    uiResID
// Argument     : const int     nSize
// Argument     : const int     nItems
// Argument     : COLORREF      crColor
///////////////////////////////////////////////////////////////////////////////////////////
CImageList * ui_CreateImageList(const UINT uiResID, const int nSize, const int nItems,
                                COLORREF crColor)
{
    CImageList * pList = new CImageList();
    ATLASSERT(pList);

    if (pList) {
        if (pList->Create(nSize, nSize, ILC_COLORDDB, nItems, 1)) {
            CBitmap     Bmp;
            COLORMAP    Map[1];
            Map[0].from = RGB(255, 0, 255);
            Map[0].to   = crColor;
            Bmp.LoadMappedBitmap(uiResID, 0, Map, 1);
            pList->Add(Bmp);
        } else {
            ATLASSERT(FALSE && "Failed to create image list");
        }
    }

    return pList;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ui_GetIcon
// Description  :
// Return type  : HICON
// Argument     : const UINT uiID
///////////////////////////////////////////////////////////////////////////////////////////
HICON ui_GetIcon(const UINT uiID)
{
    HICON hIcon  = (HICON)LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(uiID),
                                    IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
    ATLASSERT(hIcon);
    return hIcon;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ui_CreateFont
// Description  :
// Return type  : bool
// Argument     : CFont &       Font
// Argument     : const char *  szFontName
// Argument     : const int     nSize
// Argument     : const bool    bBold
///////////////////////////////////////////////////////////////////////////////////////////
bool ui_CreateFont(CFont & Font, const char * szFontName, const int nSize, const bool bBold)
{
    LOGFONT lf;
    int     nSizeFont   = sizeof(LOGFONT);
    BOOL    bCreated    = FALSE;
    ZeroMemory(&lf, nSizeFont);
    ::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT), nSizeFont, &lf);
    lf.lfCharSet    = DEFAULT_CHARSET;
    lf.lfWeight     = bBold ? FW_BOLD : FW_NORMAL;

    if (szFontName) {
        strcpy(lf.lfFaceName, szFontName);
    }

    if (nSize > 0) {
        lf.lfHeight = nSize * 10;
        bCreated    = Font.CreatePointFontIndirect(&lf) != NULL;
    } else {
        bCreated = Font.CreateFontIndirect(&lf) != NULL;
    }

    return (bCreated != FALSE);
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ui_FillSolidRect
// Description  :
// Return type  : void
// Argument     : const HDC         hDC
// Argument     : const CRect &     rc
// Argument     : const COLORREF    crColor
///////////////////////////////////////////////////////////////////////////////////////////
void ui_FillSolidRect(const HDC hDC, const CRect & rc, const COLORREF crColor)
{
    ATLASSERT(hDC);
    ::SetBkColor(hDC, crColor);
    BOOL bResult = ::ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
    ATLASSERT(bResult);
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ui_DrawDashedLineH
// Description  :
// Return type  : void
// Argument     : const HDC hDC
// Argument     : const int nStartX
// Argument     : const int nStartY
// Argument     : const int nEndX
///////////////////////////////////////////////////////////////////////////////////////////
void ui_DrawDashedLineH(const HDC hDC, const int nStartX, const int nStartY, const int nEndX)
{
    int nX = nStartX;
    int nY = nStartY;
    ::MoveToEx(hDC, nX, nY, NULL);

    for (int nAcross = nStartX; nAcross < nEndX; nAcross += 2) {
        nX++;
        ::LineTo(hDC, nX, nY);
        nX++;
        ::MoveToEx(hDC, nX, nY, NULL);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ui_DrawDashedLineV
// Description  :
// Return type  : void
// Argument     : const HDC hDC
// Argument     : const int nStartX
// Argument     : const int nStartY
// Argument     : const int nEndY
///////////////////////////////////////////////////////////////////////////////////////////
void ui_DrawDashedLineV(const HDC hDC, const int nStartX, const int nStartY, const int nEndY)
{
    int nX = nStartX;
    int nY = nStartY;
    ::MoveToEx(hDC, nX, nY, NULL);

    for (int nDown = nStartY; nDown < nEndY; nDown += 2) {
        nY++;
        ::LineTo(hDC, nX, nY);
        nY++;
        ::MoveToEx(hDC, nX, nY, NULL);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ui_DrawFocusRect
// Description  : Draw a Dashed focus rectangle in the color specified
// Return type  : void
// Argument     : const HDC         hDC
// Argument     : const CRect &     rc
// Argument     : const COLORREF    crColor
///////////////////////////////////////////////////////////////////////////////////////////
void ui_DrawFocusRect(const HDC hDC, const CRect & rc, const COLORREF crColor)
{
    ATLASSERT(hDC);
    HPEN hPen = ::CreatePen(PS_SOLID, 0, crColor);
    {
        ui_PushGDI<HPEN> PushPen(hDC, hPen);
        int     nAdjX   = rc.Width()  % 2 ? 1 : 0;
        int     nAdjY   = rc.Height() % 2 ? 1 : 0;
        ui_DrawDashedLineH(hDC, rc.left + 1,    rc.top,             rc.right);
        ui_DrawDashedLineH(hDC, rc.left + 1,    rc.bottom - nAdjY,  rc.right);
        ui_DrawDashedLineV(hDC, rc.left,            rc.top + 1,     rc.bottom);
        ui_DrawDashedLineV(hDC, rc.right - nAdjX,   rc.top + 1,     rc.bottom);
    }
    ::DeleteObject(hPen);
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ui_DrawSplitter
// Description  :
// Return type  : void
// Argument     : const HDC hDC
// Argument     : const CRect &rc
// Argument     : const COLORREF crShadow
// Argument     : const COLORREF crHiLight
///////////////////////////////////////////////////////////////////////////////////////////
void ui_DrawSplitter(const HDC hDC, const CRect &rc, const COLORREF crShadow, const COLORREF crHiLight)
{
    ATLASSERT(hDC);
    HPEN hPenLight  = ::CreatePen(PS_SOLID, 0, crHiLight);
    HPEN hPenDark   = ::CreatePen(PS_SOLID, 0, crShadow);
    {
        ui_PushGDI<HPEN> PushPen(hDC, hPenDark);
        ::MoveToEx(hDC, rc.left, rc.top, NULL);
        ::LineTo(hDC,   rc.left, rc.bottom);
    }
    {
        ui_PushGDI<HPEN> PushPen(hDC, hPenLight);
        ::MoveToEx(hDC, rc.left + 1, rc.top, NULL);
        ::LineTo(hDC,   rc.left + 1, rc.bottom);
    }
    ::DeleteObject(hPenDark);
    ::DeleteObject(hPenLight);
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ui_DrawArrow
// Description  :
// Return type  : void
// Argument     : const HDC         hDC
// Argument     : const CRect &     rc
// Argument     : const COLORREF    crShadow
// Argument     : bool              bDown
///////////////////////////////////////////////////////////////////////////////////////////
void ui_DrawArrow(const HDC hDC, const CRect &rc, const COLORREF crShadow, bool bDown)
{
    ATLASSERT(hDC);
    ::BeginPath(hDC);
    int nEdgeX  = ::GetSystemMetrics(SM_CXEDGE);
    int nW      = rc.Width() - nEdgeX * 2;

    if (nW % 2 == 0)                    //It looks better if odd
        nW--;

    int nH  = (nW + 1) / 2;         //Make it half the height
    int nX  = rc.left + nEdgeX;
    int nY  = rc.top  + (rc.Height() - nH) / 2;
    nW--;
    nH--;

    if (bDown) {
        ::MoveToEx(hDC, nX, nY, NULL);
        ::LineTo(hDC,   nX + nW, nY);
        ::LineTo(hDC,   nX + nW / 2, nY + nH);
        ::LineTo(hDC,   nX, nY);
    } else {
        ::MoveToEx(hDC, nX,         nY + nH, NULL);
        ::LineTo(hDC,   nX + nW,    nY + nH);
        ::LineTo(hDC,   nX + nW / 2, nY);
        ::LineTo(hDC,   nX,         nY + nH);
    }

    ::EndPath(hDC);
    HBRUSH hbrFill  = ::CreateSolidBrush(crShadow);
    {
        ui_PushGDI<HBRUSH> PushBrush(hDC, hbrFill);
        ::StrokeAndFillPath(hDC);
    }
    ::DeleteObject(hbrFill);
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ui_GetFullUrl
// Description  :
// Return type  : void
// Argument     : char *        szFullUrl
// Argument     : const DWORD   dwLen
// Argument     : const char *  szUrlText
// Argument     : const DWORD   dwStrLen
///////////////////////////////////////////////////////////////////////////////////////////
void ui_GetFullUrl(char * szFullUrl, const DWORD dwLen, const char * szUrlText, const DWORD dwStrLen)
{
    DWORD dwPos = strcspn(szUrlText, ":./\\?&#%%");

    //If the user has not entered any seperating or special information
    //then treat it as a name and help by filling in with full info
    if (dwPos == dwStrLen) {
        wsprintf(szFullUrl, "http://www.%s.com/", szUrlText);
    } else {
        dwPos           = 0;
        char *szItem    = (char*)strchr(szUrlText, ':'); //Find protocol to use

        if (szItem) {
            dwPos = szItem - szUrlText + 1;
            strncpy(szFullUrl, szUrlText, dwPos);
            szFullUrl[dwPos] = '\0';
            strcat(szFullUrl, "//");
        } else {
            strcpy(szFullUrl, "http://");
        }

        //Skip slashes if any since we added them automatically
        while (dwPos < dwStrLen && ((szUrlText[dwPos] == '/') || (szUrlText[dwPos] == '\\'))) {
            dwPos++;
        }

        //Find out if they entered any seperator for address
        szItem = (char*)strchr(&szUrlText[dwPos], '.');

        if (szItem == NULL) {
            strcat(szFullUrl, "www.");
        }

        //Add site they wanted
        strcat(szFullUrl, &szUrlText[dwPos]);

        //Add the common ending if they did not enter one
        if (szItem == NULL) {
            strcat(szFullUrl, ".com");
        }

        //Terminate with trailing backslash
        DWORD dwStrLen = strlen(szFullUrl);
        ATLASSERT(dwStrLen < dwLen);

        if (szFullUrl[dwStrLen - 1] != '/') {
            strcat(szFullUrl, "/");
        }
    }

    ATLTRACE("Full Url: %s\n", szFullUrl);
}
