// aboutdlg.h : interface of the CAboutDlg class
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABOUTDLG_H__2268E520_777C_42FF_81BD_B7CE6622D519__INCLUDED_)
#define AFX_ABOUTDLG_H__2268E520_777C_42FF_81BD_B7CE6622D519__INCLUDED_

class CAboutDlg : public CDialogImpl<CAboutDlg>
{
public:
    enum { IDD = IDD_ABOUTBOX };

    BEGIN_MSG_MAP(CAboutDlg)
    MSG_WM_INITDIALOG(OnInitDialog)
    COMMAND_ID_HANDLER_EX(IDOK, OnCloseCmd)
    COMMAND_ID_HANDLER_EX(IDCANCEL, OnCloseCmd)
    END_MSG_MAP()

    BOOL OnInitDialog(HWND hwndFocus, LPARAM lParam);
    void OnCloseCmd(UINT uCode, int nID, HWND hwndCtrl);
};

#endif // !defined(AFX_ABOUTDLG_H__2268E520_777C_42FF_81BD_B7CE6622D519__INCLUDED_)
