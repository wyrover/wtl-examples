// KibblesView.cpp : implementation of the CKibblesView class
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "kibbles.h"
#include "KibblesView.h"
#include "MyDialogs.h"
#include "JobRunningDlg.h"
#include "DownloadFileDlg.h"
#include "ChooseColorsDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction

CKibblesView::CKibblesView() :
    m_bPolling(false), m_pDropTarget(NULL),
    m_crDownloadedPartPen(g_crDownloadedPartPenDefault),
    m_crRemainingPartPen(g_crRemainingPartPenDefault),
    m_crRemainingPartBrush(g_crRemainingPartFillDefault),
    m_crText(g_crTextDefault), m_crBkgnd(g_crBkgndDefault)
{
    TCHAR szMyDocsDir[MAX_PATH];
    SHGetSpecialFolderPath(*this, szMyDocsDir, CSIDL_PERSONAL, true);
    PathAddBackslash(szMyDocsDir);
    m_sDownloadDir = szMyDocsDir;
}


//////////////////////////////////////////////////////////////////////
// Message handlers

BOOL CKibblesView::PreTranslateMessage(MSG* pMsg)
{
    pMsg;
    return FALSE;
}

LRESULT CKibblesView::OnCreate(LPCREATESTRUCT lpcs)
{
    HRESULT hr;
    // You must specify CLSCTX_LOCAL_SERVER as the context since the BITS manager
    // runs as a service (out-of-proc).
    hr = m_pBits.CoCreateInstance(CLSID_BackgroundCopyManager, NULL,
                                  CLSCTX_LOCAL_SERVER);

    if (FAILED(hr)) {
        CString sMsg;
        sMsg.Format(IDS_COCREATE_BITS_FAILED, _E(hr));
        MsgBox((LPCTSTR) sMsg);
        return -1;
    }

    m_pDropTarget = CDropTargetImpl::CreateMe(this);

    if (NULL == m_pDropTarget) {
        MsgBox(IDS_CREATE_DROPTARGET_FAILED, MB_ICONWARNING);
    } else {
        hr = RegisterDragDrop(*this, m_pDropTarget);

        if (FAILED(hr)) {
            CString sMsg;
            m_pDropTarget->Release();
            m_pDropTarget = NULL;
            sMsg.Format(IDS_REGISTER_DRAGDROP_FAILED, _E(hr));
            MsgBox((LPCTSTR) sMsg, MB_ICONWARNING);
        }
    }

    // Create GDI objects w/the initial colors.
    CreateGDIObjects();
    // Create a font to use when drawing the job status info. Normally you
    // would use AtlGetDefaultGuiFont(), however on English, that returns
    // MS Sans Serif instead of Tahoma. Sans Serif is UGLY so I do it this
    // way instead. If SystemParametersInfo() fails (not likely),
    // then the drawing code will fall back to using the font returned by
    // AtlGetDefaultGuiFont().
    NONCLIENTMETRICS ncm = { sizeof(NONCLIENTMETRICS) };

    if (SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &ncm, false))
        m_font.CreateFontIndirect(&ncm.lfMessageFont);

    if (m_font.IsNull()) {
        LOGFONT lf = {0};
        CFontHandle(AtlGetDefaultGuiFont()).GetLogFont(lf);
        m_font.CreateFontIndirect(&lf);
    }

    return 0;
}

void CKibblesView::OnDestroy()
{
    if (m_bPolling) {
        KillTimer(m_timerID);
        m_bPolling = false;
    }

    if (NULL != m_pDropTarget) {
        RevokeDragDrop(*this);
        m_pDropTarget->Release();
        m_pDropTarget = NULL;
    }
}

BOOL CKibblesView::OnEraseBkgnd(CDCHandle dc)
{
    return TRUE;    // we'll do all painting in OnPaint()
}

