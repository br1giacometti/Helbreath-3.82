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

void EffectManager::AddEffectImpl(EffectType sType, int sX, int sY, int dX, int dY, char cStartFrame, int iV1)
{
	int i;
	short sAbsX, sAbsY, sDist;
	long lPan;
	int  iV2 = 0;
	if (ConfigManager::Get().GetDetailLevel() == 0) // Detail Level Low
	{
		switch (sType) {
		case EffectType::BURST_SMALL:
		case EffectType::BURST_MEDIUM:
		case EffectType::BURST_SMALL_GRENADE:
		case EffectType::BURST_LARGE:
		case EffectType::FOOTPRINT:
		case EffectType::RED_CLOUD_PARTICLES:
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
			case EffectType::NORMAL_HIT: // coup normal
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - _iAttackerHeight[iV1];
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 2;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			case EffectType::ARROW_FLYING:	// Arrow Flying
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - _iAttackerHeight[iV1];
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 10;
				m_pEffectList[i]->m_cDir = CMisc::cCalcDirection(sX, sY, dX, dY);
				m_pGame->PlaySound('C', 4, sDist);
				break;

			case EffectType::GOLD_DROP: // Gold
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

			case EffectType::FIREBALL_EXPLOSION: // FireBall Fire Explosion
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

			case EffectType::ENERGY_BOLT_EXPLOSION:	 // Energy Bolt
			case EffectType::LIGHTNING_ARROW_EXPLOSION: // Lightning Arrow
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

			case EffectType::MAGIC_MISSILE_EXPLOSION: // Magic Missile Explosion
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

			case EffectType::BURST_SMALL: // Burst
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 4;
				m_pEffectList[i]->m_dwFrameTime = 30;
				break;

			case EffectType::BURST_MEDIUM: // Burst
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_rX = 6 - (rand() % 12);
				m_pEffectList[i]->m_rY = -8 - (rand() % 6);
				m_pEffectList[i]->m_cMaxFrame = 14;
				m_pEffectList[i]->m_dwFrameTime = 30;
				break;

			case EffectType::BURST_SMALL_GRENADE:
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_rX = 6 - (rand() % 12);
				if (iV2 == 0)
					m_pEffectList[i]->m_rY = -2 - (rand() % 4);
				else m_pEffectList[i]->m_rY = -2 - (rand() % 10);
				m_pEffectList[i]->m_cMaxFrame = 8;
				m_pEffectList[i]->m_dwFrameTime = 30;
				break;

			case EffectType::BURST_LARGE: // Burst
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_rX = 8 - (rand() % 16);
				m_pEffectList[i]->m_rY = 4 - (rand() % 12);
				m_pEffectList[i]->m_cMaxFrame = 10;
				m_pEffectList[i]->m_dwFrameTime = 30;
				break;

			case EffectType::BUBBLES_DRUNK: // Bulles druncncity
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 18;
				m_pEffectList[i]->m_dwFrameTime = 20;
				break;

			case EffectType::FOOTPRINT: // Traces of pas ou Tremor (pas en low detail)
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

			case EffectType::RED_CLOUD_PARTICLES: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 16;
				m_pEffectList[i]->m_dwFrameTime = 80;
				break;

			case EffectType::PROJECTILE_GENERIC: //
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 40;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				break;

			case EffectType::ICE_STORM:
				m_pEffectList[i]->m_mX = sX + (rand() % 20) - 40;
				m_pEffectList[i]->m_mY = sY + (rand() % 20) - 40;
				m_pEffectList[i]->m_rX = 8 - (rand() % 16);
				m_pEffectList[i]->m_rY = 4 - (rand() % 12);
				m_pEffectList[i]->m_mX3 = sX;
				m_pEffectList[i]->m_mY3 = sY;
				m_pEffectList[i]->m_iV1 = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				break;

			case EffectType::IMPACT_BURST:
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

			case EffectType::CRITICAL_STRIKE_1:
			case EffectType::CRITICAL_STRIKE_2:
			case EffectType::CRITICAL_STRIKE_3:
			case EffectType::CRITICAL_STRIKE_4:
			case EffectType::CRITICAL_STRIKE_5:
			case EffectType::CRITICAL_STRIKE_6:
			case EffectType::CRITICAL_STRIKE_7:
			case EffectType::CRITICAL_STRIKE_8: // Critical strike with a weapon
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 40;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 10;
				m_pEffectList[i]->m_cDir = CMisc::cCalcDirection(sX, sY, dX, dY);
				break;

			case EffectType::MASS_FIRE_STRIKE_CALLER1: // Mass-Fire-Strike (called 1 time)
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

			case EffectType::MASS_FIRE_STRIKE_CALLER3: // Mass-Fire-Strike (called 3 times)
			case EffectType::SALMON_BURST_IMPACT: //
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

			case EffectType::FOOTPRINT_RAIN: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 4;
				m_pEffectList[i]->m_dwFrameTime = 100;
				break;

			case EffectType::IMPACT_EFFECT: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 16;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			case EffectType::BLOODY_SHOCK_STRIKE: //
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

			case EffectType::MASS_MAGIC_MISSILE_AURA1: // Snoopy: Added for Mass Magic-Missile
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

			case EffectType::MASS_MAGIC_MISSILE_AURA2: // Snoopy: Added for Mass Magic-Missile
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

			case EffectType::CHILL_WIND_IMPACT: //
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

			case EffectType::ICE_STRIKE_VARIANT_1: // Large Type 1, 2, 3, 4
			case EffectType::ICE_STRIKE_VARIANT_2:
			case EffectType::ICE_STRIKE_VARIANT_3:
			case EffectType::ICE_STRIKE_VARIANT_4:
			case EffectType::ICE_STRIKE_VARIANT_5: // Small Type 1, 2
			case EffectType::ICE_STRIKE_VARIANT_6:
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

			case EffectType::BLIZZARD_VARIANT_1: // Blizzard
			case EffectType::BLIZZARD_VARIANT_2: // Blizzard
			case EffectType::BLIZZARD_VARIANT_3: // Blizzard
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

			case EffectType::SMOKE_DUST: //
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

			case EffectType::SPARKLE_SMALL:
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 9; //15;
				m_pEffectList[i]->m_dwFrameTime = 80;
				break;

			case EffectType::PROTECTION_RING: // Protect ring
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

			case EffectType::HOLD_TWIST: // Hold twist
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

			case EffectType::STAR_TWINKLE: // star twingkling (effect armes brillantes)
			case EffectType::UNUSED_55: // Unused
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 10;
				m_pEffectList[i]->m_dwFrameTime = 15;
				break;

			case EffectType::MASS_CHILL_WIND: //  Mass-Chill-Wind
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

			case EffectType::BUFF_EFFECT_LIGHT: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 16;
				m_pEffectList[i]->m_dwFrameTime = 80;
				break;

			case EffectType::METEOR_FLYING: //
				m_pEffectList[i]->m_mX = sX + 300;
				m_pEffectList[i]->m_mY = sY - 460;
				m_pEffectList[i]->m_cMaxFrame = 10;
				m_pEffectList[i]->m_dwFrameTime = 50;
				break;

			case EffectType::FIRE_AURA_GROUND: //
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

			case EffectType::METEOR_IMPACT: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 6;
				m_pEffectList[i]->m_dwFrameTime = 100;
				break;

			case EffectType::FIRE_EXPLOSION_CRUSADE: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 16;
				m_pEffectList[i]->m_dwFrameTime = 20;
				break;

			case EffectType::WHITE_HALO: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 15;
				m_pEffectList[i]->m_dwFrameTime = 20;
				break;

			case EffectType::MS_CRUSADE_CASTING: // Crusade's MS
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 30;
				m_pEffectList[i]->m_dwFrameTime = 80;
				break;

			case EffectType::MS_CRUSADE_EXPLOSION: // Crusade MS explosion
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

			case EffectType::MS_FIRE_SMOKE: // Crusade's MS fire + smoke ?
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 27;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			case EffectType::WORM_BITE: // worm-bite
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

			case EffectType::LIGHT_EFFECT_1: // identique au cas 70
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

			case EffectType::LIGHT_EFFECT_2: // identtique au cas 69
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

			case EffectType::BLIZZARD_PROJECTILE: //
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

			case EffectType::BLIZZARD_IMPACT: // Blizzard
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

			case EffectType::AURA_EFFECT_1:
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 15;
				m_pEffectList[i]->m_dwFrameTime = 60;
				break;

			case EffectType::AURA_EFFECT_2:
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 19;
				m_pEffectList[i]->m_dwFrameTime = 40;
				break;

			case EffectType::ICE_GOLEM_EFFECT_1: //ice golem
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_dX = dX;
				m_pEffectList[i]->m_dY = dY;
				m_pEffectList[i]->m_cMaxFrame = 16;
				m_pEffectList[i]->m_dwFrameTime = 40;
				break;

			case EffectType::ICE_GOLEM_EFFECT_2: //ice golem
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_dX = dX;
				m_pEffectList[i]->m_dY = dY;
				m_pEffectList[i]->m_cMaxFrame = 16;
				m_pEffectList[i]->m_dwFrameTime = 40;
				break;

			case EffectType::ICE_GOLEM_EFFECT_3: //ice golem
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_dX = dX;
				m_pEffectList[i]->m_dY = dY;
				m_pEffectList[i]->m_cMaxFrame = 16;
				m_pEffectList[i]->m_dwFrameTime = 40;
				break;

			case EffectType::EARTH_SHOCK_WAVE_PARTICLE: // Snoopy: Added, implemented last in v351
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

			case EffectType::STORM_BLADE: //  Snoopy: Added (StormBlade)
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 27;
				m_pEffectList[i]->m_dwFrameTime = 40;
				break;

			case EffectType::GATE_APOCALYPSE: //  Snoopy: Added (Gate Apocalypse)
				m_pEffectList[i]->m_cMaxFrame = 30;
				m_pEffectList[i]->m_dwFrameTime = 40;
				break;

			case EffectType::MAGIC_MISSILE_FLYING: // MagicMissile is Flying
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 40;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 1, sDist, lPan);
				break;

			case EffectType::HEAL: // Heal
			case EffectType::STAMINA_DRAIN: // Staminar-Drain
			case EffectType::GREAT_HEAL: // Great Heal
			case EffectType::STAMINA_RECOVERY: // Staminar-Recovery
			case EffectType::GREAT_STAMINA_RECOVERY: // Great-Staminar-Recovery
				m_pEffectList[i]->m_cMaxFrame = 14;
				m_pEffectList[i]->m_dwFrameTime = 80;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 5, sDist, lPan);
				break;

			case EffectType::CREATE_FOOD: // CreateFood
			case EffectType::UNUSED_122: // Recall
			case EffectType::POSSESSION: // Possession
			case EffectType::POISON: // Poison
			case EffectType::DETECT_INVISIBILITY: // DetectInvi
			case EffectType::CURE: // Cure
			case EffectType::CONFUSE_LANGUAGE: // Confuse language
			case EffectType::POLYMORPH: // Polymorph
			case EffectType::MASS_POISON: // Mass-Poison
			case EffectType::CONFUSION: // Confusion
			case EffectType::MASS_CONFUSION: // Mass-Confusion
				m_pEffectList[i]->m_cMaxFrame = 13;
				m_pEffectList[i]->m_dwFrameTime = 120;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 5, sDist, lPan);
				break;

			case EffectType::ENERGY_BOLT_FLYING: // Energy-Bolt
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 40;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 1, sDist, lPan);
				break;

			case EffectType::RECALL: // Recall
			case EffectType::SUMMON_CREATURE: // Summon
			case EffectType::INVISIBILITY: // Invi
			case EffectType::HASTE: // Haste
				m_pEffectList[i]->m_cMaxFrame = 12;
				m_pEffectList[i]->m_dwFrameTime = 80;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 5, sDist, lPan);
				break;

			case EffectType::DEFENSE_SHIELD: // Defense-Shield
			case EffectType::GREAT_DEFENSE_SHIELD: // Great-Defense-Shield
				m_pEffectList[i]->m_cMaxFrame = 12;
				m_pEffectList[i]->m_dwFrameTime = 120;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 5, sDist, lPan);
				break;

			case EffectType::CELEBRATING_LIGHT: // Celebrating Light
				AddEffectImpl(static_cast<EffectType>(69 + (rand() % 2)), dX * 32 + 20 - (rand() % 40), dY * 32 + 20 - (rand() % 40), 0, 0, -12, 0);
				AddEffectImpl(static_cast<EffectType>(69 + (rand() % 2)), dX * 32 + 20 - (rand() % 40), dY * 32 + 20 - (rand() % 40), 0, 0, -9, 0);
				AddEffectImpl(static_cast<EffectType>(69 + (rand() % 2)), dX * 32 + 20 - (rand() % 40), dY * 32 + 20 - (rand() % 40), 0, 0, -6, 0);
				AddEffectImpl(static_cast<EffectType>(69 + (rand() % 2)), dX * 32 + 20 - (rand() % 40), dY * 32 + 20 - (rand() % 40), 0, 0, -3, 0);
				AddEffectImpl(static_cast<EffectType>(69 + (rand() % 2)), dX * 32 + 20 - (rand() % 40), dY * 32 + 20 - (rand() % 40), 0, 0, 0, 0);
				delete m_pEffectSpr[i];
				m_pEffectSpr[i] = 0;
				break;

			case EffectType::FIRE_BALL_FLYING: // Fire Ball
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 40;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				m_pEffectList[i]->m_cDir = CMisc::cCalcDirection(sX, sY, dX, dY);
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 1, sDist, lPan);
				break;

			case EffectType::PROTECT_FROM_NM: // Protect form N.M
			case EffectType::PROTECT_FROM_MAGIC: // Protection from Magic
				AddEffectImpl( EffectType::PROTECTION_RING, dX * 32, dY * 32, 0, 0, 0, 0);
				delete m_pEffectSpr[i];
				m_pEffectSpr[i] = 0;
				break;

			case EffectType::HOLD_PERSON: // Hold Person
			case EffectType::PARALYZE: // Paralyze
				AddEffectImpl( EffectType::HOLD_TWIST, dX * 32, dY * 32, 0, 0, 0, 0);
				delete m_pEffectSpr[i];
				m_pEffectSpr[i] = 0;
				break;

			case EffectType::FIRE_STRIKE_FLYING: // Fire Strike
			case EffectType::LIGHTNING_ARROW_FLYING: // Lightning Arrow
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 40;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				m_pEffectList[i]->m_cDir = CMisc::cCalcDirection(sX, sY, dX, dY);
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 1, sDist, lPan);
				break;

			case EffectType::TREMOR: // Tremor.
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 4, sDist, lPan);
				m_pGame->SetCameraShakingEffect(sDist, 2);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);

				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				m_pEffectList[i]->m_cMaxFrame = 2;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			case EffectType::LIGHTNING: // Lightning
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

			case EffectType::CHILL_WIND: // ChillWind
				m_pEffectList[i]->m_cMaxFrame = 2;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			case EffectType::TRIPLE_ENERGY_BOLT: // Triple-Energy-Bolt
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				break;

			case EffectType::BERSERK: // Berserk : Cirlcle 6 magic
			case EffectType::ILLUSION_MOVEMENT: // Illusion-Movement
			case EffectType::ILLUSION: // Illusion
			case EffectType::INHIBITION_CASTING: // Inhibition-Casting
			case EffectType::MASS_ILLUSION: // Mass-Illusion
			case EffectType::MASS_ILLUSION_MOVEMENT: // Mass-Illusion-Movement
				m_pEffectList[i]->m_cMaxFrame = 11;
				m_pEffectList[i]->m_dwFrameTime = 100;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 5, sDist, lPan);
				break;

			case EffectType::LIGHTNING_BOLT: // LightningBolt
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

			case EffectType::MASS_LIGHTNING_ARROW: // Mass-Ligtning-Arrow
				m_pEffectList[i]->m_cMaxFrame = 3;
				m_pEffectList[i]->m_dwFrameTime = 130;
				break;

			case EffectType::ICE_STRIKE: // Ice-Strike
				m_pEffectList[i]->m_cMaxFrame = 2;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			case EffectType::ENERGY_STRIKE: // Energy-Strike
				m_pEffectList[i]->m_cMaxFrame = 7;
				m_pEffectList[i]->m_dwFrameTime = 80;
				break;

			case EffectType::MASS_FIRE_STRIKE_FLYING: // Mass-Fire-Strike
			case EffectType::SALMON_BURST: //
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 40;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				m_pEffectList[i]->m_cDir = CMisc::cCalcDirection(sX, sY, dX, dY);
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 1, sDist, lPan);
				break;

			case EffectType::MASS_CHILL_WIND_SPELL: // Mass-Chill-Wind
				m_pEffectList[i]->m_cMaxFrame = 2;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			case EffectType::WORM_BITE_MASS: // worm-bite
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 4, sDist, lPan);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);

				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				AddEffectImpl( EffectType::FOOTPRINT, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
				m_pEffectList[i]->m_cMaxFrame = 1;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			case EffectType::ABSOLUTE_MAGIC_PROTECTION: // Absolute-Magic-Protection
				m_pEffectList[i]->m_cMaxFrame = 21;
				m_pEffectList[i]->m_dwFrameTime = 70;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 5, sDist, lPan);
				break;

			case EffectType::ARMOR_BREAK: // Armor Break
				m_pEffectList[i]->m_cMaxFrame = 13;
				m_pEffectList[i]->m_dwFrameTime = 80;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 5, sDist, lPan);
				break;

			case EffectType::BLOODY_SHOCK_WAVE: // Bloody-Shock-Wave
				m_pEffectList[i]->m_cMaxFrame = 7;
				m_pEffectList[i]->m_dwFrameTime = 80;
				break;

			case EffectType::MASS_ICE_STRIKE: // Mass-Ice-Strike
				m_pEffectList[i]->m_cMaxFrame = 2;
				m_pEffectList[i]->m_dwFrameTime = 10;
				break;

			case EffectType::LIGHTNING_STRIKE: // Lightning-Strike
				m_pEffectList[i]->m_cMaxFrame = 5;
				m_pEffectList[i]->m_dwFrameTime = 120;
				break;

			case EffectType::CANCELLATION: // Snoopy: Added Cancellation
				m_pEffectList[i]->m_cMaxFrame = 23;
				m_pEffectList[i]->m_dwFrameTime = 60;
				sDist = sDist / 32;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 5, sDist, lPan);
				break;

			case EffectType::METEOR_STRIKE_DESCENDING: // MS
				m_pEffectList[i]->m_mX = dX * 32 + 300;
				m_pEffectList[i]->m_mY = dY * 32 - 460;
				m_pEffectList[i]->m_cMaxFrame = 10;
				m_pEffectList[i]->m_dwFrameTime = 25;
				break;

			case EffectType::MASS_MAGIC_MISSILE_FLYING: // Snoopy: Added Mass-Magic-Missile
				m_pEffectList[i]->m_mX = sX * 32;
				m_pEffectList[i]->m_mY = sY * 32 - 40;
				m_pEffectList[i]->m_iErr = 0;
				m_pEffectList[i]->m_cMaxFrame = 0;
				m_pEffectList[i]->m_dwFrameTime = 20;
				lPan = -(((m_pGame->m_sViewPointX / 32) + fixx) - sX) * fixpan;
				m_pGame->PlaySound('E', 1, sDist, lPan);
				break;

			case EffectType::MASS_MM_AURA_CASTER: // Snoopy: Moved for new spells: Caster aura for Mass MagicMissile
				//case 184: // Effect on caster for MassMM
				m_pEffectList[i]->m_cMaxFrame = 29;
				m_pEffectList[i]->m_dwFrameTime = 80;
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				break;

			case EffectType::BLIZZARD: // Blizzard
				m_pEffectList[i]->m_cMaxFrame = 7;
				m_pEffectList[i]->m_dwFrameTime = 80;
				break;

				//case 192: // Hero set Effect
			case EffectType::MAGE_HERO_SET: // Hero set Effect
				m_pEffectList[i]->m_cMaxFrame = 30;
				m_pEffectList[i]->m_dwFrameTime = 40;
				break;

				//case 193: // Hero set Effect
			case EffectType::WAR_HERO_SET: // Hero set Effect
				m_pEffectList[i]->m_cMaxFrame = 19;
				m_pEffectList[i]->m_dwFrameTime = 18;
				break;

			case EffectType::RESURRECTION: // Resurrection
				m_pEffectList[i]->m_cMaxFrame = 30;
				m_pEffectList[i]->m_dwFrameTime = 40;
				break;

			case EffectType::EARTH_SHOCK_WAVE: // Snoopy: Added Earth-Shock-Wave
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
			case EffectType::SHOTSTAR_FALL_1: //
			case EffectType::SHOTSTAR_FALL_2: //
			case EffectType::SHOTSTAR_FALL_3: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 15;
				m_pEffectList[i]->m_dwFrameTime = 25;
				break;

			case EffectType::EXPLOSION_FIRE_APOCALYPSE: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 18;
				m_pEffectList[i]->m_dwFrameTime = 70;
				break;

			case EffectType::CRACK_OBLIQUE: //
			case EffectType::CRACK_HORIZONTAL: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 12;
				m_pEffectList[i]->m_dwFrameTime = 70;
				break;

			case EffectType::STEAMS_SMOKE: //
				m_pEffectList[i]->m_mX = sX;
				m_pEffectList[i]->m_mY = sY;
				m_pEffectList[i]->m_cMaxFrame = 3;
				m_pEffectList[i]->m_dwFrameTime = 70;
				break;

			case EffectType::GATE_ROUND: //
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
