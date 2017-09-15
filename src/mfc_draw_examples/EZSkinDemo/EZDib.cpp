// EZDib.cpp: implementation of the CEZDib class.
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
#include "stdafx.h"
#include "EZDib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define PADWIDTH(x)	(((x)*8 + 31)  & (~31))/8

CEZDibPalette::CEZDibPalette(CEZDib* pBmp)
{
	
	ASSERT( pBmp );
    int cPaletteEntries = pBmp->GetPalEntries();
    int cPalette = sizeof(LOGPALETTE) +
		sizeof(PALETTEENTRY) * cPaletteEntries;
    // Since the LOGPALETTE structure is open-ended, you
    // must dynamically allocate it, rather than using one
    // off the stack.
    LOGPALETTE* pPal = (LOGPALETTE*)new BYTE[cPalette];
    RGBQUAD*    pColorTab = pBmp->GetColorTablePtr();
    pPal->palVersion = 0x300;
    pPal->palNumEntries = (WORD)cPaletteEntries;
    // Roll through the color table, and add each color to
    // the logical palette.
    for( int ndx = 0; ndx < cPaletteEntries; ndx++ )
    {
        pPal->palPalEntry[ndx].peRed   = pColorTab[ndx].rgbRed;
        pPal->palPalEntry[ndx].peGreen = pColorTab[ndx].rgbGreen;
        pPal->palPalEntry[ndx].peBlue  = pColorTab[ndx].rgbBlue;
        pPal->palPalEntry[ndx].peFlags = NULL;
    }
    VERIFY( CreatePalette( pPal ) );
    delete [] (BYTE*)pPal;
}


IMPLEMENT_DYNCREATE(CEZDib,CBitmap);

CEZDib :: CEZDib()
: m_pInfo(0)
, m_pPixels(0)
, m_pPal(0)
, m_bIsPadded(FALSE)
,m_nType(BMP_NORMAL)
{
}

CEZDib::CEZDib(CString strPath,int nType)
: m_pInfo(0)
, m_pPixels(0)
, m_pPal(0)
, m_bIsPadded(FALSE)
,m_nType(nType)
{
	
	Load(strPath);
}


CEZDib::CEZDib(UINT nIDResource,int nType)
: m_pInfo(0)
, m_pPixels(0)
, m_pPal(0)
, m_bIsPadded(FALSE)
,m_nType(nType){
	
	Load(nIDResource);
}

CEZDib :: ~CEZDib() 
{
	
	
	DestroyBitmap();
}

void CEZDib :: DestroyBitmap() 
{
	if(m_hObject)
		CBitmap::DeleteObject();
	if(m_pInfo)
		delete [] (BYTE*)m_pInfo;
	if(m_pPixels)
		delete [] m_pPixels;
	if(m_pPal)
		delete m_pPal;
	m_pInfo = 0;
	m_pPixels = 0;
	m_pPal = 0;
}

