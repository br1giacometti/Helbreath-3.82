#include "DialogBox_ChangeStatsMajestic.h"
#include "Game.h"
#include "lan_eng.h"
#include "GlobalDef.h"
#include "SpriteID.h"
#include "NetMessages.h"

DialogBox_ChangeStatsMajestic::DialogBox_ChangeStatsMajestic(CGame* pGame)
	: IDialogBox(DialogBoxId::ChangeStatsMajestic, pGame)
{
}

void DialogBox_ChangeStatsMajestic::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX, sY, szX;
	uint32_t dwTime = m_pGame->m_dwCurTime;
	char cTxt[120];
	int iStats;
	sX = Info().sX;
	sY = Info().sY;
	szX = Info().sSizeX;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 2);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, sX + 16, sY + 100, 4);

	PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_LEVELUP_SETTING14);
	PutAlignedString(sX, sX + szX, sY + 65, DRAW_DIALOGBOX_LEVELUP_SETTING15);

	// Majestic Points Left
	PutString(sX + 20, sY + 85, DRAW_DIALOGBOX_LEVELUP_SETTING16, RGB(0, 0, 0));
	wsprintf(cTxt, "%d", m_pGame->m_iGizonItemUpgradeLeft);
	if (m_pGame->m_iGizonItemUpgradeLeft > 0)
	{
		PutString(sX + 73, sY + 102, cTxt, RGB(0, 255, 0));
	}
	else
	{
		PutString(sX + 73, sY + 102, cTxt, RGB(0, 0, 0));
	}

	// Strength
	PutString(sX + 24, sY + 125, DRAW_DIALOGBOX_LEVELUP_SETTING4, RGB(5, 5, 5));
	wsprintf(cTxt, "%d", m_pGame->m_iStr);
	PutString(sX + 109, sY + 125, cTxt, RGB(25, 35, 25));
	iStats = m_pGame->m_iStr + m_pGame->m_cLU_Str;
	wsprintf(cTxt, "%d", iStats);
	if (iStats < m_pGame->m_iStr)
	{
		PutString(sX + 162, sY + 125, cTxt, RGB(255, 0, 0));
	}
	else
	{
		PutString(sX + 162, sY + 125, cTxt, RGB(25, 35, 25));
	}
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 127) && (msY <= sY + 133))
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 127, 6, dwTime);

	// Vitality
	PutString(sX + 24, sY + 144, DRAW_DIALOGBOX_LEVELUP_SETTING5, RGB(5, 5, 5));
	wsprintf(cTxt, "%d", m_pGame->m_iVit);
	PutString(sX + 109, sY + 144, cTxt, RGB(25, 35, 25));
	iStats = m_pGame->m_iVit + m_pGame->m_cLU_Vit;
	wsprintf(cTxt, "%d", iStats);
	if (iStats < m_pGame->m_iVit)
	{
		PutString(sX + 162, sY + 144, cTxt, RGB(255, 0, 0));
	}
	else
	{
		PutString(sX + 162, sY + 144, cTxt, RGB(25, 35, 25));
	}
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 146) && (msY <= sY + 152))
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 146, 6, dwTime);

	// Dexterity
	PutString(sX + 24, sY + 163, DRAW_DIALOGBOX_LEVELUP_SETTING6, RGB(5, 5, 5));
	wsprintf(cTxt, "%d", m_pGame->m_iDex);
	PutString(sX + 109, sY + 163, cTxt, RGB(25, 35, 25));
	iStats = m_pGame->m_iDex + m_pGame->m_cLU_Dex;
	wsprintf(cTxt, "%d", iStats);
	if (iStats < m_pGame->m_iDex)
	{
		PutString(sX + 162, sY + 163, cTxt, RGB(255, 0, 0));
	}
	else
	{
		PutString(sX + 162, sY + 163, cTxt, RGB(25, 35, 25));
	}
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 165) && (msY <= sY + 171))
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 165, 6, dwTime);

	// Intelligence
	PutString(sX + 24, sY + 182, DRAW_DIALOGBOX_LEVELUP_SETTING7, RGB(5, 5, 5));
	wsprintf(cTxt, "%d", m_pGame->m_iInt);
	PutString(sX + 109, sY + 182, cTxt, RGB(25, 35, 25));
	iStats = m_pGame->m_iInt + m_pGame->m_cLU_Int;
	wsprintf(cTxt, "%d", iStats);
	if (iStats < m_pGame->m_iInt)
	{
		PutString(sX + 162, sY + 182, cTxt, RGB(255, 0, 0));
	}
	else
	{
		PutString(sX + 162, sY + 182, cTxt, RGB(25, 35, 25));
	}
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 184) && (msY <= sY + 190))
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 184, 6, dwTime);

	// Magic
	PutString(sX + 24, sY + 201, DRAW_DIALOGBOX_LEVELUP_SETTING8, RGB(5, 5, 5));
	wsprintf(cTxt, "%d", m_pGame->m_iMag);
	PutString(sX + 109, sY + 201, cTxt, RGB(25, 35, 25));
	iStats = m_pGame->m_iMag + m_pGame->m_cLU_Mag;
	wsprintf(cTxt, "%d", iStats);
	if (iStats < m_pGame->m_iMag)
	{
		PutString(sX + 162, sY + 201, cTxt, RGB(255, 0, 0));
	}
	else
	{
		PutString(sX + 162, sY + 201, cTxt, RGB(25, 35, 25));
	}
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 203) && (msY <= sY + 209))
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 203, 6, dwTime);

	// Charisma
	PutString(sX + 24, sY + 220, DRAW_DIALOGBOX_LEVELUP_SETTING9, RGB(5, 5, 5));
	wsprintf(cTxt, "%d", m_pGame->m_iCharisma);
	PutString(sX + 109, sY + 220, cTxt, RGB(25, 35, 25));
	iStats = m_pGame->m_iCharisma + m_pGame->m_cLU_Char;
	wsprintf(cTxt, "%d", iStats);
	if (iStats < m_pGame->m_iCharisma)
	{
		PutString(sX + 162, sY + 220, cTxt, RGB(255, 0, 0));
	}
	else
	{
		PutString(sX + 162, sY + 220, cTxt, RGB(25, 35, 25));
	}
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 222) && (msY <= sY + 228))
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 222, 6, dwTime);

	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 17);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 16);

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

