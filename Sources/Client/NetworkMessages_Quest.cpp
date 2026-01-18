#include "Game.h"
#include "NetworkMessageManager.h"
#include "Packet/SharedPackets.h"
#include "lan_eng.h"
#include "DialogBoxIDs.h"
#include <cstdio>
#include <cstring>
#include <windows.h>

namespace NetworkMessageHandlers {

void HandleQuestCounter(CGame* pGame, char* pData)
{
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyQuestCounter>(
		pData, sizeof(hb::net::PacketNotifyQuestCounter));
	if (!pkt) return;
	pGame->m_stQuest.sCurrentCount = static_cast<short>(pkt->current_count);
}

void HandleQuestContents(CGame* pGame, char* pData)
{
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyQuestContents>(
		pData, sizeof(hb::net::PacketNotifyQuestContents));
	if (!pkt) return;
	pGame->m_stQuest.sWho = pkt->who;
	pGame->m_stQuest.sQuestType = pkt->quest_type;
	pGame->m_stQuest.sContribution = pkt->contribution;
	pGame->m_stQuest.sTargetType = pkt->target_type;
	pGame->m_stQuest.sTargetCount = pkt->target_count;
	pGame->m_stQuest.sX = pkt->x;
	pGame->m_stQuest.sY = pkt->y;
	pGame->m_stQuest.sRange = pkt->range;
	pGame->m_stQuest.bIsQuestCompleted = (pkt->is_completed != 0);
	std::memset(pGame->m_stQuest.cTargetName, 0, sizeof(pGame->m_stQuest.cTargetName));
	memcpy(pGame->m_stQuest.cTargetName, pkt->target_name, 20);
}

void HandleQuestReward(CGame* pGame, char* pData)
{
	short sWho, sFlag;
	char cRewardName[21], cTxt[120];
	int iAmount, iIndex, iPreCon;
	const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyQuestReward>(
		pData, sizeof(hb::net::PacketNotifyQuestReward));
	if (!pkt) return;
	sWho = pkt->who;
	sFlag = pkt->flag;
	iAmount = pkt->amount;
	std::memset(cRewardName, 0, sizeof(cRewardName));
	memcpy(cRewardName, pkt->reward_name, 20);
	iPreCon = pGame->m_iContribution;
	pGame->m_iContribution = pkt->contribution;

	if (sFlag == 1)
	{
		pGame->m_stQuest.sWho = 0;
		pGame->m_stQuest.sQuestType = 0;
		pGame->m_stQuest.sContribution = 0;
		pGame->m_stQuest.sTargetType = 0;
		pGame->m_stQuest.sTargetCount = 0;
		pGame->m_stQuest.sX = 0;
		pGame->m_stQuest.sY = 0;
		pGame->m_stQuest.sRange = 0;
		pGame->m_stQuest.sCurrentCount = 0;
		pGame->m_stQuest.bIsQuestCompleted = false;
		std::memset(pGame->m_stQuest.cTargetName, 0, sizeof(pGame->m_stQuest.cTargetName));
		pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::NpcTalk, 0, sWho + 110, 0);
		iIndex = pGame->m_dialogBoxManager.Info(DialogBoxId::NpcTalk).sV1;
		pGame->m_pMsgTextList2[iIndex] = new class CMsg(0, "  ", 0);
		iIndex++;
		std::memset(cTxt, 0, sizeof(cTxt));
		if (memcmp(cRewardName, "ġ", 6) == 0)
		{
			if (iAmount > 0) wsprintf(cTxt, NOTIFYMSG_QUEST_REWARD1, iAmount);
		}
		else
		{
			wsprintf(cTxt, NOTIFYMSG_QUEST_REWARD2, iAmount, cRewardName);
		}
		pGame->m_pMsgTextList2[iIndex] = new class CMsg(0, cTxt, 0);
		iIndex++;
		pGame->m_pMsgTextList2[iIndex] = new class CMsg(0, "  ", 0);
		iIndex++;
		std::memset(cTxt, 0, sizeof(cTxt));
		if (iPreCon < pGame->m_iContribution)
			wsprintf(cTxt, NOTIFYMSG_QUEST_REWARD3, pGame->m_iContribution - iPreCon);
		else wsprintf(cTxt, NOTIFYMSG_QUEST_REWARD4, iPreCon - pGame->m_iContribution);

		pGame->m_pMsgTextList2[iIndex] = new class CMsg(0, "  ", 0);
		iIndex++;
	}
	else pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::NpcTalk, 0, sWho + 120, 0);
}

void HandleQuestCompleted(CGame* pGame, char* pData)
{
	pGame->m_stQuest.bIsQuestCompleted = true;
	pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::Quest);
	pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Quest, 1, 0, 0);
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
	pGame->PlaySound('E', 23, 0);
	pGame->AddEventList(NOTIFY_MSG_HANDLER44, 10);
}

void HandleQuestAborted(CGame* pGame, char* pData)
{
	pGame->m_stQuest.sQuestType = 0;
	pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::Quest);
	pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Quest, 2, 0, 0);
}

} // namespace NetworkMessageHandlers
