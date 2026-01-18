#include "DialogBox_Manufacture.h"
#include "Game.h"
#include "GlobalDef.h"
#include "SpriteID.h"
#include "lan_eng.h"
#include "NetMessages.h"
#include "InputManager.h"

DialogBox_Manufacture::DialogBox_Manufacture(CGame* pGame)
	: IDialogBox(DialogBoxId::Manufacture, pGame)
{
}

void DialogBox_Manufacture::OnDraw(short msX, short msY, short msZ, char cLB)
{
	int iAdjX = 5;
	int iAdjY = 8;
	short sX, sY;

	switch (Info().cMode) {
	case 1: // Alchemy waiting for ingredients
		if (Info().cStr[0] != 0)
		{
			sX = Info().sX + iAdjX + (Info().cStr[0] - (rand() % (Info().cStr[0] * 2)));
			sY = Info().sY + iAdjY + (Info().cStr[0] - (rand() % (Info().cStr[0] * 2)));
		}
		else
		{
			sX = Info().sX;
			sY = Info().sY;
		}
		DrawAlchemyWaiting(sX, sY, msX, msY);
		break;

	case 2: // Alchemy creating potion
		if (Info().cStr[0] != 0)
		{
			sX = Info().sX + iAdjX + (Info().cStr[0] - (rand() % (Info().cStr[0] * 2)));
			sY = Info().sY + iAdjY + (Info().cStr[0] - (rand() % (Info().cStr[0] * 2)));
		}
		else
		{
			sX = Info().sX;
			sY = Info().sY;
		}
		DrawAlchemyCreating(sX, sY);
		break;

	case 3: // Manufacture: item list
		sX = Info().sX;
		sY = Info().sY;
		DrawManufactureList(sX, sY, msX, msY, msZ, cLB);
		break;

	case 4: // Manufacture: waiting for ingredients
		sX = Info().sX;
		sY = Info().sY;
		DrawManufactureWaiting(sX, sY, msX, msY);
		break;

	case 5: // Manufacture: in progress
		sX = Info().sX;
		sY = Info().sY;
		DrawManufactureInProgress(sX, sY);
		break;

	case 6: // Manufacture: done
		sX = Info().sX;
		sY = Info().sY;
		DrawManufactureDone(sX, sY, msX, msY);
		break;

	case 7: // Crafting: waiting for ingredients
		if (Info().cStr[0] != 0)
		{
			sX = Info().sX + iAdjX + (Info().cStr[0] - (rand() % (Info().cStr[0] * 2)));
			sY = Info().sY + iAdjY + (Info().cStr[0] - (rand() % (Info().cStr[0] * 2)));
		}
		else
		{
			sX = Info().sX;
			sY = Info().sY;
		}
		DrawCraftingWaiting(sX, sY, msX, msY);
		break;

	case 8: // Crafting: in progress
		if (Info().cStr[0] != 0)
		{
			sX = Info().sX + 5 + (Info().cStr[0] - (rand() % (Info().cStr[0] * 2)));
			sY = Info().sY + 8 + (Info().cStr[0] - (rand() % (Info().cStr[0] * 2)));
		}
		else
		{
			sX = Info().sX;
			sY = Info().sY;
		}
		DrawCraftingInProgress(sX, sY);
		break;
	}
}

void DialogBox_Manufacture::DrawAlchemyWaiting(short sX, short sY, short msX, short msY)
{
	int iAdjX = 5;
	int iAdjY = 8;
	uint32_t dwTime = m_pGame->m_dwCurTime;

	m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX, sY, 1, dwTime);

	if (Info().sV1 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
		m_pGame->m_pItemList[Info().sV1]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)),
			m_pGame->m_pItemList[Info().sV1]->m_sSpriteFrame, dwTime);

	if (Info().sV2 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
		m_pGame->m_pItemList[Info().sV2]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + 45 * 1 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)),
			m_pGame->m_pItemList[Info().sV2]->m_sSpriteFrame, dwTime);

	if (Info().sV3 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
		m_pGame->m_pItemList[Info().sV3]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + 45 * 2 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)),
			m_pGame->m_pItemList[Info().sV3]->m_sSpriteFrame, dwTime);

	if (Info().sV4 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
		m_pGame->m_pItemList[Info().sV4]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)),
			m_pGame->m_pItemList[Info().sV4]->m_sSpriteFrame, dwTime);

	if (Info().sV5 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
		m_pGame->m_pItemList[Info().sV5]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + 45 * 1 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)),
			m_pGame->m_pItemList[Info().sV5]->m_sSpriteFrame, dwTime);

	if (Info().sV6 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
		m_pGame->m_pItemList[Info().sV6]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + 45 * 2 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)),
			m_pGame->m_pItemList[Info().sV6]->m_sSpriteFrame, dwTime);

	if ((msX >= sX + iAdjX + 60) && (msX <= sX + iAdjX + 153) && (msY >= sY + iAdjY + 175) && (msY <= sY + iAdjY + 195))
		m_pGame->PutString_SprFont(sX + iAdjX + 60, sY + iAdjY + 175, "Try Now!", 16, 16, 30);
	else m_pGame->PutString_SprFont(sX + iAdjX + 60, sY + iAdjY + 175, "Try Now!", 6, 6, 20);
}

