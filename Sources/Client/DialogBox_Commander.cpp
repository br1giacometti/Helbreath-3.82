#include "DialogBox_Commander.h"
#include "Game.h"
#include "lan_eng.h"
#include "GlobalDef.h"
#include "SpriteID.h"
#include "ConfigManager.h"
#include "NetMessages.h"

DialogBox_Commander::DialogBox_Commander(CGame* pGame)
	: IDialogBox(DialogBoxId::CrusadeCommander, pGame)
{
}

void DialogBox_Commander::OnUpdate()
{
	uint32_t dwTime = m_pGame->G_dwGlobalTime;
	if ((dwTime - m_pGame->m_dwCommanderCommandRequestedTime) > 1000 * 10)
	{
		m_pGame->_RequestMapStatus("middleland", 3);
		m_pGame->_RequestMapStatus("middleland", 1);
		m_pGame->m_dwCommanderCommandRequestedTime = dwTime;
	}
}

void DialogBox_Commander::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX, sY, szX, szY, MapSzX, MapSzY;
	uint32_t dwTime = m_pGame->G_dwGlobalTime;
	double dV1, dV2, dV3;
	int i, tX, tY;
	sX = Info().sX;
	sY = Info().sY;
	szX = Info().sSizeX;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY - 5, 0, false, ConfigManager::Get().IsDialogTransparencyEnabled());
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 15, false, ConfigManager::Get().IsDialogTransparencyEnabled());

	switch (Info().cMode) {
	case 0: // Main dlg
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 340, 3, dwTime);
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 340, 1, dwTime);
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100, sY + 340, 2, dwTime);
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150, sY + 340, 30, dwTime);
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 4, dwTime);
		PutAlignedString(sX, sX + szX, sY + 37, DRAW_DIALOGBOX_COMMANDER1);

		if ((msX >= sX + 20) && (msX <= sX + 20 + 46) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 340, 17, dwTime);
			PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER2, 255, 255, 255);
		}
		else if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 46 + 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 340, 15, dwTime);
			PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER3, 255, 255, 255);
		}
		else if ((msX >= sX + 20 + 100) && (msX <= sX + 20 + 46 + 100) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100, sY + 340, 16, dwTime);
			PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER4, 255, 255, 255);
		}
		else if ((msX >= sX + 20 + 150) && (msX <= sX + 20 + 46 + 150) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150, sY + 340, 24, dwTime);
			PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER5, 255, 255, 255);
		}
		else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 18, dwTime);
			PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER6, 255, 255, 255);
		}
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21, false, ConfigManager::Get().IsDialogTransparencyEnabled());
		break;

	case 1: // Set TP
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 20, dwTime);
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 4, dwTime);
		PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_COMMANDER7);

		if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 19, dwTime);
			PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER8, 255, 255, 255);
		}
		else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 18, dwTime);
			PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER9, 255, 255, 255);
		}
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21, false, ConfigManager::Get().IsDialogTransparencyEnabled());

		if ((msX >= sX + 15) && (msX <= sX + 15 + 278) && (msY >= sY + 60) && (msY <= sY + 60 + 272))
		{
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, msX, msY, 42, false, true);
		}
		break;

	case 2: // Use TP
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 340, 1, dwTime);
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 20, dwTime);
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 4, dwTime);
		PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_COMMANDER10);

		if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 46 + 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 340, 15, dwTime);
			PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER11, 255, 255, 255);
		}
		else if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 19, dwTime);
			PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER12, 255, 255, 255);
		}
		else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 18, dwTime);
			PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER13, 255, 255, 255);
		}
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21, false, ConfigManager::Get().IsDialogTransparencyEnabled());
		break;

	case 3: // Choose summon
		if ((m_pGame->m_bCitizen == true) && (m_pGame->m_bAresden == true))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 220, 6, dwTime);
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 220, 5, dwTime);
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100, sY + 220, 7, dwTime);
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150, sY + 220, 35, dwTime);
		}
		else if ((m_pGame->m_bCitizen == true) && (m_pGame->m_bAresden == false))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 220, 9, dwTime);
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 220, 8, dwTime);
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100, sY + 220, 7, dwTime);
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150, sY + 220, 35, dwTime);
		}
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 20, dwTime);
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 4, dwTime);

		PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_COMMANDER14);

		wsprintf(m_pGame->G_cTxt, "%s %d", DRAW_DIALOGBOX_COMMANDER15, m_pGame->m_iConstructionPoint);
		PutAlignedString(sX, sX + 323, sY + 190, m_pGame->G_cTxt);

		if ((m_pGame->m_bCitizen == true) && (m_pGame->m_bAresden == true))
		{
			if ((msX >= sX + 20) && (msX <= sX + 20 + 46) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
			{
				if (m_pGame->m_iConstructionPoint >= 3000)
				{
					m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 220, 11, dwTime);
				}
				PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER16, 255, 255, 255);
				PutString2(msX + 20, msY + 50, DRAW_DIALOGBOX_COMMANDER17, 255, 255, 255);
			}
			else if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 50 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
			{
				if (m_pGame->m_iConstructionPoint >= 2000)
				{
					m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 220, 10, dwTime);
				}
				PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER18, 255, 255, 255);
				PutString2(msX + 20, msY + 50, DRAW_DIALOGBOX_COMMANDER19, 255, 255, 255);
			}
			else if ((msX >= sX + 20 + 100) && (msX <= sX + 20 + 100 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
			{
				if (m_pGame->m_iConstructionPoint >= 1000)
				{
					m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100, sY + 220, 12, dwTime);
				}
				PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER20, 255, 255, 255);
				PutString2(msX + 20, msY + 50, DRAW_DIALOGBOX_COMMANDER21, 255, 255, 255);
			}
			else if ((msX >= sX + 20 + 150) && (msX <= sX + 20 + 150 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
			{
				if (m_pGame->m_iConstructionPoint >= 5000)
				{
					m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150, sY + 220, 29, dwTime);
				}
				PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER22, 255, 255, 255);
				PutString2(msX + 20, msY + 50, DRAW_DIALOGBOX_COMMANDER23, 255, 255, 255);
			}
			else if ((msX >= sX + 20) && (msX <= sX + 380) && (msY > sY + 140) && (msY < sY + 160))
			{
				PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER24, 255, 255, 255);
			}
			else if ((msX >= sX + 20) && (msX <= sX + 380) && (msY > sY + 160) && (msY < sY + 175))
			{
				PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER25, 255, 255, 255);
			}
			else if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
			{
				m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 19, dwTime);
				PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER26, 255, 255, 255);
			}
			else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
			{
				m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 18, dwTime);
				PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER27, 255, 255, 255);
			}
		}
		else if ((m_pGame->m_bCitizen == true) && (m_pGame->m_bAresden == false))
		{
			if ((msX >= sX + 20) && (msX <= sX + 20 + 46) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
			{
				if (m_pGame->m_iConstructionPoint >= 3000)
				{
					m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 220, 14, dwTime);
				}
				PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER28, 255, 255, 255);
				PutString2(msX + 20, msY + 50, DRAW_DIALOGBOX_COMMANDER29, 255, 255, 255);
			}
			else if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 50 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
			{
				if (m_pGame->m_iConstructionPoint >= 2000)
				{
					m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 220, 13, dwTime);
				}
				PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER30, 255, 255, 255);
				PutString2(msX + 20, msY + 50, DRAW_DIALOGBOX_COMMANDER31, 255, 255, 255);
			}
			else if ((msX >= sX + 20 + 100) && (msX <= sX + 20 + 100 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
			{
				if (m_pGame->m_iConstructionPoint >= 1000)
				{
					m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100, sY + 220, 12, dwTime);
				}
				PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER32, 255, 255, 255);
				PutString2(msX + 20, msY + 50, DRAW_DIALOGBOX_COMMANDER33, 255, 255, 255);
			}
			else if ((msX >= sX + 20 + 150) && (msX <= sX + 20 + 150 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
			{
				if (m_pGame->m_iConstructionPoint >= 5000)
				{
					m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150, sY + 220, 29, dwTime);
				}
				PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER34, 255, 255, 255);
				PutString2(msX + 20, msY + 50, DRAW_DIALOGBOX_COMMANDER35, 255, 255, 255);
			}
			else if ((msX >= sX + 20) && (msX <= sX + 380) && (msY > sY + 140) && (msY < sY + 160))
			{
				PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER36, 255, 255, 255);
			}
			else if ((msX >= sX + 20) && (msX <= sX + 380) && (msY > sY + 160) && (msY < sY + 175))
			{
				PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER37, 255, 255, 255);
			}
			else if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
			{
				m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 19, dwTime);
				PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER38, 255, 255, 255);
			}
			else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
			{
				m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 18, dwTime);
				PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER39, 255, 255, 255);
			}
		}
		PutAlignedString(sX, sX + 323, sY + 80, DRAW_DIALOGBOX_COMMANDER40);
		PutAlignedString(sX, sX + 323, sY + 95, DRAW_DIALOGBOX_COMMANDER41);
		PutAlignedString(sX, sX + 323, sY + 110, DRAW_DIALOGBOX_COMMANDER42);

		switch (Info().sV1) {
		case 0:
			PutAlignedString(sX, sX + 323, sY + 140, DRAW_DIALOGBOX_COMMANDER43, 255, 255, 255);
			PutAlignedString(sX, sX + 323, sY + 160, DRAW_DIALOGBOX_COMMANDER44, 4, 0, 50);
			break;
		case 1:
			PutAlignedString(sX, sX + 323, sY + 140, DRAW_DIALOGBOX_COMMANDER43, 4, 0, 50);
			PutAlignedString(sX, sX + 323, sY + 160, DRAW_DIALOGBOX_COMMANDER44, 255, 255, 255);
			break;
		}
		break;

	case 4: // Set Construction point
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 20, dwTime);
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 4, dwTime);
		PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_COMMANDER47);

		if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 19, dwTime);
			PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER48, 255, 255, 255);
		}
		else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 18, dwTime);
			PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER49, 255, 255, 255);
		}
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21);
		if ((msX >= sX + 15) && (msX <= sX + 15 + 278) && (msY >= sY + 60) && (msY <= sY + 60 + 272))
		{
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, msX, msY, 41, false, true);
		}
		break;
	}

	// Draw map structures and positions
	switch (Info().cMode) {
	case 0:
	case 1:
	case 2:
	case 4:
		szX = 0;
		szY = 0;
		MapSzX = 0;
		MapSzY = 0;
		if (strcmp(m_pGame->m_cStatusMapName, "aresden") == 0)
		{
			szX = 250;
			szY = 250;
		}
		else if (strcmp(m_pGame->m_cStatusMapName, "elvine") == 0)
		{
			szX = 250;
			szY = 250;
		}
		else if (strcmp(m_pGame->m_cStatusMapName, "middleland") == 0)
		{
			szX = 279;
			szY = 280;
			MapSzX = 524;
			MapSzY = 524;
		}
		if (szX != 0)
		{
			for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++)
				if (m_pGame->m_stCrusadeStructureInfo[i].cType != 0)
				{
					dV1 = (double)MapSzX;
					dV2 = (double)m_pGame->m_stCrusadeStructureInfo[i].sX;
					dV3 = (dV2 * (double)szX) / dV1;
					tX = (int)dV3;
					dV1 = (double)MapSzY;
					dV2 = (double)m_pGame->m_stCrusadeStructureInfo[i].sY;
					dV3 = (dV2 * (double)szY) / dV1;
					tY = (int)dV3;
					switch (m_pGame->m_stCrusadeStructureInfo[i].cType) {
					case 38:
						if (m_pGame->m_stCrusadeStructureInfo[i].cSide == 1)
							DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 39, false, true);
						else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 37, false, true);
						break;
					case 36:
					case 37:
					case 39:
						if (m_pGame->m_stCrusadeStructureInfo[i].cSide == 1)
							DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 38, false, true);
						else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 36, false, true);
						break;
					case 42:
						DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 40);
						break;
					}
				}
			if (m_pGame->m_iTeleportLocX != -1)
			{
				dV1 = (double)MapSzX;
				dV2 = (double)m_pGame->m_iTeleportLocX;
				dV3 = (dV2 * (double)szX) / dV1;
				tX = (int)dV3;
				dV1 = (double)MapSzY;
				dV2 = (double)m_pGame->m_iTeleportLocY;
				dV3 = (dV2 * (double)szY) / dV1;
				tY = (int)dV3;
				if ((Info().cMode == 1) && (tY >= 30) && (tY <= 494))
				{
					DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 42, false, true);
				}
				else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 42, false, true);
			}
			if ((Info().cMode != 2) && (m_pGame->m_iConstructLocX != -1))
			{
				dV1 = (double)MapSzX;
				dV2 = (double)m_pGame->m_iConstructLocX;
				dV3 = (dV2 * (double)szX) / dV1;
				tX = (int)dV3;
				dV1 = (double)MapSzY;
				dV2 = (double)m_pGame->m_iConstructLocY;
				dV3 = (dV2 * (double)szY) / dV1;
				tY = (int)dV3;
				DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 41, false, true);
			}
			if (strcmp(m_pGame->m_cMapName, "middleland") == 0)
			{
				dV1 = (double)MapSzX;
				dV2 = (double)m_pGame->m_sPlayerX;
				dV3 = (dV2 * (double)szX) / dV1;
				tX = (int)dV3;
				dV1 = (double)MapSzY;
				dV2 = (double)m_pGame->m_sPlayerY;
				dV3 = (dV2 * (double)szY) / dV1;
				tY = (int)dV3;
				DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 43);
			}
		}
		if (Info().cMode != 3)
		{
			if ((msX >= sX + 15) && (msX <= sX + 15 + 278) && (msY >= sY + 60) && (msY <= sY + 60 + 272))
			{
				dV1 = (double)(msX - (sX + 15));
				dV2 = (double)MapSzX;
				dV3 = (dV2 * dV1) / szX;
				tX = (int)dV3;
				dV1 = (double)(msY - (sY + 60));
				dV2 = (double)MapSzX;
				dV3 = (dV2 * dV1) / szY;
				tY = (int)dV3;
				if (tX < 30) tX = 30;
				if (tY < 30) tY = 30;
				if (tX > MapSzX - 30) tX = MapSzX - 30;
				if (tY > MapSzY - 30) tY = MapSzY - 30;
				wsprintf(m_pGame->G_cTxt, "%d,%d", tX, tY);
				m_pGame->PutString_SprFont3(msX + 10, msY - 10, m_pGame->G_cTxt, m_pGame->m_wR[13] * 4, m_pGame->m_wG[13] * 4, m_pGame->m_wB[13] * 4, false, 2);
			}
		}
		break;
	}
}

