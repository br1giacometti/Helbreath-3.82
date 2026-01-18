#include "DialogBox_GuideMap.h"
#include "ConfigManager.h"
#include "Game.h"
#include "GlobalDef.h"
#include "lan_eng.h"

DialogBox_GuideMap::DialogBox_GuideMap(CGame* pGame)
	: IDialogBox(DialogBoxId::GuideMap, pGame)
{
	SetDefaultRect(LOGICAL_MAX_X - 128, 0, 128, 128);
}

void DialogBox_GuideMap::OnUpdate()
{
	// Clear expired monster event
	if (m_pGame->m_dwMonsterEventTime != 0 &&
		(m_pGame->m_dwCurTime - m_pGame->m_dwMonsterEventTime) >= 30000)
	{
		m_pGame->m_dwMonsterEventTime = 0;
		m_pGame->m_sMonsterID = 0;
	}
}

void DialogBox_GuideMap::DrawBorder(short sX, short sY)
{
	for (short shX = -2; shX < 130; shX++)
	{
		m_pGame->m_DDraw.PutPixel(sX + shX, sY - 2, 50, 50, 50);
		m_pGame->m_DDraw.PutPixel(sX + shX, sY - 1, 50, 50, 50);
		m_pGame->m_DDraw.PutPixel(sX + shX, sY + 128, 50, 50, 50);
		m_pGame->m_DDraw.PutPixel(sX + shX, sY + 129, 50, 50, 50);
	}
	for (short shY = -2; shY < 130; shY++)
	{
		m_pGame->m_DDraw.PutPixel(sX - 2, sY + shY, 50, 50, 50);
		m_pGame->m_DDraw.PutPixel(sX - 1, sY + shY, 50, 50, 50);
		m_pGame->m_DDraw.PutPixel(sX + 128, sY + shY, 50, 50, 50);
		m_pGame->m_DDraw.PutPixel(sX + 129, sY + shY, 50, 50, 50);
	}
}

void DialogBox_GuideMap::DrawZoomedMap(short sX, short sY)
{
	int m_iMaxMapIndex = DEF_SPRID_INTERFACE_GUIDEMAP + m_pGame->m_cMapIndex + 1;
	uint32_t dwTime = m_pGame->m_dwCurTime;

	if (m_pGame->m_cMapIndex >= 35)
		m_iMaxMapIndex = DEF_SPRID_INTERFACE_GUIDEMAP + m_pGame->m_cMapIndex + 1;

	short shX = m_pGame->m_sPlayerX - 64;
	short shY = m_pGame->m_sPlayerY - 64;
	if (shX < 0) shX = 0;
	if (shY < 0) shY = 0;
	if (shX > m_pGame->m_pMapData->m_sMapSizeX - 128) shX = m_pGame->m_pMapData->m_sMapSizeX - 128;
	if (shY > m_pGame->m_pMapData->m_sMapSizeY - 128) shY = m_pGame->m_pMapData->m_sMapSizeY - 128;

	if (ConfigManager::Get().IsDialogTransparencyEnabled())
		m_pGame->m_pSprite[m_iMaxMapIndex]->PutShiftTransSprite2(sX, sY, shX, shY, 0, dwTime);
	else
		m_pGame->m_pSprite[m_iMaxMapIndex]->PutShiftSpriteFast(sX, sY, shX, shY, 0, dwTime);

	m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX - shX + m_pGame->m_sPlayerX, sY - shY + m_pGame->m_sPlayerY, 37, dwTime);

	if ((m_pGame->m_dwCurTime - m_pGame->m_dwMonsterEventTime) < 30000)
	{
		if ((m_pGame->m_dwCurTime % 500) < 370)
		{
			if (m_pGame->m_sEventX >= shX && m_pGame->m_sEventX <= shX + 128 &&
				m_pGame->m_sEventY >= shY && m_pGame->m_sEventY <= shY + 128)
			{
				m_pGame->m_pSprite[DEF_SPRID_INTERFACE_MONSTER]->PutSpriteFast(
					sX + m_pGame->m_sEventX - shX, sY + m_pGame->m_sEventY - shY,
					m_pGame->m_sMonsterID, dwTime);
			}
		}
	}
}