void DialogBox_Manufacture::DrawAlchemyCreating(short sX, short sY)
{
	int iAdjX = 5;
	int iAdjY = 8;
	uint32_t dwTime = m_pGame->m_dwCurTime;

	m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX, sY, 1, dwTime);

	if (Info().sV1 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
		m_pGame->m_pItemList[Info().sV1]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)),
			m_pGame->m_pItemList[Info().sV1]->m_sSpriteFrame, dwTime);

	if (Info().sV2 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
		m_pGame->m_pItemList[Info().sV2]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + 45 * 1 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)),
			m_pGame->m_pItemList[Info().sV2]->m_sSpriteFrame, dwTime);

	if (Info().sV3 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
		m_pGame->m_pItemList[Info().sV3]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + 45 * 2 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)),
			m_pGame->m_pItemList[Info().sV3]->m_sSpriteFrame, dwTime);

	if (Info().sV4 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
		m_pGame->m_pItemList[Info().sV4]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)),
			m_pGame->m_pItemList[Info().sV4]->m_sSpriteFrame, dwTime);

	if (Info().sV5 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
		m_pGame->m_pItemList[Info().sV5]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + 45 * 1 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)),
			m_pGame->m_pItemList[Info().sV5]->m_sSpriteFrame, dwTime);

	if (Info().sV6 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
		m_pGame->m_pItemList[Info().sV6]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + 45 * 2 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)),
			m_pGame->m_pItemList[Info().sV6]->m_sSpriteFrame, dwTime);

	m_pGame->PutString_SprFont(sX + iAdjX + 60, sY + iAdjY + 175, "Creating...", 20, 6, 6);

	if ((dwTime - Info().dwT1) > 1000)
	{
		Info().dwT1 = dwTime;
		Info().cStr[0]++;
	}

	if (Info().cStr[0] >= 5)
	{
		m_pGame->bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_CREATEPORTION, 0, 0, 0, 0, 0);
		m_pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::Manufacture);
		m_pGame->PlaySound('E', 42, 0);
	}
}

