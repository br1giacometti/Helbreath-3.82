#include "Game.h"
#include "NetworkMessageManager.h"
#include "Packet/SharedPackets.h"
#include "lan_eng.h"
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <cmath>

namespace NetworkMessageHandlers {
	// Helper function to update location flags from location string
	static void UpdateLocationFlags(CGame* pGame, const char* cLocation)
	{
		if (memcmp(cLocation, "aresden", 7) == 0)
		{
			pGame->m_bAresden = true;
			pGame->m_bCitizen = true;
			pGame->m_bHunter = false;
		}
		else if (memcmp(cLocation, "arehunter", 9) == 0)
		{
			pGame->m_bAresden = true;
			pGame->m_bCitizen = true;
			pGame->m_bHunter = true;
		}
		else if (memcmp(cLocation, "elvine", 6) == 0)
		{
			pGame->m_bAresden = false;
			pGame->m_bCitizen = true;
			pGame->m_bHunter = false;
		}
		else if (memcmp(cLocation, "elvhunter", 9) == 0)
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
	}

	void HandleCreateNewGuildResponse(CGame* pGame, char* pData)
	{
		const auto* header = hb::net::PacketCast<hb::net::PacketHeader>(
			pData, sizeof(hb::net::PacketHeader));
		if (!header) return;
		switch (header->msg_type) {
		case DEF_MSGTYPE_CONFIRM:
			pGame->m_iGuildRank = 0;
			pGame->m_dialogBoxManager.Info(DialogBoxId::GuildMenu).cMode = 3;
			break;
		case DEF_MSGTYPE_REJECT:
			pGame->m_iGuildRank = -1;
			pGame->m_dialogBoxManager.Info(DialogBoxId::GuildMenu).cMode = 4;
			break;
		}
	}

	void HandleDisbandGuildResponse(CGame* pGame, char* pData)
	{
		const auto* header = hb::net::PacketCast<hb::net::PacketHeader>(
			pData, sizeof(hb::net::PacketHeader));
		if (!header) return;
		switch (header->msg_type) {
		case DEF_MSGTYPE_CONFIRM:
			std::memset(pGame->m_cGuildName, 0, sizeof(pGame->m_cGuildName));
			pGame->m_iGuildRank = -1;
			pGame->m_dialogBoxManager.Info(DialogBoxId::GuildMenu).cMode = 7;
			break;
		case DEF_MSGTYPE_REJECT:
			pGame->m_dialogBoxManager.Info(DialogBoxId::GuildMenu).cMode = 8;
			break;
		}
	}

