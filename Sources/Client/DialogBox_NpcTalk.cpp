#include "DialogBox_NpcTalk.h"
#include "Game.h"

#define DEF_TEXTDLGMAXLINES 300

DialogBox_NpcTalk::DialogBox_NpcTalk(CGame* pGame)
	: IDialogBox(DialogBoxId::NpcTalk, pGame)
{
	SetDefaultRect(337 + SCREENX, 57 + SCREENY, 258, 339);
}

int DialogBox_NpcTalk::GetTotalLines() const
{
	int iTotalLines = 0;
	for (int i = 0; i < DEF_TEXTDLGMAXLINES; i++)
	{
		if (m_pGame->m_pMsgTextList2[i] != nullptr)
			iTotalLines++;
	}
	return iTotalLines;
}

void DialogBox_NpcTalk::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = m_pGame->m_dialogBoxManager.Info(DialogBoxId::NpcTalk).sX;
	short sY = m_pGame->m_dialogBoxManager.Info(DialogBoxId::NpcTalk).sY;

	m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);

	DrawButtons(sX, sY, msX, msY);
	DrawTextContent(sX, sY);

	int iTotalLines = GetTotalLines();
	DrawScrollBar(sX, sY, iTotalLines);
	HandleScrollBarDrag(sX, sY, msX, msY, iTotalLines, cLB);
}

void DialogBox_NpcTalk::DrawButtons(short sX, short sY, short msX, short msY)
{
	switch (m_pGame->m_dialogBoxManager.Info(DialogBoxId::NpcTalk).cMode)
	{
	case 0: // OK button only
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) &&
			(msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 1: // Accept / Decline buttons
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) &&
			(msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 33);
		else
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 32);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) &&
			(msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 41);
		else
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 40);
		break;

	case 2: // Next button
		if ((msX >= sX + 190) && (msX <= sX + 278) &&
			(msY >= sY + 296) && (msY <= sY + 316))
			m_pGame->PutString_SprFont(sX + 190, sY + 270, "Next", 6, 6, 20);
		else
			m_pGame->PutString_SprFont(sX + 190, sY + 270, "Next", 0, 0, 7);
		break;
	}
}

void DialogBox_NpcTalk::DrawTextContent(short sX, short sY)
{
	short sView = m_pGame->m_dialogBoxManager.Info(DialogBoxId::NpcTalk).sView;
	short sSizeX = m_pGame->m_dialogBoxManager.Info(DialogBoxId::NpcTalk).sSizeX;

	for (int i = 0; i < 17; i++)
	{
		if ((i < DEF_TEXTDLGMAXLINES) && (m_pGame->m_pMsgTextList2[i + sView] != nullptr))
		{
			m_pGame->PutAlignedString(sX, sX + sSizeX, sY + 57 + i * 15,
				m_pGame->m_pMsgTextList2[i + sView]->m_pMsg, 45, 25, 25);
		}
	}
}

void DialogBox_NpcTalk::DrawScrollBar(short sX, short sY, int iTotalLines)
{
	if (iTotalLines > 17)
	{
		double d1 = (double)m_pGame->m_dialogBoxManager.Info(DialogBoxId::NpcTalk).sView;
		double d2 = (double)(iTotalLines - 17);
		double d3 = (274.0 * d1) / d2;
		int iPointerLoc = (int)d3;
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 3);
	}
}

void DialogBox_NpcTalk::HandleScrollBarDrag(short sX, short sY, short msX, short msY, int iTotalLines, char cLB)
{
	if (cLB != 0 && iTotalLines > 17)
	{
		if (m_pGame->m_dialogBoxManager.iGetTopDialogBoxIndex() == DialogBoxId::NpcTalk)
		{
			if ((msX >= sX + 240) && (msX <= sX + 260) &&
				(msY >= sY + 40) && (msY <= sY + 320))
			{
				double d1 = (double)(msY - (sY + 40));
				double d2 = (double)(iTotalLines - 17);
				double d3 = (d1 * d2) / 274.0;
				int iPointerLoc = (int)d3;

				if (iPointerLoc > iTotalLines)
					iPointerLoc = iTotalLines;
				m_pGame->m_dialogBoxManager.Info(DialogBoxId::NpcTalk).sView = iPointerLoc;
			}
		}
	}
	else
	{
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::NpcTalk).bIsScrollSelected = false;
	}
}

bool DialogBox_NpcTalk::OnClick(short msX, short msY)
{
	short sX = m_pGame->m_dialogBoxManager.Info(DialogBoxId::NpcTalk).sX;
	short sY = m_pGame->m_dialogBoxManager.Info(DialogBoxId::NpcTalk).sY;

	switch (m_pGame->m_dialogBoxManager.Info(DialogBoxId::NpcTalk).cMode)
	{
	case 0: // OK button
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) &&
			(msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{
			m_pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::NpcTalk);
			m_pGame->PlaySound('E', 14, 5);
			return true;
		}
		break;

	case 1: // Accept / Decline buttons
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) &&
			(msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{
			// Accept
			m_pGame->bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_QUESTACCEPTED, 0, 0, 0, 0, 0);
			m_pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::NpcTalk);
			m_pGame->PlaySound('E', 14, 5);
			return true;
		}
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) &&
			(msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{
			// Decline
			m_pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::NpcTalk);
			m_pGame->PlaySound('E', 14, 5);
			return true;
		}
		break;

	case 2: // Next button
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) &&
			(msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{
			m_pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::NpcTalk);
			m_pGame->PlaySound('E', 14, 5);
			return true;
		}
		break;
	}

	return false;
}
