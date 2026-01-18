#include "DialogBox_ItemDrop.h"
#include "Game.h"
#include "lan_eng.h"

DialogBox_ItemDrop::DialogBox_ItemDrop(CGame* pGame)
	: IDialogBox(DialogBoxId::ItemDropConfirm, pGame)
{
	SetDefaultRect(0 + SCREENX, 0 + SCREENY, 270, 105);
}

void DialogBox_ItemDrop::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;
	char cTxt[120], cStr1[64], cStr2[64], cStr3[64];

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME1, sX, sY, 2);

	m_pGame->GetItemName(m_pGame->m_pItemList[Info().sView], cStr1, cStr2, cStr3);

	if (strlen(Info().cStr) == 0)
		wsprintf(cTxt, "%s", cStr1);

	// Item name (green if special, blue otherwise)
	if (m_pGame->m_bIsSpecial)
	{
		PutString(sX + 35, sY + 20, cTxt, RGB(0, 255, 50));
		PutString(sX + 36, sY + 20, cTxt, RGB(0, 255, 50));
	}
	else
	{
		PutString(sX + 35, sY + 20, cTxt, RGB(4, 0, 50));
		PutString(sX + 36, sY + 20, cTxt, RGB(4, 0, 50));
	}

	// "Do you want to drop?" text
	PutString(sX + 35, sY + 36, DRAW_DIALOGBOX_ITEM_DROP1, RGB(4, 0, 50));
	PutString(sX + 36, sY + 36, DRAW_DIALOGBOX_ITEM_DROP1, RGB(4, 0, 50));

	// Toggle option text
	if (m_pGame->m_bItemDrop)
	{
		// "Don't show this message again"
		if ((msX >= sX + 35) && (msX <= sX + 240) && (msY >= sY + 80) && (msY <= sY + 90))
		{
			PutString(sX + 35, sY + 80, DRAW_DIALOGBOX_ITEM_DROP2, RGB(255, 255, 255));
			PutString(sX + 36, sY + 80, DRAW_DIALOGBOX_ITEM_DROP2, RGB(255, 255, 255));
		}
		else
		{
			PutString(sX + 35, sY + 80, DRAW_DIALOGBOX_ITEM_DROP2, RGB(4, 0, 50));
			PutString(sX + 36, sY + 80, DRAW_DIALOGBOX_ITEM_DROP2, RGB(4, 0, 50));
		}
	}
	else
	{
		// "Show this message again"
		if ((msX >= sX + 35) && (msX <= sX + 240) && (msY >= sY + 80) && (msY <= sY + 90))
		{
			PutString(sX + 35, sY + 80, DRAW_DIALOGBOX_ITEM_DROP3, RGB(255, 255, 255));
			PutString(sX + 36, sY + 80, DRAW_DIALOGBOX_ITEM_DROP3, RGB(255, 255, 255));
		}
		else
		{
			PutString(sX + 35, sY + 80, DRAW_DIALOGBOX_ITEM_DROP3, RGB(4, 0, 50));
			PutString(sX + 36, sY + 80, DRAW_DIALOGBOX_ITEM_DROP3, RGB(4, 0, 50));
		}
	}

	// Yes button
	if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 30, sY + 55, 19);
	else
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 30, sY + 55, 18);

	// No button
	if ((msX >= sX + 170) && (msX <= sX + 170 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 170, sY + 55, 3);
	else
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 170, sY + 55, 2);
}

bool DialogBox_ItemDrop::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;

	if (m_pGame->m_cCommand < 0) return false;

	// Yes button - drop item
	if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
	{
		Info().cMode = 3;
		bSendCommand(MSGID_COMMAND_COMMON,
			DEF_COMMONTYPE_ITEMDROP,
			0,
			Info().sView,
			1,
			0,
			m_pGame->m_pItemList[Info().sView]->m_cName);
		DisableThisDialog();
		return true;
	}

	// No button - cancel
	if ((msX >= sX + 170) && (msX <= sX + 170 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
	{
		for (int i = 0; i < DEF_MAXSELLLIST; i++)
			m_pGame->m_bIsItemDisabled[i] = false;

		DisableThisDialog();
		return true;
	}

	// Toggle "don't show again" option
	if ((msX >= sX + 35) && (msX <= sX + 240) && (msY >= sY + 80) && (msY <= sY + 90))
	{
		m_pGame->m_bItemDrop = !m_pGame->m_bItemDrop;
		return true;
	}

	return false;
}
