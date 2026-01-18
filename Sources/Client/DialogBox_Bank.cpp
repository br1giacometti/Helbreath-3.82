#include "DialogBox_Bank.h"
#include "Game.h"
#include "InputManager.h"
#include "lan_eng.h"

DialogBox_Bank::DialogBox_Bank(CGame* pGame)
	: IDialogBox(DialogBoxId::Bank, pGame)
{
	SetDefaultRect(60 + SCREENX, 50 + SCREENY, 258, 339);
}

void DialogBox_Bank::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;
	short szX = Info().sSizeX - 5;

	m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
	m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 21);

	switch (Info().cMode) {
	case -1:
		PutString(sX + 30 + 15, sY + 70, DRAW_DIALOGBOX_BANK1, RGB(0, 0, 0));
		PutString(sX + 30 + 15, sY + 85, DRAW_DIALOGBOX_BANK2, RGB(0, 0, 0));
		break;

	case 0:
		DrawItemList(sX, sY, szX, msX, msY, msZ, cLB);
		break;
	}
}

void DialogBox_Bank::DrawItemList(short sX, short sY, short szX, short msX, short msY, short msZ, char cLB)
{
	char cStr1[64], cStr2[64], cStr3[64];
	bool bFlag = false;
	int iLoc = 45;

	std::memset(cStr1, 0, sizeof(cStr1));
	std::memset(cStr2, 0, sizeof(cStr2));
	std::memset(cStr3, 0, sizeof(cStr3));

	for (int i = 0; i < Info().sV1; i++) {
		int itemIndex = i + Info().sView;
		if ((m_pGame->m_pBankList[itemIndex] != 0) && (itemIndex < DEF_MAXBANKITEMS)) {
			m_pGame->GetItemName(m_pGame->m_pBankList[itemIndex], cStr1, cStr2, cStr3);

			if ((msX > sX + 30) && (msX < sX + 210) && (msY >= sY + 110 + i * 15) && (msY <= sY + 124 + i * 15)) {
				bFlag = true;
				PutAlignedString(sX, sX + szX, sY + 110 + i * 15, cStr1, 255, 255, 255);
				DrawItemDetails(sX, sY, szX, itemIndex, iLoc);
			}
			else {
				if (m_pGame->m_bIsSpecial)
					PutAlignedString(sX, sX + szX, sY + 110 + i * 15, cStr1, 0, 255, 50);
				else
					PutAlignedString(sX, sX + szX, sY + 110 + i * 15, cStr1, 0, 0, 0);
			}
		}
	}

	// Count total items for scrollbar
	int iTotalLines = 0;
	for (int i = 0; i < DEF_MAXBANKITEMS; i++)
		if (m_pGame->m_pBankList[i] != 0) iTotalLines++;

	DrawScrollbar(sX, sY, iTotalLines, msX, msY, msZ, cLB);

	if (!bFlag) {
		PutAlignedString(sX, sX + szX, sY + 45, DRAW_DIALOGBOX_BANK3);
		PutAlignedString(sX, sX + szX, sY + 60, DRAW_DIALOGBOX_BANK4);
		PutAlignedString(sX, sX + szX, sY + 75, DRAW_DIALOGBOX_BANK5);
	}
}

