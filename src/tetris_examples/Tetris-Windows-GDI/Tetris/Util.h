#pragma once
#include <MMSystem.h>

void trace(LPCTSTR format, ...);
void FillRectBrush(HDC hdc, int x, int y, int width, int height, COLORREF color);
void BorderedRect(HDC hdc, int x, int y, int width, int height, COLORREF color);
void drawRect(HDC hdc, int x, int y, int width, int height);
void mciShowLastError(MMRESULT result);
void mciAssert(MMRESULT result);
BOOL ReadWaveFile(LPTSTR lpszFileName, LPWAVEFORMATEX lpwf, LPBYTE *lplpData, LPDWORD lpdwDataSize);
BOOL LoadBitmapFromBMPFile( LPTSTR szFileName, HBITMAP *phBitmap, HPALETTE *phPalette );
BOOL LoadBitmapToDC(LPTSTR szFileName, int x, int y, HDC hdc);
void drawRectColor(HDC hdc, int x, int y, int width, int height, COLORREF color, int bold_width);
void DrawFormatText(HDC hdc, LPRECT rect, UINT type, LPCTSTR format, ...);
void TextFormatOut(HDC hdc, int x, int y, LPCTSTR format, ...);
void mciPlayBGM(LPTSTR szFileName, double volume_scale);