#include "Game.h"
#include "NetworkMessageManager.h"
#include "Packet/SharedPackets.h"
#include "lan_eng.h"
#include "DialogBoxIDs.h"
#include <cstdio>
#include <cstring>
#include <windows.h>

namespace NetworkMessageHandlers {

void HandleFishChance(CGame* pGame, char* pData)
{
	int iFishChance;
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyFishChance>(
		pData, sizeof(hb::net::PacketNotifyFishChance));
	if (!pkt) return;
	iFishChance = pkt->chance;
	pGame->m_dialogBoxManager.Info(DialogBoxId::Fishing).sV1 = iFishChance;
}

void HandleEventFishMode(CGame* pGame, char* pData)
{
	short sSprite, sSpriteFrame;
	char cName[21];
	WORD wPrice;

	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyEventFishMode>(
		pData, sizeof(hb::net::PacketNotifyEventFishMode));
	if (!pkt) return;

	wPrice = pkt->price;
	sSprite = static_cast<short>(pkt->sprite);
	sSpriteFrame = static_cast<short>(pkt->sprite_frame);

	std::memset(cName, 0, sizeof(cName));
	memcpy(cName, pkt->name, 20);

	pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Fishing, 0, 0, wPrice, cName);
	pGame->m_dialogBoxManager.Info(DialogBoxId::Fishing).sV3 = sSprite;
	pGame->m_dialogBoxManager.Info(DialogBoxId::Fishing).sV4 = sSpriteFrame;

	pGame->AddEventList(NOTIFYMSG_EVENTFISHMODE1, 10);
}

void HandleFishCanceled(CGame* pGame, char* pData)
{
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyFishCanceled>(
		pData, sizeof(hb::net::PacketNotifyFishCanceled));
	if (!pkt) return;
	switch (pkt->reason) {
	case 0:
		pGame->AddEventList(NOTIFY_MSG_HANDLER52, 10);
		pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::Fishing);
		break;
	case 1:
		pGame->AddEventList(NOTIFY_MSG_HANDLER53, 10);
		pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::Fishing);
		break;
	case 2:
		pGame->AddEventList(NOTIFY_MSG_HANDLER54, 10);
		pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::Fishing);
		break;
	}
}

void HandleFishSuccess(CGame* pGame, char* pData)
{
	pGame->AddEventList(NOTIFY_MSG_HANDLER55, 10);
	pGame->PlaySound('E', 23, 5);
	pGame->PlaySound('E', 17, 5);
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
}

void HandleFishFail(CGame* pGame, char* pData)
{
	pGame->AddEventList(NOTIFY_MSG_HANDLER56, 10);
	pGame->PlaySound('E', 24, 5);
}

} // namespace NetworkMessageHandlers
