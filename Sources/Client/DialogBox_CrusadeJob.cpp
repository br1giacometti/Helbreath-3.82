#include "DialogBox_CrusadeJob.h"
#include "Game.h"
#include "GlobalDef.h"
#include "lan_eng.h"

DialogBox_CrusadeJob::DialogBox_CrusadeJob(CGame* pGame)
	: IDialogBox(DialogBoxId::CrusadeJob, pGame)
{
	SetDefaultRect(360 + SCREENX, 65 + SCREENY, 258, 339);
}

void DialogBox_CrusadeJob::DrawModeSelectJob(short sX, short sY, short msX, short msY)
{
	PutAlignedString(sX + 24, sX + 246, sY + 45 + 20, DRAWDIALOGBOX_CRUSADEJOB1);
	PutAlignedString(sX + 24, sX + 246, sY + 60 + 20, DRAWDIALOGBOX_CRUSADEJOB2);
	PutAlignedString(sX + 24, sX + 246, sY + 75 + 20, DRAWDIALOGBOX_CRUSADEJOB3);
	PutAlignedString(sX + 24, sX + 246, sY + 90 + 20, DRAWDIALOGBOX_CRUSADEJOB4);

	if (m_pGame->m_bCitizen)
	{
		if (m_pGame->m_iGuildRank == 0)
		{
			// Guild master can be Commander
			if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
				PutAlignedString(sX + 24, sX + 246, sY + 150, DRAWDIALOGBOX_CRUSADEJOB5, 255, 255, 255);
			else
				PutAlignedString(sX + 24, sX + 246, sY + 150, DRAWDIALOGBOX_CRUSADEJOB5, 4, 0, 50);
		}
		else
		{
			// Non-guild masters can be Soldier
			if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
				PutAlignedString(sX + 24, sX + 246, sY + 150, DRAWDIALOGBOX_CRUSADEJOB7, 255, 255, 255);
			else
				PutAlignedString(sX + 24, sX + 246, sY + 150, DRAWDIALOGBOX_CRUSADEJOB7, 4, 0, 50);

			// Guild members can also be Constructor
			if (m_pGame->m_iGuildRank != -1)
			{
				if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 175) && (msY < sY + 190))
					PutAlignedString(sX + 24, sX + 246, sY + 175, DRAWDIALOGBOX_CRUSADEJOB9, 255, 255, 255);
				else
					PutAlignedString(sX + 24, sX + 246, sY + 175, DRAWDIALOGBOX_CRUSADEJOB9, 4, 0, 50);
			}
		}
	}

	PutAlignedString(sX + 24, sX + 246, sY + 290 - 40, DRAWDIALOGBOX_CRUSADEJOB10);
	PutAlignedString(sX + 24, sX + 246, sY + 305 - 40, DRAWDIALOGBOX_CRUSADEJOB17);

	// Help button
	if ((msX > sX + 210) && (msX < sX + 260) && (msY >= sY + 296) && (msY <= sY + 316))
		m_pGame->PutString_SprFont(sX + 50 + 160, sY + 296, "Help", 6, 6, 20);
	else
		m_pGame->PutString_SprFont(sX + 50 + 160, sY + 296, "Help", 0, 0, 7);
}

void DialogBox_CrusadeJob::DrawModeConfirm(short sX, short sY, short msX, short msY)
{
	PutAlignedString(sX + 24, sX + 246, sY + 90 + 20, DRAWDIALOGBOX_CRUSADEJOB18);

	switch (m_pGame->m_iCrusadeDuty)
	{
	case 1: PutAlignedString(sX + 24, sX + 246, sY + 125, DRAWDIALOGBOX_CRUSADEJOB19); break;
	case 2: PutAlignedString(sX + 24, sX + 246, sY + 125, DRAWDIALOGBOX_CRUSADEJOB20); break;
	case 3: PutAlignedString(sX + 24, sX + 246, sY + 125, DRAWDIALOGBOX_CRUSADEJOB21); break;
	}

	PutAlignedString(sX + 24, sX + 246, sY + 145, DRAWDIALOGBOX_CRUSADEJOB22);

	// "View details" link
	if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 160) && (msY < sY + 175))
		PutAlignedString(sX + 24, sX + 246, sY + 160, DRAWDIALOGBOX_CRUSADEJOB23, 255, 255, 255);
	else
		PutAlignedString(sX + 24, sX + 246, sY + 160, DRAWDIALOGBOX_CRUSADEJOB23, 4, 0, 50);

	PutAlignedString(sX + 24, sX + 246, sY + 175, DRAWDIALOGBOX_CRUSADEJOB25);
	PutAlignedString(sX + 24, sX + 246, sY + 190, DRAWDIALOGBOX_CRUSADEJOB26);

	// OK button
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) &&
		(msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
	else
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

void DialogBox_CrusadeJob::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);

	switch (Info().cMode)
	{
	case 1:
		DrawModeSelectJob(sX, sY, msX, msY);
		break;
	case 2:
		DrawModeConfirm(sX, sY, msX, msY);
		break;
	}
}

bool DialogBox_CrusadeJob::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;

	switch (Info().cMode)
	{
	case 1:
		if (!m_pGame->m_bCitizen)
		{
			DisableDialogBox(DialogBoxId::CrusadeJob);
			m_pGame->PlaySound('E', 14, 5);
			return true;
		}

		if (m_pGame->m_iGuildRank == 0)
		{
			// Guild master - Commander option
			if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
			{
				m_pGame->bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_SELECTCRUSADEDUTY, 0, 3, 0, 0, 0);
				DisableDialogBox(DialogBoxId::CrusadeJob);
				m_pGame->PlaySound('E', 14, 5);
				return true;
			}
		}
		else
		{
			// Soldier option
			if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
			{
				m_pGame->bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_SELECTCRUSADEDUTY, 0, 1, 0, 0, 0);
				DisableDialogBox(DialogBoxId::CrusadeJob);
				m_pGame->PlaySound('E', 14, 5);
				return true;
			}

			// Constructor option (guild members only)
			if (m_pGame->m_iGuildRank != -1)
			{
				if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 175) && (msY < sY + 190))
				{
					m_pGame->bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_SELECTCRUSADEDUTY, 0, 2, 0, 0, 0);
					DisableDialogBox(DialogBoxId::CrusadeJob);
					m_pGame->PlaySound('E', 14, 5);
					return true;
				}
			}
		}

		// Help button
		if ((msX > sX + 210) && (msX < sX + 260) && (msY >= sY + 296) && (msY <= sY + 316))
		{
			m_pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::Text);
			m_pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Text, 813, 0, 0);
			m_pGame->PlaySound('E', 14, 5);
			return true;
		}
		break;

	case 2:
		// View details link
		if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 160) && (msY < sY + 175))
		{
			switch (m_pGame->m_iCrusadeDuty)
			{
			case 1: m_pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Text, 803, 0, 0); break;
			case 2: m_pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Text, 805, 0, 0); break;
			case 3: m_pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::Text, 808, 0, 0); break;
			}
			return true;
		}

		// OK button
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) &&
			(msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		{
			DisableDialogBox(DialogBoxId::CrusadeJob);
			m_pGame->PlaySound('E', 14, 5);
			return true;
		}
		break;
	}

	return false;
}