BOOL CEZDib :: CreateFromBitmap( CDC * pDC, CBitmap * pSrcBitmap ) 
{
	ASSERT_VALID(pSrcBitmap);
	ASSERT_VALID(pDC);
	
	
	
	try {
		BITMAP bmHdr;
		
		// Get the pSrcBitmap info
		pSrcBitmap->GetObject(sizeof(BITMAP), &bmHdr);
		
		if(!CreateBitmapIndirect(&bmHdr))
			throw TEXT("could not create copy");
		
		// Reallocate space for the image data
		if( m_pPixels ) 
		{
			delete [] m_pPixels;
			m_pPixels = 0;
		}
		
		DWORD dwWidth;
		if (bmHdr.bmBitsPixel > 8)
			dwWidth = PADWIDTH(bmHdr.bmWidth * 3);
		else
			dwWidth = PADWIDTH(bmHdr.bmWidth);
		
		m_pPixels = new BYTE[dwWidth*bmHdr.bmHeight];
		if( !m_pPixels )
			throw TEXT("could not allocate data storage\n" );
		
		// Set the appropriate number of colors base on BITMAP structure info
		WORD wColors;
		switch( bmHdr.bmBitsPixel ) {
		case 1 : 
			wColors = 2;
			break;
		case 4 :
			wColors = 16;
			break;
		case 8 :
			wColors = 256;
			break;
		default :
			wColors = 0;
			break;
		}
		
		// Re-allocate and populate BITMAPINFO structure
		if( m_pInfo ) {
			delete [] (BYTE*)m_pInfo;
			m_pInfo = 0;
		}
		
		m_pInfo = (BITMAPINFO*)new BYTE[sizeof(BITMAPINFOHEADER) + wColors*sizeof(RGBQUAD)];
		if( !m_pInfo )
			throw TEXT("could not allocate BITMAPINFO struct\n");
		
		// Populate BITMAPINFO header info
		m_pInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		m_pInfo->bmiHeader.biWidth = bmHdr.bmWidth;
		m_pInfo->bmiHeader.biHeight = bmHdr.bmHeight;
		m_pInfo->bmiHeader.biPlanes = bmHdr.bmPlanes;
		
		
		if( bmHdr.bmBitsPixel > 8 )
			m_pInfo->bmiHeader.biBitCount = 24;
		else
			m_pInfo->bmiHeader.biBitCount = bmHdr.bmBitsPixel;
		
		m_pInfo->bmiHeader.biCompression = BI_RGB;
		m_pInfo->bmiHeader.biSizeImage = ((((bmHdr.bmWidth * bmHdr.bmBitsPixel) + 31) & ~31) >> 3) * bmHdr.bmHeight;
		m_pInfo->bmiHeader.biXPelsPerMeter = 0;
		m_pInfo->bmiHeader.biYPelsPerMeter = 0;
		m_pInfo->bmiHeader.biClrUsed = 0;
		m_pInfo->bmiHeader.biClrImportant = 0;
		
		// Now actually get the bits
		int test = ::GetDIBits(pDC->GetSafeHdc(), (HBITMAP)pSrcBitmap->GetSafeHandle(),
			0, (WORD)bmHdr.bmHeight, m_pPixels, m_pInfo, DIB_RGB_COLORS);
		
		// check that we scanned in the correct number of bitmap lines
		if( test != (int)bmHdr.bmHeight )
			throw TEXT("call to GetDIBits did not return full number of requested scan lines\n");
		
		CreatePalette();
		m_bIsPadded = FALSE;
#ifdef _DEBUG
	} catch( TCHAR * psz ) {
		TRACE1("CEZDib::CreateFromBitmap(): %s\n", psz);
#else
	} catch( TCHAR * ) {
#endif
		if( m_pPixels ) {
			delete [] m_pPixels;
			m_pPixels = 0;
		}
		if( m_pInfo ) {
			delete [] (BYTE*) m_pInfo;
			m_pInfo = 0;
		}
		return FALSE;
	}
	
	return TRUE;
}


BOOL CEZDib :: LoadBitmap(LPCTSTR pszID) 
{
	HBITMAP hBmp = (HBITMAP)::LoadImage(
		AfxGetInstanceHandle(), 
		pszID, IMAGE_BITMAP,
		0,0, LR_CREATEDIBSECTION
		);
	
	if( hBmp == 0 ) 
		return FALSE;
	
	CBitmap bmp;
	bmp.Attach(hBmp);
	CClientDC cdc( CWnd::GetDesktopWindow() );
	BOOL bRet = CreateFromBitmap( &cdc, &bmp );
	bmp.DeleteObject();
	return bRet;
}


