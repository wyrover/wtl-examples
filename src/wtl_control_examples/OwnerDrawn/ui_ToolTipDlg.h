//////////////////////////////////////////////////////////////////////////////////////////
//      Project: PinkYeti
//   $Workfile:: ui_ToolTipDlg.h                                       $   - Title
//
//  Description: Class to help manage tool tips for dialogs
//
//       Author: Jay Giganti
// Date Created: 3/29/2001
//     $Author:: Jay                                                   $   - Reviewer
//    $Modtime:: 4/02/01 3:45p                                         $   - Date Reviewed
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
//     $Archive:: /Code/Pkgs/UI/ui_ToolTipDlg.h                                          $
//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __UI_TOOLTIPDLG_H__
#define __UI_TOOLTIPDLG_H__

#include <AtlCtrls.h>

class ui_ToolTipDlg
{
public:
    ui_ToolTipDlg();
    virtual ~ui_ToolTipDlg();

    void SetOwner(HWND hWndOwner);
    void SetupToolTips();

    bool IsActive()
    {
        return m_bTipsActive;
    }

protected:
    void CleanUp();

    HWND            m_hWndOwner;
    CToolTipCtrl    m_wndToolTip;
    bool            m_bTipsActive;
private:                                                    //Disable these

    ui_ToolTipDlg(const ui_ToolTipDlg& rhs);                //Copy constructor
    ui_ToolTipDlg& operator =(const ui_ToolTipDlg& rhs);    //Assignment
};

#endif //__UI_TOOLTIPDLG_H__

