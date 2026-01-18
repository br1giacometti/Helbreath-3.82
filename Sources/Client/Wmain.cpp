// -------------------------------------------------------------- 
//                      Helbreath Client 						  
//
//                      1998.10 by Soph
//
// --------------------------------------------------------------


// MODERNIZED: Prevent old winsock.h from loading (must be before windows.h)
#define _WINSOCKAPI_

#include <windows.h>
#include "CommonTypes.h"
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <winbase.h>
#include <mmsystem.h>
#include <process.h>
#include "XSocket.h"
#include "Game.h"
#include "GlobalDef.h"
#include "resource.h"
#include "FrameTiming.h"
#include "ConfigManager.h"
#include "InputManager.h"

// --------------------------------------------------------------
#define WM_USER_TIMERSIGNAL		WM_USER + 500
#define WM_USER_CALCSOCKETEVENT WM_USER + 600

int G_iAddTable31[64][510], G_iAddTable63[64][510];
int G_iAddTransTable31[510][64], G_iAddTransTable63[510][64];

long G_lTransG100[64][64], G_lTransRB100[64][64];
long G_lTransG70[64][64], G_lTransRB70[64][64];
long G_lTransG50[64][64], G_lTransRB50[64][64];
long G_lTransG25[64][64], G_lTransRB25[64][64];
long G_lTransG2[64][64], G_lTransRB2[64][64];

char szAppClass[32];
HWND G_hWnd = 0;
HWND G_hEditWnd = 0;
HINSTANCE G_hInstance = 0;
MMRESULT G_mmTimer;
char G_cSpriteAlphaDegree;
class CGame* G_pGame;
class XSocket* G_pCalcSocket = 0;
bool G_bIsCalcSocketConnected = true;
	uint32_t G_dwCalcSocketTime = 0, G_dwCalcSocketSendTime = 0;

char G_cCmdLine[256], G_cCmdLineTokenA[120], G_cCmdLineTokenA_Lowercase[120], G_cCmdLineTokenB[120], G_cCmdLineTokenC[120], G_cCmdLineTokenD[120], G_cCmdLineTokenE[120];

BOOL InitApplication(HINSTANCE hInstance);
bool InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void EventLoop();
void OnDestroy();
void Initialize(char* pCmdLine);
void CALLBACK _TimerFunc(UINT wID, UINT wUser, DWORD dwUSer, DWORD dw1, DWORD dw2);

MMRESULT _StartTimer(DWORD dwTime);
void _StopTimer(MMRESULT timerid);

