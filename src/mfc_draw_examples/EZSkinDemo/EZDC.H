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

// EZDC.h: interface for the CEZMemDc,CEZMonoDC & CEZBmpDC classes.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EZDC_H__DF4DC305_A4E6_4117_BA4E_4698AA8FEEE1__INCLUDED_)
#define AFX_EZDC_H__DF4DC305_A4E6_4117_BA4E_4698AA8FEEE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//Based on probably the most distributed class - CMemDC
//Added and additional param to the constructor
//BOOL bCopyOnDestruct - "False" provides the user with a scratchpad DC

class CEZMemDC : public CDC
{
public:
	// constructor sets up the memory DC
	CEZMemDC(CDC* pDC, LPRECT pRect = NULL,BOOL bCopyOnDestruct = TRUE ,BOOL fCopyOld = FALSE) 
		: CDC(),m_pDC(pDC),m_bCopyOnDestruct(bCopyOnDestruct)
	{
		ASSERT(pDC != NULL);
		m_bMemDC = !pDC->IsPrinting();
		if (m_bMemDC) // Create a Memory DC
		{
			m_rect = pRect?*pRect:CEZClipRect(pDC);
			CreateCompatibleDC(pDC);
			m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
			m_pOldBitmap = (CBitmap*)SelectObject(&m_bitmap);
			SetWindowOrg(m_rect.left, m_rect.top);
			if(fCopyOld)
				BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
				m_pDC, m_rect.left, m_rect.top, SRCCOPY);
			
			
			
		}
		else  // Make a copy of the relevent parts of the current DC for printing
		{
			m_bPrinting = pDC->m_bPrinting;
			m_hDC = pDC->m_hDC;
			m_hAttribDC = pDC->m_hAttribDC;
		}
	}
	
	// Destructor copies the contents of the mem DC to the original DC
	~CEZMemDC()
	{
		if (m_bMemDC ) 
		{	 
			// Copy the offscreen bitmap onto the screen
			
			
			
			if(m_bCopyOnDestruct)
				m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
				this, m_rect.left, m_rect.top, SRCCOPY);
			
			
			SelectObject(m_pOldBitmap);
			
			
		} 
		else 
		{
			// All we need to do is replace the DC with an illegal value,
			// this keeps us from accidently deleting the handles associated with
			// the CDCthat was passed to the constructor.
			
			m_hDC = m_hAttribDC = NULL;
			
			
		}
		
	}
	
	// Allow usage as a pointer
	CEZMemDC* operator->() {return this;}
	
	// Allow usage as a pointer
	operator CEZMemDC*() {return this;}
	
private:
	CBitmap  m_bitmap;      // Offscreen bitmap
	CBitmap* m_pOldBitmap;
	CDC*     m_pDC;         // Saves CDCpassed in constructor
	CRect    m_rect;        // Rectangle of drawing area.
	BOOL     m_bMemDC;      // TRUE if CDCreally is a Memory DC.
	
	BOOL m_bCopyOnDestruct;
	
	
};


//A handy class for creating Transparent Bitmaps

class CEZMonoDC: public CDC
{
	
	
public:
	
	CEZMonoDC(CDC* pDCSrc,LPRECT pRect=NULL):CDC()
	{
		ASSERT(pDCSrc != NULL);
		CreateCompatibleDC(pDCSrc);
		
		m_rect = pRect?*pRect:CEZClipRect(pDCSrc);
		
		m_bitmap.CreateBitmap(m_rect.Width(),m_rect.Height(),1,1,NULL);
		
		pDCSrc->SetBkColor(pDCSrc->GetPixel(  0, 0 ) ) ;
		
		m_pOldBitmap =(CBitmap*)SelectObject(&m_bitmap);
		SetWindowOrg(m_rect.left, m_rect.top);
		
	}
	
	
	CEZMonoDC* operator->() {return this;}
	
	~CEZMonoDC()
	{
		ASSERT(this);
		ASSERT(m_hDC);
		SelectObject(m_pOldBitmap);
	}
	// Allow usage as a pointer
	operator CEZMonoDC*() {return this;}
	
	
private:
	CBitmap  m_bitmap;      // Monochrome bitmap
	CBitmap* m_pOldBitmap;
	CRect m_rect;	//Mask Rect
	
};


class CEZBmpDC : public CDC
{
public:
	// constructor sets up the memory DC
	CEZBmpDC(CDC* pDC, CBitmap* pBitmap) 
		: CDC()
	{
		ASSERT(pDC != NULL);
		
		ASSERT(pBitmap!=NULL);
		
		CreateCompatibleDC(pDC);
		m_pOldBitmap = (CBitmap*)SelectObject(pBitmap);
		
		
	}
	
	CEZBmpDC(CDC* pDC, CBitmap* pBitmap,CRect* rcDst,CRect* rcSrc) 
		: CDC()
	{
		ASSERT(pDC != NULL);
		
		ASSERT(pBitmap!=NULL);

		CRect rcDC,rcBmp;
		if(!rcSrc || rcSrc->IsRectEmpty()) 
		{
			BITMAP bm;
			pBitmap->GetBitmap(&bm);
			rcBmp = CRect(0,0,bm.bmWidth,bm.bmHeight);
		}
		
		if(!rcDst || rcDst->IsRectEmpty())
		{
			rcDst = rcSrc;
		}
		

		CEZBmpDC bmpDC(pDC,pBitmap);

		CreateCompatibleDC(pDC);
		m_bitmap.CreateCompatibleBitmap(pDC,rcDC.Width(),rcDC.Height());
		m_pOldBitmap = (CBitmap*)SelectObject(&m_bitmap);
		BitBlt(rcDC.left,rcDC.top,rcDC.Width(),rcDC.Height(),&bmpDC,rcBmp.left,rcBmp.top,SRCCOPY);
			
				
	}
	// Destructor copies the contents of the mem DC to the original DC
	~CEZBmpDC()
	{
		
		SelectObject(m_pOldBitmap);
		
		
	}
	
	// Allow usage as a pointer
	CEZBmpDC* operator->() {return this;}
	
	// Allow usage as a pointer
	operator CEZBmpDC*() {return this;}
	
private:
	CBitmap m_bitmap; //For the Second constructor
	CBitmap* m_pOldBitmap;
	
	
	
};

#endif