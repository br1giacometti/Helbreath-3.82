#include "Game.h"
#include "NetworkMessageManager.h"
#include "Packet/SharedPackets.h"
#include "lan_eng.h"
#include <cstdio>
#include <cstring>
#include "DialogBoxIDs.h"

namespace NetworkMessageHandlers {
	void HandleSpawnEvent(CGame* pGame, char* pData)
	{
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifySpawnEvent>(
			pData, sizeof(hb::net::PacketNotifySpawnEvent));
		if (!pkt) return;
		pGame->m_sMonsterID = pkt->monster_id;
		pGame->m_sEventX = pkt->x;
		pGame->m_sEventY = pkt->y;
		pGame->m_dwMonsterEventTime = pGame->m_dwCurTime;
	}

	void HandleMonsterCount(CGame* pGame, char* pData)
	{
		char cTxt[120];
		int iCount;
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyMonsterCount>(
			pData, sizeof(hb::net::PacketNotifyMonsterCount));
		if (!pkt) return;
		iCount = pkt->count;
		wsprintf(cTxt, "Rest Monster :%d", iCount);
		pGame->AddEventList(cTxt, 10);
	}

	void HandleResurrectPlayer(CGame* pGame, char* pData)
	{
		pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Resurrect, 0, 0, 0);
	}
} // namespace NetworkMessageHandlers