void DialogBox_Bank::DrawItemDetails(short sX, short sY, short szX, int iItemIndex, int iLoc)
{
	char cStr1[64], cStr2[64], cStr3[64];
	std::memset(cStr1, 0, sizeof(cStr1));
	std::memset(cStr2, 0, sizeof(cStr2));
	std::memset(cStr3, 0, sizeof(cStr3));

	m_pGame->GetItemName(m_pGame->m_pBankList[iItemIndex], cStr1, cStr2, cStr3);

	if (m_pGame->m_bIsSpecial)
		PutAlignedString(sX + 70, sX + szX, sY + iLoc, cStr1, 0, 255, 50);
	else
		PutAlignedString(sX + 70, sX + szX, sY + iLoc, cStr1, 255, 255, 255);

	if (strlen(cStr2) > 0) {
		iLoc += 15;
		PutAlignedString(sX + 70, sX + szX, sY + iLoc, cStr2, 150, 150, 150);
	}
	if (strlen(cStr3) > 0) {
		iLoc += 15;
		PutAlignedString(sX + 70, sX + szX, sY + iLoc, cStr3, 150, 150, 150);
	}

	// Level limit
	if (m_pGame->m_pBankList[iItemIndex]->m_sLevelLimit != 0 &&
		m_pGame->m_pBankList[iItemIndex]->m_dwAttribute & 0x00000001) {
		iLoc += 15;
		wsprintf(m_pGame->G_cTxt, "%s: %d", DRAW_DIALOGBOX_SHOP24, m_pGame->m_pBankList[iItemIndex]->m_sLevelLimit);
		PutAlignedString(sX + 70, sX + szX, sY + iLoc, m_pGame->G_cTxt, 150, 150, 150);
	}

	// Weight for equipment
	if ((m_pGame->m_pBankList[iItemIndex]->m_cEquipPos != DEF_EQUIPPOS_NONE) &&
		(m_pGame->m_pBankList[iItemIndex]->m_wWeight >= 1100)) {
		iLoc += 15;
		int _wWeight = 0;
		if (m_pGame->m_pBankList[iItemIndex]->m_wWeight % 100) _wWeight = 1;
		wsprintf(m_pGame->G_cTxt, DRAW_DIALOGBOX_SHOP15, m_pGame->m_pBankList[iItemIndex]->m_wWeight / 100 + _wWeight);
		PutAlignedString(sX + 70, sX + szX, sY + iLoc, m_pGame->G_cTxt, 150, 150, 150);
	}

	// Draw item sprite
	char cItemColor = m_pGame->m_pBankList[iItemIndex]->m_cItemColor;
	if (cItemColor == 0) {
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pBankList[iItemIndex]->m_sSprite]->PutSpriteFast(
			sX + 60, sY + 68, m_pGame->m_pBankList[iItemIndex]->m_sSpriteFrame, m_pGame->m_dwCurTime);
	}
	else {
		if ((m_pGame->m_pBankList[iItemIndex]->m_cEquipPos == DEF_EQUIPPOS_LHAND) ||
			(m_pGame->m_pBankList[iItemIndex]->m_cEquipPos == DEF_EQUIPPOS_RHAND) ||
			(m_pGame->m_pBankList[iItemIndex]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND)) {
			m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pBankList[iItemIndex]->m_sSprite]->PutSpriteRGB(
				sX + 60, sY + 68, m_pGame->m_pBankList[iItemIndex]->m_sSpriteFrame,
				m_pGame->m_wWR[cItemColor] - m_pGame->m_wR[0],
				m_pGame->m_wWG[cItemColor] - m_pGame->m_wG[0],
				m_pGame->m_wWB[cItemColor] - m_pGame->m_wB[0], m_pGame->m_dwCurTime);
		}
		else {
			m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pBankList[iItemIndex]->m_sSprite]->PutSpriteRGB(
				sX + 60, sY + 68, m_pGame->m_pBankList[iItemIndex]->m_sSpriteFrame,
				m_pGame->m_wR[cItemColor] - m_pGame->m_wR[0],
				m_pGame->m_wG[cItemColor] - m_pGame->m_wG[0],
				m_pGame->m_wB[cItemColor] - m_pGame->m_wB[0], m_pGame->m_dwCurTime);
		}
	}
}

void DialogBox_Bank::DrawScrollbar(short sX, short sY, int iTotalLines, short msX, short msY, short msZ, char cLB)
{
	int iPointerLoc;
	double d1, d2, d3;

	if (iTotalLines > Info().sV1) {
		d1 = (double)Info().sView;
		d2 = (double)(iTotalLines - Info().sV1);
		d3 = (274.0f * d1) / d2;
		iPointerLoc = (int)d3;
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 3);
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX + 242, sY + iPointerLoc + 35, 7);
	}
	else {
		iPointerLoc = 0;
	}

	if (cLB != 0 && (m_pGame->m_dialogBoxManager.iGetTopDialogBoxIndex() == DialogBoxId::Bank) && iTotalLines > Info().sV1) {
		if ((msX >= sX + 230) && (msX <= sX + 260) && (msY >= sY + 40) && (msY <= sY + 320)) {
			d1 = (double)(msY - (sY + 35));
			d2 = (double)(iTotalLines - Info().sV1);
			d3 = (d1 * d2) / 274.0f;
			Info().sView = (int)(d3 + 0.5);
		}
		else if ((msX >= sX + 230) && (msX <= sX + 260) && (msY > sY + 10) && (msY < sY + 40)) {
			Info().sView = 0;
		}
	}
	else {
		Info().bIsScrollSelected = false;
	}

	if (m_pGame->m_dialogBoxManager.iGetTopDialogBoxIndex() == DialogBoxId::Bank && msZ != 0) {
		if (iTotalLines > 50)
			Info().sView = Info().sView - msZ / 30;
		else {
			if (msZ > 0) Info().sView--;
			if (msZ < 0) Info().sView++;
		}
		InputManager::Get().ClearWheelDelta();
	}

	if (iTotalLines > Info().sV1 && Info().sView > iTotalLines - Info().sV1)
		Info().sView = iTotalLines - Info().sV1;
	if (iTotalLines <= Info().sV1)
		Info().sView = 0;
	if (Info().sView < 0)
		Info().sView = 0;
}

bool DialogBox_Bank::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;

	switch (Info().cMode) {
	case -1:
		break;

	case 0:
		for (int i = 0; i < Info().sV1; i++) {
			if ((msX > sX + 30) && (msX < sX + 210) && (msY >= sY + 110 + i * 15) && (msY <= sY + 124 + i * 15)) {
				int itemIndex = Info().sView + i;
				if ((m_pGame->m_pBankList[itemIndex] != 0) && (itemIndex < DEF_MAXBANKITEMS)) {
					if (m_pGame->_iGetTotalItemNum() >= 50) {
						AddEventList(DLGBOX_CLICK_BANK1, 10);
						return true;
					}
					bSendCommand(MSGID_REQUEST_RETRIEVEITEM, 0, 0, itemIndex, 0, 0, 0);
					Info().cMode = -1;
					PlaySoundEffect('E', 14, 5);
				}
				return true;
			}
		}
		break;
	}

	return false;
}
