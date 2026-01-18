#include "InputManager.h"
#include <cstring>

InputManager& InputManager::Get()
{
	static InputManager s_instance;
	return s_instance;
}

InputManager::InputManager()
	: m_hWnd(nullptr)
	, m_active(false)
	, m_mouseX(0)
	, m_mouseY(0)
	, m_wheelDelta(0)
	, m_leftDown(false)
	, m_rightDown(false)
	, m_leftPressed(false)
	, m_rightPressed(false)
	, m_leftReleased(false)
	, m_rightReleased(false)
{
	std::memset(m_keyDown, 0, sizeof(m_keyDown));
	std::memset(m_keyPressed, 0, sizeof(m_keyPressed));
	std::memset(m_keyReleased, 0, sizeof(m_keyReleased));
}

InputManager::~InputManager() = default;

void InputManager::Initialize(HWND hWnd)
{
	m_hWnd = hWnd;
	UpdateCursorClip(false);

	if (m_hWnd && GetForegroundWindow() == m_hWnd) {
		SetActive(true);
	}
}

void InputManager::SetActive(bool active)
{
	m_active = active;
	UpdateCursorClip(active);
	if (!active) {
		ClearAllKeys();
	}
}

void InputManager::BeginFrame()
{
	m_leftPressed = false;
	m_rightPressed = false;
	m_leftReleased = false;
	m_rightReleased = false;
	m_wheelDelta = 0;
	std::memset(m_keyPressed, 0, sizeof(m_keyPressed));
	std::memset(m_keyReleased, 0, sizeof(m_keyReleased));
}

void InputManager::OnMouseMove(int x, int y)
{
	UpdateLogicalPosition(x, y);
}

void InputManager::OnMouseDown(int button)
{
	if (button == 0) {
		if (!m_leftDown) {
			m_leftPressed = true;
		}
		m_leftDown = true;
	}
	else if (button == 1) {
		if (!m_rightDown) {
			m_rightPressed = true;
		}
		m_rightDown = true;
	}

	if (m_hWnd) {
		SetCapture(m_hWnd);
	}
}

void InputManager::OnMouseUp(int button)
{
	if (button == 0) {
		if (m_leftDown) {
			m_leftReleased = true;
		}
		m_leftDown = false;
	}
	else if (button == 1) {
		if (m_rightDown) {
			m_rightReleased = true;
		}
		m_rightDown = false;
	}

	if (!m_leftDown && !m_rightDown && GetCapture() == m_hWnd) {
		ReleaseCapture();
	}
}

void InputManager::OnMouseWheel(int delta, int x, int y)
{
	UpdateLogicalPosition(x, y);
	m_wheelDelta = static_cast<short>(m_wheelDelta + delta);
}

void InputManager::OnKeyDown(int vk)
{
	if (vk < 0 || vk >= kKeyCount) {
		return;
	}
	m_keyPressed[vk] = true;
	m_keyDown[vk] = true;
}

void InputManager::OnKeyUp(int vk)
{
	if (vk < 0 || vk >= kKeyCount) {
		return;
	}
	if (m_keyDown[vk]) {
		m_keyReleased[vk] = true;
	}
	m_keyDown[vk] = false;
}

bool InputManager::IsLeftMouseDown() const
{
	return m_leftDown;
}

bool InputManager::IsLeftMousePressed() const
{
	return m_leftPressed;
}

bool InputManager::IsLeftMouseReleased() const
{
	return m_leftReleased;
}

bool InputManager::IsRightMouseDown() const
{
	return m_rightDown;
}

bool InputManager::IsRightMousePressed() const
{
	return m_rightPressed;
}

bool InputManager::IsRightMouseReleased() const
{
	return m_rightReleased;
}

bool InputManager::IsKeyDown(int vk) const
{
	if (vk < 0 || vk >= kKeyCount) {
		return false;
	}
	return m_keyDown[vk];
}

bool InputManager::IsKeyPressed(int vk) const
{
	if (vk < 0 || vk >= kKeyCount) {
		return false;
	}
	return m_keyPressed[vk];
}

bool InputManager::IsKeyReleased(int vk) const
{
	if (vk < 0 || vk >= kKeyCount) {
		return false;
	}
	return m_keyReleased[vk];
}

bool InputManager::ConsumeKeyPressed(int vk)
{
	if (vk < 0 || vk >= kKeyCount) {
		return false;
	}
	if (!m_keyPressed[vk]) {
		return false;
	}
	m_keyPressed[vk] = false;
	return true;
}

void InputManager::ClearKeyPressed(int vk)
{
	if (vk < 0 || vk >= kKeyCount) {
		return;
	}
	m_keyPressed[vk] = false;
}

void InputManager::ClearAllKeys()
{
	std::memset(m_keyDown, 0, sizeof(m_keyDown));
	std::memset(m_keyPressed, 0, sizeof(m_keyPressed));
	std::memset(m_keyReleased, 0, sizeof(m_keyReleased));
}

