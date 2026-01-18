#include "DialogBox_Exchange.h"
#include "Game.h"
#include "lan_eng.h"

DialogBox_Exchange::DialogBox_Exchange(CGame* pGame)
	: IDialogBox(DialogBoxId::Exchange, pGame)
{
	SetDefaultRect(0 + SCREENX, 0 + SCREENY, 540, 350);
}

void DialogBox_Exchange::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;
	short szX = Info().sSizeX;

	m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_NEWEXCHANGE, sX, sY, 0);

	switch (Info().cMode) {
	case 1: // Not yet confirmed exchange
		PutAlignedString(sX + 80, sX + 180, sY + 38, m_pGame->m_cPlayerName, 35, 55, 35);
		if (m_pGame->m_stDialogBoxExchangeInfo[4].sV1 != -1)
			PutAlignedString(sX + 250, sX + 540, sY + 38, m_pGame->m_stDialogBoxExchangeInfo[4].cStr2, 35, 55, 35);

		DrawItems(sX, sY, msX, msY, 0, 8);

		if ((m_pGame->m_stDialogBoxExchangeInfo[0].sV1 != -1) && (m_pGame->m_stDialogBoxExchangeInfo[4].sV1 == -1)) {
			PutAlignedString(sX, sX + szX, sY + 245, DRAW_DIALOGBOX_EXCHANGE9, 55, 25, 25);
			PutAlignedString(sX, sX + szX, sY + 260, DRAW_DIALOGBOX_EXCHANGE10, 55, 25, 25);
			PutAlignedString(sX, sX + szX, sY + 275, DRAW_DIALOGBOX_EXCHANGE11, 55, 25, 25);
			m_pGame->PutString_SprFont(sX + 220, sY + 310, "Exchange", 15, 15, 15);
		}
		else if ((m_pGame->m_stDialogBoxExchangeInfo[0].sV1 == -1) && (m_pGame->m_stDialogBoxExchangeInfo[4].sV1 != -1)) {
			PutAlignedString(sX, sX + szX, sY + 215, DRAW_DIALOGBOX_EXCHANGE12, 55, 25, 25);
			PutAlignedString(sX, sX + szX, sY + 230, DRAW_DIALOGBOX_EXCHANGE13, 55, 25, 25);
			PutAlignedString(sX, sX + szX, sY + 245, DRAW_DIALOGBOX_EXCHANGE14, 55, 25, 25);
			PutAlignedString(sX, sX + szX, sY + 260, DRAW_DIALOGBOX_EXCHANGE15, 55, 25, 25);
			PutAlignedString(sX, sX + szX, sY + 275, DRAW_DIALOGBOX_EXCHANGE16, 55, 25, 25);
			PutAlignedString(sX, sX + szX, sY + 290, DRAW_DIALOGBOX_EXCHANGE17, 55, 25, 25);
			m_pGame->PutString_SprFont(sX + 220, sY + 310, "Exchange", 15, 15, 15);
		}
		else if ((m_pGame->m_stDialogBoxExchangeInfo[0].sV1 != -1) && (m_pGame->m_stDialogBoxExchangeInfo[4].sV1 != -1)) {
			PutAlignedString(sX, sX + szX, sY + 215, DRAW_DIALOGBOX_EXCHANGE18, 55, 25, 25);
			PutAlignedString(sX, sX + szX, sY + 230, DRAW_DIALOGBOX_EXCHANGE19, 55, 25, 25);
			PutAlignedString(sX, sX + szX, sY + 245, DRAW_DIALOGBOX_EXCHANGE20, 55, 25, 25);
			PutAlignedString(sX, sX + szX, sY + 260, DRAW_DIALOGBOX_EXCHANGE21, 55, 25, 25);
			PutAlignedString(sX, sX + szX, sY + 275, DRAW_DIALOGBOX_EXCHANGE22, 55, 25, 25);
			PutAlignedString(sX, sX + szX, sY + 290, DRAW_DIALOGBOX_EXCHANGE23, 55, 25, 25);
			if ((msX >= sX + 200) && (msX <= sX + 200 + DEF_BTNSZX) && (msY >= sY + 310) && (msY <= sY + 310 + DEF_BTNSZY))
				m_pGame->PutString_SprFont(sX + 220, sY + 310, "Exchange", 6, 6, 20);
			else
				m_pGame->PutString_SprFont(sX + 220, sY + 310, "Exchange", 0, 0, 7);
		}
		if ((msX >= sX + 450) && (msX <= sX + 450 + DEF_BTNSZX) && (msY >= sY + 310) && (msY <= sY + 310 + DEF_BTNSZY)
			&& (m_pGame->m_dialogBoxManager.IsEnabled(DialogBoxId::ConfirmExchange) == false))
			m_pGame->PutString_SprFont(sX + 450, sY + 310, "Cancel", 6, 6, 20);
		else
			m_pGame->PutString_SprFont(sX + 450, sY + 310, "Cancel", 0, 0, 7);
		break;

	case 2: // You have confirmed the exchange
		PutAlignedString(sX + 80, sX + 180, sY + 38, m_pGame->m_cPlayerName, 35, 55, 35);
		if (m_pGame->m_stDialogBoxExchangeInfo[4].sV1 != -1)
			PutAlignedString(sX + 250, sX + 540, sY + 38, m_pGame->m_stDialogBoxExchangeInfo[4].cStr2, 35, 55, 35);

		DrawItems(sX, sY, msX, msY, 0, 8);

		wsprintf(m_pGame->G_cTxt, DRAW_DIALOGBOX_EXCHANGE33, m_pGame->m_stDialogBoxExchangeInfo[4].cStr2);
		PutAlignedString(sX, sX + szX, sY + 215, m_pGame->G_cTxt, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + 230, DRAW_DIALOGBOX_EXCHANGE34, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + 245, DRAW_DIALOGBOX_EXCHANGE35, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + 260, DRAW_DIALOGBOX_EXCHANGE36, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + 275, DRAW_DIALOGBOX_EXCHANGE37, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + 290, DRAW_DIALOGBOX_EXCHANGE38, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + 305, DRAW_DIALOGBOX_EXCHANGE39, 55, 25, 25);
		break;
	}
}

