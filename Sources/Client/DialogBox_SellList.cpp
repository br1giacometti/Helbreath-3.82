#include "DialogBox_SellList.h"
#include "Game.h"
#include "GlobalDef.h"
#include "lan_eng.h"

DialogBox_SellList::DialogBox_SellList(CGame* pGame)
	: IDialogBox(DialogBoxId::SellList, pGame)
{
	SetDefaultRect(170 + SCREENX, 70 + SCREENY, 258, 339);
}

void DialogBox_SellList::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;
	short szX = Info().sSizeX;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 11);

	int iEmptyCount = 0;
	DrawItemList(sX, sY, szX, msX, msY, iEmptyCount);

	if (iEmptyCount == DEF_MAXSELLLIST) {
		DrawEmptyListMessage(sX, sY, szX);
	}

	bool bHasItems = (iEmptyCount < DEF_MAXSELLLIST);
	DrawButtons(sX, sY, msX, msY, bHasItems);
}

void DialogBox_SellList::DrawItemList(short sX, short sY, short szX, short msX, short msY, int& iEmptyCount)
{
	char cTxt[256], cStr1[64], cStr2[64], cStr3[64];

	for (int i = 0; i < DEF_MAXSELLLIST; i++)
	{
		if (m_pGame->m_stSellItemList[i].iIndex != -1)
		{
			int iItemIndex = m_pGame->m_stSellItemList[i].iIndex;
			std::memset(cStr1, 0, sizeof(cStr1));
			std::memset(cStr2, 0, sizeof(cStr2));
			std::memset(cStr3, 0, sizeof(cStr3));
			m_pGame->GetItemName(m_pGame->m_pItemList[iItemIndex], cStr1, cStr2, cStr3);

			bool bHover = (msX > sX + 25) && (msX < sX + 250) && (msY >= sY + 55 + i * 15) && (msY <= sY + 55 + 14 + i * 15);

			if (m_pGame->m_stSellItemList[i].iAmount > 1)
			{
				// Multiple items
				std::memset(cTxt, 0, sizeof(cTxt));
				wsprintf(cTxt, DRAW_DIALOGBOX_SELL_LIST1, m_pGame->m_stSellItemList[i].iAmount, cStr1);

				if (bHover)
					PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cTxt, 255, 255, 255);
				else if (m_pGame->m_bIsSpecial)
					PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cTxt, 0, 255, 50);
				else
					PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cTxt, 45, 25, 25);
			}
			else
			{
				// Single item
				if (bHover)
				{
					if ((strlen(cStr2) == 0) && (strlen(cStr3) == 0))
					{
						PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cStr1, 255, 255, 255);
					}
					else
					{
						std::memset(cTxt, 0, sizeof(cTxt));
						if ((strlen(cStr1) + strlen(cStr2) + strlen(cStr3)) < 36)
						{
							if ((strlen(cStr2) > 0) && (strlen(cStr3) > 0))
								wsprintf(cTxt, "%s(%s, %s)", cStr1, cStr2, cStr3);
							else
								wsprintf(cTxt, "%s(%s%s)", cStr1, cStr2, cStr3);
							PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cTxt, 255, 255, 255);
						}
						else
						{
							if ((strlen(cStr2) > 0) && (strlen(cStr3) > 0))
								wsprintf(cTxt, "(%s, %s)", cStr2, cStr3);
							else
								wsprintf(cTxt, "(%s%s)", cStr2, cStr3);
							PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cStr1, 255, 255, 255);
							PutAlignedString(sX, sX + szX, sY + 55 + i * 15 + 15, cTxt, 200, 200, 200);
							i++;
						}
					}
				}
				else
				{
					if ((strlen(cStr2) == 0) && (strlen(cStr3) == 0))
					{
						if (m_pGame->m_bIsSpecial)
							PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cStr1, 0, 255, 50);
						else
							PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cStr1, 45, 25, 25);
					}
					else
					{
						std::memset(cTxt, 0, sizeof(cTxt));
						if ((strlen(cStr1) + strlen(cStr2) + strlen(cStr3)) < 36)
						{
							if ((strlen(cStr2) > 0) && (strlen(cStr3) > 0))
								wsprintf(cTxt, "%s(%s, %s)", cStr1, cStr2, cStr3);
							else
								wsprintf(cTxt, "%s(%s%s)", cStr1, cStr2, cStr3);

							if (m_pGame->m_bIsSpecial)
								PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cTxt, 0, 255, 50);
							else
								PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cTxt, 45, 25, 25);
						}
						else
						{
							if (m_pGame->m_bIsSpecial)
								PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cStr1, 0, 255, 50);
							else
								PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cStr1, 45, 25, 25);
						}
					}
				}
			}
		}
		else
		{
			iEmptyCount++;
		}
	}
}

