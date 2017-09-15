//////////////////////////////////////////////////////////////////////////////////////////
//      Project: PinkYeti
//   $Workfile:: ui_ToolTipDlg.cpp                                     $   - Title
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
//     $Archive:: /Code/Pkgs/UI/ui_ToolTipDlg.cpp                                        $
//
//////////////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ui_ToolTipDlg.h"

///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ui_ToolTipDlg
// Description  :
// Return type  :
///////////////////////////////////////////////////////////////////////////////////////////
ui_ToolTipDlg::ui_ToolTipDlg() : m_hWndOwner(NULL), m_bTipsActive(false)
{
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ~ui_ToolTipDlg
// Description  :
// Return type  :
///////////////////////////////////////////////////////////////////////////////////////////
ui_ToolTipDlg::~ui_ToolTipDlg()
{
    CleanUp();
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: CleanUp
// Description  :
// Return type  : void
///////////////////////////////////////////////////////////////////////////////////////////
void ui_ToolTipDlg::CleanUp()
{
    m_bTipsActive = false;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: SetOwner
// Description  :
// Return type  : void
// Argument     : HWND hWndOwner
///////////////////////////////////////////////////////////////////////////////////////////
void ui_ToolTipDlg::SetOwner(HWND hWndOwner)
{
    CleanUp();

    if (hWndOwner) {
        m_hWndOwner = hWndOwner;

        if (m_wndToolTip.IsWindow() == FALSE) {
            m_wndToolTip.Create(m_hWndOwner);
        }

        m_wndToolTip.Activate(TRUE);
        SetupToolTips();
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: SetupToolTips
// Description  :
// Return type  : void
///////////////////////////////////////////////////////////////////////////////////////////
void ui_ToolTipDlg::SetupToolTips()
{
    if (m_hWndOwner) {
        int  nCtrlId;
        HWND hWndChild = ::GetWindow(m_hWndOwner, GW_CHILD);

        while (hWndChild) {
            nCtrlId = ::GetDlgCtrlID(hWndChild);
            CToolInfo ti(TTF_SUBCLASS, hWndChild, 0, NULL, (LPTSTR)nCtrlId);
            m_wndToolTip.AddTool(&ti);
            hWndChild = ::GetWindow(hWndChild, GW_HWNDNEXT);
        }

        m_bTipsActive = true;
    }
}