// --------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (G_pGame->GetText(hWnd, message, wParam, lParam)) return 0;

	switch (message) {
	case WM_USER_CALCSOCKETEVENT:
		G_pGame->_CalcSocketClosed();
		break;

	case WM_CLOSE:
		if ((G_pGame->m_cGameMode == DEF_GAMEMODE_ONMAINGAME) && (G_pGame->m_bForceDisconn == false))
		{

#ifdef _DEBUG
			if (G_pGame->m_cLogOutCount == -1 || G_pGame->m_cLogOutCount > 2) G_pGame->m_cLogOutCount = 1;
#else
			if (G_pGame->m_cLogOutCount == -1 || G_pGame->m_cLogOutCount > 11) G_pGame->m_cLogOutCount = 11;
#endif

		}
		else if (G_pGame->m_cGameMode == DEF_GAMEMODE_ONLOADING) return (DefWindowProc(hWnd, message, wParam, lParam));
		else if (G_pGame->m_cGameMode == DEF_GAMEMODE_ONMAINMENU) G_pGame->ChangeGameMode(DEF_GAMEMODE_ONQUIT);
		break;

	case WM_SYSCOMMAND:
		if ((wParam & 0xFFF0) == SC_SCREENSAVE || (wParam & 0xFFF0) == SC_MONITORPOWER)
			return 0;
		return DefWindowProc(hWnd, message, wParam, lParam);

	case WM_USER_TIMERSIGNAL:
		G_pGame->OnTimer();
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SHIFT:
			InputManager::Get().OnKeyDown(VK_SHIFT);
			return (DefWindowProc(hWnd, message, wParam, lParam));
		case VK_CONTROL:
			InputManager::Get().OnKeyDown(VK_CONTROL);
			return (DefWindowProc(hWnd, message, wParam, lParam));
		case VK_INSERT:
		case VK_DELETE:
		case VK_TAB:
		case VK_RETURN:
		case VK_ESCAPE:
		case VK_END:
		case VK_HOME:
		case VK_F1:
		case VK_F2:
		case VK_F3:
		case VK_F4:
		case VK_F5:
		case VK_F6:
		case VK_F7:
		case VK_F8:
		case VK_F9:
		case VK_F10:
		case VK_F11:
		case VK_F12:
		case VK_PRIOR: // Page-Up
		case VK_NEXT: // Page-Down
		case VK_LWIN:
		case VK_RWIN:
		case VK_MULTIPLY:
		case VK_ADD: //'+'
		case VK_SEPARATOR:
		case VK_SUBTRACT: //'-'
		case VK_DECIMAL:
		case VK_DIVIDE:
		case VK_NUMLOCK:
		case VK_SCROLL:
			return (DefWindowProc(hWnd, message, wParam, lParam));
		}
		G_pGame->OnKeyDown(wParam);
		return (DefWindowProc(hWnd, message, wParam, lParam));

	case WM_KEYUP:
		switch (wParam)
		{
		case VK_SHIFT:
			InputManager::Get().OnKeyUp(VK_SHIFT);
			return (DefWindowProc(hWnd, message, wParam, lParam));
		case VK_CONTROL:
			InputManager::Get().OnKeyUp(VK_CONTROL);
			return (DefWindowProc(hWnd, message, wParam, lParam));
		case VK_RETURN:
			InputManager::Get().OnKeyUp(VK_RETURN);
			InputManager::Get().SetEnterPressed();
			return (DefWindowProc(hWnd, message, wParam, lParam));
		}
		G_pGame->OnKeyUp(wParam);
		return (DefWindowProc(hWnd, message, wParam, lParam));

	case WM_SYSKEYDOWN:
		switch (wParam)
		{
		case VK_SHIFT:
			InputManager::Get().OnKeyDown(VK_SHIFT);
			break;
		case VK_CONTROL:
			InputManager::Get().OnKeyDown(VK_CONTROL);
			break;
		case VK_MENU:
			InputManager::Get().OnKeyDown(VK_MENU);
			break;
		case VK_RETURN:
			InputManager::Get().OnKeyDown(VK_RETURN);
			break;
		}
		return (DefWindowProc(hWnd, message, wParam, lParam));

	case WM_SYSKEYUP:
		switch (wParam)
		{
		case VK_SHIFT:
			InputManager::Get().OnKeyUp(VK_SHIFT);
			break;
		case VK_CONTROL:
			InputManager::Get().OnKeyUp(VK_CONTROL);
			break;
		case VK_MENU:
			InputManager::Get().OnKeyUp(VK_MENU);
			break;
		case VK_RETURN:
			InputManager::Get().OnKeyUp(VK_RETURN);
			InputManager::Get().ClearEnterPressed();
			break;
		case VK_ESCAPE:
			InputManager::Get().OnKeyUp(VK_ESCAPE);
			InputManager::Get().ClearEscPressed();
			break;
		}
		return (DefWindowProc(hWnd, message, wParam, lParam));

	case WM_ACTIVATEAPP:
		if (wParam == 0)
		{
			G_pGame->m_bIsProgramActive = false;
			InputManager::Get().SetActive(false);
		}
		else
		{
			G_pGame->m_bIsProgramActive = true;
			InputManager::Get().SetActive(true);
			InputManager::Get().ClearAllKeys();

			G_pGame->m_bIsRedrawPDBGS = true;
			G_pGame->m_DDraw.ChangeDisplayMode(G_hWnd);

			if (G_pGame->bCheckImportantFile() == false)
			{
				MessageBox(G_pGame->m_hWnd, "File checksum error! Get Update again please!", "ERROR1", MB_ICONEXCLAMATION | MB_OK);
				PostQuitMessage(0);
				return 0;
			}
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_SETFOCUS:
		InputManager::Get().SetActive(true);
		break;

	case WM_KILLFOCUS:
		InputManager::Get().SetActive(false);
		break;

	case WM_MOUSEMOVE:
		InputManager::Get().OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK: // Handle double-click as button down for manual detection
		InputManager::Get().OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		InputManager::Get().OnMouseDown(0);
		break;

	case WM_LBUTTONUP:
		InputManager::Get().OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		InputManager::Get().OnMouseUp(0);
		break;

	case WM_RBUTTONDOWN:
		InputManager::Get().OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		InputManager::Get().OnMouseDown(1);
		break;

	case WM_RBUTTONUP:
		InputManager::Get().OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		InputManager::Get().OnMouseUp(1);
		break;

	case WM_MOUSEWHEEL:
	{
		POINT pt{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		ScreenToClient(hWnd, &pt);
		InputManager::Get().OnMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam), pt.x, pt.y);
		break;
	}

	case WM_SETCURSOR:
		SetCursor(0);
		return true;

	case WM_DESTROY:
		OnDestroy();
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;

	// MODERNIZED: Removed WM_USER_GAMESOCKETEVENT and WM_USER_LOGSOCKETEVENT handlers
	// Sockets now polled directly in UpdateScreen_OnGame() instead of window messages

	default:
		return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return 0;
}

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	srand((unsigned)time(0));

	// Ensure consistent pixel coordinates under RDP and high-DPI setups.
	// Try per-monitor v2 first, then fall back to system DPI aware on older OS.
	if (!SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
		SetProcessDPIAware();
	}

	// Load settings early so window size is available
	ConfigManager::Get().Initialize();
	ConfigManager::Get().Load();

	G_pGame = new class CGame;

	sprintf(szAppClass, "Client-I%d", (int)hInstance);
	if (!InitApplication(hInstance))		return (false);
	if (!InitInstance(hInstance, nCmdShow)) return (false);

	Initialize((char*)lpCmdLine);

	EventLoop();

	delete G_pGame;

	return 0;
}