BOOL CEZDib :: Load( CFile* pFile ) {
    ASSERT( pFile );
    BOOL fReturn = TRUE;
    try {
        delete [] (BYTE*)m_pInfo;
        delete [] m_pPixels;
        m_pInfo = 0;
        m_pPixels = 0;
        DWORD       dwStart = pFile->GetPosition();
        //
        // Check to make sure we have a bitmap. The first two bytes must
        // be 'B' and 'M'.
        BITMAPFILEHEADER fileHeader;
        pFile->Read(&fileHeader, sizeof(fileHeader));
        if( fileHeader.bfType != 0x4D42 )
            throw TEXT("Error:Unexpected file type, not a DIB\n");
		
        BITMAPINFOHEADER infoHeader;
        pFile->Read( &infoHeader, sizeof(infoHeader) );
        if( infoHeader.biSize != sizeof(infoHeader) )
            throw TEXT("Error:OS2 PM BMP Format not supported\n");
		
        // Store the sizes of the DIB structures
        int cPaletteEntries = GetPalEntries( infoHeader );
        int cColorTable = 256 * sizeof(RGBQUAD);
        int cInfo = sizeof(BITMAPINFOHEADER) + cColorTable;
        int cPixels = fileHeader.bfSize - fileHeader.bfOffBits;
        //
        // Allocate space for a new bitmap info header, and copy
        // the info header that was loaded from the file. Read the
        // the file and store the results in the color table.
        m_pInfo = (BITMAPINFO*)new BYTE[cInfo];
        memcpy( m_pInfo, &infoHeader, sizeof(BITMAPINFOHEADER) );
        pFile->Read( ((BYTE*)m_pInfo) + sizeof(BITMAPINFOHEADER),
			cColorTable );
        //
        // Allocate space for the pixel area, and load the pixel
        // info from the file.
        m_pPixels = new BYTE[cPixels];
        pFile->Seek(dwStart + fileHeader.bfOffBits, CFile::begin);
        pFile->Read( m_pPixels, cPixels );
		CreatePalette();
		m_bIsPadded = TRUE;
#ifdef _DEBUG
    } catch( TCHAR * psz ) {
		TRACE( psz );
#else
    } catch( TCHAR * ) {
#endif
        fReturn = FALSE;
    }
    return fReturn;
}

BOOL CEZDib :: Load( const CString & strFilename ) 
{
	
	ASSERT(!m_hObject);
	HBITMAP hBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),strFilename,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	if(!hBmp)
		return FALSE;
	CBitmap::Attach(hBmp);
	CFile file;
	
	
	if( file.Open( strFilename, CFile::modeRead ) )
		return Load( &file );
	return FALSE;
}

BOOL CEZDib :: Save( const CString & strFileName ) {
    ASSERT(! strFileName.IsEmpty());
	
    CFile File;
	
	if( !File.Open(strFileName, CFile::modeCreate|CFile::modeWrite) ) {
		TRACE1("CEZDib::Save(): Failed to open file %s for writing.\n", LPCSTR(strFileName));
		return FALSE;
	}
	
    return Save( &File );
}      


// Does not open or close pFile.  Assumes
// caller will do it.
BOOL CEZDib :: Save( CFile * pFile ) {
	ASSERT_VALID( pFile );
    ASSERT( m_pInfo );
    ASSERT( m_pPixels );
    
    BITMAPFILEHEADER bmfHdr;
    
	DWORD dwPadWidth = PADWIDTH(GetWidth());
	
	// Make sure bitmap data is in padded format
	PadBits();
    
    bmfHdr.bfType = 0x4D42;
    // initialize to BitmapInfo size
    DWORD dwImageSize= m_pInfo->bmiHeader.biSize;
	// Add in palette size
    WORD wColors = GetColorCount();
    WORD wPaletteSize = (WORD)(wColors*sizeof(RGBQUAD));
    dwImageSize += wPaletteSize;
    
    // Add in size of actual bit array
    dwImageSize += PADWIDTH((GetWidth()) * DWORD(m_pInfo->bmiHeader.biBitCount)/8) * GetHeight();
    m_pInfo->bmiHeader.biSizeImage = 0;
    bmfHdr.bfSize = dwImageSize + sizeof(BITMAPFILEHEADER);
    bmfHdr.bfReserved1 = 0;
    bmfHdr.bfReserved2 = 0;
    bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + m_pInfo->bmiHeader.biSize + wPaletteSize;
    pFile->Write(&bmfHdr, sizeof(BITMAPFILEHEADER));
    
    pFile->Write(m_pInfo, sizeof(BITMAPINFO) + (wColors-1)*sizeof(RGBQUAD));
    pFile->WriteHuge(m_pPixels,
		DWORD((dwPadWidth*(DWORD)m_pInfo->bmiHeader.biBitCount*GetHeight())/8) );
	
	return TRUE;
}

BOOL CEZDib :: CreatePalette() {
	if( m_pPal )
		delete m_pPal;
	m_pPal = 0;
	ASSERT( m_pInfo );
	// We only need a palette, if there are <= 256 colors.
	// otherwise we would bomb the memory.
	if( m_pInfo->bmiHeader.biBitCount <= 8 )
		m_pPal = new CEZDibPalette(this);
	return m_pPal ? TRUE : FALSE;
}

void CEZDib :: ClearPalette() {
	if( m_pPal )
		delete m_pPal;
	m_pPal = 0;
}