bool DialogBox_Commander::OnClick(short msX, short msY)
{
	short sX, sY, tX, tY;
	double d1, d2, d3;

	if (m_pGame->m_bIsCrusadeMode == false) return false;

	sX = Info().sX;
	sY = Info().sY;

	switch (Info().cMode) {
	case 0: // Main
		if ((msX >= sX + 20) && (msX <= sX + 20 + 46) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			Info().cMode = 1;
			PlaySoundEffect('E', 14, 5);
		}
		if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 46 + 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			if (m_pGame->m_iTeleportLocX == -1)
			{
				m_pGame->SetTopMsg(m_pGame->m_pGameMsgList[15]->m_pMsg, 5);
			}
			else if (strcmp(m_pGame->m_cMapName, m_pGame->m_cTeleportMapName) == 0)
			{
				m_pGame->SetTopMsg(m_pGame->m_pGameMsgList[16]->m_pMsg, 5);
			}
			else
			{
				Info().cMode = 2;
				PlaySoundEffect('E', 14, 5);
			}
		}
		if ((msX >= sX + 20 + 100) && (msX <= sX + 20 + 46 + 100) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			Info().cMode = 3;
			Info().sV1 = 0;
			PlaySoundEffect('E', 14, 5);
		}
		if ((msX >= sX + 20 + 150) && (msX <= sX + 20 + 46 + 150) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			Info().cMode = 4;
			PlaySoundEffect('E', 14, 5);
		}
		if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			DisableDialogBox(DialogBoxId::Text);
			EnableDialogBox(DialogBoxId::Text, 808, 0, 0);
			PlaySoundEffect('E', 14, 5);
		}
		break;

	case 1: // Set TP
		if ((msX >= sX + 15) && (msX <= sX + 15 + 278) && (msY >= sY + 60) && (msY <= sY + 60 + 272))
		{
			d1 = (double)(msX - (sX + 15));
			d2 = (double)(524.0f);
			d3 = (d2 * d1) / 279.0f;
			tX = (int)d3;
			d1 = (double)(msY - (sY + 60));
			d2 = (double)(524.0f);
			d3 = (d2 * d1) / (280.0f);
			tY = (int)d3;
			if (tX < 30) tX = 30;
			if (tY < 30) tY = 30;
			if (tX > 494) tX = 494;
			if (tY > 494) tY = 494;
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SETGUILDTELEPORTLOC, 0, tX, tY, 0, "middleland");
			Info().cMode = 0;
			PlaySoundEffect('E', 14, 5);
			m_pGame->_RequestMapStatus("middleland", 1);
		}
		if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			Info().cMode = 0;
			PlaySoundEffect('E', 14, 5);
		}
		if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			DisableDialogBox(DialogBoxId::Text);
			EnableDialogBox(DialogBoxId::Text, 809, 0, 0);
			PlaySoundEffect('E', 14, 5);
		}
		break;

	case 2: // Use TP
		if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 46 + 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GUILDTELEPORT, 0, 0, 0, 0, 0);
			DisableDialogBox(DialogBoxId::CrusadeCommander);
			PlaySoundEffect('E', 14, 5);
		}
		if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			Info().cMode = 0;
			PlaySoundEffect('E', 14, 5);
		}
		if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			DisableDialogBox(DialogBoxId::Text);
			EnableDialogBox(DialogBoxId::Text, 810, 0, 0);
			PlaySoundEffect('E', 14, 5);
		}
		break;

	case 3: // Summon Unit
		if (m_pGame->m_bAresden == true)
		{
			if ((msX >= sX + 20) && (msX <= sX + 20 + 46) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
			{
				if (m_pGame->m_iConstructionPoint >= 3000)
				{
					bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 47, 1, Info().sV1, 0);
					PlaySoundEffect('E', 14, 5);
					DisableDialogBox(DialogBoxId::CrusadeCommander);
				}
			}
			if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 50 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
			{
				if (m_pGame->m_iConstructionPoint >= 2000)
				{
					bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 46, 1, Info().sV1, 0);
					PlaySoundEffect('E', 14, 5);
					DisableDialogBox(DialogBoxId::CrusadeCommander);
				}
			}
			if ((msX >= sX + 20 + 100) && (msX <= sX + 20 + 100 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
			{
				if (m_pGame->m_iConstructionPoint >= 1000)
				{
					bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 43, 1, Info().sV1, 0);
					PlaySoundEffect('E', 14, 5);
					DisableDialogBox(DialogBoxId::CrusadeCommander);
				}
			}
			if ((msX >= sX + 20 + 150) && (msX <= sX + 20 + 150 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
			{
				if (m_pGame->m_iConstructionPoint >= 1500)
				{
					bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 51, 1, Info().sV1, 0);
					PlaySoundEffect('E', 14, 5);
					DisableDialogBox(DialogBoxId::CrusadeCommander);
				}
			}
		}
		else if (m_pGame->m_bAresden == false)
		{
			if ((msX >= sX + 20) && (msX <= sX + 20 + 46) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
			{
				if (m_pGame->m_iConstructionPoint >= 3000)
				{
					bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 45, 1, Info().sV1, 0);
					PlaySoundEffect('E', 14, 5);
					DisableDialogBox(DialogBoxId::CrusadeCommander);
				}
			}
			if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 50 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
			{
				if (m_pGame->m_iConstructionPoint >= 2000)
				{
					bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 44, 1, Info().sV1, 0);
					PlaySoundEffect('E', 14, 5);
					DisableDialogBox(DialogBoxId::CrusadeCommander);
				}
			}
			if ((msX >= sX + 20 + 100) && (msX <= sX + 20 + 100 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
			{
				if (m_pGame->m_iConstructionPoint >= 1000)
				{
					bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 43, 1, Info().sV1, 0);
					PlaySoundEffect('E', 14, 5);
					DisableDialogBox(DialogBoxId::CrusadeCommander);
				}
			}
			if ((msX >= sX + 20 + 150) && (msX <= sX + 20 + 150 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
			{
				if (m_pGame->m_iConstructionPoint >= 1500)
				{
					bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 51, 1, Info().sV1, 0);
					PlaySoundEffect('E', 14, 5);
					DisableDialogBox(DialogBoxId::CrusadeCommander);
				}
			}
		}
		if ((msX >= sX + 20) && (msX <= sX + 380) && (msY > sY + 140) && (msY < sY + 160))
		{
			Info().sV1 = 0;
			PlaySoundEffect('E', 14, 5);
		}
		if ((msX >= sX + 20) && (msX <= sX + 380) && (msY > sY + 160) && (msY < sY + 175))
		{
			Info().sV1 = 1;
			PlaySoundEffect('E', 14, 5);
		}
		if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			Info().cMode = 0;
			PlaySoundEffect('E', 14, 5);
		}
		if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			DisableDialogBox(DialogBoxId::Text);
			EnableDialogBox(DialogBoxId::Text, 811, 0, 0);
			PlaySoundEffect('E', 14, 5);
		}
		break;

	case 4: // Set constr
		if ((msX >= sX + 15) && (msX <= sX + 15 + 278) && (msY >= sY + 60) && (msY <= sY + 60 + 272))
		{
			d1 = (double)(msX - (sX + 15));
			d2 = (double)(524.0);
			d3 = (d2 * d1) / 279.0f;
			tX = (int)d3;
			d1 = (double)(msY - (sY + 60));
			d2 = (double)(524.0);
			d3 = (d2 * d1) / (280.0);
			tY = (int)d3;
			if (tX < 30) tX = 30;
			if (tY < 30) tY = 30;
			if (tX > 494) tX = 494;
			if (tY > 494) tY = 494;
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SETGUILDCONSTRUCTLOC, 0, tX, tY, 0, "middleland");
			Info().cMode = 0;
			PlaySoundEffect('E', 14, 5);
			m_pGame->_RequestMapStatus("middleland", 1);
		}
		if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			Info().cMode = 0;
			PlaySoundEffect('E', 14, 5);
		}
		if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			DisableDialogBox(DialogBoxId::Text);
			EnableDialogBox(DialogBoxId::Text, 812, 0, 0);
			PlaySoundEffect('E', 14, 5);
		}
		break;
	}

	return false;
}