void DialogBox_Manufacture::DrawManufactureList(short sX, short sY, short msX, short msY, short msZ, char cLB)
{
	int iAdjX = 5;
	int iAdjY = 8;
	uint32_t dwTime = m_pGame->m_dwCurTime;
	short szX = Info().sSizeX;
	char cTemp[120], cTemp2[120];
	char cStr1[64], cStr2[64], cStr3[64];
	int iLoc;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 0);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 8);
	PutString(sX + iAdjX + 44, sY + iAdjY + 38, "Name", RGB(0, 0, 0));
	PutString(sX + iAdjX + 171, sY + iAdjY + 38, "Max.Skill", RGB(0, 0, 0));

	iLoc = 0;
	for (int i = 0; i < 13; i++)
		if (m_pGame->m_pDispBuildItemList[i + Info().sView] != 0) {

			std::memset(cTemp, 0, sizeof(cTemp));
			m_pGame->GetItemName(m_pGame->FindItemIdByName(m_pGame->m_pDispBuildItemList[i + Info().sView]->m_cName), 0, cStr1, cStr2, cStr3);
			wsprintf(cTemp, "%s", cStr1);
			std::memset(cTemp2, 0, sizeof(cTemp2));
			wsprintf(cTemp2, "%d%%", m_pGame->m_pDispBuildItemList[i + Info().sView]->m_iMaxSkill);

			if ((msX >= sX + 30) && (msX <= sX + 180) && (msY >= sY + iAdjY + 55 + iLoc * 15) && (msY <= sY + iAdjY + 69 + iLoc * 15))
			{
				PutString(sX + 30, sY + iAdjY + 55 + iLoc * 15, cTemp, RGB(255, 255, 255));
				PutString(sX + 190, sY + iAdjY + 55 + iLoc * 15, cTemp2, RGB(255, 255, 255));
			}
			else
			{
				if (m_pGame->m_pDispBuildItemList[i + Info().sView]->m_bBuildEnabled == true)
				{
					PutString(sX + 30, sY + iAdjY + 55 + iLoc * 15, cTemp, RGB(34, 30, 120));
					PutString(sX + 190, sY + iAdjY + 55 + iLoc * 15, cTemp2, RGB(34, 30, 120));
				}
				else
				{
					PutString(sX + 30, sY + iAdjY + 55 + iLoc * 15, cTemp, RGB(45, 25, 25));
					PutString(sX + 190, sY + iAdjY + 55 + iLoc * 15, cTemp2, RGB(45, 25, 25));
				}
			}
			iLoc++;
		}

	if ((Info().sView >= 1) && (m_pGame->m_pDispBuildItemList[Info().sView - 1] != 0))
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutSpriteFast(sX + iAdjX + 225, sY + iAdjY + 210, 23, dwTime);
	else m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutTransSpriteRGB(sX + iAdjX + 225, sY + iAdjY + 210, 23, 5, 5, 5, dwTime);

	if (m_pGame->m_pDispBuildItemList[Info().sView + 13] != 0)
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutSpriteFast(sX + iAdjX + 225, sY + iAdjY + 230, 24, dwTime);
	else m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutTransSpriteRGB(sX + iAdjX + 225, sY + iAdjY + 230, 24, 5, 5, 5, dwTime);

	if ((cLB != 0) && (m_pGame->m_dialogBoxManager.iGetTopDialogBoxIndex() == DialogBoxId::Manufacture)) {
		if ((msX >= sX + iAdjX + 225) && (msX <= sX + iAdjX + 245) && (msY >= sY + iAdjY + 210) && (msY <= sY + iAdjY + 230)) {
			Info().sView--;
		}

		if ((msX >= sX + iAdjX + 225) && (msX <= sX + iAdjX + 245) && (msY >= sY + iAdjY + 230) && (msY <= sY + iAdjY + 250)) {
			if (m_pGame->m_pDispBuildItemList[Info().sView + 13] != 0)
				Info().sView++;
		}
	}
	if ((msZ != 0) && (m_pGame->m_dialogBoxManager.iGetTopDialogBoxIndex() == DialogBoxId::Manufacture)) {
		Info().sView = Info().sView - msZ / 60;
		InputManager::Get().ClearWheelDelta();
	}
	if (m_pGame->m_pDispBuildItemList[Info().sView + 12] == 0)
	{
		while (1)
		{
			Info().sView--;
			if (Info().sView < 1) break;
			if (m_pGame->m_pDispBuildItemList[Info().sView + 12] != 0) break;
		}
	}
	if (Info().sView < 0) Info().sView = 0;

	PutAlignedString(sX, sX + Info().sSizeX, sY + 265, DRAW_DIALOGBOX_SKILLDLG2, 55, 25, 25);
	PutAlignedString(sX, sX + Info().sSizeX, sY + 280, DRAW_DIALOGBOX_SKILLDLG3, 55, 25, 25);
	PutAlignedString(sX, sX + Info().sSizeX, sY + 295, DRAW_DIALOGBOX_SKILLDLG4, 55, 25, 25);
	PutAlignedString(sX, sX + Info().sSizeX, sY + 310, DRAW_DIALOGBOX_SKILLDLG5, 55, 25, 25);
	PutAlignedString(sX, sX + Info().sSizeX, sY + 340, DRAW_DIALOGBOX_SKILLDLG6, 55, 25, 25);
}

