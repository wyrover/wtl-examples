//----------------------------------------------------------------------------------------//
/******************************************************************************************
V. Lakshmi Narasimhan,ezlux@yahoo.com
This Code is a Part of the EZSkin Framework.

Feel free to use ,modify,twist,turn,digest or anything u want to do.
However if u find this code useful enough to be used in your great
commercial application an e-mail would be appreciated!

This code is provided "as is" without any warranty -express or implied
blah. blah.. blah...
********************************************************************************************/
//------------------------------------------------------------------------------------------//
#if !defined(AFX_EZDIALOG_H__16ED9519_B0E0_44D0_99CA_621B3F8A73C1__INCLUDED_)
#define AFX_EZDIALOG_H__16ED9519_B0E0_44D0_99CA_621B3F8A73C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EZDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEZDialog dialog

#include "EZDialogSkin.h"
#include "EZCaption.h"
#include "EZBorder.h"
class CEZDialog : public CDialog
{
// Construction
public:
	
	CEZDialog();
	CEZDialog(UINT uResource,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEZDialog)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEZDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


	// Generated message map functions
	//{{AFX_MSG(CEZDialog)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	virtual BOOL OnInitDialog();
		//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
		void Init();
protected:

	CBrush m_brushHollow;
	CEZCaption m_Caption;
	CEZBorder m_Border;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EZDIALOG_H__16ED9519_B0E0_44D0_99CA_621B3F8A73C1__INCLUDED_)
