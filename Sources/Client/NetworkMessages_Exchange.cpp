#include "Game.h"
#include "NetworkMessageManager.h"
#include "Packet/SharedPackets.h"
#include "lan_eng.h"
#include "DialogBoxIDs.h"
#include <cstring>
#include <cstdio>

namespace NetworkMessageHandlers {
	void HandleExchangeItemComplete(CGame* pGame, char* pData)
	{
		pGame->AddEventList(NOTIFYMSG_EXCHANGEITEM_COMPLETE1, 10);
		pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::Exchange);
		//Snoopy: MultiTrade
		pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::ConfirmExchange);
		pGame->PlaySound('E', 23, 5);
	}

	void HandleCancelExchangeItem(CGame* pGame, char* pData)
	{
		pGame->PlaySound('E', 24, 5);
		pGame->AddEventList(NOTIFYMSG_CANCEL_EXCHANGEITEM1, 10);
		pGame->AddEventList(NOTIFYMSG_CANCEL_EXCHANGEITEM2, 10);
		//Snoopy: MultiTrade
		pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::ConfirmExchange);
		pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::Exchange);
	}
} // namespace NetworkMessageHandlers