void DialogBox_Manufacture::DrawManufactureWaiting(short sX, short sY, short msX, short msY)
{
	int iAdjX = -1;
	int iAdjY = -7;
	uint32_t dwTime = m_pGame->m_dwCurTime;
	short szX = Info().sSizeX;
	char cTemp[120];
	char cStr1[64], cStr2[64], cStr3[64];
	int iLoc;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 0);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 8);
	m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_iSprH]->PutSpriteFast(sX + iAdjX + 62 + 5, sY + iAdjY + 84 + 17,
		m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_iSprFrame, dwTime);

	std::memset(cTemp, 0, sizeof(cTemp));
	m_pGame->GetItemName(m_pGame->FindItemIdByName(m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_cName), 0, cStr1, cStr2, cStr3);
	wsprintf(cTemp, "%s", cStr1);
	PutString(sX + iAdjX + 44 + 10 + 60, sY + iAdjY + 55, cTemp, RGB(255, 255, 255));

	wsprintf(cTemp, DRAW_DIALOGBOX_SKILLDLG7
		, m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_iSkillLimit
		, m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_iMaxSkill);
	PutString(sX + iAdjX + 44 + 10 + 60, sY + iAdjY + 55 + 2 * 15, cTemp, RGB(45, 25, 25));
	PutString(sX + iAdjX + 44 + 10 + 60, sY + iAdjY + 55 + 3 * 15 + 5, DRAW_DIALOGBOX_SKILLDLG8, RGB(45, 25, 25));

	iLoc = 4;
	for (int elem = 1; elem <= 6; elem++)
	{
		if (m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_iElementCount[elem] != 0)
		{
			char* elemName = nullptr;
			bool elemFlag = false;
			switch (elem) {
			case 1: elemName = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_cElementName1; elemFlag = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_bElementFlag[1]; break;
			case 2: elemName = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_cElementName2; elemFlag = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_bElementFlag[2]; break;
			case 3: elemName = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_cElementName3; elemFlag = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_bElementFlag[3]; break;
			case 4: elemName = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_cElementName4; elemFlag = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_bElementFlag[4]; break;
			case 5: elemName = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_cElementName5; elemFlag = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_bElementFlag[5]; break;
			case 6: elemName = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_cElementName6; elemFlag = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_bElementFlag[6]; break;
			}
			m_pGame->GetItemName(m_pGame->FindItemIdByName(elemName), 0, cStr1, cStr2, cStr3);
			wsprintf(cTemp, "%s", cStr1);
			if (elemFlag)
				PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, RGB(45, 25, 25));
			else
				PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, RGB(150, 150, 150));
			iLoc++;
		}
	}

	if (m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_bBuildEnabled == true)
	{
		// Draw ingredient slots
		for (int slot = 0; slot < 6; slot++)
		{
			int slotX = (slot % 3) * 45;
			int slotY = (slot / 3) * 45;
			m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX + 55 + 30 + slotX + 13, sY + iAdjY + 55 + slotY + 180, 2, dwTime);
		}

		// Draw items in slots
		if (Info().sV1 != -1)
			m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV1]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 30 + 13, sY + iAdjY + 55 + 180, m_pGame->m_pItemList[Info().sV1]->m_sSpriteFrame, dwTime);
		if (Info().sV2 != -1)
			m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV2]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 45 + 30 + 13, sY + iAdjY + 55 + 180, m_pGame->m_pItemList[Info().sV2]->m_sSpriteFrame, dwTime);
		if (Info().sV3 != -1)
			m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV3]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 90 + 30 + 13, sY + iAdjY + 55 + 180, m_pGame->m_pItemList[Info().sV3]->m_sSpriteFrame, dwTime);
		if (Info().sV4 != -1)
			m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV4]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 30 + 13, sY + iAdjY + 100 + 180, m_pGame->m_pItemList[Info().sV4]->m_sSpriteFrame, dwTime);
		if (Info().sV5 != -1)
			m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV5]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 45 + 30 + 13, sY + iAdjY + 100 + 180, m_pGame->m_pItemList[Info().sV5]->m_sSpriteFrame, dwTime);
		if (Info().sV6 != -1)
			m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV6]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 90 + 30 + 13, sY + iAdjY + 100 + 180, m_pGame->m_pItemList[Info().sV6]->m_sSpriteFrame, dwTime);

		PutAlignedString(sX, sX + szX, sY + iAdjY + 230 + 75, DRAW_DIALOGBOX_SKILLDLG15, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + iAdjY + 245 + 75, DRAW_DIALOGBOX_SKILLDLG16, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + iAdjY + 260 + 75, DRAW_DIALOGBOX_SKILLDLG17, 55, 25, 25);

		if ((msX >= sX + iAdjX + 32) && (msX <= sX + iAdjX + 95) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372))
			m_pGame->PutString_SprFont(sX + iAdjX + 25, sY + iAdjY + 330 + 23, "Back", 6, 6, 20);
		else m_pGame->PutString_SprFont(sX + iAdjX + 25, sY + iAdjY + 330 + 23, "Back", 0, 0, 7);

		if ((msX >= sX + iAdjX + 160) && (msX <= sX + iAdjX + 255) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372)) {
			if (Info().cStr[4] == 1)
				m_pGame->PutString_SprFont(sX + iAdjX + 153, sY + iAdjY + 330 + 23, "Manufacture", 6, 6, 20);
			else m_pGame->PutString_SprFont(sX + iAdjX + 153, sY + iAdjY + 330 + 23, "Manufacture", 10, 10, 10);
		}
		else {
			if (Info().cStr[4] == 1)
				m_pGame->PutString_SprFont(sX + iAdjX + 153, sY + iAdjY + 330 + 23, "Manufacture", 0, 0, 7);
			else m_pGame->PutString_SprFont(sX + iAdjX + 153, sY + iAdjY + 330 + 23, "Manufacture", 10, 10, 10);
		}
	}
	else {
		PutAlignedString(sX, sX + szX, sY + iAdjY + 200 + 75, DRAW_DIALOGBOX_SKILLDLG18, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + iAdjY + 215 + 75, DRAW_DIALOGBOX_SKILLDLG19, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + iAdjY + 230 + 75, DRAW_DIALOGBOX_SKILLDLG20, 55, 25, 25);
		if ((msX >= sX + iAdjX + 32) && (msX <= sX + iAdjX + 95) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372))
			m_pGame->PutString_SprFont(sX + iAdjX + 25, sY + iAdjY + 330 + 23, "Back", 6, 6, 20);
		else m_pGame->PutString_SprFont(sX + iAdjX + 25, sY + iAdjY + 330 + 23, "Back", 0, 0, 7);
	}
}