bool DialogBox_ChangeStatsMajestic::OnClick(short msX, short msY)
{
	short sX, sY;

	sX = Info().sX;
	sY = Info().sY;

	if ((m_pGame->cStateChange1 != 0) || (m_pGame->cStateChange2 != 0) || (m_pGame->cStateChange3 != 0)) {
		// Strength UP
		if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 127) && (msY <= sY + 133) && (m_pGame->m_cLU_Str < 0))
		{
			if (m_pGame->cStateChange1 == DEF_STR)
			{
				m_pGame->cStateChange1 = 0;
				m_pGame->m_cLU_Str += 1;
				m_pGame->m_iLU_Point -= 1;
			}
			else if (m_pGame->cStateChange2 == DEF_STR)
			{
				m_pGame->cStateChange2 = 0;
				m_pGame->m_cLU_Str += 1;
				m_pGame->m_iLU_Point -= 1;
			}
			else if (m_pGame->cStateChange3 == DEF_STR)
			{
				m_pGame->cStateChange3 = 0;
				m_pGame->m_cLU_Str += 1;
				m_pGame->m_iLU_Point -= 1;
			}
			PlaySoundEffect('E', 14, 5);
		}

		// Vitality UP
		if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 146) && (msY <= sY + 152) && (m_pGame->m_cLU_Vit < 0)) {
			if (m_pGame->cStateChange1 == DEF_VIT)
			{
				m_pGame->cStateChange1 = 0;
				m_pGame->m_cLU_Vit += 1;
				m_pGame->m_iLU_Point -= 1;
			}
			else if (m_pGame->cStateChange2 == DEF_VIT)
			{
				m_pGame->cStateChange2 = 0;
				m_pGame->m_cLU_Vit += 1;
				m_pGame->m_iLU_Point -= 1;
			}
			else if (m_pGame->cStateChange3 == DEF_VIT)
			{
				m_pGame->cStateChange3 = 0;
				m_pGame->m_cLU_Vit += 1;
				m_pGame->m_iLU_Point -= 1;
			}
			PlaySoundEffect('E', 14, 5);
		}

		// Dexterity UP
		if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 165) && (msY <= sY + 171) && (m_pGame->m_cLU_Dex < 0)) {
			if (m_pGame->cStateChange1 == DEF_DEX) {
				m_pGame->cStateChange1 = 0;
				m_pGame->m_cLU_Dex += 1;
				m_pGame->m_iLU_Point -= 1;
			}
			else if (m_pGame->cStateChange2 == DEF_DEX) {
				m_pGame->cStateChange2 = 0;
				m_pGame->m_cLU_Dex += 1;
				m_pGame->m_iLU_Point -= 1;
			}
			else if (m_pGame->cStateChange3 == DEF_DEX) {
				m_pGame->cStateChange3 = 0;
				m_pGame->m_cLU_Dex += 1;
				m_pGame->m_iLU_Point -= 1;
			}
			PlaySoundEffect('E', 14, 5);
		}

		// Intelligence UP
		if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 184) && (msY <= sY + 190) && (m_pGame->m_cLU_Int < 0)) {
			if (m_pGame->cStateChange1 == DEF_INT) {
				m_pGame->cStateChange1 = 0;
				m_pGame->m_cLU_Int += 1;
				m_pGame->m_iLU_Point -= 1;
			}
			else if (m_pGame->cStateChange2 == DEF_INT) {
				m_pGame->cStateChange2 = 0;
				m_pGame->m_cLU_Int += 1;
				m_pGame->m_iLU_Point -= 1;
			}
			else if (m_pGame->cStateChange3 == DEF_INT) {
				m_pGame->cStateChange3 = 0;
				m_pGame->m_cLU_Int += 1;
				m_pGame->m_iLU_Point -= 1;
			}
			PlaySoundEffect('E', 14, 5);
		}

		// Magic UP
		if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 203) && (msY <= sY + 209) && (m_pGame->m_cLU_Mag < 0)) {
			if (m_pGame->cStateChange1 == DEF_MAG) {
				m_pGame->cStateChange1 = 0;
				m_pGame->m_cLU_Mag += 1;
				m_pGame->m_iLU_Point -= 1;
			}
			else if (m_pGame->cStateChange2 == DEF_MAG) {
				m_pGame->cStateChange2 = 0;
				m_pGame->m_cLU_Mag += 1;
				m_pGame->m_iLU_Point -= 1;
			}
			else if (m_pGame->cStateChange3 == DEF_MAG) {
				m_pGame->cStateChange3 = 0;
				m_pGame->m_cLU_Mag += 1;
				m_pGame->m_iLU_Point -= 1;
			}
			PlaySoundEffect('E', 14, 5);
		}

		// Charisma UP
		if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 222) && (msY <= sY + 228) && (m_pGame->m_cLU_Char < 0)) {
			if (m_pGame->cStateChange1 == DEF_CHR) {
				m_pGame->cStateChange1 = 0;
				m_pGame->m_cLU_Char += 1;
				m_pGame->m_iLU_Point -= 1;
			}
			else if (m_pGame->cStateChange2 == DEF_CHR) {
				m_pGame->cStateChange2 = 0;
				m_pGame->m_cLU_Char += 1;
				m_pGame->m_iLU_Point -= 1;
			}
			else if (m_pGame->cStateChange3 == DEF_CHR) {
				m_pGame->cStateChange3 = 0;
				m_pGame->m_cLU_Char += 1;
				m_pGame->m_iLU_Point -= 1;
			}
			PlaySoundEffect('E', 14, 5);
		}
	}

	if ((m_pGame->cStateChange1 == 0) || (m_pGame->cStateChange2 == 0) || (m_pGame->cStateChange3 == 0) && (m_pGame->m_iGizonItemUpgradeLeft > 0))
	{
		// Strength DOWN
		if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 127) && (msY <= sY + 133) && (m_pGame->m_iStr > 10))
		{
			if (m_pGame->cStateChange1 == 0)
			{
				m_pGame->cStateChange1 = DEF_STR;
				m_pGame->m_cLU_Str -= 1;
				m_pGame->m_iLU_Point += 1;
			}
			else if (m_pGame->cStateChange2 == 0)
			{
				m_pGame->cStateChange2 = DEF_STR;
				m_pGame->m_cLU_Str -= 1;
				m_pGame->m_iLU_Point += 1;
			}
			else
			{
				m_pGame->cStateChange3 = DEF_STR;
				m_pGame->m_cLU_Str -= 1;
				m_pGame->m_iLU_Point += 1;
			}
			PlaySoundEffect('E', 14, 5);
		}

		// Vitality DOWN
		if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 146) && (msY <= sY + 152) && (m_pGame->m_iVit > 10)) {
			if (m_pGame->cStateChange1 == 0) {
				m_pGame->cStateChange1 = DEF_VIT;
				m_pGame->m_cLU_Vit -= 1;
				m_pGame->m_iLU_Point += 1;
			}
			else if (m_pGame->cStateChange2 == 0) {
				m_pGame->cStateChange2 = DEF_VIT;
				m_pGame->m_cLU_Vit -= 1;
				m_pGame->m_iLU_Point += 1;
			}
			else {
				m_pGame->cStateChange3 = DEF_VIT;
				m_pGame->m_cLU_Vit -= 1;
				m_pGame->m_iLU_Point += 1;
			}
			PlaySoundEffect('E', 14, 5);
		}

		// Dexterity DOWN
		if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 165) && (msY <= sY + 171) && (m_pGame->m_iDex > 10)) {
			if (m_pGame->cStateChange1 == 0) {
				m_pGame->cStateChange1 = DEF_DEX;
				m_pGame->m_cLU_Dex -= 1;
				m_pGame->m_iLU_Point += 1;
			}
			else if (m_pGame->cStateChange2 == 0) {
				m_pGame->cStateChange2 = DEF_DEX;
				m_pGame->m_cLU_Dex -= 1;
				m_pGame->m_iLU_Point += 1;
			}
			else {
				m_pGame->cStateChange3 = DEF_DEX;
				m_pGame->m_cLU_Dex -= 1;
				m_pGame->m_iLU_Point += 1;
			}
			PlaySoundEffect('E', 14, 5);
		}

		// Intelligence DOWN
		if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 184) && (msY <= sY + 190) && (m_pGame->m_iInt > 10))
		{
			if (m_pGame->cStateChange1 == 0)
			{
				m_pGame->cStateChange1 = DEF_INT;
				m_pGame->m_cLU_Int -= 1;
				m_pGame->m_iLU_Point += 1;
			}
			else if (m_pGame->cStateChange2 == 0)
			{
				m_pGame->cStateChange2 = DEF_INT;
				m_pGame->m_cLU_Int -= 1;
				m_pGame->m_iLU_Point += 1;
			}
			else
			{
				m_pGame->cStateChange3 = DEF_INT;
				m_pGame->m_cLU_Int -= 1;
				m_pGame->m_iLU_Point += 1;
			}
			PlaySoundEffect('E', 14, 5);
		}

		// Magic DOWN
		if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 203) && (msY <= sY + 209) && (m_pGame->m_iMag > 10)) {
			if (m_pGame->cStateChange1 == 0) {
				m_pGame->cStateChange1 = DEF_MAG;
				m_pGame->m_cLU_Mag -= 1;
				m_pGame->m_iLU_Point += 1;
			}
			else if (m_pGame->cStateChange2 == 0) {
				m_pGame->cStateChange2 = DEF_MAG;
				m_pGame->m_cLU_Mag -= 1;
				m_pGame->m_iLU_Point += 1;
			}
			else {
				m_pGame->cStateChange3 = DEF_MAG;
				m_pGame->m_cLU_Mag -= 1;
				m_pGame->m_iLU_Point += 1;
			}
			PlaySoundEffect('E', 14, 5);
		}

		// Charisma DOWN
		if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 222) && (msY <= sY + 228) && (m_pGame->m_iCharisma > 10)) {
			if (m_pGame->cStateChange1 == 0) {
				m_pGame->cStateChange1 = DEF_CHR;
				m_pGame->m_cLU_Char -= 1;
				m_pGame->m_iLU_Point += 1;
			}
			else if (m_pGame->cStateChange2 == 0) {
				m_pGame->cStateChange2 = DEF_CHR;
				m_pGame->m_cLU_Char -= 1;
				m_pGame->m_iLU_Point += 1;
			}
			else {
				m_pGame->cStateChange3 = DEF_CHR;
				m_pGame->m_cLU_Char -= 1;
				m_pGame->m_iLU_Point += 1;
			}
			PlaySoundEffect('E', 14, 5);
		}
	}
	else
	{
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		{
			bSendCommand(MSGID_STATECHANGEPOINT, 0, 0, 0, 0, 0, 0);
			DisableDialogBox(DialogBoxId::ChangeStatsMajestic);
			PlaySoundEffect('E', 14, 5);
		}
	}
	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		DisableDialogBox(DialogBoxId::ChangeStatsMajestic);
		PlaySoundEffect('E', 14, 5);
	}
	return false;
}
