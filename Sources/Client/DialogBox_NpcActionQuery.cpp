#include "DialogBox_NpcActionQuery.h"
#include "Game.h"
#include "GlobalDef.h"
#include "lan_eng.h"

DialogBox_NpcActionQuery::DialogBox_NpcActionQuery(CGame* pGame)
	: IDialogBox(DialogBoxId::NpcActionQuery, pGame)
{
	SetDefaultRect(237 + SCREENX, 57 + SCREENY, 252, 87);
}

void DialogBox_NpcActionQuery::DrawHighlightedText(short sX, short sY, const char* text, short msX, short msY, short hitX1, short hitX2, short hitY1, short hitY2)
{
	if ((msX > hitX1) && (msX < hitX2) && (msY > hitY1) && (msY < hitY2)) {
		PutString(sX, sY, (char*)text, RGB(255, 255, 255));
		PutString(sX + 1, sY, (char*)text, RGB(255, 255, 255));
	}
	else {
		PutString(sX, sY, (char*)text, RGB(4, 0, 50));
		PutString(sX + 1, sY, (char*)text, RGB(4, 0, 50));
	}
}

void DialogBox_NpcActionQuery::DrawMode0_NpcMenu(short sX, short sY, short msX, short msY)
{
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 5);

	switch (Info().sV3) {
	case 15:
		PutString(sX + 33, sY + 23, NPC_NAME_SHOP_KEEPER, RGB(45, 25, 25));
		PutString(sX + 33 - 1, sY + 23 - 1, NPC_NAME_SHOP_KEEPER, RGB(255, 255, 255));
		break;
	case 19:
		PutString(sX + 33, sY + 23, NPC_NAME_MAGICIAN, RGB(45, 25, 25));
		PutString(sX + 33 - 1, sY + 23 - 1, NPC_NAME_MAGICIAN, RGB(255, 255, 255));
		break;
	case 20:
		PutString(sX + 33, sY + 23, NPC_NAME_WAREHOUSE_KEEPER, RGB(45, 25, 25));
		PutString(sX + 33 - 1, sY + 23 - 1, NPC_NAME_WAREHOUSE_KEEPER, RGB(255, 255, 255));
		break;
	case 24:
		PutString(sX + 33, sY + 23, NPC_NAME_BLACKSMITH_KEEPER, RGB(45, 25, 25));
		PutString(sX + 33 - 1, sY + 23 - 1, NPC_NAME_BLACKSMITH_KEEPER, RGB(255, 255, 255));
		break;
	case 25:
		PutString(sX + 33, sY + 23, NPC_NAME_CITYHALL_OFFICER, RGB(45, 25, 25));
		PutString(sX + 33 - 1, sY + 23 - 1, NPC_NAME_CITYHALL_OFFICER, RGB(255, 255, 255));
		break;
	case 26:
		PutString(sX + 33, sY + 23, NPC_NAME_GUILDHALL_OFFICER, RGB(45, 25, 25));
		PutString(sX + 33 - 1, sY + 23 - 1, NPC_NAME_GUILDHALL_OFFICER, RGB(255, 255, 255));
		break;
	case 90:
		PutString(sX + 33, sY + 23, "Heldenian staff officer", RGB(45, 25, 25));
		PutString(sX + 33 - 1, sY + 23 - 1, "Heldenian staff officer", RGB(255, 255, 255));
		break;
	}

	if (Info().sV3 == 25) {
		// OFFER
		DrawHighlightedText(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY13, msX, msY, sX + 25, sX + 100, sY + 55, sY + 70);
	}
	else if (Info().sV3 == 20) {
		// WITHDRAW
		DrawHighlightedText(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY17, msX, msY, sX + 25, sX + 100, sY + 55, sY + 70);
	}
	else if (Info().sV3 == 19) {
		// LEARN
		DrawHighlightedText(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY19, msX, msY, sX + 25, sX + 100, sY + 55, sY + 70);
	}
	else {
		// TRADE
		DrawHighlightedText(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, msX, msY, sX + 25, sX + 100, sY + 55, sY + 70);
	}

	if (m_pGame->m_dialogBoxManager.IsEnabled(DialogBoxId::NpcTalk) == false) {
		DrawHighlightedText(sX + 125, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, msX, msY, sX + 125, sX + 180, sY + 55, sY + 70);
	}
}