bool InputManager::IsCtrlDown() const
{
	return IsKeyDown(VK_CONTROL);
}

bool InputManager::IsShiftDown() const
{
	return IsKeyDown(VK_SHIFT);
}

bool InputManager::IsAltDown() const
{
	return IsKeyDown(VK_MENU);
}

bool InputManager::IsEnterPressed() const
{
	return IsKeyPressed(VK_RETURN);
}

bool InputManager::IsEscPressed() const
{
	return IsKeyPressed(VK_ESCAPE);
}

void InputManager::SetEnterPressed()
{
	m_keyPressed[VK_RETURN] = true;
}

void InputManager::SetEscPressed()
{
	m_keyPressed[VK_ESCAPE] = true;
}

void InputManager::ClearEnterPressed()
{
	ClearKeyPressed(VK_RETURN);
}

void InputManager::ClearEscPressed()
{
	ClearKeyPressed(VK_ESCAPE);
}

short InputManager::GetMouseX() const
{
	return m_mouseX;
}

short InputManager::GetMouseY() const
{
	return m_mouseY;
}

short InputManager::GetWheelDelta() const
{
	return m_wheelDelta;
}

short InputManager::ConsumeWheelDelta()
{
	short delta = m_wheelDelta;
	m_wheelDelta = 0;
	return delta;
}

void InputManager::ClearWheelDelta()
{
	m_wheelDelta = 0;
}

void InputManager::SetMousePosition(short x, short y)
{
	m_mouseX = x;
	m_mouseY = y;
}

void InputManager::GetLegacyState(short* pX, short* pY, short* pZ, char* pLB, char* pRB) const
{
	if (pX) *pX = m_mouseX;
	if (pY) *pY = m_mouseY;
	if (pZ) *pZ = m_wheelDelta;
	if (pLB) *pLB = m_leftDown ? 1 : 0;
	if (pRB) *pRB = m_rightDown ? 1 : 0;
}

void InputManager::UpdateLogicalPosition(int clientX, int clientY)
{
	if (!m_hWnd) {
		m_mouseX = static_cast<short>(clientX);
		m_mouseY = static_cast<short>(clientY);
		return;
	}

	RECT rcClient{};
	GetClientRect(m_hWnd, &rcClient);
	int winW = rcClient.right - rcClient.left;
	int winH = rcClient.bottom - rcClient.top;
	if (winW <= 0 || winH <= 0) {
		return;
	}

	double scale = static_cast<double>(winW) / static_cast<double>(LOGICAL_WIDTH);
	double scaleY = static_cast<double>(winH) / static_cast<double>(LOGICAL_HEIGHT);
	if (scaleY < scale) {
		scale = scaleY;
	}
	if (scale <= 0.0) {
		scale = 1.0;
	}

	int destW = static_cast<int>(LOGICAL_WIDTH * scale);
	int destH = static_cast<int>(LOGICAL_HEIGHT * scale);
	int offsetX = (winW - destW) / 2;
	int offsetY = (winH - destH) / 2;

	long scaledX = static_cast<long>((clientX - offsetX) / scale);
	long scaledY = static_cast<long>((clientY - offsetY) / scale);

	if (scaledX < 0) scaledX = 0;
	if (scaledY < 0) scaledY = 0;
	if (scaledX > LOGICAL_MAX_X) scaledX = LOGICAL_MAX_X;
	if (scaledY > LOGICAL_MAX_Y) scaledY = LOGICAL_MAX_Y;

	m_mouseX = static_cast<short>(scaledX);
	m_mouseY = static_cast<short>(scaledY);
}

void InputManager::UpdateCursorClip(bool active)
{
	if (!m_hWnd) {
		return;
	}

	if (active) {
		RECT rcClient{};
		GetClientRect(m_hWnd, &rcClient);
		int winW = rcClient.right - rcClient.left;
		int winH = rcClient.bottom - rcClient.top;
		double scale = static_cast<double>(winW) / static_cast<double>(LOGICAL_WIDTH);
		double scaleY = static_cast<double>(winH) / static_cast<double>(LOGICAL_HEIGHT);
		if (scaleY < scale) {
			scale = scaleY;
		}
		if (scale <= 0.0) {
			scale = 1.0;
		}
		int destW = static_cast<int>(LOGICAL_WIDTH * scale);
		int destH = static_cast<int>(LOGICAL_HEIGHT * scale);
		int offsetX = (winW - destW) / 2;
		int offsetY = (winH - destH) / 2;

		POINT ptTopLeft{ offsetX, offsetY };
		POINT ptBottomRight{ offsetX + destW, offsetY + destH };
		ClientToScreen(m_hWnd, &ptTopLeft);
		ClientToScreen(m_hWnd, &ptBottomRight);
		RECT rcClip{ ptTopLeft.x, ptTopLeft.y, ptBottomRight.x, ptBottomRight.y };
		ClipCursor(&rcClip);
	}
	else {
		ClipCursor(nullptr);
	}
}
