#include "Game.h"
#include "NetworkMessageManager.h"
#include "Packet/SharedPackets.h"
#include "lan_eng.h"
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <cmath>


namespace NetworkMessageHandlers {
	void HandleHP(CGame* pGame, char* pData)
	{
		int iPrevHP;
		char cTxt[120];

		iPrevHP = pGame->m_iHP;
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyHP>(
		pData, sizeof(hb::net::PacketNotifyHP));
	if (!pkt) return;
	pGame->m_iHP = static_cast<int>(pkt->hp);
	pGame->m_iHungerStatus = static_cast<int>(pkt->hunger);

	if (pGame->m_iHP > iPrevHP)
	{
		if ((pGame->m_iHP - iPrevHP) < 10) return;
		wsprintf(cTxt, NOTIFYMSG_HP_UP, pGame->m_iHP - iPrevHP);
		pGame->AddEventList(cTxt, 10);
		pGame->PlaySound('E', 21, 0);
	}
	else
	{
		if ((pGame->m_cLogOutCount > 0) && (pGame->m_bForceDisconn == false))
		{
			pGame->m_cLogOutCount = -1;
			pGame->AddEventList(NOTIFYMSG_HP2, 10);
		}
		pGame->m_dwDamagedTime = GameClock::GetTimeMS();
		if (pGame->m_iHP < 20) pGame->AddEventList(NOTIFYMSG_HP3, 10);
		if ((iPrevHP - pGame->m_iHP) < 10) return;
		wsprintf(cTxt, NOTIFYMSG_HP_DOWN, iPrevHP - pGame->m_iHP);
		pGame->AddEventList(cTxt, 10);
	}
	}

	void HandleMP(CGame* pGame, char* pData)
	{
		int iPrevMP;
		char cTxt[120];
		iPrevMP = pGame->m_iMP;
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyMP>(
			pData, sizeof(hb::net::PacketNotifyMP));
		if (!pkt) return;
		pGame->m_iMP = static_cast<int>(pkt->mp);
		if (abs(pGame->m_iMP - iPrevMP) < 10) return;
		if (pGame->m_iMP > iPrevMP)
		{
			wsprintf(cTxt, NOTIFYMSG_MP_UP, pGame->m_iMP - iPrevMP);
			pGame->AddEventList(cTxt, 10);
			pGame->PlaySound('E', 21, 0);
		}
		else
		{
			wsprintf(cTxt, NOTIFYMSG_MP_DOWN, iPrevMP - pGame->m_iMP);
			pGame->AddEventList(cTxt, 10);
		}
	}

	void HandleSP(CGame* pGame, char* pData)
	{
		int iPrevSP;
		iPrevSP = pGame->m_iSP;
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifySP>(
			pData, sizeof(hb::net::PacketNotifySP));
		if (!pkt) return;
		pGame->m_iSP = static_cast<int>(pkt->sp);
		if (abs(pGame->m_iSP - iPrevSP) < 10) return;
		if (pGame->m_iSP > iPrevSP)
		{
			wsprintf(pGame->G_cTxt, NOTIFYMSG_SP_UP, pGame->m_iSP - iPrevSP);
			pGame->AddEventList(pGame->G_cTxt, 10);
			pGame->PlaySound('E', 21, 0);
		}
		else
		{
			wsprintf(pGame->G_cTxt, NOTIFYMSG_SP_DOWN, iPrevSP - pGame->m_iSP);
			pGame->AddEventList(pGame->G_cTxt, 10);
		}
	}

	void HandleExp(CGame* pGame, char* pData)
	{
		DWORD iPrevExp;
		char cTxt[120];

		iPrevExp = pGame->m_iExp;
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyExp>(
			pData, sizeof(hb::net::PacketNotifyExp));
		if (!pkt) return;
		pGame->m_iExp = static_cast<int>(pkt->exp);

		if (pGame->m_iExp > iPrevExp)
		{
			wsprintf(cTxt, EXP_INCREASED, pGame->m_iExp - iPrevExp);
			pGame->AddEventList(cTxt, 10);
		}
		else
		{
			wsprintf(cTxt, EXP_DECREASED, iPrevExp - pGame->m_iExp);
			pGame->AddEventList(cTxt, 10);
		}
	}

	void HandleLevelUp(CGame* pGame, char* pData)
	{
		int i, iPrevLevel;
		char cTxt[120];

		iPrevLevel = pGame->m_iLevel;
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyLevelUp>(
			pData, sizeof(hb::net::PacketNotifyLevelUp));
		if (!pkt) return;

		pGame->m_iLevel = pkt->level;
		pGame->m_iStr = pkt->str;
		pGame->m_iVit = pkt->vit;
		pGame->m_iDex = pkt->dex;
		pGame->m_iInt = pkt->intel;
		pGame->m_iMag = pkt->mag;
		pGame->m_iCharisma = pkt->chr;

		pGame->m_iLU_Point = pGame->m_iLevel * 3 - ((pGame->m_iStr + pGame->m_iVit + pGame->m_iDex + pGame->m_iInt + pGame->m_iMag + pGame->m_iCharisma) - 70) - 3;
		pGame->m_cLU_Str = pGame->m_cLU_Vit = pGame->m_cLU_Dex = pGame->m_cLU_Int = pGame->m_cLU_Mag = pGame->m_cLU_Char = 0;

		wsprintf(cTxt, NOTIFYMSG_LEVELUP1, pGame->m_iLevel);
		pGame->AddEventList(cTxt, 10);

		switch (pGame->m_sPlayerType) {
		case 1:
		case 2:
		case 3:
			pGame->PlaySound('C', 21, 0);
			break;
		case 4:
		case 5:
		case 6:
			pGame->PlaySound('C', 22, 0);
			break;
		}

		pGame->_RemoveChatMsgListByObjectID(pGame->m_sPlayerObjectID);

		for (i = 1; i < DEF_MAXCHATMSGS; i++)
			if (pGame->m_pChatMsgList[i] == 0) {
				std::memset(cTxt, 0, sizeof(cTxt));
				strcpy(cTxt, "Level up!");
				pGame->m_pChatMsgList[i] = new class CMsg(23, cTxt, pGame->m_dwCurTime);
				pGame->m_pChatMsgList[i]->m_iObjectID = pGame->m_sPlayerObjectID;

				if (pGame->m_pMapData->bSetChatMsgOwner(pGame->m_sPlayerObjectID, -10, -10, i) == false) {
					delete pGame->m_pChatMsgList[i];
					pGame->m_pChatMsgList[i] = 0;
				}
				return;
			}
	}
} // namespace NetworkMessageHandlers
