// Effect_Update.cpp: UpdateEffects implementation
//
//////////////////////////////////////////////////////////////////////

#include "EffectManager.h"
#include "Game.h"
#include "Sprite.h"
#include "Effect.h"
#include "GlobalDef.h"
#include "Misc.h"

extern int _iAttackerHeight[];

void EffectManager::UpdateEffectsImpl()
{
	int i, x;
	uint32_t dwTime;

	short sAbsX, sAbsY, sDist;
	char  cDir;
	long lPan;
	dwTime = m_pGame->m_dwCurTime;
	dwTime += m_pGame->m_pMapData->m_dwFrameAdjustTime;
	for (i = 0; i < DEF_MAXEFFECTS; i++)
		if (m_pEffectList[i] != 0) {
			if ((dwTime - m_pEffectList[i]->m_dwTime) > m_pEffectList[i]->m_dwFrameTime)
			{
				m_pEffectList[i]->m_dwTime = dwTime;
				m_pEffectList[i]->m_cFrame++;

				m_pEffectList[i]->m_mX2 = m_pEffectList[i]->m_mX;
				m_pEffectList[i]->m_mY2 = m_pEffectList[i]->m_mY;
				switch (m_pEffectList[i]->m_sType) {
				case 1: // coup normal
					if (m_pEffectList[i]->m_cFrame == 1)
					{
						for (int j = 1; j <= m_pEffectList[i]->m_iV1; j++) AddEffectImpl(11, m_pEffectList[i]->m_mX + 15 - (rand() % 30), m_pEffectList[i]->m_mY + 15 - (rand() % 30), 0, 0, -1 * (rand() % 2), 0);
					}
					if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 2:	// (Arrow missing target ?)
					CMisc::GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
						m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32 - 40,
						&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
						&m_pEffectList[i]->m_iErr, 70);
					if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
						&& (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY * 32 - 40)) <= 2))
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 4: // Gold Drop ,33,69,70
				case 33: //
				case 69:
				case 70:
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 5:
				case 30:
				case 31: // Fire Explosion
				case 252:
					if (m_pEffectList[i]->m_cFrame == 1)
					{
						AddEffectImpl(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2), 0);
						AddEffectImpl(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2), 0);
						AddEffectImpl(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2), 0);
						AddEffectImpl(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2), 0);
						AddEffectImpl(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2), 0);
					}
					if (m_pEffectList[i]->m_cFrame == 7)
					{
						AddEffectImpl(15, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, 0, 0);
						AddEffectImpl(15, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, 0, 0);
						AddEffectImpl(15, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, 0, 0);
					}
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 6: // Lightning Bolt Burst
					if (m_pEffectList[i]->m_cFrame == 1)
					{
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
					}
					if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 7: // Magic Missile Burst
					if (m_pEffectList[i]->m_cFrame == 1)
					{
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
					}
					if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 9:  // Burst Type 2
				case 11: // Burst Type 3
					m_pEffectList[i]->m_mX += m_pEffectList[i]->m_rX;
					m_pEffectList[i]->m_mY += m_pEffectList[i]->m_rY;
					m_pEffectList[i]->m_rY++;
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 10: // Lightning Arrow Burst
					if (m_pEffectList[i]->m_cFrame == 1)
					{
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
					}
					if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 12: // Burst Type 4
					m_pEffectList[i]->m_mX += m_pEffectList[i]->m_rX;
					m_pEffectList[i]->m_mY += m_pEffectList[i]->m_rY;
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 13: // Bulles druncncity
					if (m_pEffectList[i]->m_cFrame < 15)
					{
						if ((rand() % 2) == 0)
							m_pEffectList[i]->m_mX++;
						else m_pEffectList[i]->m_mX--;
						m_pEffectList[i]->m_mY--;
					}
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 16: //
					CMisc::GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
						m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY,
						&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
						&m_pEffectList[i]->m_iErr, 40);
					AddEffectImpl(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, -1 * (rand() % 4));
					if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX) <= 2)
						&& (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY)) <= 2))
					{
						AddEffectImpl(18, m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY, 0, 0, 0, 0); // testcode 0111 18
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
						AddEffectImpl(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 17: // Ice-Storm
					cDir = CMisc::cGetNextMoveDir(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, m_pEffectList[i]->m_mX3, m_pEffectList[i]->m_mY3);
					switch (cDir) {
					case 1:
						m_pEffectList[i]->m_rY -= 2;
						break;
					case 2:
						m_pEffectList[i]->m_rY -= 2;
						m_pEffectList[i]->m_rX += 2;
						break;
					case 3:
						m_pEffectList[i]->m_rX += 2;
						break;
					case 4:
						m_pEffectList[i]->m_rX += 2;
						m_pEffectList[i]->m_rY += 2;
						break;
					case 5:
						m_pEffectList[i]->m_rY += 2;
						break;
					case 6:
						m_pEffectList[i]->m_rX -= 2;
						m_pEffectList[i]->m_rY += 2;
						break;
					case 7:
						m_pEffectList[i]->m_rX -= 2;
						break;
					case 8:
						m_pEffectList[i]->m_rX -= 2;
						m_pEffectList[i]->m_rY -= 2;
						break;
					}
					if (m_pEffectList[i]->m_rX < -10) m_pEffectList[i]->m_rX = -10;
					if (m_pEffectList[i]->m_rX > 10) m_pEffectList[i]->m_rX = 10;
					if (m_pEffectList[i]->m_rY < -10) m_pEffectList[i]->m_rY = -10;
					if (m_pEffectList[i]->m_rY > 10) m_pEffectList[i]->m_rY = 10;
					m_pEffectList[i]->m_mX += m_pEffectList[i]->m_rX;
					m_pEffectList[i]->m_mY += m_pEffectList[i]->m_rY;
					m_pEffectList[i]->m_mY3--;
					if (m_pEffectList[i]->m_cFrame > 10)
					{
						m_pEffectList[i]->m_cFrame = 0;
						if (abs(m_pEffectList[i]->m_sY - m_pEffectList[i]->m_mY3) > 100)
						{
							delete m_pEffectList[i];
							m_pEffectList[i] = 0;
						}
					}
					break;

				case 20: // Critical strike with a weapon
				case 21:
				case 22:
				case 23:
				case 24:
				case 25:
				case 26:
				case 27: // Critical strike with a weapon
					CMisc::GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
						m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32 - 40,
						&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
						&m_pEffectList[i]->m_iErr, 50);
					AddEffectImpl(8, m_pEffectList[i]->m_mX + 10 - (rand() % 20), m_pEffectList[i]->m_mY + 10 - (rand() % 20), 0, 0, 0, 0);//-1*(rand() % 4));
					AddEffectImpl(8, m_pEffectList[i]->m_mX + 10 - (rand() % 20), m_pEffectList[i]->m_mY + 10 - (rand() % 20), 0, 0, 0, 0);//-1*(rand() % 4));
					AddEffectImpl(8, m_pEffectList[i]->m_mX + 10 - (rand() % 20), m_pEffectList[i]->m_mY + 10 - (rand() % 20), 0, 0, 0, 0);//-1*(rand() % 4));
					AddEffectImpl(8, m_pEffectList[i]->m_mX + 10 - (rand() % 20), m_pEffectList[i]->m_mY + 10 - (rand() % 20), 0, 0, 0, 0);//-1*(rand() % 4));
					AddEffectImpl(8, m_pEffectList[i]->m_mX + 10 - (rand() % 20), m_pEffectList[i]->m_mY + 10 - (rand() % 20), 0, 0, 0, 0);//-1*(rand() % 4));
					if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2) &&
						(abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY * 32 - 40)) <= 2))
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 34: //
					CMisc::GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
						m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY,
						&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
						&m_pEffectList[i]->m_iErr, 50);
					AddEffectImpl(33, m_pEffectList[i]->m_mX + (rand() % 30) - 15, m_pEffectList[i]->m_mY + (rand() % 30) - 15, 0, 0, -1 * (rand() % 4));
					if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX) <= 2) &&
						(abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY)) <= 2))
					{
						AddEffectImpl(33, m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY, 0, 0, 0, 0); //7
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;


				case 40:
				case 56:
					if (m_pEffectList[i]->m_cFrame == 9)
					{
						AddEffectImpl(51, m_pEffectList[i]->m_mX + ((rand() % 100) - 50), m_pEffectList[i]->m_mY + ((rand() % 70) - 35), 0, 0, 0, 0);
						AddEffectImpl(51, m_pEffectList[i]->m_mX + ((rand() % 100) - 50), m_pEffectList[i]->m_mY + ((rand() % 70) - 35), 0, 0, 0, 0);
						AddEffectImpl(51, m_pEffectList[i]->m_mX + ((rand() % 100) - 50), m_pEffectList[i]->m_mY + ((rand() % 70) - 35), 0, 0, 0, 0);
						AddEffectImpl(51, m_pEffectList[i]->m_mX + ((rand() % 100) - 50), m_pEffectList[i]->m_mY + ((rand() % 70) - 35), 0, 0, 0, 0);
						AddEffectImpl(51, m_pEffectList[i]->m_mX + ((rand() % 100) - 50), m_pEffectList[i]->m_mY + ((rand() % 70) - 35), 0, 0, 0, 0);
					}
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 41: //Large Type 1, 2, 3, 4
				case 42:
				case 43:
				case 44:
				case 45: // Small Type 1, 2
				case 46:
					if (m_pEffectList[i]->m_cFrame >= 7)
					{
						m_pEffectList[i]->m_mX--;
						m_pEffectList[i]->m_mY += m_pEffectList[i]->m_iV1;
						m_pEffectList[i]->m_iV1++;
					}

					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						if ((m_pEffectList[i]->m_sType != 45) && (m_pEffectList[i]->m_sType != 46))
						{
							AddEffectImpl(50, m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, 0, 0, 0, 0);
							AddEffectImpl(14, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
							AddEffectImpl(14, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
							AddEffectImpl(14, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
							AddEffectImpl(51, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
							AddEffectImpl(51, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
						}
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 47: // Blizzard
				case 48:
				case 49:
					if (m_pEffectList[i]->m_cFrame >= 7)
					{
						m_pEffectList[i]->m_mX--;
						m_pEffectList[i]->m_mY += m_pEffectList[i]->m_iV1;
						m_pEffectList[i]->m_iV1 += 4;
					}
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						if (m_pEffectList[i]->m_sType == 49)
							AddEffectImpl(72, m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, 0, 0, 0, 0);
						else AddEffectImpl(50, m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, 0, 0, 0, 0);
						AddEffectImpl(14, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
						AddEffectImpl(14, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
						AddEffectImpl(14, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);

						AddEffectImpl(51, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
						AddEffectImpl(51, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 60: //
				case 181: // Meteor-Strike
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						AddEffectImpl(61, m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, 0, 0, 0, 0);
						AddEffectImpl(63, m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, 0, 0, 0, 0);
						AddEffectImpl(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2), 0);
						AddEffectImpl(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2), 0);
						AddEffectImpl(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2), 0);
						AddEffectImpl(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2), 0);
						AddEffectImpl(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2), 0);
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					else if (m_pEffectList[i]->m_cFrame >= 0)
					{
						m_pEffectList[i]->m_mX -= 30;
						m_pEffectList[i]->m_mY += 46;
						AddEffectImpl(62, m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, 0, 0, 0, 0);
					}
					break;

				case 62:
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					else if (m_pEffectList[i]->m_cFrame >= 0)
					{
						m_pEffectList[i]->m_mX += (rand() % 3) - 1;
						m_pEffectList[i]->m_mY += (rand() % 3) - 1;
					}
					break;

				case 65: // Building fire after MS (crusade) 65 & 67
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					else if (m_pEffectList[i]->m_cFrame >= 0)
					{
						m_pEffectList[i]->m_mX += (rand() % 3) - 1;
						m_pEffectList[i]->m_mY -= 4 + (rand() % 2);
					}
					break;

				case 66:
				case 203:
				case 204:
				case 205:
				case 206:
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 68:
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					else if (m_pEffectList[i]->m_cFrame == 11)
					{
						m_pGame->SetCameraShakingEffect(m_pEffectList[i]->m_iV1, 2);
					}
					break;

				case 71:
					CMisc::GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
						m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY,
						&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
						&m_pEffectList[i]->m_iErr, 50);
					AddEffectImpl(48, m_pEffectList[i]->m_mX + (rand() % 30) - 15, m_pEffectList[i]->m_mY + (rand() % 30) - 15, 0, 0, 0, 0);
					AddEffectImpl(51, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
					if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX) <= 2) &&
						(abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY)) <= 2))
					{
						AddEffectImpl(49, m_pEffectList[i]->m_mX/* + (rand() % 30) - 15*/, m_pEffectList[i]->m_mY/* + (rand() % 30) - 15*/, 0, 0, 0, 0);
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 81: // Snoopy: Ajout StromBlade
					CMisc::GetPoint(m_pEffectList[i]->m_mX
						, m_pEffectList[i]->m_mY
						, m_pEffectList[i]->m_dX * 32
						, m_pEffectList[i]->m_dY * 32
						, &m_pEffectList[i]->m_mX
						, &m_pEffectList[i]->m_mY
						, &m_pEffectList[i]->m_iErr
						, 10);
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 100: // Magic Missile
					CMisc::GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
						m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32/* - 40*/,
						&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
						&m_pEffectList[i]->m_iErr, 50);
					AddEffectImpl(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, -1 * (rand() % 4));

					if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2) &&
						(abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY * 32/* - 40*/)) <= 2))
					{
						AddEffectImpl(7, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0, 0);
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 110: // Enegy-Bolt
					CMisc::GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
						m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32/* - 40*/,
						&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
						&m_pEffectList[i]->m_iErr, 50);
					AddEffectImpl(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, -1 * (rand() % 4));
					AddEffectImpl(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, -1 * (rand() % 4));
					if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
						&& (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY * 32) <= 2))
					{
						AddEffectImpl(6, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0, 0); // 6 testcode 0111
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 120: // Fire Ball
					CMisc::GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
						m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32/* - 40*/,
						&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
						&m_pEffectList[i]->m_iErr, 50);
					if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
						&& (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY * 32) <= 2))
					{
						AddEffectImpl(5, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0, 0);
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 130: // Fire Strike
					CMisc::GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
						m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32/* - 40*/,
						&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
						&m_pEffectList[i]->m_iErr, 50);
					if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
						&& (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY * 32) <= 2))
					{
						AddEffectImpl(5, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0, 0);
						AddEffectImpl(5, m_pEffectList[i]->m_dX * 32 - 30, m_pEffectList[i]->m_dY * 32 - 15, 0, 0, -7, 0);
						AddEffectImpl(5, m_pEffectList[i]->m_dX * 32 + 35, m_pEffectList[i]->m_dY * 32 - 30, 0, 0, -5, 0);
						AddEffectImpl(5, m_pEffectList[i]->m_dX * 32 + 20, m_pEffectList[i]->m_dY * 32 + 30, 0, 0, -3, 0);
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 137: // Lightning Arrow
					CMisc::GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
						m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32/* - 40*/,
						&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
						&m_pEffectList[i]->m_iErr, 50);
					AddEffectImpl(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, -1 * (rand() % 4));
					AddEffectImpl(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, -1 * (rand() % 4));
					AddEffectImpl(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, -1 * (rand() % 4));
					if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
						&& (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY * 32) <= 2))
					{
						AddEffectImpl(10, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0, 0);
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 143: // Lightning
				case 151: // Lightning-Bolt
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						AddEffectImpl(10, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0, 0);
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					else
					{
						m_pEffectList[i]->m_rX = 5 - (rand() % 10);
						m_pEffectList[i]->m_rY = 5 - (rand() % 10);
					}
					break;

				case 145: // Chill-Wind
					AddEffectImpl(40, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0, 0);
					AddEffectImpl(40, m_pEffectList[i]->m_dX * 32 - 30, m_pEffectList[i]->m_dY * 32 - 15, 0, 0, -10, 0);
					AddEffectImpl(40, m_pEffectList[i]->m_dX * 32 + 35, m_pEffectList[i]->m_dY * 32 - 30, 0, 0, -6, 0);
					AddEffectImpl(40, m_pEffectList[i]->m_dX * 32 + 20, m_pEffectList[i]->m_dY * 32 + 30, 0, 0, -3, 0);
					delete m_pEffectList[i];
					m_pEffectList[i] = 0;
					break;

				case 147:  // Triple-Energy-Bolt
					AddEffectImpl(110, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
						m_pEffectList[i]->m_dX - 1, m_pEffectList[i]->m_dY - 1, 0);
					AddEffectImpl(110, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
						m_pEffectList[i]->m_dX + 1, m_pEffectList[i]->m_dY - 1, 0);
					AddEffectImpl(110, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
						m_pEffectList[i]->m_dX + 1, m_pEffectList[i]->m_dY + 1, 0);
					AddEffectImpl(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, -1 * (rand() % 4));
					lPan = -(((m_pGame->m_sViewPointX / 32) + VIEW_CENTER_TILE_X) - m_pEffectList[i]->m_dX) * LOGICAL_WIDTH;
					m_pGame->PlaySound('E', 1, sDist, lPan);
					AddEffectImpl(7, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0, 0);
					delete m_pEffectList[i];
					m_pEffectList[i] = 0;
					break;

				case 156: // Mass-Lightning-Arrow
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					else
					{
						AddEffectImpl(137, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
							m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY, 0);
						sAbsX = abs(((m_pGame->m_sViewPointX / 32) + VIEW_CENTER_TILE_X) - m_pEffectList[i]->m_dX);
						sAbsY = abs(((m_pGame->m_sViewPointY / 32) + VIEW_CENTER_TILE_Y) - m_pEffectList[i]->m_dY);
						if (sAbsX > sAbsY) sDist = sAbsX;
						else sDist = sAbsY;
						lPan = -(((m_pGame->m_sViewPointX / 32) + VIEW_CENTER_TILE_X) - m_pEffectList[i]->m_dX) * LOGICAL_WIDTH;
						m_pGame->PlaySound('E', 1, sDist, lPan);
					}
					break;

				case 157: // Ice-Strike
					AddEffectImpl(41, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0, 0);
					for (x = 0; x < 14; x++)
					{
						AddEffectImpl(41 + (rand() % 3), m_pEffectList[i]->m_dX * 32 + (rand() % 100) - 50 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 90) - 45, 0, 0, -1 * x - 1);
					}
					for (x = 0; x < 6; x++)
					{
						AddEffectImpl(45 + (rand() % 2), m_pEffectList[i]->m_dX * 32 + (rand() % 100) - 50 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 90) - 45, 0, 0, -1 * x - 1 - 10);
					}
					delete m_pEffectList[i];
					m_pEffectList[i] = 0;
					break;

				case 160: // Energy-Strike
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					else
					{
						AddEffectImpl(16, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
							m_pEffectList[i]->m_dX * 32 + 50 - (rand() % 100), m_pEffectList[i]->m_dY * 32 + 50 - (rand() % 100), 0);
						sAbsX = abs(((m_pGame->m_sViewPointX / 32) + VIEW_CENTER_TILE_X) - m_pEffectList[i]->m_dX);
						sAbsY = abs(((m_pGame->m_sViewPointY / 32) + VIEW_CENTER_TILE_Y) - m_pEffectList[i]->m_dY);
						if (sAbsX > sAbsY) sDist = sAbsX;
						else sDist = sAbsY;
						lPan = -(((m_pGame->m_sViewPointX / 32) + VIEW_CENTER_TILE_X) - m_pEffectList[i]->m_dX);
						m_pGame->PlaySound('E', 1, sDist, lPan);
					}
					break;

				case 161: // Mass-Fire-Strike
					CMisc::GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
						m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32/* - 40*/,
						&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
						&m_pEffectList[i]->m_iErr, 50);
					if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
						&& (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY * 32) <= 2))
					{
						AddEffectImpl(30, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0, 0);
						AddEffectImpl(31, m_pEffectList[i]->m_dX * 32 - 30, m_pEffectList[i]->m_dY * 32 - 15, 0, 0, -7, 0);
						AddEffectImpl(31, m_pEffectList[i]->m_dX * 32 + 35, m_pEffectList[i]->m_dY * 32 - 30, 0, 0, -5, 0);
						AddEffectImpl(31, m_pEffectList[i]->m_dX * 32 + 20, m_pEffectList[i]->m_dY * 32 + 30, 0, 0, -3, 0);
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 163: // Mass-Chill-Wind Chill-Wind
					AddEffectImpl(56, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0, 0);
					AddEffectImpl(56, m_pEffectList[i]->m_dX * 32 - 30, m_pEffectList[i]->m_dY * 32 - 15, 0, 0, -10, 0);
					AddEffectImpl(56, m_pEffectList[i]->m_dX * 32 + 35, m_pEffectList[i]->m_dY * 32 - 30, 0, 0, -6, 0);
					AddEffectImpl(56, m_pEffectList[i]->m_dX * 32 + 20, m_pEffectList[i]->m_dY * 32 + 30, 0, 0, -3, 0);
					AddEffectImpl(56, m_pEffectList[i]->m_dX * 32 + (rand() % 100) - 50, m_pEffectList[i]->m_dY * 32 + (rand() % 70) - 35, 0, 0, -1 * (rand() % 10));
					AddEffectImpl(56, m_pEffectList[i]->m_dX * 32 + (rand() % 100) - 50, m_pEffectList[i]->m_dY * 32 + (rand() % 70) - 35, 0, 0, -1 * (rand() % 10));
					AddEffectImpl(56, m_pEffectList[i]->m_dX * 32 + (rand() % 100) - 50, m_pEffectList[i]->m_dY * 32 + (rand() % 70) - 35, 0, 0, -1 * (rand() % 10));
					AddEffectImpl(56, m_pEffectList[i]->m_dX * 32 + (rand() % 100) - 50, m_pEffectList[i]->m_dY * 32 + (rand() % 70) - 35, 0, 0, -1 * (rand() % 10));
					delete m_pEffectList[i];
					m_pEffectList[i] = 0;
					break;

				case 164: // worm-bite
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						AddEffectImpl(68, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0, 0); // testcode 0111 18
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 170: // Bloody-Shock-Wave
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					else if ((m_pEffectList[i]->m_cFrame % 2) == 0)
					{
						AddEffectImpl(34, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
							m_pEffectList[i]->m_dX * 32 + 30 - (rand() % 60), m_pEffectList[i]->m_dY * 32 + 30 - (rand() % 60), 0);
						sAbsX = abs(((m_pGame->m_sViewPointX / 32) + VIEW_CENTER_TILE_X) - m_pEffectList[i]->m_dX);
						sAbsY = abs(((m_pGame->m_sViewPointY / 32) + VIEW_CENTER_TILE_Y) - m_pEffectList[i]->m_dY);
						if (sAbsX > sAbsY) sDist = sAbsX;
						else sDist = sAbsY;
						lPan = -(((m_pGame->m_sViewPointX / 32) + VIEW_CENTER_TILE_X) - m_pEffectList[i]->m_dX);
						m_pGame->PlaySound('E', 1, sDist, lPan);
					}
					break;

				case 172: // Mass-Ice-Strike
					AddEffectImpl(44, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0, 0);
					AddEffectImpl(44, m_pEffectList[i]->m_dX * 32 + (rand() % 110) - 55 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 100) - 50, 0, 0, -1 * (rand() % 3));
					AddEffectImpl(44, m_pEffectList[i]->m_dX * 32 + (rand() % 110) - 55 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 100) - 50, 0, 0, -1 * (rand() % 3));
					AddEffectImpl(44, m_pEffectList[i]->m_dX * 32 + (rand() % 110) - 55 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 100) - 50, 0, 0, -1 * (rand() % 3));
					AddEffectImpl(44, m_pEffectList[i]->m_dX * 32 + (rand() % 110) - 55 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 100) - 50, 0, 0, -1 * (rand() % 3));
					AddEffectImpl(44, m_pEffectList[i]->m_dX * 32 + (rand() % 110) - 55 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 100) - 50, 0, 0, -1 * (rand() % 3));
					AddEffectImpl(44, m_pEffectList[i]->m_dX * 32 + (rand() % 110) - 55 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 100) - 50, 0, 0, -1 * (rand() % 3));
					AddEffectImpl(44, m_pEffectList[i]->m_dX * 32 + (rand() % 110) - 55 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 100) - 50, 0, 0, -1 * (rand() % 3));
					AddEffectImpl(44, m_pEffectList[i]->m_dX * 32 + (rand() % 110) - 55 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 100) - 50, 0, 0, -1 * (rand() % 3));
					for (x = 0; x < 16; x++)
					{
						AddEffectImpl(44, m_pEffectList[i]->m_dX * 32 + (rand() % 110) - 55 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 100) - 50, 0, 0, -1 * x - 1, 0);
					}
					for (x = 0; x < 8; x++)
					{
						AddEffectImpl(45 + (rand() % 2), m_pEffectList[i]->m_dX * 32 + (rand() % 100) - 50 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 90) - 45, 0, 0, -1 * x - 1 - 10);
					}
					delete m_pEffectList[i];
					m_pEffectList[i] = 0;
					break;

				case 174: // Lightning-Strike
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					else
					{
						AddEffectImpl(151, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
							m_pEffectList[i]->m_dX + (rand() % 3) - 1, m_pEffectList[i]->m_dY + (rand() % 3) - 1, 0);
						sAbsX = abs(((m_pGame->m_sViewPointX / 32) + VIEW_CENTER_TILE_X) - m_pEffectList[i]->m_dX);
						sAbsY = abs(((m_pGame->m_sViewPointY / 32) + VIEW_CENTER_TILE_Y) - m_pEffectList[i]->m_dY);
						if (sAbsX > sAbsY) sDist = sAbsX;
						else sDist = sAbsY;
						lPan = -(((m_pGame->m_sViewPointX / 32) + VIEW_CENTER_TILE_X) - m_pEffectList[i]->m_dX);
						m_pGame->PlaySound('E', 1, sDist, lPan);
					}
					break;

				case 182: // Mass-Magic-Missile
					CMisc::GetPoint(m_pEffectList[i]->m_mX
						, m_pEffectList[i]->m_mY
						, m_pEffectList[i]->m_dX * 32
						, m_pEffectList[i]->m_dY * 32
						, &m_pEffectList[i]->m_mX
						, &m_pEffectList[i]->m_mY
						, &m_pEffectList[i]->m_iErr
						, 50);
					AddEffectImpl(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, -1 * (rand() % 4));
					if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
						&& (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY * 32) <= 2))
					{	// JLE 0043132A
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					else
					{
						AddEffectImpl(35, m_pEffectList[i]->m_dX * 32 + 22, m_pEffectList[i]->m_dY * 32 - 15, 0, 0, -7, 1);
						AddEffectImpl(36, m_pEffectList[i]->m_dX * 32 - 22, m_pEffectList[i]->m_dY * 32 - 7, 0, 0, -7, 1);
						AddEffectImpl(36, m_pEffectList[i]->m_dX * 32 + 30, m_pEffectList[i]->m_dY * 32 - 22, 0, 0, -5, 1);
						AddEffectImpl(36, m_pEffectList[i]->m_dX * 32 + 12, m_pEffectList[i]->m_dY * 32 + 22, 0, 0, -3, 1);
					}
					break;

				case 191: // Blizzard
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					else /*if (m_pEffectList[i]->m_cFrame == 1)*/
					{
						AddEffectImpl(71, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
							m_pEffectList[i]->m_dX * 32 + (rand() % 120) - 60, m_pEffectList[i]->m_dY * 32 + (rand() % 120) - 60, 0);
						sAbsX = abs(((m_pGame->m_sViewPointX / 32) + VIEW_CENTER_TILE_X) - m_pEffectList[i]->m_dX);
						sAbsY = abs(((m_pGame->m_sViewPointY / 32) + VIEW_CENTER_TILE_Y) - m_pEffectList[i]->m_dY);
						if (sAbsX > sAbsY) sDist = sAbsX;
						else sDist = sAbsY;
						lPan = -(((m_pGame->m_sViewPointX / 32) + VIEW_CENTER_TILE_X) - m_pEffectList[i]->m_dX);
						m_pGame->PlaySound('E', 1, sDist, lPan);
					}
					break;

				case 196: // Earth-Shock-Wave
					CMisc::GetPoint(m_pEffectList[i]->m_mX
						, m_pEffectList[i]->m_mY
						, m_pEffectList[i]->m_dX * 32
						, m_pEffectList[i]->m_dY * 32
						, &m_pEffectList[i]->m_mX
						, &m_pEffectList[i]->m_mY
						, &m_pEffectList[i]->m_iErr
						, 40);
					AddEffectImpl(80, m_pEffectList[i]->m_mX + (rand() % 30) - 15, m_pEffectList[i]->m_mY + (rand() % 30) - 15, 0, 0, 0, 1);
					AddEffectImpl(80, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, 0, 0);
					if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					else
					{
						sAbsX = abs(((m_pGame->m_sViewPointX / 32) + VIEW_CENTER_TILE_X) - m_pEffectList[i]->m_dX);
						sAbsY = abs(((m_pGame->m_sViewPointY / 32) + VIEW_CENTER_TILE_Y) - m_pEffectList[i]->m_dY);
						if (sAbsX > sAbsY) sDist = sAbsX - 10;
						else sDist = sAbsY - 10;
						lPan = -(((m_pGame->m_sViewPointX / 32) + VIEW_CENTER_TILE_X) - m_pEffectList[i]->m_dX);
						m_pGame->PlaySound('E', 1, sDist, lPan);
					}
					break;

				case 200:
					if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					else
					{
						AddEffectImpl(203, m_pEffectList[i]->m_sX + 40, m_pEffectList[i]->m_sY + 120, 0, 0, 0, 0);
						AddEffectImpl(204, m_pEffectList[i]->m_sX - 10, m_pEffectList[i]->m_sY + 70, 0, 0, 0, 0);
						AddEffectImpl(205, m_pEffectList[i]->m_sX - 10, m_pEffectList[i]->m_sY + 75, 0, 0, 0, 0);
						AddEffectImpl(206, m_pEffectList[i]->m_sX - 7, m_pEffectList[i]->m_sY + 27, 0, 0, 0, 0);
						AddEffectImpl(201, (rand() % 160) + 320, (rand() % 120) + 240, 0, 0, 0, 1);
						AddEffectImpl(202, (rand() % 160) + 320, (rand() % 120) + 240, 0, 0, 0, 1);
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 201:
					if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					else
					{
						AddEffectImpl(203, m_pEffectList[i]->m_sX + 110, m_pEffectList[i]->m_sY + 120, 0, 0, 0, 0);
						AddEffectImpl(204, m_pEffectList[i]->m_sX - 10, m_pEffectList[i]->m_sY + 70, 0, 0, 0, 0);
						AddEffectImpl(205, m_pEffectList[i]->m_sX - 10, m_pEffectList[i]->m_sY + 75, 0, 0, 0, 0);
						AddEffectImpl(202, (rand() % 160) + 320, (rand() % 120) + 240, 0, 0, 0, 1);
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 202:
					if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					else
					{
						AddEffectImpl(203, m_pEffectList[i]->m_sX + 65, m_pEffectList[i]->m_sY + 120, 0, 0, 0, 0);
						AddEffectImpl(204, m_pEffectList[i]->m_sX - 10, m_pEffectList[i]->m_sY + 70, 0, 0, 0, 0);
						AddEffectImpl(205, m_pEffectList[i]->m_sX - 10, m_pEffectList[i]->m_sY + 75, 0, 0, 0, 0);
						AddEffectImpl(206, m_pEffectList[i]->m_sX - 7, m_pEffectList[i]->m_sY + 27, 0, 0, 0, 0);
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 250: // Gate round
					CMisc::GetPoint(m_pEffectList[i]->m_mX
						, m_pEffectList[i]->m_mY
						, m_pEffectList[i]->m_dX * 32
						, m_pEffectList[i]->m_dY * 32 - 40
						, &m_pEffectList[i]->m_mX
						, &m_pEffectList[i]->m_mY
						, &m_pEffectList[i]->m_iErr
						, 10);
					if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
						&& (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY * 32 - 40)) <= 2))
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 251: // Salmon burst (effect11s)
					CMisc::GetPoint(m_pEffectList[i]->m_mX
						, m_pEffectList[i]->m_mY
						, m_pEffectList[i]->m_dX * 32
						, m_pEffectList[i]->m_dY * 32
						, &m_pEffectList[i]->m_mX
						, &m_pEffectList[i]->m_mY
						, &m_pEffectList[i]->m_iErr
						, 50);
					if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
						&& (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY * 32 - 40)) <= 2))
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					else
					{
						AddEffectImpl(252, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0, 1);
						AddEffectImpl(252, m_pEffectList[i]->m_dX * 32 - 30, m_pEffectList[i]->m_dY * 32 - 15, 0, 0, -7, 1);
						AddEffectImpl(252, m_pEffectList[i]->m_dX * 32 - 35, m_pEffectList[i]->m_dY * 32 - 30, 0, 0, -5, 1);
						AddEffectImpl(252, m_pEffectList[i]->m_dX * 32 + 20, m_pEffectList[i]->m_dY * 32 + 30, 0, 0, -3, 1);
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;

				case 8:
				case 14:
				case 15:
				case 18:
				case 32:
				case 35: //
				case 36: //
				case 50:
				case 51:
				case 52:
				case 53:
				case 54:
				case 55:
				case 57:
				case 61:
				case 63:
				case 64:
				case 67:
				case 72:
				case 73:
				case 74:
				case 75:
				case 76:
				case 77:
				case 80: //
				case 82: //

				case 101:
				case 102:
				case 111:
				case 112:
				case 113:
				case 121:
				case 122:
				case 123: // Stamina Rec
				case 124:
				case 125:
				case 126:
				case 127:
				case 128: // Gr Stamina Rec
				case 131:
				case 132:
				case 133:
				case 134:
				case 135:
				case 136:
				case 142:
				case 144:
				case 150: // Berserk : Cirlcle 6 magic
				case 152: // Polymorph
				case 153:
				case 162:
				case 165:
				case 166:
				case 171:
				case 176: //
				case 177: //

				case 180:
				case 183: //
				case 184: // EP's Magic Drain
				case 190:
				case 192:
				case 193:
				case 194:
				case 195:
				case 242: // Mage hero effect
				case 243: // War hero effect
				case 244: // Snoopy: d�plac� pour nvx sorts: Aura du casteur de Mass MagicMissile
					if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
					{
						delete m_pEffectList[i];
						m_pEffectList[i] = 0;
					}
					break;
				}
			}
		}

}
