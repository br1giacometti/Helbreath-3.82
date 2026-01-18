#include "Game.h"
#include "NetworkMessageManager.h"
#include "Packet/SharedPackets.h"
#include "lan_eng.h"
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <cmath>

namespace NetworkMessageHandlers {
	void HandleCharisma(CGame* pGame, char* pData)
	{
		int  iPrevChar;
		char cTxt[120];

		iPrevChar = pGame->m_iCharisma;
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyCharisma>(
			pData, sizeof(hb::net::PacketNotifyCharisma));
		if (!pkt) return;
		pGame->m_iCharisma = static_cast<int>(pkt->charisma);

		if (pGame->m_iCharisma > iPrevChar)
		{
			wsprintf(cTxt, NOTIFYMSG_CHARISMA_UP, pGame->m_iCharisma - iPrevChar);
			pGame->AddEventList(cTxt, 10);
			pGame->PlaySound('E', 21, 0);
		}
		else
		{
			wsprintf(cTxt, NOTIFYMSG_CHARISMA_DOWN, iPrevChar - pGame->m_iCharisma);
			pGame->AddEventList(cTxt, 10);
		}
	}

	void HandleHunger(CGame* pGame, char* pData)
	{
		char cHLv;
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyHunger>(
			pData, sizeof(hb::net::PacketNotifyHunger));
		if (!pkt) return;
		pGame->m_iHungerStatus = pkt->hunger;

		cHLv = pGame->m_iHungerStatus;
		if ((cHLv <= 40) && (cHLv > 30)) pGame->AddEventList(NOTIFYMSG_HUNGER1, 10);
		if ((cHLv <= 25) && (cHLv > 20)) pGame->AddEventList(NOTIFYMSG_HUNGER2, 10);
		if ((cHLv <= 20) && (cHLv > 15)) pGame->AddEventList(NOTIFYMSG_HUNGER3, 10);
		if ((cHLv <= 15) && (cHLv > 10)) pGame->AddEventList(NOTIFYMSG_HUNGER4, 10);
		if ((cHLv <= 10) && (cHLv >= 0)) pGame->AddEventList(NOTIFYMSG_HUNGER5, 10);
	}

	void HandlePlayerProfile(CGame* pGame, char* pData)
	{
		char cTemp[500];
		int i;
		std::memset(cTemp, 0, sizeof(cTemp));
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyPlayerProfile>(
			pData, sizeof(hb::net::PacketNotifyPlayerProfile));
		if (!pkt) return;
		strcpy(cTemp, pkt->text);
		for (i = 0; i < 500; i++)
			if (cTemp[i] == '_') cTemp[i] = ' ';
		pGame->AddEventList(cTemp, 10);
	}

	void HandlePlayerStatus(CGame* pGame, bool bOnGame, char* pData)
	{
		char cName[12], cMapName[12];
		uint16_t dx = 1, dy = 1;
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyPlayerStatus>(
			pData, sizeof(hb::net::PacketNotifyPlayerStatus));
		if (!pkt) return;
		std::memset(cName, 0, sizeof(cName));
		memcpy(cName, pkt->name, 10);
		std::memset(cMapName, 0, sizeof(cMapName));
		memcpy(cMapName, pkt->map_name, 10);
		dx = pkt->x;
		dy = pkt->y;
		std::memset(pGame->G_cTxt, 0, sizeof(pGame->G_cTxt));
		if (bOnGame == true) {
			if (cMapName[0] == 0)
				wsprintf(pGame->G_cTxt, NOTIFYMSG_PLAYER_STATUS1, cName);
			else wsprintf(pGame->G_cTxt, NOTIFYMSG_PLAYER_STATUS2, cName, cMapName, dx, dy);
		}
		else wsprintf(pGame->G_cTxt, NOTIFYMSG_PLAYER_STATUS3, cName);
		pGame->AddEventList(pGame->G_cTxt, 10);
	}

	void HandleWhisperMode(CGame* pGame, bool bActive, char* pData)
	{
		char cName[12];
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyWhisperMode>(
			pData, sizeof(hb::net::PacketNotifyWhisperMode));
		if (!pkt) return;
		std::memset(cName, 0, sizeof(cName));
		memcpy(cName, pkt->name, 10);
		if (bActive == true)
		{
			wsprintf(pGame->G_cTxt, NOTIFYMSG_WHISPERMODE1, cName);
			if (pGame->m_pWhisperMsg[DEF_MAXWHISPERMSG - 1] != 0) {
				delete pGame->m_pWhisperMsg[DEF_MAXWHISPERMSG - 1];
				pGame->m_pWhisperMsg[DEF_MAXWHISPERMSG - 1] = 0;
			}
			for (int i = DEF_MAXWHISPERMSG - 2; i >= 0; i--) {
				pGame->m_pWhisperMsg[i + 1] = pGame->m_pWhisperMsg[i];
				pGame->m_pWhisperMsg[i] = 0;
			}
			pGame->m_pWhisperMsg[0] = new class CMsg(0, cName, 0);
			pGame->m_cWhisperIndex = 0;
		}
		else wsprintf(pGame->G_cTxt, NOTIFYMSG_WHISPERMODE2, cName);

		pGame->AddEventList(pGame->G_cTxt, 10);
	}

	void HandlePlayerShutUp(CGame* pGame, char* pData)
	{
		char cName[12];
		WORD wTime;
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyPlayerShutUp>(
			pData, sizeof(hb::net::PacketNotifyPlayerShutUp));
		if (!pkt) return;
		wTime = pkt->time;
		std::memset(cName, 0, sizeof(cName));
		memcpy(cName, pkt->name, 10);
		if (memcmp(pGame->m_cPlayerName, cName, 10) == 0)
			wsprintf(pGame->G_cTxt, NOTIFYMSG_PLAYER_SHUTUP1, wTime);
		else wsprintf(pGame->G_cTxt, NOTIFYMSG_PLAYER_SHUTUP2, cName, wTime);

		pGame->AddEventList(pGame->G_cTxt, 10);
	}

	void HandleRatingPlayer(CGame* pGame, char* pData)
	{
		char cName[12];
		uint16_t cValue;
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyRatingPlayer>(
			pData, sizeof(hb::net::PacketNotifyRatingPlayer));
		if (!pkt) return;
		cValue = pkt->result;
		std::memset(cName, 0, sizeof(cName));
		memcpy(cName, pkt->name, 10);
		std::memset(pGame->G_cTxt, 0, sizeof(pGame->G_cTxt));
		if (memcmp(pGame->m_cPlayerName, cName, 10) == 0)
		{
			if (cValue == 1)
			{
				strcpy(pGame->G_cTxt, NOTIFYMSG_RATING_PLAYER1);
				pGame->PlaySound('E', 23, 0);
			}
		}
		else
		{
			if (cValue == 1)
				wsprintf(pGame->G_cTxt, NOTIFYMSG_RATING_PLAYER2, cName);
			else wsprintf(pGame->G_cTxt, NOTIFYMSG_RATING_PLAYER3, cName);
		}
		pGame->AddEventList(pGame->G_cTxt, 10);
	}

	void HandleCannotRating(CGame* pGame, char* pData)
	{
		char cTxt[120];

		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyCannotRating>(
			pData, sizeof(hb::net::PacketNotifyCannotRating));
		if (!pkt) return;
		const auto wTime = pkt->time_left;

		if (wTime == 0) wsprintf(cTxt, NOTIFYMSG_CANNOT_RATING1, wTime * 3);
		else wsprintf(cTxt, NOTIFYMSG_CANNOT_RATING2, wTime * 3);
		pGame->AddEventList(cTxt, 10);
	}
}
