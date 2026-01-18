#include "Game.h"
#include "NetworkMessageManager.h"
#include "Packet/SharedPackets.h"
#include "lan_eng.h"
#include "DialogBoxIDs.h"
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <cmath>

namespace NetworkMessageHandlers {

void HandleCraftingSuccess(CGame* pGame, char* pData)
{
	pGame->m_iContribution -= pGame->m_iContributionPrice;
	pGame->m_iContributionPrice = 0;
	pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::Noticement);
	pGame->AddEventList(NOTIFY_MSG_HANDLER42, 10);		// "Item manufacture success!"
	pGame->PlaySound('E', 23, 5);
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

void HandleCraftingFail(CGame* pGame, char* pData)
{
	int iV1;
	pGame->m_iContributionPrice = 0;
	{
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyCraftingFail>(
			pData, sizeof(hb::net::PacketNotifyCraftingFail));
		if (!pkt) return;
		iV1 = pkt->reason; // Error reason
	}
	switch (iV1) {
	case 1:
		pGame->AddEventList(DEF_MSG_NOTIFY_CRAFTING_NO_PART, 10);		// "There is not enough material"
		pGame->PlaySound('E', 24, 5);
		break;
	case 2:
		pGame->AddEventList(DEF_MSG_NOTIFY_CRAFTING_NO_CONTRIB, 10);	// "There is not enough Contribution Point"
		pGame->PlaySound('E', 24, 5);
		break;
	default:
	case 3:
		pGame->AddEventList(DEF_MSG_NOTIFY_CRAFTING_FAILED, 10);		// "Crafting failed"
		pGame->PlaySound('E', 24, 5);
		break;
	}
}

void HandleBuildItemSuccess(CGame* pGame, char* pData)
{
	short sV1, sV2;
	pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::Manufacture);
	{
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyBuildItemResult>(
			pData, sizeof(hb::net::PacketNotifyBuildItemResult));
		if (!pkt) return;
		sV1 = pkt->item_id;
		sV2 = pkt->item_count;
	}
	if (sV1 < 10000)
	{
		pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Manufacture, 6, 1, sV1, 0);
		pGame->m_dialogBoxManager.Info(DialogBoxId::Manufacture).sV1 = sV2;
	}
	else
	{
		pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Manufacture, 6, 1, -1 * (sV1 - 10000), 0);
		pGame->m_dialogBoxManager.Info(DialogBoxId::Manufacture).sV1 = sV2;
	}
	pGame->AddEventList(NOTIFY_MSG_HANDLER42, 10);
	pGame->PlaySound('E', 23, 5);
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

void HandleBuildItemFail(CGame* pGame, char* pData)
{
	pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::Manufacture);
	pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Manufacture, 6, 0, 0);
	pGame->AddEventList(NOTIFY_MSG_HANDLER43, 10);
	pGame->PlaySound('E', 24, 5);
}

void HandlePortionSuccess(CGame* pGame, char* pData)
{
	pGame->AddEventList(NOTIFY_MSG_HANDLER46, 10);
}

void HandlePortionFail(CGame* pGame, char* pData)
{
	pGame->AddEventList(NOTIFY_MSG_HANDLER47, 10);
}

void HandleLowPortionSkill(CGame* pGame, char* pData)
{
	pGame->AddEventList(NOTIFY_MSG_HANDLER48, 10);
}

void HandleNoMatchingPortion(CGame* pGame, char* pData)
{
	pGame->AddEventList(NOTIFY_MSG_HANDLER49, 10);
}

} // namespace NetworkMessageHandlers
