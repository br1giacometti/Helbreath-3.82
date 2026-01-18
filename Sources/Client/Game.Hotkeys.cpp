#include "Game.h"
#include "AudioManager.h"
#include "ConfigManager.h"
#include "HotkeyManager.h"
#include "LAN_ENG.H"

extern int _tmp_iStatus;
extern char _tmp_cName[21];
extern short _tmp_sOwnerType;

void CGame::RegisterHotkeys()
{
	auto& hotkeys = HotkeyManager::Get();
	hotkeys.Clear();

	HotkeyManager::KeyCombo ctrlOnly{ 0, true, false, false };

	hotkeys.Register({ 'A', ctrlOnly.ctrl, ctrlOnly.shift, ctrlOnly.alt }, HotkeyManager::Trigger::KeyUp,
		[this]() { Hotkey_ToggleForceAttack(); });
	hotkeys.Register({ 'D', ctrlOnly.ctrl, ctrlOnly.shift, ctrlOnly.alt }, HotkeyManager::Trigger::KeyUp,
		[this]() { Hotkey_CycleDetailLevel(); });
	hotkeys.Register({ 'H', ctrlOnly.ctrl, ctrlOnly.shift, ctrlOnly.alt }, HotkeyManager::Trigger::KeyUp,
		[this]() { Hotkey_ToggleHelp(); });
	hotkeys.Register({ 'W', ctrlOnly.ctrl, ctrlOnly.shift, ctrlOnly.alt }, HotkeyManager::Trigger::KeyUp,
		[this]() { Hotkey_ToggleDialogTransparency(); });
	hotkeys.Register({ 'X', ctrlOnly.ctrl, ctrlOnly.shift, ctrlOnly.alt }, HotkeyManager::Trigger::KeyUp,
		[this]() { Hotkey_ToggleSystemMenu(); });
	hotkeys.Register({ 'M', ctrlOnly.ctrl, ctrlOnly.shift, ctrlOnly.alt }, HotkeyManager::Trigger::KeyUp,
		[this]() { Hotkey_ToggleGuideMap(); });
#ifdef _DEBUG
	hotkeys.Register({ 'Q', ctrlOnly.ctrl, ctrlOnly.shift, ctrlOnly.alt }, HotkeyManager::Trigger::KeyUp,
		[this]() { Hotkey_EnableAdminCommand(); });
#endif
	hotkeys.Register({ 'R', ctrlOnly.ctrl, ctrlOnly.shift, ctrlOnly.alt }, HotkeyManager::Trigger::KeyUp,
		[this]() { Hotkey_ToggleRunningMode(); });
	hotkeys.Register({ 'S', ctrlOnly.ctrl, ctrlOnly.shift, ctrlOnly.alt }, HotkeyManager::Trigger::KeyUp,
		[this]() { Hotkey_ToggleSoundAndMusic(); });
	hotkeys.Register({ 'T', ctrlOnly.ctrl, ctrlOnly.shift, ctrlOnly.alt }, HotkeyManager::Trigger::KeyUp,
		[this]() { Hotkey_WhisperTarget(); });
}

void CGame::Hotkey_ToggleForceAttack()
{
	if (!InputManager::Get().IsCtrlDown() || m_cGameMode != DEF_GAMEMODE_ONMAINGAME || m_bInputStatus) {
		return;
	}
	if (m_bForceAttack)
	{
		m_bForceAttack = false;
		AddEventList(DEF_MSG_FORCEATTACK_OFF, 10);
	}
	else
	{
		m_bForceAttack = true;
		AddEventList(DEF_MSG_FORCEATTACK_ON, 10);
	}
}

void CGame::Hotkey_CycleDetailLevel()
{
	if (!InputManager::Get().IsCtrlDown() || m_cGameMode != DEF_GAMEMODE_ONMAINGAME || m_bInputStatus) {
		return;
	}
	int detailLevel = ConfigManager::Get().GetDetailLevel();
	detailLevel++;
	if (detailLevel > 2) detailLevel = 0;
	ConfigManager::Get().SetDetailLevel(detailLevel);
	switch (detailLevel) {
	case 0:
		AddEventList(NOTIFY_MSG_DETAIL_LEVEL_LOW, 10);
		break;
	case 1:
		AddEventList(NOTIFY_MSG_DETAIL_LEVEL_MEDIUM, 10);
		break;
	case 2:
		AddEventList(NOTIFY_MSG_DETAIL_LEVEL_HIGH, 10);
		break;
	}
}

