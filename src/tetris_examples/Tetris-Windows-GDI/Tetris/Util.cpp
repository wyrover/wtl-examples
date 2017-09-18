#include "stdafx.h"
#include "Util.h"

#define TRACE_BUFFER_SIZE 1024
#define FORMAT_BUFFER_SIZE 1024
#define MCI_LASTERROR_BUFSIZE 1024

void trace(LPCTSTR format, ...)
{
	va_list arg;
	va_start(arg, format);
	
	TCHAR buffer[TRACE_BUFFER_SIZE];
	::_vsnwprintf_s(buffer, TRACE_BUFFER_SIZE, TRACE_BUFFER_SIZE, format, arg);
	::OutputDebugString(buffer);	
	va_end(arg);
}

void DrawFormatText(HDC hdc, LPRECT rect, UINT type, LPCTSTR format, ...)
{
	va_list arg;
	va_start(arg, format);
	
	TCHAR buffer[TRACE_BUFFER_SIZE];
	::_vsnwprintf_s(buffer, TRACE_BUFFER_SIZE, TRACE_BUFFER_SIZE, format, arg);
	::DrawText(hdc, buffer, lstrlen(buffer), rect, type);	
	va_end(arg);
}

void TextFormatOut(HDC hdc, int x, int y, LPCTSTR format, ...)
{
	va_list arg;
	va_start(arg, format);
	
	TCHAR buffer[FORMAT_BUFFER_SIZE];
	::_vsnwprintf_s(buffer, FORMAT_BUFFER_SIZE, FORMAT_BUFFER_SIZE, format, arg);
	::TextOut(hdc, x, y, buffer, lstrlen(buffer));
	va_end(arg);
}

void BorderedRect(HDC hdc, int x, int y, int width, int height, COLORREF color)
{
	FillRectBrush(hdc, x, y, width, height, color);
	drawRect(hdc, x, y, width, height);
}

void FillRectBrush(HDC hdc, int x, int y, int width, int height, COLORREF color)
{
	RECT rect;
	rect.top = y;
	rect.left = x;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	HBRUSH brush = ::CreateSolidBrush(color);
	::FillRect(hdc, &rect, brush);
	::DeleteObject(brush);
}

void drawRect(HDC hdc, int x, int y, int width, int height)
{
	::MoveToEx(hdc, x, y, NULL);
	::LineTo(hdc, x + width - 1, y);
	::LineTo(hdc, x + width - 1, y + height);
	::LineTo(hdc, x, y + height);
	::LineTo(hdc, x, y);
}

void drawRectColor(HDC hdc, int x, int y, int width, int height, COLORREF color, int bold_width)
{
	HPEN pen = ::CreatePen(PS_SOLID, bold_width, color);
	HBRUSH oldPen = (HBRUSH)::SelectObject(hdc, pen);

	drawRect(hdc, x, y, width, height);

	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);
}

void mciShowLastError(MMRESULT result)
{
	LPTSTR lpstr = (LPWSTR)::GlobalAlloc(GMEM_FIXED, MCI_LASTERROR_BUFSIZE);
	mciGetErrorString(result, lpstr, MCI_LASTERROR_BUFSIZE);
	::MessageBox(NULL, lpstr, L"ERROR", MB_OK);
}

void mciAssert(MMRESULT result)
{
	// エラーだったときはその内容を表示して強制終了します
	if(result != MMSYSERR_NOERROR){
		::mciShowLastError(result);
		exit(1);
	}
}

