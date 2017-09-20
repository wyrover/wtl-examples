// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "MainDlg.h"
#include <atlcoll.h>
#include <tracetool/tracetool.h>

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    // center the dialog on the screen
    CenterWindow();
    // set icons
    HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
    SetIcon(hIcon, TRUE);
    HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
    SetIcon(hIconSmall, FALSE);
    //DragAcceptFiles(TRUE);
    

    return TRUE;
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
    dlg.DoModal();
    return 0;
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: Add validation code
    EndDialog(wID);
    return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    EndDialog(wID);
    return 0;
}


LRESULT CMainDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    WTL::CPaintDC dc(m_hWnd);
   /* Graphics g(dc.m_hDC);
    DrawPic(dc.m_hDC, filename_);*/
    //draw_image(m_hWnd, filename_);
    return 0;
}

LRESULT CMainDlg::OnDropFiles(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    /*HDROP hDropInfo = (HDROP)wParam;
    wchar_t file[MAX_PATH];
    DragQueryFileW(hDropInfo, 0, file, sizeof(file) / sizeof(*file));
    filename_ = string16(file);
    draw_image(m_hWnd, filename_);
    DragFinish(hDropInfo);*/
    return 0;
}

LRESULT CMainDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    SendMessage(m_hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
    return 0;
}

LRESULT CMainDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    UINT state = (UINT)wParam;
    CSize Size = CSize(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    InvalidateRect(NULL, TRUE);
    return 0;
}
LRESULT CMainDlg::OnBnClickedButton1(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    CAtlMap<CString, CString> map_data;
    
    CRegKey reg;

    do 
    {
        CString rootkey = TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\SideBySide\\Winners");
        LONG lRes = reg.Open(HKEY_LOCAL_MACHINE, rootkey, KEY_READ | KEY_WOW64_64KEY);
        if (lRes != ERROR_SUCCESS) {
            break;
        }

        TCHAR buff[256];
        DWORD len = _countof(buff);
        for (int i = 0; ERROR_SUCCESS == reg.EnumKey(i, buff, &len); i++, len = _countof(buff)) {
            if (StrStrI(buff, TEXT(".inf")) > 0) {
                //TRACE_SEND_W(buff);
                map_data[buff] = buff;
            }
            //CRegKey infReg;
            //TCHAR ext[64];
            //ULONG len2 = _countof(ext);
            //if (ERROR_SUCCESS == infReg.Open(HKEY_LOCAL_MACHINE, rootkey + _T("\\") + buff, KEY_READ)
            //    && ERROR_SUCCESS == infReg.QueryStringValue(_T("Extension"), ext, &len2)) {
            //        //m_mimes[CStringA(ext).MakeLower()] = CStringA(buff).MakeLower();


            //}
        }

        POSITION begin_pos = map_data.GetStartPosition();
        CAtlMap<CString, CString>::CPair* item = NULL;
        while ((item = map_data.GetNext(begin_pos)) != NULL) {
            TRACE_SEND_W(item->m_key);
            TRACE_SEND_W(item->m_value);
        }
           

        TRACE_SEND_A("hello!");

    } while (0);
    

	return 0;
}

