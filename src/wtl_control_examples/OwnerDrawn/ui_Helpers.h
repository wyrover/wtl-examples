//////////////////////////////////////////////////////////////////////////////////////////
//      Project: PinkYeti
//   $Workfile:: ui_Helpers.h                                          $   - Title
//
//  Description: Routines to help wrap global functions
//
//       Author: Jay Giganti
// Date Created: 11/09/2000
//     $Author:: Jay                                                   $   - Reviewer
//    $Modtime:: 2/21/01 12:26a                                        $   - Date Reviewed
//
//     $Archive:: /Code/Pkgs/UI/ui_Helpers.h                                             $
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

#ifndef __HELPERS_H__
#define __HELPERS_H__

#ifndef IDANI_CAPTION
    #define IDANI_CAPTION 3
#endif

#include <AtlCtrls.h>
#include <AtlMisc.h>

class ui_Button;

BOOL    ui_PlaySoundResource(int nResID, bool bAsynch = true);
HICON   ui_GetIcon(const UINT uiID);
void    ui_FillSolidRect(const HDC hDC, const CRect & rc, const COLORREF crColor);
void    ui_DrawFocusRect(const HDC hDC, const CRect & rc, const COLORREF crColor);
void    ui_DrawDashedLineH(const HDC hDC, const int nStartX, const int nStartY, const int nEndX);
void    ui_DrawDashedLineV(const HDC hDC, const int nStartX, const int nStartY, const int nEndY);
void    ui_DrawArrow(const HDC hDC, const CRect &rc, const COLORREF crShadow, bool bDown);
void    ui_DrawSplitter(const HDC hDC, const CRect &rc, const COLORREF crShadow, const COLORREF crHiLight);
bool    ui_CreateFont(CFont & Font, const char * szFontName, const int nSize, const bool bBold);
void    ui_GetFullUrl(char * szFullUrl, const DWORD dwLen, const char * szUrlText, const DWORD dwStrLen);

CImageList * ui_CreateImageList(const UINT uiResID, const int nSize, const int nItems, COLORREF crColor);

//Helper Class to select and unselect a GDI Object in Construction and Deconstruction
template <typename Type>
class ui_PushGDI
{
public:
    ui_PushGDI(HDC hDC, Type Object) : m_hDC(hDC),
        m_hOldObject(static_cast<Type>(::SelectObject(m_hDC, Object)))
    {
    }

    ~ui_PushGDI()
    {
        ::SelectObject(m_hDC, m_hOldObject);
    }
private:
    HDC     m_hDC;
    Type    m_hOldObject;
};



#endif //__HELPERS_H__


