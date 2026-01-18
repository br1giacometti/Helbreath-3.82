#include "DialogBox_HudPanel.h"
#include "Game.h"
#include "GlobalDef.h"
#include "SharedCalculations.h"

// Static button data shared between draw and click handling
const DialogBox_HudPanel::ToggleButtonInfo DialogBox_HudPanel::TOGGLE_BUTTONS[] = {
	{ 410, 447, 412, 6, "Character",   DialogBoxId::CharacterInfo },
	{ 447, 484, 449, 7, "Inventory",   DialogBoxId::Inventory },
	{ 484, 521, 486, 8, "Magics",      DialogBoxId::Magic },
	{ 521, 558, 523, 9, "Skills",      DialogBoxId::Skill },
	{ 558, 595, 560, 10, "Chat Log",   DialogBoxId::ChatHistory },
	{ 595, 631, 597, 11, "System Menu", DialogBoxId::SystemMenu }
};

DialogBox_HudPanel::DialogBox_HudPanel(CGame* pGame)
	: IDialogBox(DialogBoxId::HudPanel, pGame)
{
	SetDefaultRect(0, LOGICAL_HEIGHT - ICON_PANEL_HEIGHT, ICON_PANEL_WIDTH, ICON_PANEL_HEIGHT);
}

bool DialogBox_HudPanel::IsInButton(short msX, short msY, int x1, int x2) const
{
	return (msX > x1) && (msX < x2) && (msY > BTN_Y1) && (msY < BTN_Y2);
}

void DialogBox_HudPanel::ToggleDialogWithSound(DialogBoxId::Type dialogId)
{
	if (m_pGame->m_dialogBoxManager.IsEnabled(dialogId))
		m_pGame->m_dialogBoxManager.DisableDialogBox(dialogId);
	else
		EnableDialogBox(dialogId, 0, 0, 0);
	m_pGame->PlaySound('E', 14, 5);
}

void DialogBox_HudPanel::DrawGaugeBars()
{
	int iMaxPoint, iBarWidth;
	uint32_t dwTime = m_pGame->m_dwCurTime;
	auto* pSprite = m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL];

	// HP bar
	iMaxPoint = CalculateMaxHP(m_pGame->m_iVit, m_pGame->m_iLevel,
	                           m_pGame->m_iStr, m_pGame->m_iAngelicStr);
	if (m_pGame->m_iHP > iMaxPoint) m_pGame->m_iHP = iMaxPoint;
	iBarWidth = HP_MP_BAR_WIDTH - (m_pGame->m_iHP * HP_MP_BAR_WIDTH) / iMaxPoint;
	if (iBarWidth < 0) iBarWidth = 0;
	if (iBarWidth > HP_MP_BAR_WIDTH) iBarWidth = HP_MP_BAR_WIDTH;
	pSprite->PutSpriteFastWidth(HP_BAR_X, HP_BAR_Y, 12, iBarWidth, dwTime);

	// HP number
	wsprintf(m_pGame->G_cTxt, "%d", (short)m_pGame->m_iHP);
	if (m_pGame->m_bIsPoisoned)
	{
		m_pGame->PutString_SprNum(85, HP_NUM_Y, m_pGame->G_cTxt,
			m_pGame->m_wR[5] * 11, m_pGame->m_wG[5] * 11, m_pGame->m_wB[5] * 11);
		m_pGame->PutString_SprFont3(35, HP_BAR_Y + 2, "Poisoned",
			m_pGame->m_wR[5] * 8, m_pGame->m_wG[5] * 8, m_pGame->m_wB[5] * 8, true, 2);
	}
	else
	{
		m_pGame->PutString_SprNum(HP_NUM_X + 1, HP_NUM_Y + 1, m_pGame->G_cTxt, 0, 0, 0);
		m_pGame->PutString_SprNum(HP_NUM_X, HP_NUM_Y, m_pGame->G_cTxt, 255, 255, 255);
	}

	// MP bar
	iMaxPoint = CalculateMaxMP(m_pGame->m_iMag, m_pGame->m_iAngelicMag,
	                           m_pGame->m_iLevel, m_pGame->m_iInt, m_pGame->m_iAngelicInt);
	if (m_pGame->m_iMP > iMaxPoint) m_pGame->m_iMP = iMaxPoint;
	iBarWidth = HP_MP_BAR_WIDTH - (m_pGame->m_iMP * HP_MP_BAR_WIDTH) / iMaxPoint;
	if (iBarWidth < 0) iBarWidth = 0;
	if (iBarWidth > HP_MP_BAR_WIDTH) iBarWidth = HP_MP_BAR_WIDTH;
	pSprite->PutSpriteFastWidth(HP_BAR_X, MP_BAR_Y, 12, iBarWidth, dwTime);

	// MP number
	wsprintf(m_pGame->G_cTxt, "%d", (short)m_pGame->m_iMP);
	m_pGame->PutString_SprNum(HP_NUM_X + 1, MP_NUM_Y + 1, m_pGame->G_cTxt, 0, 0, 0);
	m_pGame->PutString_SprNum(HP_NUM_X, MP_NUM_Y, m_pGame->G_cTxt, 255, 255, 255);

	// SP bar
	iMaxPoint = CalculateMaxSP(m_pGame->m_iStr, m_pGame->m_iAngelicStr, m_pGame->m_iLevel);
	if (m_pGame->m_iSP > iMaxPoint) m_pGame->m_iSP = iMaxPoint;
	iBarWidth = SP_BAR_WIDTH - (m_pGame->m_iSP * SP_BAR_WIDTH) / iMaxPoint;
	if (iBarWidth < 0) iBarWidth = 0;
	if (iBarWidth > SP_BAR_WIDTH) iBarWidth = SP_BAR_WIDTH;
	pSprite->PutSpriteFastWidth(SP_BAR_X, SP_BAR_Y, 13, iBarWidth, dwTime);

	// SP number
	wsprintf(m_pGame->G_cTxt, "%d", (short)m_pGame->m_iSP);
	m_pGame->PutString_SprNum(SP_NUM_X + 1, SP_NUM_Y + 1, m_pGame->G_cTxt, 0, 0, 0);
	m_pGame->PutString_SprNum(SP_NUM_X, SP_NUM_Y, m_pGame->G_cTxt, 255, 255, 255);

	// Experience bar
	uint32_t iCurLevelExp = m_pGame->iGetLevelExp(m_pGame->m_iLevel);
	uint32_t iNextLevelExp = m_pGame->iGetLevelExp(m_pGame->m_iLevel + 1);
	uint32_t iExpRange = iNextLevelExp - iCurLevelExp;
	uint32_t iExpProgress = m_pGame->m_iExp - iCurLevelExp;
	iBarWidth = (iExpProgress * ICON_PANEL_WIDTH) / iExpRange;
	if (iBarWidth < 0) iBarWidth = 0;
	if (iBarWidth > ICON_PANEL_WIDTH) iBarWidth = ICON_PANEL_WIDTH;
	pSprite->PutSpriteFastWidth(0, EXP_BAR_Y, 18, iBarWidth, dwTime);
}

