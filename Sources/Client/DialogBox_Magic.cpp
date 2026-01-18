#include "DialogBox_Magic.h"
#include "ConfigManager.h"
#include "Game.h"
#include "InputManager.h"
#include "Misc.h"
#include "lan_eng.h"

DialogBox_Magic::DialogBox_Magic(CGame* pGame)
	: IDialogBox(DialogBoxId::Magic, pGame)
{
	SetDefaultRect(337 + SCREENX, 57 + SCREENY, 258, 328);
}

void DialogBox_Magic::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX, sY;
	int iCPivot, i, iYloc, iMagicCircle, iManaCost;
	const bool dialogTrans = ConfigManager::Get().IsDialogTransparencyEnabled();
	char cTxt[120], cMana[10];
	double dV1, dV2, dV3, dV4;
	int iResult;
	short sLevelMagic;
	uint32_t dwTime = m_pGame->m_dwCurTime;

	sX = Info().sX;
	sY = Info().sY;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME1, sX, sY, 1, false, dialogTrans);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 7, false, dialogTrans);

	// Handle scroll wheel input
	if (m_pGame->m_dialogBoxManager.iGetTopDialogBoxIndex() == DialogBoxId::Magic && msZ != 0)
	{
		if (msZ > 0) Info().sView--;
		if (msZ < 0) Info().sView++;
		InputManager::Get().ClearWheelDelta();
	}
	if (Info().sView < 0) Info().sView = 9;
	if (Info().sView > 9) Info().sView = 0;

	// Circle title
	std::memset(cTxt, 0, sizeof(cTxt));
	switch (Info().sView) {
	case 0: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC1);  break;
	case 1: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC2);  break;
	case 2: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC3);  break;
	case 3: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC4);  break;
	case 4: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC5);  break;
	case 5: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC6);  break;
	case 6: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC7);  break;
	case 7: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC8);  break;
	case 8: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC9);  break;
	case 9: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC10); break;
	}
	PutAlignedString(sX + 3, sX + 256, sY + 50, cTxt);
	PutAlignedString(sX + 4, sX + 257, sY + 50, cTxt);

	iCPivot = Info().sView * 10;
	iYloc = 0;
	for (i = 0; i < 9; i++)
	{
		if ((m_pGame->m_cMagicMastery[iCPivot + i] != 0) && (m_pGame->m_pMagicCfgList[iCPivot + i] != 0))
		{
			wsprintf(cTxt, "%s", m_pGame->m_pMagicCfgList[iCPivot + i]->m_cName);
			CMisc::ReplaceString(cTxt, '-', ' ');

			iManaCost = m_pGame->iGetManaCost(iCPivot + i);

			if (iManaCost > m_pGame->m_iMP)
			{
				// Insufficient mana - grayed out
				if (CMisc::bCheckIMEString(cTxt) == false)
				{
					PutString(sX + 30, sY + 73 + iYloc, cTxt, RGB(41, 16, 41));
					PutString(sX + 31, sY + 73 + iYloc, cTxt, RGB(41, 16, 41));
				}
				else
					m_pGame->PutString_SprFont(sX + 30, sY + 70 + iYloc, cTxt, 5, 5, 5);
				wsprintf(cMana, "%3d", iManaCost);
				m_pGame->PutString_SprFont(sX + 206, sY + 70 + iYloc, cMana, 5, 5, 5);
			}
			else if ((msX >= sX + 30) && (msX <= sX + 240) && (msY >= sY + 70 + iYloc) && (msY <= sY + 70 + 14 + iYloc))
			{
				// Mouse hover - highlighted
				if (CMisc::bCheckIMEString(cTxt) == false)
				{
					PutString(sX + 30, sY + 73 + iYloc, cTxt, RGB(255, 255, 255));
					PutString(sX + 31, sY + 73 + iYloc, cTxt, RGB(255, 255, 255));
				}
				else
					m_pGame->PutString_SprFont(sX + 30, sY + 70 + iYloc, cTxt, 250, 250, 250);
				wsprintf(cMana, "%3d", iManaCost);
				m_pGame->PutString_SprFont(sX + 206, sY + 70 + iYloc, cMana, 250, 250, 250);
			}
			else
			{
				// Normal - default color
				if (CMisc::bCheckIMEString(cTxt) == false)
				{
					PutString(sX + 30, sY + 73 + iYloc, cTxt, RGB(8, 0, 66));
					PutString(sX + 31, sY + 73 + iYloc, cTxt, RGB(8, 0, 66));
				}
				else
					m_pGame->PutString_SprFont(sX + 30, sY + 70 + iYloc, cTxt, 1, 1, 8);
				wsprintf(cMana, "%3d", iManaCost);
				m_pGame->PutString_SprFont(sX + 206, sY + 70 + iYloc, cMana, 1, 1, 8);
			}

			iYloc += 18;
		}
	}

	// No spells message
	if (iYloc == 0)
	{
		PutAlignedString(sX + 3, sX + 256, sY + 100, DRAW_DIALOGBOX_MAGIC11);
		PutAlignedString(sX + 3, sX + 256, sY + 115, DRAW_DIALOGBOX_MAGIC12);
		PutAlignedString(sX + 3, sX + 256, sY + 130, DRAW_DIALOGBOX_MAGIC13);
		PutAlignedString(sX + 3, sX + 256, sY + 145, DRAW_DIALOGBOX_MAGIC14);
		PutAlignedString(sX + 3, sX + 256, sY + 160, DRAW_DIALOGBOX_MAGIC15);
	}

	// Circle selector bar
	m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 30, sY + 250, 19, dwTime);

	// Circle selector highlight
	switch (Info().sView) {
	case 0: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 30, sY + 250, 20, dwTime); break;
	case 1: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 43, sY + 250, 21, dwTime); break;
	case 2: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 61, sY + 250, 22, dwTime); break;
	case 3: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 86, sY + 250, 23, dwTime); break;
	case 4: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 106, sY + 250, 24, dwTime); break;
	case 5: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 121, sY + 250, 25, dwTime); break;
	case 6: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 142, sY + 250, 26, dwTime); break;
	case 7: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 169, sY + 250, 27, dwTime); break;
	case 8: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 202, sY + 250, 28, dwTime); break;
	case 9: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 222, sY + 250, 29, dwTime); break;
	}

	// Calculate magic probability
	iMagicCircle = Info().sView + 1;

	static int _tmp_iMCProb[] = { 0, 300, 250, 200, 150, 100, 80, 70, 60, 50, 40 };
	static int _tmp_iMLevelPenalty[] = { 0,   5,   5,   8,   8,  10, 14, 28, 32, 36, 40 };

	if (m_pGame->m_cSkillMastery[4] == 0)
		dV1 = 1.0f;
	else
		dV1 = (double)m_pGame->m_cSkillMastery[4];

	dV2 = (double)(dV1 / 100.0f);
	dV3 = (double)_tmp_iMCProb[iMagicCircle];
	dV1 = dV2 * dV3;
	iResult = (int)dV1;

	if ((m_pGame->m_iInt + m_pGame->m_iAngelicInt) > 50)
		iResult += ((m_pGame->m_iInt + m_pGame->m_iAngelicInt) - 50) / 2;

	sLevelMagic = (m_pGame->m_iLevel / 10);
	if (iMagicCircle != sLevelMagic)
	{
		if (iMagicCircle > sLevelMagic)
		{
			dV1 = (double)(m_pGame->m_iLevel - sLevelMagic * 10);
			dV2 = (double)abs(iMagicCircle - sLevelMagic) * _tmp_iMLevelPenalty[iMagicCircle];
			dV3 = (double)abs(iMagicCircle - sLevelMagic) * 10;
			dV4 = (dV1 / dV3) * dV2;
			iResult -= abs(abs(iMagicCircle - sLevelMagic) * _tmp_iMLevelPenalty[iMagicCircle] - (int)dV4);
		}
		else
		{
			iResult += 5 * abs(iMagicCircle - sLevelMagic);
		}
	}

	// Weather modifier
	switch (m_pGame->m_cWhetherStatus)
	{
	case 0: break;
	case 1: iResult = iResult - (iResult / 24); break;
	case 2: iResult = iResult - (iResult / 12); break;
	case 3: iResult = iResult - (iResult / 5);  break;
	}

	// Equipment magic bonus
	for (i = 0; i < DEF_MAXITEMS; i++)
	{
		if (m_pGame->m_pItemList[i] == 0) continue;
		if (m_pGame->m_bIsItemEquipped[i] == true)
		{
			if (((m_pGame->m_pItemList[i]->m_dwAttribute & 0x00F00000) >> 20) == 10)
			{
				dV1 = (double)iResult;
				dV2 = (double)(((m_pGame->m_pItemList[i]->m_dwAttribute & 0x000F0000) >> 16) * 3);
				dV3 = dV1 + dV2;
				iResult = (int)dV3;
				break;
			}
		}
	}

	if (iResult > 100) iResult = 100;
	if (m_pGame->m_iSP < 1) iResult = iResult * 9 / 10;
	if (iResult < 1) iResult = 1;

	// Display magic probability
	std::memset(cTxt, 0, sizeof(cTxt));
	wsprintf(cTxt, DRAW_DIALOGBOX_MAGIC16, iResult);
	PutAlignedString(sX, sX + 256, sY + 267, cTxt);
	PutAlignedString(sX + 1, sX + 257, sY + 267, cTxt);

	// Alchemy button
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 285) && (msY <= sY + 285 + DEF_BTNSZY))
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + 285, 49, false, dialogTrans);
	else
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + 285, 48, false, dialogTrans);
}

