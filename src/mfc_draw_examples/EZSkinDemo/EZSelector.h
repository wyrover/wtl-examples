// EZSelector.h: interface for the CEZSelector class.
//
//////////////////////////////////////////////////////////////////////

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

#if !defined(AFX_EZSELECTOR_H__76F2962C_1EEB_4DDA_BFB6_85D2B35EF5E5__INCLUDED_)
#define AFX_EZSELECTOR_H__76F2962C_1EEB_4DDA_BFB6_85D2B35EF5E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEZSelector  
{
public:
	CEZSelector(){}
	void Select(CDC* pDC, CGdiObject* pNew)
	{
		ASSERT(pDC);
		ASSERT(!pNew->IsKindOf(RUNTIME_CLASS(CRgn)));
		m_pDC = pDC;
		m_pOld = pDC->SelectObject(pNew);
		ASSERT(m_pOld);
		m_bSelect =TRUE;
	}
	void  Destruct()
	{

		if(m_pOld && m_pDC && m_bSelect)
			m_pDC->SelectObject(m_pOld);

	}
	CEZSelector(CDC* pDC, CGdiObject* pNew)
	: m_pOld(pDC->SelectObject(pNew))
	  ,m_pDC(pDC)
	  ,m_bSelect(FALSE)
	{
		ASSERT(m_pOld);
		ASSERT(!pNew->IsKindOf(RUNTIME_CLASS(CRgn)));
	}

	CEZSelector(CDC* pDC, int iStockObject)
	: m_pOld(pDC->SelectStockObject(iStockObject)),
	  m_pDC(pDC)
	  ,m_bSelect(FALSE)
	{
		ASSERT(m_pOld);
	}

	~CEZSelector()
	{
		
		if(m_pOld && m_pDC && !m_bSelect)
			m_pDC->SelectObject(m_pOld);
	}

private:
	CEZSelector(const CEZSelector&);
	CEZSelector& operator=(const CEZSelector&);

	// prevent region selection at compile-time
	CEZSelector(CDC* pDC, CRgn* pRgn);
	void Select(CDC* pDC, CRgn* pRgn);
	CGdiObject* m_pOld;
	CDC*		m_pDC;
	BOOL m_bSelect;

};

#endif // !defined(AFX_EZSELECTOR_H__76F2962C_1EEB_4DDA_BFB6_85D2B35EF5E5__INCLUDED_)