void DialogBox_Exchange::DrawItems(short sX, short sY, short msX, short msY, int iStartIndex, int iEndIndex)
{
	uint32_t dwTime = m_pGame->m_dwCurTime;
	char cItemColor;
	short sXadd;

	for (int i = iStartIndex; i < iEndIndex; i++) {
		sXadd = (58 * i) + 48;
		if (i > 3) sXadd += 20;

		if (m_pGame->m_stDialogBoxExchangeInfo[i].sV1 != -1) {
			cItemColor = m_pGame->m_stDialogBoxExchangeInfo[i].sV4;
			if (cItemColor == 0) {
				m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_stDialogBoxExchangeInfo[i].sV1]->PutSpriteFast(
					sX + sXadd, sY + 130, m_pGame->m_stDialogBoxExchangeInfo[i].sV2, dwTime);
			}
			else {
				switch (m_pGame->m_stDialogBoxExchangeInfo[i].sV1) {
				case 1:  // Swds
				case 2:  // Bows
				case 3:  // Shields
				case 15: // Axes hammers
				case 17: // Wands
					m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_stDialogBoxExchangeInfo[i].sV1]->PutSpriteRGB(
						sX + sXadd, sY + 130, m_pGame->m_stDialogBoxExchangeInfo[i].sV2,
						m_pGame->m_wWR[cItemColor] - m_pGame->m_wR[0],
						m_pGame->m_wWG[cItemColor] - m_pGame->m_wG[0],
						m_pGame->m_wWB[cItemColor] - m_pGame->m_wB[0], dwTime);
					break;
				default:
					m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_stDialogBoxExchangeInfo[i].sV1]->PutSpriteRGB(
						sX + sXadd, sY + 130, m_pGame->m_stDialogBoxExchangeInfo[i].sV2,
						m_pGame->m_wR[cItemColor] - m_pGame->m_wR[0],
						m_pGame->m_wG[cItemColor] - m_pGame->m_wG[0],
						m_pGame->m_wB[cItemColor] - m_pGame->m_wB[0], dwTime);
					break;
				}
			}

			DrawItemInfo(sX, sY, Info().sSizeX, msX, msY, i, sXadd);
		}
	}
}

