#include "Game.h"
#include "NetworkMessageManager.h"
#include "Packet/SharedPackets.h"
#include "lan_eng.h"
#include "DialogBoxIDs.h"
#include <cstring>
#include <cstdio>


namespace NetworkMessageHandlers {
	void HandleItemToBank(CGame* pGame, char* pData)
	{
		char cIndex;
		DWORD dwCount, dwAttribute;
		char  cName[21], cItemType, cEquipPos, cGenderLimit, cItemColor;
		bool  bIsEquipped;
		short sSprite, sSpriteFrame, sLevelLimit, sItemEffectValue2, sItemSpecEffectValue2;
		WORD wWeight, wCurLifeSpan;
		char  cTxt[120];
		const auto* pkt = hb::net::PacketCast<hb::net::PacketNotifyItemToBank>(
			pData, sizeof(hb::net::PacketNotifyItemToBank));
		if (!pkt) return;

		cIndex = static_cast<char>(pkt->bank_index);
		std::memset(cName, 0, sizeof(cName));
		memcpy(cName, pkt->name, 20);
		dwCount = pkt->count;
		cItemType = static_cast<char>(pkt->item_type);
		cEquipPos = static_cast<char>(pkt->equip_pos);
		bIsEquipped = (pkt->is_equipped != 0);
		sLevelLimit = static_cast<short>(pkt->level_limit);
		cGenderLimit = static_cast<char>(pkt->gender_limit);
		wCurLifeSpan = pkt->cur_lifespan;
		wWeight = pkt->weight;
		sSprite = static_cast<short>(pkt->sprite);
		sSpriteFrame = static_cast<short>(pkt->sprite_frame);
		cItemColor = static_cast<char>(pkt->item_color);
		sItemEffectValue2 = static_cast<short>(pkt->item_effect_value2);
		dwAttribute = pkt->attribute;
		sItemSpecEffectValue2 = static_cast<short>(pkt->spec_effect_value2);

		char cStr1[64], cStr2[64], cStr3[64];
		strcpy(cStr1, cName);
		cStr2[0] = 0;
		cStr3[0] = 0;

		if (pGame->m_pBankList[cIndex] == 0) {
			pGame->m_pBankList[cIndex] = new class CItem;

			memcpy(pGame->m_pBankList[cIndex]->m_cName, cName, 20);
			pGame->m_pBankList[cIndex]->m_dwCount = dwCount;

			pGame->m_pBankList[cIndex]->m_cItemType = cItemType;
			pGame->m_pBankList[cIndex]->m_cEquipPos = cEquipPos;

			pGame->m_pBankList[cIndex]->m_sLevelLimit = sLevelLimit;
			pGame->m_pBankList[cIndex]->m_cGenderLimit = cGenderLimit;
			pGame->m_pBankList[cIndex]->m_wCurLifeSpan = wCurLifeSpan;
			pGame->m_pBankList[cIndex]->m_wWeight = wWeight;
			pGame->m_pBankList[cIndex]->m_sSprite = sSprite;
			pGame->m_pBankList[cIndex]->m_sSpriteFrame = sSpriteFrame;
			pGame->m_pBankList[cIndex]->m_cItemColor = cItemColor;
			pGame->m_pBankList[cIndex]->m_sItemEffectValue2 = sItemEffectValue2;
			pGame->m_pBankList[cIndex]->m_dwAttribute = dwAttribute;
			pGame->m_pBankList[cIndex]->m_sItemSpecEffectValue2 = sItemSpecEffectValue2;

			std::memset(cTxt, 0, sizeof(cTxt));
			if (dwCount == 1) wsprintf(cTxt, NOTIFYMSG_ITEMTOBANK3, cStr1);
			else wsprintf(cTxt, NOTIFYMSG_ITEMTOBANK2, dwCount, cStr1);

			if (pGame->m_dialogBoxManager.IsEnabled(DialogBoxId::Bank) == true)
				pGame->m_dialogBoxManager.Info(DialogBoxId::Bank).sView = DEF_MAXBANKITEMS - 12;
			pGame->AddEventList(cTxt, 10);
		}
	}

	void HandleCannotItemToBank(CGame* pGame, char* pData)
	{
		pGame->AddEventList(NOTIFY_MSG_HANDLER63, 10);
	}
} // namespace NetworkMessageHandlers

