//////////////////////////////////////////////////////////////////////////////////////////
//      Project: PinkYeti
//   $Workfile:: PageBlocks.cpp                                        $   - Title
//
//  Description: This class will handle the settings for what content that want to allow
//               based on how people have rated it for the type of information it holds
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
//     $Archive:: /Code/Apps/PinkYeti/PageBlocks.cpp                                     $
//
//////////////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "PageBlocks.h"
#include <string>

using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: CPageBlocks
// Description  :
// Return type  :
///////////////////////////////////////////////////////////////////////////////////////////
CPageBlocks::CPageBlocks()
{
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ~CPageBlocks
// Description  :
// Return type  :
///////////////////////////////////////////////////////////////////////////////////////////
CPageBlocks::~CPageBlocks()
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
LRESULT CPageBlocks::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    m_Mature.Attach(GetDlgItem(IDC_MATURE));
    m_Spam.Attach(GetDlgItem(IDC_SPAM));
    m_Offensive.Attach(GetDlgItem(IDC_OFFENSIVE));
    m_Mature.SetCheck(FALSE);
    m_Spam.SetCheck(TRUE);
    m_Offensive.SetCheck(FALSE);
    m_TipDlg.SetOwner(m_hWnd);
    return 0;
}