void CKibblesView::OnPaint(CDCHandle /*unused*/)
{
    static const double pi = acos(-1.0);
    CPaintDC dc(*this);
    CDC dcMem;
    CBitmap bmpMem;
    CRect rcWnd, rcText, rcPie;
    CString s = GetJobProgressDescripton();
    GetClientRect(rcWnd);
    rcText = rcWnd;
    rcPie = rcWnd;
    dcMem.CreateCompatibleDC(dc);
    bmpMem.CreateCompatibleBitmap(dc, rcWnd.Width(), rcWnd.Height());
    CSaveDC sdc1(dc), sdc2(dcMem);
    dcMem.SelectBitmap(bmpMem);
    dcMem.SetBkMode(OPAQUE);
    dcMem.SetTextColor(m_crText);
    dcMem.SetBkColor(m_crBkgnd);
    dcMem.SelectFont(m_font);
    // Fill in the background.
    dcMem.FillSolidRect(rcWnd, m_crBkgnd);
    // Find the RECT needed to hold the status text
    dcMem.DrawText(s, -1, rcText, DT_CALCRECT | DT_NOPREFIX);
    rcPie.top = rcText.bottom;
    // Draw the text.
    dcMem.DrawText(s, -1, rcText, DT_NOPREFIX);

    // Calc the square region where we'll draw the pie chart
    if (rcPie.Width() > rcPie.Height()) {
        long lDiff = rcPie.Width() - rcPie.Height();
        rcPie.left += lDiff / 2;
        rcPie.right -= lDiff / 2;
    } else if (rcPie.Height() > rcPie.Width()) {
        long lDiff = rcPie.Height() - rcPie.Width();
        rcPie.top += lDiff / 2;
        rcPie.bottom -= lDiff / 2;
    }

    rcPie.DeflateRect(10, 10);
    // Calc the endpoint of the radian that separates the two pie parts.
    CPoint ptStart(rcPie.right, rcPie.CenterPoint().y);
    CPoint ptEnd(rcPie.right, rcPie.CenterPoint().y);
    double dPercentDone = GetJobDownloadProgress();

    // 0% and 100% just use ptStart==ptEnd.
    if (dPercentDone != 0 && dPercentDone != 100) {
        double dRadians = dPercentDone / 100.0 * 2.0 * pi;
        double dPieRadius = rcPie.Width() / 2.0;
        double x = dPieRadius * cos(dRadians);
        double y = dPieRadius * -sin(dRadians);     // negate because positive Y axis is down
        ptEnd.x = rcPie.CenterPoint().x + (long) x;
        ptEnd.y = rcPie.CenterPoint().y + (long) y;
    }

    // Draw the pie piece for the completed part of the download.
    // If the percentage is really small, the start and end points can be
    // equal, which would result in the entire pie being drawn in both
    // sets of colors.  If that's the case, don't draw this part of the pie.
    if (dPercentDone > 0 && (dPercentDone == 100 || ptStart != ptEnd)) {
        // Select a colored pen and a null brush into the DC, this will make the
        // pie piece outlined, but the interior won't be changed.
        dcMem.SelectPen(m_penDownloadedPart);
        dcMem.SelectStockBrush(NULL_BRUSH);
        // Draw the pie piece in a path.
        dcMem.BeginPath();
        dcMem.Pie(rcPie, ptStart, ptEnd);
        dcMem.EndPath();
        // Clip the DC to this path, meaning all drawing between now and AbortPath()
        // will be clipped to the pie piece.
        dcMem.SelectClipPath(RGN_COPY);
        // Fill the interior of the pie piece with a red-blue gradient.
        TRIVERTEX atv[] = {
            { rcPie.right, rcPie.top, 0xff00, 0, 0 },    // 0 top right (red)
            { rcPie.left, rcPie.top, 0, 0, 0x8000 },     // 1 top left (dark blue)
            { rcPie.right, rcPie.bottom, 0, 0, 0x8000 }, // 2 bottom right (dark blue)
            { rcPie.left, rcPie.bottom, 0, 0, 0xff00 }   // 3 bottom left (blue)
        };
        GRADIENT_TRIANGLE agt[] = {
            { 1, 0, 2 },    // triangle 1 (top right)
            { 1, 3, 2 }     // triangle 2 (bottom left)
        };
        dcMem.GradientFill(atv, countof(atv), agt, countof(agt), GRADIENT_FILL_TRIANGLE);

        // Draw a bitmap in the interior of the pie piece.
        if (m_bmpRemainingPart) {
            CDC dcMem2;
            dcMem2.CreateCompatibleDC(dc);
            CSaveDC sdc3(dcMem2);
            dcMem2.SelectBitmap(m_bmpRemainingPart);
            dcMem.BitBlt(rcPie.CenterPoint().x - m_szRemainingBmpSize.cx / 2,
                         rcPie.CenterPoint().y - m_szRemainingBmpSize.cy / 2,
                         m_szRemainingBmpSize.cx, m_szRemainingBmpSize.cy,
                         dcMem2, 0, 0, SRCCOPY);
        }

        // Undo the clipping.
        dcMem.SelectClipRgn(NULL);
        dcMem.AbortPath();
        // Call Pie() again to re-draw the outline of the pie piece.
        dcMem.Pie(rcPie, ptStart, ptEnd);
    }

    // Draw the pie piece for the remaining part of the download.
    if (dPercentDone < 100) {
        dcMem.SelectPen(m_penRemainingPart);
        dcMem.SelectBrush(m_brushRemainingPart);
        dcMem.Pie(rcPie, ptEnd, ptStart);
    }

    // Blit the contents back to the screen.
    dc.BitBlt(0, 0, rcWnd.Width(), rcWnd.Height(), dcMem, 0, 0, SRCCOPY);
}