void DialogBox_HudPanel::DrawStatusIcons(short msX, short msY)
{
	uint32_t dwTime = m_pGame->m_dwCurTime;
	auto* pSprite = m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL];

	// Level up / Restart text
	if (m_pGame->m_iHP > 0)
	{
		if ((m_pGame->m_iLU_Point > 0) && !m_pGame->m_dialogBoxManager.IsEnabled(DialogBoxId::LevelUpSetting))
		{
			int flashColor = (GameClock::GetTimeMS() / 3) % 255;
			m_pGame->PutString_SprFont2(LEVELUP_TEXT_X, LEVELUP_TEXT_Y, "Level Up!", flashColor, flashColor, 0);
		}
	}
	else if (m_pGame->m_cRestartCount == -1)
	{
		int flashColor = (GameClock::GetTimeMS() / 3) % 255;
		m_pGame->PutString_SprFont2(LEVELUP_TEXT_X, LEVELUP_TEXT_Y, "Restart", flashColor, flashColor, 0);
	}

	// Combat mode / Safe attack icon
	if (m_pGame->m_bIsSafeAttackMode)
		pSprite->PutSpriteFast(COMBAT_ICON_X, COMBAT_ICON_Y, 4, dwTime);
	else if (m_pGame->m_bIsCombatMode)
		pSprite->PutSpriteFast(COMBAT_ICON_X, COMBAT_ICON_Y, 5, dwTime);

	// Combat mode button hover
	if (IsInButton(msX, msY, BTN_COMBAT_X1, BTN_COMBAT_X2))
	{
		pSprite->PutSpriteFast(BTN_COMBAT_X1, BTN_Y1, 16, dwTime);
		const char* tooltip = m_pGame->m_bIsCombatMode
			? (m_pGame->m_bIsSafeAttackMode ? "Safe Attack" : "Attack")
			: "Peace";
		wsprintf(m_pGame->G_cTxt, "%s", tooltip);
		PutString(msX - 10, msY - 20, m_pGame->G_cTxt, RGB(250, 250, 220));
	}

	// Crusade icon
	if (m_pGame->m_bIsCrusadeMode && m_pGame->m_iCrusadeDuty != 0)
	{
		bool bHover = IsInButton(msX, msY, BTN_CRUSADE_X1, BTN_CRUSADE_X2);
		if (m_pGame->m_bAresden)
			pSprite->PutSpriteFast(BTN_CRUSADE_X1 + (bHover ? 1 : 0), BTN_Y1, bHover ? 1 : 2, dwTime);
		else
			pSprite->PutSpriteFast(BTN_CRUSADE_X1, BTN_Y1, bHover ? 0 : 15, dwTime);
	}

	// Map message / coordinates (or remaining EXP when Ctrl pressed)
	if (InputManager::Get().IsCtrlDown())
	{
		uint32_t iCurExp = m_pGame->iGetLevelExp(m_pGame->m_iLevel);
		uint32_t iNextExp = m_pGame->iGetLevelExp(m_pGame->m_iLevel + 1);
		if (m_pGame->m_iExp < iNextExp)
		{
			uint32_t iExpRange = iNextExp - iCurExp;
			uint32_t iExpProgress = (m_pGame->m_iExp > iCurExp) ? (m_pGame->m_iExp - iCurExp) : 0;
			wsprintf(m_pGame->G_cTxt, "Rest Exp: %d", iExpRange - iExpProgress);
		}
	}
	else
	{
		wsprintf(m_pGame->G_cTxt, "%s (%d,%d)", m_pGame->m_cMapMessage, m_pGame->m_sPlayerX, m_pGame->m_sPlayerY);
	}
	PutAlignedString(MAP_MSG_X1 + 1, MAP_MSG_X2 + 1, MAP_MSG_Y + 1, m_pGame->G_cTxt, 0, 0, 0);
	PutAlignedString(MAP_MSG_X1, MAP_MSG_X2, MAP_MSG_Y, m_pGame->G_cTxt, 200, 200, 120);
}