void DialogBox_NpcActionQuery::DrawMode1_GiveToPlayer(short sX, short sY, short msX, short msY)
{
	char cTxt[120], cTxt2[120], cStr1[64], cStr2[64], cStr3[64];
	std::memset(cStr1, 0, sizeof(cStr1));
	std::memset(cStr2, 0, sizeof(cStr2));
	std::memset(cStr3, 0, sizeof(cStr3));

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 6);
	m_pGame->GetItemName(m_pGame->m_pItemList[Info().sV1], cStr1, cStr2, cStr3);
	wsprintf(cTxt, DRAW_DIALOGBOX_NPCACTION_QUERY29, Info().sV3, cStr1);
	wsprintf(cTxt2, DRAW_DIALOGBOX_NPCACTION_QUERY29_1, Info().cStr);

	PutString(sX + 24, sY + 25, cTxt, RGB(45, 25, 25));
	PutString(sX + 24, sY + 40, cTxt2, RGB(45, 25, 25));

	DrawHighlightedText(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY30, msX, msY, sX + 25, sX + 100, sY + 55, sY + 70);
	DrawHighlightedText(sX + 155, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY34, msX, msY, sX + 155, sX + 210, sY + 55, sY + 70);
}

void DialogBox_NpcActionQuery::DrawMode2_SellToShop(short sX, short sY, short msX, short msY)
{
	char cTxt[120], cTxt2[120], cStr1[64], cStr2[64], cStr3[64];
	std::memset(cStr1, 0, sizeof(cStr1));
	std::memset(cStr2, 0, sizeof(cStr2));
	std::memset(cStr3, 0, sizeof(cStr3));

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 5);
	m_pGame->GetItemName(m_pGame->m_pItemList[Info().sV1], cStr1, cStr2, cStr3);

	wsprintf(cTxt, DRAW_DIALOGBOX_NPCACTION_QUERY29, Info().sV3, cStr1);
	wsprintf(cTxt2, DRAW_DIALOGBOX_NPCACTION_QUERY29_1, Info().cStr);

	PutString(sX + 24, sY + 20, cTxt, RGB(45, 25, 25));
	PutString(sX + 24, sY + 35, cTxt2, RGB(45, 25, 25));

	DrawHighlightedText(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY39, msX, msY, sX + 25, sX + 100, sY + 55, sY + 70);

	if ((m_pGame->m_pItemList[Info().sV1]->m_cItemType != DEF_ITEMTYPE_CONSUME) &&
		(m_pGame->m_pItemList[Info().sV1]->m_cItemType != DEF_ITEMTYPE_ARROW))
	{
		DrawHighlightedText(sX + 125, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY43, msX, msY, sX + 125, sX + 180, sY + 55, sY + 70);
	}
}

void DialogBox_NpcActionQuery::DrawMode3_DepositToWarehouse(short sX, short sY, short msX, short msY)
{
	char cTxt[120], cTxt2[120], cStr1[64], cStr2[64], cStr3[64];
	std::memset(cStr1, 0, sizeof(cStr1));
	std::memset(cStr2, 0, sizeof(cStr2));
	std::memset(cStr3, 0, sizeof(cStr3));

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 6);
	m_pGame->GetItemName(m_pGame->m_pItemList[Info().sV1], cStr1, cStr2, cStr3);

	wsprintf(cTxt, DRAW_DIALOGBOX_NPCACTION_QUERY29, Info().sV3, cStr1);
	wsprintf(cTxt2, DRAW_DIALOGBOX_NPCACTION_QUERY29_1, Info().cStr);

	PutAlignedString(sX, sX + 240, sY + 20, cTxt, 45, 25, 25);
	PutAlignedString(sX, sX + 240, sY + 35, cTxt2, 45, 25, 25);

	DrawHighlightedText(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY48, msX, msY, sX + 25, sX + 100, sY + 55, sY + 70);
}

