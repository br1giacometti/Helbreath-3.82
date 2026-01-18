#include "DialogBox_GuildOperation.h"
#include "Game.h"
#include "lan_eng.h"

DialogBox_GuildOperation::DialogBox_GuildOperation(CGame* pGame)
	: IDialogBox(DialogBoxId::GuildOperation, pGame)
{
	SetDefaultRect(0 + SCREENX, 0 + SCREENY, 270, 236);
}

void DialogBox_GuildOperation::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;

	m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);
	m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 19);

	switch (m_pGame->m_stGuildOpList[0].cOpMode) {
	case 1:
		DrawJoinRequest(sX, sY, msX, msY);
		break;
	case 2:
		DrawDismissRequest(sX, sY, msX, msY);
		break;
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		DrawInfoMessage(sX, sY, msX, msY, m_pGame->m_stGuildOpList[0].cOpMode);
		break;
	}
}

void DialogBox_GuildOperation::DrawJoinRequest(short sX, short sY, short msX, short msY)
{
	PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION1);
	PutAlignedString(sX + 24, sX + 248, sY + 65, m_pGame->m_stGuildOpList[0].cName, 35, 35, 35);
	PutAlignedString(sX + 24, sX + 248, sY + 69, "____________________", 0, 0, 0);
	PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION2);
	PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION3);
	PutAlignedString(sX + 24, sX + 248, sY + 120, DRAW_DIALOGBOX_GUILD_OPERATION4);
	PutAlignedString(sX + 24, sX + 248, sY + 160, DRAW_DIALOGBOX_GUILD_OPERATION5, 55, 25, 25);

	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 33);
	else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 32);

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 35);
	else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 34);
}

void DialogBox_GuildOperation::DrawDismissRequest(short sX, short sY, short msX, short msY)
{
	PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION6);
	PutAlignedString(sX + 24, sX + 248, sY + 65, m_pGame->m_stGuildOpList[0].cName, 35, 35, 35);
	PutAlignedString(sX + 24, sX + 248, sY + 69, "____________________", 0, 0, 0);
	PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION7);
	PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION8);
	PutAlignedString(sX + 24, sX + 248, sY + 120, DRAW_DIALOGBOX_GUILD_OPERATION9);
	PutAlignedString(sX + 24, sX + 248, sY + 160, DRAW_DIALOGBOX_GUILD_OPERATION10, 55, 25, 25);

	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 33);
	else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 32);

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 35);
	else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 34);
}

void DialogBox_GuildOperation::DrawInfoMessage(short sX, short sY, short msX, short msY, int mode)
{
	switch (mode) {
	case 3:
		PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION11);
		PutAlignedString(sX + 24, sX + 248, sY + 65, m_pGame->m_stGuildOpList[0].cName, 35, 35, 35);
		PutAlignedString(sX + 24, sX + 248, sY + 69, "____________________", 0, 0, 0);
		PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION12);
		PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION13);
		break;
	case 4:
		PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION14);
		PutAlignedString(sX + 24, sX + 248, sY + 65, m_pGame->m_stGuildOpList[0].cName, 35, 35, 35);
		PutAlignedString(sX + 24, sX + 248, sY + 69, "____________________", 0, 0, 0);
		PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION15);
		PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION16);
		break;
	case 5:
		PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION17);
		PutAlignedString(sX + 24, sX + 248, sY + 65, m_pGame->m_stGuildOpList[0].cName, 35, 35, 35);
		PutAlignedString(sX + 24, sX + 248, sY + 69, "____________________", 0, 0, 0);
		PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION18);
		PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION19);
		PutAlignedString(sX + 24, sX + 248, sY + 120, DRAW_DIALOGBOX_GUILD_OPERATION20);
		break;
	case 6:
		PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION21);
		PutAlignedString(sX + 24, sX + 248, sY + 65, m_pGame->m_stGuildOpList[0].cName, 35, 35, 35);
		PutAlignedString(sX + 24, sX + 248, sY + 69, "____________________", 0, 0, 0);
		PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION22);
		PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION23);
		break;
	case 7:
		PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION24);
		PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION25);
		PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION26);
		PutAlignedString(sX + 24, sX + 248, sY + 120, DRAW_DIALOGBOX_GUILD_OPERATION27);
		break;
	}

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
	else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

bool DialogBox_GuildOperation::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;
	char cName20[24];

	std::memset(cName20, 0, sizeof(cName20));

	switch (m_pGame->m_stGuildOpList[0].cOpMode) {
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			m_pGame->_ShiftGuildOperationList();
			if (m_pGame->m_stGuildOpList[0].cOpMode == 0)
				m_pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::GuildOperation);
			return true;
		}
		return false;
	}

	// Approve button
	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		PlaySoundEffect('E', 14, 5);

		switch (m_pGame->m_stGuildOpList[0].cOpMode) {
		case 1:
			strcpy(cName20, m_pGame->m_stGuildOpList[0].cName);
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_JOINGUILDAPPROVE, 0, 0, 0, 0, cName20);
			break;
		case 2:
			strcpy(cName20, m_pGame->m_stGuildOpList[0].cName);
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_DISMISSGUILDAPPROVE, 0, 0, 0, 0, cName20);
			break;
		}
		m_pGame->_ShiftGuildOperationList();
		if (m_pGame->m_stGuildOpList[0].cOpMode == 0)
			m_pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::GuildOperation);
		return true;
	}

	// Reject button
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		PlaySoundEffect('E', 14, 5);

		switch (m_pGame->m_stGuildOpList[0].cOpMode) {
		case 1:
			strcpy(cName20, m_pGame->m_stGuildOpList[0].cName);
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_JOINGUILDREJECT, 0, 0, 0, 0, cName20);
			break;
		case 2:
			strcpy(cName20, m_pGame->m_stGuildOpList[0].cName);
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_DISMISSGUILDREJECT, 0, 0, 0, 0, cName20);
			break;
		}
		m_pGame->_ShiftGuildOperationList();
		if (m_pGame->m_stGuildOpList[0].cOpMode == 0)
			m_pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::GuildOperation);
		return true;
	}

	return false;
}
