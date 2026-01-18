// winmain.h

#pragma once

#include "CommonTypes.h"

#ifdef _WIN32
// Log levels
#define LOG_LEVEL_INFO 0
#define LOG_LEVEL_NOTICE 1
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_ERROR 3

//void OnBotAccept();
void PutXSocketLogList(char* cMsg);
void PutXSocketLogFileList(char* cMsg);
bool InitApplication(HINSTANCE hInstance);
bool InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void OnAccept();
void OnAcceptLogin();
void PutLogList(char* cMsg);
void PutLogListLevel(int level, const char* cMsg);
void OnKeyUp(WPARAM wParam, LPARAM lParam);
void UpdateScreen();
int  EventLoop();
void OnPaint();
void OnDestroy();
void Initialize();
void CALLBACK _TimerFunc(UINT wID, UINT wUser, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
MMRESULT _StartTimer(uint32_t dwTime);
void _StopTimer(MMRESULT timerid);
#endif