void DialogBox_HudPanel::DrawIconButtons(short msX, short msY)
{
	if (msY <= BTN_Y1 || msY >= BTN_Y2) return;

	uint32_t dwTime = m_pGame->m_dwCurTime;
	auto* pSprite = m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL];

	for (int i = 0; i < TOGGLE_BUTTON_COUNT; i++)
	{
		const auto& btn = TOGGLE_BUTTONS[i];
		if (msX > btn.x1 && msX < btn.x2)
		{
			pSprite->PutSpriteFast(btn.spriteX, BTN_Y1, btn.spriteFrame, dwTime);
			wsprintf(m_pGame->G_cTxt, "%s", btn.tooltip);
			int tooltipOffset = (btn.dialogId == DialogBoxId::SystemMenu) ? -20 : -10;
			PutString(msX + tooltipOffset, msY - 20, m_pGame->G_cTxt, RGB(250, 250, 220));
			break;
		}
	}
}

void DialogBox_HudPanel::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short panelX = Info().sX;
	short panelY = Info().sY;

	m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(panelX, panelY, 14, m_pGame->m_dwCurTime);
	DrawGaugeBars();
	DrawStatusIcons(msX, msY);
	DrawIconButtons(msX, msY);
}

bool DialogBox_HudPanel::OnClick(short msX, short msY)
{
	// Crusade button
	if (IsInButton(msX, msY, BTN_CRUSADE_X1, BTN_CRUSADE_X2))
	{
		if (!m_pGame->m_bIsCrusadeMode) return false;
		switch (m_pGame->m_iCrusadeDuty)
		{
		case 1: EnableDialogBox(DialogBoxId::CrusadeSoldier, 0, 0, 0); break;
		case 2: EnableDialogBox(DialogBoxId::CrusadeConstructor, 0, 0, 0); break;
		case 3: EnableDialogBox(DialogBoxId::CrusadeCommander, 0, 0, 0); break;
		default: return false;
		}
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// Combat mode toggle
	if (IsInButton(msX, msY, BTN_COMBAT_X1, BTN_COMBAT_X2))
	{
		m_pGame->bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TOGGLECOMBATMODE, 0, 0, 0, 0, 0);
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// Dialog toggle buttons (Character, Inventory, Magic, Skill, Chat, System)
	for (int i = 0; i < TOGGLE_BUTTON_COUNT; i++)
	{
		const auto& btn = TOGGLE_BUTTONS[i];
		if (IsInButton(msX, msY, btn.x1, btn.x2))
		{
			ToggleDialogWithSound(btn.dialogId);
			return true;
		}
	}

	return false;
}