BOOL CEZDib::Draw(CDC* pDC,const CRect& rectDC,const CRect& rectDIB) const
{
	
	ASSERT(pDC);
	if(!m_hObject)
		return FALSE;
	if(!m_pInfo)
		return FALSE;
	CRect rcDC,rcDIB;
	
	if(rectDC.IsRectEmpty())
	{
		pDC->GetClipBox(&rcDC);
		
	}
	
	else
	{
		rcDC = rectDC;
	}
	if(rectDIB.IsRectEmpty())
	{
		rcDIB = CRect(0,0,GetWidth(),GetHeight());
	}
	else
		rcDIB = rectDIB;
	
	
	switch(m_nType)
	{
	case BMP_NORMAL:
		DrawNormal(pDC,rcDC,rcDIB);
		return TRUE;
	case BMP_STRETCH:
		DrawStretched(pDC,rcDC,rcDIB);
		return TRUE;
	case BMP_TILE:
		DrawTiled(pDC,rcDC,rcDIB);
		return TRUE;
		
	};
	
	return FALSE;
	
}


void CEZDib :: DrawTiled( CDC* pDC, CRect& rectDC, CRect& rectDIB) const
{
	
	ASSERT( pDC );
	ASSERT(m_hObject);
	ASSERT(m_pInfo);
    HDC     hdc = pDC->GetSafeHdc();
	
	CPalette * pOldPal = 0;
	
	if( m_pPal ) 
	{
		pOldPal = pDC->SelectPalette( m_pPal, FALSE );
		pDC->RealizePalette();
		// Make sure to use the stretching mode best for color pictures
		pDC->SetStretchBltMode(COLORONCOLOR);
	}
	
	int x=rectDC.left,y=rectDC.top;
	
	
	while(y<rectDC.bottom)
	{
		
		while(x<rectDC.right)
		{
			
			CRect rcDC(x,y,__min(x+rectDIB.Width(),rectDC.right),__min(y+rectDIB.Height(),rectDC.bottom));
			
			SetDIBitsToDevice
				(
				hdc,					// device
				rcDC.left,			// DestX
				rcDC.top,				// DestY
				rcDC.Width(),			// DestWidth
				rcDC.Height(),		// DestHeight
				rectDIB.left,			// SrcX
				GetHeight() -
				rectDIB.top -
				rectDIB.Height(),	// SrcY
				0,						// StartScan
				GetHeight(),			// NumScans
				GetPixelPtr(),			// color data
				GetHeaderPtr(),			// header data
				DIB_RGB_COLORS			// color usage
				);
			
			
			x+=rectDIB.Width();
			
		}
		x=rectDC.left;
		y+=rectDIB.Height();
	}
	
	if( m_pPal )
		pDC->SelectPalette( pOldPal, FALSE );
}

//
// DrawDib uses StretchDIBits to display the bitmap.
void CEZDib :: DrawStretched( CDC* pDC, CRect& rectDC,CRect& rectImage) const
{
    ASSERT( pDC );
    HDC     hdc = pDC->GetSafeHdc();
	
	CPalette * pOldPal = 0;
	
	if( m_pPal ) 
	{
		pOldPal = pDC->SelectPalette( m_pPal, FALSE );
		pDC->RealizePalette();
		// Make sure to use the stretching mode best for color pictures
		pDC->SetStretchBltMode(COLORONCOLOR);
	}
	
    
	StretchDIBits( hdc,
		rectDC.left,
		rectDC.top,
		rectDC.Width(),
		rectDC.Height(),
		rectImage.left,
		rectImage.top,
		rectImage.Width(),
		rectImage.Height(),
		GetPixelPtr(),
		GetHeaderPtr(),
		DIB_RGB_COLORS,
		SRCCOPY );
	
	if( m_pPal )
		pDC->SelectPalette( pOldPal, FALSE );
}