void CKibblesView::OnTimer(UINT id)
{
    if (id != m_timerID) {
        SetMsgHandled(false);
        return;
    }

    // We should only get here if we have a BITS job running.
    ATLASSERT(m_pJob);
    // If the job is in the transferred state, complete it. If it's in the
    // acknowledged state, we can stop polling.
    BG_JOB_STATE state;
    HRESULT hr;
    hr = m_pJob->GetState(&state);

    if (SUCCEEDED(hr)) {
        if (BG_JOB_STATE_TRANSFERRED == state) {
            hr = m_pJob->Complete();

            if (FAILED(hr))
                ATLTRACE(_T("Warning: Complete() failed in OnTimer(): %s\n"), _E(hr));
        } else if (BG_JOB_STATE_ACKNOWLEDGED == state) {
            KillTimer(m_timerID);
            m_bPolling = false;
        }
    } else
        ATLTRACE(_T("Warning: GetState() failed in OnTimer(): %s\n"), _E(hr));

    Invalidate();
}


//////////////////////////////////////////////////////////////////////
// Command handlers

void CKibblesView::OnSetDownloadDir(UINT uCode, int nID, HWND hwndCtrl)
{
    CMyFolderDialog fd(GetTopLevelParent(), IDS_SELECT_DOWNLOAD_DIR,
                       BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);
    fd.m_sInitialDir = m_sDownloadDir;

    if (IDOK == fd.DoModal()) {
        LPTSTR p = NULL;
        m_sDownloadDir = fd.GetFolderPath();
        p = m_sDownloadDir.GetBuffer(MAX_PATH);
        PathAddBackslash(p);
        m_sDownloadDir.ReleaseBuffer();
    }
}

void CKibblesView::OnAddFile(UINT uCode, int nID, HWND hwndCtrl)
{
    CDownloadFileDlg dlg;
    dlg.m_sLocalFilename = m_sDownloadDir;

    if (IDOK == dlg.DoModal(GetTopLevelParent()))
        if (!AddFileToJob(dlg.m_sURL, dlg.m_sLocalFilename))
            AtlMessageBox(GetTopLevelParent(), IDS_ADD_FILE_FAILED);
}

void CKibblesView::OnChangeColors(UINT uCode, int nID, HWND hwndCtrl)
{
    CChooseColorsDlg dlg;
    dlg.m_crText = m_crText;
    dlg.m_crBkgnd = m_crBkgnd;
    dlg.m_crDownloadedOutline = m_crDownloadedPartPen;
    dlg.m_crRemainingOutline = m_crRemainingPartPen;
    dlg.m_crRemainingFill = m_crRemainingPartBrush;

    if (IDOK == dlg.DoModal(GetTopLevelParent())) {
        m_crText = dlg.m_crText;
        m_crBkgnd = dlg.m_crBkgnd;
        m_crDownloadedPartPen = dlg.m_crDownloadedOutline;
        m_crRemainingPartPen = dlg.m_crRemainingOutline;
        m_crRemainingPartBrush = dlg.m_crRemainingFill;
        CreateGDIObjects();
        RedrawWindow();
    }
}

void CKibblesView::OnRandomizeColors(UINT uCode, int nID, HWND hwndCtrl)
{
    m_crBkgnd = RandomRGB();
    m_crText = RandomRGB();
    m_crDownloadedPartPen = RandomRGB();
    m_crRemainingPartBrush = RandomRGB();
    m_crRemainingPartPen = RandomRGB();
    CreateGDIObjects();
    RedrawWindow();
}


//////////////////////////////////////////////////////////////////////
// Drop handler

HRESULT CKibblesView::OnDrop(LPCTSTR szDroppedURL)
{
    if (!AddFileToJob(szDroppedURL))
        AtlMessageBox(GetTopLevelParent(), IDS_ADD_FILE_FAILED);

    return S_OK;
}


//////////////////////////////////////////////////////////////////////
// Operations