void DialogBox_Manufacture::DrawManufactureInProgress(short sX, short sY)
{
	int iAdjX = -1;
	int iAdjY = -7;
	uint32_t dwTime = m_pGame->m_dwCurTime;
	short szX = Info().sSizeX;
	char cTemp[120];
	char cStr1[64], cStr2[64], cStr3[64];
	int iLoc;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 0);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 8);
	m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_iSprH]->PutSpriteFast(sX + iAdjX + 62 + 5, sY + iAdjY + 84 + 17,
		m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_iSprFrame, dwTime);

	std::memset(cTemp, 0, sizeof(cTemp));
	m_pGame->GetItemName(m_pGame->FindItemIdByName(m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_cName), 0, cStr1, cStr2, cStr3);
	wsprintf(cTemp, "%s", cStr1);
	PutString(sX + iAdjX + 44 + 10 + 60, sY + iAdjY + 55, cTemp, RGB(255, 255, 255));

	wsprintf(cTemp, DRAW_DIALOGBOX_SKILLDLG7, m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_iSkillLimit, m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_iMaxSkill);
	PutString(sX + iAdjX + 44 + 10 + 60, sY + iAdjY + 55 + 2 * 15, cTemp, RGB(45, 25, 25));
	PutString(sX + iAdjX + 44 + 10 + 60, sY + iAdjY + 55 + 3 * 15 + 5, DRAW_DIALOGBOX_SKILLDLG8, RGB(45, 25, 25));

	iLoc = 4;
	for (int elem = 1; elem <= 6; elem++)
	{
		if (m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_iElementCount[elem] != 0)
		{
			char* elemName = nullptr;
			bool elemFlag = false;
			switch (elem) {
			case 1: elemName = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_cElementName1; elemFlag = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_bElementFlag[1]; break;
			case 2: elemName = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_cElementName2; elemFlag = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_bElementFlag[2]; break;
			case 3: elemName = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_cElementName3; elemFlag = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_bElementFlag[3]; break;
			case 4: elemName = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_cElementName4; elemFlag = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_bElementFlag[4]; break;
			case 5: elemName = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_cElementName5; elemFlag = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_bElementFlag[5]; break;
			case 6: elemName = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_cElementName6; elemFlag = m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_bElementFlag[6]; break;
			}
			m_pGame->GetItemName(m_pGame->FindItemIdByName(elemName), 0, cStr1, cStr2, cStr3);
			wsprintf(cTemp, "%s", cStr1);
			if (elemFlag)
				PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, RGB(45, 25, 25));
			else
				PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, RGB(120, 120, 120));
			iLoc++;
		}
	}

	// Draw ingredient slots
	for (int slot = 0; slot < 6; slot++)
	{
		int slotX = (slot % 3) * 45;
		int slotY = (slot / 3) * 45;
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX + 55 + 30 + slotX + 13, sY + iAdjY + 55 + slotY + 180, 2, dwTime);
	}

	// Draw items in slots
	if (Info().sV1 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV1]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 30 + 13, sY + iAdjY + 55 + 180, m_pGame->m_pItemList[Info().sV1]->m_sSpriteFrame, dwTime);
	if (Info().sV2 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV2]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 45 + 30 + 13, sY + iAdjY + 55 + 180, m_pGame->m_pItemList[Info().sV2]->m_sSpriteFrame, dwTime);
	if (Info().sV3 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV3]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 90 + 30 + 13, sY + iAdjY + 55 + 180, m_pGame->m_pItemList[Info().sV3]->m_sSpriteFrame, dwTime);
	if (Info().sV4 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV4]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 30 + 13, sY + iAdjY + 100 + 180, m_pGame->m_pItemList[Info().sV4]->m_sSpriteFrame, dwTime);
	if (Info().sV5 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV5]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 45 + 30 + 13, sY + iAdjY + 100 + 180, m_pGame->m_pItemList[Info().sV5]->m_sSpriteFrame, dwTime);
	if (Info().sV6 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV6]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 90 + 30 + 13, sY + iAdjY + 100 + 180, m_pGame->m_pItemList[Info().sV6]->m_sSpriteFrame, dwTime);

	PutString(sX + iAdjX + 33, sY + iAdjY + 230 + 75, DRAW_DIALOGBOX_SKILLDLG29, RGB(55, 25, 25));
	PutString(sX + iAdjX + 33, sY + iAdjY + 245 + 75, DRAW_DIALOGBOX_SKILLDLG30, RGB(55, 25, 25));

	if ((dwTime - Info().dwT1) > 1000)
	{
		Info().dwT1 = dwTime;
		Info().cStr[1]++;
		if (Info().cStr[1] >= 7) Info().cStr[1] = 7;
	}

	if (Info().cStr[1] == 4)
	{
		m_pGame->bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_BUILDITEM, 0, 0, 0, 0, m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_cName);
		Info().cStr[1]++;
	}
}

