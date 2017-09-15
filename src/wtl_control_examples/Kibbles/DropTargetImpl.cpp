// DropTargetImpl.cpp: implementation of the CDropTargetImpl class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "kibbles.h"
#include "DropTargetImpl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction

CDropTargetImpl::CDropTargetImpl() : m_bAcceptDrop(false)
{
}

CDropTargetImpl::~CDropTargetImpl()
{
}

CDropTargetImpl* CDropTargetImpl::CreateMe(CDropHandler* pParent)
{
    CComObject<CDropTargetImpl>* pObj = NULL;

    if (FAILED(CComObject<CDropTargetImpl>::CreateInstance(&pObj)))
        return NULL;

    pObj->m_pParent = pParent;
    pObj->AddRef();
    return pObj;
}


//////////////////////////////////////////////////////////////////////
// IDropTarget

STDMETHODIMP CDropTargetImpl::DragEnter(
    IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
    if (NULL == pDataObj || NULL == *pdwEffect)
        return E_POINTER;

    if (!(*pdwEffect & (DROPEFFECT_LINK | DROPEFFECT_COPY)))
        return E_INVALIDARG;

    m_dwEffect = DROPEFFECT_NONE;
    m_bAcceptDrop = ReadURLFromDataObject(pDataObj);

    if (m_bAcceptDrop) {
        if (*pdwEffect & DROPEFFECT_LINK)
            m_dwEffect = DROPEFFECT_LINK;
        else if (*pdwEffect & DROPEFFECT_COPY)
            m_dwEffect = DROPEFFECT_COPY;
    }

    *pdwEffect = m_dwEffect;
    return S_OK;
}

STDMETHODIMP CDropTargetImpl::DragOver(
    DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
    if (NULL == *pdwEffect)
        return E_POINTER;

    *pdwEffect = m_dwEffect;
    return S_OK;
}

STDMETHODIMP CDropTargetImpl::DragLeave()
{
    return S_OK;
}

STDMETHODIMP CDropTargetImpl::Drop(
    IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
    HRESULT hr;

    if (NULL == pDataObj || NULL == *pdwEffect)
        return E_POINTER;

    *pdwEffect = DROPEFFECT_NONE;
    hr = m_pParent->OnDrop(m_sURLToDownload);

    if (SUCCEEDED(hr))
        *pdwEffect = m_dwEffect;

    return SUCCEEDED(hr) ? S_OK : E_FAIL;
}


//////////////////////////////////////////////////////////////////////
// Other methods

bool CDropTargetImpl::ReadURLFromDataObject(IDataObject* pDataObj)
{
    CComPtr<IEnumFORMATETC> pEnum;
    HRESULT hr;
    m_sURLToDownload.Empty();

    if (FAILED(pDataObj->EnumFormatEtc(DATADIR_GET, &pEnum)))
        return false;

    for (;;) {
        ULONG cFetched = 0;
        FORMATETC etc = {0};
        TCHAR szFormatName[128];
        int nRet;
        hr = pEnum->Next(1, &etc, &cFetched);

        if (S_OK != hr)
            break;

        nRet = GetClipboardFormatName(etc.cfFormat, szFormatName,
                                      countof(szFormatName));

        if (0 == nRet)
            continue;

        if (0 != lstrcmp(szFormatName, _T("UniformResourceLocator")))
            continue;

        hr = pDataObj->QueryGetData(&etc);

        if (FAILED(hr))
            continue;

        STGMEDIUM stg = {0};
        stg.tymed = etc.tymed;
        hr = pDataObj->GetData(&etc, &stg);

        if (FAILED(hr))
            continue;

        if (TYMED_HGLOBAL == stg.tymed) {
            void* pvData = GlobalLock(stg.hGlobal);

            if (NULL != pvData) {
                m_sURLToDownload = (LPCSTR) pvData;
                GlobalUnlock(stg.hGlobal);
            }
        }

        ReleaseStgMedium(&stg);

        if (!m_sURLToDownload.IsEmpty())
            return true;
    }

    return false;
}