void CKibblesView::SetNoBackgroundPicture()
{
    if (m_bmpRemainingPart) {
        m_bmpRemainingPart.DeleteObject();
        RedrawWindow();
    }
}

void CKibblesView::SetBackgroundPicture(LPCTSTR szFilename)
{
    if (m_bmpRemainingPart)
        m_bmpRemainingPart.DeleteObject();

    m_bmpRemainingPart = AtlLoadBitmapImage(szFilename, LR_LOADFROMFILE);

    if (m_bmpRemainingPart)
        m_bmpRemainingPart.GetSize(m_szRemainingBmpSize);

    RedrawWindow();
}

void CKibblesView::UseDefaultBackgroundPicture()
{
    if (m_bmpRemainingPart)
        m_bmpRemainingPart.DeleteObject();

    m_bmpRemainingPart.LoadBitmap(IDB_BKGND_DUCK);

    if (m_bmpRemainingPart)
        m_bmpRemainingPart.GetSize(m_szRemainingBmpSize);

    RedrawWindow();
}

bool CKibblesView::AllowClose()
{
    bool bRet = true;

    // If we have a job running that's not completed, see if the user
    // wants to cancel it, stop it, or let it run.
    if (m_pJob && m_bPolling) {
        CJobRunningDlg dlg;
        HRESULT hr;

        if (IDOK != dlg.DoModal())
            bRet = false;
        else {
            ATLASSERT(m_pJob);

            if (CJobRunningDlg::complete == dlg.m_nChoice) {
                hr = m_pJob->Complete();

                if (FAILED(hr)) {
                    CString sMsg;
                    sMsg.Format(IDS_COMPLETE_JOB_ERROR, _E(hr));
                    MsgBox((LPCTSTR) sMsg);
                }
            } else if (CJobRunningDlg::cancel == dlg.m_nChoice) {
                hr = m_pJob->Cancel();

                if (FAILED(hr))
                    ATLTRACE(_T("Warning: Cancel() failed in AllowClose(): %s\n"), _E(hr));
            }
        }
    }

    return bRet;
}


//////////////////////////////////////////////////////////////////////
// Other methods

void CKibblesView::CreateGDIObjects()
{
    if (m_penDownloadedPart)
        m_penDownloadedPart.DeleteObject();

    if (m_penRemainingPart)
        m_penRemainingPart.DeleteObject();

    if (m_brushRemainingPart)
        m_brushRemainingPart.DeleteObject();

    if (!m_bmpRemainingPart) {
        m_bmpRemainingPart.LoadBitmap(IDB_BKGND_DUCK);

        if (m_bmpRemainingPart)
            m_bmpRemainingPart.GetSize(m_szRemainingBmpSize);
    }

    m_penDownloadedPart.CreatePen(PS_SOLID, 7, m_crDownloadedPartPen);
    m_penRemainingPart.CreatePen(PS_SOLID, 1, m_crRemainingPartPen);
    m_brushRemainingPart.CreateHatchBrush(HS_DIAGCROSS, m_crRemainingPartBrush);
}

bool CKibblesView::AddFileToJob(LPCTSTR szURL)
{
    CString sLocalName;
    CUrlComponents url;

    // Get the filename part from the URL.
    if (!InternetCrackUrl(szURL, 0, 0, &url)) {
        ATLTRACE("Error: InternetCrackUrl() failed in AddFileToJob(): %s\n", _E2());
        return false;
    }

    // Build the path to the local file.
    sLocalName = m_sDownloadDir;
    sLocalName += PathFindFileName(url.szUrlPath);
    // Add it to the job
    return AddFileToJob(szURL, sLocalName);
}

