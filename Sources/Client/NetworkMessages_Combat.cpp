#include "Game.h"
#include "NetworkMessageManager.h"
#include "Packet/SharedPackets.h"
#include "lan_eng.h"
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <cmath>

namespace NetworkMessageHandlers {
	void HandleKilled(CGame* pGame, char* pData)
	{
		char cAttackerName[21];
		pGame->m_bCommandAvailable = false;
		pGame->m_cCommand = DEF_OBJECTSTOP;
		pGame->m_iHP = 0;
		pGame->m_cCommand = -1;
		// Restart
		pGame->m_bItemUsingStatus = false;
		pGame->ClearSkillUsingStatus();
		std::memset(cAttackerName, 0, sizeof(cAttackerName));
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyKilled>(
			pData, sizeof(hb::net::PacketNotifyKilled));
		if (!pkt) return;
		memcpy(cAttackerName, pkt->attacker_name, 20);
		pGame->AddEventList(NOTIFYMSG_KILLED1, 10);
		pGame->AddEventList(NOTIFYMSG_KILLED3, 10);
	}

	void HandlePKcaptured(CGame* pGame, char* pData)
	{
		DWORD iExp, iRewardGold;
		int     iPKcount, iLevel;
		char cTxt[120], cName[12];
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyPKcaptured>(
			pData, sizeof(hb::net::PacketNotifyPKcaptured));
		if (!pkt) return;
		iPKcount = pkt->pk_count;
		iLevel = pkt->victim_pk_count;
		std::memset(cName, 0, sizeof(cName));
		memcpy(cName, pkt->victim_name, 10);
		iRewardGold = pkt->reward_gold;
		iExp = pkt->exp;
		wsprintf(cTxt, NOTIFYMSG_PK_CAPTURED1, iLevel, cName, iPKcount);
		pGame->AddEventList(cTxt, 10);
		wsprintf(cTxt, EXP_INCREASED, iExp - pGame->m_iExp);
		pGame->AddEventList(cTxt, 10);
		wsprintf(cTxt, NOTIFYMSG_PK_CAPTURED3, iExp - pGame->m_iExp);
		pGame->AddEventList(cTxt, 10);
	}

	void HandlePKpenalty(CGame* pGame, char* pData)
	{
		DWORD iExp;
		int     iPKcount, iStr, iVit, iDex, iInt, iMag, iChr;
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyPKpenalty>(
			pData, sizeof(hb::net::PacketNotifyPKpenalty));
		if (!pkt) return;
		iExp = pkt->exp;
		iStr = pkt->str;
		iVit = pkt->vit;
		iDex = pkt->dex;
		iInt = pkt->intel;
		iMag = pkt->mag;
		iChr = pkt->chr;
		iPKcount = pkt->pk_count;
		wsprintf(pGame->G_cTxt, NOTIFYMSG_PK_PENALTY1, iPKcount);
		pGame->AddEventList(pGame->G_cTxt, 10);
		if (pGame->m_iExp > iExp)
		{
			wsprintf(pGame->G_cTxt, NOTIFYMSG_PK_PENALTY2, pGame->m_iExp - iExp);
			pGame->AddEventList(pGame->G_cTxt, 10);
		}
		pGame->m_iExp = iExp;
		pGame->m_iStr = iStr;
		pGame->m_iVit = iVit;
		pGame->m_iDex = iDex;
		pGame->m_iInt = iInt;
		pGame->m_iMag = iMag;
		pGame->m_iCharisma = iChr;
		pGame->m_iPKCount = iPKcount;
	}

	void HandleEnemyKills(CGame* pGame, char* pData)
	{
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyEnemyKills>(
			pData, sizeof(hb::net::PacketNotifyEnemyKills));
		if (!pkt) return;
		pGame->m_iEnemyKillCount = pkt->count;
	}

	void HandleEnemyKillReward(CGame* pGame, char* pData)
	{
		DWORD iExp;
		short sGuildRank;
		char cName[12], cGuildName[24], cTxt[120];
		int   iEnemyKillCount, iWarContribution;

		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyEnemyKillReward>(
			pData, sizeof(hb::net::PacketNotifyEnemyKillReward));
		if (!pkt) return;

		std::memset(cName, 0, sizeof(cName));
		std::memset(cGuildName, 0, sizeof(cGuildName));

		iExp = pkt->exp;
		iEnemyKillCount = static_cast<int>(pkt->kill_count);
		memcpy(cName, pkt->killer_name, 10);
		memcpy(cGuildName, pkt->killer_guild, 20);
		sGuildRank = pkt->killer_rank;
		iWarContribution = pkt->war_contribution;

		if (iWarContribution > pGame->m_iWarContribution)
		{
			wsprintf(pGame->G_cTxt, "%s +%d!", pGame->m_pGameMsgList[21]->m_pMsg, iWarContribution - pGame->m_iWarContribution);
			pGame->SetTopMsg(pGame->G_cTxt, 5);
		}
		else if (iWarContribution < pGame->m_iWarContribution)
		{
		}
		pGame->m_iWarContribution = iWarContribution;

		if (sGuildRank == -1)
		{
			wsprintf(cTxt, NOTIFYMSG_ENEMYKILL_REWARD1, cName);
			pGame->AddEventList(cTxt, 10);
		}
		else
		{
			wsprintf(cTxt, NOTIFYMSG_ENEMYKILL_REWARD2, cName, cGuildName);
			pGame->AddEventList(cTxt, 10);
		}

		if (pGame->m_iEnemyKillCount != iEnemyKillCount)
		{
			if (pGame->m_iEnemyKillCount > iEnemyKillCount)
			{
				wsprintf(cTxt, NOTIFYMSG_ENEMYKILL_REWARD5, pGame->m_iEnemyKillCount - iEnemyKillCount);
				pGame->AddEventList(cTxt, 10);
			}
			else
			{
				wsprintf(cTxt, NOTIFYMSG_ENEMYKILL_REWARD6, iEnemyKillCount - pGame->m_iEnemyKillCount);
				pGame->AddEventList(cTxt, 10);
			}
		}

		if (iExp >= 0) pGame->m_iExp = iExp;
		if (iEnemyKillCount >= 0) pGame->m_iEnemyKillCount = iEnemyKillCount;
		pGame->PlaySound('E', 23, 0);

		pGame->_RemoveChatMsgListByObjectID(pGame->m_sPlayerObjectID);
		for (int i = 1; i < DEF_MAXCHATMSGS; i++) {
			if (pGame->m_pChatMsgList[i] == 0) {
				std::memset(cTxt, 0, sizeof(cTxt));
				strcpy(cTxt, "Enemy Kill!");
				pGame->m_pChatMsgList[i] = new class CMsg(23, cTxt, pGame->m_dwCurTime);
				pGame->m_pChatMsgList[i]->m_iObjectID = pGame->m_sPlayerObjectID;
				if (pGame->m_pMapData->bSetChatMsgOwner(pGame->m_sPlayerObjectID, -10, -10, i) == false) {
					delete pGame->m_pChatMsgList[i];
					pGame->m_pChatMsgList[i] = 0;
				}
				break;
			}
		}
		pGame->CreateScreenShot();
	}

