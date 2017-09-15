//////////////////////////////////////////////////////////////////////////////////////////
//      Project: PinkYeti
//   $Workfile:: UserSettingsSheet.h                                   $   - Title
//
//  Description: This file contains the code for the property Sheet that will be used to
//               allow the user to change their settings
//
//       Author: Jay Giganti
// Date Created: 2/10/2001
//     $Author:: Jay                                                   $   - Reviewer
//    $Modtime:: 2/19/01 12:23p                                        $   - Date Reviewed
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
//     $Archive:: /Code/Apps/PinkYeti/UserSettingsSheet.h                                $
//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __USER_SETTINGS_SHEET_H__
#define __USER_SETTINGS_SHEET_H__

#include "Resource.h"
#include "PageBlocks.h"
#include "PageGlobal.h"
#include "ui_TabCtrl.h"

//The actual Property Sheet to Display
class CUserSettingsSheet: public CPropertySheetImpl<CUserSettingsSheet>
{
public:
    CUserSettingsSheet();
    virtual ~CUserSettingsSheet();

    BEGIN_MSG_MAP(CUserSettingsSheet)
    NOTIFY_CODE_HANDLER(TCN_SELCHANGE, OnSelChange)
    CHAIN_MSG_MAP(CPropertySheetImpl<CUserSettingsSheet>)
    REFLECT_NOTIFICATIONS()
    END_MSG_MAP()

    HWND    Create(const HWND hWndParent, const int nStartPage, const CRect & rc);
    LRESULT OnSelChange(WPARAM wParam, LPNMHDR pnmHdr, BOOL & bHandled);

    static int CALLBACK PropSheetCallback(HWND hWnd, UINT uMsg, LPARAM lParam);

protected:
    CPageBlocks     m_PageBlocks;
    CPageGlobal     m_PageGlobal;
    ui_TabCtrl      m_Tab;

private:                                                            //Disable these
    CUserSettingsSheet(const CUserSettingsSheet& rhs);              //Copy constructor
    CUserSettingsSheet& operator =(const CUserSettingsSheet& rhs);  //Assignment
};

#endif //__USER_SETTINGS_SHEET_H__
