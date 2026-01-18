#include "Game.h"
#include "NetworkMessageManager.h"
#include "Packet/SharedPackets.h"
#include "lan_eng.h"
#include <cstdio>
#include <cstring>

namespace NetworkMessageHandlers {

void HandleApocGateStart(CGame* pGame, char* pData)
{
	pGame->SetTopMsg("The portal to the Apocalypse is opened.", 10);
}

void HandleApocGateEnd(CGame* pGame, char* pData)
{
	pGame->SetTopMsg("The portal to the Apocalypse is closed.", 10);
}

void HandleApocGateOpen(CGame* pGame, char* pData)
{
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyApocGateOpen>(
		pData, sizeof(hb::net::PacketNotifyApocGateOpen));
	if (!pkt) return;
	pGame->m_iGatePositX = pkt->gate_x;
	pGame->m_iGatePositY = pkt->gate_y;
	std::memset(pGame->m_cGateMapName, 0, sizeof(pGame->m_cGateMapName));
	memcpy(pGame->m_cGateMapName, pkt->map_name, sizeof(pkt->map_name));
}

void HandleApocGateClose(CGame* pGame, char* pData)
{
	pGame->m_iGatePositX = pGame->m_iGatePositY = -1;
	std::memset(pGame->m_cGateMapName, 0, sizeof(pGame->m_cGateMapName));
}

void HandleApocForceRecall(CGame* pGame, char* pData)
{
	pGame->AddEventList("You are recalled by force, because the Apocalypse is started.", 10);
}

void HandleAbaddonKilled(CGame* pGame, char* pData)
{
	char cTxt[128];
	char cKiller[21];
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyAbaddonKilled>(
		pData, sizeof(hb::net::PacketNotifyAbaddonKilled));
	if (!pkt) return;
	std::memset(cKiller, 0, sizeof(cKiller));
	memcpy(cKiller, pkt->killer_name, sizeof(pkt->killer_name));
	
	wsprintf(cTxt, "Abaddon is destroyed by %s", cKiller);
	pGame->AddEventList(cTxt, 10);
}

} // namespace NetworkMessageHandlers
