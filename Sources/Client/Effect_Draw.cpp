// Effect_Draw.cpp: DrawEffects implementation
//
//////////////////////////////////////////////////////////////////////

#include "EffectManager.h"
#include "Game.h"
#include "Sprite.h"
#include "Effect.h"
#include "GlobalDef.h"
#include "Misc.h"

void EffectManager::DrawEffectsImpl()
{
	int i, dX, dY, iDvalue, tX, tY, rX, rY, rX2, rY2, rX3, rY3, rX4, rY4, rX5, rY5, iErr;
	char  cTempFrame;
	uint32_t dwTime = m_pGame->m_dwCurTime;
	short sObjectType;
	char  cName[21];
	int iStatus;

	for (i = 0; i < DEF_MAXEFFECTS; i++)
		if ((m_pEffectList[i] != 0) && (m_pEffectList[i]->m_cFrame >= 0))
		{
			switch (m_pEffectList[i]->m_sType) {
			case EffectType::NORMAL_HIT: // Normal hit
				if (m_pEffectList[i]->m_cFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[8]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case EffectType::ARROW_FLYING: // Arrow flying
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				cTempFrame = (m_pEffectList[i]->m_cDir - 1) * 2;
				if (cTempFrame < 0) break;
				m_pEffectSpr[7]->PutSpriteFast(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::GOLD_DROP: // gold
				/// 1.5
				if (m_pEffectList[i]->m_cFrame < 9) break;
				cTempFrame = m_pEffectList[i]->m_cFrame - 9;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[1]->PutSpriteFast(dX, dY - 40, cTempFrame, dwTime);

				break;

			case EffectType::FIREBALL_EXPLOSION: // FireBall Fire Explosion
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				iDvalue = (cTempFrame - 8) * (-5);
				if (cTempFrame < 7)
					m_pEffectSpr[3]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				else m_pEffectSpr[3]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime);
				break;

			case EffectType::ENERGY_BOLT_EXPLOSION:	 // Energy Bolt
			case EffectType::LIGHTNING_ARROW_EXPLOSION: // Lightning Arrow
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				iDvalue = (cTempFrame - 7) * (-6);
				if (cTempFrame < 6)
					m_pEffectSpr[6]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				else m_pEffectSpr[6]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
				break;

			case EffectType::MAGIC_MISSILE_EXPLOSION: // Magic Missile Explosion
				cTempFrame = m_pEffectList[i]->m_cFrame;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				iDvalue = (cTempFrame - 4) * (-3);
				if (cTempFrame < 4)
					m_pEffectSpr[6]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				else m_pEffectSpr[6]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
				break;

			case EffectType::BURST_SMALL: // Burst
				cTempFrame = m_pEffectList[i]->m_cFrame;
				cTempFrame = 4 - cTempFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::BURST_MEDIUM: // Burst
				cTempFrame = (rand() % 5);
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::BURST_SMALL_GRENADE: // pt grenat
				cTempFrame = (rand() % 5) + 5;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[11]->PutTransSprite2(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::BURST_LARGE: // Burst
				cTempFrame = (rand() % 6) + 10;
				if (cTempFrame < 0) break;
				iDvalue = (m_pEffectList[i]->m_cFrame - 4) * (-3);
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				if (cTempFrame < 4)
					m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				else //m_pEffectSpr[11]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
				//
					m_pEffectSpr[11]->PutTransSprite(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::BUBBLES_DRUNK:
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				if (cTempFrame < 13)
				{
					m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, 25 + (cTempFrame / 5), dwTime);
				}
				else
				{
					m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, (8 + cTempFrame), dwTime);
				}
				break;

			case EffectType::FOOTPRINT: // Traces of pas (terrain sec)
				if (m_pEffectList[i]->m_cFrame < 0) break;
				dX = m_pEffectList[i]->m_mX - m_pGame->m_sViewPointX;
				dY = m_pEffectList[i]->m_mY - m_pGame->m_sViewPointY;
				m_pEffectSpr[11]->PutTransSprite50_NoColorKey(dX, dY, (28 + m_pEffectList[i]->m_cFrame), dwTime);
				break;

			case EffectType::RED_CLOUD_PARTICLES: // petits nuages rouges
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = m_pEffectList[i]->m_mX - m_pGame->m_sViewPointX;
				dY = m_pEffectList[i]->m_mY - m_pGame->m_sViewPointY;
				m_pEffectSpr[11]->PutTransSprite50_NoColorKey(dX, dY, (33 + cTempFrame), dwTime);
				break;

			case EffectType::PROJECTILE_GENERIC: //
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[0]->PutTransSprite_NoColorKey(dX, dY, 0, dwTime);
				break;

			case EffectType::ICE_STORM: //test
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				cTempFrame = 39 + (rand() % 3) * 3 + (rand() % 3);
				if (cTempFrame < 0) break;
				m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				dX = (m_pEffectList[i]->m_mX2) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY2) - m_pGame->m_sViewPointY;
				m_pEffectSpr[11]->PutTransSprite50_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::IMPACT_BURST: //
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				m_pEffectSpr[18]->PutTransSprite70_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::CRITICAL_STRIKE_1: // critical hit
			case EffectType::CRITICAL_STRIKE_2:
			case EffectType::CRITICAL_STRIKE_3:
			case EffectType::CRITICAL_STRIKE_4:
			case EffectType::CRITICAL_STRIKE_5:
			case EffectType::CRITICAL_STRIKE_6:
			case EffectType::CRITICAL_STRIKE_7:
			case EffectType::CRITICAL_STRIKE_8: // Critical strike with a weapon
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[8]->PutTransSprite_NoColorKey(dX, dY, 1, dwTime);
				break;

			case EffectType::MASS_FIRE_STRIKE_CALLER1: // Mass-Fire-Strike
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				m_pEffectSpr[14]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::MASS_FIRE_STRIKE_CALLER3: // Mass-Fire-Strike
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				m_pEffectSpr[15]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::FOOTPRINT_RAIN: // Trace of pas  (raining weather)
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				cTempFrame = m_pEffectList[i]->m_cFrame + 20;
				if (cTempFrame < 0) break;
				m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::IMPACT_EFFECT: //
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				iDvalue = 0;
				m_pEffectSpr[19]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
				break;

			case EffectType::BLOODY_SHOCK_STRIKE: // absent (220 et 351)
				break;

			case EffectType::MASS_MAGIC_MISSILE_AURA1: // Snoopy: Added if (m_pEffectList[i]->m_cFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				cTempFrame = m_pEffectList[i]->m_cFrame;
				m_pEffectSpr[6]->PutTransSprite_NoColorKey(dX - 30, dY - 18, cTempFrame, dwTime);
				break;

			case EffectType::MASS_MAGIC_MISSILE_AURA2: // Snoopy: Added if (m_pEffectList[i]->m_cFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				cTempFrame = m_pEffectList[i]->m_cFrame;
				m_pEffectSpr[97]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::CHILL_WIND_IMPACT:
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[20]->PutTransSprite50_NoColorKey(dX, dY, cTempFrame, dwTime); // 20
				break;

			case EffectType::ICE_STRIKE_VARIANT_1: // Large Type 1, 2, 3, 4
			case EffectType::ICE_STRIKE_VARIANT_2:
			case EffectType::ICE_STRIKE_VARIANT_3:
			case EffectType::ICE_STRIKE_VARIANT_4:
			case EffectType::ICE_STRIKE_VARIANT_5: // Small Type 1, 2
			case EffectType::ICE_STRIKE_VARIANT_6:
				dX = (m_pEffectList[i]->m_sX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_sY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[21]->PutFadeSprite(dX, dY, 48, dwTime);
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				if ((8 * (static_cast<int>(m_pEffectList[i]->m_sType) - 41) + cTempFrame) < (8 * (static_cast<int>(m_pEffectList[i]->m_sType) - 41) + 7))
				{
					iDvalue = -8 * (6 - cTempFrame);
					m_pEffectSpr[21]->PutTransSpriteRGB(dX, dY, 8 * (static_cast<int>(m_pEffectList[i]->m_sType) - 41) + cTempFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
				}
				else
				{
					if ((cTempFrame - 5) >= 8) cTempFrame = ((cTempFrame - 5) - 8) + 5;
					m_pEffectSpr[21]->PutSpriteFast(dX, dY, 8 * (static_cast<int>(m_pEffectList[i]->m_sType) - 41) + (cTempFrame - 5), dwTime);
				}
				break;

			case EffectType::BLIZZARD_VARIANT_1:
			case EffectType::BLIZZARD_VARIANT_2:
			case EffectType::BLIZZARD_VARIANT_3: // Blizzard
				dX = (m_pEffectList[i]->m_sX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_sY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[static_cast<int>(m_pEffectList[i]->m_sType) - 1]->PutRevTransSprite(dX, dY, 0, dwTime);
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				//PutString(dX, dY, "*", RGB(255,255,255);
				if (cTempFrame < 7) {
					iDvalue = -8 * (6 - cTempFrame);
					m_pEffectSpr[static_cast<int>(m_pEffectList[i]->m_sType) - 1]->PutTransSpriteRGB(dX, dY, cTempFrame + 1, iDvalue, iDvalue, iDvalue, dwTime);
				}
				else {
					if (cTempFrame >= 8) cTempFrame = cTempFrame % 8;
					m_pEffectSpr[static_cast<int>(m_pEffectList[i]->m_sType) - 1]->PutSpriteFast(dX, dY, cTempFrame + 1, dwTime);
				}
				break;

			case EffectType::SMOKE_DUST:
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;

				if (cTempFrame <= 6) {
					iDvalue = 0;
					m_pEffectSpr[22]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime);	// RGB2
				}
				else {
					iDvalue = -5 * (cTempFrame - 6);
					m_pEffectSpr[22]->PutTransSpriteRGB(dX, dY, 6, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
				}
				break;

			case EffectType::SPARKLE_SMALL: //
				cTempFrame = m_pEffectList[i]->m_cFrame + 11; //15
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[28]->PutTransSprite25(dX, dY, cTempFrame, dwTime); //20
				break;


			case EffectType::PROTECTION_RING: // Protection Ring commente par siementec, a voir
				/*			cTempFrame = m_pEffectList[i]->m_cFrame;
					dX  = (m_pEffectList[i]->m_mX)  - m_pGame->m_sViewPointX;
					dY  = (m_pEffectList[i]->m_mY)  - m_pGame->m_sViewPointY;
					m_pEffectSpr[24]->PutTransSprite(dX, dY, cTempFrame, dwTime);
				*/
				break;


			case EffectType::HOLD_TWIST: // Hold Twist
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				if (cTempFrame < 0) cTempFrame = 0;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[25]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime); //25
				break;

			case EffectType::STAR_TWINKLE: //  star twingkling (effect armes brillantes)
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) cTempFrame = 0;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[28]->PutTransSprite(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::UNUSED_55: //
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) cTempFrame = 0;
				dX = (m_pEffectList[i]->m_mX);
				dY = (m_pEffectList[i]->m_mY);
				m_pEffectSpr[28]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::MASS_CHILL_WIND: // Mass-Chill-Wind
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) cTempFrame = 0;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[29]->PutTransSprite50_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::BUFF_EFFECT_LIGHT:  // absent (220 et 351)
				break;

			case EffectType::METEOR_FLYING:  //
			case EffectType::METEOR_STRIKE_DESCENDING: // MS
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				if (cTempFrame > 4)
				{
					cTempFrame = cTempFrame / 4;
				}
				if (cTempFrame >= 0)
				{
					dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
					dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
					m_pEffectSpr[31]->PutSpriteFast(dX, dY, 15 + cTempFrame, dwTime);
					m_pEffectSpr[31]->PutTransSprite(dX, dY, cTempFrame, dwTime);
				}
				break;

			case EffectType::FIRE_AURA_GROUND: // Fire aura on ground (crueffect1, 1)
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[32]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::METEOR_IMPACT: // MS strike
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				if (cTempFrame > 0)
				{
					cTempFrame = cTempFrame - 1;
					dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
					dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
					m_pEffectSpr[31]->PutRevTransSprite(dX, dY, 20 + cTempFrame, dwTime, cTempFrame / 3);
				}
				break;

			case EffectType::FIRE_EXPLOSION_CRUSADE: // Fire explosion (crueffect1, 2)
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[33]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::WHITE_HALO: // Whitish halo effect
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[34]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::MS_CRUSADE_CASTING: // MS from crusade striking
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				cTempFrame = cTempFrame / 6;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[31]->PutRevTransSprite(dX, dY, 20 + cTempFrame, dwTime, cTempFrame >> 2);
				break;

			case EffectType::MS_CRUSADE_EXPLOSION: // MS explodes on the ground
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[39]->PutRevTransSprite(dX, dY, cTempFrame, dwTime);
				m_pEffectSpr[39]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::MS_FIRE_SMOKE: // MS fire with smoke
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				switch (rand() % 3) {
				case EffectType::INVALID: m_pEffectSpr[0]->PutTransSprite25_NoColorKey(dX, dY + 20, 1, dwTime); break;
				case EffectType::NORMAL_HIT: m_pEffectSpr[0]->PutTransSprite50_NoColorKey(dX, dY + 20, 1, dwTime); break;
				case EffectType::ARROW_FLYING: m_pEffectSpr[0]->PutTransSprite70_NoColorKey(dX, dY + 20, 1, dwTime); break;
				}
				m_pEffectSpr[35]->PutTransSprite70_NoColorKey(dX, dY, cTempFrame / 3, dwTime);
				break;

			case EffectType::WORM_BITE: // worm-bite
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				if (cTempFrame <= 11)
				{
					m_pEffectSpr[40]->PutSpriteFast(dX, dY, cTempFrame, dwTime);
					m_pEffectSpr[41]->PutTransSprite50_NoColorKey(dX, dY, cTempFrame, dwTime);
					m_pEffectSpr[44]->PutRevTransSprite(dX - 2, dY - 3, cTempFrame, dwTime);
					m_pEffectSpr[44]->PutTransSprite_NoColorKey(dX - 4, dY - 3, cTempFrame, dwTime);
				}
				else
				{
					switch (cTempFrame) {
					case EffectType::BURST_LARGE:
					case EffectType::BUBBLES_DRUNK:
					case EffectType::FOOTPRINT: m_pEffectSpr[40]->PutSpriteFast(dX, dY, 11, dwTime); break;
					case EffectType::RED_CLOUD_PARTICLES: m_pEffectSpr[40]->PutTransSprite70_NoColorKey(dX, dY, 11, dwTime); break;
					case EffectType::PROJECTILE_GENERIC: m_pEffectSpr[40]->PutTransSprite50_NoColorKey(dX, dY, 11, dwTime); break;
					case EffectType::ICE_STORM: m_pEffectSpr[40]->PutTransSprite25_NoColorKey(dX, dY, 11, dwTime); break;
					}
				}
				break;

			case EffectType::LIGHT_EFFECT_1: // identique au cas 70
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[42]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::LIGHT_EFFECT_2: // identique au cas 69
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[43]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::BLIZZARD_PROJECTILE: // absent v220 et v351
				break;

			case EffectType::BLIZZARD_IMPACT: // Blizzard
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				if (cTempFrame <= 8)
				{
					iDvalue = 0;
					m_pEffectSpr[51]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime);
				}
				else
				{
					iDvalue = -1 * (cTempFrame - 8);
					m_pEffectSpr[51]->PutTransSpriteRGB(dX, dY, 8, iDvalue, iDvalue, iDvalue, dwTime);	// RGB2
				}
				break;

			case EffectType::AURA_EFFECT_1: // absent v220 et v351
			case EffectType::AURA_EFFECT_2: // absent v220 et v351
			case EffectType::ICE_GOLEM_EFFECT_1: // absent v220 et v351
			case EffectType::ICE_GOLEM_EFFECT_2: // absent v220 et v351
			case EffectType::ICE_GOLEM_EFFECT_3: // absent v220 et v351
				break;

			case EffectType::EARTH_SHOCK_WAVE_PARTICLE:
			case EffectType::EARTH_SHOCK_WAVE: // Earth-Shock-Wave
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[91]->PutSpriteFast(dX, dY, cTempFrame, dwTime); //Nbe d'arguments modifi�s ds the 351....
				m_pEffectSpr[92]->PutTransSprite(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::STORM_BLADE: // Snoopy: Added StormBlade
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				cTempFrame = m_pEffectList[i]->m_cFrame;
				m_pEffectSpr[100]->PutTransSprite_NoColorKey(dX + 70, dY + 70, cTempFrame, dwTime);
				break;

			case EffectType::GATE_APOCALYPSE: // Gate (apocalypse)
				cTempFrame = m_pEffectList[i]->m_cFrame;
				m_pEffectSpr[101]->PutTransSprite_NoColorKey(320, 480, cTempFrame, dwTime);
				break;

			case EffectType::MAGIC_MISSILE_FLYING: // Magic Missile
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[0]->PutTransSprite_NoColorKey(dX, dY, 0, dwTime);
				break;

			case EffectType::HEAL: // Heal
			case EffectType::GREAT_HEAL: // Great-Heal
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				iDvalue = (cTempFrame - 5) * (-5);
				m_pEffectSpr[50]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case EffectType::CREATE_FOOD: // Create Food
			case EffectType::PROTECT_FROM_NM: // Protection from N.M
			case EffectType::HOLD_PERSON: // Hold-Person
			case EffectType::POSSESSION: // Possession
			case EffectType::POISON: // Poison
			case EffectType::PROTECT_FROM_MAGIC: // Protect-From-Magic
			case EffectType::DETECT_INVISIBILITY: // Detect-Invisibility
			case EffectType::PARALYZE: // Paralyze
			case EffectType::CURE: // Cure
			case EffectType::CONFUSE_LANGUAGE: // Confuse Language
			case EffectType::POLYMORPH: // Polymorph
			case EffectType::MASS_POISON: // Mass-Poison
			case EffectType::CONFUSION: // Confusion
			case EffectType::MASS_CONFUSION: // Mass-Confusion
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				iDvalue = (cTempFrame - 5) * (-5);
				if (cTempFrame < 5)
					m_pEffectSpr[4]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
				else m_pEffectSpr[4]->PutTransSpriteRGB(dX, dY, m_pEffectList[i]->m_cFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
				break;

			case EffectType::ENERGY_BOLT_FLYING: // Energy-Bolt
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[0]->PutTransSprite_NoColorKey(dX, dY, 2 + (rand() % 4), dwTime);
				break;

			case EffectType::STAMINA_DRAIN: // Staminar Drain
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				iDvalue = (cTempFrame - 5) * (-5);
				m_pEffectSpr[49]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case EffectType::RECALL: // Recall
			case EffectType::SUMMON_CREATURE: // Summon-Creature
			case EffectType::INVISIBILITY: // Invisibility
			case EffectType::HASTE: // Haste
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				iDvalue = (cTempFrame - 5) * (-5);
				m_pEffectSpr[52]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case EffectType::DEFENSE_SHIELD: // Defense Shield
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				iDvalue = (cTempFrame - 5) * (-5);
				if (cTempFrame < 6)
					m_pEffectSpr[62]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
				else m_pEffectSpr[62]->PutTransSpriteRGB(dX, dY, m_pEffectList[i]->m_cFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
				break;

			case EffectType::FIRE_BALL_FLYING: // Fire Ball
			case EffectType::FIRE_STRIKE_FLYING: // Fire Strike
			case EffectType::MASS_FIRE_STRIKE_FLYING: // Mass-Fire-Strike
			case EffectType::SALMON_BURST: //
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				cTempFrame = (m_pEffectList[i]->m_cDir - 1) * 4 + (rand() % 4);
				if (cTempFrame < 0) break;
				m_pEffectSpr[5]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::UNUSED_122: // Absent v220 et 351
				break;

			case EffectType::STAMINA_RECOVERY: // Staminar-Recovery
			case EffectType::GREAT_STAMINA_RECOVERY: // Great-Staminar-Recovery
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				iDvalue = (cTempFrame - 5) * (-5);
				m_pEffectSpr[56]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case EffectType::LIGHTNING_ARROW_FLYING: // Lightning Arrow
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				tX = (m_pEffectList[i]->m_mX2) - m_pGame->m_sViewPointX;
				tY = (m_pEffectList[i]->m_mY2) - m_pGame->m_sViewPointY;
				iErr = 0;
				CMisc::GetPoint(dX, dY, tX, tY, &rX, &rY, &iErr, 15);
				CMisc::GetPoint(dX, dY, tX, tY, &rX2, &rY2, &iErr, 30);
				CMisc::GetPoint(dX, dY, tX, tY, &rX3, &rY3, &iErr, 45);
				CMisc::GetPoint(dX, dY, tX, tY, &rX4, &rY4, &iErr, 60);
				CMisc::GetPoint(dX, dY, tX, tY, &rX5, &rY5, &iErr, 75);
				cTempFrame = (m_pEffectList[i]->m_cDir - 1) * 4 + (rand() % 4);
				if (cTempFrame < 0) break;
				m_pEffectSpr[10]->PutTransSprite25_NoColorKey(rX5, rY5, cTempFrame, dwTime);
				cTempFrame = (m_pEffectList[i]->m_cDir - 1) * 4 + (rand() % 4);
				if (cTempFrame < 0) break;
				m_pEffectSpr[10]->PutTransSprite25_NoColorKey(rX4, rY4, cTempFrame, dwTime);
				cTempFrame = (m_pEffectList[i]->m_cDir - 1) * 4 + (rand() % 4);
				if (cTempFrame < 0) break;
				m_pEffectSpr[10]->PutTransSprite50_NoColorKey(rX3, rY3, cTempFrame, dwTime);
				cTempFrame = (m_pEffectList[i]->m_cDir - 1) * 4 + (rand() % 4);
				if (cTempFrame < 0) break;
				m_pEffectSpr[10]->PutTransSprite50_NoColorKey(rX2, rY2, cTempFrame, dwTime);
				cTempFrame = (m_pEffectList[i]->m_cDir - 1) * 4 + (rand() % 4);
				if (cTempFrame < 0) break;
				m_pEffectSpr[10]->PutTransSprite70_NoColorKey(rX, rY, cTempFrame, dwTime);
				cTempFrame = (m_pEffectList[i]->m_cDir - 1) * 4 + (rand() % 4);
				if (cTempFrame < 0) break;
				m_pEffectSpr[10]->PutTransSprite(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::LIGHTNING: // Lightning
				m_pGame->_DrawThunderEffect(m_pEffectList[i]->m_dX * 32 - m_pGame->m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_pGame->m_sViewPointY - LOGICAL_WIDTH,
					m_pEffectList[i]->m_dX * 32 - m_pGame->m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_pGame->m_sViewPointY,
					m_pEffectList[i]->m_rX, m_pEffectList[i]->m_rY, 1);
				m_pGame->_DrawThunderEffect(m_pEffectList[i]->m_dX * 32 - m_pGame->m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_pGame->m_sViewPointY - LOGICAL_WIDTH,
					m_pEffectList[i]->m_dX * 32 - m_pGame->m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_pGame->m_sViewPointY,
					m_pEffectList[i]->m_rX + 4, m_pEffectList[i]->m_rY + 2, 2);
				m_pGame->_DrawThunderEffect(m_pEffectList[i]->m_dX * 32 - m_pGame->m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_pGame->m_sViewPointY - LOGICAL_WIDTH,
					m_pEffectList[i]->m_dX * 32 - m_pGame->m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_pGame->m_sViewPointY,
					m_pEffectList[i]->m_rX - 2, m_pEffectList[i]->m_rY - 2, 2);
				break;

			case EffectType::GREAT_DEFENSE_SHIELD: // Great-Defense-Shield
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				iDvalue = (cTempFrame - 5) * (-5);
				if (cTempFrame < 9)
					m_pEffectSpr[63]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
				else m_pEffectSpr[63]->PutTransSpriteRGB(dX, dY, m_pEffectList[i]->m_cFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
				break;

			case EffectType::LIGHTNING_BOLT: // Lightning Bolt
				m_pGame->_DrawThunderEffect(m_pEffectList[i]->m_mX - m_pGame->m_sViewPointX, m_pEffectList[i]->m_mY - m_pGame->m_sViewPointY,
					m_pEffectList[i]->m_dX * 32 - m_pGame->m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_pGame->m_sViewPointY,
					m_pEffectList[i]->m_rX, m_pEffectList[i]->m_rY, 1);

				m_pGame->_DrawThunderEffect(m_pEffectList[i]->m_mX - m_pGame->m_sViewPointX, m_pEffectList[i]->m_mY - m_pGame->m_sViewPointY,
					m_pEffectList[i]->m_dX * 32 - m_pGame->m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_pGame->m_sViewPointY,
					m_pEffectList[i]->m_rX + 2, m_pEffectList[i]->m_rY - 2, 2);

				m_pGame->_DrawThunderEffect(m_pEffectList[i]->m_mX - m_pGame->m_sViewPointX, m_pEffectList[i]->m_mY - m_pGame->m_sViewPointY,
					m_pEffectList[i]->m_dX * 32 - m_pGame->m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_pGame->m_sViewPointY,
					m_pEffectList[i]->m_rX - 2, m_pEffectList[i]->m_rY - 2, 2);
				break;

			case EffectType::ABSOLUTE_MAGIC_PROTECTION: // Absolute-Magic-Protect
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY; // 53 = APFM buble
				m_pEffectSpr[53]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case EffectType::ARMOR_BREAK: // Armor-Break
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				m_pEffectSpr[55]->PutRevTransSprite(dX, dY + 35, m_pEffectList[i]->m_cFrame, dwTime);
				m_pEffectSpr[54]->PutTransSprite50(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case EffectType::CANCELLATION: // Cancellation
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				m_pEffectSpr[90]->PutTransSprite_NoColorKey(dX + 50, dY + 85, cTempFrame, dwTime);
				break;

			case EffectType::ILLUSION_MOVEMENT: // Illusion-Movement
			case EffectType::ILLUSION: // Illusion
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				iDvalue = (cTempFrame - 5) * (-3);
				if (cTempFrame < 9)	m_pEffectSpr[60]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
				else m_pEffectSpr[60]->PutTransSpriteRGB(dX, dY, m_pEffectList[i]->m_cFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
				break;

			case EffectType::MASS_MAGIC_MISSILE_FLYING: //Mass-Magic-Missile
				cTempFrame = m_pEffectList[i]->m_cFrame;
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[98]->PutTransSprite(dX, dY, cTempFrame, dwTime, 0);
				break;

			case EffectType::INHIBITION_CASTING: // Inhibition-Casting
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				iDvalue = (cTempFrame - 5) * (-3);
				if (cTempFrame < 9) m_pEffectSpr[94]->PutTransSprite_NoColorKey(dX, dY + 40, m_pEffectList[i]->m_cFrame, dwTime);
				else m_pEffectSpr[94]->PutTransSpriteRGB(dX, dY + 40, m_pEffectList[i]->m_cFrame, iDvalue, iDvalue, iDvalue, dwTime);
				break;

			case EffectType::MASS_MM_AURA_CASTER: // Snoopy: Moved for new spells: Caster aura for Mass MagicMissile
				//case 184: // Caster aura for Mass MagicMissile
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = m_pEffectList[i]->m_mX - m_pGame->m_sViewPointX;
				dY = m_pEffectList[i]->m_mY - m_pGame->m_sViewPointY;
				m_pEffectSpr[96]->PutTransSprite(dX, dY, m_pEffectList[i]->m_cFrame, dwTime, 0);
				break;

			case EffectType::MASS_ILLUSION: // Mass-Illusion
			case EffectType::MASS_ILLUSION_MOVEMENT: // Mass-Illusion-Movement
				cTempFrame = m_pEffectList[i]->m_cFrame;
				if (cTempFrame < 0) break;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				iDvalue = (cTempFrame - 5) * (-3);
				if (cTempFrame < 9) m_pEffectSpr[61]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
				else m_pEffectSpr[61]->PutTransSpriteRGB(dX, dY, m_pEffectList[i]->m_cFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
				break;

				//case 192: // Mage Hero set effect
			case EffectType::MAGE_HERO_SET:
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				m_pEffectSpr[87]->PutTransSprite_NoColorKey(dX + 50, dY + 57, m_pEffectList[i]->m_cFrame, dwTime);
				break;

				//case 193: // War Hero set effect
			case EffectType::WAR_HERO_SET:
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				m_pEffectSpr[88]->PutTransSprite_NoColorKey(dX + 65, dY + 80, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case EffectType::RESURRECTION: // Resurrection
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				m_pEffectSpr[99]->PutTransSprite(dX, dY, m_pEffectList[i]->m_cFrame, dwTime, 0);
				break;

			case EffectType::SHOTSTAR_FALL_1: // shotstar fall on ground
				dX = m_pEffectList[i]->m_mX;
				dY = m_pEffectList[i]->m_mY;
				m_pEffectSpr[133]->PutTransSprite_NoColorKey(dX, dY, (rand() % 15), dwTime);
				break;

			case EffectType::SHOTSTAR_FALL_2: // shotstar fall on ground
				dX = m_pEffectList[i]->m_mX;
				dY = m_pEffectList[i]->m_mY;
				m_pEffectSpr[134]->PutTransSprite_NoColorKey(dX, dY, (rand() % 15), dwTime);
				break;

			case EffectType::SHOTSTAR_FALL_3: // shotstar fall on ground
				dX = m_pEffectList[i]->m_mX;
				dY = m_pEffectList[i]->m_mY;
				m_pEffectSpr[135]->PutTransSprite_NoColorKey(dX, dY, (rand() % 15), dwTime);
				break;

			case EffectType::EXPLOSION_FIRE_APOCALYPSE: // explosion feu apoc
				dX = m_pEffectList[i]->m_mX;
				dY = m_pEffectList[i]->m_mY;
				m_pEffectSpr[136]->PutTransSprite_NoColorKey(dX, dY, (rand() % 18), dwTime);
				break;

			case EffectType::CRACK_OBLIQUE: // Faille oblique
				dX = m_pEffectList[i]->m_mX;
				dY = m_pEffectList[i]->m_mY;
				m_pEffectSpr[137]->PutTransSprite_NoColorKey(dX, dY, (rand() % 12), dwTime);
				break;

			case EffectType::CRACK_HORIZONTAL: // Faille horizontale
				dX = m_pEffectList[i]->m_mX;
				dY = m_pEffectList[i]->m_mY;
				m_pEffectSpr[138]->PutTransSprite_NoColorKey(dX, dY, (rand() % 12), dwTime);
				break;

			case EffectType::STEAMS_SMOKE: // steams
				dX = m_pEffectList[i]->m_mX;
				dY = m_pEffectList[i]->m_mY;
				m_pEffectSpr[139]->PutTransSprite_NoColorKey(dX, dY, (rand() % 20), dwTime);
				break;

			case EffectType::GATE_ROUND: // Gate (round one)
				dX = m_pEffectList[i]->m_mX - m_pGame->m_sViewPointX;
				dY = m_pEffectList[i]->m_mY - m_pGame->m_sViewPointY;
				m_pEffectSpr[103]->PutTransSprite_NoColorKey(dX, dY, (rand() % 3), dwTime);
				break;

			case EffectType::SALMON_BURST_IMPACT: // burst (lisgt salmon color)
				dX = m_pEffectList[i]->m_mX - m_pGame->m_sViewPointX;
				dY = m_pEffectList[i]->m_mY - m_pGame->m_sViewPointY;
				m_pEffectSpr[104]->PutTransSprite_NoColorKey(dX, dY, (rand() % 3), dwTime);
				break;
			}
		}
}
