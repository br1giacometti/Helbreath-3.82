#include "DialogBox_SysMenu.h"
#include "InputManager.h"
#include "Game.h"
#include "GlobalDef.h"
#include "lan_eng.h"
#include "AudioManager.h"
#include "CommonTypes.h"
#include "ConfigManager.h"
#include <cstring>

extern HWND G_hWnd;

// 4:3 resolutions from 640x480 to 1440x1080
const Resolution DialogBox_SysMenu::s_Resolutions[] = {
	{ 640, 480 },
	{ 800, 600 },
	{ 1024, 768 },
	{ 1280, 960 },
	{ 1440, 1080 }
};

const int DialogBox_SysMenu::s_NumResolutions = sizeof(s_Resolutions) / sizeof(s_Resolutions[0]);

int DialogBox_SysMenu::GetCurrentResolutionIndex()
{
	int currentWidth = ConfigManager::Get().GetWindowWidth();
	int currentHeight = ConfigManager::Get().GetWindowHeight();

	for (int i = 0; i < s_NumResolutions; i++) {
		if (s_Resolutions[i].width == currentWidth && s_Resolutions[i].height == currentHeight) {
			return i;
		}
	}
	return GetNearestResolutionIndex(currentWidth, currentHeight);
}

int DialogBox_SysMenu::GetNearestResolutionIndex(int width, int height)
{
	int bestIndex = 0;
	int bestDiff = abs(s_Resolutions[0].width - width) + abs(s_Resolutions[0].height - height);

	for (int i = 1; i < s_NumResolutions; i++) {
		int diff = abs(s_Resolutions[i].width - width) + abs(s_Resolutions[i].height - height);
		if (diff < bestDiff) {
			bestDiff = diff;
			bestIndex = i;
		}
	}
	return bestIndex;
}

void DialogBox_SysMenu::CycleResolution()
{
	int currentIndex = GetCurrentResolutionIndex();
	int nextIndex = (currentIndex + 1) % s_NumResolutions;
	ApplyResolution(nextIndex);
}

void DialogBox_SysMenu::ApplyResolution(int index)
{
	if (index < 0 || index >= s_NumResolutions) return;

	int newWidth = s_Resolutions[index].width;
	int newHeight = s_Resolutions[index].height;

	// Update config
	ConfigManager::Get().SetWindowSize(newWidth, newHeight);
	ConfigManager::Get().Save();

	// Get screen dimensions for centering
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Calculate centered position
	int newX = (screenWidth - newWidth) / 2;
	int newY = (screenHeight - newHeight) / 2;

	// Resize and center the window
	SetWindowPos(G_hWnd, HWND_TOP, newX, newY, newWidth, newHeight, SWP_SHOWWINDOW);
	InputManager::Get().SetActive(true);
}

DialogBox_SysMenu::DialogBox_SysMenu(CGame* pGame)
	: IDialogBox(DialogBoxId::SystemMenu, pGame)
{
	SetDefaultRect(337 + SCREENX, 107 + SCREENY, 258, 268);
}

void DialogBox_SysMenu::DrawDetailLevel(short sX, short sY)
{
	const int detailLevel = ConfigManager::Get().GetDetailLevel();
	PutString(sX + 23, sY + 63, DRAW_DIALOGBOX_SYSMENU_DETAILLEVEL, RGB(45, 25, 25));
	PutString(sX + 24, sY + 63, DRAW_DIALOGBOX_SYSMENU_DETAILLEVEL, RGB(45, 25, 25));

	if (detailLevel == 0)
		PutString(sX + 121, sY + 63, DRAW_DIALOGBOX_SYSMENU_LOW, RGB(255, 255, 255));
	else PutString(sX + 121, sY + 63, DRAW_DIALOGBOX_SYSMENU_LOW, RGB(45, 25, 25));

	if (detailLevel == 1)
		PutString(sX + 153, sY + 63, DRAW_DIALOGBOX_SYSMENU_NORMAL, RGB(255, 255, 255));
	else PutString(sX + 153, sY + 63, DRAW_DIALOGBOX_SYSMENU_NORMAL, RGB(45, 25, 25));

	if (detailLevel == 2)
		PutString(sX + 205, sY + 63, DRAW_DIALOGBOX_SYSMENU_HIGH, RGB(255, 255, 255));
	else PutString(sX + 205, sY + 63, DRAW_DIALOGBOX_SYSMENU_HIGH, RGB(45, 25, 25));
}