BOOL ReadWaveFile(LPTSTR lpszFileName, LPWAVEFORMATEX lpwf, LPBYTE *lplpData, LPDWORD lpdwDataSize)
{
	HMMIO    hmmio;
	MMCKINFO mmckRiff;
	MMCKINFO mmckFmt;
	MMCKINFO mmckData;
	LPBYTE   lpData;

	hmmio = mmioOpen(lpszFileName, NULL, MMIO_READ);
	if (hmmio == NULL) {
		MessageBox(NULL, TEXT("ファイルのオープンに失敗しました。"), NULL, MB_ICONWARNING);
		return FALSE;
	}
	
	mmckRiff.fccType = mmioStringToFOURCC(TEXT("WAVE"), 0);
	if (mmioDescend(hmmio, &mmckRiff, NULL, MMIO_FINDRIFF) != MMSYSERR_NOERROR) {
		MessageBox(NULL, TEXT("WAVEファイルではありません。"), NULL, MB_ICONWARNING);
		mmioClose(hmmio, 0);
		return FALSE;
	}

	mmckFmt.ckid = mmioStringToFOURCC(TEXT("fmt "), 0);
	if (mmioDescend(hmmio, &mmckFmt, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
		mmioClose(hmmio, 0);
		return FALSE;
	}
	mmioRead(hmmio, (HPSTR)lpwf, mmckFmt.cksize);
	mmioAscend(hmmio, &mmckFmt, 0);
	if (lpwf->wFormatTag != WAVE_FORMAT_PCM) {
		MessageBox(NULL, TEXT("PCMデータではありません。"), NULL, MB_ICONWARNING);
		mmioClose(hmmio, 0);
		return FALSE;
	}

	mmckData.ckid = mmioStringToFOURCC(TEXT("data"), 0);
	if (mmioDescend(hmmio, &mmckData, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
		mmioClose(hmmio, 0);
		return FALSE;
	}
	lpData = (LPBYTE)HeapAlloc(GetProcessHeap(), 0, mmckData.cksize);
	mmioRead(hmmio, (HPSTR)lpData, mmckData.cksize);
	mmioAscend(hmmio, &mmckData, 0);

	mmioAscend(hmmio, &mmckRiff, 0);
	mmioClose(hmmio, 0);

	*lplpData = lpData;
	*lpdwDataSize = mmckData.cksize;

	return TRUE;
}

BOOL LoadBitmapFromBMPFile( LPTSTR szFileName, HBITMAP *phBitmap, HPALETTE *phPalette )
{
	BITMAP  bm;

	*phBitmap = NULL;
	*phPalette = NULL;

	// Use LoadImage() to get the image loaded into a DIBSection
	*phBitmap = (HBITMAP)LoadImage( NULL, szFileName, IMAGE_BITMAP, 0, 0,
				LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	if( *phBitmap == NULL )
		return FALSE;

	// Get the color depth of the DIBSection
	GetObject(*phBitmap, sizeof(BITMAP), &bm );
	// If the DIBSection is 256 color or less, it has a color table
	if( ( bm.bmBitsPixel * bm.bmPlanes ) <= 8 )
	{
		HDC           hMemDC;
		HBITMAP       hOldBitmap;
		RGBQUAD       rgb[256];
		LPLOGPALETTE  pLogPal;
		WORD          i;

		// Create a memory DC and select the DIBSection into it
		hMemDC = CreateCompatibleDC( NULL );
		hOldBitmap = (HBITMAP)SelectObject( hMemDC, *phBitmap );
		// Get the DIBSection's color table
		GetDIBColorTable( hMemDC, 0, 256, rgb );
		// Create a palette from the color tabl
		pLogPal = (LOGPALETTE *)malloc( sizeof(LOGPALETTE) + (256*sizeof(PALETTEENTRY)) );
		pLogPal->palVersion = 0x300;
		pLogPal->palNumEntries = 256;
		for(i=0;i<256;i++)
		{
			pLogPal->palPalEntry[i].peRed = rgb[i].rgbRed;
			pLogPal->palPalEntry[i].peGreen = rgb[i].rgbGreen;
			pLogPal->palPalEntry[i].peBlue = rgb[i].rgbBlue;
			pLogPal->palPalEntry[i].peFlags = 0;
		}
		*phPalette = CreatePalette( pLogPal );
		// Clean up
		free( pLogPal );
		SelectObject( hMemDC, hOldBitmap );
		DeleteDC( hMemDC );
	}
	else   // It has no color table, so use a halftone palette
	{
		HDC    hRefDC;

		hRefDC = GetDC( NULL );
		*phPalette = CreateHalftonePalette( hRefDC );
		ReleaseDC( NULL, hRefDC );
	}
	return TRUE;
}

BOOL LoadBitmapToDC(LPTSTR szFileName, int x, int y, HDC hdc)
{
	HBITMAP hBitmap2, hOldBitmap2;
	HPALETTE hPalette2, hOldPalette2;
	HDC hMemDC;
	BITMAP bm;

	if( LoadBitmapFromBMPFile(szFileName, &hBitmap2, &hPalette2) )
	{
		::GetObject(hBitmap2, sizeof(BITMAP), &bm);
		hMemDC = ::CreateCompatibleDC(hdc);
		hOldBitmap2 = (HBITMAP)::SelectObject(hMemDC, hBitmap2);
		hOldPalette2 = ::SelectPalette(hdc, hPalette2, FALSE);
		::RealizePalette(hdc);
			
		::BitBlt(hdc, x, y, bm.bmWidth, bm.bmHeight,
			hMemDC, 0, 0, SRCAND);

		::SelectObject(hMemDC, hOldBitmap2);
		::DeleteObject(hBitmap2);

		::SelectPalette(hdc, hOldPalette2, FALSE);
		::DeleteObject(hPalette2);
		return TRUE;
	}else{
		::OutputDebugString(L"error loading bitmap\n");
		return FALSE;
	}
}

// .wav information
WAVEFORMATEX wfe;
WAVEHDR whdr[2]; // double buffering
HWAVEOUT hWaveOut;
LPBYTE lpWaveData;
DWORD dwDataSize;
int sound_ptr = 0;

void CALLBACK musicCallback(
	HWAVEOUT hwo , UINT uMsg,         
	DWORD dwInstance,  
	DWORD dwParam1, DWORD dwParam2     
){
	if(uMsg == MM_WOM_OPEN)
		trace(L"open\n");
	if(uMsg == MM_WOM_CLOSE)
		trace(L"close\n");
	if(uMsg == MM_WOM_DONE){
		trace(L"done\n");

		if(sound_ptr >= 2){ // 2回目のバッファが終わったら、最初にバッファを参照するように(double buffering)
			sound_ptr = 0;
		}
		::mciAssert( ::waveOutWrite(hWaveOut, &whdr[sound_ptr++], sizeof(WAVEHDR)) );
	}
}

void mciPlayBGM(LPTSTR szFileName, double volume_scale)
{
	if(!ReadWaveFile(szFileName, &wfe, &lpWaveData, &dwDataSize)){
		MessageBox(NULL, TEXT("WAVEデバイスの読み込みに失敗しました。"), NULL, MB_ICONWARNING);
		return;
	}

	if(::waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfe,(DWORD_PTR)&musicCallback, 0, CALLBACK_FUNCTION) != MMSYSERR_NOERROR){
		MessageBox(NULL, TEXT("WAVEデバイスのオープンに失敗しました。"), NULL, MB_ICONWARNING);
		return;
	}

	for(int i=0; i<2; i++){
		whdr[i].lpData = (LPSTR)lpWaveData;
		whdr[i].dwBufferLength = dwDataSize;
		whdr[i].dwFlags = 0;

		::waveOutPrepareHeader(hWaveOut, &whdr[i], sizeof(WAVEHDR));

		// 最初は両方のバッファを再生する
		::mciAssert( ::waveOutWrite(hWaveOut, &whdr[i], sizeof(WAVEHDR)) );
	}

	// 音量の設定
	DWORD left = (DWORD)(0xFFFF * volume_scale); // 0xFFFF = max volume
	DWORD right = left;
	DWORD dwVolume = MAKELONG(left, right);
	::mciAssert(::waveOutSetVolume(hWaveOut, dwVolume));
}