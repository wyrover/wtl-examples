// DownloadFileDlg.h: interface for the CDownloadFileDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOWNLOADFILEDLG_H__D93E5C00_2951_424C_8754_A031F1F9DB9F__INCLUDED_)
#define AFX_DOWNLOADFILEDLG_H__D93E5C00_2951_424C_8754_A031F1F9DB9F__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

class CDownloadFileDlg : public CDialogImpl<CDownloadFileDlg>,
    public CWinDataExchange<CDownloadFileDlg>
{
public:
    enum { IDD = IDD_DOWNLOAD_FILE };

    // Construction
    CDownloadFileDlg();

    // Maps
    BEGIN_MSG_MAP(CDownloadFileDlg)
    MSG_WM_INITDIALOG(OnInitDialog)
    COMMAND_ID_HANDLER_EX(IDC_BROWSE, OnBrowse)
    COMMAND_ID_HANDLER_EX(IDOK, OnOK)
    COMMAND_ID_HANDLER_EX(IDCANCEL, OnCancel)
    END_MSG_MAP()

    BEGIN_DDX_MAP(CDownloadFileDlg)
    DDX_TEXT(IDC_URL, m_sURL)
    DDX_TEXT(IDC_LOCAL_FILENAME, m_sLocalFilename)
    END_DDX_MAP()

    // Message handlers
    BOOL OnInitDialog(HWND hwndFocus, LPARAM lParam);

    // Command handlers
    void OnBrowse(UINT uCode, int nID, HWND hwndCtrl);
    void OnOK(UINT uCode, int nID, HWND hwndCtrl);
    void OnCancel(UINT uCode, int nID, HWND hwndCtrl);

    // DDX data
    CString m_sURL, m_sLocalFilename;
};

#endif // !defined(AFX_DOWNLOADFILEDLG_H__D93E5C00_2951_424C_8754_A031F1F9DB9F__INCLUDED_)
