#include "DialogBox_LevelUpSetting.h"
#include "Game.h"
#include "lan_eng.h"

DialogBox_LevelUpSetting::DialogBox_LevelUpSetting(CGame* pGame)
	: IDialogBox(DialogBoxId::LevelUpSetting, pGame)
{
	SetDefaultRect(0 + SCREENX, 0 + SCREENY, 258, 339);
}

void DialogBox_LevelUpSetting::DrawStatRow(short sX, short sY, int iYOffset, const char* pLabel,
                                            int iCurrentStat, int iPendingChange, short msX, short msY,
                                            int iArrowYOffset, bool bCanIncrease, bool bCanDecrease)
{
	char cTxt[120];
	uint32_t dwTime = m_pGame->m_dwCurTime;

	// Stat label
	PutString(sX + 24, sY + iYOffset, (char*)pLabel, RGB(5, 5, 5));

	// Current value
	wsprintf(cTxt, "%d", iCurrentStat);
	PutString(sX + 109, sY + iYOffset, cTxt, RGB(25, 35, 25));

	// New value (with pending changes)
	int iNewStat = iCurrentStat + iPendingChange;
	wsprintf(cTxt, "%d", iNewStat);
	if (iNewStat != iCurrentStat)
		PutString(sX + 162, sY + iYOffset, cTxt, RGB(255, 0, 0));
	else
		PutString(sX + 162, sY + iYOffset, cTxt, RGB(25, 35, 25));

	// + arrow highlight
	if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + iArrowYOffset) && (msY <= sY + iArrowYOffset + 6) && bCanIncrease)
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 195, sY + iArrowYOffset, 5, dwTime);

	// - arrow highlight
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + iArrowYOffset) && (msY <= sY + iArrowYOffset + 6) && bCanDecrease)
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + iArrowYOffset, 6, dwTime);
}

void DialogBox_LevelUpSetting::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;
	short szX = Info().sSizeX;
	uint32_t dwTime = m_pGame->m_dwCurTime;
	char cTxt[120];

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 2);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, sX + 16, sY + 100, 4);

	// Header text
	PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_LEVELUP_SETTING1);
	PutAlignedString(sX, sX + szX, sY + 65, DRAW_DIALOGBOX_LEVELUP_SETTING2);

	// Points Left
	PutString(sX + 20, sY + 85, DRAW_DIALOGBOX_LEVELUP_SETTING3, RGB(0, 0, 0));
	wsprintf(cTxt, "%d", m_pGame->m_iLU_Point);
	if (m_pGame->m_iLU_Point > 0)
		PutString(sX + 73, sY + 102, cTxt, RGB(0, 255, 0));
	else
		PutString(sX + 73, sY + 102, cTxt, RGB(0, 0, 0));

	// Draw stat rows
	DrawStatRow(sX, sY, 125, DRAW_DIALOGBOX_LEVELUP_SETTING4, m_pGame->m_iStr, m_pGame->m_cLU_Str,
	            msX, msY, 127, (m_pGame->m_iStr < m_pGame->iMaxStats), (m_pGame->m_cLU_Str > 0));

	DrawStatRow(sX, sY, 144, DRAW_DIALOGBOX_LEVELUP_SETTING5, m_pGame->m_iVit, m_pGame->m_cLU_Vit,
	            msX, msY, 146, (m_pGame->m_iVit < m_pGame->iMaxStats), (m_pGame->m_cLU_Vit > 0));

	DrawStatRow(sX, sY, 163, DRAW_DIALOGBOX_LEVELUP_SETTING6, m_pGame->m_iDex, m_pGame->m_cLU_Dex,
	            msX, msY, 165, (m_pGame->m_iDex < m_pGame->iMaxStats), (m_pGame->m_cLU_Dex > 0));

	DrawStatRow(sX, sY, 182, DRAW_DIALOGBOX_LEVELUP_SETTING7, m_pGame->m_iInt, m_pGame->m_cLU_Int,
	            msX, msY, 184, (m_pGame->m_iInt < m_pGame->iMaxStats), (m_pGame->m_cLU_Int > 0));

	DrawStatRow(sX, sY, 201, DRAW_DIALOGBOX_LEVELUP_SETTING8, m_pGame->m_iMag, m_pGame->m_cLU_Mag,
	            msX, msY, 203, (m_pGame->m_iMag < m_pGame->iMaxStats), (m_pGame->m_cLU_Mag > 0));

	DrawStatRow(sX, sY, 220, DRAW_DIALOGBOX_LEVELUP_SETTING9, m_pGame->m_iCharisma, m_pGame->m_cLU_Char,
	            msX, msY, 222, (m_pGame->m_iCharisma < m_pGame->iMaxStats), (m_pGame->m_cLU_Char > 0));

	// Close button
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) &&
	    (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
	else
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);

	// Majestic button (only if no pending changes and no points left)
	if ((m_pGame->m_cLU_Str == 0) && (m_pGame->m_cLU_Vit == 0) && (m_pGame->m_cLU_Dex == 0) &&
	    (m_pGame->m_cLU_Int == 0) && (m_pGame->m_cLU_Mag == 0) && (m_pGame->m_cLU_Char == 0))
	{
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) &&
		    (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		{
			if (m_pGame->m_iLU_Point <= 0)
				DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 21);
		}
		else
		{
			if (m_pGame->m_iLU_Point <= 0)
				DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 20);
		}
	}
}

