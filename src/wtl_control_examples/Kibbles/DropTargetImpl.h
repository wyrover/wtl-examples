// DropTargetImpl.h: interface for the CDropTargetImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DROPTARGETIMPL_H__63ECAF10_389A_4B99_A7F0_E92E8EE9DDCD__INCLUDED_)
#define AFX_DROPTARGETIMPL_H__63ECAF10_389A_4B99_A7F0_E92E8EE9DDCD__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

class CDropHandler
{
public:
    virtual HRESULT OnDrop(LPCTSTR szDroppedURL) = 0;
};

class CDropTargetImpl : public CComObjectRootEx<CComObjectThreadModel>,
    public CComCoClass<CDropTargetImpl>,
    public IDropTarget
{
public:
    // Construction/destruction
    static CDropTargetImpl* CreateMe(CDropHandler* pParent);
    ~CDropTargetImpl();

    // Maps
    BEGIN_COM_MAP(CDropTargetImpl)
    COM_INTERFACE_ENTRY(IDropTarget)
    END_COM_MAP()

    // IDropTarget methods
    STDMETHODIMP DragEnter(IDataObject* pDataObj,
                           DWORD grfKeyState, POINTL pt,
                           DWORD* pdwEffect);

    STDMETHODIMP DragOver(DWORD grfKeyState, POINTL pt,
                          DWORD* pdwEffect);

    STDMETHODIMP DragLeave();

    STDMETHODIMP Drop(IDataObject* pDataObj, DWORD grfKeyState,
                      POINTL pt, DWORD* pdwEffect);

protected:
    // Protected ctor, create with CreateMe().
    CDropTargetImpl();

    bool ReadURLFromDataObject(IDataObject* pDataObj);

    CString m_sURLToDownload;
    bool m_bAcceptDrop;
    DWORD m_dwEffect;

    CDropHandler* m_pParent;
};

#endif // !defined(AFX_DROPTARGETIMPL_H__63ECAF10_389A_4B99_A7F0_E92E8EE9DDCD__INCLUDED_)
