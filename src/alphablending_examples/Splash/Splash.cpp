#include "stdafx.h"
#include "resource.h"

#ifdef _DEBUG
#define debugger \
	_asm{int 3}; \

#else
#define debugger \
	; \

#endif


/////////////////////
// CONSTANTS
/////////////

#define TRY_PER_PIXEL_ALPHA

const COLORREF CHROMA_KEY = RGB(0xFF, 0x0, 0xFF);
const TCHAR* RID_SAMPLE_IMAGE = MAKEINTRESOURCE(IDB_SAMPLE);



/////////////////////
// GLOBALS
/////////////

// application instance
HINSTANCE g_hInstance = (HINSTANCE)INVALID_HANDLE_VALUE;

// try per pixel alpha blending?
#ifdef TRY_PER_PIXEL_ALPHA
bool g_bUsePerPixelAlpha = true;
#else
bool g_bUsePerPixelAlpha = false;
#endif

// splash image
HBITMAP g_hbmSplashImage = (HBITMAP)INVALID_HANDLE_VALUE;
HBRUSH g_hbrSplashImage = (HBRUSH)INVALID_HANDLE_VALUE;
BITMAPINFO* g_pbmiSplashImage = NULL;
void* g_pSplashImagePixels = NULL;
INT g_iSplashImageWidth = 0;
INT g_iSplashImageHeight = 0;


// mouse dragging
bool bMouseDown = false;
bool bMouseDragging = false;
POINTS ptMouseDown_Screen;
POINTS ptMouseDown_Screen_WindowPos;


/////////////////////
// FORWARD DECS
/////////////

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

bool Paint(HDC hdc, PAINTSTRUCT* ps, HWND hWnd);
void LoadSplashImage();
void UnloadSplashImage();


void LoadSplashImage()
{
	// create brush
	g_hbmSplashImage = LoadBitmap(g_hInstance, RID_SAMPLE_IMAGE);
	g_hbrSplashImage = CreatePatternBrush(g_hbmSplashImage);

	// access the image bytes
	BITMAPV5HEADER* pImageHeader = (BITMAPV5HEADER*)LockResource(LoadResource(NULL, FindResource(NULL, RID_SAMPLE_IMAGE, RT_BITMAP)));
	DWORD* pImageData = (DWORD*)(((char*)pImageHeader) + pImageHeader->bV5Size);
	
	// store dimensions globally
	g_iSplashImageWidth = pImageHeader->bV5Width;
	g_iSplashImageHeight = pImageHeader->bV5Height;

	// modify image bytes so the pixels are premultiplied
	for(int j = 0; j < g_iSplashImageHeight; ++j)
	{
		for(int i = 0; i < g_iSplashImageWidth; ++i)
		{
			int index = ( g_iSplashImageHeight - j - 1 ) * g_iSplashImageWidth + i;

			DWORD d = pImageData[index];

			BYTE a = d >> 24;
			BYTE pmR = static_cast<BYTE>( ((d & 0x00FF0000) >> 16) * a / 255 );
			BYTE pmG = static_cast<BYTE>( ((d & 0x0000FF00) >> 8) * a / 255 );
			BYTE pmB = static_cast<BYTE>( ((d & 0x000000FF)) * a / 255 );
			d = pmB | (pmG << 8) | (pmR << 16) | (a << 24);
			
			pImageData[index] = d;
		}
	}

	// store pointers globally
	g_pbmiSplashImage = reinterpret_cast<BITMAPINFO*>(pImageHeader);
	g_pSplashImagePixels = pImageData;
}

void UnloadSplashImage()
{
	// note: not necessary in WinXP+ to "unlock" the g_pbmiSplashImage data pointer.

	DeleteObject(g_hbrSplashImage);
	DeleteObject(g_hbmSplashImage);
}


/////////////////////
// METHODS
/////////////
int APIENTRY _tWinMain(
	HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR lpCmdLine,
    int nCmdShow
)
{
	// store instance handle
	g_hInstance = hInstance;


	//////
	// load resources
	LoadSplashImage();


	//////
	// setup class & create window
	MyRegisterClass(hInstance);
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}


	//////
	// message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnloadSplashImage();

	// quit
	return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= TEXT("Splash");
	wcex.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	RECT workingAreaRect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &workingAreaRect, 0);
	int width = workingAreaRect.right - workingAreaRect.left;
	int height = workingAreaRect.bottom - workingAreaRect.top;
	int x;
	int y;
	if(g_iSplashImageWidth >= width)
	{
		x = workingAreaRect.left;
	}
	else
	{
		x = workingAreaRect.left + width/2 - g_iSplashImageWidth/2;
	}
	if(g_iSplashImageHeight >= height)
	{
		y = workingAreaRect.top;
	}
	else
	{
		y = workingAreaRect.top + height/2 - g_iSplashImageHeight/2 - 60;
		if(y < workingAreaRect.top)
		{
			y = workingAreaRect.top;
		}
	}
	
	hWnd = CreateWindowEx(
			WS_EX_LAYERED, 
			TEXT("Splash"), 
			TEXT("Splash"), 
			WS_POPUP,
			x, 
			y, 
			g_iSplashImageWidth, 
			g_iSplashImageHeight, 
			NULL, 
			NULL, 
			hInstance, 
			NULL
		)
	;

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