void CGame::Hotkey_ToggleHelp()
{
	if (!InputManager::Get().IsCtrlDown() || m_cGameMode != DEF_GAMEMODE_ONMAINGAME || m_bInputStatus) {
		return;
	}
	if (m_dialogBoxManager.IsEnabled(DialogBoxId::Help) == false)
		m_dialogBoxManager.EnableDialogBox(DialogBoxId::Help, 0, 0, 0);
	else
	{
		m_dialogBoxManager.DisableDialogBox(DialogBoxId::Help);
		m_dialogBoxManager.DisableDialogBox(DialogBoxId::Text);
	}
}

void CGame::Hotkey_ToggleDialogTransparency()
{
	if (!InputManager::Get().IsCtrlDown() || m_cGameMode != DEF_GAMEMODE_ONMAINGAME || m_bInputStatus) {
		return;
	}
	bool enabled = ConfigManager::Get().IsDialogTransparencyEnabled();
	ConfigManager::Get().SetDialogTransparencyEnabled(!enabled);
}

void CGame::Hotkey_ToggleSystemMenu()
{
	if (!InputManager::Get().IsCtrlDown() || m_cGameMode != DEF_GAMEMODE_ONMAINGAME || m_bInputStatus) {
		return;
	}
	if (m_dialogBoxManager.IsEnabled(DialogBoxId::SystemMenu) == false)
		m_dialogBoxManager.EnableDialogBox(DialogBoxId::SystemMenu, 0, 0, 0);
	else m_dialogBoxManager.DisableDialogBox(DialogBoxId::SystemMenu);
}

void CGame::Hotkey_ToggleGuideMap()
{
	if (m_cGameMode != DEF_GAMEMODE_ONMAINGAME || !InputManager::Get().IsCtrlDown()) {
		return;
	}
	if (m_dialogBoxManager.IsEnabled(DialogBoxId::GuideMap) == true) m_dialogBoxManager.DisableDialogBox(DialogBoxId::GuideMap);
	else m_dialogBoxManager.EnableDialogBox(DialogBoxId::GuideMap, 0, 0, 0, 0);
}

void CGame::Hotkey_EnableAdminCommand()
{
#ifdef _DEBUG
	if (!InputManager::Get().IsCtrlDown() || m_cGameMode != DEF_GAMEMODE_ONMAINGAME) {
		return;
	}
	std::memset(m_cChatMsg, 0, sizeof(m_cChatMsg));
	strcpy(m_cChatMsg, "/enableadmincommand 147258 ");
	StartInputString(CHAT_INPUT_X, CHAT_INPUT_Y, sizeof(m_cChatMsg), m_cChatMsg);
#endif
}

void CGame::Hotkey_ToggleRunningMode()
{
	if (!InputManager::Get().IsCtrlDown() || m_cGameMode != DEF_GAMEMODE_ONMAINGAME || m_bInputStatus) {
		return;
	}
	bool runningMode = ConfigManager::Get().IsRunningModeEnabled();
	if (runningMode)
	{
		ConfigManager::Get().SetRunningModeEnabled(false);
		AddEventList(NOTIFY_MSG_CONVERT_WALKING_MODE, 10);
	}
	else
	{
		ConfigManager::Get().SetRunningModeEnabled(true);
		AddEventList(NOTIFY_MSG_CONVERT_RUNNING_MODE, 10);
	}
}