void CEZDib :: DrawNormal( CDC * pDC, CRect & rectDC, CRect & rectDIB ) const
{
    ASSERT( pDC );
    HDC     hdc = pDC->GetSafeHdc();
	
	CPalette * pOldPal = 0;
	
	if( m_pPal ) {
		pOldPal = pDC->SelectPalette( m_pPal, FALSE );
		pDC->RealizePalette();
		// Make sure to use the stretching mode best for color pictures
		pDC->SetStretchBltMode(COLORONCOLOR);
	}
	
	   
	SetDIBitsToDevice(
		hdc,					// device
		rectDC.left,			// DestX
		rectDC.top,				// DestY
		rectDC.Width(),			// DestWidth
		rectDC.Height(),		// DestHeight
		rectDIB.left,			// SrcX
		GetHeight() -
		rectDIB.top -
		rectDIB.Height(),	// SrcY
		0,						// StartScan
		GetHeight(),			// NumScans
		GetPixelPtr(),			// color data
		GetHeaderPtr(),			// header data
		DIB_RGB_COLORS			// color usage
		);
	
	if( m_pPal )
		pDC->SelectPalette( pOldPal, FALSE );
	
	
}

BITMAPINFO * CEZDib :: GetHeaderPtr() const 
{
    ASSERT( m_pInfo );
    ASSERT( m_pPixels );
    return m_pInfo;
}

RGBQUAD * CEZDib :: GetColorTablePtr() const 
{
    ASSERT( m_pInfo );
    ASSERT( m_pPixels );
    RGBQUAD* pColorTable = 0;
    if( m_pInfo != 0 ) {
        int cOffset = sizeof(BITMAPINFOHEADER);
        pColorTable = (RGBQUAD*)(((BYTE*)(m_pInfo)) + cOffset);
    }
    return pColorTable;
}

BYTE * CEZDib :: GetPixelPtr() const 
{
    ASSERT( m_pInfo );
    ASSERT( m_pPixels );
    return m_pPixels;
}

int CEZDib :: GetWidth() const 
{
    ASSERT( m_pInfo );
    return m_pInfo->bmiHeader.biWidth;
}

int CEZDib :: GetHeight() const 
{
    ASSERT( m_pInfo );
    return m_pInfo->bmiHeader.biHeight;
}

WORD CEZDib :: GetColorCount() const 
{
	ASSERT( m_pInfo );
	
	switch( m_pInfo->bmiHeader.biBitCount )	
	{
	case 1:		return 2;
	case 4:		return 16;
	case 8:		return 256;
	default:	return 0;
	}
}

int CEZDib :: GetPalEntries() const 
{
    ASSERT( m_pInfo );
    return GetPalEntries( *(BITMAPINFOHEADER*)m_pInfo );
}

int CEZDib :: GetPalEntries( BITMAPINFOHEADER& infoHeader ) const 
{
	int nReturn;
	if( infoHeader.biClrUsed == 0 )
		nReturn = ( 1 << infoHeader.biBitCount );
	else
		nReturn = infoHeader.biClrUsed;
	
	return nReturn;
}

DWORD CEZDib :: GetBitsPerPixel() const 
{
	ASSERT( m_pInfo );
	return m_pInfo->bmiHeader.biBitCount;
}

DWORD CEZDib :: LastByte( DWORD dwBitsPerPixel, DWORD dwPixels ) const 
{
	register DWORD dwBits = dwBitsPerPixel * dwPixels;
	register DWORD numBytes  = dwBits / 8;
	register DWORD extraBits = dwBits - numBytes * 8;
    return (extraBits % 8) ? numBytes+1 : numBytes;
}


DWORD CEZDib :: GetBytesPerLine( DWORD dwBitsPerPixel, DWORD dwWidth ) const 
{
	DWORD dwBits = dwBitsPerPixel * dwWidth;
	
	if( (dwBits % 32) == 0 )
		return (dwBits/8);  // already DWORD aligned, no padding needed
	
	DWORD dwPadBits = 32 - (dwBits % 32);
	return (dwBits/8 + dwPadBits/8 + (((dwPadBits % 8) > 0) ? 1 : 0));
}