	void HandleGlobalAttackMode(CGame* pGame, char* pData)
	{
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyGlobalAttackMode>(
			pData, sizeof(hb::net::PacketNotifyGlobalAttackMode));
		if (!pkt) return;
		switch (pkt->mode) {
		case 0:
			pGame->AddEventList(NOTIFYMSG_GLOBAL_ATTACK_MODE1, 10);
			pGame->AddEventList(NOTIFYMSG_GLOBAL_ATTACK_MODE2, 10);
			break;

		case 1:
			pGame->AddEventList(NOTIFYMSG_GLOBAL_ATTACK_MODE3, 10);
			break;
		}
	}

	void HandleDamageMove(CGame* pGame, char* pData)
	{
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyDamageMove>(
			pData, sizeof(hb::net::PacketNotifyDamageMove));
		if (!pkt) return;
		pGame->m_sDamageMove = pkt->dir;
		pGame->m_sDamageMoveAmount = pkt->amount;
	}

	void HandleObserverMode(CGame* pGame, char* pData)
	{
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyObserverMode>(
			pData, sizeof(hb::net::PacketNotifyObserverMode));
		if (!pkt) return;
		if (pkt->enabled == 1)
		{
			pGame->AddEventList(NOTIFY_MSG_HANDLER40); // "Observer Mode On. Press 'SHIFT + ESC' to Log Out..."
			pGame->m_bIsObserverMode = true;
			pGame->m_dwObserverCamTime = GameClock::GetTimeMS();
			char cName[12];
			std::memset(cName, 0, sizeof(cName));
			memcpy(cName, pGame->m_cPlayerName, 10);
			pGame->m_pMapData->bSetOwner(pGame->m_sPlayerObjectID, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, cName, 0, 0, 0, 0);
		}
		else
		{
			pGame->AddEventList(NOTIFY_MSG_HANDLER41); // "Observer Mode Off"
			pGame->m_bIsObserverMode = false;
			pGame->m_pMapData->bSetOwner(pGame->m_sPlayerObjectID, pGame->m_sPlayerX, pGame->m_sPlayerY, pGame->m_sPlayerType, pGame->m_cPlayerDir, pGame->m_sPlayerAppr1, pGame->m_sPlayerAppr2, pGame->m_sPlayerAppr3, pGame->m_sPlayerAppr4, pGame->m_iPlayerApprColor, pGame->m_iPlayerStatus, pGame->m_cPlayerName, DEF_OBJECTSTOP, 0, 0, 0);
		}
	}

	void HandleSuperAttackLeft(CGame* pGame, char* pData)
	{
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifySuperAttackLeft>(
			pData, sizeof(hb::net::PacketNotifySuperAttackLeft));
		if (!pkt) return;
		pGame->m_iSuperAttackLeft = pkt->left;
	}

	void HandleSafeAttackMode(CGame* pGame, char* pData)
	{
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifySafeAttackMode>(
			pData, sizeof(hb::net::PacketNotifySafeAttackMode));
		if (!pkt) return;
		switch (pkt->enabled) {
		case 1:
			if (!pGame->m_bIsSafeAttackMode) pGame->AddEventList(NOTIFY_MSG_HANDLER50, 10);
			pGame->m_bIsSafeAttackMode = true;
			break;
		case 0:
			if (pGame->m_bIsSafeAttackMode) pGame->AddEventList(NOTIFY_MSG_HANDLER51, 10);
			pGame->m_bIsSafeAttackMode = false;
			break;
		}
	}

	void HandleNpcHp(CGame* pGame, char* pData)
	{
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyNpcHp>(
			pData, sizeof(hb::net::PacketNotifyNpcHp));
		if (!pkt) return;
		pGame->iNpcHP = pkt->hp;
		pGame->iNpcMaxHP = pkt->max_hp;
	}
}