void DialogBox_Exchange::DrawItemInfo(short sX, short sY, short szX, short msX, short msY, int iItemIndex, short sXadd)
{
	char cNameStr[120], cSubStr1[120], cSubStr2[120];
	char cTxt[120], cTxt2[128];
	int iLoc;

	m_pGame->GetItemName(m_pGame->m_stDialogBoxExchangeInfo[iItemIndex].sItemID,
		m_pGame->m_stDialogBoxExchangeInfo[iItemIndex].dwV1, cNameStr, cSubStr1, cSubStr2);

	if ((msX >= sX + sXadd - 6) && (msX <= sX + sXadd + 42) && (msY >= sY + 61) && (msY <= sY + 200)) {
		wsprintf(cTxt, "%s", cNameStr);
		if (m_pGame->m_bIsSpecial) {
			PutAlignedString(sX + 15, sX + 155, sY + 215, cTxt, 0, 255, 50);
			PutAlignedString(sX + 16, sX + 156, sY + 215, cTxt, 0, 255, 50);
		}
		else {
			PutAlignedString(sX + 15, sX + 155, sY + 215, cTxt, 35, 35, 35);
			PutAlignedString(sX + 16, sX + 156, sY + 215, cTxt, 35, 35, 35);
		}

		iLoc = 0;
		if (strlen(cSubStr1) != 0) {
			PutAlignedString(sX + 16, sX + 155, sY + 235 + iLoc, cSubStr1, 0, 0, 0);
			iLoc += 15;
		}
		if (strlen(cSubStr2) != 0) {
			PutAlignedString(sX + 16, sX + 155, sY + 235 + iLoc, cSubStr2, 0, 0, 0);
			iLoc += 15;
		}

		if (m_pGame->m_stDialogBoxExchangeInfo[iItemIndex].sV3 != 1) {
			if (m_pGame->m_stDialogBoxExchangeInfo[iItemIndex].sV3 > 1) {
				m_pGame->DisplayCommaNumber_G_cTxt(m_pGame->m_stDialogBoxExchangeInfo[iItemIndex].sV3);
				strcpy(cTxt2, m_pGame->G_cTxt);
			}
			else {
				wsprintf(cTxt2, DRAW_DIALOGBOX_EXCHANGE2, m_pGame->m_stDialogBoxExchangeInfo[iItemIndex].sV3);
			}
			PutAlignedString(sX + 16, sX + 155, sY + 235 + iLoc, cTxt2, 35, 35, 35);
			iLoc += 15;
		}

		if (m_pGame->m_stDialogBoxExchangeInfo[iItemIndex].sV5 != -1) {
			// Crafting Magins completion fix
			if (m_pGame->m_stDialogBoxExchangeInfo[iItemIndex].sV1 == 22) {
				if ((m_pGame->m_stDialogBoxExchangeInfo[iItemIndex].sV2 > 5) &&
					(m_pGame->m_stDialogBoxExchangeInfo[iItemIndex].sV2 < 10)) {
					wsprintf(cTxt, GET_ITEM_NAME2, (m_pGame->m_stDialogBoxExchangeInfo[iItemIndex].sV7 - 100));
				}
			}
			else if (m_pGame->m_stDialogBoxExchangeInfo[iItemIndex].sV1 == 6) {
				wsprintf(cTxt, GET_ITEM_NAME1, (m_pGame->m_stDialogBoxExchangeInfo[iItemIndex].sV7 - 100));
			}
			else {
				wsprintf(cTxt, GET_ITEM_NAME2, m_pGame->m_stDialogBoxExchangeInfo[iItemIndex].sV7);
			}
			PutAlignedString(sX + 16, sX + 155, sY + 235 + iLoc, cTxt, 35, 35, 35);
			iLoc += 15;
		}

		if (iLoc < 45) {
			wsprintf(cTxt, DRAW_DIALOGBOX_EXCHANGE3, m_pGame->m_stDialogBoxExchangeInfo[iItemIndex].sV5,
				m_pGame->m_stDialogBoxExchangeInfo[iItemIndex].sV6);
			PutAlignedString(sX + 16, sX + 155, sY + 235 + iLoc, cTxt, 35, 35, 35);
		}
	}
}

bool DialogBox_Exchange::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;

	switch (Info().cMode) {
	case 1: // Not yet confirmed the exchange
		if ((msX >= sX + 220) && (msX <= sX + 220 + DEF_BTNSZX) && (msY >= sY + 310) && (msY <= sY + 310 + DEF_BTNSZY)) {
			// Exchange button
			if ((m_pGame->m_stDialogBoxExchangeInfo[0].sV1 != -1) && (m_pGame->m_stDialogBoxExchangeInfo[4].sV1 != -1)) {
				PlaySoundEffect('E', 14, 5);
				Info().cMode = 2;
				// Show confirmation dialog
				m_pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::ConfirmExchange, 0, 0, 0);
				m_pGame->m_dialogBoxManager.Info(DialogBoxId::ConfirmExchange).cMode = 1;
			}
			return true;
		}
		if ((msX >= sX + 450) && (msX <= sX + 450 + DEF_BTNSZX) && (msY >= sY + 310) && (msY <= sY + 310 + DEF_BTNSZY)
			&& (m_pGame->m_dialogBoxManager.IsEnabled(DialogBoxId::ConfirmExchange) == false)) {
			// Cancel button
			m_pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::Exchange);
			m_pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::Map);
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_CANCELEXCHANGEITEM, 0, 0, 0, 0, 0);
			PlaySoundEffect('E', 14, 5);
			return true;
		}
		break;

	case 2: // Someone already confirmed the exchange
		break;
	}

	return false;
}