bool DialogBox_Magic::OnClick(short msX, short msY)
{
	int i, iCPivot, iYloc;
	short sX, sY;

	sX = Info().sX;
	sY = Info().sY;
	iCPivot = Info().sView * 10;
	iYloc = 0;
	for (i = 0; i < 9; i++)
	{
		if ((m_pGame->m_cMagicMastery[iCPivot + i] != 0) && (m_pGame->m_pMagicCfgList[iCPivot + i] != 0))
		{
			if ((msX >= sX + 30) && (msX <= sX + 240) && (msY >= sY + 70 + iYloc) && (msY <= sY + 70 + 18 + iYloc))
			{
				m_pGame->UseMagic(iCPivot + i);
				PlaySoundEffect('E', 14, 5);
				return true;
			}
			iYloc += 18;
		}
	}
	if ((msX >= sX + 16) && (msX <= sX + 38) && (msY >= sY + 240) && (msY <= sY + 268))
		Info().sView = 0;
	if ((msX >= sX + 39) && (msX <= sX + 56) && (msY >= sY + 240) && (msY <= sY + 268))
		Info().sView = 1;
	if ((msX >= sX + 57) && (msX <= sX + 81) && (msY >= sY + 240) && (msY <= sY + 268))
		Info().sView = 2;
	if ((msX >= sX + 82) && (msX <= sX + 101) && (msY >= sY + 240) && (msY <= sY + 268))
		Info().sView = 3;
	if ((msX >= sX + 102) && (msX <= sX + 116) && (msY >= sY + 240) && (msY <= sY + 268))
		Info().sView = 4;
	if ((msX >= sX + 117) && (msX <= sX + 137) && (msY >= sY + 240) && (msY <= sY + 268))
		Info().sView = 5;
	if ((msX >= sX + 138) && (msX <= sX + 165) && (msY >= sY + 240) && (msY <= sY + 268))
		Info().sView = 6;
	if ((msX >= sX + 166) && (msX <= sX + 197) && (msY >= sY + 240) && (msY <= sY + 268))
		Info().sView = 7;
	if ((msX >= sX + 198) && (msX <= sX + 217) && (msY >= sY + 240) && (msY <= sY + 268))
		Info().sView = 8;
	if ((msX >= sX + 218) && (msX <= sX + 239) && (msY >= sY + 240) && (msY <= sY + 268))
		Info().sView = 9;

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 285) && (msY <= sY + 285 + DEF_BTNSZY))
	{
		if (m_pGame->m_cSkillMastery[12] == 0) AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY16, 10);
		else
		{
			for (i = 0; i < DEF_MAXITEMS; i++)
				if ((m_pGame->m_pItemList[i] != 0) && (m_pGame->m_pItemList[i]->m_cItemType == DEF_ITEMTYPE_USE_SKILL_ENABLEDIALOGBOX) &&
					(m_pGame->m_pItemList[i]->m_sSpriteFrame == 55))
				{
					EnableDialogBox(DialogBoxId::Manufacture, 1, 0, 0, 0);
					AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY10, 10);
					PlaySoundEffect('E', 14, 5);
					return true;
				}
			AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY15, 10);
		}
		PlaySoundEffect('E', 14, 5);
	}
	return false;
}