bool CKibblesView::AddFileToJob(LPCTSTR szURL, LPCTSTR szLocalFilename)
{
    HRESULT hr;

    // If there is a current job, is it finished? If so, release our itf on it.
    if (m_pJob && !m_bPolling)
        m_pJob.Release();

    // Create a new BITS job if there isn't a running job already.
    if (!m_pJob) {
        CString sJobName;
        sJobName.Format(_T("Kibbles_%u"), GetTickCount());
        hr = m_pBits->CreateJob(sJobName, BG_JOB_TYPE_DOWNLOAD,
                                &m_jobGuid, &m_pJob);

        if (FAILED(hr)) {
            CString sMsg;
            sMsg.Format(IDS_CREATE_JOB_ERROR, _E(hr));
            MsgBox((LPCTSTR) sMsg);
            return false;
        }

        // If you use an HTTP proxy that doesn't support HTTP 1.1, you need
        // this call so that BITS doesn't use that proxy.
        hr = m_pJob->SetProxySettings(BG_JOB_PROXY_USAGE_NO_PROXY, NULL, NULL);

        if (FAILED(hr))
            ATLTRACE(_T("Warning: SetProxySettings() failed in AddFileToJob(): %s\n"), _E(hr));
    }

    // Add this file to the BITS job.
    hr = m_pJob->AddFile(szURL, szLocalFilename);

    if (FAILED(hr)) {
        CString sMsg;
        sMsg.Format(IDS_ADD_FILE_ERROR, _E(hr));
        MessageBox(sMsg);
        return false;
    }

    // If the job isn't running, start it.
    BG_JOB_STATE state;
    hr = m_pJob->GetState(&state);

    if (SUCCEEDED(hr)) {
        switch (state) {
        case BG_JOB_STATE_SUSPENDED:
        case BG_JOB_STATE_ERROR:
        case BG_JOB_STATE_TRANSIENT_ERROR:
            hr = m_pJob->Resume();

            if (FAILED(hr)) {
                CString sMsg;
                sMsg.Format(IDS_RESUME_JOB_ERROR, _E(hr));
                MsgBox((LPCTSTR) sMsg);
            } else if (!m_bPolling) {
                SetTimer(m_timerID, m_timerInterval);
                m_bPolling = true;
            }

            break;
        }
    } else {
        CString sMsg;
        sMsg.Format(IDS_GET_STATE_ERROR, _E(hr));
        MsgBox((LPCTSTR) sMsg, MB_ICONWARNING);
    }

    return true;
}

double CKibblesView::GetJobDownloadProgress() const
{
    HRESULT hr;
    double dRet = 0;

    if (!m_pJob)
        return 0;

    // Read the download progress
    BG_JOB_PROGRESS rProgress = {0};
    hr = m_pJob->GetProgress(&rProgress);

    if (SUCCEEDED(hr)) {
        // Special-case the cases of unknown total size, 0%, and 100%,
        // so we can return an exact percentage.
        if (0 != rProgress.BytesTransferred &&
            BG_SIZE_UNKNOWN != rProgress.BytesTotal) {
            if (rProgress.BytesTransferred == rProgress.BytesTotal)
                dRet = 100;
            else
                dRet = (100.0 * (__int64) rProgress.BytesTransferred) / (__int64) rProgress.BytesTotal;
        }
    } else
        ATLTRACE(_T("Warning: GetProgress() failed in GetJobDownloadProgress(): %s\n"), _E(hr));

    return dRet;
}

CString CKibblesView::GetJobProgressDescripton() const
{
    HRESULT hr;
    CString sDescription;

    // If we don't have a running BITS job, return a simple message with instructions.
    if (!m_pJob)
        return CString(LPCTSTR(IDS_NOJOB_MESSAGE));

    // Read the job state
    BG_JOB_STATE state;
    hr = m_pJob->GetState(&state);

    if (SUCCEEDED(hr)) {
        CString s;
        s.Format(IDS_JOB_STATE_DESC, JobStateToString(state));
        sDescription += s;
    }

    // Read the download progress
    BG_JOB_PROGRESS rProgress = {0};
    hr = m_pJob->GetProgress(&rProgress);

    if (SUCCEEDED(hr)) {
        CString sTotalBytes, sPct, sMsg;

        if (BG_SIZE_UNKNOWN == rProgress.BytesTotal) {
            sTotalBytes.LoadString(IDS_FILESIZE_UNKNOWN);
            sPct = _T("0");
        } else {
            sTotalBytes.Format(_T("%I64u"), rProgress.BytesTotal);

            if (0 == rProgress.BytesTotal)
                sPct = _T("0");
            else
                sPct.Format(_T("%ld"),
                            long((100U * rProgress.BytesTransferred) / rProgress.BytesTotal));
        }

        sMsg.Format(IDS_AMT_DOWNLOADED_DESC,
                    rProgress.FilesTransferred, rProgress.FilesTotal,
                    rProgress.BytesTransferred, (LPCTSTR) sTotalBytes,
                    (LPCTSTR) sPct);
        sDescription += sMsg;
    }

    return sDescription;
}

void CKibblesView::MsgBox(_U_STRINGorID szMessage, UINT uFlags, HWND hwndParent)
{
    if (NULL == hwndParent && ::IsWindowVisible(GetTopLevelParent()))
        hwndParent = GetTopLevelParent();

    AtlMessageBox(hwndParent, szMessage, IDS_MSGBOX_TITLE, uFlags);
}
