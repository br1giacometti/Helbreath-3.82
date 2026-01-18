// Magic_Player.cpp: Player magic handling implementation
//
// Contains MagicManager::HandlePlayerMagicImpl()
// Full implementation migrated from CGame::PlayerMagicHandler()
//
//////////////////////////////////////////////////////////////////////

#include "MagicManager.h"
#include "Game.h"
#include "EntityManager.h"

extern char G_cTxt[512];
extern void PutHackLogFileList(char* cStr);

// These arrays are local to this translation unit (avoid duplicate symbols with Game.cpp)
static int  _tmp_iMCProb[] = { 0, 300, 250, 200, 150, 100, 80, 70, 60, 50, 40 };
static int  _tmp_iMLevelPenalty[] = { 0,   5,   5,   8,   8,  10, 14, 28, 32, 36, 40 };

void MagicManager::HandlePlayerMagicImpl(int iClientH, int dX, int dY, short sType, bool bItemEffect, int iV1)
{
	short sX, sY, sOwnerH, sMagicCircle, rx, ry, sLevelMagic, sTemp;
	char cDir, cOwnerType, cName[11], cItemName[21], cNpcWaypoint[11], cName_Master[11], cNpcName[21], cRemainItemColor, cScanMessage[256];
	double dV1, dV2, dV3, dV4;
	int    i, iErr, iRet, ix, iy, iResult, iDiceRes, iNamingValue, iFollowersNum, iEraseReq, iWhetherBonus;
	int    tX, tY, iManaCost, iMagicAttr;
	class  CItem* pItem;
	uint32_t dwTime;
	uint16_t wWeaponType;
	short sEqStatus;
	int iMapSide = 0;
	short sIDNum;
	uint32_t dwAttr;

	dwTime = GameClock::GetTimeMS();
	m_pGame->m_pClientList[iClientH]->m_bMagicConfirm = true;

	if (m_pGame->m_pClientList[iClientH] == 0) return;
	if (m_pGame->m_pClientList[iClientH]->m_bIsInitComplete == false) return;

	if ((dX < 0) || (dX >= m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->m_sSizeX) ||
		(dY < 0) || (dY >= m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->m_sSizeY)) return;

	if (((dwTime - m_pGame->m_pClientList[iClientH]->m_dwRecentAttackTime) < 1000) && (bItemEffect == 0)) {
		try
		{
			std::snprintf(G_cTxt, sizeof(G_cTxt), "3.51 Detection: (%s) Player: (%s) - Magic casting speed is too fast! Hack?", m_pGame->m_pClientList[iClientH]->m_cIPaddress, m_pGame->m_pClientList[iClientH]->m_cCharName);
			PutHackLogFileList(G_cTxt);
			m_pGame->DeleteClient(iClientH, true, true);
		}
		catch (...)
		{
		}
		return;
	}
	m_pGame->m_pClientList[iClientH]->m_dwRecentAttackTime = dwTime;
	m_pGame->m_pClientList[iClientH]->m_dwLastActionTime = dwTime;

	if (m_pGame->m_pClientList[iClientH]->m_cMapIndex < 0) return;
	if (m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex] == 0) return;

	if ((sType < 0) || (sType >= 100))     return;
	if (m_pGame->m_pMagicConfigList[sType] == 0) return;

	if ((bItemEffect == false) && (m_pGame->m_pClientList[iClientH]->m_cMagicMastery[sType] != 1)) return;

	if ((m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->m_bIsAttackEnabled == false) && (m_pGame->m_pClientList[iClientH]->m_iAdminUserLevel == 0)) return;
	//if ((var_874 ) && (m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->m_bIsHeldenianMap ) && (m_pGame->m_pMagicConfigList[sType]->m_sType != 8)) return;

	if (((m_pGame->m_pClientList[iClientH]->m_iStatus & 0x100000) != 0) && (bItemEffect != true)) {
		m_pGame->SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, 0, -1, 0);
		return;
	}

	if (m_pGame->m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND] != -1) {
		wWeaponType = ((m_pGame->m_pClientList[iClientH]->m_sAppr2 & 0x0FF0) >> 4);
		if ((wWeaponType >= 34) && (wWeaponType <= 39)) {
		}
		else return;
	}

	if ((m_pGame->m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_LHAND] != -1) ||
		(m_pGame->m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND] != -1)) return;

	if ((m_pGame->m_pClientList[iClientH]->m_iSpellCount > 1) && (bItemEffect == false)) {
		try
		{
			std::snprintf(G_cTxt, sizeof(G_cTxt), "TSearch Spell Hack: (%s) Player: (%s) - casting magic without precasting.", m_pGame->m_pClientList[iClientH]->m_cIPaddress, m_pGame->m_pClientList[iClientH]->m_cCharName);
			PutHackLogFileList(G_cTxt);
			m_pGame->DeleteClient(iClientH, true, true);
		}
		catch (...)
		{
		}
		return;
	}

	if (m_pGame->m_pClientList[iClientH]->m_bInhibition) {
		m_pGame->SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, 0, -1, 0);
		return;
	}

	/*if (((m_pGame->m_pClientList[iClientH]->m_iUninteruptibleCheck - (m_pGame->iGetMaxHP(iClientH)/10)) > (m_pGame->m_pClientList[iClientH]->m_iHP)) && (m_pGame->m_pClientList[iClientH]->m_bMagicItem == false)) {
		m_pGame->SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, 0,
			0, 0, 0, 0, 0, 0);
		return;
	}*/

	if (m_pGame->m_pMagicConfigList[sType]->m_sType == 32) { // Invisiblity
		sEqStatus = m_pGame->m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];
		if ((sEqStatus != -1) && (m_pGame->m_pClientList[iClientH]->m_pItemList[sEqStatus] != 0)) {
			if ((m_pGame->m_pClientList[iClientH]->m_pItemList[sEqStatus]->m_sIDnum == 865) || (m_pGame->m_pClientList[iClientH]->m_pItemList[sEqStatus]->m_sIDnum == 866)) {
				bItemEffect = true;
			}
		}
	}

	sX = m_pGame->m_pClientList[iClientH]->m_sX;
	sY = m_pGame->m_pClientList[iClientH]->m_sY;

	sMagicCircle = (sType / 10) + 1;
	if (m_pGame->m_pClientList[iClientH]->m_cSkillMastery[4] == 0)
		dV1 = 1.0f;
	else dV1 = (double)m_pGame->m_pClientList[iClientH]->m_cSkillMastery[4];

	if (bItemEffect) dV1 = (double)100.0f;
	dV2 = (double)(dV1 / 100.0f);
	dV3 = (double)_tmp_iMCProb[sMagicCircle];
	dV1 = dV2 * dV3;
	iResult = (int)dV1;

	if ((m_pGame->m_pClientList[iClientH]->m_iInt + m_pGame->m_pClientList[iClientH]->m_iAngelicInt) > 50)
		iResult += ((m_pGame->m_pClientList[iClientH]->m_iInt + m_pGame->m_pClientList[iClientH]->m_iAngelicInt) - 50) / 2;

	sLevelMagic = (m_pGame->m_pClientList[iClientH]->m_iLevel / 10);
	if (sMagicCircle != sLevelMagic) {
		if (sMagicCircle > sLevelMagic) {
			dV1 = (double)(m_pGame->m_pClientList[iClientH]->m_iLevel - sLevelMagic * 10);
			dV2 = (double)abs(sMagicCircle - sLevelMagic) * _tmp_iMLevelPenalty[sMagicCircle];
			dV3 = (double)abs(sMagicCircle - sLevelMagic) * 10;
			dV4 = (dV1 / dV3) * dV2;
			iResult -= abs(abs(sMagicCircle - sLevelMagic) * _tmp_iMLevelPenalty[sMagicCircle] - (int)dV4);
		}
		else {
			iResult += 5 * abs(sMagicCircle - sLevelMagic);
		}
	}

	switch (m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->m_cWhetherStatus) {
	case 0: break;
	case 1: iResult = iResult - (iResult / 24); break;
	case 2:	iResult = iResult - (iResult / 12); break;
	case 3: iResult = iResult - (iResult / 5);  break;
	}

	if (m_pGame->m_pClientList[iClientH]->m_iSpecialWeaponEffectType == 10) {
		dV1 = (double)iResult;
		dV2 = (double)(m_pGame->m_pClientList[iClientH]->m_iSpecialWeaponEffectValue * 3);
		dV3 = dV1 + dV2;
		iResult = (int)dV3;
	}

	if (iResult <= 0) iResult = 1;

	iWhetherBonus = m_pGame->iGetWhetherMagicBonusEffect(sType, m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->m_cWhetherStatus);

	iManaCost = m_pGame->m_pMagicConfigList[sType]->m_sValue1;
	if ((m_pGame->m_pClientList[iClientH]->m_bIsSafeAttackMode) &&
		(m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->m_bIsFightZone == false)) {
		iManaCost += (iManaCost / 2) - (iManaCost / 10);
	}

	if (m_pGame->m_pClientList[iClientH]->m_iManaSaveRatio > 0) {
		dV1 = (double)m_pGame->m_pClientList[iClientH]->m_iManaSaveRatio;
		dV2 = (double)(dV1 / 100.0f);
		dV3 = (double)iManaCost;
		dV1 = dV2 * dV3;
		dV2 = dV3 - dV1;
		iManaCost = (int)dV2;

		if (iManaCost <= 0) iManaCost = 1;
	}

	wWeaponType = ((m_pGame->m_pClientList[iClientH]->m_sAppr2 & 0x0FF0) >> 4);
	if (wWeaponType == 34) {
		iManaCost += 20;
	}

	if (iResult < 100) {
		iDiceRes = m_pGame->iDice(1, 100);
		if (iResult < iDiceRes) {
			m_pGame->SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, 0, -1, 0);
			return;
		}
	}

	if (((m_pGame->m_pClientList[iClientH]->m_iHungerStatus <= 10) || (m_pGame->m_pClientList[iClientH]->m_iSP <= 0)) && (m_pGame->iDice(1, 1000) <= 100)) {
		m_pGame->SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, 0, -1, 0);
		return;
	}

	if (m_pGame->m_pClientList[iClientH]->m_iMP < iManaCost) {
		return;
	}

	iResult = m_pGame->m_pClientList[iClientH]->m_cSkillMastery[4];
	if ((m_pGame->m_pClientList[iClientH]->m_iMag + m_pGame->m_pClientList[iClientH]->m_iAngelicMag) > 50) iResult += ((m_pGame->m_pClientList[iClientH]->m_iMag + m_pGame->m_pClientList[iClientH]->m_iAngelicMag) - 50);

	sLevelMagic = (m_pGame->m_pClientList[iClientH]->m_iLevel / 10);
	if (sMagicCircle != sLevelMagic) {
		if (sMagicCircle > sLevelMagic) {
			dV1 = (double)(m_pGame->m_pClientList[iClientH]->m_iLevel - sLevelMagic * 10);
			dV2 = (double)abs(sMagicCircle - sLevelMagic) * _tmp_iMLevelPenalty[sMagicCircle];
			dV3 = (double)abs(sMagicCircle - sLevelMagic) * 10;
			dV4 = (dV1 / dV3) * dV2;

			iResult -= abs(abs(sMagicCircle - sLevelMagic) * _tmp_iMLevelPenalty[sMagicCircle] - (int)dV4);
		}
		else {
			iResult += 5 * abs(sMagicCircle - sLevelMagic);
		}
	}

	iResult += m_pGame->m_pClientList[iClientH]->m_iAddAR;
	if (iResult <= 0) iResult = 1;

	if (sType >= 80) iResult += 10000;

	if (m_pGame->m_pMagicConfigList[sType]->m_sType == 28) {
		iResult += 10000;
	}

	if (m_pGame->m_pMagicConfigList[sType]->m_cCategory == 1) {
		if (m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->iGetAttribute(sX, sY, 0x00000005) != 0) return;
	}

	iMagicAttr = m_pGame->m_pMagicConfigList[sType]->m_iAttribute;
	if ((m_pGame->m_pClientList[iClientH]->m_iStatus & 0x10) != 0) {
		m_pGame->SetInvisibilityFlag(iClientH, DEF_OWNERTYPE_PLAYER, false);
		m_pGame->bRemoveFromDelayEventList(iClientH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_INVISIBILITY);
		m_pGame->m_pClientList[iClientH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = 0;
	}

	m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
	if ((m_pGame->m_bIsCrusadeMode == false) && (cOwnerType == DEF_OWNERTYPE_PLAYER)) {
		if ((m_pGame->m_pClientList[iClientH]->m_bIsPlayerCivil != true) && (m_pGame->m_pClientList[sOwnerH]->m_bIsPlayerCivil)) {
			if (m_pGame->m_pClientList[iClientH]->m_cSide != m_pGame->m_pClientList[sOwnerH]->m_cSide) return;
		}
		else if ((m_pGame->m_pClientList[iClientH]->m_bIsPlayerCivil) && (m_pGame->m_pClientList[sOwnerH]->m_bIsPlayerCivil == false)) {
			switch (m_pGame->m_pMagicConfigList[sType]->m_sType) {
			case 1:  // DEF_MAGICTYPE_DAMAGE_SPOT
			case 4:  // DEF_MAGICTYPE_SPDOWN_SPOT 4
			case 8:  // DEF_MAGICTYPE_TELEPORT 8
			case 10: // DEF_MAGICTYPE_CREATE 10
			case 11: // DEF_MAGICTYPE_PROTECT 11
			case 12: // DEF_MAGICTYPE_HOLDOBJECT 12
			case 16: // DEF_MAGICTYPE_CONFUSE
			case 17: // DEF_MAGICTYPE_POISON
			case 32: // DEF_MAGICTYPE_RESURRECTION
			case DEF_MAGICTYPE_HASTE:
				return;
			}
		}
	}

	if (m_pGame->m_pMagicConfigList[sType]->m_dwDelayTime == 0) {
		switch (m_pGame->m_pMagicConfigList[sType]->m_sType) {
		case DEF_MAGICTYPE_HASTE:
			switch (m_pGame->m_pMagicConfigList[sType]->m_sValue4) {
			case 1:
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);

				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (sOwnerH == iClientH) goto MAGIC_NOEFFECT;
					if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HASTE] != 0) goto MAGIC_NOEFFECT;
					m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HASTE] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
					m_pGame->SetHasteFlag(sOwnerH, cOwnerType, true);
					break;

				case DEF_OWNERTYPE_NPC:
					goto MAGIC_NOEFFECT;
					break;
				}
				m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_HASTE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000),
					sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				if (cOwnerType == DEF_OWNERTYPE_PLAYER)
					m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_HASTE, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);
				break;
			}
			break;
		case DEF_MAGICTYPE_DAMAGE_SPOT:
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);

			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) && (m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
			}
			break;

		case DEF_MAGICTYPE_HPUP_SPOT:
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			m_pGame->Effect_HpUp_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6);
			break;

		case DEF_MAGICTYPE_DAMAGE_AREA:
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);

			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) && (m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
			}

			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) && (m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
							m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					}
				}
			break;

		case DEF_MAGICTYPE_SPDOWN_SPOT:
			break;

		case DEF_MAGICTYPE_SPDOWN_AREA:
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6);
			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
				}
			break;

		case DEF_MAGICTYPE_POLYMORPH:
			// ÂºÂ¯Â½Ã… Â¸Â¶Â¹Ã½. 
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (1) { // m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_POLYMORPH] != 0) goto MAGIC_NOEFFECT;
					m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_POLYMORPH] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
					// Â¿Ã¸Â·Â¡ Ã…Â¸Ã€Ã”Ã€Â» Ã€ÃºÃ€Ã¥Ã‡Ã˜ Â³ÃµÂ´Ã‚Â´Ã™.
					m_pGame->m_pClientList[sOwnerH]->m_sOriginalType = m_pGame->m_pClientList[sOwnerH]->m_sType;
					// Â¹Ã™Â²Ã¯ Â¿ÃœÃ‡Ã¼Ã€Â» Ã…Ã«ÂºÂ¸Ã‡Ã˜ ÃÃ˜Â´Ã™.
					m_pGame->m_pClientList[sOwnerH]->m_sType = 18;
					m_pGame->SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_POLYMORPH] != 0) goto MAGIC_NOEFFECT;
					m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_POLYMORPH] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
					// Â¿Ã¸Â·Â¡ Ã…Â¸Ã€Ã”Ã€Â» Ã€ÃºÃ€Ã¥Ã‡Ã˜ Â³ÃµÂ´Ã‚Â´Ã™.
					m_pGame->m_pNpcList[sOwnerH]->m_sOriginalType = m_pGame->m_pNpcList[sOwnerH]->m_sType;
					// Â¹Ã™Â²Ã¯ Â¿ÃœÃ‡Ã¼Ã€Â» Ã…Ã«ÂºÂ¸Ã‡Ã˜ ÃÃ˜Â´Ã™.
					m_pGame->m_pNpcList[sOwnerH]->m_sType = 18;
					m_pGame->SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
					break;
				}

				// ÂºÂ¯Â½Ã… ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
				m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_POLYMORPH, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000),
					sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				// ÃˆÂ¿Â°ÃºÂ°Â¡ Â»Ã½Â°Ã¥Ã€Â½Ã€Â» Â¾Ã‹Â·ÃÃÃ˜Â´Ã™.
				if (cOwnerType == DEF_OWNERTYPE_PLAYER)
					m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_POLYMORPH, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);
			}
			break;

			// 05/20/2004 - Hypnotoad - Cancellation
		case DEF_MAGICTYPE_CANCELLATION:
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) && (m_pGame->m_pClientList[sOwnerH]->m_iHP > 0) && (m_pGame->m_pClientList[sOwnerH]->m_iAdminUserLevel == 0)) {

				// Removes Invisibility Flag 0x0010
				m_pGame->SetInvisibilityFlag(sOwnerH, cOwnerType, false);

				// Removes Illusion Flag 0x01000000
				m_pGame->SetIllusionFlag(sOwnerH, cOwnerType, false);

				// Removes Defense Shield Flag 0x02000000
				// Removes Great Defense Shield Flag 0x02000000
				m_pGame->SetDefenseShieldFlag(sOwnerH, cOwnerType, false);

				// Removes Absolute Magic Protection Flag 0x04000000	
				// Removes Protection From Magic Flag 0x04000000
				m_pGame->SetMagicProtectionFlag(sOwnerH, cOwnerType, false);

				// Removes Protection From Arrow Flag 0x08000000
				m_pGame->SetProtectionFromArrowFlag(sOwnerH, cOwnerType, false);

				// Removes Illusion Movement Flag 0x00200000
				m_pGame->SetIllusionMovementFlag(sOwnerH, cOwnerType, false);

				// Removes Berserk Flag 0x0020
				m_pGame->SetBerserkFlag(sOwnerH, cOwnerType, false);

				//Removes ice-added 
				m_pGame->SetIceFlag(sOwnerH, cOwnerType, false);

				//Remove paralyse

				m_pGame->bRemoveFromDelayEventList(sOwnerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_ICE);
				m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime),
					sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				m_pGame->bRemoveFromDelayEventList(sOwnerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_HOLDOBJECT);
				m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_HOLDOBJECT, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime),
					sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				m_pGame->bRemoveFromDelayEventList(sOwnerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_INHIBITION);
				m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_INHIBITION, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime),
					sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				m_pGame->bRemoveFromDelayEventList(sOwnerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_INVISIBILITY);
				m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_INVISIBILITY, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime),
					sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				m_pGame->bRemoveFromDelayEventList(sOwnerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_BERSERK);
				m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_BERSERK, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime),
					sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				m_pGame->bRemoveFromDelayEventList(sOwnerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_PROTECT);
				m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_PROTECT, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime),
					sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				m_pGame->bRemoveFromDelayEventList(sOwnerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_CONFUSE);
				m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_CONFUSE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime),
					sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				// Update Client
				m_pGame->SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
			}
			break;

		case DEF_MAGICTYPE_DAMAGE_AREA_NOSPOT_SPDOWN:
			// ������ ó������ �ʴ´�.
			// �ֺ� ���� ȿ�� 
			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// �ڽŵ� ������ �� ������ ����.
					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);
						m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
					}

					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
						(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
						// ���� ô�ϰ� �ִ� �÷��̾��.
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);
							m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
						}
					}
				}
			break;

		case DEF_MAGICTYPE_DAMAGE_LINEAR:
			// Ã€ÃÃÃ·Â¼Â± Â»Ã³Â¿Â¡ Ã€Ã–Â´Ã‚ Â¸Ã±Ã‡Â¥Â¸Â¦ Â¸Ã°ÂµÃŽ Â°Ã¸Â°ÃÃ‡Ã‘Â´Ã™.
			sX = m_pGame->m_pClientList[iClientH]->m_sX;
			sY = m_pGame->m_pClientList[iClientH]->m_sY;

			for (i = 2; i < 10; i++) {
				iErr = 0;
				CMisc::GetPoint2(sX, sY, dX, dY, &tX, &tY, &iErr, i);

				// tx, ty
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY);
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				// tx-1, ty
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				// tx+1, ty
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				// tx, ty-1
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				// tx, ty+1
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				if ((abs(tX - dX) <= 1) && (abs(tY - dY) <= 1)) break;
			}

			// ÃÃ–ÂºÂ¯ Â°Ã¸Â°Ã ÃˆÂ¿Â°Ãº 
			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// Ã€ÃšÂ½Ã…ÂµÂµ Ã‡Ã‡Ã†Ã¸ÂµÃ‰ Â¼Ã¶ Ã€Ã–Ã€Â¸Â´Ã ÃÃ–Ã€Ã‡.
					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
						(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
						// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
							m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					}
				}

			// dX, dY
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false

			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
				(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
				// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
			}
			break;

			// v2.16 2002-5-23 Â°Ã­Â±Â¤Ã‡Ã¶ 
		case DEF_MAGICTYPE_ICE_LINEAR:
			// Ã€ÃÃÃ·Â¼Â± Â»Ã³Â¿Â¡ Ã€Ã–Â´Ã‚ Â¸Ã±Ã‡Â¥Â¸Â¦ Â¸Ã°ÂµÃŽ Â¾Ã³Â¸Â®Â¸Ã§ Â°Ã¸Â°ÃÃ‡Ã‘Â´Ã™.
			sX = m_pGame->m_pClientList[iClientH]->m_sX;
			sY = m_pGame->m_pClientList[iClientH]->m_sY;

			for (i = 2; i < 10; i++) {
				iErr = 0;
				CMisc::GetPoint2(sX, sY, dX, dY, &tX, &tY, &iErr, i);

				// tx, ty
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY);
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// Â¾Ã³Â¾Ã®Â¼Â­ ÂµÂ¿Ã€Ã›Ã€ÃŒ Â´ÃŠÂ¾Ã®ÃÃ¶Â´Ã‚ ÃˆÂ¿Â°Ãº
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (m_pGame->m_pClientList[sOwnerH]->m_iHP < 0) goto MAGIC_NOEFFECT;
						// Ã…Â¸Â°Ã™Ã€ÃŒ Â»Ã¬Â¾Ã†Ã€Ã–Â°Ã­ Â¾Ã³Ã€Â½ Ã€ÃºÃ‡Ã—Â¿Â¡ Â½Ã‡Ã†ÃÃ‡ÃŸÂ´Ã™Â¸Ã© Â¾Ã³Â¾Ã®ÂºÃ™Â´Ã‚Â´Ã™.
						if ((m_pGame->m_pClientList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
								// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								// Â´Ã«Â»Ã³Ã€ÃŒ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Ã€ÃŽ Â°Ã¦Â¿Ã¬ Â¾Ã‹Â·ÃÃÃ˜Â´Ã™.
								m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if ((m_pGame->m_pNpcList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
								// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
				}

				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// Â¾Ã³Â¾Ã®Â¼Â­ ÂµÂ¿Ã€Ã›Ã€ÃŒ Â´ÃŠÂ¾Ã®ÃÃ¶Â´Ã‚ ÃˆÂ¿Â°Ãº
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// Ã…Â¸Â°Ã™Ã€ÃŒ Â»Ã¬Â¾Ã†Ã€Ã–Â°Ã­ Â¾Ã³Ã€Â½ Ã€ÃºÃ‡Ã—Â¿Â¡ Â½Ã‡Ã†ÃÃ‡ÃŸÂ´Ã™Â¸Ã© Â¾Ã³Â¾Ã®ÂºÃ™Â´Ã‚Â´Ã™.
							if ((m_pGame->m_pClientList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
									// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
									m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									// Â´Ã«Â»Ã³Ã€ÃŒ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Ã€ÃŽ Â°Ã¦Â¿Ã¬ Â¾Ã‹Â·ÃÃÃ˜Â´Ã™.
									m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if ((m_pGame->m_pNpcList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
									// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
									m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
						//
					}
				}

				// tx-1, ty
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// Â¾Ã³Â¾Ã®Â¼Â­ ÂµÂ¿Ã€Ã›Ã€ÃŒ Â´ÃŠÂ¾Ã®ÃÃ¶Â´Ã‚ ÃˆÂ¿Â°Ãº
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// Ã…Â¸Â°Ã™Ã€ÃŒ Â»Ã¬Â¾Ã†Ã€Ã–Â°Ã­ Â¾Ã³Ã€Â½ Ã€ÃºÃ‡Ã—Â¿Â¡ Â½Ã‡Ã†ÃÃ‡ÃŸÂ´Ã™Â¸Ã© Â¾Ã³Â¾Ã®ÂºÃ™Â´Ã‚Â´Ã™.
						if ((m_pGame->m_pClientList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
								// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								// Â´Ã«Â»Ã³Ã€ÃŒ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Ã€ÃŽ Â°Ã¦Â¿Ã¬ Â¾Ã‹Â·ÃÃÃ˜Â´Ã™.
								m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if ((m_pGame->m_pNpcList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
								// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
					//
				}

				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// Â¾Ã³Â¾Ã®Â¼Â­ ÂµÂ¿Ã€Ã›Ã€ÃŒ Â´ÃŠÂ¾Ã®ÃÃ¶Â´Ã‚ ÃˆÂ¿Â°Ãº
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// Ã…Â¸Â°Ã™Ã€ÃŒ Â»Ã¬Â¾Ã†Ã€Ã–Â°Ã­ Â¾Ã³Ã€Â½ Ã€ÃºÃ‡Ã—Â¿Â¡ Â½Ã‡Ã†ÃÃ‡ÃŸÂ´Ã™Â¸Ã© Â¾Ã³Â¾Ã®ÂºÃ™Â´Ã‚Â´Ã™.
							if ((m_pGame->m_pClientList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
									// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
									m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									// Â´Ã«Â»Ã³Ã€ÃŒ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Ã€ÃŽ Â°Ã¦Â¿Ã¬ Â¾Ã‹Â·ÃÃÃ˜Â´Ã™.
									m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if ((m_pGame->m_pNpcList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
									// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
									m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
						//
					}
				}

				// tx+1, ty
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// Â¾Ã³Â¾Ã®Â¼Â­ ÂµÂ¿Ã€Ã›Ã€ÃŒ Â´ÃŠÂ¾Ã®ÃÃ¶Â´Ã‚ ÃˆÂ¿Â°Ãº
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// Ã…Â¸Â°Ã™Ã€ÃŒ Â»Ã¬Â¾Ã†Ã€Ã–Â°Ã­ Â¾Ã³Ã€Â½ Ã€ÃºÃ‡Ã—Â¿Â¡ Â½Ã‡Ã†ÃÃ‡ÃŸÂ´Ã™Â¸Ã© Â¾Ã³Â¾Ã®ÂºÃ™Â´Ã‚Â´Ã™.
						if ((m_pGame->m_pClientList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
								// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								// Â´Ã«Â»Ã³Ã€ÃŒ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Ã€ÃŽ Â°Ã¦Â¿Ã¬ Â¾Ã‹Â·ÃÃÃ˜Â´Ã™.
								m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if ((m_pGame->m_pNpcList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
								// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
					//
				}

				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// Â¾Ã³Â¾Ã®Â¼Â­ ÂµÂ¿Ã€Ã›Ã€ÃŒ Â´ÃŠÂ¾Ã®ÃÃ¶Â´Ã‚ ÃˆÂ¿Â°Ãº
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// Ã…Â¸Â°Ã™Ã€ÃŒ Â»Ã¬Â¾Ã†Ã€Ã–Â°Ã­ Â¾Ã³Ã€Â½ Ã€ÃºÃ‡Ã—Â¿Â¡ Â½Ã‡Ã†ÃÃ‡ÃŸÂ´Ã™Â¸Ã© Â¾Ã³Â¾Ã®ÂºÃ™Â´Ã‚Â´Ã™.
							if ((m_pGame->m_pClientList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
									// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
									m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									// Â´Ã«Â»Ã³Ã€ÃŒ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Ã€ÃŽ Â°Ã¦Â¿Ã¬ Â¾Ã‹Â·ÃÃÃ˜Â´Ã™.
									m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if ((m_pGame->m_pNpcList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
									// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
									m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
						//
					}
				}

				// tx, ty-1
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// Â¾Ã³Â¾Ã®Â¼Â­ ÂµÂ¿Ã€Ã›Ã€ÃŒ Â´ÃŠÂ¾Ã®ÃÃ¶Â´Ã‚ ÃˆÂ¿Â°Ãº
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// Ã…Â¸Â°Ã™Ã€ÃŒ Â»Ã¬Â¾Ã†Ã€Ã–Â°Ã­ Â¾Ã³Ã€Â½ Ã€ÃºÃ‡Ã—Â¿Â¡ Â½Ã‡Ã†ÃÃ‡ÃŸÂ´Ã™Â¸Ã© Â¾Ã³Â¾Ã®ÂºÃ™Â´Ã‚Â´Ã™.
						if ((m_pGame->m_pClientList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
								// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								// Â´Ã«Â»Ã³Ã€ÃŒ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Ã€ÃŽ Â°Ã¦Â¿Ã¬ Â¾Ã‹Â·ÃÃÃ˜Â´Ã™.
								m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if ((m_pGame->m_pNpcList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
								// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
					//
				}

				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// Â¾Ã³Â¾Ã®Â¼Â­ ÂµÂ¿Ã€Ã›Ã€ÃŒ Â´ÃŠÂ¾Ã®ÃÃ¶Â´Ã‚ ÃˆÂ¿Â°Ãº
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// Ã…Â¸Â°Ã™Ã€ÃŒ Â»Ã¬Â¾Ã†Ã€Ã–Â°Ã­ Â¾Ã³Ã€Â½ Ã€ÃºÃ‡Ã—Â¿Â¡ Â½Ã‡Ã†ÃÃ‡ÃŸÂ´Ã™Â¸Ã© Â¾Ã³Â¾Ã®ÂºÃ™Â´Ã‚Â´Ã™.
							if ((m_pGame->m_pClientList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
									// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
									m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									// Â´Ã«Â»Ã³Ã€ÃŒ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Ã€ÃŽ Â°Ã¦Â¿Ã¬ Â¾Ã‹Â·ÃÃÃ˜Â´Ã™.
									m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if ((m_pGame->m_pNpcList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
									// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
									m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
						//
					}
				}

				// tx, ty+1
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// Â¾Ã³Â¾Ã®Â¼Â­ ÂµÂ¿Ã€Ã›Ã€ÃŒ Â´ÃŠÂ¾Ã®ÃÃ¶Â´Ã‚ ÃˆÂ¿Â°Ãº
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// Ã…Â¸Â°Ã™Ã€ÃŒ Â»Ã¬Â¾Ã†Ã€Ã–Â°Ã­ Â¾Ã³Ã€Â½ Ã€ÃºÃ‡Ã—Â¿Â¡ Â½Ã‡Ã†ÃÃ‡ÃŸÂ´Ã™Â¸Ã© Â¾Ã³Â¾Ã®ÂºÃ™Â´Ã‚Â´Ã™.
						if ((m_pGame->m_pClientList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
								// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								// Â´Ã«Â»Ã³Ã€ÃŒ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Ã€ÃŽ Â°Ã¦Â¿Ã¬ Â¾Ã‹Â·ÃÃÃ˜Â´Ã™.
								m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if ((m_pGame->m_pNpcList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
								// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
					//
				}

				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// Â¾Ã³Â¾Ã®Â¼Â­ ÂµÂ¿Ã€Ã›Ã€ÃŒ Â´ÃŠÂ¾Ã®ÃÃ¶Â´Ã‚ ÃˆÂ¿Â°Ãº
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// Ã…Â¸Â°Ã™Ã€ÃŒ Â»Ã¬Â¾Ã†Ã€Ã–Â°Ã­ Â¾Ã³Ã€Â½ Ã€ÃºÃ‡Ã—Â¿Â¡ Â½Ã‡Ã†ÃÃ‡ÃŸÂ´Ã™Â¸Ã© Â¾Ã³Â¾Ã®ÂºÃ™Â´Ã‚Â´Ã™.
							if ((m_pGame->m_pClientList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
									// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
									m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									// Â´Ã«Â»Ã³Ã€ÃŒ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Ã€ÃŽ Â°Ã¦Â¿Ã¬ Â¾Ã‹Â·ÃÃÃ˜Â´Ã™.
									m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if ((m_pGame->m_pNpcList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
									// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
									m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
						//
					}
				}

				if ((abs(tX - dX) <= 1) && (abs(tY - dY) <= 1)) break;
			}

			// ÃÃ–ÂºÂ¯ Â°Ã¸Â°Ã ÃˆÂ¿Â°Ãº 
			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// Ã€ÃšÂ½Ã…ÂµÂµ Ã‡Ã‡Ã†Ã¸ÂµÃ‰ Â¼Ã¶ Ã€Ã–Ã€Â¸Â´Ã ÃÃ–Ã€Ã‡.
					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// Â¾Ã³Â¾Ã®Â¼Â­ ÂµÂ¿Ã€Ã›Ã€ÃŒ Â´ÃŠÂ¾Ã®ÃÃ¶Â´Ã‚ ÃˆÂ¿Â°Ãº
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// Ã…Â¸Â°Ã™Ã€ÃŒ Â»Ã¬Â¾Ã†Ã€Ã–Â°Ã­ Â¾Ã³Ã€Â½ Ã€ÃºÃ‡Ã—Â¿Â¡ Â½Ã‡Ã†ÃÃ‡ÃŸÂ´Ã™Â¸Ã© Â¾Ã³Â¾Ã®ÂºÃ™Â´Ã‚Â´Ã™.
							if ((m_pGame->m_pClientList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
									// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
									m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									// Â´Ã«Â»Ã³Ã€ÃŒ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Ã€ÃŽ Â°Ã¦Â¿Ã¬ Â¾Ã‹Â·ÃÃÃ˜Â´Ã™.
									m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if ((m_pGame->m_pNpcList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
									// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
									m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
						//
					}

					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
						(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
						// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
							// Â¾Ã³Â¾Ã®Â¼Â­ ÂµÂ¿Ã€Ã›Ã€ÃŒ Â´ÃŠÂ¾Ã®ÃÃ¶Â´Ã‚ ÃˆÂ¿Â°Ãº
							switch (cOwnerType) {
							case DEF_OWNERTYPE_PLAYER:
								if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								// Ã…Â¸Â°Ã™Ã€ÃŒ Â»Ã¬Â¾Ã†Ã€Ã–Â°Ã­ Â¾Ã³Ã€Â½ Ã€ÃºÃ‡Ã—Â¿Â¡ Â½Ã‡Ã†ÃÃ‡ÃŸÂ´Ã™Â¸Ã© Â¾Ã³Â¾Ã®ÂºÃ™Â´Ã‚Â´Ã™.
								if ((m_pGame->m_pClientList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
									if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
										m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
										m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
										// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
										m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
											sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
										// Â´Ã«Â»Ã³Ã€ÃŒ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Ã€ÃŽ Â°Ã¦Â¿Ã¬ Â¾Ã‹Â·ÃÃÃ˜Â´Ã™.
										m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
									}
								}
								break;

							case DEF_OWNERTYPE_NPC:
								if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								if ((m_pGame->m_pNpcList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
									if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
										m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
										m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
										// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
										m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
											sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									}
								}
								break;
							}
							//
						}
					}
				}

			// dX, dY
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
				m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
				// Â¾Ã³Â¾Ã®Â¼Â­ ÂµÂ¿Ã€Ã›Ã€ÃŒ Â´ÃŠÂ¾Ã®ÃÃ¶Â´Ã‚ ÃˆÂ¿Â°Ãº
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					// Ã…Â¸Â°Ã™Ã€ÃŒ Â»Ã¬Â¾Ã†Ã€Ã–Â°Ã­ Â¾Ã³Ã€Â½ Ã€ÃºÃ‡Ã—Â¿Â¡ Â½Ã‡Ã†ÃÃ‡ÃŸÂ´Ã™Â¸Ã© Â¾Ã³Â¾Ã®ÂºÃ™Â´Ã‚Â´Ã™.
					if ((m_pGame->m_pClientList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
						if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
							m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
							m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
							// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
							m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
								sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							// Â´Ã«Â»Ã³Ã€ÃŒ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Ã€ÃŽ Â°Ã¦Â¿Ã¬ Â¾Ã‹Â·ÃÃÃ˜Â´Ã™.
							m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
						}
					}
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if ((m_pGame->m_pNpcList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
						if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
							m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
							m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
							// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
							m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
								sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
						}
					}
					break;
				}
				//
			}

			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
				(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
				// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
					// Â¾Ã³Â¾Ã®Â¼Â­ ÂµÂ¿Ã€Ã›Ã€ÃŒ Â´ÃŠÂ¾Ã®ÃÃ¶Â´Ã‚ ÃˆÂ¿Â°Ãº
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// Ã…Â¸Â°Ã™Ã€ÃŒ Â»Ã¬Â¾Ã†Ã€Ã–Â°Ã­ Â¾Ã³Ã€Â½ Ã€ÃºÃ‡Ã—Â¿Â¡ Â½Ã‡Ã†ÃÃ‡ÃŸÂ´Ã™Â¸Ã© Â¾Ã³Â¾Ã®ÂºÃ™Â´Ã‚Â´Ã™.
						if ((m_pGame->m_pClientList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
								// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								// Â´Ã«Â»Ã³Ã€ÃŒ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Ã€ÃŽ Â°Ã¦Â¿Ã¬ Â¾Ã‹Â·ÃÃÃ˜Â´Ã™.
								m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if ((m_pGame->m_pNpcList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
								// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
					//
				}
			}
			break;


		case DEF_MAGICTYPE_INHIBITION:
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			switch (cOwnerType) {
			case DEF_OWNERTYPE_PLAYER:
				if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
				if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INHIBITION] != 0) goto MAGIC_NOEFFECT;
				if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] == 5) goto MAGIC_NOEFFECT;
				if (m_pGame->m_pClientList[iClientH]->m_cSide == m_pGame->m_pClientList[sOwnerH]->m_cSide) goto MAGIC_NOEFFECT;
				if (memcmp(m_pGame->m_pClientList[iClientH]->m_cLocation, "NONE", 4) == 0) goto MAGIC_NOEFFECT;
				//if (m_pGame->m_pClientList[sOwnerH]->m_iAdminUserLevel != 0) goto MAGIC_NOEFFECT;
				m_pGame->m_pClientList[sOwnerH]->m_bInhibition = true;
				m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_INHIBITION, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000),
					sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);
				break;
			}
			break;


		case DEF_MAGICTYPE_TREMOR: // v1.4 ÃÃ–ÂºÂ¯ Â°Ã¸Â°Ã ÃˆÂ¿Â°ÃºÂ¿Â¡ Ã€ÃŒÂ¾Ã® Ã€ÃœÂ·Ã¹ ÃˆÂ¿Â°ÃºÂ°Â¡ Ã€Ã–Â´Ã™.
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);

			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
				(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
				// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
			}

			// ÃÃ–ÂºÂ¯ Â°Ã¸Â°Ã ÃˆÂ¿Â°Ãº 
			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// Ã€ÃšÂ½Ã…ÂµÂµ Ã‡Ã‡Ã†Ã¸ÂµÃ‰ Â¼Ã¶ Ã€Ã–Ã€Â¸Â´Ã ÃÃ–Ã€Ã‡.
					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
						(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
						// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
							m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					}
				}
			break;

		case DEF_MAGICTYPE_DAMAGE_AREA_NOSPOT:
			// ÃÃ·Â°ÃÃ€Âº ÃƒÂ³Â¸Â®Ã‡ÃÃÃ¶ Â¾ÃŠÂ´Ã‚Â´Ã™.
			// ÃÃ–ÂºÂ¯ Â°Ã¸Â°Ã ÃˆÂ¿Â°Ãº 
			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// Ã€ÃšÂ½Ã…ÂµÂµ Ã‡Ã‡Ã†Ã¸ÂµÃ‰ Â¼Ã¶ Ã€Ã–Ã€Â¸Â´Ã ÃÃ–Ã€Ã‡.
					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
						(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
						// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
							m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					}
				}
			break;

		case DEF_MAGICTYPE_SPUP_AREA:
			// SpÂ°Â¡ Â»Ã³Â½Ã‚Ã‡Ã‘Â´Ã™.
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			// Â¸Â¶Â¹Ã½ Ã€ÃºÃ‡Ã—Ã€ÃŒ Ã‡ÃŠÂ¿Ã¤Â¾Ã¸Â´Ã™. 
			m_pGame->Effect_SpUp_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6);
			// ÃÃ–ÂºÂ¯ Â°Ã¸Â°Ã ÃˆÂ¿Â°Ãº 
			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// Ã€ÃšÂ½Ã…ÂµÂµ Ã‡Ã‡Ã†Ã¸ÂµÃ‰ Â¼Ã¶ Ã€Ã–Ã€Â¸Â´Ã ÃÃ–Ã€Ã‡.
					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					// Â¸Â¶Â¹Ã½Ã€ÃºÃ‡Ã—Ã€ÃŒ Ã‡ÃŠÂ¿Ã¤ Â¾Ã¸Â´Ã™.
					m_pGame->Effect_SpUp_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
				}
			break;

			// v2.16 2002-5-23 °í±¤Çö 
		case DEF_MAGICTYPE_DAMAGE_LINEAR_SPDOWN:
			// ÀÏÁ÷¼± »ó¿¡ ÀÖ´Â ¸ñÇ¥¸¦ ¸ðµÎ ¾ó¸®¸ç °ø°ÝÇÑ´Ù.
			sX = m_pGame->m_pClientList[iClientH]->m_sX;
			sY = m_pGame->m_pClientList[iClientH]->m_sY;

			for (i = 2; i < 10; i++) {
				iErr = 0;
				CMisc::GetPoint2(sX, sY, dX, dY, &tX, &tY, &iErr, i);

				// tx, ty
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY);
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// ¾ó¾î¼­ µ¿ÀÛÀÌ ´Ê¾îÁö´Â È¿°ú
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// Å¸°ÙÀÌ »ì¾ÆÀÖ°í ¾óÀ½ ÀúÇ×¿¡ ½ÇÆÐÇß´Ù¸é ¾ó¾îºÙ´Â´Ù.
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
							m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
							m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
						}
						break;
					}
				}

				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// Á×Àº Ã´ÇÏ°í ÀÖ´Â ÇÃ·¹ÀÌ¾î´Ù.
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// ¾ó¾î¼­ µ¿ÀÛÀÌ ´Ê¾îÁö´Â È¿°ú
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// Å¸°ÙÀÌ »ì¾ÆÀÖ°í ¾óÀ½ ÀúÇ×¿¡ ½ÇÆÐÇß´Ù¸é ¾ó¾îºÙ´Â´Ù.
							if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
								m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
								m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
							}
							break;
						}
						//
					}
				}

				// tx-1, ty
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// ¾ó¾î¼­ µ¿ÀÛÀÌ ´Ê¾îÁö´Â È¿°ú
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// Å¸°ÙÀÌ »ì¾ÆÀÖ°í ¾óÀ½ ÀúÇ×¿¡ ½ÇÆÐÇß´Ù¸é ¾ó¾îºÙ´Â´Ù.
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
							m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {

							m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
							m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
						}
						break;
					}
					//
				}

				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// Á×Àº Ã´ÇÏ°í ÀÖ´Â ÇÃ·¹ÀÌ¾î´Ù.
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// ¾ó¾î¼­ µ¿ÀÛÀÌ ´Ê¾îÁö´Â È¿°ú
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// Å¸°ÙÀÌ »ì¾ÆÀÖ°í ¾óÀ½ ÀúÇ×¿¡ ½ÇÆÐÇß´Ù¸é ¾ó¾îºÙ´Â´Ù.
							if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
								m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
								m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
							}
							break;
						}
						//
					}
				}

				// tx+1, ty
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// ¾ó¾î¼­ µ¿ÀÛÀÌ ´Ê¾îÁö´Â È¿°ú
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// Å¸°ÙÀÌ »ì¾ÆÀÖ°í ¾óÀ½ ÀúÇ×¿¡ ½ÇÆÐÇß´Ù¸é ¾ó¾îºÙ´Â´Ù.
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
							m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
							m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
						}
						break;
					}
					//
				}

				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// Á×Àº Ã´ÇÏ°í ÀÖ´Â ÇÃ·¹ÀÌ¾î´Ù.
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// ¾ó¾î¼­ µ¿ÀÛÀÌ ´Ê¾îÁö´Â È¿°ú
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// Å¸°ÙÀÌ »ì¾ÆÀÖ°í ¾óÀ½ ÀúÇ×¿¡ ½ÇÆÐÇß´Ù¸é ¾ó¾îºÙ´Â´Ù.
							if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
								m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
								m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
							}
							break;
						}
						//
					}
				}

				// tx, ty-1
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// ¾ó¾î¼­ µ¿ÀÛÀÌ ´Ê¾îÁö´Â È¿°ú
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// Å¸°ÙÀÌ »ì¾ÆÀÖ°í ¾óÀ½ ÀúÇ×¿¡ ½ÇÆÐÇß´Ù¸é ¾ó¾îºÙ´Â´Ù.
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
							m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
							m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
						}
						break;
					}
					//
				}

				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// Á×Àº Ã´ÇÏ°í ÀÖ´Â ÇÃ·¹ÀÌ¾î´Ù.
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// ¾ó¾î¼­ µ¿ÀÛÀÌ ´Ê¾îÁö´Â È¿°ú
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// Å¸°ÙÀÌ »ì¾ÆÀÖ°í ¾óÀ½ ÀúÇ×¿¡ ½ÇÆÐÇß´Ù¸é ¾ó¾îºÙ´Â´Ù.
							if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
								m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
								m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
							}
							break;
						}
						//
					}
				}

				// tx, ty+1
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// ¾ó¾î¼­ µ¿ÀÛÀÌ ´Ê¾îÁö´Â È¿°ú
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// Å¸°ÙÀÌ »ì¾ÆÀÖ°í ¾óÀ½ ÀúÇ×¿¡ ½ÇÆÐÇß´Ù¸é ¾ó¾îºÙ´Â´Ù.
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
							m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
							m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
						}
						break;
					}
					//
				}

				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// Á×Àº Ã´ÇÏ°í ÀÖ´Â ÇÃ·¹ÀÌ¾î´Ù.
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// ¾ó¾î¼­ µ¿ÀÛÀÌ ´Ê¾îÁö´Â È¿°ú
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// Å¸°ÙÀÌ »ì¾ÆÀÖ°í ¾óÀ½ ÀúÇ×¿¡ ½ÇÆÐÇß´Ù¸é ¾ó¾îºÙ´Â´Ù.
							if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
								m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
								m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
							}
							break;
						}
						//
					}
				}

				if ((abs(tX - dX) <= 1) && (abs(tY - dY) <= 1)) break;
			}

			// ÁÖº¯ °ø°Ý È¿°ú 
			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// ÀÚ½Åµµ ÇÇÆøµÉ ¼ö ÀÖÀ¸´Ï ÁÖÀÇ.
					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// ¾ó¾î¼­ µ¿ÀÛÀÌ ´Ê¾îÁö´Â È¿°ú
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// Å¸°ÙÀÌ »ì¾ÆÀÖ°í ¾óÀ½ ÀúÇ×¿¡ ½ÇÆÐÇß´Ù¸é ¾ó¾îºÙ´Â´Ù.
							if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
								m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
								m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
							}
							break;
						}
						//
					}

					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
						(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
						// Á×Àº Ã´ÇÏ°í ÀÖ´Â ÇÃ·¹ÀÌ¾î´Ù.
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
							// ¾ó¾î¼­ µ¿ÀÛÀÌ ´Ê¾îÁö´Â È¿°ú
							switch (cOwnerType) {
							case DEF_OWNERTYPE_PLAYER:
								if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								// Å¸°ÙÀÌ »ì¾ÆÀÖ°í ¾óÀ½ ÀúÇ×¿¡ ½ÇÆÐÇß´Ù¸é ¾ó¾îºÙ´Â´Ù.
								if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
									m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
									m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
									m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
								}
								break;

							case DEF_OWNERTYPE_NPC:
								if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
									m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
									m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
									m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
								}
								break;
							}
							//
						}
					}
				}

			// dX, dY
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
				m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
				// ¾ó¾î¼­ µ¿ÀÛÀÌ ´Ê¾îÁö´Â È¿°ú
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					// Å¸°ÙÀÌ »ì¾ÆÀÖ°í ¾óÀ½ ÀúÇ×¿¡ ½ÇÆÐÇß´Ù¸é ¾ó¾îºÙ´Â´Ù.
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
						m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
					}
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
						m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
					}
					break;
				}
				//
			}

			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
				(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
				// Á×Àº Ã´ÇÏ°í ÀÖ´Â ÇÃ·¹ÀÌ¾î´Ù.
				if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
					// ¾ó¾î¼­ µ¿ÀÛÀÌ ´Ê¾îÁö´Â È¿°ú
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// Å¸°ÙÀÌ »ì¾ÆÀÖ°í ¾óÀ½ ÀúÇ×¿¡ ½ÇÆÐÇß´Ù¸é ¾ó¾îºÙ´Â´Ù.
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
							m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							m_pGame->Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
							m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);

						}
						break;
					}
					//
				}
			}
			break;

		case DEF_MAGICTYPE_TELEPORT:
			// Ã…ÃšÂ·Â¹Ã†Ã·Ã†Â® Â¸Â¶Â¹Ã½. sValue 4Â¿Â¡ ÂµÃ»Â¶Ã³Â¼Â­ Ã…ÃšÂ·Â¹Ã†Ã·Ã†Â® Â¸Ã±Ã€Ã»ÃÃ¶Â°Â¡ Â°Ã¡ÃÂ¤ÂµÃˆÂ´Ã™.
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);

			switch (m_pGame->m_pMagicConfigList[sType]->m_sValue4) {
			case 1:
				// Ã€ÃšÂ½Ã…Ã€ÃŒ Â¼Ã’Â¼Ã“ÂµÃˆ Â¸Â¶Ã€Â»Â·ÃŽ Ã…ÃšÂ·Â¹Ã†Ã·Ã†Â®. RecallÃ€ÃŒÂ´Ã™.
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (sOwnerH == iClientH)) {
					// Ã€ÃšÂ½Ã…Â¿ÃœÂ¿Â¡Â´Ã‚ RecallÃ‡Ã’ Â¼Ã¶ Â¾Ã¸Â´Ã™.
					m_pGame->RequestTeleportHandler(iClientH, "1   ");
				}
				break;
			}
			break;

		case DEF_MAGICTYPE_SUMMON:
			// Â¼Ã’ÃˆÂ¯Â¸Â¶Â¹Ã½ 

			// Â»Ã§Ã…ÃµÃ€Ã¥ Â³Â»Â¿Â¡Â¼Â­Â´Ã‚ Â¼Ã’ÃˆÂ¯Â¸Â¶Â¹Ã½Ã€ÃŒ ÂºÃ’Â°Â¡Â´Ã‰.
			if (m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->m_bIsFightZone) return;

			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			// ÃÃ¶ÃÂ¤ÂµÃˆ OwnerÂ°Â¡ MasterÂ°Â¡ ÂµÃˆÂ´Ã™. 
			if ((sOwnerH != 0) && (cOwnerType == DEF_OWNERTYPE_PLAYER)) {
				// MasterÂ·ÃŽ ÃÃ¶ÃÂ¤ÂµÃˆ Â´Ã«Â»Ã³Ã€Â» ÂµÃ»Â¶Ã³Â´Ã™Â´ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Â°Â´ÃƒÂ¼ Â¼Ã¶Â¸Â¦ Â°Ã¨Â»ÃªÃ‡Ã‘Â´Ã™. 
				iFollowersNum = m_pGame->iGetFollowerNumber(sOwnerH, cOwnerType);

				// Â¼Ã’ÃˆÂ¯Â¸Â¶Â¹Ã½Ã€Â» CastingÃ‡Ã‘ Ã€ÃšÃ€Ã‡ Magery/20 Â¸Â¸Ã…Â­Ã€Ã‡ Â¸Ã³Â½ÂºÃ…ÃÂ¸Â¦ Â¼Ã’ÃˆÂ¯Ã‡Ã’ Â¼Ã¶ Ã€Ã–Â´Ã™.
				if (iFollowersNum >= (m_pGame->m_pClientList[iClientH]->m_cSkillMastery[4] / 20)) break;

				iNamingValue = m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->iGetEmptyNamingValue();
				if (iNamingValue == -1) {
					// Â´ÃµÃ€ÃŒÂ»Ã³ Ã€ÃŒ Â¸ÃŠÂ¿Â¡ NPCÂ¸Â¦ Â¸Â¸ÂµÃ©Â¼Ã¶ Â¾Ã¸Â´Ã™. Ã€ÃŒÂ¸Â§Ã€Â» Ã‡Ã’Â´Ã§Ã‡Ã’ Â¼Ã¶ Â¾Ã¸Â±Ã¢ Â¶Â§Â¹Â®.
				}
				else {
					// NPCÂ¸Â¦ Â»Ã½Â¼ÂºÃ‡Ã‘Â´Ã™.
					std::memset(cName, 0, sizeof(cName));
					std::snprintf(cName, sizeof(cName), "XX%d", iNamingValue);
					cName[0] = '_';
					cName[1] = m_pGame->m_pClientList[iClientH]->m_cMapIndex + 65;

					// MageryÂ¿Â¡ ÂµÃ»Â¶Ã³ Â¼Ã’ÃˆÂ¯ÂµÃ‡Â´Ã‚ Â¸Ã³Â½ÂºÃ…ÃÃ€Ã‡ ÂµÃ®Â±ÃžÃ€ÃŒ Â´ÃžÂ¶Ã³ÃÃ¸Â´Ã™.
					std::memset(cNpcName, 0, sizeof(cNpcName));

					switch (iV1) {
					case 0: // Ã€ÃÂ¹ÃÃ€Ã»Ã€ÃŽ Â°Ã¦Â¿Ã¬ 
						iResult = m_pGame->iDice(1, m_pGame->m_pClientList[iClientH]->m_cSkillMastery[4] / 10);

						// v1.42 ÃƒÃ–Ã€Ãº Â¸Ã· Â·Â¹ÂºÂ§Ã€Â» Ã€Ã”Â·Ã‚ 
						if (iResult < m_pGame->m_pClientList[iClientH]->m_cSkillMastery[4] / 20)
							iResult = m_pGame->m_pClientList[iClientH]->m_cSkillMastery[4] / 20;

						switch (iResult) {
						case 1: strcpy(cNpcName, "Slime"); break;
						case 2: strcpy(cNpcName, "Giant-Ant"); break;
						case 3: strcpy(cNpcName, "Amphis"); break;
						case 4: strcpy(cNpcName, "Orc"); break;
						case 5: strcpy(cNpcName, "Skeleton"); break;
						case 6:	strcpy(cNpcName, "Clay-Golem"); break;
						case 7:	strcpy(cNpcName, "Stone-Golem"); break;
						case 8: strcpy(cNpcName, "Orc-Mage"); break;
						case 9:	strcpy(cNpcName, "Hellbound"); break;
						case 10:strcpy(cNpcName, "Cyclops"); break;
						}
						break;

					case 1:	strcpy(cNpcName, "Orc"); break;
					case 2: strcpy(cNpcName, "Skeleton"); break;
					case 3: strcpy(cNpcName, "Clay-Golem"); break;
					case 4: strcpy(cNpcName, "Stone-Golem"); break;
					case 5: strcpy(cNpcName, "Hellbound"); break;
					case 6: strcpy(cNpcName, "Cyclops"); break;
					case 7: strcpy(cNpcName, "Troll"); break;
					case 8: strcpy(cNpcName, "Orge"); break;
					}

					if (m_pGame->bCreateNewNpc(cNpcName, cName, m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->m_cName, 0, 0, DEF_MOVETYPE_RANDOM, &dX, &dY, cNpcWaypoint, 0, 0, m_pGame->m_pClientList[iClientH]->m_cSide, false, true) == false) {
						// Â½Ã‡Ã†ÃÃ‡ÃŸÃ€Â¸Â¹Ã‡Â·ÃŽ Â¿Â¹Â¾Ã ÂµÃˆ NameValueÂ¸Â¦ Ã‡Ã˜ÃÂ¦Â½ÃƒÃ…Â²Â´Ã™.
						m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->SetNamingValueEmpty(iNamingValue);
					}
					else {
						std::memset(cName_Master, 0, sizeof(cName_Master));
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							memcpy(cName_Master, m_pGame->m_pClientList[sOwnerH]->m_cCharName, 10);
							break;
						case DEF_OWNERTYPE_NPC:
							memcpy(cName_Master, m_pGame->m_pNpcList[sOwnerH]->m_cName, 5);
							break;
						}
						if (m_pGame->m_pEntityManager != 0) m_pGame->m_pEntityManager->bSetNpcFollowMode(cName, cName_Master, cOwnerType);
					}
				}
			}
			break;

		case DEF_MAGICTYPE_CREATE:
			// Â¹Â«Â¾Ã°Â°Â¡Â¸Â¦ Â»Ã½Â¼ÂºÂ½ÃƒÃ…Â°Â´Ã‚ Â¸Â¶Â¹Ã½ 

			// Ã€Â§Ã„Â¡Ã‡Ã’ Â¼Ã¶ Â¾Ã¸Â´Ã‚ Â°Ã·Â¿Â¡Â´Ã‚ Â»Ã½Â±Ã¢ÃÃ¶ Â¾ÃŠÂ´Ã‚Â´Ã™. 
			if (m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->bGetIsMoveAllowedTile(dX, dY) == false)
				goto MAGIC_NOEFFECT;

			pItem = new class CItem;

			switch (m_pGame->m_pMagicConfigList[sType]->m_sValue4) {
			case 1:
				// Food
				if (m_pGame->iDice(1, 2) == 1)
					std::snprintf(cItemName, sizeof(cItemName), "Meat");
				else std::snprintf(cItemName, sizeof(cItemName), "Baguette");
				break;
			}

			m_pGame->_bInitItemAttr(pItem, cItemName);

			// v2.15 Â¸Â¶Â¹Ã½Ã€Â¸Â·ÃŽ Â»Ã½Â±Ã¤ Â¾Ã†Ã€ÃŒÃ…Ã›Â¿Â¡ Â°Ã­Ã€Â¯Â¹Ã¸ÃˆÂ£ Ã€ÃºÃ€Ã¥ 
			pItem->m_sTouchEffectType = DEF_ITET_ID;
			pItem->m_sTouchEffectValue1 = static_cast<short>(m_pGame->iDice(1, 100000));
			pItem->m_sTouchEffectValue2 = static_cast<short>(m_pGame->iDice(1, 100000));
			pItem->m_sTouchEffectValue3 = (short)GameClock::GetTimeMS();

			// Â¾Ã†Ã€ÃŒÃ…Ã›Ã€Â» Â¼Â­Ã€Ã–Â´Ã‚ Ã€Â§Ã„Â¡Â¿Â¡ Â¹Ã¶Â¸Â°Â´Ã™. 
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->bSetItem(dX, dY, pItem);

			// v1.41 ÃˆÃ±Â±Ã Â¾Ã†Ã€ÃŒÃ…Ã›Ã€Â» Â¶Â³Â¾Ã®Â¶ÃŸÂ¸Â° Â°ÃÃ€ÃŒÂ¶Ã³Â¸Ã© Â·ÃŽÂ±Ã—Â¸Â¦ Â³Â²Â±Ã¤Â´Ã™. 
			m_pGame->_bItemLog(DEF_ITEMLOG_DROP, iClientH, (int)-1, pItem);

			// Â´Ã™Â¸Â¥ Ã…Â¬Â¶Ã³Ã€ÃŒÂ¾Ã°Ã†Â®Â¿Â¡Â°Ã” Â¾Ã†Ã€ÃŒÃ…Ã›Ã€ÃŒ Â¶Â³Â¾Ã®ÃÃ¸ Â°ÃÃ€Â» Â¾Ã‹Â¸Â°Â´Ã™. 
			m_pGame->SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_ITEMDROP, m_pGame->m_pClientList[iClientH]->m_cMapIndex,
				dX, dY, pItem->m_sIDnum, 0, pItem->m_cItemColor, pItem->m_dwAttribute); // v1.4 color
			break;

		case DEF_MAGICTYPE_PROTECT:
			// ÂºÂ¸ÃˆÂ£ Â¸Â¶Â¹Ã½ 
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);

			// ÂºÂ¸ÃˆÂ£ Â»Ã³Ã…Ã‚Â¶Ã³Â´Ã‚ Â°ÃÃ€Â» Â¼Â³ÃÂ¤Ã‡ÃÂ±Ã¢ Ã€Ã¼Â¿Â¡ Ã€ÃŒÂ¹ÃŒ Ã‡Ã˜Â´Ã§ ÂºÂ¸ÃˆÂ£Â°Â¡ Â°Ã‰Â·ÃÃ€Ã–Â´Ã‚ÃÃ¶ ÃˆÂ®Ã€ÃŽÃ‡ÃÂ°Ã­ Â°Ã‰Â·ÃÃ€Ã–Â´Ã™Â¸Ã© Â¸Â¶Â¹Ã½Ã€Âº Â¹Â«Â½ÃƒÂµÃˆÂ´Ã™. 
			switch (cOwnerType) {
			case DEF_OWNERTYPE_PLAYER:
				if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
				if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] != 0) goto MAGIC_NOEFFECT;
				// v1.4334 ÃÃŸÂ¸Â³Ã€Âº Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â¿Â¡Â°Ã” Â¸Â¶Â¹Ã¦Ã€Â» Â¸Ã¸Ã‡ÃÂ°Ã” Â¼Ã¶ÃÂ¤
				if (memcmp(m_pGame->m_pClientList[iClientH]->m_cLocation, "NONE", 4) == 0) goto MAGIC_NOEFFECT;

				m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
				switch (m_pGame->m_pMagicConfigList[sType]->m_sValue4) {
				case 1:
					m_pGame->SetProtectionFromArrowFlag(sOwnerH, DEF_OWNERTYPE_PLAYER, true);
					break;
				case 2:
				case 5:
					m_pGame->SetMagicProtectionFlag(sOwnerH, DEF_OWNERTYPE_PLAYER, true);
					break;
				case 3:
				case 4:
					m_pGame->SetDefenseShieldFlag(sOwnerH, DEF_OWNERTYPE_PLAYER, true);
					break;
				}
				break;

			case DEF_OWNERTYPE_NPC:
				if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
				if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] != 0) goto MAGIC_NOEFFECT;
				// ÃÂ¤Ã€Ã» NPCÂµÃ©Ã€Âº ÂºÂ¸ÃˆÂ£ Â¸Â¶Â¹Ã½ Ã€Ã»Â¿Ã« Â¾ÃˆÂµÃŠ.				
				if (m_pGame->m_pNpcList[sOwnerH]->m_cActionLimit != 0) goto MAGIC_NOEFFECT;
				m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;

				switch (m_pGame->m_pMagicConfigList[sType]->m_sValue4) {
				case 1:
					m_pGame->SetProtectionFromArrowFlag(sOwnerH, DEF_OWNERTYPE_NPC, true);
					break;
				case 2:
				case 5:
					m_pGame->SetMagicProtectionFlag(sOwnerH, DEF_OWNERTYPE_NPC, true);
					break;
				case 3:
				case 4:
					m_pGame->SetDefenseShieldFlag(sOwnerH, DEF_OWNERTYPE_NPC, true);
					break;
				}
				break;
			}

			// ÂºÂ¸ÃˆÂ£ ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
			m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_PROTECT, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000),
				sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

			// ÃˆÂ¿Â°ÃºÂ°Â¡ Â»Ã½Â°Ã¥Ã€Â½Ã€Â» Â¾Ã‹Â·ÃÃÃ˜Â´Ã™.
			if (cOwnerType == DEF_OWNERTYPE_PLAYER)
				m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_PROTECT, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);
			break;

		case DEF_MAGICTYPE_SCAN:
			std::memset(cScanMessage, 0, sizeof(cScanMessage));
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					std::snprintf(cScanMessage, sizeof(cScanMessage), " Player: %s HP:%d MP:%d.", m_pGame->m_pClientList[sOwnerH]->m_cCharName, m_pGame->m_pClientList[sOwnerH]->m_iHP, m_pGame->m_pClientList[sOwnerH]->m_iMP);
					m_pGame->ShowClientMsg(iClientH, cScanMessage);
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					std::snprintf(cScanMessage, sizeof(cScanMessage), " NPC: %s HP:%d MP:%d", m_pGame->m_pNpcList[sOwnerH]->m_cNpcName, m_pGame->m_pNpcList[sOwnerH]->m_iHP, m_pGame->m_pNpcList[sOwnerH]->m_iMana);
					m_pGame->ShowClientMsg(iClientH, cScanMessage);
					break;
				}
				m_pGame->SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pGame->m_pClientList[iClientH]->m_cMapIndex,
					m_pGame->m_pClientList[iClientH]->m_sX, m_pGame->m_pClientList[iClientH]->m_sY, dX, dY, 10, (short)10);
			}
			break;

		case DEF_MAGICTYPE_HOLDOBJECT:
			// Â¿Ã€ÂºÃªÃÂ§Ã†Â®Ã€Ã‡ Â¿Ã²ÃÃ·Ã€Ã“Ã€Â» ÂºÃ€Â¼Ã¢Ã‡Ã‘Â´Ã™. 
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {

				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0) goto MAGIC_NOEFFECT;
					if (m_pGame->m_pClientList[sOwnerH]->m_iAddPR >= 500) goto MAGIC_NOEFFECT;
					// v1.4334 ÃÃŸÂ¸Â³Ã€Âº Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â¿Â¡Â°Ã” Ã†ÃÂ·Â²Ã€Â» Â¸Ã¸Ã‡ÃÂ°Ã” Â¼Ã¶ÃÂ¤
					if (memcmp(m_pGame->m_pClientList[iClientH]->m_cLocation, "NONE", 4) == 0) goto MAGIC_NOEFFECT;
					// 2002-09-10 #2 Â¾ÃˆÃ€Ã¼ÃÃ¶Â´Ã«(No-Attack-Area) Ã†ÃÂ·Â² Â¸Â¶Â¹Ã½ Â¾ÃˆÂµÃ‡Â°Ã” Ã‡Ã”
					if (cOwnerType == DEF_OWNERTYPE_PLAYER) {

						if (m_pGame->m_pMapList[m_pGame->m_pClientList[sOwnerH]->m_cMapIndex]->iGetAttribute(sX, sY, 0x00000006) != 0) goto MAGIC_NOEFFECT;
						if (m_pGame->m_pMapList[m_pGame->m_pClientList[sOwnerH]->m_cMapIndex]->iGetAttribute(dX, dY, 0x00000006) != 0) goto MAGIC_NOEFFECT;
					}

					// 2002-09-10 #3 Ã€Ã¼Â¸Ã©Ã€Ã¼Â½ÃƒÂ¿Ã Â¹ÃŒÂµÃ©Â·Â£ÂµÃ¥Â¿Â¡Â¼Â­Â¸Â¦ ÃÂ¦Â¿ÃœÃ‡ÃÂ°Ã­ Â°Â°Ã€Âº Ã†Ã­Â¿Â¡Â°Ã”Â´Ã‚ Ã†ÃÂ·Â² Â¾ÃˆÂµÃŠ
					if (strcmp(m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->m_cName, "middleland") != 0 &&
						m_pGame->m_bIsCrusadeMode == false &&
						m_pGame->m_pClientList[iClientH]->m_cSide == m_pGame->m_pClientList[sOwnerH]->m_cSide)
						goto MAGIC_NOEFFECT;

					m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicLevel >= 6) goto MAGIC_NOEFFECT; // v1.4 Â¸Â¶Â¹Ã½ Â·Â¹ÂºÂ§ 6Ã€ÃŒÂ»Ã³Ã€ÃŽ Â¸Â®Ã„Â¡Â±Ãž Ã€ÃŒÂ»Ã³Ã€Ã‡ Â¸Â¶Â¹Ã½ Â¸Ã³Â½ÂºÃ…ÃÂ¿Â¡Â°Ã”Â´Ã‚ Â¸Â¶ÂºÃ± Â¸Â¶Â¹Ã½ Ã…Ã«Ã‡ÃÃÃ¶ Â¾ÃŠÂ´Ã‚Â´Ã™.
					if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0) goto MAGIC_NOEFFECT;
					m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
					break;
				}

				// ÂºÂ¸ÃˆÂ£ ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
				m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_HOLDOBJECT, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000),
					sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				// ÃˆÂ¿Â°ÃºÂ°Â¡ Â»Ã½Â°Ã¥Ã€Â½Ã€Â» Â¾Ã‹Â·ÃÃÃ˜Â´Ã™.
				if (cOwnerType == DEF_OWNERTYPE_PLAYER)
					m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_HOLDOBJECT, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);
			}
			break;

		case DEF_MAGICTYPE_INVISIBILITY:
			switch (m_pGame->m_pMagicConfigList[sType]->m_sValue4) {
			case 1:
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);

				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if ((sOwnerH != iClientH) && ((memcmp(m_pGame->m_pClientList[iClientH]->m_cLocation, "elvhunter", 9) == 0) || (memcmp(m_pGame->m_pClientList[iClientH]->m_cLocation, "arehunter", 9) == 0)) && ((memcmp(m_pGame->m_pClientList[sOwnerH]->m_cLocation, "elvhunter", 9) != 0) || (memcmp(m_pGame->m_pClientList[sOwnerH]->m_cLocation, "arehunter", 9) != 0))) goto MAGIC_NOEFFECT;
					if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) goto MAGIC_NOEFFECT;
					if (memcmp(m_pGame->m_pClientList[iClientH]->m_cLocation, "NONE", 4) == 0) goto MAGIC_NOEFFECT;

					m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
					m_pGame->SetInvisibilityFlag(sOwnerH, cOwnerType, true);
					m_pGame->RemoveFromTarget(sOwnerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_INVISIBILITY);
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) goto MAGIC_NOEFFECT;

					if (m_pGame->m_pNpcList[sOwnerH]->m_cActionLimit == 0) {
						// Ã€ÃŒÂµÂ¿Ã‡ÃÃÃ¶ Â¾ÃŠÂ´Ã‚ NPCÂ´Ã‚ Ã…ÃµÂ¸Ã­ Â¸Â¶Â¹Ã½Ã€Â» Â°Ã‰ Â¼Ã¶ Â¾Ã¸Â´Ã™.
						m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
						m_pGame->SetInvisibilityFlag(sOwnerH, cOwnerType, true);
						// Ã€ÃŒ NPCÂ¸Â¦ ÃƒÃŸÃ€Ã»Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã¸ Â¸Ã³Â½ÂºÃ…ÃÂ¸Â¦ Ã‡Ã˜ÃÂ¦Â½ÃƒÃ…Â²Â´Ã™.
						m_pGame->RemoveFromTarget(sOwnerH, DEF_OWNERTYPE_NPC, DEF_MAGICTYPE_INVISIBILITY);
					}
					break;
				}

				// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
				m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_INVISIBILITY, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000),
					sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				if (cOwnerType == DEF_OWNERTYPE_PLAYER)
					m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_INVISIBILITY, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);
				break;

			case 2:
				// v1.4334 ÃÃŸÂ¸Â³Ã€Âº Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â¿Â¡Â°Ã” ÃÃŸÂµÂ¶Ã€Â» Â¸Ã¸Ã‡ÃÂ°Ã” Â¼Ã¶ÃÂ¤
				if (memcmp(m_pGame->m_pClientList[iClientH]->m_cLocation, "NONE", 4) == 0) goto MAGIC_NOEFFECT;
				if ((memcmp(m_pGame->m_pClientList[iClientH]->m_cLocation, "elvhunter", 9) == 0) || (memcmp(m_pGame->m_pClientList[iClientH]->m_cLocation, "arehunter", 9) == 0)) goto MAGIC_NOEFFECT;

				// dX, dY Â¹ÃÂ°Ã¦ 8 ÃÃ–ÂºÂ¯Ã€Ã‡ Invisibility Â»Ã³Ã…Ã‚Ã€ÃŽ ObjectÂ°Â¡ Ã€Ã–Ã€Â¸Â¸Ã© Ã‡Ã˜ÃÂ¦ Â½ÃƒÃ…Â²Â´Ã™.
				for (ix = dX - 8; ix <= dX + 8; ix++)
					for (iy = dY - 8; iy <= dY + 8; iy++) {
						m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
						if (sOwnerH != 0) {
							switch (cOwnerType) {
							case DEF_OWNERTYPE_PLAYER:
								if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) {
									m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = 0;
									m_pGame->SetInvisibilityFlag(sOwnerH, cOwnerType, false);
									m_pGame->bRemoveFromDelayEventList(sOwnerH, cOwnerType, DEF_MAGICTYPE_INVISIBILITY);
								}
								break;

							case DEF_OWNERTYPE_NPC:
								if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) {
									m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = 0;
									m_pGame->SetInvisibilityFlag(sOwnerH, cOwnerType, false);
									m_pGame->bRemoveFromDelayEventList(sOwnerH, cOwnerType, DEF_MAGICTYPE_INVISIBILITY);
								}
								break;
							}
						}
					}
				break;
			}
			break;

		case DEF_MAGICTYPE_CREATE_DYNAMIC:
			// Dynamic ObjectÂ¸Â¦ Â»Ã½Â¼ÂºÃ‡ÃÂ°Ã­ ÃˆÂ¿Â·Ã‚Ã€ÃŒ ÃÃ¶Â¼Ã“ÂµÃ‡Â´Ã‚ Ã…Â¸Ã€Ã”.

			// v2.1 Â¸Â¶Ã€Â» Â³Â»Â¿Â¡Â¼Â­Â´Ã‚ Ã‡ÃŠÂµÃ¥ Â¸Â¶Â¹Ã½ Â±ÃÃÃ¶(Ã€Ã¼Â¸Ã©Ã€Ã¼Â½Ãƒ ÃÂ¦Â¿Ãœ)
			if (m_pGame->m_bIsCrusadeMode == false) {
				if (strcmp(m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->m_cName, "aresden") == 0) return;
				if (strcmp(m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->m_cName, "elvine") == 0) return;
				// v2.14
				if (strcmp(m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->m_cName, "arefarm") == 0) return;
				if (strcmp(m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->m_cName, "elvfarm") == 0) return;
			}

			switch (m_pGame->m_pMagicConfigList[sType]->m_sValue10) {
			case DEF_DYNAMICOBJECT_PCLOUD_BEGIN: // ÂµÂ¶Â±Â¸Â¸Â§

			case DEF_DYNAMICOBJECT_FIRE:   // Fire Ã€ÃŒÂ´Ã™.
			case DEF_DYNAMICOBJECT_SPIKE:  // Spike

#ifdef DEF_TAIWANLOG 
				short sTemp_X, sTemp_Y;
				// v2.15 Â¸Â¶Â¹Ã½Ã€Â» Â»Ã§Â¿Ã«Ã‡Ã‘ Ã€Â§Ã„Â¡Â¸Â¦ Ã‡Â¥Â½ÃƒÃ‡ÃÂ±Ã¢ Ã€Â§Ã‡Ã‘ ÂºÂ¯Â¼Ã¶
				sTemp_X = m_pGame->m_pClientList[iClientH]->m_sX;
				sTemp_Y = m_pGame->m_pClientList[iClientH]->m_sY;

				m_pGame->m_pClientList[iClientH]->m_sX = dX;
				m_pGame->m_pClientList[iClientH]->m_sY = dY;

				m_pGame->_bItemLog(DEF_ITEMLOG_SPELLFIELD, iClientH, m_pGame->m_pMagicConfigList[sType]->m_cName, 0);

				m_pGame->m_pClientList[iClientH]->m_sX = sTemp_X;
				m_pGame->m_pClientList[iClientH]->m_sY = sTemp_Y;
#endif

				switch (m_pGame->m_pMagicConfigList[sType]->m_sValue11) {
				case 1:
					// wall - type
					cDir = CMisc::cGetNextMoveDir(m_pGame->m_pClientList[iClientH]->m_sX, m_pGame->m_pClientList[iClientH]->m_sY, dX, dY);
					switch (cDir) {
					case 1:	rx = 1; ry = 0;   break;
					case 2: rx = 1; ry = 1;   break;
					case 3: rx = 0; ry = 1;   break;
					case 4: rx = -1; ry = 1;  break;
					case 5: rx = 1; ry = 0;   break;
					case 6: rx = -1; ry = -1; break;
					case 7: rx = 0; ry = -1;  break;
					case 8: rx = 1; ry = -1;  break;
					}

					m_pGame->iAddDynamicObjectList(iClientH, DEF_OWNERTYPE_PLAYER_INDIRECT, m_pGame->m_pMagicConfigList[sType]->m_sValue10, m_pGame->m_pClientList[iClientH]->m_cMapIndex,
						dX, dY, m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000);

					m_pGame->bAnalyzeCriminalAction(iClientH, dX, dY);

					for (i = 1; i <= m_pGame->m_pMagicConfigList[sType]->m_sValue12; i++) {
						m_pGame->iAddDynamicObjectList(iClientH, DEF_OWNERTYPE_PLAYER_INDIRECT, m_pGame->m_pMagicConfigList[sType]->m_sValue10, m_pGame->m_pClientList[iClientH]->m_cMapIndex,
							dX + i * rx, dY + i * ry, m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000);
						m_pGame->bAnalyzeCriminalAction(iClientH, dX + i * rx, dY + i * ry);

						m_pGame->iAddDynamicObjectList(iClientH, DEF_OWNERTYPE_PLAYER_INDIRECT, m_pGame->m_pMagicConfigList[sType]->m_sValue10, m_pGame->m_pClientList[iClientH]->m_cMapIndex,
							dX - i * rx, dY - i * ry, m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000);
						m_pGame->bAnalyzeCriminalAction(iClientH, dX - i * rx, dY - i * ry);
					}
					break;

				case 2:
					// Field - Type
					bool bFlag = false;
					int cx, cy;
					for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue12; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue12; ix++)
						for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue12; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue12; iy++) {
							m_pGame->iAddDynamicObjectList(iClientH, DEF_OWNERTYPE_PLAYER_INDIRECT, m_pGame->m_pMagicConfigList[sType]->m_sValue10, m_pGame->m_pClientList[iClientH]->m_cMapIndex,
								ix, iy, m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000, m_pGame->m_pMagicConfigList[sType]->m_sValue5);

							// Â¸Â¸Â¾Ã  Â¸Â¶Ã€Â»Â¿Â¡Â¼Â­ Ã‡ÃŠÂµÃ¥Â¸Â¦ Â±Ã± Â°Ã·Â¿Â¡ Â¹Â«Â°Ã­Ã‡Ã‘ Ã€ÃšÂ°Â¡ Ã€Ã–Â¾ÃºÂ´Ã™Â¸Ã© Â°Ã¸Â°ÃÃ€ÃšÂ´Ã‚ Â°Â¡ÂµÃ¥Ã€Ã‡ Â°Ã¸Â°ÃÃ€Â» Â¹ÃžÂ°Ã” ÂµÃˆÂ´Ã™. 
							if (m_pGame->bAnalyzeCriminalAction(iClientH, ix, iy, true)) {
								bFlag = true;
								cx = ix;
								cy = iy;
							}
						}
					// Ã‡ÃŠÂµÃ¥Ã€ÃŽ Â°Ã¦Â¿Ã¬ Â°Ã¦ÂºÃ±Â¸Â¦ 1Â¸Ã­Â¸Â¸ Â¼Ã’ÃˆÂ¯Ã‡ÃÂ±Ã¢ Ã€Â§Ã‡Ã”.
					if (bFlag) m_pGame->bAnalyzeCriminalAction(iClientH, cx, cy);
					break;
				}
				//
				break;

			case DEF_DYNAMICOBJECT_ICESTORM:
				// Ice-Storm Dynamic Object 
				m_pGame->iAddDynamicObjectList(iClientH, DEF_OWNERTYPE_PLAYER_INDIRECT, m_pGame->m_pMagicConfigList[sType]->m_sValue10, m_pGame->m_pClientList[iClientH]->m_cMapIndex,
					dX, dY, m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000,
					m_pGame->m_pClientList[iClientH]->m_cSkillMastery[4]);
				break;

			default:
				break;
			}
			break;

		case DEF_MAGICTYPE_POSSESSION:
			// Â¿Ã¸Â°Ã…Â¸Â®Â¿Â¡ Â¶Â³Â¾Ã®ÃÂ® Ã€Ã–Â´Ã‚ Â¹Â°Â°Ã‡Ã€Â» ÃÃ½Â¾Ã®Â¿Ã€Â´Ã‚ Â¸Â¶Â¹Ã½Ã€ÃŒÂ´Ã™. 
			// v2.12 ÃÃŸÂ¸Â³Ã€Âº Ã†Ã·ÃÂ¦Â¼Ã‡ Â¸Â¶Â¹Ã½ Â»Ã§Â¿Ã« ÂºÃ’Â°Â¡ 
			if (m_pGame->m_pClientList[iClientH]->m_cSide == 0) goto MAGIC_NOEFFECT;

			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (sOwnerH != 0) break; // v1.41 Ã†Ã·ÃÂ¦Â¼Ã‡ Â¸Â¶Â¹Ã½Ã€Âº Â»Ã§Â¶Ã·Ã€ÃŒ Â¼Â­ Ã€Ã–Â´Ã‚ Ã€Â§Â¿Â¡Â´Ã‚ ÃˆÂ¿Â·Ã‚Ã€ÃŒ Â¾Ã¸Â´Ã™. 

			pItem = m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->pGetItem(dX, dY, &sIDNum, &cRemainItemColor, &dwAttr);
			if (pItem != 0) {
				// Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â°Â¡ Â¾Ã†Ã€ÃŒÃ…Ã›Ã€Â» ÃˆÂ¹ÂµÃ¦Ã‡ÃÂ¿Â´Â´Ã™. 
				if (m_pGame->_bAddClientItemList(iClientH, pItem, &iEraseReq)) {
					// Â¾Ã†Ã€ÃŒÃ…Ã›Ã€Â» ÃˆÂ¹ÂµÃ¦Ã‡ÃŸÂ´Ã™.

					// v1.411 Â·ÃŽÂ±Ã— Â³Â²Â±Ã¤Â´Ã™.
					m_pGame->_bItemLog(DEF_ITEMLOG_GET, iClientH, (int)-1, pItem);

					iRet = m_pGame->SendItemNotifyMsg(iClientH, DEF_NOTIFY_ITEMOBTAINED, pItem, 0);

					switch (iRet) {
					case DEF_XSOCKEVENT_QUENEFULL:
					case DEF_XSOCKEVENT_SOCKETERROR:
					case DEF_XSOCKEVENT_CRITICALERROR:
					case DEF_XSOCKEVENT_SOCKETCLOSED:
						// Â¸ÃžÂ½ÃƒÃÃ¶Â¸Â¦ ÂºÂ¸Â³Â¾Â¶Â§ Â¿Â¡Â·Â¯Â°Â¡ Â¹ÃŸÂ»Ã½Ã‡ÃŸÂ´Ã™Â¸Ã© ÃÂ¦Â°Ã…Ã‡Ã‘Â´Ã™.
						m_pGame->DeleteClient(iClientH, true, true);
						return;
					}
				}
				else
				{
					// Â°Ã¸Â°Â£Ã€ÃŒ ÂºÃŽÃÂ·Ã‡ÃÂ°Ã…Â³Âª Ã‡Ã‘Â°Ã¨ÃÃŸÂ·Â®Ã€Â» ÃƒÃŠÂ°ÃºÃ‡ÃŸÂ´Ã™. Â¾Ã†Ã€ÃŒÃ…Ã›Ã€Â» Â¾Ã²Ã€Â» Â¼Ã¶ Â¾Ã¸Â´Ã™.

					// Â°Â¡ÃÂ®Â¿Ã”Â´Ã¸ Â¾Ã†Ã€ÃŒÃ…Ã›Ã€Â» Â¿Ã¸Â»Ã³ÃˆÂ¸ÂºÂ¹Â½ÃƒÃ…Â²Â´Ã™. 
					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->bSetItem(dX, dY, pItem);

					iRet = m_pGame->SendItemNotifyMsg(iClientH, DEF_NOTIFY_CANNOTCARRYMOREITEM, 0, 0);


					switch (iRet) {
					case DEF_XSOCKEVENT_QUENEFULL:
					case DEF_XSOCKEVENT_SOCKETERROR:
					case DEF_XSOCKEVENT_CRITICALERROR:
					case DEF_XSOCKEVENT_SOCKETCLOSED:
						// Â¸ÃžÂ½ÃƒÃÃ¶Â¸Â¦ ÂºÂ¸Â³Â¾Â¶Â§ Â¿Â¡Â·Â¯Â°Â¡ Â¹ÃŸÂ»Ã½Ã‡ÃŸÂ´Ã™Â¸Ã© ÃÂ¦Â°Ã…Ã‡Ã‘Â´Ã™.
						m_pGame->DeleteClient(iClientH, true, true);
						return;
					}
				}
			}
			//
			break;

		case DEF_MAGICTYPE_CONFUSE:
			// if the caster side is the same as the targets side, no effect occurs
			switch (m_pGame->m_pMagicConfigList[sType]->m_sValue4) {
			case 1: // confuse LanguageÃ¬ÂÂ´Ã«â€¹Â¤. 
			case 2: // Confusion, Mass Confusion 	
				for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
					for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
						// Ã¬Å¾ÂÃ¬â€¹Â Ã«Ââ€ž Ã­â€Â¼Ã­ÂÂ­Ã«ÂÂ  Ã¬Ë†Ëœ Ã¬Å¾Ë†Ã¬Å“Â¼Ã«â€¹Ë† Ã¬Â£Â¼Ã¬ÂËœ.
						m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
						if (cOwnerType == DEF_OWNERTYPE_PLAYER) {
							// Ã­â€¢Â´Ã«â€¹Â¹ Ã¬Å“â€žÃ¬Â¹ËœÃ¬â€”Â Ã¬ÂºÂÃ«Â¦Â­Ã­â€žÂ°ÃªÂ°â‚¬ Ã¬Å¾Ë†Ã«â€¹Â¤.
							if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if ((m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) && (m_pGame->m_pClientList[iClientH]->m_cSide != m_pGame->m_pClientList[sOwnerH]->m_cSide)) {
								// Ã¬Æ’ÂÃ«Å’â‚¬Ã«Â°Â©Ã¬ÂÂ´ Ã«Â§Ë†Ã«Â²â€¢ Ã¬Â â‚¬Ã­â€¢Â­Ã¬â€”Â Ã¬â€¹Â¤Ã­Å’Â¨Ã­â€“Ë†Ã«â€¹Â¤.
								if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_CONFUSE] != 0) break; //Ã¬ÂÂ´Ã«Â¯Â¸ Ã«â€¹Â¤Ã«Â¥Â¸ ConfuseÃ­Å¡Â¨ÃªÂ³Â¼ÃªÂ°â‚¬ Ã¬Å¾Ë†Ã«â€¹Â¤Ã«Â©Â´ Ã«Â¬Â´Ã¬â€¹Å“Ã«ÂÅ“Ã«â€¹Â¤.
								m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_CONFUSE] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;

								// Ã­Å¡Â¨ÃªÂ³Â¼ÃªÂ°â‚¬ Ã­â€¢Â´Ã¬Â Å“Ã«ÂÂ  Ã«â€¢Å’ Ã«Â°Å“Ã¬Æ’ÂÃ­â€¢Â  Ã«â€Å“Ã«Â Ë†Ã¬ÂÂ´ Ã¬ÂÂ´Ã«Â²Â¤Ã­Å Â¸Ã«Â¥Â¼ Ã«â€œÂ±Ã«Â¡ÂÃ­â€¢Å“Ã«â€¹Â¤.
								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_CONFUSE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

								// Ã«Â§Ë†Ã«Â²â€¢Ã¬â€”Â ÃªÂ±Â¸Ã«Â Â¸Ã¬ÂÅ’Ã¬Ââ€ž Ã¬â€¢Å’Ã«Â¦Â°Ã«â€¹Â¤.
								m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_CONFUSE, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);
							}
						}
					}
				break;

			case 3: // Ilusion, Mass-Ilusion
				for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
					for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
						// Ã¬Å¾ÂÃ¬â€¹Â Ã«Ââ€ž Ã­â€Â¼Ã­ÂÂ­Ã«ÂÂ  Ã¬Ë†Ëœ Ã¬Å¾Ë†Ã¬Å“Â¼Ã«â€¹Ë† Ã¬Â£Â¼Ã¬ÂËœ.
						m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
						if (cOwnerType == DEF_OWNERTYPE_PLAYER) {
							// Ã­â€¢Â´Ã«â€¹Â¹ Ã¬Å“â€žÃ¬Â¹ËœÃ¬â€”Â Ã¬ÂºÂÃ«Â¦Â­Ã­â€žÂ°ÃªÂ°â‚¬ Ã¬Å¾Ë†Ã«â€¹Â¤.
							if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if ((m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) && (m_pGame->m_pClientList[iClientH]->m_cSide != m_pGame->m_pClientList[sOwnerH]->m_cSide)) {
								// Ã¬Æ’ÂÃ«Å’â‚¬Ã«Â°Â©Ã¬ÂÂ´ Ã«Â§Ë†Ã«Â²â€¢ Ã¬Â â‚¬Ã­â€¢Â­Ã¬â€”Â Ã¬â€¹Â¤Ã­Å’Â¨Ã­â€“Ë†Ã«â€¹Â¤.
								if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_CONFUSE] != 0) break; //Ã¬ÂÂ´Ã«Â¯Â¸ Ã«â€¹Â¤Ã«Â¥Â¸ ConfuseÃ­Å¡Â¨ÃªÂ³Â¼ÃªÂ°â‚¬ Ã¬Å¾Ë†Ã«â€¹Â¤Ã«Â©Â´ Ã«Â¬Â´Ã¬â€¹Å“Ã«ÂÅ“Ã«â€¹Â¤.
								m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_CONFUSE] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;

								switch (m_pGame->m_pMagicConfigList[sType]->m_sValue4) {
								case 3:
									m_pGame->SetIllusionFlag(sOwnerH, DEF_OWNERTYPE_PLAYER, true);
									break;
								}

								// Ã­Å¡Â¨ÃªÂ³Â¼ÃªÂ°â‚¬ Ã­â€¢Â´Ã¬Â Å“Ã«ÂÂ  Ã«â€¢Å’ Ã«Â°Å“Ã¬Æ’ÂÃ­â€¢Â  Ã«â€Å“Ã«Â Ë†Ã¬ÂÂ´ Ã¬ÂÂ´Ã«Â²Â¤Ã­Å Â¸Ã«Â¥Â¼ Ã«â€œÂ±Ã«Â¡ÂÃ­â€¢Å“Ã«â€¹Â¤.
								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_CONFUSE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

								// Ã«Â§Ë†Ã«Â²â€¢Ã¬â€”Â ÃªÂ±Â¸Ã«Â Â¸Ã¬ÂÅ’Ã¬Ââ€ž Ã¬â€¢Å’Ã«Â¦Â°Ã«â€¹Â¤.
								m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_CONFUSE, m_pGame->m_pMagicConfigList[sType]->m_sValue4, iClientH, 0);
							}
						}
					}
				break;

			case 4: // Ilusion Movement
				if (m_pGame->m_pClientList[iClientH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) break;
				for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
					for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
						m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
						if (cOwnerType == DEF_OWNERTYPE_PLAYER) {
							if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if ((m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) && (m_pGame->m_pClientList[iClientH]->m_cSide != m_pGame->m_pClientList[sOwnerH]->m_cSide)) {
								if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_CONFUSE] != 0) break;
								m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_CONFUSE] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
								switch (m_pGame->m_pMagicConfigList[sType]->m_sValue4) {
								case 4:
									m_pGame->SetIllusionMovementFlag(sOwnerH, DEF_OWNERTYPE_PLAYER, true);
									break;
								}

								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_CONFUSE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

								m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_CONFUSE, m_pGame->m_pMagicConfigList[sType]->m_sValue4, iClientH, 0);
							}
						}
					}
			}
			break;


		case DEF_MAGICTYPE_POISON:
			// ÃÃŸÂµÂ¶ Â¸Â¶Â¹Ã½. Â¸Ã•Ã€Ãº Â¸Â¶Â¹Ã½ Ã€ÃºÃ‡Ã—Ã€Â» Â±Â¼Â¸Â®Â°Ã­ Â´Ã™Ã€Â½Ã€Â¸Â·ÃŽ ÂµÂ¶Â¼ÂºÃ€ÃºÃ‡Ã—Ã€Â» Ã‡Ã‘Â¹Ã¸ Â´Ãµ Â±Â¼Â¸Â°Â´Ã™. 
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);

			if (m_pGame->m_pMagicConfigList[sType]->m_sValue4 == 1) {
				// ÃÃŸÂµÂ¶Ã€Â» Â°Ã…Â´Ã‚ Â¸Â¶Â¹Ã½ 
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					// v1.4334 ÃÃŸÂ¸Â³Ã€Âº Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â¿Â¡Â°Ã” ÃÃŸÂµÂ¶Ã€Â» Â¸Ã¸Ã‡ÃÂ°Ã” Â¼Ã¶ÃÂ¤
					if (memcmp(m_pGame->m_pClientList[iClientH]->m_cLocation, "NONE", 4) == 0) goto MAGIC_NOEFFECT;

					// Â¹Ã¼ÃÃ‹Ã‡Ã Ã€Â§Â¶Ã³Â¸Ã© 
					m_pGame->bAnalyzeCriminalAction(iClientH, dX, dY);

					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						// Â¸Â¶Â¹Ã½ Ã€ÃºÃ‡Ã—Â¿Â¡ Â½Ã‡Ã†ÃÃ‡ÃŸÂ´Ã™. ÂµÂ¶Â¼ÂºÃ€ÃºÃ‡Ã—Ã€Â» Â°Ã¨Â»ÃªÃ‡Ã‘Â´Ã™.
						if (m_pGame->bCheckResistingPoisonSuccess(sOwnerH, cOwnerType) == false) {
							// ÃÃŸÂµÂ¶ÂµÃ‡Â¾ÃºÂ´Ã™.
							m_pGame->m_pClientList[sOwnerH]->m_bIsPoisoned = true;
							m_pGame->m_pClientList[sOwnerH]->m_iPoisonLevel = m_pGame->m_pMagicConfigList[sType]->m_sValue5;
							m_pGame->m_pClientList[sOwnerH]->m_dwPoisonTime = dwTime;
							// 05/06/2004 - Hypnotoad - poison aura appears when cast Poison
							m_pGame->SetPoisonFlag(sOwnerH, cOwnerType, true);
							// ÃÃŸÂµÂ¶ÂµÃ‡Â¾ÃºÃ€Â½Ã€Â» Â¾Ã‹Â¸Â°Â´Ã™. 
							m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_POISON, m_pGame->m_pMagicConfigList[sType]->m_sValue5, 0, 0);
#ifdef DEF_TAIWANLOG
							m_pGame->_bItemLog(DEF_ITEMLOG_POISONED, sOwnerH, (char*)0, 0);
#endif
						}
					}
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (m_pGame->m_pNpcList[sOwnerH]->m_iHP > 0) goto MAGIC_NOEFFECT;
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						// Â¸Â¶Â¹Ã½ Ã€ÃºÃ‡Ã—Â¿Â¡ Â½Ã‡Ã†ÃÃ‡ÃŸÂ´Ã™. ÂµÂ¶Â¼ÂºÃ€ÃºÃ‡Ã—Ã€Â» Â°Ã¨Â»ÃªÃ‡Ã‘Â´Ã™.
						if (m_pGame->bCheckResistingPoisonSuccess(sOwnerH, cOwnerType) == false) {
							// ÃÃŸÂµÂ¶ÂµÃ‡Â¾ÃºÂ´Ã™.

						}
					}
					break;
				}
			}
			else if (m_pGame->m_pMagicConfigList[sType]->m_sValue4 == 0) {
				// ÃÃŸÂµÂ¶Ã€Â» Ã‡ÂªÂ´Ã‚ Â¸Â¶Â¹Ã½ 
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;

					if (m_pGame->m_pClientList[sOwnerH]->m_bIsPoisoned) {
						// ÃÃŸÂµÂ¶ÂµÃˆ Â»Ã³Ã…Ã‚Â¿Â´Â´Ã™Â¸Ã© ÃÃŸÂµÂ¶Ã€Â» Ã‡Â¬Â´Ã™.
						m_pGame->m_pClientList[sOwnerH]->m_bIsPoisoned = false;
						// 05/06/2004 - Hypnotoad - poison aura removed when cure cast
						m_pGame->SetPoisonFlag(sOwnerH, cOwnerType, false);
						// ÃÃŸÂµÂ¶Ã€ÃŒ Ã‡Â®Â·ÃˆÃ€Â½Ã€Â» Â¾Ã‹Â¸Â°Â´Ã™. 
						m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTOFF, DEF_MAGICTYPE_POISON, 0, 0, 0);
					}
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					break;
				}
			}
			break;

		case DEF_MAGICTYPE_BERSERK:
			switch (m_pGame->m_pMagicConfigList[sType]->m_sValue4) {
			case 1:
				// Â¹Ã¶Â¼Â­Ã„Â¿ Â¸Ã°ÂµÃ¥Â·ÃŽ Ã€Ã¼ÃˆÂ¯ÂµÃˆÂ´Ã™.
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);

				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_BERSERK] != 0) goto MAGIC_NOEFFECT;
					m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_BERSERK] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
					m_pGame->SetBerserkFlag(sOwnerH, cOwnerType, true);
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_BERSERK] != 0) goto MAGIC_NOEFFECT;
					// ÃÂ¤Ã€Ã» NPCÂµÃ©Ã€Âº Â±Â¤ÂºÃ Â¾ÃˆÂµÃŠ				
					if (m_pGame->m_pNpcList[sOwnerH]->m_cActionLimit != 0) goto MAGIC_NOEFFECT;
					// 2002-09-11 #3 Ã€Ã» Â¸Ã³Â½ÂºÃ…ÃÂ´Ã‚ Â±Â¤ÂºÃÂµÃ‡ÃÃ¶ Â¾ÃŠÃ€Â½
					if (m_pGame->m_pClientList[iClientH]->m_cSide != m_pGame->m_pNpcList[sOwnerH]->m_cSide) goto MAGIC_NOEFFECT;

					m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_BERSERK] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
					m_pGame->SetBerserkFlag(sOwnerH, cOwnerType, true);
					break;
				}

				// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
				m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_BERSERK, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000),
					sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				if (cOwnerType == DEF_OWNERTYPE_PLAYER)
					m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_BERSERK, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);
				break;
			}
			break;

			// v2.16 2002-5-23 Â°Ã­Â±Â¤Ã‡Ã¶ Â¼Ã¶ÃÂ¤
		case DEF_MAGICTYPE_DAMAGE_AREA_ARMOR_BREAK:
			// ÃÃ–ÂºÂ¯ Â°Ã¸Â°Ã ÃˆÂ¿Â°Ãº 
			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// Ã€ÃšÂ½Ã…ÂµÂµ Ã‡Ã‡Ã†Ã¸ÂµÃ‰ Â¼Ã¶ Ã€Ã–Ã€Â¸Â´Ã ÃÃ–Ã€Ã‡.
					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// Â¹Ã¦Â¾Ã®Â±Â¸Ã€Ã‡ Â¼Ã¶Â¸Ã­Ã€Â» ÃÃ™Ã€ÃŽÂ´Ã™.
						m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
					}

					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
						(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
						// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
							// Â¹Ã¦Â¾Ã®Â±Â¸Ã€Ã‡ Â¼Ã¶Â¸Ã­Ã€Â» ÃÃ™Ã€ÃŽÂ´Ã™.
							m_pGame->ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue10);
						}
					}
				}
			break;

			// Resurrection Magic. 
		case DEF_MAGICTYPE_RESURRECTION:
			// 10 Mins once
			if (m_pGame->m_pClientList[iClientH]->m_iSpecialAbilityTime != 0) goto MAGIC_NOEFFECT;
			m_pGame->m_pClientList[iClientH]->m_iSpecialAbilityTime = DEF_SPECABLTYTIMESEC / 2;
			// Get the ID of the dead Player/NPC on coords dX, dY. 
			m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			switch (cOwnerType) {
				// For Player. 
			case DEF_OWNERTYPE_PLAYER:
				// The Player has to exist. 
				if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
				// Resurrection is not for alive Players. 
				if (m_pGame->m_pClientList[sOwnerH]->m_bIsKilled == false) goto MAGIC_NOEFFECT;
				// Set Deadflag to Alive. 
				m_pGame->m_pClientList[sOwnerH]->m_bIsKilled = false;
				// Player's HP becomes half of the Max HP. 
				m_pGame->m_pClientList[sOwnerH]->m_iHP = ((m_pGame->m_pClientList[sOwnerH]->m_iLevel * 2) + (m_pGame->m_pClientList[sOwnerH]->m_iVit * 3) + ((m_pGame->m_pClientList[sOwnerH]->m_iStr + m_pGame->m_pClientList[sOwnerH]->m_iAngelicStr) / 2)) / 2;
				// Send new HP to Player. 
				m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_HP, 0, 0, 0, 0);
				// Make Player stand up. (Currently, by a fake damage). 
				m_pGame->m_pMapList[m_pGame->m_pClientList[sOwnerH]->m_cMapIndex]->ClearDeadOwner(dX, dY);
				m_pGame->m_pMapList[m_pGame->m_pClientList[sOwnerH]->m_cMapIndex]->SetOwner(sOwnerH, DEF_OWNERTYPE_PLAYER, dX, dY);
				m_pGame->SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, 0, 0, 0);
				m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_HP, 0, 0, 0, 0);
				break;
				// Resurrection is not for NPC's. 
			case DEF_OWNERTYPE_NPC:
				goto MAGIC_NOEFFECT;
				break;
			}
			break;

		case DEF_MAGICTYPE_ICE:
			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {

					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						// Â´Ã«Â¹ÃŒÃÃ¶Â¿Ã Ã‡Ã”Â²Â²
						//m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						m_pGame->Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						// Â¾Ã³Â¾Ã®Â¼Â­ ÂµÂ¿Ã€Ã›Ã€ÃŒ Â´ÃŠÂ¾Ã®ÃÃ¶Â´Ã‚ ÃˆÂ¿Â°Ãº
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pGame->m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// Ã…Â¸Â°Ã™Ã€ÃŒ Â»Ã¬Â¾Ã†Ã€Ã–Â°Ã­ Â¾Ã³Ã€Â½ Ã€ÃºÃ‡Ã—Â¿Â¡ Â½Ã‡Ã†ÃÃ‡ÃŸÂ´Ã™Â¸Ã© Â¾Ã³Â¾Ã®ÂºÃ™Â´Ã‚Â´Ã™.
							if ((m_pGame->m_pClientList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
									// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
									m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									// Â´Ã«Â»Ã³Ã€ÃŒ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Ã€ÃŽ Â°Ã¦Â¿Ã¬ Â¾Ã‹Â·ÃÃÃ˜Â´Ã™.
									m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pGame->m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if ((m_pGame->m_pNpcList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pGame->m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
									// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
									m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}

					}

					m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
						(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
						// ÃÃ—Ã€Âº ÃƒÂ´Ã‡ÃÂ°Ã­ Ã€Ã–Â´Ã‚ Ã‡ÃƒÂ·Â¹Ã€ÃŒÂ¾Ã®Â´Ã™.
						if (m_pGame->bCheckResistingMagicSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {

							//m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							m_pGame->Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							// Â¾Ã³Â¾Ã®Â¼Â­ ÂµÂ¿Ã€Ã›Ã€ÃŒ Â´ÃŠÂ¾Ã®ÃÃ¶Â´Ã‚ ÃˆÂ¿Â°Ãº. ÃÃ—ÃÃ¶ Â¾ÃŠÂ¾Ã’Ã€Â¸Â¸Ã© Ã€Ã»Â¿Ã« 
							if ((m_pGame->m_pClientList[sOwnerH]->m_iHP > 0) && (m_pGame->bCheckResistingIceSuccess(m_pGame->m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									m_pGame->SetIceFlag(sOwnerH, cOwnerType, true);
									// ÃˆÂ¿Â°ÃºÂ°Â¡ Ã‡Ã˜ÃÂ¦ÂµÃ‰ Â¶Â§ Â¹ÃŸÂ»Ã½Ã‡Ã’ ÂµÃ´Â·Â¹Ã€ÃŒ Ã€ÃŒÂºÂ¥Ã†Â®Â¸Â¦ ÂµÃ®Â·ÃÃ‡Ã‘Â´Ã™.
									m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);

									m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
						}
					}
				}
			break;

		default:
			break;
		}
	}
	else {
		// Casting ÃˆÃ„ ÂµÃ´Â·Â¹Ã€ÃŒÂ°Â¡ Â°Ã‰Â¸Â®Â´Ã‚ Â¸Â¶Â¹Ã½
		// Resurrection wand(MS.10) or Resurrection wand(MS.20)

		if (m_pGame->m_pMagicConfigList[sType]->m_sType == DEF_MAGICTYPE_RESURRECTION) {
			//Check if player has resurrection wand
			if (m_pGame->m_pClientList[iClientH] != 0 && m_pGame->m_pClientList[iClientH]->m_iSpecialAbilityTime == 0 &&
				m_pGame->m_pClientList[iClientH]->m_bIsSpecialAbilityEnabled == false) {
				m_pGame->m_pMapList[m_pGame->m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
				if (m_pGame->m_pClientList[sOwnerH] != 0) {
					// GM's can ressurect ne1, and players must be on same side to ressurect

					if ((m_pGame->m_pClientList[iClientH]->m_iAdminUserLevel < 1) &&
						(m_pGame->m_pClientList[sOwnerH]->m_cSide != m_pGame->m_pClientList[iClientH]->m_cSide)) {
						return;
					}
					if (cOwnerType == DEF_OWNERTYPE_PLAYER && m_pGame->m_pClientList[sOwnerH] != 0 &&
						m_pGame->m_pClientList[sOwnerH]->m_iHP <= 0) {
						m_pGame->m_pClientList[sOwnerH]->m_bIsBeingResurrected = true;
						m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_RESURRECTPLAYER, 0, 0, 0, 0);
						if (m_pGame->m_pClientList[iClientH]->m_iAdminUserLevel < 2) {
							m_pGame->m_pClientList[iClientH]->m_bIsSpecialAbilityEnabled = true;
							m_pGame->m_pClientList[iClientH]->m_dwSpecialAbilityStartTime = dwTime;
							m_pGame->m_pClientList[iClientH]->m_iSpecialAbilityLastSec = 0;
							m_pGame->m_pClientList[iClientH]->m_iSpecialAbilityTime = m_pGame->m_pMagicConfigList[sType]->m_dwDelayTime;

							sTemp = m_pGame->m_pClientList[iClientH]->m_sAppr4;
							sTemp = 0xFF0F & sTemp;
							sTemp = sTemp | 0x40;
							m_pGame->m_pClientList[iClientH]->m_sAppr4 = sTemp;
						}
						m_pGame->SendNotifyMsg(0, iClientH, DEF_NOTIFY_SPECIALABILITYSTATUS, 1, m_pGame->m_pClientList[iClientH]->m_iSpecialAbilityType, m_pGame->m_pClientList[iClientH]->m_iSpecialAbilityLastSec, 0);
						m_pGame->SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
					}
				}
			}
		}
	}

MAGIC_NOEFFECT:

	if (m_pGame->m_pClientList[iClientH] == 0) return;

	//Mana Slate
	if ((m_pGame->m_pClientList[iClientH]->m_iStatus & 0x800000) != 0) {
		iManaCost = 0;
	}

	// ManaÂ¸Â¦ Â°Â¨Â¼Ã’Â½ÃƒÃ…Â°Â°Ã­ Ã…Ã«ÂºÂ¸Ã‡Ã‘Â´Ã™.
	m_pGame->m_pClientList[iClientH]->m_iMP -= iManaCost; // sValue1Ã€ÃŒ Mana Cost
	if (m_pGame->m_pClientList[iClientH]->m_iMP < 0)
		m_pGame->m_pClientList[iClientH]->m_iMP = 0;

	m_pGame->CalculateSSN_SkillIndex(iClientH, 4, 1);

	m_pGame->SendNotifyMsg(0, iClientH, DEF_NOTIFY_MP, 0, 0, 0, 0);

	// Â¸Â¶Â¹Ã½ ÃˆÂ¿Â°ÃºÂ¸Â¦ Â´Ã™Â¸Â¥ Ã…Â¬Â¶Ã³Ã€ÃŒÂ¾Ã°Ã†Â®Â¿Â¡Â°Ã” Ã€Ã¼Â¼Ã›Ã‡Ã‘Â´Ã™. Â¸Â¶Â¹Ã½Â¹Ã¸ÃˆÂ£ + 100Ã€ÃŒ Â¿Â¡Ã†Ã¥Ã†Â® Â¹Ã¸ÃˆÂ£ 
	m_pGame->SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pGame->m_pClientList[iClientH]->m_cMapIndex,
		m_pGame->m_pClientList[iClientH]->m_sX, m_pGame->m_pClientList[iClientH]->m_sY, dX, dY, (sType + 100), m_pGame->m_pClientList[iClientH]->m_sType);

}





