// MyDialogs.cpp: implementation of the CMyDialogs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "kibbles.h"
#include "MyDialogs.h"

//////////////////////////////////////////////////////////////////////
// CMyFileDialog

CMyFileDialog::CMyFileDialog(
    BOOL bOpenFileDialog, _U_STRINGorID szDefExt, _U_STRINGorID szFileName,
    DWORD dwFlags, _U_STRINGorID szFilter, HWND hwndParent) :
    CFileDialogImpl<CMyFileDialog>(bOpenFileDialog, NULL, NULL, 0,
                                   NULL, hwndParent),
    m_sDefExt(szDefExt.m_lpstr), m_sFileName(szFileName.m_lpstr),
    m_sFilter(szFilter.m_lpstr)
{
    m_ofn.lpstrDefExt = m_sDefExt;
    m_ofn.Flags |= dwFlags;
    m_ofn.lpstrFilter = PrepFilterString(m_sFilter);

    // setup initial file name
    if (!m_sFileName.IsEmpty())
        lstrcpyn(m_szFileName, m_sFileName, _MAX_PATH);
}

void CMyFileDialog::OnInitDone(LPOFNOTIFY lpon)
{
    GetFileDialogWindow().CenterWindow(lpon->lpOFN->hwndOwner);
}

LPCTSTR CMyFileDialog::PrepFilterString(CString& sFilter)
{
    LPTSTR psz = sFilter.GetBuffer(0);
    LPCTSTR pszRet = psz;

    while ('\0' != *psz) {
        if ('|' == *psz)
            *psz++ = '\0';
        else
            psz = CharNext(psz);
    }

    return pszRet;
}


//////////////////////////////////////////////////////////////////////
// CMyFolderDialog

CMyFolderDialog::CMyFolderDialog(
    HWND hWndParent, _U_STRINGorID szTitle, UINT uFlags) :
    CFolderDialogImpl<CMyFolderDialog>(hWndParent, NULL, uFlags),
    m_sTitle(szTitle.m_lpstr)
{
    m_bi.lpszTitle = m_sTitle;
}

void CMyFolderDialog::OnInitialized()
{
    if (!m_sInitialDir.IsEmpty())
        SetSelection(m_sInitialDir);
}
