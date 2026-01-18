// DXC_ddraw.h: interface for the DXC_ddraw class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <memory.h>
#include <string.h>
#include "ddraw.h"
#include "Misc.h"
#include "GlobalDef.h"

typedef signed char i8;
class DXC_ddraw  
{
public:	
	void DrawItemShadowBox(short sX, short sY, short dX, short dY, int iType = 0);
	bool m_init;
	void ChangeBPP(i8 bpp);

	DXC_ddraw();
	virtual ~DXC_ddraw();
	bool bInit(HWND hWnd);
	void ColorTransferRGB(COLORREF fcolor, int * iR, int * iG, int * iB);
	HRESULT InitFlipToGDI(HWND hWnd);
	void ChangeDisplayMode(HWND hWnd);
	void DrawText(LPRECT pRect, const char * pString, COLORREF rgb);
	void _ReleaseBackBufferDC();
	void _GetBackBufferDC();
	void TextOut(int x, int y, char * cStr, COLORREF rgb);
	void _TestPixelFormat();
	uint32_t _dwColorMatch(IDirectDrawSurface7 * pdds4, uint16_t wColorKey);
	uint32_t _dwColorMatch(IDirectDrawSurface7 * pdds4, COLORREF rgb);
	long _CalcMinValue(int iS, int iD, char cMode);
	long _CalcMaxValue(int iS, int iD, char cMode, char cMethod, double dAlpha);
	HRESULT iSetColorKey(IDirectDrawSurface7 * pdds4, uint16_t wColorKey);
	void PutPixel(short sX, short sY, uint16_t wR, uint16_t wG, uint16_t wB);
	void DrawShadowBox(short sX, short sY, short dX, short dY, int iType = 0);
	void ClearBackB4();
	IDirectDrawSurface7 * pCreateOffScreenSurface(uint16_t iSzX, uint16_t iSzY);
	HRESULT iSetColorKey(IDirectDrawSurface7 * pdds4, COLORREF rgb);
	HRESULT iFlip();
	bool Screenshot(LPCTSTR FileName, LPDIRECTDRAWSURFACE7 lpDDS);
	
	long    m_lTransG100[64][64], m_lTransRB100[64][64];
	long    m_lTransG70[64][64], m_lTransRB70[64][64];
	long    m_lTransG50[64][64], m_lTransRB50[64][64];
	long    m_lTransG25[64][64], m_lTransRB25[64][64];
	long    m_lTransG2[64][64], m_lTransRB2[64][64];
	long    m_lFadeG[64][64],  m_lFadeRB[64][64];

	bool m_bFullMode;

	LPDIRECTDRAW7		 m_lpDD4;
	LPDIRECTDRAWSURFACE7 m_lpFrontB4, m_lpBackB4, m_lpBackB4flip;
	LPDIRECTDRAWSURFACE7 m_lpPDBGS;// Pre-Draw Background Surface
	uint16_t * m_pBackB4Addr;
	RECT  m_rcClipArea, m_rcFlipping;
	short  m_sBackB4Pitch;
	char   m_cPixelFormat;
	HDC m_hDC;
	HFONT m_hFontInUse;
	int res_x;
	int res_y;
	int res_x_mid;
	int res_y_mid;
};
