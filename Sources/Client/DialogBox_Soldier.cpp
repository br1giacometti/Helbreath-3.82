#include "DialogBox_Soldier.h"
#include "Game.h"
#include "lan_eng.h"
#include "GlobalDef.h"
#include "SpriteID.h"
#include "ConfigManager.h"
#include "NetMessages.h"

DialogBox_Soldier::DialogBox_Soldier(CGame* pGame)
	: IDialogBox(DialogBoxId::CrusadeSoldier, pGame)
{
}

void DialogBox_Soldier::OnUpdate()
{
	uint32_t dwTime = m_pGame->G_dwGlobalTime;
	if ((dwTime - m_pGame->m_dwCommanderCommandRequestedTime) > 1000 * 10)
	{
		m_pGame->_RequestMapStatus("middleland", 1);
		m_pGame->m_dwCommanderCommandRequestedTime = dwTime;
	}
}

void DialogBox_Soldier::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX, sY, szX, szY, MapSzX, MapSzY;
	uint32_t dwTime = m_pGame->G_dwGlobalTime;
	char cMapName[120];
	double dV1, dV2, dV3;
	int tX, tY;
	sX = Info().sX;
	sY = Info().sY;
	szX = Info().sSizeX;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY - 5, 0, false, ConfigManager::Get().IsDialogTransparencyEnabled());
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21, false, ConfigManager::Get().IsDialogTransparencyEnabled());
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 17, false, ConfigManager::Get().IsDialogTransparencyEnabled());

	switch (Info().cMode) {
	case 0: // Main dlg, Map
		if (m_pGame->m_iTeleportLocX != -1)
		{
			std::memset(cMapName, 0, sizeof(cMapName));
			m_pGame->GetOfficialMapName(m_pGame->m_cTeleportMapName, cMapName);
			wsprintf(m_pGame->G_cTxt, DRAW_DIALOGBOX_SOLDIER1, cMapName, m_pGame->m_iTeleportLocX, m_pGame->m_iTeleportLocY);
			PutAlignedString(sX, sX + szX, sY + 40, m_pGame->G_cTxt);
		}
		else PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_SOLDIER2);

		if ((msX >= sX + 20) && (msX <= sX + 20 + 46)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 340, 15, dwTime);
		}
		else m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 340, 1, dwTime);

		if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 18, dwTime);
		}
		else m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 4, dwTime);

		if ((msX >= sX + 20) && (msX <= sX + 20 + 46)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_SOLDIER3, 255, 255, 255);
		}
		else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_SOLDIER4, 255, 255, 255);
		}
		break;

	case 1: // TP now
		PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_SOLDIER5);
		if ((msX >= sX + 20) && (msX <= sX + 20 + 46)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 340, 15, dwTime);
		}
		else m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 340, 1, dwTime);

		if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74 - 50, sY + 340, 19, dwTime);
		}
		else m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74 - 50, sY + 340, 20, dwTime);

		if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 18, dwTime);
		}
		else m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 4, dwTime);

		if ((msX >= sX + 20) && (msX <= sX + 20 + 46)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_SOLDIER6, 255, 255, 255);
		}
		else if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_SOLDIER7, 255, 255, 255);
		}
		else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_SOLDIER8, 255, 255, 255);
		}
		break;
	}

	// Draw map overlay
	switch (Info().cMode) {
	case 0: // Main
	case 1: // TP
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
			for (int i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++)
				if (m_pGame->m_stCrusadeStructureInfo[i].cType == 42)
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
				DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 42, false, true);
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
		if ((msX >= sX + 15) && (msX <= sX + 15 + 278)
			&& (msY >= sY + 60) && (msY <= sY + 60 + 272))
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
		break;
	}
}

bool DialogBox_Soldier::OnClick(short msX, short msY)
{
	short sX, sY;
	if (m_pGame->m_bIsCrusadeMode == false) return false;
	sX = Info().sX;
	sY = Info().sY;

	switch (Info().cMode) {
	case 0: // Main dlg
		if ((msX >= sX + 20) && (msX <= sX + 20 + 46) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
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
				Info().cMode = 1;
				PlaySoundEffect('E', 14, 5);
			}
		}
		if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			DisableDialogBox(DialogBoxId::Text);
			EnableDialogBox(DialogBoxId::Text, 803, 0, 0);
			PlaySoundEffect('E', 14, 5);
		}
		break;

	case 1: // Use TP
		if ((msX >= sX + 20) && (msX <= sX + 20 + 46 + 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GUILDTELEPORT, 0, 0, 0, 0, 0);
			DisableDialogBox(DialogBoxId::CrusadeSoldier);
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
			EnableDialogBox(DialogBoxId::Text, 804, 0, 0);
			PlaySoundEffect('E', 14, 5);
		}
		break;
	}
	return false;
}