/////////////////////
// METHODS: painting
/////////////
bool Paint(HDC hdc, PAINTSTRUCT* ps, HWND hWnd)
{
#ifdef _DEBUG
	if(g_iSplashImageHeight == 0 || g_iSplashImageWidth == 0)
	{
		// splash image must be loaded first.
		debugger;
	}
#endif

	if(!g_bUsePerPixelAlpha)
	{
		RECT rect;
		rect.bottom = g_iSplashImageHeight;
		rect.top = 0;
		rect.left = 0;
		rect.right = g_iSplashImageWidth;
	
		FillRect(hdc, &rect, g_hbrSplashImage);
		return true;
	}


	//////
	// setup a "back buffer" to be same format as the screen DC.
	HDC hdcScreen = GetDC(NULL);
	HDC hdcBackBuffer = CreateCompatibleDC(hdcScreen);
	HBITMAP hbmBackBuffer = CreateCompatibleBitmap(hdcScreen, g_iSplashImageWidth, g_iSplashImageHeight);
	HGDIOBJ hbmOld = SelectObject(hdcBackBuffer, hbmBackBuffer);

	// copy image to backbuffer
	SetDIBitsToDevice(
		hdcBackBuffer, 
		0,
		0,
		g_iSplashImageWidth,
		g_iSplashImageHeight,
		0,
		0,
		0,
		g_iSplashImageHeight,
		g_pSplashImagePixels,
		reinterpret_cast<BITMAPINFO*>(g_pbmiSplashImage), 
		0
	);

	//////
	// copy to "front buffer"
	POINT ptSrc;
	ptSrc.x = 0;
	ptSrc.y = 0;
	SIZE size;
	size.cx = g_iSplashImageWidth;
	size.cy = g_iSplashImageHeight;
	BLENDFUNCTION bf;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;
	bf.BlendFlags = 0;
	bf.BlendOp = AC_SRC_OVER;
	if(!UpdateLayeredWindow(hWnd, NULL, NULL, &size, hdcBackBuffer, &ptSrc, 0, &bf, ULW_ALPHA))
	{
#ifdef _DEBUG
		auto e = GetLastError();
		debugger;
#endif
		DeleteDC(hdcBackBuffer);
		return false;
	}
		
	// reset and release DC
	SelectObject(hdcBackBuffer, hbmOld);
	DeleteDC(hdcBackBuffer);

	// done
	return true;
}


/////////////////////
// METHODS: input
/////////////
void ProcessMouse(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_LBUTTONDOWN:
		if(bMouseDown){
			break;
		}
		bMouseDown = true;

		// grab window position
		RECT rctWindow;
		GetWindowRect(hWnd, &rctWindow);

		// grab and transform mouse position
		ptMouseDown_Screen = MAKEPOINTS(lParam);
		ptMouseDown_Screen.x += static_cast<SHORT>(rctWindow.left);
		ptMouseDown_Screen.y += static_cast<SHORT>(rctWindow.top);

		// save window position
		ptMouseDown_Screen_WindowPos.x = static_cast<SHORT>(rctWindow.left);
		ptMouseDown_Screen_WindowPos.y = static_cast<SHORT>(rctWindow.top);



		break;
	case WM_LBUTTONUP:
		bMouseDown = false;
		bMouseDragging = false;

		break;
	case WM_MOUSEMOVE:
		{
			//if(!bMouseDown)
			if((wParam & MK_LBUTTON) == 0 || !bMouseDown)
			{
				break;
			}

			bMouseDragging = true;

			// grab window position
			RECT rctWindow;
			GetWindowRect(hWnd, &rctWindow);

			// grab and transform mouse position
			POINTS ptMouseNow = MAKEPOINTS(lParam);
			ptMouseNow.x += static_cast<SHORT>(rctWindow.left);
			ptMouseNow.y += static_cast<SHORT>(rctWindow.top);

			// calculate mouse delta
			int dX = ptMouseNow.x - ptMouseDown_Screen.x;
			int dY = ptMouseNow.y - ptMouseDown_Screen.y;
			
			// grab window dimensions
			int iHeight = rctWindow.bottom - rctWindow.top;
			int iWidth = rctWindow.right - rctWindow.left;

			// calculate new window position
			int iNewX = ptMouseDown_Screen_WindowPos.x + dX;
			int iNewY = ptMouseDown_Screen_WindowPos.y + dY;

			// move window
			MoveWindow(hWnd, iNewX , iNewY, iWidth, iHeight, TRUE);

			break;
		}
	}
}

void ProcessKeyboard(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_ESCAPE:
				PostMessage(hWnd, WM_DESTROY, 0, 0);
				break;
			}

			break;
		}
		
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch (message)
	{
	case WM_CREATE:
		if(g_bUsePerPixelAlpha)
		{
			// try the per pixel metho
			bool bPaintSuccess = Paint(0, 0, hWnd);
			if(!bPaintSuccess)
			{ // per pixel failed

				// switch to chroma key method.
				g_bUsePerPixelAlpha = false;
				SetLayeredWindowAttributes(hWnd, CHROMA_KEY, 255, LWA_COLORKEY);
			}
		}
		else
		{
			// setup chroma key method.
			SetLayeredWindowAttributes(hWnd, CHROMA_KEY, 255, LWA_COLORKEY);
		}

		break;

	case WM_PAINT:
		if(!g_bUsePerPixelAlpha)
		{
			hdc = BeginPaint(hWnd, &ps);
		
			Paint(hdc, &ps, hWnd);

			EndPaint(hWnd, &ps);
		}
		break;

	case WM_KEYDOWN:
	case WM_KEYUP:
		ProcessKeyboard(hWnd, message, wParam, lParam);
		break;

	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
		ProcessMouse(hWnd, message, wParam, lParam);
		break;



	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
