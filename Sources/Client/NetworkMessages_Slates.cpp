#include "Game.h"
#include "NetworkMessageManager.h"
#include "Packet/SharedPackets.h"
#include "lan_eng.h"
#include <cstdio>
#include <cstring>

namespace NetworkMessageHandlers {
	void HandleSlateCreateSuccess(CGame* pGame, char* pData)
	{
		pGame->AddEventList(DEF_MSG_NOTIFY_SLATE_CREATESUCCESS, 10);
	}

	void HandleSlateCreateFail(CGame* pGame, char* pData)
	{
		pGame->AddEventList(DEF_MSG_NOTIFY_SLATE_CREATEFAIL, 10);
	}

	void HandleSlateInvincible(CGame* pGame, char* pData)
	{
		pGame->AddEventList(DEF_MSG_NOTIFY_SLATE_INVINCIBLE, 10);
		pGame->m_bUsingSlate = true;
	}

	void HandleSlateMana(CGame* pGame, char* pData)
	{
		pGame->AddEventList(DEF_MSG_NOTIFY_SLATE_MANA, 10);
		pGame->m_bUsingSlate = true;
	}

	void HandleSlateExp(CGame* pGame, char* pData)
	{
		pGame->AddEventList(DEF_MSG_NOTIFY_SLATE_EXP, 10);
		pGame->m_bUsingSlate = true;
	}

	void HandleSlateStatus(CGame* pGame, char* pData)
	{
		pGame->AddEventList(DEF_MSG_NOTIFY_SLATECLEAR, 10);
		pGame->m_bUsingSlate = false;
	}

	void HandleSlateBerserk(CGame* pGame, char* pData)
	{
		pGame->AddEventList(DEF_MSG_NOTIFY_SLATE_BERSERK, 10); // "Berserk magic casted!"
		pGame->m_bUsingSlate = true;
	}
} // namespace NetworkMessageHandlers
