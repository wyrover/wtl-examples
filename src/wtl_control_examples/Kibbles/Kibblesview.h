// KibblesView.h : interface of the CKibblesView class
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_KIBBLESVIEW_H__B1D286A8_E04D_4167_87E3_382192BBCEF0__INCLUDED_)
#define AFX_KIBBLESVIEW_H__B1D286A8_E04D_4167_87E3_382192BBCEF0__INCLUDED_

#if _MSC_VER >= 1000
    #pragma once
#endif // _MSC_VER >= 1000

#include "DropTargetImpl.h"

class CKibblesView : public CWindowImpl<CKibblesView>,
    public CDropHandler
{
public:
    DECLARE_WND_CLASS(NULL)

    // Construction
    CKibblesView();

    // Maps
    BEGIN_MSG_MAP(CKibblesView)
    MSG_WM_CREATE(OnCreate)
    MSG_WM_DESTROY(OnDestroy)
    MSG_WM_ERASEBKGND(OnEraseBkgnd)
    MSG_WM_PAINT(OnPaint)
    MSG_WM_TIMER(OnTimer)
    COMMAND_ID_HANDLER_EX(IDC_SET_DOWNLOAD_DIR, OnSetDownloadDir)
    COMMAND_ID_HANDLER_EX(IDC_ADD_FILE, OnAddFile)
    COMMAND_ID_HANDLER_EX(IDC_CHANGE_COLORS, OnChangeColors)
    COMMAND_ID_HANDLER_EX(IDC_RANDOMIZE_COLORS, OnRandomizeColors)
    END_MSG_MAP()

    // Message handlers
    BOOL    PreTranslateMessage(MSG* pMsg);

    LRESULT OnCreate(LPCREATESTRUCT lpcs);
    void    OnDestroy();
    BOOL    OnEraseBkgnd(CDCHandle dc);
    void    OnPaint(CDCHandle /*unused*/);
    void    OnTimer(UINT id);

    // Command handlers
    void OnSetDownloadDir(UINT uCode, int nID, HWND hwndCtrl);
    void OnAddFile(UINT uCode, int nID, HWND hwndCtrl);
    void OnChangeColors(UINT uCode, int nID, HWND hwndCtrl);
    void OnRandomizeColors(UINT uCode, int nID, HWND hwndCtrl);

    // Drop handler
    HRESULT OnDrop(LPCTSTR szDroppedURL);

    // Operations
    void SetNoBackgroundPicture();
    void UseDefaultBackgroundPicture();
    void SetBackgroundPicture(LPCTSTR szFilename);
    bool AllowClose();

protected:
    // BITS and job info
    CComPtr<IBackgroundCopyManager> m_pBits;
    CComPtr<IBackgroundCopyJob> m_pJob;
    GUID m_jobGuid;

    // GDI objects for drawing
    CPen    m_penDownloadedPart, m_penRemainingPart;
    CBrush  m_brushRemainingPart;
    CBitmap m_bmpRemainingPart;
    CSize   m_szRemainingBmpSize;
    CFont   m_font;

    COLORREF m_crDownloadedPartPen, m_crRemainingPartPen,
             m_crRemainingPartBrush, m_crText, m_crBkgnd;

    // State info
    bool    m_bPolling;
    CString m_sDownloadDir;

    // Drop target impl
    CDropTargetImpl* m_pDropTarget;

    // Other methods
    void CreateGDIObjects();
    bool AddFileToJob(LPCTSTR szURL);
    bool AddFileToJob(LPCTSTR szURL, LPCTSTR szLocalFilename);

    CString GetJobProgressDescripton() const;
    double GetJobDownloadProgress() const;

    void MsgBox(_U_STRINGorID szMessage, UINT uFlags = MB_ICONERROR,
                HWND hwndParent = NULL);

private:
    enum { m_timerID = 37, m_timerInterval = 250 };

    static COLORREF RandomRGB()
    {
        return RGB(rand() & 0xFF, rand() & 0xFF, rand() & 0xFF);
    }
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KIBBLESVIEW_H__B1D286A8_E04D_4167_87E3_382192BBCEF0__INCLUDED_)