void DialogBox_SysMenu::DrawSoundSettings(short sX, short sY)
{
	PutString(sX + 23, sY + 84, DRAW_DIALOGBOX_SYSMENU_SOUND, RGB(45, 25, 25));
	PutString(sX + 24, sY + 84, DRAW_DIALOGBOX_SYSMENU_SOUND, RGB(45, 25, 25));

	if (AudioManager::Get().IsSoundAvailable()) {
		if (AudioManager::Get().IsSoundEnabled())
			PutString(sX + 85, sY + 85, DRAW_DIALOGBOX_SYSMENU_ON, RGB(255, 255, 255));
		else
			PutString(sX + 83, sY + 85, DRAW_DIALOGBOX_SYSMENU_OFF, RGB(200, 200, 200));
	}
	else PutString(sX + 68, sY + 85, DRAW_DIALOGBOX_SYSMENU_DISABLED, RGB(100, 100, 100));

	PutString(sX + 123, sY + 84, DRAW_DIALOGBOX_SYSMENU_MUSIC, RGB(45, 25, 25));
	PutString(sX + 124, sY + 84, DRAW_DIALOGBOX_SYSMENU_MUSIC, RGB(45, 25, 25));

	if (AudioManager::Get().IsSoundAvailable()) {
		if (AudioManager::Get().IsMusicEnabled())
			PutString(sX + 180, sY + 85, DRAW_DIALOGBOX_SYSMENU_ON, RGB(255, 255, 255));
		else
			PutString(sX + 178, sY + 85, DRAW_DIALOGBOX_SYSMENU_OFF, RGB(200, 200, 200));
	}
	else PutString(sX + 163, sY + 85, DRAW_DIALOGBOX_SYSMENU_DISABLED, RGB(100, 100, 100));
}

void DialogBox_SysMenu::DrawChatSettings(short sX, short sY)
{
	PutString(sX + 23, sY + 106, DRAW_DIALOGBOX_SYSMENU_WHISPER, RGB(45, 25, 25));
	PutString(sX + 24, sY + 106, DRAW_DIALOGBOX_SYSMENU_WHISPER, RGB(45, 25, 25));

	if (m_pGame->m_bWhisper)
		PutString(sX + 85, sY + 106, DRAW_DIALOGBOX_SYSMENU_ON, RGB(255, 255, 255));
	else
		PutString(sX + 82, sY + 106, DRAW_DIALOGBOX_SYSMENU_OFF, RGB(200, 200, 200));

	PutString(sX + 123, sY + 106, DRAW_DIALOGBOX_SYSMENU_SHOUT, RGB(45, 25, 25));
	PutString(sX + 124, sY + 106, DRAW_DIALOGBOX_SYSMENU_SHOUT, RGB(45, 25, 25));

	if (m_pGame->m_bShout)
		PutString(sX + 180, sY + 106, DRAW_DIALOGBOX_SYSMENU_ON, RGB(255, 255, 255));
	else
		PutString(sX + 177, sY + 106, DRAW_DIALOGBOX_SYSMENU_OFF, RGB(200, 200, 200));
}

void DialogBox_SysMenu::DrawVolumeSliders(short sX, short sY, short msX, short msY, char cLB)
{
	PutString(sX + 23, sY + 124, DRAW_DIALOGBOX_SYSMENU_SOUNDVOLUME, RGB(45, 25, 25));
	PutString(sX + 24, sY + 124, DRAW_DIALOGBOX_SYSMENU_SOUNDVOLUME, RGB(45, 25, 25));
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX + 130 + AudioManager::Get().GetSoundVolume(), sY + 129, 8);

	PutString(sX + 23, sY + 141, DRAW_DIALOGBOX_SYSMENU_MUSICVOLUME, RGB(45, 25, 25));
	PutString(sX + 24, sY + 141, DRAW_DIALOGBOX_SYSMENU_MUSICVOLUME, RGB(45, 25, 25));
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX + 130 + AudioManager::Get().GetMusicVolume(), sY + 145, 8);

	// Handle slider dragging
	if ((cLB != 0) && (m_pGame->m_dialogBoxManager.iGetTopDialogBoxIndex() == DialogBoxId::SystemMenu)) {
		if ((msX >= sX + 127) && (msX <= sX + 238) && (msY >= sY + 122) && (msY <= sY + 138)) {
			int volume = msX - (sX + 127);
			if (volume > 100) volume = 100;
			if (volume < 0) volume = 0;
			AudioManager::Get().SetSoundVolume(volume);
		}
		if ((msX >= sX + 127) && (msX <= sX + 238) && (msY >= sY + 139) && (msY <= sY + 155)) {
			int volume = msX - (sX + 127);
			if (volume > 100) volume = 100;
			if (volume < 0) volume = 0;
			AudioManager::Get().SetMusicVolume(volume);
		}
	}
	else Info().bIsScrollSelected = false;
}

