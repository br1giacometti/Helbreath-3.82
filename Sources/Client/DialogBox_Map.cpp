#include "DialogBox_Map.h"
#include "ConfigManager.h"
#include "Game.h"
#include "GlobalDef.h"

DialogBox_Map::DialogBox_Map(CGame* pGame)
	: IDialogBox(DialogBoxId::Map, pGame)
{
	SetDefaultRect(336 + SCREENX, 88 + SCREENY, 270, 346);
}

void DialogBox_Map::OnEnable(int cType, int sV1, int sV2, char* pString)
{
	Info().sV1 = sV1;
	Info().sV2 = sV2;
	Info().sSizeX = 290;
	Info().sSizeY = 290;
}

void DialogBox_Map::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;
	const bool dialogTrans = ConfigManager::Get().IsDialogTransparencyEnabled();
	uint32_t dwTime = m_pGame->m_dwCurTime;
	double dV1, dV2, dV3;
	int tX, tY, szX, szY, dX, dY;

	szX = 0;
	szY = 0;

	switch (Info().sV1) {
	case 1:
		switch (Info().sV2) {
		case 0: // aresden
			if (dialogTrans)
				m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS1]->PutTransSprite2(sX, sY, 0, dwTime);
			else m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS1]->PutSpriteFast(sX, sY, 0, dwTime);
			dX = 19;
			dY = 20;
			szX = 260;
			szY = 260;
			break;

		case 1: // elvine
			if (dialogTrans)
				m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS1]->PutTransSprite2(sX, sY, 1, dwTime);
			else m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS1]->PutSpriteFast(sX, sY, 1, dwTime);
			dX = 20;
			dY = 18;
			szX = 260;
			szY = 260;
			break;

		case 2: // middleland
			if (dialogTrans)
				m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS2]->PutTransSprite2(sX, sY, 0, dwTime);
			else m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS2]->PutSpriteFast(sX, sY, 0, dwTime);
			dX = 11;
			dY = 31;
			szX = 280;
			szY = 253;
			break;

		case 3: // default
			if (dialogTrans)
				m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS2]->PutTransSprite2(sX, sY, 1, dwTime);
			else m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS2]->PutSpriteFast(sX, sY, 1, dwTime);
			dX = 52;
			dY = 42;
			szX = 200;
			szY = 200;
			break;

		case 4: // aresden dungeon
			if (dialogTrans)
				m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS3]->PutTransSprite2(sX, sY, 0, dwTime);
			else m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS3]->PutSpriteFast(sX, sY, 0, dwTime);
			dX = 40;
			dY = 40;
			szX = 220;
			szY = 220;
			break;

		case 5: // elvine dungeon
			if (dialogTrans)
				m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS3]->PutTransSprite2(sX, sY, 1, dwTime);
			else m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS3]->PutSpriteFast(sX, sY, 1, dwTime);
			dX = 40;
			dY = 40;
			szX = 220;
			szY = 220;
			break;

		case 6: // aresden
			if (dialogTrans)
				m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS4]->PutTransSprite2(sX, sY, 0, dwTime);
			else m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS4]->PutSpriteFast(sX, sY, 0, dwTime);
			dX = 40;
			dY = 40;
			szX = 220;
			szY = 220;
			break;

		case 7: // elvine
			if (dialogTrans)
				m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS4]->PutTransSprite2(sX, sY, 1, dwTime);
			else m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS4]->PutSpriteFast(sX, sY, 1, dwTime);
			dX = 40;
			dY = 40;
			szX = 220;
			szY = 220;
			break;

		case 8: // aresden
			if (dialogTrans)
				m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS5]->PutTransSprite2(sX, sY, 0, dwTime);
			else m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS5]->PutSpriteFast(sX, sY, 0, dwTime);
			dX = 40;
			dY = 32;
			szX = 220;
			szY = 220;
			break;

		case 9: // elvine
			if (dialogTrans)
				m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS5]->PutTransSprite2(sX, sY, 1, dwTime);
			else m_pGame->m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS5]->PutSpriteFast(sX, sY, 1, dwTime);
			dX = 40;
			dY = 38;
			szX = 220;
			szY = 220;
			break;
		}

		dV1 = (double)m_pGame->m_pMapData->m_sMapSizeX;
		dV2 = (double)m_pGame->m_sPlayerX;
		dV3 = (dV2 * (double)szX) / dV1;
		tX = (int)dV3 + dX;

		dV1 = (double)m_pGame->m_pMapData->m_sMapSizeY;
		if (dV1 == 752) dV1 = 680;
		dV2 = (double)m_pGame->m_sPlayerY;
		dV3 = (dV2 * (double)szY) / dV1;
		tY = (int)dV3 + dY;

		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, sX + tX, sY + tY, 43);
		wsprintf(m_pGame->G_cTxt, "%d,%d", m_pGame->m_sPlayerX, m_pGame->m_sPlayerY);
		m_pGame->PutString_SprFont3(sX + 10 + tX - 5, sY + 10 + tY - 6, m_pGame->G_cTxt, m_pGame->m_wR[13] * 4, m_pGame->m_wG[13] * 4, m_pGame->m_wB[13] * 4, false, 2);
		break;
	}
}

bool DialogBox_Map::OnClick(short msX, short msY)
{
	// Map dialog has no click handling - it just displays
	return false;
}
