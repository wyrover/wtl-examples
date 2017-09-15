//////////////////////////////////////////////////////////////////////////////////////////
//      Project: PinkYeti
//   $Workfile:: UserSettingsSheet.cpp                                 $   - Title
//
//  Description: This file contains the code for the property Sheet that will be used to
//               allow the user to change their settings
//
//       Author: Jay Giganti
// Date Created: 1/10/2001
//     $Author:: Jay                                                   $   - Reviewer
//    $Modtime:: 3/30/01 2:28p                                         $   - Date Reviewed
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
//     $Archive:: /Code/Apps/PinkYeti/UserSettingsSheet.cpp                              $
//
//////////////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "UserSettingsSheet.h"

static const COLORREF g_crTabFill       = RGB(181, 192, 187);
static const COLORREF g_crTabSel        = RGB(222, 222, 222);
static const COLORREF g_crTabHi         = RGB(246, 252, 249);
static const COLORREF g_crTabUnSel      = RGB(227, 235, 231);
static const COLORREF g_crText          = RGB(10,    0, 100);

///////////////////////////////////////////////////////////////////////////////////////////
// Function name: CUserSettingsSheet
// Description  :
// Return type  :
// Argument     :
///////////////////////////////////////////////////////////////////////////////////////////
CUserSettingsSheet::CUserSettingsSheet()
{
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: ~CUserSettingsSheet
// Description  :
// Return type  :
///////////////////////////////////////////////////////////////////////////////////////////
CUserSettingsSheet::~CUserSettingsSheet()
{
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: Create
// Description  : Duplicate most of the code from AtlDlgs.h
// Return type  : HWND HWND
// Argument     : const HWND    hWndParent
// Argument     : const int     nStartPage
// Argument     : const CRect & rc
///////////////////////////////////////////////////////////////////////////////////////////
HWND CUserSettingsSheet::Create(const HWND hWndParent, const int nStartPage, const CRect & rc)
{
    ATLASSERT(m_hWnd == NULL);
    AddPage(m_PageBlocks);
    AddPage(m_PageGlobal);
    m_psh.dwFlags       = PSH_NOAPPLYNOW | PSH_MODELESS | PSH_USECALLBACK;
    m_psh.hwndParent    = hWndParent;
    m_psh.phpage        = (HPROPSHEETPAGE*)m_arrPages.GetData();
    m_psh.nPages        = m_arrPages.GetSize();
    m_psh.pfnCallback   = CUserSettingsSheet::PropSheetCallback;
    _Module.AddCreateWndData(&m_thunk.cd, this);
    HWND hWnd = (HWND)::PropertySheet(&m_psh);
    _CleanUpPages();    // ensure clean-up, required if call failed
    ATLASSERT(m_hWnd == hWnd);
    HWND hWndTab = GetTabControl();
    m_Tab.SubclassWindow(hWndTab);

    if (m_hWnd) {
        HWND hWndBtn = GetDlgItem(IDCANCEL);

        if (hWndBtn) {
            ::ShowWindow(hWndBtn, SW_HIDE);
        }

        hWndBtn = GetDlgItem(IDOK);

        if (hWndBtn) {
            ::ShowWindow(hWndBtn, SW_HIDE);
        }

        int nAdjX = GetSystemMetrics(SM_CXDLGFRAME) * 2;
        int nAdjY = GetSystemMetrics(SM_CYDLGFRAME) * 2;
        SetWindowPos(NULL, rc.left - nAdjX, rc.top - nAdjY, rc.Width(), rc.Height(),
                     SWP_NOZORDER | SWP_NOACTIVATE);
    }

    SetActivePage(nStartPage);
    return hWnd;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: OnSelChange
// Description  :
// Return type  : LRESULT
// Argument     : WPARAM    wParam
// Argument     : LPNMHDR   pnmHdr
// Argument     : BOOL &    bHandled
///////////////////////////////////////////////////////////////////////////////////////////
LRESULT CUserSettingsSheet::OnSelChange(WPARAM wParam, LPNMHDR pnmHdr, BOOL & bHandled)
{
    return  DefWindowProc(WM_NOTIFY, wParam, (LPARAM)pnmHdr);
}
///////////////////////////////////////////////////////////////////////////////////////////
// Function name: PropSheetCallback
// Description  :
// Return type  : int
// Argument     : HWND      hWnd
// Argument     : UINT      uMsg
// Argument     : LPARAM    lParam
///////////////////////////////////////////////////////////////////////////////////////////
int CALLBACK CUserSettingsSheet::PropSheetCallback(HWND hWnd, UINT uMsg, LPARAM lParam)
{
    int nRetVal = 0;

    if (uMsg == PSCB_INITIALIZED) {
        ATLASSERT(hWnd != NULL);
        CUserSettingsSheet* pT = (CUserSettingsSheet*)_Module.ExtractCreateWndData();
        pT->SubclassWindow(hWnd);   // subclass the sheet window
        pT->_CleanUpPages();        // remove page handles array
    } else if (uMsg == PSCB_PRECREATE) {
        LPDLGTEMPLATE pTemplate = (LPDLGTEMPLATE)lParam;
        ATLASSERT(pTemplate);
        DWORD dwRemove  = WS_POPUP | WS_SYSMENU | WS_CAPTION | DS_MODALFRAME;
        DWORD dwAdd     = WS_CHILD | WS_VISIBLE | WS_TABSTOP | DS_CONTEXTHELP | DS_3DLOOK; //|DS_CONTROL;
        pTemplate->style             = (pTemplate->style & ~dwRemove) | dwAdd;
        pTemplate->dwExtendedStyle  |= WS_EX_CONTROLPARENT;
        nRetVal = 1;
    }

    return nRetVal;
}
