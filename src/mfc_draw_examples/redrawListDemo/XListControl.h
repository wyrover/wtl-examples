#pragma once
#include "SkinHeaderCtrl.h"

// CPatientListCtrl

class CXListControl: public CListCtrl
{
    DECLARE_DYNAMIC(CXListControl)

public:
    CXListControl();
    virtual ~CXListControl();

protected:
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()

    CSkinHeaderCtrl m_SkinHeaderCtrl;
    virtual void PreSubclassWindow();
};