void DialogBox_Manufacture::DrawManufactureDone(short sX, short sY, short msX, short msY)
{
	int iAdjX = -1;
	int iAdjY = -7;
	uint32_t dwTime = m_pGame->m_dwCurTime;
	char cTemp[120];
	char cStr1[64], cStr2[64], cStr3[64];

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 0);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 8);
	m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_iSprH]->PutSpriteFast(sX + iAdjX + 62 + 5, sY + iAdjY + 84 + 17,
		m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_iSprFrame, dwTime);

	std::memset(cTemp, 0, sizeof(cTemp));
	m_pGame->GetItemName(m_pGame->FindItemIdByName(m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_cName), 0, cStr1, cStr2, cStr3);

	wsprintf(cTemp, "%s", cStr1);
	PutString(sX + iAdjX + 44 + 10 + 60, sY + iAdjY + 55, cTemp, RGB(255, 255, 255));

	if (Info().cStr[2] == 1) {
		PutString(sX + iAdjX + 33 + 11, sY + iAdjY + 200 - 45, DRAW_DIALOGBOX_SKILLDLG31, RGB(55, 25, 25));

		if (Info().sV1 == DEF_ITEMTYPE_MATERIAL) {
			wsprintf(m_pGame->G_cTxt, DRAW_DIALOGBOX_SKILLDLG32, Info().cStr[3]);
			PutString(sX + iAdjX + 33 + 11, sY + iAdjY + 215 - 45, m_pGame->G_cTxt, RGB(55, 25, 25));
		}
		else {
			wsprintf(m_pGame->G_cTxt, DRAW_DIALOGBOX_SKILLDLG33, (int)Info().cStr[3] + 100);
			PutString(sX + iAdjX + 33, sY + iAdjY + 215 - 45, m_pGame->G_cTxt, RGB(55, 25, 25));
		}
	}
	else {
		PutString(sX + iAdjX + 33 + 11, sY + iAdjY + 200, DRAW_DIALOGBOX_SKILLDLG34, RGB(55, 25, 25));
	}

	if ((msX >= sX + iAdjX + 32) && (msX <= sX + iAdjX + 95) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372))
		m_pGame->PutString_SprFont(sX + iAdjX + 35, sY + iAdjY + 330 + 23, "Back", 6, 6, 20);
	else m_pGame->PutString_SprFont(sX + iAdjX + 35, sY + iAdjY + 330 + 23, "Back", 0, 0, 7);
}

void DialogBox_Manufacture::DrawCraftingWaiting(short sX, short sY, short msX, short msY)
{
	int iAdjX = 5;
	int iAdjY = 8;
	uint32_t dwTime = m_pGame->m_dwCurTime;

	m_pGame->m_pSprite[DEF_SPRID_INTERFACE_CRAFTING]->PutSpriteFast(sX, sY, 0, dwTime);

	if (Info().sV1 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV1]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)), m_pGame->m_pItemList[Info().sV1]->m_sSpriteFrame, dwTime);
	if (Info().sV2 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV2]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 + 45 + (1 - (rand() % 3)), sY + iAdjY + 40 + (1 - (rand() % 3)), m_pGame->m_pItemList[Info().sV2]->m_sSpriteFrame, dwTime);
	if (Info().sV3 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV3]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 + 90 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)), m_pGame->m_pItemList[Info().sV3]->m_sSpriteFrame, dwTime);
	if (Info().sV4 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV4]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)), m_pGame->m_pItemList[Info().sV4]->m_sSpriteFrame, dwTime);
	if (Info().sV5 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV5]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 + 45 + (1 - (rand() % 3)), sY + iAdjY + 115 + (1 - (rand() % 3)), m_pGame->m_pItemList[Info().sV5]->m_sSpriteFrame, dwTime);
	if (Info().sV6 != -1)
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV6]->m_sSprite]->PutSpriteFast(sX + iAdjX + 75 + 90 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)), m_pGame->m_pItemList[Info().sV6]->m_sSpriteFrame, dwTime);

	if ((msX >= sX + iAdjX + 60) && (msX <= sX + iAdjX + 153) && (msY >= sY + iAdjY + 175) && (msY <= sY + iAdjY + 195))
		m_pGame->PutString_SprFont(sX + iAdjX + 60, sY + iAdjY + 175, "Try Now!", 16, 16, 30);
	else m_pGame->PutString_SprFont(sX + iAdjX + 60, sY + iAdjY + 175, "Try Now!", 6, 6, 20);
}

