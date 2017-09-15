// JobRunningDlg.h: interface for the CJobRunningDlg class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JOBRUNNINGDLG_H__A003AC7D_CF4F_484A_B42A_058CC38C34D6__INCLUDED_)
#define AFX_JOBRUNNINGDLG_H__A003AC7D_CF4F_484A_B42A_058CC38C34D6__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

class CJobRunningDlg : public CDialogImpl<CJobRunningDlg>,
    public CWinDataExchange<CJobRunningDlg>
{
public:
    // Construction
    enum { IDD = IDD_JOB_RUNNING };

    CJobRunningDlg();

    // Maps
    BEGIN_MSG_MAP(CJobRunningDlg)
    MSG_WM_INITDIALOG(OnInitDialog)
    COMMAND_ID_HANDLER_EX(IDOK, OnOK)
    COMMAND_ID_HANDLER_EX(IDCANCEL, OnCancel)
    END_MSG_MAP()

    BEGIN_DDX_MAP(CJobRunningDlg)
    DDX_RADIO(IDC_FINISH_JOB, m_nChoice)
    END_DDX_MAP()

    // Message handlers
    BOOL OnInitDialog(HWND hwndFocus, LPARAM lParam);
    void OnOK(UINT uCode, int nID, HWND hwndCtrl);
    void OnCancel(UINT uCode, int nID, HWND hwndCtrl);

    // Data
    enum { complete, cancel, letitrun };
    int m_nChoice;
};

#endif // !defined(AFX_JOBRUNNINGDLG_H__A003AC7D_CF4F_484A_B42A_058CC38C34D6__INCLUDED_)
