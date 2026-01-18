#include "Game.h"
#include "NetworkMessageManager.h"
#include "Packet/SharedPackets.h"
#include "lan_eng.h"
#include <cstdio>
#include <cstring>

namespace NetworkMessageHandlers {

void HandleHeldenianTeleport(CGame* pGame, char* pData)
{
	pGame->SetTopMsg("Teleport to Heldenian field is available from now. Magic casting is forbidden until real battle.", 10);
}

void HandleHeldenianEnd(CGame* pGame, char* pData)
{
	pGame->SetTopMsg("Heldenian holy war has been closed.", 10);
}

void HandleHeldenianStart(CGame* pGame, char* pData)
{
	pGame->SetTopMsg("Heldenian real battle has been started form now on.", 10);
}

void HandleHeldenianVictory(CGame* pGame, char* pData)
{
	short sSide;
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyHeldenianVictory>(
		pData, sizeof(hb::net::PacketNotifyHeldenianVictory));
	if (!pkt) return;
	sSide = pkt->side;
	pGame->ShowHeldenianVictory(sSide);
	pGame->m_iHeldenianAresdenLeftTower = -1;
	pGame->m_iHeldenianElvineLeftTower = -1;
	pGame->m_iHeldenianAresdenFlags = -1;
	pGame->m_iHeldenianElvineFlags = -1;
}

void HandleHeldenianCount(CGame* pGame, char* pData)
{
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyHeldenianCount>(
		pData, sizeof(hb::net::PacketNotifyHeldenianCount));
	if (!pkt) return;
	pGame->m_iHeldenianAresdenLeftTower = pkt->aresden_tower_left;
	pGame->m_iHeldenianElvineLeftTower = pkt->elvine_tower_left;
	pGame->m_iHeldenianAresdenFlags = pkt->aresden_flags;
	pGame->m_iHeldenianElvineFlags = pkt->elvine_flags;
}

void HandleHeldenianRecall(CGame* pGame, char* pData)
{
	pGame->SetTopMsg("Characters will be recalled by force as Heldenian begins.", 10);
}

} // namespace NetworkMessageHandlers
