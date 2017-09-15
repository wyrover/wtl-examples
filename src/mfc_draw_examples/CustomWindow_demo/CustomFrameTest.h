#pragma once

#include "CustomWindowFrm.h"
// CCustomFrameTest frame

class CCustomFrameTest : public CCustomFrame
{
	DECLARE_DYNCREATE(CCustomFrameTest)
public:
	CCustomFrameTest();           // protected constructor used by dynamic creation
	virtual ~CCustomFrameTest();
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};