void DialogBox_SellList::DrawEmptyListMessage(short sX, short sY, short szX)
{
	PutAlignedString(sX, sX + szX, sY + 55 + 30 + 282 - 117 - 170, DRAW_DIALOGBOX_SELL_LIST2);
	PutAlignedString(sX, sX + szX, sY + 55 + 45 + 282 - 117 - 170, DRAW_DIALOGBOX_SELL_LIST3);
	PutAlignedString(sX, sX + szX, sY + 55 + 60 + 282 - 117 - 170, DRAW_DIALOGBOX_SELL_LIST4);
	PutAlignedString(sX, sX + szX, sY + 55 + 75 + 282 - 117 - 170, DRAW_DIALOGBOX_SELL_LIST5);
	PutAlignedString(sX, sX + szX, sY + 55 + 95 + 282 - 117 - 170, DRAW_DIALOGBOX_SELL_LIST6);
	PutAlignedString(sX, sX + szX, sY + 55 + 110 + 282 - 117 - 170, DRAW_DIALOGBOX_SELL_LIST7);
	PutAlignedString(sX, sX + szX, sY + 55 + 125 + 282 - 117 - 170, DRAW_DIALOGBOX_SELL_LIST8);
	PutAlignedString(sX, sX + szX, sY + 55 + 155 + 282 - 117 - 170, DRAW_DIALOGBOX_SELL_LIST9);
}

void DialogBox_SellList::DrawButtons(short sX, short sY, short msX, short msY, bool bHasItems)
{
	// Sell button (only enabled when there are items)
	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) &&
		(msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY) && bHasItems)
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 39);
	else
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 38);

	// Cancel button
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) &&
		(msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
	else
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
}

bool DialogBox_SellList::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;

	// Check if clicking on an item in the list to remove it
	for (int i = 0; i < DEF_MAXSELLLIST; i++)
	{
		if ((msX > sX + 25) && (msX < sX + 250) && (msY >= sY + 55 + i * 15) && (msY <= sY + 55 + 14 + i * 15))
		{
			if (m_pGame->m_pItemList[m_pGame->m_stSellItemList[i].iIndex] != 0)
			{
				// Re-enable the item
				m_pGame->m_bIsItemDisabled[m_pGame->m_stSellItemList[i].iIndex] = false;
				m_pGame->m_stSellItemList[i].iIndex = -1;

				m_pGame->PlaySound('E', 14, 5);

				// Compact the list
				for (int x = 0; x < DEF_MAXSELLLIST - 1; x++)
				{
					if (m_pGame->m_stSellItemList[x].iIndex == -1)
					{
						m_pGame->m_stSellItemList[x].iIndex = m_pGame->m_stSellItemList[x + 1].iIndex;
						m_pGame->m_stSellItemList[x].iAmount = m_pGame->m_stSellItemList[x + 1].iAmount;

						m_pGame->m_stSellItemList[x + 1].iIndex = -1;
						m_pGame->m_stSellItemList[x + 1].iAmount = 0;
					}
				}
			}
			return true;
		}
	}

	// Sell button
	if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) &&
		(msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
	{
		m_pGame->bSendCommand(MSGID_REQUEST_SELLITEMLIST, 0, 0, 0, 0, 0, 0);
		m_pGame->PlaySound('E', 14, 5);
		DisableThisDialog();
		return true;
	}

	// Cancel button
	if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) &&
		(msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
	{
		m_pGame->PlaySound('E', 14, 5);
		DisableThisDialog();
		return true;
	}

	return false;
}