void DialogBox_SysMenu::DrawMiscSettings(short sX, short sY)
{
	PutString(sX + 23, sY + 158, DRAW_DIALOGBOX_SYSMENU_TRANSPARENCY, RGB(45, 25, 25));
	PutString(sX + 24, sY + 158, DRAW_DIALOGBOX_SYSMENU_TRANSPARENCY, RGB(45, 25, 25));

	if (ConfigManager::Get().IsDialogTransparencyEnabled())
		PutString(sX + 208, sY + 158, DRAW_DIALOGBOX_SYSMENU_ON, RGB(255, 255, 255));
	else
		PutString(sX + 207, sY + 158, DRAW_DIALOGBOX_SYSMENU_OFF, RGB(200, 200, 200));

	PutString(sX + 23, sY + 180, DRAW_DIALOGBOX_SYSMENU_GUIDEMAP, RGB(45, 25, 25));
	PutString(sX + 24, sY + 180, DRAW_DIALOGBOX_SYSMENU_GUIDEMAP, RGB(45, 25, 25));

	if (m_pGame->m_dialogBoxManager.IsEnabled(DialogBoxId::GuideMap))
		PutString(sX + 99, sY + 180, DRAW_DIALOGBOX_SYSMENU_ON, RGB(255, 255, 255));
	else
		PutString(sX + 98, sY + 180, DRAW_DIALOGBOX_SYSMENU_OFF, RGB(200, 200, 200));

	// Current time
	SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);
	std::memset(m_pGame->G_cTxt, 0, sizeof(m_pGame->G_cTxt));
	wsprintf(m_pGame->G_cTxt, "%d:%d:%d:%d:%d", SysTime.wMonth, SysTime.wDay, SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
	PutString(sX + 23, sY + 204, m_pGame->G_cTxt, RGB(45, 25, 25));
	PutString(sX + 24, sY + 204, m_pGame->G_cTxt, RGB(45, 25, 25));
}

void DialogBox_SysMenu::DrawServerName(short sX, short sY)
{
	PutString(sX + 23, sY + 41, UPDATE_SCREEN_ON_SELECT_CHARACTER36, RGB(45, 25, 25));
	PutString(sX + 24, sY + 41, UPDATE_SCREEN_ON_SELECT_CHARACTER36, RGB(45, 25, 25));
}

void DialogBox_SysMenu::DrawDisplayModeButtons(short sX, short sY, short msX, short msY)
{
	const bool isFullscreen = m_pGame->m_DDraw.m_bFullMode;
	const short modeY = sY + 204;
	const short windowedX = sX + 112;
	const short fullscreenX = sX + 182;

	const bool windowedHover = (msX >= sX + 110) && (msX <= sX + 168) && (msY >= sY + 200) && (msY <= sY + 213);
	const bool fullscreenHover = (msX >= sX + 180) && (msX <= sX + 242) && (msY >= sY + 200) && (msY <= sY + 213);

	COLORREF windowedColor = ((!isFullscreen) || windowedHover) ? RGB(255, 255, 255) : RGB(200, 200, 200);
	COLORREF fullscreenColor = (isFullscreen || fullscreenHover) ? RGB(255, 255, 255) : RGB(200, 200, 200);

	PutString(windowedX, modeY, "Windowed", windowedColor);
	PutString(fullscreenX, modeY, "Fullscreen", fullscreenColor);
}

void DialogBox_SysMenu::DrawButtons(short sX, short sY, short msX, short msY)
{
	// Log-Out button
	if (m_pGame->m_cLogOutCount == -1) {
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + 225) && (msY <= sY + 225 + DEF_BTNSZY))
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + 225, 9);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + 225, 8);
	}
	else {
		// Continue button
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + 225) && (msY <= sY + 225 + DEF_BTNSZY))
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + 225, 7);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + 225, 6);
	}

	// Restart button (only when dead)
	if ((m_pGame->m_iHP <= 0) && (m_pGame->m_cRestartCount == -1)) {
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 225) && (msY <= sY + 225 + DEF_BTNSZY))
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + 225, 37);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + 225, 36);
	}
	else if (m_pGame->m_cRestartCount == -1) {
		DrawDisplayModeButtons(sX, sY, msX, msY);
		// Resolution button (replaces credits)
		DrawResolutionButton(sX, sY, msX, msY);
	}
}

