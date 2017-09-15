// EZDib.h: interface for the CEZDib class.
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
//Based on several DIB classes 
//Paul DiLascia in periodicals 97
//Chris Becke's GDI Tutors at Code Project
//Jörg König 's CDIBitmap class

#if !defined(AFX_EZBITMAP_H__709D1929_D862_45DB_B914_DF5CDD0A4136__INCLUDED_)
#define AFX_EZBITMAP_H__709D1929_D862_45DB_B914_DF5CDD0A4136__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SRCNOTAND  0x00220326
class CEZDib : public CBitmap  
{

DECLARE_DYNCREATE(CEZDib)
public:
	
	friend class CEZDibPalette;
	CEZDib();
	CEZDib(CString strPath,int nType= BMP_TILE);
	CEZDib(UINT nIDResource,int nType = BMP_TILE);

	
	
	enum 
	{
		BMP_NORMAL	=0,
		BMP_TILE,
		BMP_STRETCH

	};
private:

	int m_nType;
	
	BITMAPINFO *	m_pInfo;
	BYTE *			m_pPixels;
	CEZDibPalette*	m_pPal;
	BOOL			m_bIsPadded;

	
	
private:
	CEZDib( const CEZDib& bmp );
	
public:		// attributes
	BITMAPINFO *	GetHeaderPtr() const;
	BYTE *			GetPixelPtr() const;
	RGBQUAD *		GetColorTablePtr() const;
	int				GetWidth() const;
	int				GetHeight() const;
	CSize			GetBitmapSize()const{return CSize(GetWidth(),GetHeight());}	
	CEZDibPalette*	GetPalette() const { return m_pPal; }
	const int GetType() const{return m_nType;}
	void SetType(const int nType){m_nType = nType;}

	
public:		// operations
	BOOL			CreatePalette();	// auto. made by "Load()" and "CreateFromBitmap()"
	void			ClearPalette();		// destroy the palette associated with this image
	BOOL			CreateFromBitmap( CDC *, CBitmap * );
	virtual BOOL	Save( const CString & strFile);
	BOOL			Load(UINT ID){return LoadBitmap(MAKEINTRESOURCE(ID));} 
	BOOL			LoadBitmap(UINT ID) { return LoadBitmap(MAKEINTRESOURCE(ID)); }
	BOOL			LoadBitmap(LPCTSTR ID); 
	void			DestroyBitmap();
	BOOL			DeleteObject() { DestroyBitmap(); return TRUE; }
	
public:		// overridables
		// draw parts of the dib into a given area of the DC
	virtual BOOL Draw ( CDC * pDC, const CRect&  rectDC=CRect(0,0,0,0), const CRect & rectDIB=CRect(0,0,0,0) ) const;
	virtual BOOL Draw (CDC& dc,LPRECT prectDC=NULL,LPRECT prectImg=NULL)const
	{
		CRect rcDC = prectDC?*prectDC:CRect(0,0,0,0);
		CRect rcImg = prectImg?*prectImg:CRect(0,0,0,0);


		return Draw(&dc,rcDC,rcImg);
	}

	BOOL DrawTransparent(CDC* pDC,COLORREF clrTrans,const CRect& rcDest = CRect(0,0,0,0),const CRect& rcSrc = CRect(0,0,0,0)) const;
	
	// load a bitmap from disk
	
	virtual BOOL	Load( const CString & strFile);
	


	// save the bitmap to disk
	
	
protected:
	
	virtual BOOL	Load( CFile * pFile );
	virtual BOOL	Save( CFile * pFile );

	virtual void DrawTiled ( CDC* pDC, CRect& rectDC, CRect& rectDIB) const;
	virtual void DrawStretched ( CDC* pDC, CRect& rectDC,CRect& rectImage) const;
	virtual void DrawNormal ( CDC * pDC, CRect & rectDC, CRect & rectDIB ) const;

	int				GetPalEntries() const;
	int				GetPalEntries( BITMAPINFOHEADER& infoHeader ) const;
	DWORD			GetBitsPerPixel() const;
	DWORD			LastByte( DWORD BitsPerPixel, DWORD PixelCount ) const;
	DWORD			GetBytesPerLine( DWORD BitsPerPixel, DWORD Width ) const;
	BOOL			PadBits();
	BOOL			UnPadBits();
	WORD			GetColorCount() const;
public:
	HBITMAP Detach();
	BOOL Attach(HBITMAP hBitmap);
	virtual ~CEZDib();
	
};


/////////////////////////////////////////////////////////////////////////////////
// Class CEZDibPalette
//
/////////////////////////////////////////////////////////////////////////////////


class CEZDibPalette : public CPalette  
{
public:
	CEZDibPalette(CEZDib* pBmp);
	
};



#endif // !defined(AFX_EZBITMAP_H__709D1929_D862_45DB_B914_DF5CDD0A4136__INCLUDED_)