void CGame::Hotkey_ToggleSoundAndMusic()
{
	if (!InputManager::Get().IsCtrlDown() || m_cGameMode != DEF_GAMEMODE_ONMAINGAME || m_bInputStatus) {
		return;
	}
	if (AudioManager::Get().IsMusicEnabled())
	{
		AudioManager::Get().SetMusicEnabled(false);
		AudioManager::Get().StopMusic();
		AddEventList(NOTIFY_MSG_MUSIC_OFF, 10);
		return;
	}
	if (AudioManager::Get().IsSoundEnabled())
	{
		AudioManager::Get().StopSound(SoundType::Effect, 38);
		AudioManager::Get().SetSoundEnabled(false);
		AddEventList(NOTIFY_MSG_SOUND_OFF, 10);
		return;
	}
	if (AudioManager::Get().IsSoundAvailable())
	{
		AudioManager::Get().SetMusicEnabled(true);
		AddEventList(NOTIFY_MSG_MUSIC_ON, 10);
	}
	if (AudioManager::Get().IsSoundAvailable())
	{
		AudioManager::Get().SetSoundEnabled(true);
		AddEventList(NOTIFY_MSG_SOUND_ON, 10);
	}
	StartBGM();
}

void CGame::Hotkey_WhisperTarget()
{
	if (!InputManager::Get().IsCtrlDown() || m_cGameMode != DEF_GAMEMODE_ONMAINGAME || m_bInputStatus) {
		return;
	}
	char tempid[100], cLB, cRB;
	short sX, sY, msX, msY, msZ;
	sX = m_dialogBoxManager.Info(DialogBoxId::ChatHistory).sX;
	sY = m_dialogBoxManager.Info(DialogBoxId::ChatHistory).sY;
	std::memset(tempid, 0, sizeof(tempid));
	InputManager::Get().GetLegacyState(&msX, &msY, &msZ, &cLB, &cRB);
	if (m_dialogBoxManager.IsEnabled(DialogBoxId::ChatHistory) == true && (msX >= sX + 20) && (msX <= sX + 360) && (msY >= sY + 35) && (msY <= sY + 139))
	{
		char* token, cBuff[64];
		char   seps[] = ":";
		int i = (139 - msY + sY) / 13;
		if (m_pChatScrollList[i + m_dialogBoxManager.Info(DialogBoxId::ChatHistory).sView] == 0) return;
		if (m_pChatScrollList[i + m_dialogBoxManager.Info(DialogBoxId::ChatHistory).sView]->m_pMsg[0] == ' ') i++;
		strcpy(cBuff, m_pChatScrollList[i + m_dialogBoxManager.Info(DialogBoxId::ChatHistory).sView]->m_pMsg);
		token = strtok(cBuff, seps);
		wsprintf(tempid, "/to %s", token);
		bSendCommand(MSGID_COMMAND_CHATMSG, 0, 0, 0, 0, 0, tempid);
	}
	else if (_tmp_sOwnerType < 7 && (strlen(_tmp_cName) > 0) && (m_iIlusionOwnerH == 0)
		&& ((m_bIsCrusadeMode == false) || _iGetFOE(_tmp_iStatus) >= 0))
	{
		wsprintf(tempid, "/to %s", _tmp_cName);
		bSendCommand(MSGID_COMMAND_CHATMSG, 0, 0, 0, 0, 0, tempid);
	}
	else
	{
		EndInputString();
		wsprintf(m_cChatMsg, "/to ");
		StartInputString(CHAT_INPUT_X, CHAT_INPUT_Y, sizeof(m_cChatMsg), m_cChatMsg);
	}
}

void CGame::Hotkey_Simple_UseHealthPotion()
{
	int i = 0;
	if (m_iHP <= 0) return;
	if (m_bItemUsingStatus == true)
	{
		AddEventList(USE_RED_POTION1, 10);
		return;
	}
	if (m_dialogBoxManager.IsEnabled(DialogBoxId::Exchange) == true)
	{
		AddEventList(USE_RED_POTION2, 10);
		return;
	}
	for (i = 0; i < DEF_MAXITEMS; i++)
		if ((m_pItemList[i] != 0) && (m_bIsItemDisabled[i] != true) &&
			(m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 1))
		{
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USEITEM, 0, i, 0, 0, 0);
			m_bIsItemDisabled[i] = true;
			m_bItemUsingStatus = true;
			return;
		}

	for (i = 0; i < DEF_MAXITEMS; i++)
		if ((m_pItemList[i] != 0) && (m_bIsItemDisabled[i] != true) &&
			(m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 2))
		{
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USEITEM, 0, i, 0, 0, 0);
			m_bIsItemDisabled[i] = true;
			m_bItemUsingStatus = true;
			return;
		}
}

