#include "Game.h"
#include "NetworkMessageManager.h"
#include "Packet/SharedPackets.h"
#include "lan_eng.h"
#include "DialogBoxIDs.h"
#include <cstring>
#include <cstdio>

namespace NetworkMessageHandlers {

void HandleParty(CGame* pGame, char* pData)
{
	int i;
	int sV1, sV2, sV3, sV4;
	char cTxt[120];

	const auto* basic = hb::net::PacketCast<hb::net::PacketNotifyPartyBasic>(
		pData, sizeof(hb::net::PacketNotifyPartyBasic));
	
	// If it's a basic packet, extract values. If not, sV1 will be 0 and handled or overwritten later.
	// But mostly this handler handles multiple packet types by casting differently based on type.
	// We should be careful. The original code unconditionally casts to PartyBasic first.
	// PacketNotifyPartyBasic is: header, type(16), v2(16), v3(16), v4(16).
	// This seems to be a common header for party messages.
	
	if (basic) {
		sV1 = basic->type;
		sV2 = basic->v2;
		sV3 = basic->v3;
		sV4 = basic->v4;
	} else {
		// Should not happen if dispatch logic is correct and packet size is sufficient
		return; 
	}

	switch (sV1) {
	case 1: //
		switch (sV2) {
		case 0:
			pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Party, 0, 0, 0);
			pGame->m_dialogBoxManager.Info(DialogBoxId::Party).cMode = 9;
			break;

		case 1:
			pGame->m_iPartyStatus = 1;
			pGame->m_iTotalPartyMember = 0;
			pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Party, 0, 0, 0);
			pGame->m_dialogBoxManager.Info(DialogBoxId::Party).cMode = 8;
			for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) std::memset(pGame->m_stPartyMemberNameList[i].cName, 0, sizeof(pGame->m_stPartyMemberNameList[i].cName));
			pGame->bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_JOINPARTY, 0, 2, 0, 0, pGame->m_cMCName);
			break;
		}
		break;

	case 2: //
		pGame->m_iPartyStatus = 0;
		pGame->m_iTotalPartyMember = 0;
		pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Party, 0, 0, 0);
		pGame->m_dialogBoxManager.Info(DialogBoxId::Party).cMode = 10;
		for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) std::memset(pGame->m_stPartyMemberNameList[i].cName, 0, sizeof(pGame->m_stPartyMemberNameList[i].cName));
		break;

	case 4:
	{
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyPartyName>(
			pData, sizeof(hb::net::PacketNotifyPartyName));
		if (!pkt) return;
		std::memset(cTxt, 0, sizeof(cTxt));
		memcpy(cTxt, pkt->name, sizeof(pkt->name));

		switch (sV2) {
		case 0: //
			pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Party, 0, 0, 0);
			pGame->m_dialogBoxManager.Info(DialogBoxId::Party).cMode = 9;
			break;

		case 1: //
			if (strcmp(cTxt, pGame->m_cPlayerName) == 0) {
				pGame->m_iPartyStatus = 2;
				pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Party, 0, 0, 0);
				pGame->m_dialogBoxManager.Info(DialogBoxId::Party).cMode = 8;
			}
			else {
				wsprintf(pGame->G_cTxt, NOTIFY_MSG_HANDLER1, cTxt);
				pGame->AddEventList(pGame->G_cTxt, 10);
			}

			pGame->m_iTotalPartyMember++;
			for (i = 0; i < DEF_MAXPARTYMEMBERS; i++)
				if (strlen(pGame->m_stPartyMemberNameList[i].cName) == 0) {
					std::memset(pGame->m_stPartyMemberNameList[i].cName, 0, sizeof(pGame->m_stPartyMemberNameList[i].cName));
					memcpy(pGame->m_stPartyMemberNameList[i].cName, cTxt, 10);
					break; // Replaced goto with break
				}
			break;

		case 2: //
			break;
		}
	}
	break;

	case 5: //
		pGame->m_iTotalPartyMember = 0;
		for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) std::memset(pGame->m_stPartyMemberNameList[i].cName, 0, sizeof(pGame->m_stPartyMemberNameList[i].cName));

		{
			const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyPartyList>(
				pData, sizeof(hb::net::PacketNotifyPartyList));
			if (!pkt) return;
			const char* names = pkt->names;
			pGame->m_iTotalPartyMember = pkt->count;
			for (i = 1; i <= pkt->count; i++) {
				std::memset(pGame->m_stPartyMemberNameList[i - 1].cName, 0, sizeof(pGame->m_stPartyMemberNameList[i - 1].cName));
				memcpy(pGame->m_stPartyMemberNameList[i - 1].cName, names, 10);
				names += 11;
			}
		}
		break;

	case 6:
	{
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyPartyName>(
			pData, sizeof(hb::net::PacketNotifyPartyName));
		if (!pkt) return;
		std::memset(cTxt, 0, sizeof(cTxt));
		memcpy(cTxt, pkt->name, sizeof(pkt->name));

		switch (sV2) {
		case 0: //
			pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Party, 0, 0, 0);
			pGame->m_dialogBoxManager.Info(DialogBoxId::Party).cMode = 7;
			break;

		case 1: //
			if (strcmp(cTxt, pGame->m_cPlayerName) == 0) {
				pGame->m_iPartyStatus = 0;
				pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Party, 0, 0, 0);
				pGame->m_dialogBoxManager.Info(DialogBoxId::Party).cMode = 6;
			}
			else {
				wsprintf(pGame->G_cTxt, NOTIFY_MSG_HANDLER2, cTxt);
				pGame->AddEventList(pGame->G_cTxt, 10);
			}
			for (i = 0; i < DEF_MAXPARTYMEMBERS; i++)
				if (strcmp(pGame->m_stPartyMemberNameList[i].cName, cTxt) == 0) {
					std::memset(pGame->m_stPartyMemberNameList[i].cName, 0, sizeof(pGame->m_stPartyMemberNameList[i].cName));
					pGame->m_iTotalPartyMember--;
					break; // Replaced goto with break
				}
			break;
		}
	}
	break;

	case 7: //
		pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Party, 0, 0, 0);
		pGame->m_dialogBoxManager.Info(DialogBoxId::Party).cMode = 9;
		break;

	case 8: //
		pGame->m_iPartyStatus = 0;
		pGame->m_iTotalPartyMember = 0;
		for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) std::memset(pGame->m_stPartyMemberNameList[i].cName, 0, sizeof(pGame->m_stPartyMemberNameList[i].cName));
		break;
	}
}

void HandleQueryJoinParty(CGame* pGame, char* pData)
{
	pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Party, 0, 0, 0);
	pGame->m_dialogBoxManager.Info(DialogBoxId::Party).cMode = 1;
	std::memset(pGame->m_dialogBoxManager.Info(DialogBoxId::Party).cStr, 0, sizeof(pGame->m_dialogBoxManager.Info(DialogBoxId::Party).cStr));
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyQueryJoinParty>(
		pData, sizeof(hb::net::PacketNotifyQueryJoinParty));
	if (!pkt) return;
	strcpy(pGame->m_dialogBoxManager.Info(DialogBoxId::Party).cStr, pkt->name);
}

void HandleResponseCreateNewParty(CGame* pGame, char* pData)
{
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyResponseCreateNewParty>(
		pData, sizeof(hb::net::PacketNotifyResponseCreateNewParty));
	if (!pkt) return;
	if ((bool)pkt->result == true)
	{
		pGame->m_dialogBoxManager.Info(DialogBoxId::Party).cMode = 2;
	}
	else
	{
		pGame->m_dialogBoxManager.Info(DialogBoxId::Party).cMode = 3;
	}
}

} // namespace NetworkMessageHandlers