	void HandleGuildDisbanded(CGame* pGame, char* pData)
	{
		char cName[24], cLocation[12];
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyGuildDisbanded>(
			pData, sizeof(hb::net::PacketNotifyGuildDisbanded));
		if (!pkt) return;
		std::memset(cName, 0, sizeof(cName));
		std::memset(cLocation, 0, sizeof(cLocation));
		memcpy(cName, pkt->guild_name, 20);
		memcpy(cLocation, pkt->location, 10);
		CMisc::ReplaceString(cName, '_', ' ');
		pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::GuildOperation, 0, 0, 0);
		pGame->_PutGuildOperationList(cName, 7);
		std::memset(pGame->m_cGuildName, 0, sizeof(pGame->m_cGuildName));
		pGame->m_iGuildRank = -1;
		std::memset(pGame->m_cLocation, 0, sizeof(pGame->m_cLocation));
		memcpy(pGame->m_cLocation, cLocation, 10);
		UpdateLocationFlags(pGame, pGame->m_cLocation);
	}

	void HandleNewGuildsMan(CGame* pGame, char* pData)
	{
		char cName[12], cTxt[120];
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyNewGuildsMan>(
			pData, sizeof(hb::net::PacketNotifyNewGuildsMan));
		if (!pkt) return;
		std::memset(cName, 0, sizeof(cName));
		memcpy(cName, pkt->name, 10);
		wsprintf(cTxt, NOTIFYMSG_NEW_GUILDMAN1, cName);
		pGame->AddEventList(cTxt, 10);
		pGame->ClearGuildNameList();
	}

	void HandleDismissGuildsMan(CGame* pGame, char* pData)
	{
		char cName[12], cTxt[120];

		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyDismissGuildsMan>(
			pData, sizeof(hb::net::PacketNotifyDismissGuildsMan));
		if (!pkt) return;
		std::memset(cName, 0, sizeof(cName));
		memcpy(cName, pkt->name, 10);

		if (memcmp(pGame->m_cPlayerName, cName, 10) != 0) {
			wsprintf(cTxt, NOTIFYMSG_DISMISS_GUILDMAN1, cName);
			pGame->AddEventList(cTxt, 10);
		}
		pGame->ClearGuildNameList();
	}

	void HandleCannotJoinMoreGuildsMan(CGame* pGame, char* pData)
	{
		char cName[12], cTxt[120];

		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyCannotJoinMoreGuildsMan>(
			pData, sizeof(hb::net::PacketNotifyCannotJoinMoreGuildsMan));
		if (!pkt) return;
		std::memset(cName, 0, sizeof(cName));
		memcpy(cName, pkt->name, 10);

		wsprintf(cTxt, NOTIFYMSG_CANNOT_JOIN_MOREGUILDMAN1, cName);
		pGame->AddEventList(cTxt, 10);
		pGame->AddEventList(NOTIFYMSG_CANNOT_JOIN_MOREGUILDMAN2, 10);
	}

	void HandleJoinGuildApprove(CGame* pGame, char* pData)
	{
		char cName[21];
		short sRank;
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyJoinGuildApprove>(
			pData, sizeof(hb::net::PacketNotifyJoinGuildApprove));
		if (!pkt) return;
		std::memset(cName, 0, sizeof(cName));
		memcpy(cName, pkt->guild_name, 20);
		sRank = pkt->rank;
		std::memset(pGame->m_cGuildName, 0, sizeof(pGame->m_cGuildName));
		strcpy(pGame->m_cGuildName, cName);
		pGame->m_iGuildRank = sRank;
		pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::GuildOperation, 0, 0, 0);
		pGame->_PutGuildOperationList(cName, 3);
	}

	void HandleJoinGuildReject(CGame* pGame, char* pData)
	{
		char cName[21];
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyJoinGuildReject>(
			pData, sizeof(hb::net::PacketNotifyJoinGuildReject));
		if (!pkt) return;
		std::memset(cName, 0, sizeof(cName));
		memcpy(cName, pkt->guild_name, 20);
		pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::GuildOperation, 0, 0, 0);
		pGame->_PutGuildOperationList(cName, 4);
	}

	void HandleDismissGuildApprove(CGame* pGame, char* pData)
	{
		char cName[24], cLocation[12];
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyDismissGuildApprove>(
			pData, sizeof(hb::net::PacketNotifyDismissGuildApprove));
		if (!pkt) return;
		std::memset(cName, 0, sizeof(cName));
		std::memset(cLocation, 0, sizeof(cLocation));
		memcpy(cName, pkt->guild_name, 20);
		memcpy(cLocation, pkt->location, 10);
		std::memset(pGame->m_cGuildName, 0, sizeof(pGame->m_cGuildName));
		pGame->m_iGuildRank = -1;
		std::memset(pGame->m_cLocation, 0, sizeof(pGame->m_cLocation));
		memcpy(pGame->m_cLocation, cLocation, 10);
		UpdateLocationFlags(pGame, pGame->m_cLocation);
		pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::GuildOperation, 0, 0, 0);
		pGame->_PutGuildOperationList(cName, 5);
	}

	void HandleDismissGuildReject(CGame* pGame, char* pData)
	{
		char cName[21];
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyDismissGuildReject>(
			pData, sizeof(hb::net::PacketNotifyDismissGuildReject));
		if (!pkt) return;
		std::memset(cName, 0, sizeof(cName));
		memcpy(cName, pkt->guild_name, 20);
		pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::GuildOperation, 0, 0, 0);
		pGame->_PutGuildOperationList(cName, 6);
	}

	void HandleQueryJoinGuildPermission(CGame* pGame, char* pData)
	{
		char cName[12];
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyQueryJoinGuildPermission>(
			pData, sizeof(hb::net::PacketNotifyQueryJoinGuildPermission));
		if (!pkt) return;
		std::memset(cName, 0, sizeof(cName));
		memcpy(cName, pkt->name, 10);
		pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::GuildOperation, 0, 0, 0);
		pGame->_PutGuildOperationList(cName, 1);
	}

	void HandleQueryDismissGuildPermission(CGame* pGame, char* pData)
	{
		char cName[12];
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyQueryDismissGuildPermission>(
			pData, sizeof(hb::net::PacketNotifyQueryDismissGuildPermission));
		if (!pkt) return;
		std::memset(cName, 0, sizeof(cName));
		memcpy(cName, pkt->name, 10);
		pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::GuildOperation, 0, 0, 0);
		pGame->_PutGuildOperationList(cName, 2);
	}

	void HandleReqGuildNameAnswer(CGame* pGame, char* pData)
	{
		short sV1, sV2;
		char cTemp[256];
		int i;
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyReqGuildNameAnswer>(
			pData, sizeof(hb::net::PacketNotifyReqGuildNameAnswer));
		if (!pkt) return;
		sV1 = static_cast<short>(pkt->guild_rank);
		sV2 = static_cast<short>(pkt->index);
		std::memset(cTemp, 0, sizeof(cTemp));
		memcpy(cTemp, pkt->guild_name, sizeof(pkt->guild_name));

		std::memset(pGame->m_stGuildName[sV2].cGuildName, 0, sizeof(pGame->m_stGuildName[sV2].cGuildName));
		strcpy(pGame->m_stGuildName[sV2].cGuildName, cTemp);
		pGame->m_stGuildName[sV2].iGuildRank = sV1;
		for (i = 0; i < 20; i++) if (pGame->m_stGuildName[sV2].cGuildName[i] == '_') pGame->m_stGuildName[sV2].cGuildName[i] = ' ';
	}

	void HandleNoGuildMasterLevel(CGame* pGame, char* pData)
	{
		pGame->AddEventList(NOTIFY_MSG_HANDLER59, 10);
	}

	void HandleSuccessBanGuildMan(CGame* pGame, char* pData)
	{
		pGame->AddEventList(NOTIFY_MSG_HANDLER60, 10);
	}

	void HandleCannotBanGuildMan(CGame* pGame, char* pData)
	{
		pGame->AddEventList(NOTIFY_MSG_HANDLER61, 10);
	}
}
