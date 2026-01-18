#include "Game.h"
#include "AudioManager.h"

extern char G_cSpriteAlphaDegree;
extern char G_cCmdLineTokenA[120];

#include "NetworkMessageManager.h"
#include "Packet/SharedPackets.h"
#include "lan_eng.h"
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <cmath>

namespace NetworkMessageHandlers {

void HandleWhetherChange(CGame* pGame, char* pData)
{
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyWhetherChange>(
		pData, sizeof(hb::net::PacketNotifyWhetherChange));
	if (!pkt) return;
	pGame->m_cWhetherStatus = static_cast<char>(pkt->status);

	if (pGame->m_cWhetherStatus != 0)
		pGame->SetWhetherStatus(true, pGame->m_cWhetherStatus);
	else pGame->SetWhetherStatus(false, 0);
}

void HandleTimeChange(CGame* pGame, char* pData)
{
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyTimeChange>(
		pData, sizeof(hb::net::PacketNotifyTimeChange));
	if (!pkt) return;
	G_cSpriteAlphaDegree = static_cast<char>(pkt->sprite_alpha);
	switch (G_cSpriteAlphaDegree) {
	case 1:	pGame->m_bIsXmas = false; pGame->PlaySound('E', 32, 0); break;
	case 2: pGame->m_bIsXmas = false; pGame->PlaySound('E', 31, 0); break;
	case 3: // Snoopy Special night with chrismas bulbs
		if (pGame->m_cWhetherEffectType > 3) pGame->m_bIsXmas = true;
		else pGame->m_bIsXmas = false;
		pGame->PlaySound('E', 31, 0);
		G_cSpriteAlphaDegree = 2; break;
	}
	pGame->m_cGameModeCount = 1;
	pGame->m_bIsRedrawPDBGS = true;
}

void HandleNoticeMsg(CGame* pGame, char* pData)
{
	char cMsg[1000];
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyNoticeMsg>(
		pData, sizeof(hb::net::PacketNotifyNoticeMsg));
	if (!pkt) return;
	strcpy(cMsg, pkt->text);
	pGame->AddEventList(cMsg, 10);
}

void HandleForceDisconn(CGame* pGame, char* pData)
{
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyForceDisconn>(
		pData, sizeof(hb::net::PacketNotifyForceDisconn));
	if (!pkt) return;
	const auto wpCount = pkt->seconds;
	pGame->m_bForceDisconn = true;
	//m_cLogOutCount = (char)*wpCount;
	if (pGame->m_bIsProgramActive)
	{
		if (pGame->m_cLogOutCount < 0 || pGame->m_cLogOutCount > 5) pGame->m_cLogOutCount = 5;
		pGame->AddEventList(NOTIFYMSG_FORCE_DISCONN1, 10);
	}
	else
	{
		delete pGame->m_pGSock;
		pGame->m_pGSock = 0;
		// InputManager::Get().ClearEscPressed(); // Not needed here
		AudioManager::Get().StopSound(SoundType::Effect, 38);
		AudioManager::Get().StopMusic();
		if (strlen(G_cCmdLineTokenA) != 0)
			pGame->ChangeGameMode(DEF_GAMEMODE_ONQUIT);
		else pGame->ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
	}
}

void HandleSettingSuccess(CGame* pGame, char* pData)
{
	int iPrevLevel;
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
	wsprintf(cTxt, "Your stat has been changed.");
	pGame->AddEventList(cTxt, 10);
	// CLEROTH - LU
	pGame->m_iLU_Point = pGame->m_iLevel * 3 - ((pGame->m_iStr + pGame->m_iVit + pGame->m_iDex + pGame->m_iInt + pGame->m_iMag + pGame->m_iCharisma) - 70) - 3;
	pGame->m_cLU_Str = pGame->m_cLU_Vit = pGame->m_cLU_Dex = pGame->m_cLU_Int = pGame->m_cLU_Mag = pGame->m_cLU_Char = 0;
}

void HandleServerChange(CGame* pGame, char* pData)
{
	char cWorldServerAddr[16];
	int iWorldServerPort;

	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyServerChange>(
		pData, sizeof(hb::net::PacketNotifyServerChange));
	if (!pkt) return;

	std::memset(pGame->m_cMapName, 0, sizeof(pGame->m_cMapName));
	std::memset(pGame->m_cMapMessage, 0, sizeof(pGame->m_cMapMessage));
	std::memset(cWorldServerAddr, 0, sizeof(cWorldServerAddr));

	memcpy(pGame->m_cMapName, pkt->map_name, 10);
	memcpy(cWorldServerAddr, pkt->log_server_addr, 15);
	iWorldServerPort = pkt->log_server_port;
	if (pGame->m_pGSock != 0)
	{
		delete pGame->m_pGSock;
		pGame->m_pGSock = 0;
	}
	if (pGame->m_pLSock != 0)
	{
		delete pGame->m_pLSock;
		pGame->m_pLSock = 0;
	}
	pGame->m_pLSock = new class XSocket(DEF_SOCKETBLOCKLIMIT);
	pGame->m_pLSock->bConnect(pGame->m_cLogServerAddr, iWorldServerPort);
	pGame->m_pLSock->bInitBufferSize(30000);

	pGame->m_bIsPoisoned = false;

	pGame->ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
	pGame->m_dwConnectMode = MSGID_REQUEST_ENTERGAME;
	//m_wEnterGameType = DEF_ENTERGAMEMSGTYPE_NEW; //Gateway
	pGame->m_wEnterGameType = DEF_ENTERGAMEMSGTYPE_NEW_TOWLSBUTMLS;
	std::memset(pGame->m_cMsg, 0, sizeof(pGame->m_cMsg));
	strcpy(pGame->m_cMsg, "55");
}

void HandleTotalUsers(CGame* pGame, char* pData)
{
	int iTotal;
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyTotalUsers>(
		pData, sizeof(hb::net::PacketNotifyTotalUsers));
	if (!pkt) return;
	iTotal = pkt->total;
	wsprintf(pGame->G_cTxt, NOTIFYMSG_TOTAL_USER1, iTotal);
	pGame->AddEventList(pGame->G_cTxt, 10);
}

void HandleChangePlayMode(CGame* pGame, char* pData)
{
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyChangePlayMode>(
		pData, sizeof(hb::net::PacketNotifyChangePlayMode));
	if (!pkt) return;
	memcpy(pGame->m_cLocation, pkt->location, sizeof(pkt->location));

	if (memcmp(pGame->m_cLocation, "aresden", 7) == 0)
	{
		pGame->m_bAresden = true;
		pGame->m_bCitizen = true;
		pGame->m_bHunter = false;
	}
	else if (memcmp(pGame->m_cLocation, "arehunter", 9) == 0)
	{
		pGame->m_bAresden = true;
		pGame->m_bCitizen = true;
		pGame->m_bHunter = true;
	}
	else if (memcmp(pGame->m_cLocation, "elvine", 6) == 0)
	{
		pGame->m_bAresden = false;
		pGame->m_bCitizen = true;
		pGame->m_bHunter = false;
	}
	else if (memcmp(pGame->m_cLocation, "elvhunter", 9) == 0)
	{
		pGame->m_bAresden = false;
		pGame->m_bCitizen = true;
		pGame->m_bHunter = true;
	}
	else
	{
		pGame->m_bAresden = true;
		pGame->m_bCitizen = false;
		pGame->m_bHunter = true;
	}
	pGame->AddEventList(DEF_MSG_GAMEMODE_CHANGED, 10);
}

void HandleForceRecallTime(CGame* pGame, char* pData)
{
	short sV1;
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyForceRecallTime>(
		pData, sizeof(hb::net::PacketNotifyForceRecallTime));
	if (!pkt) return;
	sV1 = static_cast<short>(pkt->seconds_left);
	if ((int)(sV1 / 20) > 0)
		wsprintf(pGame->G_cTxt, NOTIFY_MSG_FORCERECALLTIME1, (int)(sV1 / 20));
	else
		wsprintf(pGame->G_cTxt, NOTIFY_MSG_FORCERECALLTIME2);
	pGame->AddEventList(pGame->G_cTxt, 10);
}

void HandleNoRecall(CGame* pGame, char* pData)
{
	pGame->AddEventList("You can not recall in this map.", 10);
}

void HandleFightZoneReserve(CGame* pGame, char* pData)
{
	char cTxt[120];
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyFightZoneReserve>(
		pData, sizeof(hb::net::PacketNotifyFightZoneReserve));
	if (!pkt) return;
	switch (pkt->result) {
	case -5:
		pGame->AddEventList(NOTIFY_MSG_HANDLER68, 10);
		break;
	case -4:
		pGame->AddEventList(NOTIFY_MSG_HANDLER69, 10);
		break;
	case -3:
		pGame->AddEventList(NOTIFY_MSG_HANDLER70, 10);
		break;
	case -2:
		pGame->m_iFightzoneNumber = 0;
		pGame->AddEventList(NOTIFY_MSG_HANDLER71, 10);
		break;
	case -1:
		pGame->m_iFightzoneNumber = pGame->m_iFightzoneNumber * -1;
		pGame->AddEventList(NOTIFY_MSG_HANDLER72, 10);
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		wsprintf(cTxt, NOTIFY_MSG_HANDLER73, pkt->result);
		pGame->AddEventList(cTxt, 10);
		break;
	}
}

void HandleLoteryLost(CGame* pGame, char* pData)
{
	pGame->AddEventList(DEF_MSG_NOTIFY_LOTERY_LOST, 10);
}

void HandleNotFlagSpot(CGame* pGame, char* pData)
{
	pGame->AddEventList(NOTIFY_MSG_HANDLER45, 10);
}

void HandleNpcTalk(CGame* pGame, char* pData)
{
	pGame->NpcTalkHandler(pData);
}

void HandleTravelerLimitedLevel(CGame* pGame, char* pData)
{
	pGame->AddEventList(NOTIFY_MSG_HANDLER64, 10);
}

void HandleLimitedLevel(CGame* pGame, char* pData)
{
	pGame->AddEventList(NOTIFYMSG_LIMITED_LEVEL1, 10);
}

void HandleToBeRecalled(CGame* pGame, char* pData)
{
	pGame->AddEventList(NOTIFY_MSG_HANDLER62, 10);
}

} // namespace NetworkMessageHandlers