void DialogBox_Manufacture::DrawCraftingInProgress(short sX, short sY)
{
	int iAdjX = 5;
	int iAdjY = 8;
	uint32_t dwTime = m_pGame->m_dwCurTime;

	m_pGame->m_pSprite[DEF_SPRID_INTERFACE_CRAFTING]->PutSpriteFast(sX, sY, 0, dwTime);

	if (Info().sV1 != -1)
	{
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV1]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)), m_pGame->m_pItemList[Info().sV1]->m_sSpriteFrame, dwTime);
		if ((m_pGame->m_pItemList[Info().sV1]->m_cItemType == DEF_ITEMTYPE_EQUIP) && (m_pGame->m_pItemList[Info().sV1]->m_cEquipPos == DEF_EQUIPPOS_NECK))
			m_pGame->m_iContributionPrice = 10;
	}
	if (Info().sV2 != -1)
	{
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV2]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 + 45 + (1 - (rand() % 3)), sY + iAdjY + 40 + (1 - (rand() % 3)), m_pGame->m_pItemList[Info().sV2]->m_sSpriteFrame, dwTime);
		if ((m_pGame->m_pItemList[Info().sV2]->m_cItemType == DEF_ITEMTYPE_EQUIP) && (m_pGame->m_pItemList[Info().sV2]->m_cEquipPos == DEF_EQUIPPOS_NECK))
			m_pGame->m_iContributionPrice = 10;
	}
	if (Info().sV3 != -1)
	{
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV3]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 + 90 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)), m_pGame->m_pItemList[Info().sV3]->m_sSpriteFrame, dwTime);
		if ((m_pGame->m_pItemList[Info().sV3]->m_cItemType == DEF_ITEMTYPE_EQUIP) && (m_pGame->m_pItemList[Info().sV3]->m_cEquipPos == DEF_EQUIPPOS_NECK))
			m_pGame->m_iContributionPrice = 10;
	}
	if (Info().sV4 != -1)
	{
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV4]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)), m_pGame->m_pItemList[Info().sV4]->m_sSpriteFrame, dwTime);
		if ((m_pGame->m_pItemList[Info().sV4]->m_cItemType == DEF_ITEMTYPE_EQUIP) && (m_pGame->m_pItemList[Info().sV4]->m_cEquipPos == DEF_EQUIPPOS_NECK))
			m_pGame->m_iContributionPrice = 10;
	}
	if (Info().sV5 != -1)
	{
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV5]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 + 45 + (1 - (rand() % 3)), sY + iAdjY + 115 + (1 - (rand() % 3)), m_pGame->m_pItemList[Info().sV5]->m_sSpriteFrame, dwTime);
		if ((m_pGame->m_pItemList[Info().sV5]->m_cItemType == DEF_ITEMTYPE_EQUIP) && (m_pGame->m_pItemList[Info().sV5]->m_cEquipPos == DEF_EQUIPPOS_NECK))
			m_pGame->m_iContributionPrice = 10;
	}
	if (Info().sV6 != -1)
	{
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[Info().sV6]->m_sSprite]->PutSpriteFast(sX + iAdjX + 75 + 90 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)), m_pGame->m_pItemList[Info().sV6]->m_sSpriteFrame, dwTime);
		if ((m_pGame->m_pItemList[Info().sV6]->m_cItemType == DEF_ITEMTYPE_EQUIP) && (m_pGame->m_pItemList[Info().sV6]->m_cEquipPos == DEF_EQUIPPOS_NECK))
			m_pGame->m_iContributionPrice = 10;
	}

	m_pGame->PutString_SprFont(sX + iAdjX + 60, sY + iAdjY + 175, "Creating...", 20, 6, 6);

	if ((dwTime - Info().dwT1) > 1000)
	{
		Info().dwT1 = dwTime;
		Info().cStr[1]++;
	}
	if (Info().cStr[1] >= 5)
	{
		m_pGame->bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_CRAFTITEM, 0, 0, 0, 0, 0);
		m_pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::Manufacture);
		m_pGame->PlaySound('E', 42, 0);
	}
}

