#include <windows.h>
#include <scrnsave.h>
#include "resource.h"

#define MAXBMP 18 //Number of bitmaps in the animation

long nBitmaps[MAXBMP]; // holds the ID's on all the bitmaps in the animation
HBITMAP hBitmaps[MAXBMP]; // holds the ID's on all the bitmaps in the animation
HBITMAP hBitKraftwerk;
unsigned int timer; // The timers ID
int nAnimationSpeed = 300;

// Ja: TRACE("Read this: %n\n", nStuff); // Til MFC
// Eller: OutputDebugString("Hello !\n"); // Til Win32

LRESULT WINAPI ScreenSaverProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdcMain;	// The "Primary" DC 
	HDC hdcBitMap;	// The DC that the bitmaps will be loaded into
	RECT rect;		// rect is used to get the screen resolution

	static int nBitmapPointer; // The "Frame Counter"

	switch(message)
	{
	case WM_CREATE:
		hdcMain = GetDC(hWnd);	// Will we be able to get the DC ?
		if (hdcMain == NULL)	// It should never ever fail(But who knows) 
		{
			MessageBox(hWnd, "GetDC() ... so i dont se any point to carry on.", "Fatal error", MB_OK); 
			PostQuitMessage(3);
		}
		// Tests for the abillity to use StretchBlt()
		if ((GetDeviceCaps(hdcMain, RASTERCAPS) && RC_STRETCHBLT) == 0)
		{
			MessageBox(hWnd, "Graphics driver do not support StretchBlt().", "Fatal error", MB_OK); 
			PostQuitMessage(2);
		}
		ReleaseDC(hWnd, hdcMain);

		timer = SetTimer(hWnd, 1, 300, NULL); // Starts the timer that keeps the animation going
		if (timer == 0)
		{
			MessageBox(hWnd, "Unable to create Timer.", "Fatal error", MB_OK); 
			PostQuitMessage(1);
		}
		hBitmaps[0] = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_BITMAP1)); 
		hBitmaps[1] = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_BITMAP2)); 
		hBitmaps[2] = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_BITMAP3)); 
		hBitmaps[3] = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_BITMAP4)); 
		hBitmaps[4] = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_BITMAP5)); 
		hBitmaps[5] = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_BITMAP6)); 
		hBitmaps[6] = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_BITMAP7)); 
		hBitmaps[7] = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_BITMAP8)); 
		hBitmaps[8] = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_BITMAP9)); 
		hBitmaps[9] = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_BITMAP10)); 
		hBitmaps[10] = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_BITMAP11)); 
		hBitmaps[11] = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_BITMAP12)); 
		hBitmaps[12] = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_BITMAP13)); 
		hBitmaps[13] = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_BITMAP14)); 
		hBitmaps[14] = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_BITMAP15)); 
		hBitmaps[15] = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_BITMAP16)); 
		hBitmaps[16] = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_BITMAP17)); 
		hBitmaps[17] = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_BITMAP18)); 

		hBitKraftwerk = LoadBitmap(hMainInstance, MAKEINTRESOURCE(IDB_KRAFTWERK)); 

		break;
	case WM_TIMER:
		hdcMain = GetDC(hWnd); // Gets a handle to the main DC
		GetClientRect(hWnd,&rect); // gets the screen size 
		hdcBitMap = CreateCompatibleDC(hdcMain); // Gets a DC for the Bitmap
		SelectObject(hdcBitMap, hBitmaps[nBitmapPointer]); // puts the Bitmap in the DC 
		// Blits the Bitmap onto the screen
		StretchBlt(hdcMain,		// handle to destination DC
				   rect.right / 8 * 3,	// x-coord of destination upper-left corner
				   (rect.bottom / 4) - 10,	// y-coord of destination upper-left corner
				   rect.right / 4,	// width of destination rectangle
				   rect.bottom / 2,	// height of destination rectangle
				   hdcBitMap,   // handle to source DC
				   0,			// x-coord of source upper-left corner
				   0,			// y-coord of source upper-left corner
				   150,			// width of source rectangle
                   220,			// height of source rectangle
				   SRCCOPY		// raster operation code
		);

		nBitmapPointer++; // increments the Animation counter
		if (nBitmapPointer == MAXBMP) // if we have reach to the end of animation restart the animation loop 
		{
			nBitmapPointer = 0;
		}

		DeleteDC(hdcBitMap); 

		hdcBitMap = CreateCompatibleDC(hdcMain); // Gets a DC for the Bitmap
		SelectObject(hdcBitMap, hBitKraftwerk); // puts the Bitmap in the DC 
		// Blits the Bitmap onto the screen
		StretchBlt(hdcMain, (rect.right / 2) - ((rect.right / 2) - (rect.right / 8 * 3)), (rect.bottom / 2) + (rect.bottom / 4) - 10 ,((rect.right / 2) - (rect.right / 8 * 3)) * 2,((rect.right / 2) - (rect.right / 8 * 3)) / 4,hdcBitMap,0,0,71,9, SRCCOPY);

		
		DeleteDC(hdcBitMap); 
		ReleaseDC(hWnd, hdcMain);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, timer);
		DeleteObject(hBitmaps[0]); 
		DeleteObject(hBitmaps[1]); 
		DeleteObject(hBitmaps[2]); 
		DeleteObject(hBitmaps[3]); 
		DeleteObject(hBitmaps[4]); 
		DeleteObject(hBitmaps[5]); 
		DeleteObject(hBitmaps[6]); 
		DeleteObject(hBitmaps[7]); 
		DeleteObject(hBitmaps[8]); 
		DeleteObject(hBitmaps[9]); 
		DeleteObject(hBitmaps[10]); 
		DeleteObject(hBitmaps[11]); 
		DeleteObject(hBitmaps[12]); 
		DeleteObject(hBitmaps[13]); 
		DeleteObject(hBitmaps[14]); 
		DeleteObject(hBitmaps[15]); 
		DeleteObject(hBitmaps[16]); 
		DeleteObject(hBitmaps[17]); 
		DeleteObject(hBitKraftwerk); 

		break;
	default:
		return DefScreenSaverProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

BOOL WINAPI ScreenSaverConfigureDialog (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_INITDIALOG:
		
		return 1;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_OK:
		case ID_CANCEL:
			EndDialog(hDlg,0);
			return 1;
		}
		break;
	}
	return false;
}

BOOL WINAPI RegisterDialogClasses (HANDLE hInst)
{
	return true;
}