void DialogBox_NpcActionQuery::DrawMode4_TalkToNpcOrUnicorn(short sX, short sY, short msX, short msY)
{
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 5);

	switch (Info().sV3) {
	case 21:
		PutString(sX + 35, sY + 25, NPC_NAME_GUARD, RGB(45, 25, 25));
		PutString(sX + 35 - 1, sY + 25 - 1, NPC_NAME_GUARD, RGB(255, 255, 255));
		break;
	case 32:
		PutString(sX + 35, sY + 25, NPC_NAME_UNICORN, RGB(45, 25, 25));
		PutString(sX + 35 - 1, sY + 25 - 1, NPC_NAME_UNICORN, RGB(255, 255, 255));
		break;
	case 67:
		PutString(sX + 35, sY + 25, NPC_NAME_MCGAFFIN, RGB(45, 25, 25));
		PutString(sX + 35 - 1, sY + 25 - 1, NPC_NAME_MCGAFFIN, RGB(255, 255, 255));
		break;
	case 68:
		PutString(sX + 35, sY + 25, NPC_NAME_PERRY, RGB(45, 25, 25));
		PutString(sX + 35 - 1, sY + 25 - 1, NPC_NAME_PERRY, RGB(255, 255, 255));
		break;
	case 69:
		PutString(sX + 35, sY + 25, NPC_NAME_DEVLIN, RGB(45, 25, 25));
		PutString(sX + 35 - 1, sY + 25 - 1, NPC_NAME_DEVLIN, RGB(255, 255, 255));
		break;
	}

	if (m_pGame->m_dialogBoxManager.IsEnabled(DialogBoxId::NpcTalk) == false) {
		DrawHighlightedText(sX + 125, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, msX, msY, sX + 125, sX + 180, sY + 55, sY + 70);
	}
}

void DialogBox_NpcActionQuery::DrawMode5_ShopWithSell(short sX, short sY, short msX, short msY)
{
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 6);

	switch (Info().sV3) {
	case 15:
		PutString(sX + 33, sY + 23, NPC_NAME_SHOP_KEEPER, RGB(45, 25, 25));
		PutString(sX + 33 - 1, sY + 23 - 1, NPC_NAME_SHOP_KEEPER, RGB(255, 255, 255));
		break;
	case 24:
		PutString(sX + 33, sY + 23, NPC_NAME_BLACKSMITH_KEEPER, RGB(45, 25, 25));
		PutString(sX + 33 - 1, sY + 23 - 1, NPC_NAME_BLACKSMITH_KEEPER, RGB(255, 255, 255));
		// Repair All button
		DrawHighlightedText(sX + 155, sY + 22, DRAW_DIALOGBOX_NPCACTION_QUERY49, msX, msY, sX + 155, sX + 210, sY + 22, sY + 37);
		break;
	}

	// Trade
	DrawHighlightedText(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, msX, msY, sX + 25, sX + 100, sY + 55, sY + 70);

	// Sell
	DrawHighlightedText(sX + 28 + 75, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY39, msX, msY, sX + 25 + 79, sX + 80 + 75, sY + 55, sY + 70);

	if (m_pGame->m_dialogBoxManager.IsEnabled(DialogBoxId::NpcTalk) == false) {
		DrawHighlightedText(sX + 155, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, msX, msY, sX + 155, sX + 210, sY + 55, sY + 70);
	}
}

void DialogBox_NpcActionQuery::DrawMode6_Gail(short sX, short sY, short msX, short msY)
{
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 5);

	DrawHighlightedText(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, msX, msY, sX + 25, sX + 100, sY + 55, sY + 70);

	PutString(sX + 33, sY + 23, "Heldenian staff officer", RGB(45, 25, 25));
	PutString(sX + 33 - 1, sY + 23 - 1, "Heldenian staff officer", RGB(255, 255, 255));
}