bool DialogBox_Manufacture::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;
	int iAdjX = 5;
	int iAdjY = 8;

	switch (Info().cMode) {
	case 1: // Alchemy
		if ((msX >= sX + iAdjX + 60) && (msX <= sX + iAdjX + 153) && (msY >= sY + iAdjY + 175) && (msY <= sY + iAdjY + 195))
		{
			Info().cMode = 2;
			Info().cStr[0] = 1;
			Info().dwT1 = m_pGame->m_dwCurTime;
			m_pGame->PlaySound('E', 14, 5);
			m_pGame->AddEventList(DLGBOX_CLICK_SKILLDLG1, 10);
			m_pGame->PlaySound('E', 41, 0);
			return true;
		}
		break;

	case 7: // Crafting
		if ((msX >= sX + iAdjX + 60) && (msX <= sX + iAdjX + 153) && (msY >= sY + iAdjY + 175) && (msY <= sY + iAdjY + 195))
		{
			if (Info().sV1 == -1)
			{
				m_pGame->AddEventList(DLGBOX_CLICK_SKILLDLG2, 10);
				m_pGame->PlaySound('E', 14, 5);
			}
			else
			{
				Info().cMode = 8;
				Info().dwT1 = m_pGame->m_dwCurTime;
				Info().cStr[1] = 1;
				m_pGame->PlaySound('E', 14, 5);
				m_pGame->AddEventList(DLGBOX_CLICK_SKILLDLG3, 10);
				m_pGame->PlaySound('E', 51, 0);
			}
			return true;
		}
		break;

	case 3: // Manufacture list
		iAdjX = 5;
		iAdjY = 8;
		for (int i = 0; i < 13; i++)
			if (m_pGame->m_pDispBuildItemList[i + Info().sView] != 0)
			{
				if ((msX >= sX + iAdjX + 44) && (msX <= sX + iAdjX + 135 + 44) && (msY >= sY + iAdjY + 55 + i * 15) && (msY <= sY + iAdjY + 55 + 14 + i * 15)) {
					Info().cMode = 4;
					Info().cStr[0] = i + Info().sView;
					m_pGame->PlaySound('E', 14, 5);
					return true;
				}
			}
		break;

	case 4: // Manufacture waiting
		iAdjX = -1;
		iAdjY = -7;
		if (m_pGame->m_pDispBuildItemList[Info().cStr[0]]->m_bBuildEnabled == true)
		{
			if ((msX >= sX + iAdjX + 32) && (msX <= sX + iAdjX + 95) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372)) {
				// Back
				ResetItemSlots();
				Info().cMode = 3;
				m_pGame->PlaySound('E', 14, 5);
				return true;
			}

			if ((msX >= sX + iAdjX + 160) && (msX <= sX + iAdjX + 255) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372))
			{
				// Manufacture
				if (Info().cStr[4] == 1)
				{
					Info().cMode = 5;
					Info().cStr[1] = 0;
					Info().dwT1 = m_pGame->m_dwCurTime;
					m_pGame->PlaySound('E', 14, 5);
					m_pGame->PlaySound('E', 44, 0);
				}
				return true;
			}
		}
		else
		{
			if ((msX >= sX + iAdjX + 32) && (msX <= sX + iAdjX + 95) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372))
			{
				// Back
				ResetItemSlots();
				Info().cMode = 3;
				m_pGame->PlaySound('E', 14, 5);
				return true;
			}
		}
		break;

	case 6: // Manufacture done
		iAdjX = -1;
		iAdjY = -7;
		if ((msX >= sX + iAdjX + 32) && (msX <= sX + iAdjX + 95) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372)) {
			// Back
			ResetItemSlots();
			Info().cMode = 3;
			m_pGame->PlaySound('E', 14, 5);
			return true;
		}
		break;
	}

	return false;
}

void DialogBox_Manufacture::ResetItemSlots()
{
	if ((Info().sV1 != -1) && (m_pGame->m_pItemList[Info().sV1] != 0))
		m_pGame->m_bIsItemDisabled[Info().sV1] = false;
	if ((Info().sV2 != -1) && (m_pGame->m_pItemList[Info().sV2] != 0))
		m_pGame->m_bIsItemDisabled[Info().sV2] = false;
	if ((Info().sV3 != -1) && (m_pGame->m_pItemList[Info().sV3] != 0))
		m_pGame->m_bIsItemDisabled[Info().sV3] = false;
	if ((Info().sV4 != -1) && (m_pGame->m_pItemList[Info().sV4] != 0))
		m_pGame->m_bIsItemDisabled[Info().sV4] = false;
	if ((Info().sV5 != -1) && (m_pGame->m_pItemList[Info().sV5] != 0))
		m_pGame->m_bIsItemDisabled[Info().sV5] = false;
	if ((Info().sV6 != -1) && (m_pGame->m_pItemList[Info().sV6] != 0))
		m_pGame->m_bIsItemDisabled[Info().sV6] = false;

	Info().sV1 = -1;
	Info().sV2 = -1;
	Info().sV3 = -1;
	Info().sV4 = -1;
	Info().sV5 = -1;
	Info().sV6 = -1;
	Info().cStr[0] = 0;
	Info().cStr[1] = 0;
	Info().cStr[4] = 0;
}
