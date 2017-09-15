#pragma once


// CIconListBox

class CIconListBox : public CListBox
{
    DECLARE_DYNAMIC(CIconListBox)

    struct LBDATA {
        HICON hIcon;
        int   nIconHeight;
        int   nIconWidth;
    };

public:
    CIconListBox();
    virtual ~CIconListBox();

protected:
    DECLARE_MESSAGE_MAP()

public:
    virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
    virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);

    // Interface
    int AddString(LPCTSTR lpszItem, int nIcon);
    int DeleteString(UINT nIndex);
    int InsertString(int nIndex, LPCTSTR lpszItem, int nIcon);
    void ResetContent();


private:
    void DeleteItemData(UINT nIndex);

    int m_nIconHeight;  // Icon的高度,在MeasureItem函数里会用此确定每一项的高度
    int m_nOffset;      // 绘制Icon与Text时,与边框的偏距
};