BOOL InitApplication(HINSTANCE hInstance)
{
	WNDCLASS  wc;
	wc.style = (CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS);
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = sizeof(int);
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = 0;
	wc.lpszClassName = szAppClass;
	return (RegisterClass(&wc));
}

bool InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	int windowWidth = ConfigManager::Get().GetWindowWidth();
	int windowHeight = ConfigManager::Get().GetWindowHeight();

	int cx = GetSystemMetrics(SM_CXFULLSCREEN) / 2;
	int cy = GetSystemMetrics(SM_CYFULLSCREEN) / 2;
	if (cy > 340) cy += 40;
	G_hWnd = CreateWindowEx(0, szAppClass, "Helbreath", WS_POPUP,
		cx - (windowWidth / 2), cy - (windowHeight / 2),
		windowWidth, windowHeight, 0, 0, hInstance, 0);
	if (!G_hWnd) return false;
	G_hInstance = hInstance;
	ShowWindow(G_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(G_hWnd);
	return true;
}


void EventLoop()
{
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, 0, 0, 0)) return;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (G_pGame->m_bIsProgramActive)
		{
			FrameTiming::BeginFrame();
			G_pGame->RenderFrame();  // Centralized: Clear -> UpdateScreen -> Flip
			InputManager::Get().BeginFrame();
			FrameTiming::EndFrame();
		}
		else if (G_pGame->m_cGameMode == DEF_GAMEMODE_ONLOADING)
		{
			FrameTiming::BeginFrame();
			G_pGame->RenderFrame();  // Use RenderFrame for loading too
			InputManager::Get().BeginFrame();
			FrameTiming::EndFrame();
		}
		else WaitMessage();
	}
}

void OnDestroy()
{
	G_pGame->m_bIsProgramActive = false;
	_StopTimer(G_mmTimer);
	G_pGame->Quit();
	WSACleanup();
	PostQuitMessage(0);
}

void CALLBACK _TimerFunc(UINT wID, UINT wUser, DWORD dwUSer, DWORD dw1, DWORD dw2)
{
	PostMessage(G_hWnd, WM_USER_TIMERSIGNAL, wID, 0);
}


MMRESULT _StartTimer(DWORD dwTime)
{
	TIMECAPS caps;
	timeGetDevCaps(&caps, sizeof(caps));
	timeBeginPeriod(caps.wPeriodMin);
	return timeSetEvent(dwTime, 0, _TimerFunc, 0, (UINT)TIME_PERIODIC);
}


void _StopTimer(MMRESULT timerid)
{
	TIMECAPS caps;
	if (timerid != 0)
	{
		timeKillEvent(timerid);
		timerid = 0;
		timeGetDevCaps(&caps, sizeof(caps));
		timeEndPeriod(caps.wPeriodMin);
	}
}


void Initialize(char* pCmdLine)
{
	int iX, iY, iSum;
	int     iErrCode;
	uint16_t wVersionRequested;
	WSADATA wsaData;

	// Initialize timing systems
	FrameTiming::Initialize();

	wVersionRequested = MAKEWORD(2, 2);
	iErrCode = WSAStartup(wVersionRequested, &wsaData);
	if (iErrCode)
	{
		MessageBox(G_hWnd, "Winsock-V2.2 not found! Cannot execute program.", "ERROR", MB_ICONEXCLAMATION | MB_OK);
		PostQuitMessage(0);
		return;
	}
	if (G_pGame->bInit(G_hWnd, G_hInstance, pCmdLine) == false)
	{
		PostQuitMessage(0);
		return;
	}
	G_mmTimer = _StartTimer(1000);
	for (iX = 0; iX < 64; iX++)
		for (iY = 0; iY < 510; iY++)
		{
			iSum = iX + (iY - 255);
			if (iSum <= 0)  iSum = 1;
			if (iSum >= 31) iSum = 31;
			G_iAddTable31[iX][iY] = iSum;
			iSum = iX + (iY - 255);
			if (iSum <= 0)  iSum = 1;
			if (iSum >= 63) iSum = 63;
			G_iAddTable63[iX][iY] = iSum;
			if ((iY - 255) < iX) G_iAddTransTable31[iY][iX] = iX;
			else if ((iY - 255) > 31) G_iAddTransTable31[iY][iX] = 31;
			else G_iAddTransTable31[iY][iX] = iY - 255;
			if ((iY - 255) < iX) G_iAddTransTable63[iY][iX] = iX;
			else if ((iY - 255) > 63) G_iAddTransTable63[iY][iX] = 63;
			else G_iAddTransTable63[iY][iX] = iY - 255;
		}
}
