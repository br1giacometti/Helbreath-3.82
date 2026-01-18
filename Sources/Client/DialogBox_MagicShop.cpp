#include "DialogBox_MagicShop.h"
#include "Game.h"
#include "InputManager.h"
#include "Misc.h"
#include "lan_eng.h"

DialogBox_MagicShop::DialogBox_MagicShop(CGame* pGame)
	: IDialogBox(DialogBoxId::MagicShop, pGame)
{
	SetDefaultRect(30 + SCREENX, 30 + SCREENY, 304, 328);
}

void DialogBox_MagicShop::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sX;
	short sY = m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sY;

	m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, sX, sY, 1);
	m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 14);

	// Mouse wheel scrolling - read and consume input directly
	if (m_pGame->m_dialogBoxManager.iGetTopDialogBoxIndex() == DialogBoxId::MagicShop)
	{
		short sWheelDelta = InputManager::Get().GetWheelDelta();
		if (sWheelDelta != 0)
		{
			if (sWheelDelta > 0)
				m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView--;
			if (sWheelDelta < 0)
				m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView++;
			// Consume the input
			InputManager::Get().ClearWheelDelta();
		}
	}

	// Clamp view (pages 0-9)
	if (m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView < 0)
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView = 9;
	if (m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView > 9)
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView = 0;

	// Column headers
	m_pGame->PutString(sX - 20 + 60 - 17, sY - 35 + 90, DRAW_DIALOGBOX_MAGICSHOP11, RGB(45, 25, 25)); // "Spell Name"
	m_pGame->PutString(sX - 20 + 232 - 20, sY - 35 + 90, DRAW_DIALOGBOX_MAGICSHOP12, RGB(45, 25, 25)); // "Req.Int"
	m_pGame->PutString(sX - 20 + 270, sY - 35 + 90, DRAW_DIALOGBOX_MAGICSHOP13, RGB(45, 25, 25)); // "Cost"

	DrawSpellList(sX, sY, msX, msY);
	DrawPageIndicator(sX, sY);

	m_pGame->PutAlignedString(sX, sX + m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sSizeX,
		sY + 275, DRAW_DIALOGBOX_MAGICSHOP14, 45, 25, 25);
}

void DialogBox_MagicShop::DrawSpellList(short sX, short sY, short msX, short msY)
{
	int iCPivot = m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView * 10;
	int iYloc = 0;
	char cTxt[120], cMana[10];

	for (int i = 0; i < 9; i++)
	{
		if ((m_pGame->m_pMagicCfgList[iCPivot + i] != nullptr) &&
			(m_pGame->m_pMagicCfgList[iCPivot + i]->m_bIsVisible))
		{
			wsprintf(cTxt, "%s", m_pGame->m_pMagicCfgList[iCPivot + i]->m_cName);
			CMisc::ReplaceString(cTxt, '-', ' ');

			if (m_pGame->m_cMagicMastery[iCPivot + i] != 0)
			{
				// Already mastered - purple color
				if (CMisc::bCheckIMEString(cTxt) == false)
				{
					m_pGame->PutString(sX + 24, sY + 73 + iYloc, cTxt, RGB(41, 16, 41));
					m_pGame->PutString(sX + 25, sY + 73 + iYloc, cTxt, RGB(41, 16, 41));
				}
				else
				{
					m_pGame->PutString_SprFont(sX + 24, sY + 70 + iYloc, cTxt, 5, 5, 5);
				}
				wsprintf(cMana, "%3d", m_pGame->m_pMagicCfgList[iCPivot + i]->m_sValue2);
				m_pGame->PutString_SprFont(sX + 200, sY + 70 + iYloc, cMana, 5, 5, 5);
				wsprintf(cMana, "%3d", m_pGame->m_pMagicCfgList[iCPivot + i]->m_sValue3);
				m_pGame->PutString_SprFont(sX + 241, sY + 70 + iYloc, cMana, 5, 5, 5);
			}
			else if ((msX >= sX + 24) && (msX <= sX + 24 + 135) &&
				(msY >= sY + 70 + iYloc) && (msY <= sY + 70 + 14 + iYloc))
			{
				// Hovering - white color
				if (CMisc::bCheckIMEString(cTxt) == false)
				{
					m_pGame->PutString(sX + 24, sY + 73 + iYloc, cTxt, RGB(255, 255, 255));
					m_pGame->PutString(sX + 25, sY + 73 + iYloc, cTxt, RGB(255, 255, 255));
				}
				else
				{
					m_pGame->PutString_SprFont(sX - 20 + 44, sY + 70 + iYloc, cTxt, 250, 250, 250);
				}
				wsprintf(cMana, "%3d", m_pGame->m_pMagicCfgList[iCPivot + i]->m_sValue2);
				m_pGame->PutString_SprFont(sX - 20 + 220, sY + 70 + iYloc, cMana, 250, 250, 250);
				wsprintf(cMana, "%3d", m_pGame->m_pMagicCfgList[iCPivot + i]->m_sValue3);
				m_pGame->PutString_SprFont(sX - 20 + 261, sY + 70 + iYloc, cMana, 250, 250, 250);
			}
			else
			{
				// Normal - blue color
				if (CMisc::bCheckIMEString(cTxt) == false)
				{
					m_pGame->PutString(sX + 24, sY + 73 + iYloc, cTxt, RGB(8, 0, 66));
					m_pGame->PutString(sX + 25, sY + 73 + iYloc, cTxt, RGB(8, 0, 66));
				}
				else
				{
					m_pGame->PutString_SprFont(sX - 20 + 44, sY + 70 + iYloc, cTxt, 1, 1, 8);
				}
				wsprintf(cMana, "%3d", m_pGame->m_pMagicCfgList[iCPivot + i]->m_sValue2);
				m_pGame->PutString_SprFont(sX - 20 + 220, sY + 70 + iYloc, cMana, 1, 1, 8);
				wsprintf(cMana, "%3d", m_pGame->m_pMagicCfgList[iCPivot + i]->m_sValue3);
				m_pGame->PutString_SprFont(sX - 20 + 261, sY + 70 + iYloc, cMana, 1, 1, 8);
			}
			iYloc += 18;
		}
	}
}