void CGame::Hotkey_Simple_UseManaPotion()
{
	int i = 0;
	if (m_iHP <= 0) return;
	if (m_bItemUsingStatus == true)
	{
		AddEventList(USE_BLUE_POTION1, 10);
		return;
	}
	if (m_dialogBoxManager.IsEnabled(DialogBoxId::Exchange) == true)
	{
		AddEventList(USE_BLUE_POTION2, 10);
		return;
	}

	for (i = 0; i < DEF_MAXITEMS; i++)
		if ((m_pItemList[i] != 0) && (m_bIsItemDisabled[i] != true) &&
			(m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 3))
		{
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USEITEM, 0, i, 0, 0, 0);
			m_bIsItemDisabled[i] = true;
			m_bItemUsingStatus = true;
			return;
		}

	for (i = 0; i < DEF_MAXITEMS; i++)
		if ((m_pItemList[i] != 0) && (m_bIsItemDisabled[i] != true) &&
			(m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 4))
		{
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USEITEM, 0, i, 0, 0, 0);
			m_bIsItemDisabled[i] = true;
			m_bItemUsingStatus = true;
			return;
		}
}

void CGame::Hotkey_Simple_LoadBackupChat()
{
	if (((m_dialogBoxManager.IsEnabled(DialogBoxId::GuildMenu) == true) && (m_dialogBoxManager.Info(DialogBoxId::GuildMenu).cMode == 1) && (m_dialogBoxManager.iGetTopDialogBoxIndex() == DialogBoxId::GuildMenu)) ||
		((m_dialogBoxManager.IsEnabled(DialogBoxId::ItemDropExternal) == true) && (m_dialogBoxManager.Info(DialogBoxId::ItemDropExternal).cMode == 1) && (m_dialogBoxManager.iGetTopDialogBoxIndex() == DialogBoxId::ItemDropExternal)))
	{
		return;
	}
	if ((!m_bInputStatus) && (m_cBackupChatMsg[0] != '!') && (m_cBackupChatMsg[0] != '~') && (m_cBackupChatMsg[0] != '^') &&
		(m_cBackupChatMsg[0] != '@'))
	{
		std::memset(m_cChatMsg, 0, sizeof(m_cChatMsg));
		strcpy(m_cChatMsg, m_cBackupChatMsg);
		StartInputString(CHAT_INPUT_X, CHAT_INPUT_Y, sizeof(m_cChatMsg), m_cChatMsg);
	}
}

void CGame::Hotkey_Simple_UseMagicShortcut()
{
	if (m_cGameMode != DEF_GAMEMODE_ONMAINGAME) return;
	UseMagic(m_sMagicShortCut);
}

void CGame::Hotkey_Simple_ToggleCharacterInfo()
{
	if (m_dialogBoxManager.IsEnabled(DialogBoxId::CharacterInfo) == false)
		m_dialogBoxManager.EnableDialogBox(DialogBoxId::CharacterInfo, 0, 0, 0);
	else m_dialogBoxManager.DisableDialogBox(DialogBoxId::CharacterInfo);
}

void CGame::Hotkey_Simple_ToggleInventory()
{
	if (m_dialogBoxManager.IsEnabled(DialogBoxId::Inventory) == false)
		m_dialogBoxManager.EnableDialogBox(DialogBoxId::Inventory, 0, 0, 0);
	else m_dialogBoxManager.DisableDialogBox(DialogBoxId::Inventory);
}

void CGame::Hotkey_Simple_ToggleMagic()
{
	if (m_dialogBoxManager.IsEnabled(DialogBoxId::Magic) == false)
		m_dialogBoxManager.EnableDialogBox(DialogBoxId::Magic, 0, 0, 0);
	else m_dialogBoxManager.DisableDialogBox(DialogBoxId::Magic);
}

void CGame::Hotkey_Simple_ToggleSkill()
{
	if (m_dialogBoxManager.IsEnabled(DialogBoxId::Skill) == false)
		m_dialogBoxManager.EnableDialogBox(DialogBoxId::Skill, 0, 0, 0);
	else m_dialogBoxManager.DisableDialogBox(DialogBoxId::Skill);
}

