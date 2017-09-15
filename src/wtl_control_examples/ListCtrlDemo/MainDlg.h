// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <sstream>
#include <iomanip>
#include <atltime.h>
#include "ListCtrl.h"

class CUserProfile
{
public:
    CUserProfile()
    {
        m_bAdministrator = FALSE;
        m_strUserName = _T("");
        m_strDepartment = _T("");
        m_strPhoneNumber = _T("");
    }

    CUserProfile(BOOL bAdministrator, LPCTSTR lpszUserName, LPCTSTR lpszDepartment, LPCTSTR lpszPhoneNumber)
    {
        m_bAdministrator = bAdministrator;
        m_strUserName = lpszUserName;
        m_strDepartment = lpszDepartment;
        m_strPhoneNumber = lpszPhoneNumber;
    }

    BOOL m_bAdministrator;
    CString m_strUserName;
    CString m_strDepartment;
    CString m_strPhoneNumber;
};

class CListUserData : public CListImpl< CListUserData >
{
public:
    DECLARE_WND_CLASS(_T("UserList"))

protected:
    CImageList m_ilItemImages;
    CListArray < CUserProfile > m_aUsers;
    enum UserColumns { colName, colDept, colPhone };

public:
    BOOL Initialise()
    {
        if (!m_ilItemImages.CreateFromImage(IDB_EXAMPLE, 16, 0, RGB(255, 0, 255), IMAGE_BITMAP, LR_CREATEDIBSECTION))
            return FALSE;

        SetImageList(m_ilItemImages);
        AddColumn(_T("User Name"), 150);
        AddColumn(_T("Department"), 100);
        AddColumn(_T("Phone Number"), 100);
        return CListImpl< CListUserData >::Initialise();
    }

    int AddUser(CUserProfile userProfile)
    {
        m_aUsers.Add(userProfile);
        return CListImpl< CListUserData >::AddItem() ? GetItemCount() - 1 : -1;
    }

    int AddUser(BOOL bAdministrator, LPCTSTR lpszUserName, LPCTSTR lpszDepartment, LPCTSTR lpszPhoneNumber)
    {
        return AddUser(CUserProfile(bAdministrator, lpszUserName, lpszDepartment, lpszPhoneNumber));
    }

    int GetItemCount() // required by CListImpl
    {
        return m_aUsers.GetSize();
    }

    BOOL GetUser(int nItem, CUserProfile& userProfile)
    {
        if (nItem < 0 || nItem >= GetItemCount())
            return FALSE;

        userProfile = m_aUsers[ nItem ];
        return TRUE;
    }

    CString GetItemText(int nItem, int nSubItem)   // required by CListImpl
    {
        CUserProfile userProfile;

        if (!GetUser(nItem, userProfile))
            return _T("");

        switch ((UserColumns)nSubItem) {
        case colName:
            return userProfile.m_strUserName;

        case colDept:
            return userProfile.m_strDepartment;

        case colPhone:
            return userProfile.m_strPhoneNumber;
        }

        return _T("");
    }

    int GetItemImage(int nItem, int nSubItem)   // overrides CListImpl::GetItemImage
    {
        if ((UserColumns)nSubItem != colName)
            return -1;

        CUserProfile userProfile;

        if (!GetUser(nItem, userProfile))
            return -1;

        return userProfile.m_bAdministrator ? 6 : 0;
    }

    void ReverseItems() // overrides CListImpl::ReverseItems
    {
        m_aUsers.Reverse();
    }

    class CompareItem
    {
    public:
        CompareItem(UserColumns colColumn) : m_colColumn(colColumn) {}
        inline bool operator()(const CUserProfile& userProfile1, const CUserProfile& userProfile2)
        {
            switch (m_colColumn) {
            case colName:
                return (userProfile1.m_strUserName.Compare(userProfile2.m_strUserName) < 0);

            case colDept:
                return (userProfile1.m_strDepartment.Compare(userProfile2.m_strDepartment) < 0);

            case colPhone:
                return (userProfile1.m_strPhoneNumber.Compare(userProfile2.m_strPhoneNumber) < 0);
            }

            return false;
        }

    protected:
        UserColumns m_colColumn;
    };