void DialogBox_MagicShop::DrawPageIndicator(short sX, short sY)
{
	uint32_t dwTime = m_pGame->m_dwCurTime;

	// Draw page number strip
	m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 55, sY + 250, 19, dwTime);

	// Highlight current page
	short sView = m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView;
	switch (sView)
	{
	case 0: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 44 + 31, sY + 250, 20, dwTime); break;
	case 1: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 57 + 31, sY + 250, 21, dwTime); break;
	case 2: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 75 + 31, sY + 250, 22, dwTime); break;
	case 3: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 100 + 31, sY + 250, 23, dwTime); break;
	case 4: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 120 + 31, sY + 250, 24, dwTime); break;
	case 5: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 135 + 31, sY + 250, 25, dwTime); break;
	case 6: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 156 + 31, sY + 250, 26, dwTime); break;
	case 7: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 183 + 31, sY + 250, 27, dwTime); break;
	case 8: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 216 + 31, sY + 250, 28, dwTime); break;
	case 9: m_pGame->m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 236 + 31, sY + 250, 29, dwTime); break;
	}
}

bool DialogBox_MagicShop::OnClick(short msX, short msY)
{
	short sX = m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sX;
	short sY = m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sY;

	if (HandleSpellClick(sX, sY, msX, msY))
		return true;

	HandlePageClick(sX, sY, msX, msY);
	return false;
}

bool DialogBox_MagicShop::HandleSpellClick(short sX, short sY, short msX, short msY)
{
	int iAdjX = -20;
	int iAdjY = -35;
	int iCPivot = m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView * 10;
	int iYloc = 0;

	for (int i = 0; i < 9; i++)
	{
		if ((m_pGame->m_pMagicCfgList[iCPivot + i] != nullptr) &&
			(m_pGame->m_pMagicCfgList[iCPivot + i]->m_bIsVisible))
		{
			if ((msX >= sX + iAdjX + 44) && (msX <= sX + iAdjX + 135 + 44) &&
				(msY >= sY + iAdjY + 70 + iYloc + 35) && (msY <= sY + iAdjY + 70 + 14 + iYloc + 35))
			{
				if (m_pGame->m_cMagicMastery[iCPivot + i] == 0)
				{
					m_pGame->bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_STUDYMAGIC, 0, 0, 0, 0,
						m_pGame->m_pMagicCfgList[iCPivot + i]->m_cName);
					m_pGame->PlaySound('E', 14, 5);
				}
				return true;
			}
			iYloc += 18;
		}
	}
	return false;
}

void DialogBox_MagicShop::HandlePageClick(short sX, short sY, short msX, short msY)
{
	int iAdjX = -20;
	int iAdjY = -35;

	if ((msX >= sX + iAdjX + 42 + 31) && (msX <= sX + iAdjX + 50 + 31) &&
		(msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView = 0;

	if ((msX >= sX + iAdjX + 55 + 31) && (msX <= sX + iAdjX + 68 + 31) &&
		(msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView = 1;

	if ((msX >= sX + iAdjX + 73 + 31) && (msX <= sX + iAdjX + 93 + 31) &&
		(msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView = 2;

	if ((msX >= sX + iAdjX + 98 + 31) && (msX <= sX + iAdjX + 113 + 31) &&
		(msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView = 3;

	if ((msX >= sX + iAdjX + 118 + 31) && (msX <= sX + iAdjX + 129 + 31) &&
		(msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView = 4;

	if ((msX >= sX + iAdjX + 133 + 31) && (msX <= sX + iAdjX + 150 + 31) &&
		(msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView = 5;

	if ((msX >= sX + iAdjX + 154 + 31) && (msX <= sX + iAdjX + 177 + 31) &&
		(msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView = 6;

	if ((msX >= sX + iAdjX + 181 + 31) && (msX <= sX + iAdjX + 210 + 31) &&
		(msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView = 7;

	if ((msX >= sX + iAdjX + 214 + 31) && (msX <= sX + iAdjX + 230 + 31) &&
		(msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView = 8;

	if ((msX >= sX + iAdjX + 234 + 31) && (msX <= sX + iAdjX + 245 + 31) &&
		(msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::MagicShop).sView = 9;
}