BOOL CEZDib :: PadBits() 
{
	if( m_bIsPadded )
		return TRUE;
	
    // dwAdjust used when bits per pixel spreads over more than 1 byte
    DWORD dwAdjust = 1, dwOffset = 0, dwPadOffset=0;
	BOOL bIsOdd = FALSE;
    
	dwPadOffset = GetBytesPerLine(GetBitsPerPixel(), GetWidth());
	dwOffset = LastByte(GetBitsPerPixel(), GetWidth());
	
	if( dwPadOffset == dwOffset )
		return TRUE;
	
    BYTE * pTemp = new BYTE [GetWidth()*dwAdjust];
    if( !pTemp ) {
		TRACE1("CEZDib::PadBits(): could not allocate row of width %d.\n", GetWidth());
		return FALSE;
	}
    
    // enough space has already been allocated for the bit array to
    // include the padding, so we just need to shift rows around.
    // This will pad each "row" on a DWORD alignment.
	
    for( DWORD row = GetHeight()-1 ; row>0 ; --row ) {
		CopyMemory((void *)pTemp, (const void *)(m_pPixels + (row*dwOffset)), dwOffset );
		CopyMemory((void *)(m_pPixels + (row*dwPadOffset)), (const void *)pTemp, dwOffset);
	}
	//  delete [] pTemp;
    
    return TRUE;
}

BOOL CEZDib::UnPadBits() 
{
	if( ! m_bIsPadded )
		return TRUE;
	
	DWORD dwAdjust = 1;
	BOOL bIsOdd = FALSE;
	
	DWORD dwPadOffset = GetBytesPerLine(GetBitsPerPixel(), GetWidth());
	DWORD dwOffset = LastByte(GetBitsPerPixel(), GetWidth());
	
    BYTE * pTemp = new BYTE [dwOffset];
    if( !pTemp ) {
		TRACE1("CEZDib::UnPadBits() could not allocate row of width %d.\n", GetWidth());
		return FALSE;
	}
	
    // enough space has already been allocated for the bit array to
    // include the padding, so we just need to shift rows around.
    for( DWORD row=1 ; row < DWORD(GetHeight()); ++row ) {
		CopyMemory((void *)pTemp, (const void *)(m_pPixels + row*(dwPadOffset)), dwOffset);
		CopyMemory((void *)(m_pPixels + (row*dwOffset)), (const void *)pTemp, dwOffset);
	}
	
    delete [] pTemp;
    
    return TRUE;
}

BOOL CEZDib::Attach(HBITMAP hBitmap)
{
	
	
	CBitmap bmp;
	bmp.Attach(hBitmap);
	CClientDC dc(NULL);
	BOOL bRet = CreateFromBitmap(&dc,&bmp);
	bmp.Detach();
	
	return bRet;
	
}

HBITMAP CEZDib::Detach()
{
	
    delete [] (BYTE*)m_pInfo;
    delete [] m_pPixels;
	delete m_pPal;
	m_pInfo = 0;
	m_pPixels = 0;
	m_pPal = 0;
	return (HBITMAP)CBitmap::Detach();
}


BOOL CEZDib::DrawTransparent(CDC* pDC,COLORREF clrTrans,const CRect& rcDest,const CRect& rcSrc) const
{
	

	CRect rcDC(rcDest),rcBmp(rcSrc);

	
	if(rcDC.IsRectNull()) rcDC =CEZClipRect(pDC);
	if(rcBmp.IsRectNull()) rcBmp = CRect(0,0,GetWidth(),GetHeight());
	
	
	CEZMemDC memDC(pDC,&rcDC,TRUE,TRUE	),imageDC(pDC,&rcDC,FALSE);
	CEZMonoDC backDC(pDC,&rcDC),maskDC(pDC,&rcDC);
	

	DrawNormal(&imageDC,rcDC,rcBmp);

	COLORREF clrImageOld = imageDC.SetBkColor(clrTrans);
	maskDC.BitBlt(rcDC.left,rcDC.top,rcDC.Width(),rcDC.Height(),&imageDC,rcDC.left,rcDC.top,SRCCOPY);
	imageDC.SetBkColor(clrImageOld);


	backDC.BitBlt(rcDC.left,rcDC.top,rcDC.Width(),rcDC.Height(),&maskDC,rcDC.left,rcDC.top,NOTSRCCOPY);

	memDC.BitBlt(rcDC.left,rcDC.top,rcDC.Width(),rcDC.Height(),&maskDC,rcDC.left,rcDC.top,SRCAND);

	imageDC.BitBlt(rcDC.left,rcDC.top,rcDC.Width(),rcDC.Height(),&backDC,rcDC.left,rcDC.top,SRCAND);

	memDC.BitBlt(rcDC.left,rcDC.top,rcDC.Width(),rcDC.Height(),&imageDC,rcDC.left,rcDC.top,SRCPAINT);




	


	return TRUE;


		
}