void CGame::Hotkey_Simple_ToggleChatHistory()
{
	if (m_dialogBoxManager.IsEnabled(DialogBoxId::ChatHistory) == false)
		m_dialogBoxManager.EnableDialogBox(DialogBoxId::ChatHistory, 0, 0, 0);
	else m_dialogBoxManager.DisableDialogBox(DialogBoxId::ChatHistory);
}

void CGame::Hotkey_Simple_ToggleSystemMenu()
{
	if (m_bInputStatus) return;
	if (m_dialogBoxManager.IsEnabled(DialogBoxId::SystemMenu) == false)
		m_dialogBoxManager.EnableDialogBox(DialogBoxId::SystemMenu, 0, 0, 0);
	else m_dialogBoxManager.DisableDialogBox(DialogBoxId::SystemMenu);
}

void CGame::Hotkey_Simple_UseShortcut1()
{
	UseShortCut(1);
}

void CGame::Hotkey_Simple_UseShortcut2()
{
	UseShortCut(2);
}

void CGame::Hotkey_Simple_UseShortcut3()
{
	UseShortCut(3);
}

void CGame::Hotkey_Simple_WhisperCycleUp()
{
	m_cArrowPressed = 1;
	if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME)
	{
		int iTotalMsg = 0;
		for (int i = DEF_MAXWHISPERMSG - 1; i >= 0; i--)
		{
			if (m_pWhisperMsg[i] != 0)
			{
				iTotalMsg = i;
				break;
			}
		}
		m_cWhisperIndex++;
		if (m_cWhisperIndex > iTotalMsg) m_cWhisperIndex = 0;
		if (m_cWhisperIndex < 0) m_cWhisperIndex = iTotalMsg;
		if (m_pWhisperMsg[m_cWhisperIndex] != 0) {
			EndInputString();
			wsprintf(m_cChatMsg, "/to %s", m_pWhisperMsg[m_cWhisperIndex]->m_pMsg);
			StartInputString(CHAT_INPUT_X, CHAT_INPUT_Y, sizeof(m_cChatMsg), m_cChatMsg);
		}
	}
}

void CGame::Hotkey_Simple_WhisperCycleDown()
{
	m_cArrowPressed = 3;
	if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME)
	{
		int iTotalMsg = 0;
		for (int i = DEF_MAXWHISPERMSG - 1; i >= 0; i--)
		{
			if (m_pWhisperMsg[i] != 0)
			{
				iTotalMsg = i;
				break;
			}
		}
		m_cWhisperIndex--;
		if (m_cWhisperIndex < 0) m_cWhisperIndex = iTotalMsg;
		if (m_cWhisperIndex > iTotalMsg) m_cWhisperIndex = 0;
		if (m_pWhisperMsg[m_cWhisperIndex] != 0) {
			EndInputString();
			wsprintf(m_cChatMsg, "/to %s", m_pWhisperMsg[m_cWhisperIndex]->m_pMsg);
			StartInputString(CHAT_INPUT_X, CHAT_INPUT_Y, sizeof(m_cChatMsg), m_cChatMsg);
		}
	}
}

void CGame::Hotkey_Simple_ArrowLeft()
{
	m_cArrowPressed = 4;
}

void CGame::Hotkey_Simple_ArrowRight()
{
	m_cArrowPressed = 2;
}

void CGame::Hotkey_Simple_Screenshot()
{
	CreateScreenShot();
}

void CGame::Hotkey_Simple_TabToggleCombat()
{
	if (InputManager::Get().IsShiftDown())
	{
		m_cCurFocus--;
		if (m_cCurFocus < 1) m_cCurFocus = m_cMaxFocus;
	}
	else
	{
		m_cCurFocus++;
		if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
	}
	if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME)
	{
		bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TOGGLECOMBATMODE, 0, 0, 0, 0, 0);
	}
}

void CGame::Hotkey_Simple_ToggleSafeAttack()
{
	if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME) {
		bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TOGGLESAFEATTACKMODE, 0, 0, 0, 0, 0);
	}
}