void DialogBox_GuideMap::DrawFullMap(short sX, short sY)
{
	int m_iMinMapIndex = DEF_SPRID_INTERFACE_GUIDEMAP;
	int m_iMinMapSquare = m_pGame->m_cMapIndex;
	uint32_t dwTime = m_pGame->m_dwCurTime;

	if (m_pGame->m_cMapIndex >= 35)
	{
		m_iMinMapIndex = DEF_SPRID_INTERFACE_GUIDEMAP + 35;
		m_iMinMapSquare = m_pGame->m_cMapIndex - 35;
	}

	if (ConfigManager::Get().IsDialogTransparencyEnabled())
		m_pGame->m_pSprite[m_iMinMapIndex]->PutTransSprite2(sX, sY, m_iMinMapSquare, dwTime);
	else
		m_pGame->m_pSprite[m_iMinMapIndex]->PutSpriteFastNoColorKey(sX, sY, m_iMinMapSquare, dwTime);

	short shX = (m_pGame->m_sPlayerX * 128) / (m_pGame->m_pMapData->m_sMapSizeX);
	short shY = (m_pGame->m_sPlayerY * 128) / (m_pGame->m_pMapData->m_sMapSizeX);
	m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + shX, sY + shY, 37, dwTime);

	if ((m_pGame->m_dwCurTime - m_pGame->m_dwMonsterEventTime) < 30000)
	{
		if ((m_pGame->m_dwCurTime % 500) < 370)
		{
			shX = (m_pGame->m_sEventX * 128) / (m_pGame->m_pMapData->m_sMapSizeX);
			shY = (m_pGame->m_sEventY * 128) / (m_pGame->m_pMapData->m_sMapSizeX);
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_MONSTER]->PutSpriteFast(sX + shX, sY + shY, m_pGame->m_sMonsterID, dwTime);
		}
	}
}

void DialogBox_GuideMap::DrawLocationTooltip(short msX, short msY, short sX, short sY)
{
	short shX, shY;
	short szY = Info().sSizeY;

	if (ConfigManager::Get().IsZoomMapEnabled())
	{
		shX = m_pGame->m_sPlayerX - 64;
		shY = m_pGame->m_sPlayerY - 64;
		if (shX < 0) shX = 0;
		if (shY < 0) shY = 0;
		if (shX > m_pGame->m_pMapData->m_sMapSizeX - 128) shX = m_pGame->m_pMapData->m_sMapSizeX - 128;
		if (shY > m_pGame->m_pMapData->m_sMapSizeY - 128) shY = m_pGame->m_pMapData->m_sMapSizeY - 128;
		shX += msX - sX;
		shY += msY - sY;
	}
	else
	{
		shX = (msX - sX) * m_pGame->m_pMapData->m_sMapSizeX / 128;
		shY = (msY - sY) * m_pGame->m_pMapData->m_sMapSizeX / 128;
	}

	wsprintf(m_pGame->G_cTxt, "%d, %d", shX, shY);

	// Aresden map locations
	if (m_pGame->m_cMapIndex == 11)
	{
		if (shX > 46 && shX < 66 && shY > 107 && shY < 127) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_MAGICTOWER);
		else if (shX > 103 && shX < 123 && shY > 86 && shY < 116) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_GUILDHALL);
		else if (shX > 176 && shX < 196 && shY > 62 && shY < 82) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_CATH);
		else if (shX > 135 && shX < 155 && shY > 113 && shY < 133) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_CITYHALL);
		else if (shX > 97 && shX < 117 && shY > 175 && shY < 195) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE);
		else if (shX > 223 && shX < 243 && shY > 124 && shY < 144) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE);
		else if (shX > 118 && shX < 138 && shY > 157 && shY < 177) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_SHOP);
		else if (shX > 148 && shX < 178 && shY > 188 && shY < 208) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_BLACKSMITH);
		else if (shX > 69 && shX < 89 && shY > 199 && shY < 219) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_DUNGEON);
		else if (shX > 21 && shX < 41 && shY > 266 && shY < 286) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_HUNT);
		else if (shX > 20 && shX < 40 && shY > 13 && shY < 33) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_ML);
		else if (shX > 246 && shX < 266 && shY > 16 && shY < 36) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_ML);
		else if (shX > 265 && shX < 285 && shY > 195 && shY < 215) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_FARM);
		else if (shX > 88 && shX < 108 && shY > 150 && shY < 170) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_CMDHALL);
	}
	// Elvine map locations
	else if (m_pGame->m_cMapIndex == 3)
	{
		if (shX > 170 && shX < 190 && shY > 65 && shY < 85) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_MAGICTOWER);
		else if (shX > 67 && shX < 87 && shY > 130 && shY < 150) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_GUILDHALL);
		else if (shX > 121 && shX < 141 && shY > 66 && shY < 86) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_CATH);
		else if (shX > 135 && shX < 155 && shY > 117 && shY < 137) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_CITYHALL);
		else if (shX > 190 && shX < 213 && shY > 118 && shY < 138) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE);
		else if (shX > 73 && shX < 103 && shY > 165 && shY < 185) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE);
		else if (shX > 217 && shX < 237 && shY > 142 && shY < 162) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_SHOP);
		else if (shX > 216 && shX < 256 && shY > 99 && shY < 119) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_BLACKSMITH);
		else if (shX > 251 && shX < 271 && shY > 73 && shY < 93) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_DUNGEON);
		else if (shX > 212 && shX < 232 && shY > 13 && shY < 33) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_HUNT);
		else if (shX > 16 && shX < 36 && shY > 262 && shY < 282) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_ML);
		else if (shX > 244 && shX < 264 && shY > 248 && shY < 268) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_ML);
		else if (shX > 264 && shX < 284 && shY > 177 && shY < 207) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_FARM);
		else if (shX > 207 && shX < 227 && shY > 79 && shY < 99) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_CMDHALL);
	}
	// Elvine Farm
	else if (m_pGame->m_cMapIndex == 5)
	{
		if (shX > 62 && shX < 82 && shY > 187 && shY < 207) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE);
		else if (shX > 81 && shX < 101 && shY > 169 && shY < 189) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_SHOP);
		else if (shX > 101 && shX < 131 && shY > 180 && shY < 200) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_BLACKSMITH);
		else if (shX > 130 && shX < 150 && shY > 195 && shY < 215) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_DUNGEON);
		else if (shX > 86 && shX < 106 && shY > 139 && shY < 159) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_BARRACK);
	}
	// Aresden Farm
	else if (m_pGame->m_cMapIndex == 6)
	{
		if (shX > 30 && shX < 50 && shY > 80 && shY < 100) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE);
		else if (shX > 55 && shX < 85 && shY > 80 && shY < 100) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_BLACKSMITH);
		else if (shX > 52 && shX < 72 && shY > 80 && shY < 100) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_SHOP);
		else if (shX > 70 && shX < 90 && shY > 60 && shY < 80) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_DUNGEON);
		else if (shX > 45 && shX < 65 && shY > 123 && shY < 143) strcpy(m_pGame->G_cTxt, DEF_MSG_MAPNAME_BARRACK);
	}

	PutString(msX - 10, msY - 13, m_pGame->G_cTxt, RGB(200, 200, 120));
}

