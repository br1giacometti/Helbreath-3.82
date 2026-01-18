#include "DialogBox_RepairAll.h"
#include "Game.h"
#include "InputManager.h"

DialogBox_RepairAll::DialogBox_RepairAll(CGame* pGame)
	: IDialogBox(DialogBoxId::RepairAll, pGame)
{
	SetDefaultRect(337 + SCREENX, 57 + SCREENY, 258, 339);
}

void DialogBox_RepairAll::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;
	short szX = Info().sSizeX;
	char cTxt[120];
	int iTotalLines, iPointerLoc;
	double d1, d2, d3;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 10);

	for (int i = 0; i < 15; i++)
	{
		if ((i + Info().sView) < m_pGame->totalItemRepair)
		{
			std::memset(cTxt, 0, sizeof(cTxt));
			wsprintf(cTxt, "%s - Cost: %d",
				m_pGame->m_pItemList[m_pGame->m_stRepairAll[i + Info().sView].index]->m_cName,
				m_pGame->m_stRepairAll[i + Info().sView].price);

			PutString(sX + 30, sY + 45 + i * 15, cTxt, RGB(5, 5, 5));
			m_pGame->m_bIsItemDisabled[m_pGame->m_stRepairAll[i + Info().sView].index] = true;
		}
	}

	iTotalLines = m_pGame->totalItemRepair;
	if (iTotalLines > 15)
	{
		d1 = (double)Info().sView;
		d2 = (double)(iTotalLines - 15);
		d3 = (274.0f * d1) / d2;
		iPointerLoc = (int)d3;
	}
	else
	{
		iPointerLoc = 0;
	}

	if (iTotalLines > 15)
	{
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 1);
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX + 242, sY + iPointerLoc + 35, 7);
	}

	// Mouse wheel scrolling
	if (iTotalLines > 15)
	{
		if (m_pGame->m_dialogBoxManager.iGetTopDialogBoxIndex() == DialogBoxId::RepairAll && msZ != 0)
		{
			if (msZ > 0) Info().sView--;
			if (msZ < 0) Info().sView++;
			InputManager::Get().ClearWheelDelta();
		}

		if (Info().sView < 0)
			Info().sView = 0;

		if (iTotalLines > 15 && Info().sView > iTotalLines - 15)
			Info().sView = iTotalLines - 15;
	}

	if (m_pGame->totalItemRepair > 0)
	{
		// Repair button
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 43);
		else
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 42);

		// Cancel button
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
		else
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);

		// Total cost
		std::memset(cTxt, 0, sizeof(cTxt));
		wsprintf(cTxt, "Total cost : %d", m_pGame->totalPrice);
		PutString(sX + 30, sY + 270, cTxt, RGB(5, 5, 5));
	}
	else
	{
		// No items to repair
		PutAlignedString(sX, sX + szX, sY + 140, "There are no items to repair.", 5, 5, 5);

		// Cancel button only
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
		else
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
	}
}

bool DialogBox_RepairAll::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;

	for (int i = 0; i < 15; i++)
	{
		if ((i + Info().sView) < m_pGame->totalItemRepair)
		{
			// Repair button
			if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			{
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_REPAIRALLCONFIRM, 0, 0, 0, 0, 0);
				DisableThisDialog();
				return true;
			}

			// Cancel button
			if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			{
				DisableThisDialog();
				return true;
			}
		}
		else
		{
			// Cancel button (no items)
			if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			{
				DisableThisDialog();
				return true;
			}
		}
	}

	return false;
}


