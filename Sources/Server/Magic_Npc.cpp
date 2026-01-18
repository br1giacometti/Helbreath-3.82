// Magic_Npc.cpp: NPC magic handling implementation
//
// Contains MagicManager::HandleNpcMagicImpl()
// Extracted from CEntityManager::NpcMagicHandler()
//
//////////////////////////////////////////////////////////////////////

#include "MagicManager.h"
#include "Game.h"
#include "Map.h"
#include "Npc.h"
#include "Client.h"
#include "Magic.h"
#include "Misc.h"

void MagicManager::HandleNpcMagicImpl(int iNpcH, short dX, short dY, short sType)
{
	short  sOwnerH;
	char   cOwnerType;
	int i, iErr, ix, iy, sX, sY, tX, tY, iResult, iWhetherBonus, iMagicAttr;
	uint32_t  dwTime = GameClock::GetTimeMS();

	// Access NPC and Map lists through game pointer
	CNpc** m_pNpcList = m_pGame->m_pNpcList;
	CMap** m_pMapList = m_pGame->m_pMapList;

	if (m_pNpcList[iNpcH] == 0) return;
	if ((dX < 0) || (dX >= m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_sSizeX) ||
		(dY < 0) || (dY >= m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_sSizeY)) return;

	if ((sType < 0) || (sType >= 100))     return;
	if (m_pGame->m_pMagicConfigList[sType] == 0) return;

	if (m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_bIsAttackEnabled == false) return;

	iResult = m_pNpcList[iNpcH]->m_iMagicHitRatio;

	iWhetherBonus = m_pGame->iGetWhetherMagicBonusEffect(sType, m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_cWhetherStatus);

	iMagicAttr = m_pGame->m_pMagicConfigList[sType]->m_iAttribute;

	if (m_pGame->m_pMagicConfigList[sType]->m_dwDelayTime == 0) {
		switch (m_pGame->m_pMagicConfigList[sType]->m_sType) {
		case DEF_MAGICTYPE_INVISIBILITY:
			switch (m_pGame->m_pMagicConfigList[sType]->m_sValue4) {
			case 1:
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);

				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pGame->m_pClientList[sOwnerH] == 0) goto NMH_NOEFFECT;
					if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) goto NMH_NOEFFECT;
					m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
					m_pGame->SetInvisibilityFlag(sOwnerH, cOwnerType, true);
					m_pGame->RemoveFromTarget(sOwnerH, DEF_OWNERTYPE_PLAYER);
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) goto NMH_NOEFFECT;
					if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) goto NMH_NOEFFECT;
					m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
					m_pGame->SetInvisibilityFlag(sOwnerH, cOwnerType, true);
					m_pGame->RemoveFromTarget(sOwnerH, DEF_OWNERTYPE_NPC);
					break;
				}

				m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_INVISIBILITY, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000),
					sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				if (cOwnerType == DEF_OWNERTYPE_PLAYER)
					m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_INVISIBILITY, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);
				break;

			case 2:
				for (ix = dX - 8; ix <= dX + 8; ix++)
					for (iy = dY - 8; iy <= dY + 8; iy++) {
						m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
						if (sOwnerH != 0) {
							switch (cOwnerType) {
							case DEF_OWNERTYPE_PLAYER:
								if (m_pGame->m_pClientList[sOwnerH] == 0) goto NMH_NOEFFECT;
								if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) {
									if (m_pGame->m_pClientList[sOwnerH]->m_sType != 66) {
										m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = 0;
										m_pGame->SetInvisibilityFlag(sOwnerH, cOwnerType, false);
										m_pGame->bRemoveFromDelayEventList(sOwnerH, cOwnerType, DEF_MAGICTYPE_INVISIBILITY);
									}
								}
								break;

							case DEF_OWNERTYPE_NPC:
								if (m_pNpcList[sOwnerH] == 0) goto NMH_NOEFFECT;
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) {
									if (m_pGame->m_pClientList[sOwnerH]->m_sType != 66) {
										m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = 0;
										m_pGame->SetInvisibilityFlag(sOwnerH, cOwnerType, false);
										m_pGame->bRemoveFromDelayEventList(sOwnerH, cOwnerType, DEF_MAGICTYPE_INVISIBILITY);
									}
								}
								break;
							}
						}
					}
				break;
			}
			break;

		case DEF_MAGICTYPE_HOLDOBJECT:
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {

				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pGame->m_pClientList[sOwnerH] == 0) goto NMH_NOEFFECT;
					if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0) goto NMH_NOEFFECT;
					if (m_pGame->m_pClientList[sOwnerH]->m_iAddPR >= 500) goto NMH_NOEFFECT;
					m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) goto NMH_NOEFFECT;
					if (m_pNpcList[sOwnerH]->m_cMagicLevel >= 6) goto NMH_NOEFFECT;
					if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0) goto NMH_NOEFFECT;
					m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
					break;
				}

				m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_HOLDOBJECT, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000),
					sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				if (cOwnerType == DEF_OWNERTYPE_PLAYER)
					m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_HOLDOBJECT, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);
			}
			break;


		case DEF_MAGICTYPE_DAMAGE_LINEAR:
			sX = m_pNpcList[iNpcH]->m_sX;
			sY = m_pNpcList[iNpcH]->m_sY;

			for (i = 2; i < 10; i++) {
				iErr = 0;
				CMisc::GetPoint2(sX, sY, dX, dY, &tX, &tY, &iErr, i);

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY);
				if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				if ((abs(tX - dX) <= 1) && (abs(tY - dY) <= 1)) break;
			}

			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
						(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
						if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
							m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					}
				}

			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);

			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
				(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
				if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);
			}
			break;

		case DEF_MAGICTYPE_DAMAGE_SPOT:
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);

			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
				(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
				if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
			}
			break;

		case DEF_MAGICTYPE_HPUP_SPOT:
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			m_pGame->Effect_HpUp_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6);
			break;

		case DEF_MAGICTYPE_DAMAGE_AREA:
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);

			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
				(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
				if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
			}

			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
						(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
						if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
							m_pGame->Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					}
				}
			break;

		case DEF_MAGICTYPE_DAMAGE_AREA_NOSPOT:
			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
						(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
						if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
							m_pGame->Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					}
				}
			break;

		case DEF_MAGICTYPE_SPDOWN_AREA:
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				m_pGame->Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6);
			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
				}
			break;

		case DEF_MAGICTYPE_SPUP_AREA:
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			m_pGame->Effect_SpUp_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6);
			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					m_pGame->Effect_SpUp_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
				}
			break;

		}
	}
	else {
		// Casting with delay - not implemented for NPCs
	}

NMH_NOEFFECT:

	m_pNpcList[iNpcH]->m_iMana -= m_pGame->m_pMagicConfigList[sType]->m_sValue1;
	if (m_pNpcList[iNpcH]->m_iMana < 0)
		m_pNpcList[iNpcH]->m_iMana = 0;

	m_pGame->SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pNpcList[iNpcH]->m_cMapIndex,
		m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY, dX, dY, (sType + 100), m_pNpcList[iNpcH]->m_sType);
}