void DialogBox_SysMenu::DrawResolutionButton(short sX, short sY, short msX, short msY)
{
	const bool isFullscreen = m_pGame->m_DDraw.m_bFullMode;
	int resWidth = 0;
	int resHeight = 0;
	if (isFullscreen) {
		resWidth = GetSystemMetrics(SM_CXSCREEN);
		resHeight = GetSystemMetrics(SM_CYSCREEN);
	}
	else {
		int resIndex = GetCurrentResolutionIndex();
		resWidth = s_Resolutions[resIndex].width;
		resHeight = s_Resolutions[resIndex].height;
	}

	char cResText[32];
	wsprintf(cResText, "%dx%d", resWidth, resHeight);

	const short windowedX = sX + 112;
	const short fullscreenX = sX + 182;
	const int kCharWidth = 6;
	const int windowedWidth = 8 * kCharWidth;
	const int fullscreenWidth = 10 * kCharWidth;
	const int leftBound = windowedX;
	const int rightBound = fullscreenX + fullscreenWidth;
	const int textWidth = static_cast<int>(std::strlen(cResText)) * kCharWidth;
	const int textX = leftBound + ((rightBound - leftBound) / 2) - (textWidth / 2);
	const short textY = sY + 222;
	const bool bHover = !isFullscreen && (msX >= leftBound) && (msX <= rightBound) && (msY >= sY + 220) && (msY <= sY + 234);

	// Draw single-line resolution text (highlighted on hover)
	if (bHover) {
		PutString(textX, textY, cResText, RGB(255, 255, 255));
	}
	else {
		COLORREF color = isFullscreen ? RGB(150, 150, 150) : RGB(45, 25, 25);
		PutString(textX, textY, cResText, color);
		PutString(textX + 1, textY, cResText, color);
	}
}

void DialogBox_SysMenu::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME1, sX, sY, 0);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 6);

	DrawDetailLevel(sX, sY);
	DrawSoundSettings(sX, sY);
	DrawChatSettings(sX, sY);
	DrawVolumeSliders(sX, sY, msX, msY, cLB);
	DrawMiscSettings(sX, sY);
	DrawServerName(sX, sY);
	DrawButtons(sX, sY, msX, msY);
}