    void SortItems(int nColumn, BOOL bAscending)   // overrides CListImpl::SortItems
    {
        m_aUsers.Sort(CompareItem((UserColumns)nColumn));
    }
};

class CMainDlg : public CDialogImpl<CMainDlg>
{
public:
    CMainDlg()
    {
        m_wndListCtrl.RegisterClass();
        m_wndUserData.RegisterClass();
        m_wndUserList.RegisterClass();
        m_bShowMessage = TRUE;
        m_bShowThemed = TRUE;
    }

    enum { IDD = IDD_MAINDLG };

    BEGIN_MSG_MAP(CMainDlg)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
    COMMAND_ID_HANDLER(IDOK, OnOK)
    COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
    COMMAND_ID_HANDLER(IDC_THEME, OnTheme)
    NOTIFY_HANDLER_EX(IDC_USERDATA, LCN_SELECTED, OnUserDataSelected)
    NOTIFY_HANDLER_EX(IDC_USERLIST, LCN_SELECTED, OnUserListSelected)
    NOTIFY_HANDLER_EX(IDC_LISTCTRL, LCN_HYPERLINK, OnListHyperLink)
    REFLECT_NOTIFICATIONS()
    END_MSG_MAP()

protected:
    CListCtrl m_wndListCtrl;
    CListCtrlData< CUserProfile > m_wndUserData;
    CListUserData m_wndUserList;
    CImageList m_ilItemImages;
    CFont m_fntCustomFont1;
    CFont m_fntCustomFont2;
    BOOL m_bShowMessage;
    BOOL m_bShowThemed;

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        // center the dialog on the screen
        CenterWindow();
        // set icons
        HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME),
                                         IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
        SetIcon(hIcon, TRUE);
        HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME),
                                              IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
        SetIcon(hIconSmall, FALSE);
        m_wndListCtrl.SubclassWindow(GetDlgItem(IDC_LISTCTRL));
        m_wndUserData.SubclassWindow(GetDlgItem(IDC_USERDATA));
        m_wndUserList.SubclassWindow(GetDlgItem(IDC_USERLIST));

        if (!m_ilItemImages.CreateFromImage(IDB_EXAMPLE, 16, 0, RGB(255, 0, 255), IMAGE_BITMAP, LR_CREATEDIBSECTION))
            return FALSE;

        InitBasicList();
        InitDataList();
        InitUserList();
        return TRUE;
    }

    void InitBasicList()
    {
        LOGFONT logFont = { 0 };
        logFont.lfCharSet = DEFAULT_CHARSET;
        logFont.lfHeight = 90;
        lstrcpy(logFont.lfFaceName, _T("New Times Roman"));
        logFont.lfWeight = FW_BOLD;
        logFont.lfItalic = (BYTE)TRUE;
        m_fntCustomFont1.CreatePointFontIndirect(&logFont);
        logFont.lfHeight = 100;
        lstrcpy(logFont.lfFaceName, _T("Arial"));
        logFont.lfUnderline = (BYTE)TRUE;
        m_fntCustomFont2.CreatePointFontIndirect(&logFont);
        m_wndListCtrl.SetImageList(m_ilItemImages);
        m_wndListCtrl.SetFocusSubItem(TRUE);
        m_wndListCtrl.AddColumn(_T("Column 1"), 150);
        m_wndListCtrl.AddColumn(_T(""), 0, ITEM_IMAGE_3STATE, TRUE, ITEM_FORMAT_CHECKBOX_3STATE);
        m_wndListCtrl.AddColumn(_T("Column 2"), 130);
        m_wndListCtrl.AddColumn(_T("Column 3"), 80, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT);
        m_wndListCtrl.AddColumn(_T("Column 4"), 120);
        m_wndListCtrl.AddColumn(_T("Column 5"), 170, ITEM_IMAGE_ATTACHMENT, FALSE, ITEM_FORMAT_PROGRESS);
        srand(12345);

        for (int nItem = 1; nItem <= 1000; nItem++) {
#ifdef _UNICODE
            wostringstream osItemText;
#else
            ostringstream osItemText;
#endif
            osItemText << _T("Item ") << nItem;
            int nNewItem = m_wndListCtrl.AddItem(osItemText.str().c_str(), rand() % 6);
            m_wndListCtrl.SetItemCheck(nNewItem, 1, (rand() % 3) - 1);
            osItemText.str(_T(""));
            TCHAR nSortChar = _T('A') + (rand() % 26);
            osItemText << nSortChar << _T(" Random Text");
            m_wndListCtrl.SetItemText(nNewItem, 2, osItemText.str().c_str());
            m_wndListCtrl.SetItemImage(nNewItem, 2, rand() % 6);
            osItemText.str(_T(""));
            osItemText << nItem;
            m_wndListCtrl.SetItemText(nNewItem, 3, osItemText.str().c_str());
            osItemText.str(_T(""));
            osItemText << (rand() % 101);
            m_wndListCtrl.SetItemText(nNewItem, 5, osItemText.str().c_str());
        }

        CListArray < CString > aComboList;
        aComboList.Add(_T("Item 1"));
        aComboList.Add(_T("Item 2"));
        aComboList.Add(_T("Item 3"));
        aComboList.Add(_T("Item 4"));
        aComboList.Add(_T("Item 5"));
        m_wndListCtrl.SetItemText(0, 4, _T("Combo (Edit):"));
        m_wndListCtrl.SetItemFormat(0, 5, ITEM_FORMAT_COMBO, ITEM_FLAGS_COMBO_EDIT, aComboList);
        m_wndListCtrl.SetItemComboIndex(0, 5, 0);   // "Item 1"
        m_wndListCtrl.SetItemText(1, 4, _T("Combo (List):"));
        m_wndListCtrl.SetItemFormat(1, 5, ITEM_FORMAT_COMBO, ITEM_FLAGS_NONE, aComboList);
        m_wndListCtrl.SetItemText(1, 5, _T("Item 1"));
        m_wndListCtrl.SetItemText(2, 4, _T("Edit:"));
        m_wndListCtrl.SetItemFormat(2, 5, ITEM_FORMAT_EDIT);
        m_wndListCtrl.SetItemText(2, 5, _T("<alpha-numeric>"));
        m_wndListCtrl.SetItemText(3, 4, _T("Edit (Numeric):"));
        m_wndListCtrl.SetItemFormat(3, 5, ITEM_FORMAT_EDIT, ITEM_FLAGS_EDIT_NUMBER);
        m_wndListCtrl.SetItemText(3, 5, _T("123"));
        CTime tmDateTime = CTime::GetCurrentTime();
        SYSTEMTIME stDateTime;
        tmDateTime.GetAsSystemTime(stDateTime);
        m_wndListCtrl.SetItemText(4, 4, _T("Date (inc Time):"));
        m_wndListCtrl.SetItemFormat(4, 5, ITEM_FORMAT_DATETIME, ITEM_FLAGS_DATETIME_NONE);
        m_wndListCtrl.SetItemDate(4, 5, stDateTime);
        m_wndListCtrl.SetItemText(5, 4, _T("Date (Date only):"));
        m_wndListCtrl.SetItemFormat(5, 5, ITEM_FORMAT_DATETIME, ITEM_FLAGS_DATE_ONLY);
        m_wndListCtrl.SetItemDate(5, 5, stDateTime);
        m_wndListCtrl.SetItemText(6, 4, _T("Solid progress:"));
        m_wndListCtrl.SetItemFormat(6, 5, ITEM_FORMAT_PROGRESS, ITEM_FLAGS_PROGRESS_SOLID);
        m_wndListCtrl.SetItemText(7, 4, _T("Normal progress:"));
        m_wndListCtrl.SetItemText(8, 4, _T("Checkbox:"));
        m_wndListCtrl.SetItemFormat(8, 5, ITEM_FORMAT_CHECKBOX);
        m_wndListCtrl.SetItemText(9, 4, _T("Checkbox (3 State):"));
        m_wndListCtrl.SetItemFormat(9, 5, ITEM_FORMAT_CHECKBOX_3STATE);
        m_wndListCtrl.SetItemText(10, 4, _T("Checkbox (read-only):"));
        m_wndListCtrl.SetItemFormat(10, 5, ITEM_FORMAT_CHECKBOX, ITEM_FLAGS_READ_ONLY);
        m_wndListCtrl.SetItemText(11, 4, _T("Hyperlink"));
        m_wndListCtrl.SetItemFormat(11, 4, ITEM_FORMAT_HYPERLINK);
        m_wndListCtrl.SetItemText(12, 4, _T("Some very long text that should trigger titletip"));
        m_wndListCtrl.SetItemText(13, 4, _T("Built-in tooltip support"));
        m_wndListCtrl.SetItemToolTip(13, _T("This is a\nmultiline tooltip"));
        m_wndListCtrl.SetItemText(14, 4, _T("Font Support"));
        m_wndListCtrl.SetItemFont(14, 4, m_fntCustomFont1);
        m_wndListCtrl.SetItemText(15, 4, _T("Font Support"));
        m_wndListCtrl.SetItemFont(15, 4, m_fntCustomFont2);
        m_wndListCtrl.SetItemText(16, 4, _T("Colour Support"));
        m_wndListCtrl.SetItemColours(16, 4, RGB(128, 128, 64), RGB(0, 255, 0));
        m_wndListCtrl.SetItemText(17, 4, _T("Colour Support"));
        m_wndListCtrl.SetItemColours(17, 4, RGB(128, 0, 128), RGB(255, 255, 128));
    }

    void InitDataList()
    {
        CUserProfile userProfile1(FALSE, _T("Fred"), _T("Accounts"), _T("1234"));
        CUserProfile userProfile2(TRUE, _T("Simon"), _T("Accounts"), _T("1235"));
        CUserProfile userProfile3(FALSE, _T("Kate"), _T("Development"), _T("2341"));
        CUserProfile userProfile4(FALSE, _T("David"), _T("Development"), _T("2342"));
        CUserProfile userProfile5(TRUE, _T("Jake"), _T("Development"), _T("2343"));
        CUserProfile userProfile6(FALSE, _T("Mike"), _T("Marketing"), _T("5343"));
        CUserProfile userProfile7(FALSE, _T("Tony"), _T("Marketing"), _T("5344"));
        m_wndUserData.SetImageList(m_ilItemImages);
        m_wndUserData.AddColumn(_T("User Name"), 150);
        m_wndUserData.AddColumn(_T("Department"), 100);
        m_wndUserData.AddColumn(_T("Phone Number"), 100);
        int nUser = m_wndUserData.AddItem(userProfile1.m_strUserName, userProfile1.m_bAdministrator ? 6 : 0);
        m_wndUserData.SetItemText(nUser, 1, userProfile1.m_strDepartment);
        m_wndUserData.SetItemText(nUser, 2, userProfile1.m_strPhoneNumber);
        m_wndUserData.SetItemData(nUser, userProfile1);
        nUser = m_wndUserData.AddItem(userProfile2.m_strUserName, userProfile2.m_bAdministrator ? 6 : 0);
        m_wndUserData.SetItemText(nUser, 1, userProfile2.m_strDepartment);
        m_wndUserData.SetItemText(nUser, 2, userProfile2.m_strPhoneNumber);
        m_wndUserData.SetItemData(nUser, userProfile2);
        nUser = m_wndUserData.AddItem(userProfile3.m_strUserName, userProfile3.m_bAdministrator ? 6 : 0);
        m_wndUserData.SetItemText(nUser, 1, userProfile3.m_strDepartment);
        m_wndUserData.SetItemText(nUser, 2, userProfile3.m_strPhoneNumber);
        m_wndUserData.SetItemData(nUser, userProfile3);
        nUser = m_wndUserData.AddItem(userProfile4.m_strUserName, userProfile4.m_bAdministrator ? 6 : 0);
        m_wndUserData.SetItemText(nUser, 1, userProfile4.m_strDepartment);
        m_wndUserData.SetItemText(nUser, 2, userProfile4.m_strPhoneNumber);
        m_wndUserData.SetItemData(nUser, userProfile4);
        nUser = m_wndUserData.AddItem(userProfile5.m_strUserName, userProfile5.m_bAdministrator ? 6 : 0);
        m_wndUserData.SetItemText(nUser, 1, userProfile5.m_strDepartment);
        m_wndUserData.SetItemText(nUser, 2, userProfile5.m_strPhoneNumber);
        m_wndUserData.SetItemData(nUser, userProfile5);
        nUser = m_wndUserData.AddItem(userProfile6.m_strUserName, userProfile6.m_bAdministrator ? 6 : 0);
        m_wndUserData.SetItemText(nUser, 1, userProfile6.m_strDepartment);
        m_wndUserData.SetItemText(nUser, 2, userProfile6.m_strPhoneNumber);
        m_wndUserData.SetItemData(nUser, userProfile6);
        nUser = m_wndUserData.AddItem(userProfile7.m_strUserName, userProfile7.m_bAdministrator ? 6 : 0);
        m_wndUserData.SetItemText(nUser, 1, userProfile7.m_strDepartment);
        m_wndUserData.SetItemText(nUser, 2, userProfile7.m_strPhoneNumber);
        m_wndUserData.SetItemData(nUser, userProfile7);
    }

    void InitUserList()
    {
        CUserProfile userProfile1(FALSE, _T("Fred"), _T("Accounts"), _T("1234"));
        CUserProfile userProfile2(TRUE, _T("Simon"), _T("Accounts"), _T("1235"));
        CUserProfile userProfile3(FALSE, _T("Kate"), _T("Development"), _T("2341"));
        CUserProfile userProfile4(FALSE, _T("David"), _T("Development"), _T("2342"));
        CUserProfile userProfile5(TRUE, _T("Jake"), _T("Development"), _T("2343"));
        CUserProfile userProfile6(FALSE, _T("Mike"), _T("Marketing"), _T("5343"));
        CUserProfile userProfile7(FALSE, _T("Tony"), _T("Marketing"), _T("5344"));
        m_wndUserList.AddUser(userProfile1);
        m_wndUserList.AddUser(userProfile2);
        m_wndUserList.AddUser(userProfile3);
        m_wndUserList.AddUser(userProfile4);
        m_wndUserList.AddUser(userProfile5);
        m_wndUserList.AddUser(userProfile6);
        m_wndUserList.AddUser(userProfile7);
    }

    LRESULT OnUserDataSelected(LPNMHDR lpNMHDR)
    {
        CListNotify *pListNotify = reinterpret_cast<CListNotify *>(lpNMHDR);
        CUserProfile userProfile;
        m_wndUserData.GetItemData(pListNotify->m_nItem, userProfile);
#ifdef _UNICODE
        wostringstream osItemText;
#else
        ostringstream osItemText;
#endif
        osItemText << _T("User Selected: ") << userProfile.m_strUserName << _T("\r\n");
        osItemText << _T("Press Cancel to stop notifications");

        if (m_bShowMessage) {
            if (MessageBox(osItemText.str().c_str(), _T("Selected"), MB_OKCANCEL) != IDOK)
                m_bShowMessage = FALSE;
        }

        return 0;
    }

    LRESULT OnListHyperLink(LPNMHDR lpNMHDR)
    {
        CListNotify *pListNotify = reinterpret_cast<CListNotify *>(lpNMHDR);
        MessageBox(_T("Hyperlink clicked"), _T("Hyperlink"));
        return 0;
    }

    LRESULT OnUserListSelected(LPNMHDR lpNMHDR)
    {
        CListNotify *pListNotify = reinterpret_cast<CListNotify *>(lpNMHDR);
        CUserProfile userProfile;
        m_wndUserList.GetUser(pListNotify->m_nItem, userProfile);
#ifdef _UNICODE
        wostringstream osItemText;
#else
        ostringstream osItemText;
#endif
        osItemText << _T("User Selected: ") << userProfile.m_strUserName << _T("\r\n");
        osItemText << _T("Press Cancel to stop notifications");

        if (m_bShowMessage) {
            if (MessageBox(osItemText.str().c_str(), _T("Selected"), MB_OKCANCEL) != IDOK)
                m_bShowMessage = FALSE;
        }

        return 0;
    }

    LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
        dlg.DoModal();
        return 0;
    }

    LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        // TODO: Add validation code
        EndDialog(wID);
        return 0;
    }

    LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        EndDialog(wID);
        return 0;
    }

    LRESULT OnTheme(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        m_bShowThemed = !m_bShowThemed;
        m_wndListCtrl.ShowThemed(m_bShowThemed);
        m_wndUserData.ShowThemed(m_bShowThemed);
        m_wndUserList.ShowThemed(m_bShowThemed);
        return 0;
    }
};