bool DialogBox_LevelUpSetting::HandleStatClick(short msX, short msY, short sX, short sY,
                                                int iYOffset, int& iCurrentStat, uint16_t& cPendingChange)
{
	bool bMajesticOpen = m_pGame->m_dialogBoxManager.IsEnabled(DialogBoxId::ChangeStatsMajestic);

	// + button
	if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + iYOffset) && (msY <= sY + iYOffset + 6) &&
	    (iCurrentStat <= m_pGame->iMaxStats) && (m_pGame->m_iLU_Point > 0))
	{
		if (InputManager::Get().IsCtrlDown())
		{
			if ((m_pGame->m_iLU_Point >= 5) && !bMajesticOpen)
			{
				m_pGame->m_iLU_Point -= 5;
				cPendingChange += 5;
			}
		}
		else
		{
			if ((m_pGame->m_iLU_Point > 0) && !bMajesticOpen)
			{
				m_pGame->m_iLU_Point--;
				cPendingChange++;
			}
		}
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	// - button
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + iYOffset) && (msY <= sY + iYOffset + 6) &&
	    (cPendingChange > 0))
	{
		if (InputManager::Get().IsCtrlDown())
		{
			if ((cPendingChange >= 5) && !bMajesticOpen)
			{
				cPendingChange -= 5;
				m_pGame->m_iLU_Point += 5;
			}
		}
		else
		{
			if ((cPendingChange > 0) && !bMajesticOpen)
			{
				cPendingChange--;
				m_pGame->m_iLU_Point++;
			}
		}
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	return false;
}

bool DialogBox_LevelUpSetting::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;

	// Strength +/-
	if (HandleStatClick(msX, msY, sX, sY, 127, m_pGame->m_iStr, m_pGame->m_cLU_Str))
		return true;

	// Vitality +/-
	if (HandleStatClick(msX, msY, sX, sY, 146, m_pGame->m_iVit, m_pGame->m_cLU_Vit))
		return true;

	// Dexterity +/-
	if (HandleStatClick(msX, msY, sX, sY, 165, m_pGame->m_iDex, m_pGame->m_cLU_Dex))
		return true;

	// Intelligence +/-
	if (HandleStatClick(msX, msY, sX, sY, 184, m_pGame->m_iInt, m_pGame->m_cLU_Int))
		return true;

	// Magic +/-
	if (HandleStatClick(msX, msY, sX, sY, 203, m_pGame->m_iMag, m_pGame->m_cLU_Mag))
		return true;

	// Charisma +/-
	if (HandleStatClick(msX, msY, sX, sY, 222, m_pGame->m_iCharisma, m_pGame->m_cLU_Char))
		return true;

	// Close/OK button
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) &&
	    (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
	{
		if (Info().sV1 != m_pGame->m_iLU_Point)
			bSendCommand(MSGID_LEVELUPSETTINGS, 0, 0, 0, 0, 0, 0);
		DisableThisDialog();
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	// Majestic button
	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) &&
	    (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
	{
		if ((m_pGame->m_iGizonItemUpgradeLeft > 0) && (m_pGame->m_iLU_Point <= 0) &&
		    (m_pGame->m_cLU_Str == 0) && (m_pGame->m_cLU_Vit == 0) && (m_pGame->m_cLU_Dex == 0) &&
		    (m_pGame->m_cLU_Int == 0) && (m_pGame->m_cLU_Mag == 0) && (m_pGame->m_cLU_Char == 0))
		{
			DisableThisDialog();
			EnableDialogBox(DialogBoxId::ChangeStatsMajestic, 0, 0, 0);
			return true;
		}
	}

	return false;
}
