// Effect_Add.cpp: AddEffect implementation
//
//////////////////////////////////////////////////////////////////////

#include "EffectManager.h"
#include "Game.h"
#include "Sprite.h"
#include "Effect.h"
#include "GlobalDef.h"
#include "Misc.h"
#include "ConfigManager.h"

extern int _iAttackerHeight[];

void EffectManager::AddEffectImpl(short sType, int sX, int sY, int dX, int dY, char cStartFrame, int iV1)
{
	int i;
	short sAbsX, sAbsY, sDist;
	long lPan;
	int  iV2 = 0;
	if (ConfigManager::Get().GetDetailLevel() == 0) // Detail Level Low
	{
		switch (sType) {
		case 8:
		case 9:
		case 11:
		case 12:
		case 14:
		case 15:
			return;
		}
	}
	if (m_pGame->m_bIsProgramActive == false) return;
	int x = LOGICAL_WIDTH / 2;
	int y = LOGICAL_HEIGHT / 2;
	int fixx = VIEW_CENTER_TILE_X;
	int fixy = VIEW_CENTER_TILE_Y;
	sAbsX = abs(((m_pGame->m_sViewPointX / 32) + fixx) - dX);
	sAbsY = abs(((m_pGame->m_sViewPointY / 32) + fixy) - dY);
	if (sAbsX > sAbsY) sDist = sAbsX; else sDist = sAbsY;
	short fixdist = sDist;
	int fixpan = LOGICAL_WIDTH;

	for (i = 0; i < DEF_MAXEFFECTS; i++)
		if (m_pEffectList[i] == 0)
		{
			m_pEffectList[i] = new class CEffect;
			m_pEffectList[i]->m_sType = sType;
			m_pEffectList[i]->m_sX = sX;
			m_pEffectList[i]->m_sY = sY;
			m_pEffectList[i]->m_dX = dX;
			m_pEffectList[i]->m_dY = dY;
			m_pEffectList[i]->m_iV1 = iV1;
			m_pEffectList[i]->m_cFrame = cStartFrame;
			m_pEffectList[i]->m_dwTime = m_pGame->m_dwCurTime;

			switch (sType) {
			case 1: // coup normal
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - _iAttackerHeight[iV1];
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 2;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			case 2:	// Fl�che qui vole
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - _iAttackerHeight[iV1];
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 10;
				m_pEffectList[i]->m_cDir = CMisc::cCalcDirection(sX, sY, dX, dY);
				m_pGame->PlaySound('C', 4, sDist);
				break;

			case 4: // Gold
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32;
				m_pEffectList[i]->m_cMaxFrame = 12;
				m_pEffectList[i]->m_dwFrameTime = 100;
				sAbsX = abs(((m_pGame->m_sViewPointX / 32) + fixx) - sX);
				sAbsY = abs(((m_pGame->m_sViewPointY / 32) + fixy) - sY);
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 12, sDist, lPan);
				break;

			case 5: // FireBall Fire Explosion
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 11;
				m_pEffectList[i]->m_dwFrameTime = 10;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 4, sDist, lPan);
				m_pGame->SetCameraShakingEffect(sDist);
				break;

			case 6:	 // Energy Bolt
			case 10: // Lightning Arrow
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 14;
				m_pEffectList[i]->m_dwFrameTime = 10;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 2, sDist, lPan);
				m_pGame->SetCameraShakingEffect(sDist);
				break;

			case 7: // Magic Missile Explosion
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 5;
				m_pEffectList[i]->m_dwFrameTime = 50;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 3, sDist, lPan);
				break;

			case 8: // Burst
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 4;
				m_pEffectList[i]->m_dwFrameTime = 30;
				break;

			case 9: // Burst
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_rX = 6 - (rand() % 12);
				m_pEffectList[i]->m_rY = -8 - (rand() % 6);
				m_pEffectList[i]->m_cMaxFrame = 14;
				m_pEffectList[i]->m_dwFrameTime = 30;
				break;

			case 11:
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_rX = 6 - (rand() % 12);
				if (iV2 == 0)
					m_pEffectList[i]->m_rY = -2 - (rand() % 4);
				else m_pEffectList[i]->m_rY = -2 - (rand() % 10);
				m_pEffectList[i]->m_cMaxFrame = 8;
				m_pEffectList[i]->m_dwFrameTime = 30;
				break;

			case 12: // Burst
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_rX = 8 - (rand() % 16);
				m_pEffectList[i]->m_rY = 4 - (rand() % 12);
				m_pEffectList[i]->m_cMaxFrame = 10;
				m_pEffectList[i]->m_dwFrameTime = 30;
				break;

			case 13: // Bulles druncncity
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 18;
				m_pEffectList[i]->m_dwFrameTime = 20;
				break;

			case 14: // Traces de pas ou Tremor (pas en low detail)
				m_pEffectList[i]->m_mX = sX;
			if (m_pEffectList[i]->m_iV1 > 0) // Case if hit by an arrow
			{
				m_pEffectList[i]->m_mY = sY - (_iAttackerHeight[m_pEffectList[i]->m_iV1] / 4 + rand() % (_iAttackerHeight[m_pEffectList[i]->m_iV1] / 2));
				m_pEffectList[i]->m_mX = sX + (rand() % 5) - 2;
			}
			else m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 4;
				m_pEffectList[i]->m_dwFrameTime = 100;
				m_pEffectList[i]->m_iV1 = iV1;
				break;

			case 15: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 16;
				m_pEffectList[i]->m_dwFrameTime = 80;
				break;

			case 16: //
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 40;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				break;

			case 17:
				m_pEffectList[i]->m_mX = sX + (rand() % 20) - 40;
				m_pEffectList[i]->m_mY = sY + (rand() % 20) - 40;
				m_pEffectList[i]->m_rX = 8 - (rand() % 16);
				m_pEffectList[i]->m_rY = 4 - (rand() % 12);
				m_pEffectList[i]->m_mX3 = sX;
				m_pEffectList[i]->m_mY3 = sY;
				m_pEffectList[i]->m_iV1 = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				break;

			case 18:
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 10;
				m_pEffectList[i]->m_dwFrameTime = 50;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				m_pGame->SetCameraShakingEffect(sDist);
				break;

			case 20:
			case 21:
			case 22:
			case 23:
			case 24:
			case 25:
			case 26:
			case 27: // Critical strike with a weapon
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 40;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 10;
				m_pEffectList[i]->m_cDir = CMisc::cCalcDirection(sX, sY, dX, dY);
				break;

			case 30: // Mass-Fire-Strike (called 1 time)
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 9;
				m_pEffectList[i]->m_dwFrameTime = 40;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 4, sDist, lPan);
				m_pGame->SetCameraShakingEffect(sDist * 2);
				break;

			case 31: // Mass-Fire-Strike (called 3 times)
			case 252: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 8;
				m_pEffectList[i]->m_dwFrameTime = 40;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 4, sDist, lPan);
				m_pGame->SetCameraShakingEffect(sDist);
				break;

			case 32: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 4;
				m_pEffectList[i]->m_dwFrameTime = 100;
				break;

			case 33: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 16;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			case 34: //
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 40;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				m_pGame->SetCameraShakingEffect(sDist);
				break;

			case 35: // Snoopy: rajout (pour Mass Magic-Missile)
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 18;
				m_pEffectList[i]->m_dwFrameTime = 40;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 4, sDist, lPan);
				m_pGame->SetCameraShakingEffect(sDist * 2);
				break;

			case 36: // Snoopy: Rajout (pour Mass Magic-Missile)
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 15;
				m_pEffectList[i]->m_dwFrameTime = 40;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 4, sDist, lPan);
				m_pGame->SetCameraShakingEffect(sDist);
				break;

			case 40: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 15;
				m_pEffectList[i]->m_dwFrameTime = 30;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = ((sX - m_pGame->m_sViewPointX) - x) * 30;
				m_pGame->PlaySound('E', 45, sDist, lPan);
				break;

			case 41: // Large Type 1, 2, 3, 4
			case 42:
			case 43:
			case 44:
			case 45: // Small Type 1, 2
			case 46:
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY - 220;
				m_pEffectList[i]->m_cMaxFrame = 14;
				m_pEffectList[i]->m_dwFrameTime = 20;
				m_pEffectList[i]->m_iV1 = 20;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = ((sX - m_pGame->m_sViewPointX) - x) * 30;
				m_pGame->PlaySound('E', 46, sDist, lPan);
				break;

			case 47: // Blizzard
			case 48: // Blizzard
			case 49: // Blizzard
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY - 220;
				m_pEffectList[i]->m_cMaxFrame = 12;
				m_pEffectList[i]->m_dwFrameTime = 20;
				m_pEffectList[i]->m_iV1 = 20;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = ((sX - m_pGame->m_sViewPointX) - x) * 30;
				m_pGame->PlaySound('E', 46, sDist, lPan);
				break;

			case 50: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 12;
				m_pEffectList[i]->m_dwFrameTime = 50;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = ((sX - m_pGame->m_sViewPointX) - x) * 30;
				if ((rand() % 4) == 1) m_pGame->SetCameraShakingEffect(sDist);
				m_pGame->PlaySound('E', 47, sDist, lPan);
				break;

			case 51:
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 9; //15;
				m_pEffectList[i]->m_dwFrameTime = 80;
				break;

			case 52: // Protect ring
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 15;
				m_pEffectList[i]->m_dwFrameTime = 80;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = ((sX - m_pGame->m_sViewPointX) - x) * 30;
				m_pGame->PlaySound('E', 5, sDist, lPan);
				break;

			case 53: // Hold twist
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 15;
				m_pEffectList[i]->m_dwFrameTime = 80;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = ((sX - m_pGame->m_sViewPointX) - x) * 30;
				m_pGame->PlaySound('E', 5, sDist, lPan);
				break;

			case 54: // star twingkling (effect armes brillantes)
			case 55: // Unused
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 10;
				m_pEffectList[i]->m_dwFrameTime = 15;
				break;

			case 56: //  Mass-Chill-Wind
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 14;
				m_pEffectList[i]->m_dwFrameTime = 30;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = ((sX - m_pGame->m_sViewPointX) - x) * 30;
				m_pGame->PlaySound('E', 45, sDist, lPan);
				break;

			case 57: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 16;
				m_pEffectList[i]->m_dwFrameTime = 80;
				break;

			case 60: //
				m_pEffectList[i]->m_mX = sX + 300;
				m_pEffectList[i]->m_mY = sY - 460;
				m_pEffectList[i]->m_cMaxFrame = 10;
				m_pEffectList[i]->m_dwFrameTime = 50;
				break;

			case 61: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 16;
				m_pEffectList[i]->m_dwFrameTime = 10;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 4, sDist, lPan);
				m_pGame->SetCameraShakingEffect(sDist, 2);
				break;

			case 62: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 6;
				m_pEffectList[i]->m_dwFrameTime = 100;
				break;

			case 63: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 16;
				m_pEffectList[i]->m_dwFrameTime = 20;
				break;

			case 64: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 15;
				m_pEffectList[i]->m_dwFrameTime = 20;
				break;

			case 65: // Crusade's MS
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 30;
				m_pEffectList[i]->m_dwFrameTime = 80;
				break;

			case 66: // Crusade MS explosion
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 14;
				m_pEffectList[i]->m_dwFrameTime = 30;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 4, sDist, lPan);
				m_pGame->SetCameraShakingEffect(sDist, 2);
				break;

			case 67: // Crusade's MS fire + smoke ?
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 27;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			case 68: // worm-bite
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 17;
				m_pEffectList[i]->m_dwFrameTime = 30;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 4, sDist, lPan);
				m_pEffectList[i]->m_iV1 = sDist;
				//game->SetCameraShakingEffect(sDist, 2);
				break;

			case 69: // identique au cas 70
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 11;
				m_pEffectList[i]->m_dwFrameTime = 30;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 42, sDist, lPan);
				break;

			case 70: // identtique au cas 69
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 11;
				m_pEffectList[i]->m_dwFrameTime = 30;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 42, sDist, lPan);
				break;

			case 71: //
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				m_pGame->SetCameraShakingEffect(sDist);
				break;

			case 72: // Blizzard
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 15;
				m_pEffectList[i]->m_dwFrameTime = 20;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				lPan = ((sX - m_pGame->m_sViewPointX) - x) * 30;
				if ((rand() % 4) == 1) m_pGame->SetCameraShakingEffect(sDist);
				m_pGame->PlaySound('E', 47, sDist, lPan);
				break;

			case 73:
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 15;
				m_pEffectList[i]->m_dwFrameTime = 60;
				break;

			case 74:
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 19;
				m_pEffectList[i]->m_dwFrameTime = 40;
				break;

			case 75: //ice golem
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_dX = dX;
				m_pEffectList[i]->m_dY = dY;
				m_pEffectList[i]->m_cMaxFrame = 16;
				m_pEffectList[i]->m_dwFrameTime = 40;
				break;

			case 76: //ice golem
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_dX = dX;
				m_pEffectList[i]->m_dY = dY;
				m_pEffectList[i]->m_cMaxFrame = 16;
				m_pEffectList[i]->m_dwFrameTime = 40;
				break;

			case 77: //ice golem
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_dX = dX;
				m_pEffectList[i]->m_dY = dY;
				m_pEffectList[i]->m_cMaxFrame = 16;
				m_pEffectList[i]->m_dwFrameTime = 40;
				break;

			case 80: // Snoopy: rajou�, impl�ment� en dernier ds la v351
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_iV1 = 20;
				m_pEffectList[i]->m_cMaxFrame = 30;
				m_pEffectList[i]->m_dwFrameTime = 25;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				m_pGame->SetCameraShakingEffect(sDist);
				break;

			case 81: //  Snoopy: Rajout (StormBlade)
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 27;
				m_pEffectList[i]->m_dwFrameTime = 40;
				break;

			case 82: //  Snoopy: Rajout (Gate Apocalypse)
				m_pEffectList[i]->m_cMaxFrame = 30;
				m_pEffectList[i]->m_dwFrameTime = 40;
				break;

			case 100: // MagicMissile is Flying
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 40;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 1, sDist, lPan);
				break;

			case 101: // Heal
			case 111: // Staminar-Drain
			case 121: // Great Heal
			case 123: // Staminar-Recovery
			case 128: // Great-Staminar-Recovery
				m_pEffectList[i]->m_cMaxFrame = 14;
				m_pEffectList[i]->m_dwFrameTime = 80;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 5, sDist, lPan);
				break;

			case 102: // CreateFood
			case 122: // Recall
			case 126: // Possession
			case 127: // Poison
			case 134: // DetectInvi
			case 136: // Cure
			case 142: // Confuse language
			case 152: // Polymorph
			case 153: // Mass-Poison
			case 162: // Confusion
			case 171: // Mass-Confusion
				m_pEffectList[i]->m_cMaxFrame = 13;
				m_pEffectList[i]->m_dwFrameTime = 120;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 5, sDist, lPan);
				break;

			case 110: // Energy-Bolt
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 40;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 1, sDist, lPan);
				break;

			case 112: // Recall
			case 131: // Summon
			case 132: // Invi
			case 178: // Haste
				m_pEffectList[i]->m_cMaxFrame = 12;
				m_pEffectList[i]->m_dwFrameTime = 80;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 5, sDist, lPan);
				break;

			case 113: // Defense-Shield
			case 144: // Great-Defense-Shield
				m_pEffectList[i]->m_cMaxFrame = 12;
				m_pEffectList[i]->m_dwFrameTime = 120;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 5, sDist, lPan);
				break;

			case 114: // Celebrating Light
				AddEffectImpl( 69 + (rand() % 2), dX * 32 + 20 - (rand() % 40), dY * 32 + 20 - (rand() % 40), 0, 0, -12, 0);
				AddEffectImpl( 69 + (rand() % 2), dX * 32 + 20 - (rand() % 40), dY * 32 + 20 - (rand() % 40), 0, 0, -9, 0);
				AddEffectImpl( 69 + (rand() % 2), dX * 32 + 20 - (rand() % 40), dY * 32 + 20 - (rand() % 40), 0, 0, -6, 0);
				AddEffectImpl( 69 + (rand() % 2), dX * 32 + 20 - (rand() % 40), dY * 32 + 20 - (rand() % 40), 0, 0, -3, 0);
				AddEffectImpl( 69 + (rand() % 2), dX * 32 + 20 - (rand() % 40), dY * 32 + 20 - (rand() % 40), 0, 0, 0, 0);
				delete m_pEffectSpr[i];
				m_pEffectSpr[i] = 0;
				break;

			case 120: // Fire Ball
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 40;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				m_pEffectList[i]->m_cDir = CMisc::cCalcDirection(sX, sY, dX, dY);
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 1, sDist, lPan);
				break;

			case 124: // Protect form N.M
			case 133: // Protection from Magic
				AddEffectImpl( 52, dX * 32, dY * 32, 0, 0, 0, 0);
				delete m_pEffectSpr[i];
				m_pEffectSpr[i] = 0;
				break;

			case 125: // Hold Person
			case 135: // Paralyze
				AddEffectImpl( 53, dX * 32, dY * 32, 0, 0, 0, 0);
				delete m_pEffectSpr[i];
				m_pEffectSpr[i] = 0;
				break;

			case 130: // Fire Strike
			case 137: // Lightning Arrow
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 40;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				m_pEffectList[i]->m_cDir = CMisc::cCalcDirection(sX, sY, dX, dY);
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 1, sDist, lPan);
				break;

			case 138: // Tremor.
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 4, sDist, lPan);
				m_pGame->SetCameraShakingEffect(sDist, 2);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);

				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				m_pEffectList[i]->m_cMaxFrame = 2;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			case 143: // Lightning
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 50;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_rX = 5 - (rand() % 10);
				m_pEffectList[i]->m_rY = 5 - (rand() % 10);
				m_pEffectList[i]->m_cMaxFrame = 7;
				m_pEffectList[i]->m_dwFrameTime = 10;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 40, sDist, lPan);
				break;

			case 145: // ChillWind
				m_pEffectList[i]->m_cMaxFrame = 2;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			case 147: // Triple-Energy-Bolt
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				break;

			case 150: // Berserk : Cirlcle 6 magic
			case 177: // Illusion-Movement
			case 180: // Illusion
			case 183: // Inhibition-Casting
			case 190: // Mass-Illusion
			case 195: // Mass-Illusion-Movement
				m_pEffectList[i]->m_cMaxFrame = 11;
				m_pEffectList[i]->m_dwFrameTime = 100;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 5, sDist, lPan);
				break;

			case 151: // LightningBolt
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 50;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_rX = 5 - (rand() % 10);
				m_pEffectList[i]->m_rY = 5 - (rand() % 10);
				m_pEffectList[i]->m_cMaxFrame = 10;
				m_pEffectList[i]->m_dwFrameTime = 10;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 40, sDist, lPan);
				break;

			case 156: // Mass-Ligtning-Arrow
				m_pEffectList[i]->m_cMaxFrame = 3;
				m_pEffectList[i]->m_dwFrameTime = 130;
				break;

			case 157: // Ice-Strike
				m_pEffectList[i]->m_cMaxFrame = 2;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			case 160: // Energy-Strike
				m_pEffectList[i]->m_cMaxFrame = 7;
				m_pEffectList[i]->m_dwFrameTime = 80;
				break;

			case 161: // Mass-Fire-Strike
			case 251: //
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 40;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				m_pEffectList[i]->m_cDir = CMisc::cCalcDirection(sX, sY, dX, dY);
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 1, sDist, lPan);
				break;

			case 163: // Mass-Chill-Wind
				m_pEffectList[i]->m_cMaxFrame = 2;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			case 164: // worm-bite
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 4, sDist, lPan);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);

				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( 14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				m_pEffectList[i]->m_cMaxFrame = 1;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			case 165: // Absolute-Magic-Protection
				m_pEffectList[i]->m_cMaxFrame = 21;
				m_pEffectList[i]->m_dwFrameTime = 70;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 5, sDist, lPan);
				break;

			case 166: // Armor Break
				m_pEffectList[i]->m_cMaxFrame = 13;
				m_pEffectList[i]->m_dwFrameTime = 80;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 5, sDist, lPan);
				break;

			case 170: // Bloody-Shock-Wave
				m_pEffectList[i]->m_cMaxFrame = 7;
				m_pEffectList[i]->m_dwFrameTime = 80;
				break;

			case 172: // Mass-Ice-Strike
				m_pEffectList[i]->m_cMaxFrame = 2;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			case 174: // Lightning-Strike
				m_pEffectList[i]->m_cMaxFrame = 5;
				m_pEffectList[i]->m_dwFrameTime = 120;
				break;

			case 176: // Snoopy: Ajout Cancellation
				m_pEffectList[i]->m_cMaxFrame = 23;
				m_pEffectList[i]->m_dwFrameTime = 60;
				sDist = sDist / 32;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 5, sDist, lPan);
				break;

			case 181: // MS
				m_pEffectList[i]->m_mX = dX * 32 + 300;
				m_pEffectList[i]->m_mY = dY * 32 - 460;
				m_pEffectList[i]->m_cMaxFrame = 10;
				m_pEffectList[i]->m_dwFrameTime = 25;
				break;

			case 182: // Snoopy: Ajout Mass-Magic-Missile
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 40;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 1, sDist, lPan);
				break;

			case 244: // Snoopy: d�plac� pour nvx sorts: Aura du casteur de Mass MagicMissile
				//case 184: // effet sur le caster pour MassMM
				m_pEffectList[i]->m_cMaxFrame = 29;
				m_pEffectList[i]->m_dwFrameTime = 80;
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				break;

			case 191: // Blizzard
				m_pEffectList[i]->m_cMaxFrame = 7;
				m_pEffectList[i]->m_dwFrameTime = 80;
				break;

				//case 192: // Hero set Effect
			case 242: // Hero set Effect
				m_pEffectList[i]->m_cMaxFrame = 30;
				m_pEffectList[i]->m_dwFrameTime = 40;
				break;

				//case 193: // Hero set Effect
			case 243: // Hero set Effect
				m_pEffectList[i]->m_cMaxFrame = 19;
				m_pEffectList[i]->m_dwFrameTime = 18;
				break;

			case 194: // Resurrection
				m_pEffectList[i]->m_cMaxFrame = 30;
				m_pEffectList[i]->m_dwFrameTime = 40;
				break;

			case 196: // Snoopy: Ajout de Earth-Shock-Wave
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 30;
				m_pEffectList[i]->m_dwFrameTime = 25;
				sAbsX = abs(x - (sX - m_pGame->m_sViewPointX));
				sAbsY = abs(y - (sY - m_pGame->m_sViewPointY));
				if (sAbsX > sAbsY) sDist = sAbsX;
				else sDist = sAbsY;
				sDist = sDist / 32;
				m_pGame->SetCameraShakingEffect(sDist);
				break;
			case 200: //
			case 201: //
			case 202: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 15;
				m_pEffectList[i]->m_dwFrameTime = 25;
				break;

			case 203: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 18;
				m_pEffectList[i]->m_dwFrameTime = 70;
				break;

			case 204: //
			case 205: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 12;
				m_pEffectList[i]->m_dwFrameTime = 70;
				break;

			case 206: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 3;
				m_pEffectList[i]->m_dwFrameTime = 70;
				break;

			case 250: //
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 40;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			default:
				delete m_pEffectSpr[i];
				m_pEffectSpr[i] = 0;
				break;
			}
			if (m_pEffectSpr[i] != 0)
			{
				m_pEffectList[i]->m_mX2 = m_pEffectList[i]->m_mX;
				m_pEffectList[i]->m_mY2 = m_pEffectList[i]->m_mY;
			}
			return;
		}
}