bool DialogBox_SysMenu::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;

	// Detail level: Low
	if ((msX >= sX + 120) && (msX <= sX + 150) && (msY >= sY + 63) && (msY <= sY + 74)) {
		ConfigManager::Get().SetDetailLevel(0);
		AddEventList(NOTIFY_MSG_DETAIL_LEVEL_LOW, 10);
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	// Detail level: Normal
	if ((msX >= sX + 151) && (msX <= sX + 200) && (msY >= sY + 63) && (msY <= sY + 74)) {
		ConfigManager::Get().SetDetailLevel(1);
		AddEventList(NOTIFY_MSG_DETAIL_LEVEL_MEDIUM, 10);
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	// Detail level: High
	if ((msX >= sX + 201) && (msX <= sX + 234) && (msY >= sY + 63) && (msY <= sY + 74)) {
		ConfigManager::Get().SetDetailLevel(2);
		AddEventList(NOTIFY_MSG_DETAIL_LEVEL_HIGH, 10);
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	// Sound toggle
	if ((msX >= sX + 24) && (msX <= sX + 115) && (msY >= sY + 81) && (msY <= sY + 100)) {
		if (AudioManager::Get().IsSoundAvailable()) {
			if (AudioManager::Get().IsSoundEnabled()) {
				AudioManager::Get().StopSound(SoundType::Effect, 38);
				AudioManager::Get().SetSoundEnabled(false);
				AddEventList(NOTIFY_MSG_SOUND_OFF, 10);
			}
			else {
				AudioManager::Get().SetSoundEnabled(true);
				AddEventList(NOTIFY_MSG_SOUND_ON, 10);
			}
		}
		return true;
	}

	// Music toggle
	if ((msX >= sX + 116) && (msX <= sX + 202) && (msY >= sY + 81) && (msY <= sY + 100)) {
		if (AudioManager::Get().IsSoundAvailable()) {
			if (AudioManager::Get().IsMusicEnabled()) {
				AudioManager::Get().SetMusicEnabled(false);
				AddEventList(NOTIFY_MSG_MUSIC_OFF, 10);
				AudioManager::Get().StopMusic();
			}
			else {
				AudioManager::Get().SetMusicEnabled(true);
				AddEventList(NOTIFY_MSG_MUSIC_ON, 10);
				m_pGame->StartBGM();
			}
		}
		return true;
	}

	// Whisper toggle
	if ((msX >= sX + 23) && (msX <= sX + 108) && (msY >= sY + 108) && (msY <= sY + 119)) {
		if (m_pGame->m_bWhisper == true) {
			m_pGame->m_bWhisper = false;
			AddEventList(BCHECK_LOCAL_CHAT_COMMAND7, 10);
		}
		else {
			m_pGame->m_bWhisper = true;
			AddEventList(BCHECK_LOCAL_CHAT_COMMAND6, 10);
		}
		return true;
	}

	// Shout toggle
	if ((msX >= sX + 123) && (msX <= sX + 203) && (msY >= sY + 108) && (msY <= sY + 119)) {
		if (m_pGame->m_bShout == true) {
			m_pGame->m_bShout = false;
			AddEventList(BCHECK_LOCAL_CHAT_COMMAND9, 10);
		}
		else {
			m_pGame->m_bShout = true;
			AddEventList(BCHECK_LOCAL_CHAT_COMMAND8, 10);
		}
		return true;
	}

	// Transparency toggle
	if ((msX >= sX + 28) && (msX <= sX + 235) && (msY >= sY + 156) && (msY <= sY + 171)) {
		bool dialogTrans = ConfigManager::Get().IsDialogTransparencyEnabled();
		ConfigManager::Get().SetDialogTransparencyEnabled(!dialogTrans);
		return true;
	}

	// Guide Map toggle
	if ((msX >= sX + 28) && (msX <= sX + 127) && (msY >= sY + 178) && (msY <= sY + 193)) {
		if (m_pGame->m_dialogBoxManager.IsEnabled(DialogBoxId::GuideMap))
			DisableDialogBox(DialogBoxId::GuideMap);
		else
			EnableDialogBox(DialogBoxId::GuideMap, 0, 0, 0);
		return true;
	}

	// Resolution button click (only when alive and not restarting)
	if ((m_pGame->m_iHP > 0) && (m_pGame->m_cRestartCount == -1)) {
		bool isFullscreen = m_pGame->m_DDraw.m_bFullMode;
		if ((msX >= sX + 110) && (msX <= sX + 168) && (msY >= sY + 200) && (msY <= sY + 213)) {
			if (isFullscreen) {
				m_pGame->m_DDraw.m_bFullMode = false;
				m_pGame->m_DDraw.ChangeDisplayMode(G_hWnd);
				InputManager::Get().SetActive(true);
				ConfigManager::Get().SetFullscreenEnabled(false);
				ConfigManager::Get().Save();
				m_pGame->m_bIsRedrawPDBGS = true;
				PlaySoundEffect('E', 14, 5);
			}
			return true;
		}

		if ((msX >= sX + 180) && (msX <= sX + 242) && (msY >= sY + 200) && (msY <= sY + 213)) {
			if (!isFullscreen) {
				m_pGame->m_DDraw.m_bFullMode = true;
				m_pGame->m_DDraw.ChangeDisplayMode(G_hWnd);
				InputManager::Get().SetActive(true);
				ConfigManager::Get().SetFullscreenEnabled(true);
				ConfigManager::Get().Save();
				m_pGame->m_bIsRedrawPDBGS = true;
				PlaySoundEffect('E', 14, 5);
			}
			return true;
		}

		if (!isFullscreen && (msX >= sX + 112) && (msX <= sX + 242) && (msY >= sY + 220) && (msY <= sY + 234)) {
			CycleResolution();
			m_pGame->m_bIsRedrawPDBGS = true;
			PlaySoundEffect('E', 14, 5);
			AddEventList("Resolution changed.", 10);
			return true;
		}
	}

	if (m_pGame->m_bForceDisconn) return false;

	// Log-Out / Continue button
	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + 225) && (msY <= sY + 225 + DEF_BTNSZY)) {
		if (m_pGame->m_cLogOutCount == -1) {
#ifdef _DEBUG
			m_pGame->m_cLogOutCount = 1;
#else
			m_pGame->m_cLogOutCount = 11;
#endif
		}
		else {
			m_pGame->m_cLogOutCount = -1;
			AddEventList(DLGBOX_CLICK_SYSMENU2, 10);
			DisableThisDialog();
		}
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	// Restart button (only when dead)
	if ((m_pGame->m_iHP <= 0) && (m_pGame->m_cRestartCount == -1)) {
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 225) && (msY <= sY + 225 + DEF_BTNSZY)) {
			m_pGame->m_cRestartCount = 5;
			m_pGame->m_dwRestartCountTime = GameClock::GetTimeMS();
			DisableThisDialog();
			wsprintf(m_pGame->G_cTxt, DLGBOX_CLICK_SYSMENU1, m_pGame->m_cRestartCount);
			AddEventList(m_pGame->G_cTxt, 10);
			PlaySoundEffect('E', 14, 5);
			return true;
		}
	}

	return false;
}