void CGame::Hotkey_Simple_Escape()
{
	InputManager::Get().OnKeyUp(VK_ESCAPE);
	InputManager::Get().SetEscPressed();
	if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME)
	{
		if ((m_bIsObserverMode == true) && (InputManager::Get().IsShiftDown())) {
			if (m_cLogOutCount == -1) m_cLogOutCount = 1;
			m_dialogBoxManager.DisableDialogBox(DialogBoxId::SystemMenu);
			PlaySound('E', 14, 5);
		}
		else if (m_cLogOutCount != -1) {
			if (m_bForceDisconn == false) {
				m_cLogOutCount = -1;
				AddEventList(DLGBOX_CLICK_SYSMENU2, 10);
			}
		}
		if (m_bIsGetPointingMode == true) {
			m_bIsGetPointingMode = false;
			AddEventList(COMMAND_PROCESSOR1, 10);
		}
		m_bIsF1HelpWindowEnabled = false;
	}
}

void CGame::Hotkey_Simple_SpecialAbility()
{
	int i = 0;
	uint32_t dwTime = GameClock::GetTimeMS();
	if (m_cGameMode != DEF_GAMEMODE_ONMAINGAME) return;
	if (m_bInputStatus) return;
	if (m_bIsSpecialAbilityEnabled == true)
	{
		if (m_iSpecialAbilityType != 0) {
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_ACTIVATESPECABLTY, 0, 0, 0, 0, 0);
			m_bIsSpecialAbilityEnabled = false;
		}
		else AddEventList(ON_KEY_UP26, 10);
	}
	else {
		if (m_iSpecialAbilityType == 0) AddEventList(ON_KEY_UP26, 10);
		else {
			if ((m_sPlayerAppr4 & 0x00F0) != 0) {
				AddEventList(ON_KEY_UP28, 10);
				return;
			}

			i = (dwTime - m_dwSpecialAbilitySettingTime) / 1000;
			i = m_iSpecialAbilityTimeLeftSec - i;
			if (i < 0) i = 0;

			std::memset(G_cTxt, 0, sizeof(G_cTxt));
			if (i < 60) {
				switch (m_iSpecialAbilityType) {
				case 1: wsprintf(G_cTxt, ON_KEY_UP29, i); break;//"
				case 2: wsprintf(G_cTxt, ON_KEY_UP30, i); break;//"
				case 3: wsprintf(G_cTxt, ON_KEY_UP31, i); break;//"
				case 4: wsprintf(G_cTxt, ON_KEY_UP32, i); break;//"
				case 5: wsprintf(G_cTxt, ON_KEY_UP33, i); break;//"
				case 50:wsprintf(G_cTxt, ON_KEY_UP34, i); break;//"
				case 51:wsprintf(G_cTxt, ON_KEY_UP35, i); break;//"
				case 52:wsprintf(G_cTxt, ON_KEY_UP36, i); break;//"
				}
			}
			else {
				switch (m_iSpecialAbilityType) {
				case 1: wsprintf(G_cTxt, ON_KEY_UP37, i / 60); break;//"
				case 2: wsprintf(G_cTxt, ON_KEY_UP38, i / 60); break;//"
				case 3: wsprintf(G_cTxt, ON_KEY_UP39, i / 60); break;//"
				case 4: wsprintf(G_cTxt, ON_KEY_UP40, i / 60); break;//"
				case 5: wsprintf(G_cTxt, ON_KEY_UP41, i / 60); break;//"
				case 50:wsprintf(G_cTxt, ON_KEY_UP42, i / 60); break;//"
				case 51:wsprintf(G_cTxt, ON_KEY_UP43, i / 60); break;//"
				case 52:wsprintf(G_cTxt, ON_KEY_UP44, i / 60); break;//"
				}
			}
			AddEventList(G_cTxt, 10);
		}
	}
}

void CGame::Hotkey_Simple_ZoomIn()
{
	if (m_bInputStatus == false) ConfigManager::Get().SetZoomMapEnabled(true);
}

void CGame::Hotkey_Simple_ZoomOut()
{
	if (m_bInputStatus == false) ConfigManager::Get().SetZoomMapEnabled(false);
}
