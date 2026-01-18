#pragma once

// Prevent winsock.h conflicts when windows.h is included here.
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif

#include <windows.h>
#include "GlobalDef.h"

class InputManager
{
public:
	static InputManager& Get();

	void Initialize(HWND hWnd);
	void SetActive(bool active);
	void BeginFrame();

	void OnMouseMove(int x, int y);
	void OnMouseDown(int button);
	void OnMouseUp(int button);
	void OnMouseWheel(int delta, int x, int y);
	void OnKeyDown(int vk);
	void OnKeyUp(int vk);

	bool IsLeftMouseDown() const;
	bool IsLeftMousePressed() const;
	bool IsLeftMouseReleased() const;
	bool IsRightMouseDown() const;
	bool IsRightMousePressed() const;
	bool IsRightMouseReleased() const;
	bool IsKeyDown(int vk) const;
	bool IsKeyPressed(int vk) const;
	bool IsKeyReleased(int vk) const;
	bool ConsumeKeyPressed(int vk);
	void ClearKeyPressed(int vk);
	void ClearAllKeys();
	bool IsCtrlDown() const;
	bool IsShiftDown() const;
	bool IsAltDown() const;
	bool IsEnterPressed() const;
	bool IsEscPressed() const;
	void SetEnterPressed();
	void SetEscPressed();
	void ClearEnterPressed();
	void ClearEscPressed();

	short GetMouseX() const;
	short GetMouseY() const;
	short GetWheelDelta() const;
	short ConsumeWheelDelta();
	void ClearWheelDelta();
	void SetMousePosition(short x, short y);

	void GetLegacyState(short* pX, short* pY, short* pZ, char* pLB, char* pRB) const;

private:
	InputManager();
	~InputManager();
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	void UpdateLogicalPosition(int clientX, int clientY);
	void UpdateCursorClip(bool active);

	HWND m_hWnd;
	bool m_active;

	short m_mouseX;
	short m_mouseY;
	short m_wheelDelta;
	bool m_leftDown;
	bool m_rightDown;
	bool m_leftPressed;
	bool m_rightPressed;
	bool m_leftReleased;
	bool m_rightReleased;

	static constexpr int kKeyCount = 256;
	bool m_keyDown[kKeyCount];
	bool m_keyPressed[kKeyCount];
	bool m_keyReleased[kKeyCount];
};
