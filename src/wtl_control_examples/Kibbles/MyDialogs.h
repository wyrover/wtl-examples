// MyDialogs.h: interface for the CMyDialogs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYDIALOGS_H__F4B3974A_0B75_4825_9F76_D8A385C15D43__INCLUDED_)
#define AFX_MYDIALOGS_H__F4B3974A_0B75_4825_9F76_D8A385C15D43__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////

class CMyFileDialog : public CFileDialogImpl<CMyFileDialog>
{
public:
    // Construction
    CMyFileDialog(BOOL bOpenFileDialog,
                  _U_STRINGorID szDefExt = 0U,
                  _U_STRINGorID szFileName = 0U,
                  DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                  _U_STRINGorID szFilter = 0U,
                  HWND hwndParent = NULL);

    // Maps
    BEGIN_MSG_MAP(CMyFileDialog)
    CHAIN_MSG_MAP(CFileDialogImpl<CMyFileDialog>)
    END_MSG_MAP()

    // Overrides
    void OnInitDone(LPOFNOTIFY lpon);

protected:
    CString m_sDefExt, m_sFileName, m_sFilter;

    LPCTSTR PrepFilterString(CString& sFilter);
};

//////////////////////////////////////////////////////////////////////

class CMyFolderDialog : public CFolderDialogImpl<CMyFolderDialog>
{
public:
    // Construction
    CMyFolderDialog(HWND hWndParent = NULL,
                    _U_STRINGorID szTitle = 0U,
                    UINT uFlags = BIF_RETURNONLYFSDIRS);

    // Overrides
    void OnInitialized();

    // Data
    CString m_sInitialDir;

protected:
    CString m_sTitle;
};

#endif // !defined(AFX_MYDIALOGS_H__F4B3974A_0B75_4825_9F76_D8A385C15D43__INCLUDED_)
