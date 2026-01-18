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
			case 1:
				break;

			case 2:
				break;

			case 4:
				break;

			case 5:	// Fire Explosion
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

			case 6:	 // Energy Bolt
			case 10: // Lightning Arrow
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
			case 7: // Magic Missile Explosion
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

			case 16:
			case 61:
			case 66:
			case 100:
			case 110:
			case 120:
			case 130:
			case 137: // Lightning arrow
				// Light on ground below the flying effect
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				iDvalue = -5;
				m_pEffectSpr[0]->PutTransSpriteRGB(dX, dY + 30, 1, iDvalue, iDvalue, iDvalue, dwTime);
				break;

			case 69:
			case 70:
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[0]->PutTransSprite25(dX, dY + 30, 1, dwTime);
				break;

			case 33:
				break;

			case 40:
			case 56:
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

			case 52: // Protection Ring
				if (m_pEffectList[i]->m_cFrame >= 0)
				{
					dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
					dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
					m_pEffectSpr[24]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
				}
				break;

			case 57:
				if (m_pEffectList[i]->m_cFrame >= 0) {
					dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
					dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
					m_pEffectSpr[30]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
				}
				break;

			case 73:
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[74]->PutTransSprite(dX, dY - 34, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case 74:
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[75]->PutTransSprite(dX, dY + 35, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case 75: // Icegolem
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[76]->PutTransSprite25(dX + m_pEffectList[i]->m_dX * m_pEffectList[i]->m_cFrame, dY + m_pEffectList[i]->m_dY * m_pEffectList[i]->m_cFrame, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case 76:// Icegolem
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[77]->PutTransSprite25(dX + m_pEffectList[i]->m_dX * m_pEffectList[i]->m_cFrame, dY + m_pEffectList[i]->m_dY * m_pEffectList[i]->m_cFrame, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case 77:// Icegolem
				dX = (m_pEffectList[i]->m_mX) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_mY) - m_pGame->m_sViewPointY;
				m_pEffectSpr[78]->PutTransSprite25(dX + m_pEffectList[i]->m_dX * m_pEffectList[i]->m_cFrame, dY + m_pEffectList[i]->m_dY * m_pEffectList[i]->m_cFrame, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case 150: // Berserk : Cirlcle 6 magic
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				m_pEffectSpr[58]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
				break;

			case 180: // Ilusion
			case 190: // Mass Illusion
				cTempFrame = m_pEffectList[i]->m_cFrame;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				m_pEffectSpr[59]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
				break;

			case 177: // Illusion mvt
			case 195: // Mass Illusion mvt
				cTempFrame = m_pEffectList[i]->m_cFrame;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				m_pEffectSpr[102]->PutTransSprite_NoColorKey(dX, dY + 30, cTempFrame, dwTime);
				break;

			case 183: // Inhibition casting
				cTempFrame = m_pEffectList[i]->m_cFrame;
				dX = (m_pEffectList[i]->m_dX * 32) - m_pGame->m_sViewPointX;
				dY = (m_pEffectList[i]->m_dY * 32) - m_pGame->m_sViewPointY;
				m_pEffectSpr[95]->PutTransSprite_NoColorKey(dX, dY + 40, cTempFrame, dwTime);
				break;
			}
		}
}