void DialogBox_NpcActionQuery::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;

	switch (Info().cMode) {
	case 0:
		DrawMode0_NpcMenu(sX, sY, msX, msY);
		break;
	case 1:
		DrawMode1_GiveToPlayer(sX, sY, msX, msY);
		break;
	case 2:
		DrawMode2_SellToShop(sX, sY, msX, msY);
		break;
	case 3:
		DrawMode3_DepositToWarehouse(sX, sY, msX, msY);
		break;
	case 4:
		DrawMode4_TalkToNpcOrUnicorn(sX, sY, msX, msY);
		break;
	case 5:
		DrawMode5_ShopWithSell(sX, sY, msX, msY);
		break;
	case 6:
		DrawMode6_Gail(sX, sY, msX, msY);
		break;
	}
}

bool DialogBox_NpcActionQuery::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;
	int absX, absY;

	if (m_pGame->m_dialogBoxManager.IsEnabled(DialogBoxId::Exchange) == true) {
		AddEventList(BITEMDROP_SKILLDIALOG1, 10);
		return true;
	}

	switch (Info().cMode) {
	case 0: // Talk to npc
		if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70)) {
			EnableDialogBox((DialogBoxId::Type)Info().sV1, Info().sV2, 0, 0);
			DisableThisDialog();
			return true;
		}
		if ((m_pGame->m_dialogBoxManager.IsEnabled(DialogBoxId::NpcTalk) == false) && (msX > sX + 125) && (msX < sX + 180) && (msY > sY + 55) && (msY < sY + 70)) {
			switch (Info().sV1) {
			case 7:
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 1, 0, 0, 0);
				AddEventList(TALKING_TO_GUILDHALL_OFFICER, 10);
				break;
			case 11:
				switch (Info().sV2) {
				case 1:
					bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 2, 0, 0, 0);
					AddEventList(TALKING_TO_SHOP_KEEPER, 10);
					break;
				case 2:
					bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 3, 0, 0, 0);
					AddEventList(TALKING_TO_BLACKSMITH_KEEPER, 10);
					break;
				}
				break;
			case 13:
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 4, 0, 0, 0);
				AddEventList(TALKING_TO_CITYHALL_OFFICER, 10);
				break;
			case 14:
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 5, 0, 0, 0);
				AddEventList(TALKING_TO_WAREHOUSE_KEEPER, 10);
				break;
			case 16:
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 6, 0, 0, 0);
				AddEventList(TALKING_TO_MAGICIAN, 10);
				break;
			}
			DisableThisDialog();
			return true;
		}
		break;

	case 1: // On other player
		if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70)) {
			absX = abs(Info().sV5 - m_pGame->m_sPlayerX);
			absY = abs(Info().sV6 - m_pGame->m_sPlayerY);
			if ((absX <= 4) && (absY <= 4))
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GIVEITEMTOCHAR, Info().sV1, Info().sV3, Info().sV5, Info().sV6, m_pGame->m_pItemList[Info().sV1]->m_cName, Info().sV4);
			else AddEventList(DLGBOX_CLICK_NPCACTION_QUERY7, 10);
			DisableThisDialog();
			return true;
		}
		else if ((msX > sX + 155) && (msX < sX + 210) && (msY > sY + 55) && (msY < sY + 70)) {
			absX = abs(Info().sV5 - m_pGame->m_sPlayerX);
			absY = abs(Info().sV6 - m_pGame->m_sPlayerY);
			if ((absX <= 4) && (absY <= 4))
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_EXCHANGEITEMTOCHAR, Info().sV1, Info().sV3, Info().sV5, Info().sV6, m_pGame->m_pItemList[Info().sV1]->m_cName, Info().sV4);
			else AddEventList(DLGBOX_CLICK_NPCACTION_QUERY8, 10);
			DisableThisDialog();
			return true;
		}
		break;

	case 2: // Item on Shop/BS
		if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70)) {
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_SELLITEM, 0, Info().sV1, Info().sV2, Info().sV3, m_pGame->m_pItemList[Info().sV1]->m_cName, Info().sV4);
			DisableThisDialog();
			return true;
		}
		else if ((msX > sX + 125) && (msX < sX + 180) && (msY > sY + 55) && (msY < sY + 70)) {
			if (Info().sV3 == 1) {
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_REPAIRITEM, 0, Info().sV1, Info().sV2, 0, m_pGame->m_pItemList[Info().sV1]->m_cName, Info().sV4);
				DisableThisDialog();
				return true;
			}
		}
		break;

	case 3: // Put item in the WH
		if ((msX > sX + 25) && (msX < sX + 105) && (msY > sY + 55) && (msY < sY + 70)) {
			absX = abs(Info().sV5 - m_pGame->m_sPlayerX);
			absY = abs(Info().sV6 - m_pGame->m_sPlayerY);
			if ((absX <= 8) && (absY <= 8)) {
				if (m_pGame->_iGetBankItemCount() >= (m_pGame->iMaxBankItems - 1)) {
					AddEventList(DLGBOX_CLICK_NPCACTION_QUERY9, 10);
				}
				else bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GIVEITEMTOCHAR, Info().sV1, Info().sV3, Info().sV5, Info().sV6, m_pGame->m_pItemList[Info().sV1]->m_cName, Info().sV4);
			}
			else AddEventList(DLGBOX_CLICK_NPCACTION_QUERY7, 10);
			DisableThisDialog();
			return true;
		}
		break;

	case 4: // talk to npc or Unicorn
		if ((m_pGame->m_dialogBoxManager.IsEnabled(DialogBoxId::NpcTalk) == false) && (msX > sX + 125) && (msX < sX + 180) && (msY > sY + 55) && (msY < sY + 70)) {
			switch (Info().sV3) {
			case 21:
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 21, 0, 0, 0);
				AddEventList(TALKING_TO_GUARD, 10);
				break;
			case 32:
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 32, 0, 0, 0);
				AddEventList(TALKING_TO_UNICORN, 10);
				break;
			case 67:
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 67, 0, 0, 0);
				AddEventList(TALKING_TO_MCGAFFIN, 10);
				break;
			case 68:
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 68, 0, 0, 0);
				AddEventList(TALKING_TO_PERRY, 10);
				break;
			case 69:
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 69, 0, 0, 0);
				AddEventList(TALKING_TO_DEVLIN, 10);
				break;
			}
		}
		DisableThisDialog();
		return true;

	case 5: // Talk
		if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70)) {
			EnableDialogBox((DialogBoxId::Type)Info().sV1, Info().sV2, 0, 0);
			DisableThisDialog();
			return true;
		}
		if ((msX > sX + 25 + 75) && (msX < sX + 80 + 75) && (msY > sY + 55) && (msY < sY + 70)) {
			EnableDialogBox(DialogBoxId::SellList, 0, 0, 0);
			DisableThisDialog();
			return true;
		}
		if ((m_pGame->m_dialogBoxManager.IsEnabled(DialogBoxId::NpcTalk) == false) && (msX > sX + 155) && (msX < sX + 210) && (msY > sY + 55) && (msY < sY + 70)) {
			switch (Info().sV1) {
			case 7:
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 1, 0, 0, 0);
				AddEventList(TALKING_TO_GUILDHALL_OFFICER, 10);
				break;
			case 11:
				switch (Info().sV2) {
				case 1:
					bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 2, 0, 0, 0);
					AddEventList(TALKING_TO_SHOP_KEEPER, 10);
					break;
				case 2:
					bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 3, 0, 0, 0);
					AddEventList(TALKING_TO_BLACKSMITH_KEEPER, 10);
					break;
				}
				break;
			case 13:
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 4, 0, 0, 0);
				AddEventList(TALKING_TO_CITYHALL_OFFICER, 10);
				break;
			case 14:
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 5, 0, 0, 0);
				AddEventList(TALKING_TO_WAREHOUSE_KEEPER, 10);
				break;
			case 16:
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 6, 0, 0, 0);
				AddEventList(TALKING_TO_MAGICIAN, 10);
				break;
			}
			DisableThisDialog();
			return true;
		}
		// Repair All
		if ((msX > sX + 155) && (msX < sX + 210) && (msY > sY + 22) && (msY < sY + 37)) {
			if (Info().sV3 == 24) {
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_REPAIRALL, 0, 0, 0, 0, 0, 0);
				DisableThisDialog();
				return true;
			}
		}
		break;

	case 6: // Gail
		if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70)) {
			EnableDialogBox(DialogBoxId::GuildHallMenu, 0, 0, 0);
			DisableThisDialog();
			return true;
		}
		break;
	}

	return false;
}
