// Effect_Lights.cpp: DrawEffectLights implementation
//
//////////////////////////////////////////////////////////////////////

#include "EffectManager.h"
#include "Game.h"
#include "Sprite.h"
#include "Effect.h"
#include "GlobalDef.h"

void EffectManager::DrawEffectLightsImpl()
{
	int i, dX, dY, iDvalue;
	uint32_t dwTime = m_pGame->m_dwCurTime;
	char  cTempFrame;
	for (i = 0; i < DEF_MAXEFFECTS; i++)
		if (m_pEffectList[i] != 0) {
			switch (m_pEffectList[i]->m_sType) {
			case EffectType::NORMAL_HIT:
				break;

			case EffectType::ARROW_FLYING:
				break;

			case EffectType::GOLD_DROP:
				break;

			case EffectType::FIREBALL_EXPLOSION:	// Fire Explosion
				if (m_pEffectList[i]->m_cFrame >= 0)
				{
					dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
					dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
					iDvalue = (m_pEffectList[i]->m_cFrame - 7) * (-1);
					if (m_pEffectList[i]->m_cFrame < 6)
						m_pEffectSpr[0]->PutTransSprite_NoColorKey(dX, dY + 30, 1, dwTime);
					else m_pEffectSpr[0]->PutTransSpriteRGB(dX, dY + 30, 1, iDvalue, iDvalue, iDvalue, dwTime);
				}
				break;

			case EffectType::ENERGY_BOLT_EXPLOSION:	 // Energy Bolt
			case EffectType::LIGHTNING_ARROW_EXPLOSION: // Lightning Arrow
				if (m_pEffectList[i]->m_cFrame >= 0)
				{
					dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
					dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
					iDvalue = (m_pEffectList[i]->m_cFrame - 9) * (-1);
					if (m_pEffectList[i]->m_cFrame < 8)
						m_pEffectSpr[0]->PutTransSprite_NoColorKey(dX, dY + 30, 1, dwTime);
					else m_pEffectSpr[0]->PutTransSpriteRGB(dX, dY + 30, 1, iDvalue, iDvalue, iDvalue, dwTime);
				}
				break;
			case EffectType::MAGIC_MISSILE_EXPLOSION: // Magic Missile Explosion
				if (m_pEffectList[i]->m_cFrame >= 0)
				{
					dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
					dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
					iDvalue = (m_pEffectList[i]->m_cFrame - 2) * (-1);
					if (m_pEffectList[i]->m_cFrame < 2)
						m_pEffectSpr[0]->PutTransSprite_NoColorKey(dX, dY + 30, 1, dwTime);
					else m_pEffectSpr[0]->PutTransSpriteRGB(dX, dY + 30, 1, iDvalue, iDvalue, iDvalue, dwTime);
				}
				break;

			case EffectType::PROJECTILE_GENERIC:
			case EffectType::FIRE_AURA_GROUND:
			case EffectType::MS_CRUSADE_EXPLOSION:
			case EffectType::MAGIC_MISSILE_FLYING:
			case EffectType::ENERGY_BOLT_FLYING:
			case EffectType::FIRE_BALL_FLYING:
			case EffectType::FIRE_STRIKE_FLYING:
			case EffectType::LIGHTNING_ARROW_FLYING: // Lightning arrow
				// Light on ground below the flying effect
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				iDvalue = -5;
				m_pEffectSpr[0]->PutTransSpriteRGB(dX, dY + 30, 1, iDvalue, iDvalue, iDvalue, dwTime);
				break;

			case EffectType::LIGHT_EFFECT_1:
			case EffectType::LIGHT_EFFECT_2:
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[0]->PutTransSprite25(dX, dY + 30, 1, dwTime);
				break;

			case EffectType::IMPACT_EFFECT:
				break;

			case EffectType::CHILL_WIND_IMPACT:
			case EffectType::MASS_CHILL_WIND:
				if (m_pEffectList[i]->m_cFrame >= 0)
				{
					dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
					dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
					iDvalue = (m_pEffectList[i]->m_cFrame - 7) * (-1);
					if (m_pEffectList[i]->m_cFrame < 6)
						m_pEffectSpr[0]->PutTransSprite(dX, dY, 1, dwTime);
					else m_pEffectSpr[0]->PutTransSpriteRGB(dX, dY, 1, iDvalue, iDvalue, iDvalue, dwTime);
				}
				break;

			case EffectType::PROTECTION_RING: // Protection Ring
				if (m_pEffectList[i]->m_cFrame >= 0)
				{
					dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
					dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
					m_pEffectSpr[24]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
				}
				break;

			case EffectType::BUFF_EFFECT_LIGHT:
				if (m_pEffectList[i]->m_cFrame >= 0) {
					dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
					dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
					m_pEffectSpr[30]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
				}
				break;

			case EffectType::AURA_EFFECT_1:
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[74]->PutTransSprite(dX, dY - 34, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case EffectType::AURA_EFFECT_2:
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[75]->PutTransSprite(dX, dY + 35, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case EffectType::ICE_GOLEM_EFFECT_1: // Icegolem
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[76]->PutTransSprite25(dX + m_pEffectList[i]->m_dX * m_pEffectList[i]->m_cFrame, dY + m_pEffectList[i]->m_dY * m_pEffectList[i]->m_cFrame, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case EffectType::ICE_GOLEM_EFFECT_2:// Icegolem
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[77]->PutTransSprite25(dX + m_pEffectList[i]->m_dX * m_pEffectList[i]->m_cFrame, dY + m_pEffectList[i]->m_dY * m_pEffectList[i]->m_cFrame, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case EffectType::ICE_GOLEM_EFFECT_3:// Icegolem
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[78]->PutTransSprite25(dX + m_pEffectList[i]->m_dX * m_pEffectList[i]->m_cFrame, dY + m_pEffectList[i]->m_dY * m_pEffectList[i]->m_cFrame, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case EffectType::BERSERK: // Berserk : Cirlcle 6 magic
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				m_pEffectSpr[58]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case EffectType::ILLUSION: // Ilusion
			case EffectType::MASS_ILLUSION: // Mass Illusion
				cTempFrame = m_pEffectList[i]->m_cFrame;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				m_pEffectSpr[59]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case EffectType::ILLUSION_MOVEMENT: // Illusion mvt
			case EffectType::MASS_ILLUSION_MOVEMENT: // Mass Illusion mvt
				cTempFrame = m_pEffectList[i]->m_cFrame;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				m_pEffectSpr[102]->PutTransSprite_NoColorKey(dX, dY + 30, cTempFrame, dwTime);
				break;

			case EffectType::INHIBITION_CASTING: // Inhibition casting
				cTempFrame = m_pEffectList[i]->m_cFrame;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				m_pEffectSpr[95]->PutTransSprite_NoColorKey(dX, dY + 40, cTempFrame, dwTime);
				break;
			}
		}
}
