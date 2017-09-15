//////////////////////////////////////////////////////////////////////////////////////////
//      Project: PinkYeti
//   $Workfile:: PageGlobal.cpp                                       $   - Title
//
//  Description: This class will handle the settings for global information
//               These settings do not depend on the channel selected.
//
//       Author: Jay Giganti
// Date Created: 2/10/2001
//     $Author:: Jay                                                   $   - Reviewer
//    $Modtime:: 4/02/01 3:50p                                         $   - Date Reviewed
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
//
//     $Archive:: /Code/Apps/PinkYeti/PageGlobal.cpp                                    $
//
//////////////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "PageGlobal.h"
#include <string>

using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: CPageGlobal
// Description  :
// Return type  :
///////////////////////////////////////////////////////////////////////////////////////////
CPageGlobal::CPageGlobal()
{
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ~CPageGlobal
// Description  :
// Return type  :
///////////////////////////////////////////////////////////////////////////////////////////
CPageGlobal::~CPageGlobal()
{
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: OnInitDialog
// Description  :
// Return type  : LRESULT
// Argument     : UINT      uMsg
// Argument     : WPARAM    wParam
// Argument     : LPARAM    lParam
// Argument     : BOOL&     bHandled
///////////////////////////////////////////////////////////////////////////////////////////
LRESULT CPageGlobal::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    m_AutoLogIn.Attach(GetDlgItem(IDC_AUTO_LOGIN));
    m_AutoRun.Attach(GetDlgItem(IDC_AUTO_RUN));
    m_AutoDownLoad.Attach(GetDlgItem(IDC_AUTO_DOWNLOAD));
    m_DisplayTrayMsg.Attach(GetDlgItem(IDC_NO_DISPLAY));
    m_AutoLogIn.SetCheck(TRUE);
    m_AutoRun.SetCheck(TRUE);
    m_AutoDownLoad.SetCheck(FALSE);
    m_DisplayTrayMsg.SetCheck(FALSE);
    m_TipDlg.SetOwner(m_hWnd);
    return 0;
}