void DialogBox_GuideMap::OnDraw(short msX, short msY, short msZ, char cLB)
{
	if (m_pGame->m_cMapIndex < 0) return;

	short sX = Info().sX;
	short sY = Info().sY;
	short szX = Info().sSizeX;
	short szY = Info().sSizeY;

	// Clamp position
	if (sX < 20) sX = 0;
	if (sY < 20) sY = 0;
	if (sX > LOGICAL_WIDTH - 128 - 20) sX = LOGICAL_WIDTH - 128;
	if (sY > 547 - 128 - 20) sY = 547 - 128;

	DrawBorder(sX, sY);

	if (ConfigManager::Get().IsZoomMapEnabled())
		DrawZoomedMap(sX, sY);
	else
		DrawFullMap(sX, sY);

	if (cLB != 0) return;

	// Mouse hover - show zoom toggle hint and location tooltip
	if (msX >= sX && msX < sX + szY && msY >= sY && msY < sY + szY)
	{
		short shY;
		if (sY > 213) shY = sY - 17;
		else shY = sY + szY + 4;

		if (ConfigManager::Get().IsZoomMapEnabled())
			PutString(sX, shY, DEF_MSG_GUIDEMAP_MIN, RGB(200, 200, 120));
		else
			PutString(sX, shY, DEF_MSG_GUIDEMAP_MAX, RGB(200, 200, 120));

		DrawLocationTooltip(msX, msY, sX, sY);
	}
}

bool DialogBox_GuideMap::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;
	short szY = Info().sSizeY;

	// Clamp position (same as draw)
	if (sX < 20) sX = 0;
	if (sY < 20) sY = 0;
	if (sX > LOGICAL_WIDTH - 128 - 20) sX = LOGICAL_WIDTH - 128;
	if (sY > 547 - 128 - 20) sY = 547 - 128;

	if (msX >= sX && msX < sX + szY && msY >= sY && msY < sY + szY)
	{
		// Toggle zoom mode
		bool zoomMap = ConfigManager::Get().IsZoomMapEnabled();
		ConfigManager::Get().SetZoomMapEnabled(!zoomMap);
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	return false;
}
