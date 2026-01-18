#include "DialogBox_GuildMenu.h"
#include "Game.h"
#include "lan_eng.h"

DialogBox_GuildMenu::DialogBox_GuildMenu(CGame* pGame)
	: IDialogBox(DialogBoxId::GuildMenu, pGame)
{
	SetDefaultRect(0 + SCREENX, 0 + SCREENY, 258, 339);
}

void DialogBox_GuildMenu::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;
	short szX = Info().sSizeX;

	m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
	m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 19);

	switch (Info().cMode) {
	case 0:
		DrawMode0_MainMenu(sX, sY, szX, msX, msY);
		break;
	case 1:
		DrawMode1_CreateGuild(sX, sY, szX, msX, msY);
		break;
	case 2:
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU19, 55, 25, 25);
		break;
	case 3:
		PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_GUILDMENU20, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + 140, m_pGame->m_cGuildName, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + 144, "____________________", 25, 35, 25);
		PutAlignedString(sX, sX + szX, sY + 160, DRAW_DIALOGBOX_GUILDMENU21, 55, 25, 25);
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	case 4:
		PutAlignedString(sX, sX + szX, sY + 135, DRAW_DIALOGBOX_GUILDMENU22, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + 150, DRAW_DIALOGBOX_GUILDMENU23, 55, 25, 25);
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	case 5:
		DrawMode5_DisbandConfirm(sX, sY, szX, msX, msY);
		break;
	case 6:
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU29, 55, 25, 25);
		break;
	case 7:
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU30, 55, 25, 25);
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	case 8:
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU31, 55, 25, 25);
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	case 9:
		DrawMode9_AdmissionTicket(sX, sY, szX, msX, msY);
		break;
	case 10:
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU37, 55, 25, 25);
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	case 11:
		DrawMode11_SecessionTicket(sX, sY, szX, msX, msY);
		break;
	case 12:
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU43, 55, 25, 25);
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	case 13:
		DrawMode13_FightzoneSelect(sX, sY, szX, msX, msY);
		break;
	case 14:
		PutAlignedString(sX, sX + szX, sY + 130, DRAW_DIALOGBOX_GUILDMENU66, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + 145, DRAW_DIALOGBOX_GUILDMENU67, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + 160, DRAW_DIALOGBOX_GUILDMENU68, 55, 25, 25);
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	case 15:
		PutAlignedString(sX, sX + szX, sY + 135, DRAW_DIALOGBOX_GUILDMENU69, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + 150, DRAW_DIALOGBOX_GUILDMENU70, 55, 25, 25);
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	case 16:
		PutAlignedString(sX, sX + szX, sY + 135, DRAW_DIALOGBOX_GUILDMENU71, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + 150, DRAW_DIALOGBOX_GUILDMENU72, 55, 25, 25);
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	case 17:
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU73, 55, 25, 25);
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	case 18:
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU74, 55, 25, 25);
		break;
	case 19:
		if (m_pGame->m_iFightzoneNumber > 0)
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_GETOCCUPYFIGHTZONETICKET, 0, 0, 0, 0, 0);
		Info().cMode = 0;
		break;
	case 20:
		DrawMode20_ConfirmCancel(sX, sY, szX, msX, msY);
		break;
	case 21:
		PutAlignedString(sX, sX + szX, sY + ADJY + 95, DRAW_DIALOGBOX_GUILDMENU76, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + ADJY + 110, DRAW_DIALOGBOX_GUILDMENU77, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + ADJY + 135, DRAW_DIALOGBOX_GUILDMENU78, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + ADJY + 150, DRAW_DIALOGBOX_GUILDMENU79, 55, 25, 25);
		PutAlignedString(sX, sX + szX, sY + ADJY + 165, DRAW_DIALOGBOX_GUILDMENU80, 55, 25, 25);
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	case 22:
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU81, 55, 25, 25);
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	}
}

void DialogBox_GuildMenu::DrawMode0_MainMenu(short sX, short sY, short szX, short msX, short msY)
{
	// Create new guild option
	if ((m_pGame->m_iGuildRank == -1) && (m_pGame->m_iCharisma >= 20) && (m_pGame->m_iLevel >= 20)) {
		if ((msX > sX + ADJX + 80) && (msX < sX + ADJX + 210) && (msY > sY + ADJY + 63) && (msY < sY + ADJY + 78))
			PutAlignedString(sX, sX + szX, sY + ADJY + 65, DRAW_DIALOGBOX_GUILDMENU1, 255, 255, 255);
		else PutAlignedString(sX, sX + szX, sY + ADJY + 65, DRAW_DIALOGBOX_GUILDMENU1, 4, 0, 50);
	}
	else PutAlignedString(sX, sX + szX, sY + ADJY + 65, DRAW_DIALOGBOX_GUILDMENU1, 65, 65, 65);

	// Disband guild option
	if (m_pGame->m_iGuildRank == 0) {
		if ((msX > sX + ADJX + 72) && (msX < sX + ADJX + 222) && (msY > sY + ADJY + 82) && (msY < sY + ADJY + 99))
			PutAlignedString(sX, sX + szX, sY + ADJY + 85, DRAW_DIALOGBOX_GUILDMENU4, 255, 255, 255);
		else PutAlignedString(sX, sX + szX, sY + ADJY + 85, DRAW_DIALOGBOX_GUILDMENU4, 4, 0, 50);
	}
	else PutAlignedString(sX, sX + szX, sY + ADJY + 85, DRAW_DIALOGBOX_GUILDMENU4, 65, 65, 65);

	// Admission ticket option
	if ((msX > sX + ADJX + 61) && (msX < sX + ADJX + 226) && (msY > sY + ADJY + 103) && (msY < sY + ADJY + 120))
		PutAlignedString(sX, sX + szX, sY + ADJY + 105, DRAW_DIALOGBOX_GUILDMENU7, 255, 255, 255);
	else PutAlignedString(sX, sX + szX, sY + ADJY + 105, DRAW_DIALOGBOX_GUILDMENU7, 4, 0, 50);

	// Secession ticket option
	if ((msX > sX + ADJX + 60) && (msX < sX + ADJX + 227) && (msY > sY + ADJY + 123) && (msY < sY + ADJY + 139))
		PutAlignedString(sX, sX + szX, sY + ADJY + 125, DRAW_DIALOGBOX_GUILDMENU9, 255, 255, 255);
	else PutAlignedString(sX, sX + szX, sY + ADJY + 125, DRAW_DIALOGBOX_GUILDMENU9, 4, 0, 50);

	// Fightzone options
	if (m_pGame->m_iGuildRank == 0 && m_pGame->m_iFightzoneNumber == 0) {
		if ((msX > sX + ADJX + 72) && (msX < sX + ADJX + 228) && (msY > sY + ADJY + 143) && (msY < sY + ADJY + 169))
			PutAlignedString(sX, sX + szX, sY + ADJY + 145, DRAW_DIALOGBOX_GUILDMENU11, 255, 255, 255);
		else PutAlignedString(sX, sX + szX, sY + ADJY + 145, DRAW_DIALOGBOX_GUILDMENU11, 4, 0, 50);
	}
	else if (m_pGame->m_iGuildRank == 0 && m_pGame->m_iFightzoneNumber > 0) {
		if ((msX > sX + ADJX + 72) && (msX < sX + ADJX + 216) && (msY > sY + ADJY + 143) && (msY < sY + ADJY + 169))
			PutAlignedString(sX, sX + szX, sY + ADJY + 145, DRAW_DIALOGBOX_GUILDMENU13, 255, 255, 255);
		else PutAlignedString(sX, sX + szX, sY + ADJY + 145, DRAW_DIALOGBOX_GUILDMENU13, 4, 0, 50);
	}
	else if (m_pGame->m_iFightzoneNumber < 0) {
		PutAlignedString(sX, sX + szX, sY + ADJY + 145, DRAW_DIALOGBOX_GUILDMENU13, 65, 65, 65);
	}
	else PutAlignedString(sX, sX + szX, sY + ADJY + 145, DRAW_DIALOGBOX_GUILDMENU11, 65, 65, 65);

	PutAlignedString(sX, sX + szX, sY + ADJY + 205, DRAW_DIALOGBOX_GUILDMENU17);
}

void DialogBox_GuildMenu::DrawMode1_CreateGuild(short sX, short sY, short szX, short msX, short msY)
{
	PutAlignedString(sX + 24, sX + 239, sY + 125, DRAW_DIALOGBOX_GUILDMENU18, 55, 25, 25);
	PutString(sX + 75, sY + 144, "____________________", RGB(25, 35, 25));

	if (m_pGame->m_dialogBoxManager.iGetTopDialogBoxIndex() != DialogBoxId::GuildMenu)
		m_pGame->PutString(sX + 75, sY + 140, m_pGame->m_cGuildName, RGB(255, 255, 255), true, false, true);

	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		if ((strcmp(m_pGame->m_cGuildName, "NONE") == 0) || (strlen(m_pGame->m_cGuildName) == 0)) {
			m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 24);
		}
		else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 25);
	}
	else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 24);

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
	else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
}

void DialogBox_GuildMenu::DrawMode5_DisbandConfirm(short sX, short sY, short szX, short msX, short msY)
{
	PutAlignedString(sX, sX + szX, sY + 90, DRAW_DIALOGBOX_GUILDMENU24);
	PutAlignedString(sX, sX + szX, sY + 105, m_pGame->m_cGuildName, 35, 35, 35);
	PutAlignedString(sX, sX + szX, sY + 109, "____________________", 0, 0, 0);
	PutAlignedString(sX, sX + szX, sY + 130, DRAW_DIALOGBOX_GUILDMENU25);
	PutAlignedString(sX, sX + szX, sY + 145, DRAW_DIALOGBOX_GUILDMENU26);
	PutAlignedString(sX, sX + szX, sY + 160, DRAW_DIALOGBOX_GUILDMENU27);
	PutAlignedString(sX, sX + szX, sY + 185, DRAW_DIALOGBOX_GUILDMENU28, 55, 25, 25);

	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
	else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
	else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
}

void DialogBox_GuildMenu::DrawMode9_AdmissionTicket(short sX, short sY, short szX, short msX, short msY)
{
	PutAlignedString(sX, sX + szX, sY + ADJY + 60, DRAW_DIALOGBOX_GUILDMENuint32_t);
	PutAlignedString(sX, sX + szX, sY + ADJY + 75, DRAW_DIALOGBOX_GUILDMENU33);
	PutAlignedString(sX, sX + szX, sY + ADJY + 90, DRAW_DIALOGBOX_GUILDMENU34);
	PutAlignedString(sX, sX + szX, sY + ADJY + 105, DRAW_DIALOGBOX_GUILDMENU35);
	PutAlignedString(sX, sX + szX, sY + ADJY + 130, DRAW_DIALOGBOX_GUILDMENU36);
	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 31);
	else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 30);
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
	else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
}

void DialogBox_GuildMenu::DrawMode11_SecessionTicket(short sX, short sY, short szX, short msX, short msY)
{
	PutAlignedString(sX, sX + szX, sY + ADJY + 60, DRAW_DIALOGBOX_GUILDMENU38);
	PutAlignedString(sX, sX + szX, sY + ADJY + 75, DRAW_DIALOGBOX_GUILDMENU39);
	PutAlignedString(sX, sX + szX, sY + ADJY + 90, DRAW_DIALOGBOX_GUILDMENU40);
	PutAlignedString(sX, sX + szX, sY + ADJY + 105, DRAW_DIALOGBOX_GUILDMENU41);
	PutAlignedString(sX, sX + szX, sY + ADJY + 130, DRAW_DIALOGBOX_GUILDMENU42);
	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 31);
	else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 30);
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
	else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
}

void DialogBox_GuildMenu::DrawMode13_FightzoneSelect(short sX, short sY, short szX, short msX, short msY)
{
	PutAlignedString(sX, sX + szX, sY + ADJY + 40, DRAW_DIALOGBOX_GUILDMENU44);
	PutAlignedString(sX, sX + szX, sY + ADJY + 55, DRAW_DIALOGBOX_GUILDMENU45);
	PutAlignedString(sX, sX + szX, sY + ADJY + 70, DRAW_DIALOGBOX_GUILDMENU46);
	PutAlignedString(sX, sX + szX, sY + ADJY + 85, DRAW_DIALOGBOX_GUILDMENU47);
	PutAlignedString(sX, sX + szX, sY + ADJY + 100, DRAW_DIALOGBOX_GUILDMENU48);
	PutAlignedString(sX, sX + szX, sY + ADJY + 115, DRAW_DIALOGBOX_GUILDMENU49);
	PutAlignedString(sX, sX + szX, sY + ADJY + 130, DRAW_DIALOGBOX_GUILDMENU50);

	// Fightzone buttons
	if ((msX > sX + ADJX + 65) && (msX < sX + ADJX + 137) && (msY > sY + ADJY + 168) && (msY < sY + ADJY + 185))
		PutString(sX + ADJX + 65 + 25 - 23, sY + ADJY + 170, DRAW_DIALOGBOX_GUILDMENU51, RGB(255, 255, 255));
	else PutString(sX + ADJX + 65 + 25 - 23, sY + ADJY + 170, DRAW_DIALOGBOX_GUILDMENU51, RGB(4, 0, 50));

	if ((msX > sX + ADJX + 150) && (msX < sX + ADJX + 222) && (msY > sY + ADJY + 168) && (msY < sY + ADJY + 185))
		PutString(sX + ADJX + 150 + 25 - 23, sY + ADJY + 170, DRAW_DIALOGBOX_GUILDMENU53, RGB(255, 255, 255));
	else PutString(sX + ADJX + 150 + 25 - 23, sY + ADJY + 170, DRAW_DIALOGBOX_GUILDMENU53, RGB(4, 0, 50));

	if ((msX > sX + ADJX + 65) && (msX < sX + ADJX + 137) && (msY > sY + ADJY + 188) && (msY < sY + ADJY + 205))
		PutString(sX + ADJX + 65 + 25 - 23, sY + ADJY + 190, DRAW_DIALOGBOX_GUILDMENU55, RGB(255, 255, 255));
	else PutString(sX + ADJX + 65 + 25 - 23, sY + ADJY + 190, DRAW_DIALOGBOX_GUILDMENU55, RGB(4, 0, 50));

	if ((msX > sX + ADJX + 150) && (msX < sX + ADJX + 222) && (msY > sY + ADJY + 188) && (msY < sY + ADJY + 205))
		PutString(sX + ADJX + 150 + 25 - 23, sY + ADJY + 190, DRAW_DIALOGBOX_GUILDMENU57, RGB(255, 255, 255));
	else PutString(sX + ADJX + 150 + 25 - 23, sY + ADJY + 190, DRAW_DIALOGBOX_GUILDMENU57, RGB(4, 0, 50));

	if ((msX > sX + ADJX + 65) && (msX < sX + ADJX + 137) && (msY > sY + ADJY + 208) && (msY < sY + ADJY + 225))
		PutString(sX + ADJX + 65 + 25 - 23, sY + ADJY + 210, DRAW_DIALOGBOX_GUILDMENU59, RGB(255, 255, 255));
	else PutString(sX + ADJX + 65 + 25 - 23, sY + ADJY + 210, DRAW_DIALOGBOX_GUILDMENU59, RGB(4, 0, 50));

	if ((msX > sX + ADJX + 150) && (msX < sX + ADJX + 222) && (msY > sY + ADJY + 208) && (msY < sY + ADJY + 225))
		PutString(sX + ADJX + 150 + 25 - 23, sY + ADJY + 210, DRAW_DIALOGBOX_GUILDMENU61, RGB(255, 255, 255));
	else PutString(sX + ADJX + 150 + 25 - 23, sY + ADJY + 210, DRAW_DIALOGBOX_GUILDMENU61, RGB(4, 0, 50));

	if ((msX > sX + ADJX + 65) && (msX < sX + ADJX + 137) && (msY > sY + ADJY + 228) && (msY < sY + ADJY + 245))
		PutString(sX + ADJX + 65 + 25 - 23, sY + ADJY + 230, DRAW_DIALOGBOX_GUILDMENU63, RGB(255, 255, 255));
	else PutString(sX + ADJX + 65 + 25 - 23, sY + ADJY + 230, DRAW_DIALOGBOX_GUILDMENU63, RGB(4, 0, 50));

	if ((msX > sX + ADJX + 150) && (msX < sX + ADJX + 222) && (msY > sY + ADJY + 228) && (msY < sY + ADJY + 245))
		PutString(sX + ADJX + 150 + 25 - 23, sY + ADJY + 230, DRAW_DIALOGBOX_GUILDMENU65, RGB(255, 255, 255));
	else PutString(sX + ADJX + 150 + 25 - 23, sY + ADJY + 230, DRAW_DIALOGBOX_GUILDMENU65, RGB(4, 0, 50));

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
	else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
}

void DialogBox_GuildMenu::DrawMode20_ConfirmCancel(short sX, short sY, short szX, short msX, short msY)
{
	PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_GUILDMENU75, 55, 25, 25);
	PutString(sX + 75, sY + 144, "____________________", RGB(25, 35, 25));
	m_pGame->PutString(sX + 75, sY + 140, m_pGame->m_cGuildName, RGB(255, 255, 255), false, 2);
	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 25);
	else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 24);
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
	else m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
}

bool DialogBox_GuildMenu::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;

	switch (Info().cMode) {
	case 0:
		return OnClickMode0(sX, sY, msX, msY);
	case 1:
		return OnClickMode1(sX, sY, msX, msY);
	case 3:
	case 4:
	case 7:
	case 8:
	case 10:
	case 12:
		return OnClickModeOkOnly(sX, sY, msX, msY);
	case 5:
		return OnClickMode5(sX, sY, msX, msY);
	case 9:
		return OnClickMode9(sX, sY, msX, msY);
	case 11:
		return OnClickMode11(sX, sY, msX, msY);
	case 13:
		return OnClickMode13(sX, sY, msX, msY);
	case 14:
	case 15:
	case 16:
	case 17:
	case 21:
	case 22:
		return OnClickModeOkOnly(sX, sY, msX, msY);
	}
	return false;
}

bool DialogBox_GuildMenu::OnClickMode0(short sX, short sY, short msX, short msY)
{
	// Create new guild
	if ((msX > sX + ADJX + 80) && (msX < sX + ADJX + 210) && (msY > sY + ADJY + 63) && (msY < sY + ADJY + 78)) {
		if (m_pGame->m_iGuildRank != -1) return false;
		if (m_pGame->m_iCharisma < 20) return false;
		if (m_pGame->m_iLevel < 20) return false;
		if (m_pGame->m_bIsCrusadeMode) return false;
		m_pGame->EndInputString();
		m_pGame->StartInputString(sX + 75, sY + 140, 21, m_pGame->m_cGuildName);
		Info().cMode = 1;
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	// Disband guild
	if ((msX > sX + ADJX + 72) && (msX < sX + ADJX + 222) && (msY > sY + ADJY + 82) && (msY < sY + ADJY + 99)) {
		if (m_pGame->m_iGuildRank != 0) return false;
		if (m_pGame->m_bIsCrusadeMode) return false;
		Info().cMode = 5;
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	// Admission ticket
	if ((msX > sX + ADJX + 61) && (msX < sX + ADJX + 226) && (msY > sY + ADJY + 103) && (msY < sY + ADJY + 120)) {
		Info().cMode = 9;
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	// Secession ticket
	if ((msX > sX + ADJX + 60) && (msX < sX + ADJX + 227) && (msY > sY + ADJY + 123) && (msY < sY + ADJY + 139)) {
		Info().cMode = 11;
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	// Fightzone
	if (m_pGame->m_iFightzoneNumber < 0) return false;
	if ((msX > sX + ADJX + 72) && (msX < sX + ADJX + 228) && (msY > sY + ADJY + 143) && (msY < sY + ADJY + 169)) {
		if (m_pGame->m_iGuildRank != 0) return false;
		if (m_pGame->m_iFightzoneNumber == 0)
			Info().cMode = 13;
		else
			Info().cMode = 19;
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	return false;
}

bool DialogBox_GuildMenu::OnClickMode1(short sX, short sY, short msX, short msY)
{
	// Submit button
	if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		if (strcmp(m_pGame->m_cGuildName, "NONE") == 0) return false;
		if (strlen(m_pGame->m_cGuildName) == 0) return false;
		bSendCommand(MSGID_REQUEST_CREATENEWGUILD, DEF_MSGTYPE_CONFIRM, 0, 0, 0, 0, 0);
		Info().cMode = 2;
		m_pGame->EndInputString();
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	// Cancel button
	if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		Info().cMode = 0;
		m_pGame->EndInputString();
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	return false;
}

bool DialogBox_GuildMenu::OnClickMode5(short sX, short sY, short msX, short msY)
{
	// Confirm disband
	if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		bSendCommand(MSGID_REQUEST_DISBANDGUILD, DEF_MSGTYPE_CONFIRM, 0, 0, 0, 0, 0);
		Info().cMode = 6;
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	// Cancel
	if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		Info().cMode = 0;
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	return false;
}

bool DialogBox_GuildMenu::OnClickMode9(short sX, short sY, short msX, short msY)
{
	char cTemp[21];

	// Purchase admission ticket
	if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		std::memset(cTemp, 0, sizeof(cTemp));
		strcpy(cTemp, "GuildAdmissionTicket");
		bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_PURCHASEITEM, 0, 1, 0, 0, cTemp);
		Info().cMode = 0;
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	// Cancel
	if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		Info().cMode = 0;
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	return false;
}

bool DialogBox_GuildMenu::OnClickMode11(short sX, short sY, short msX, short msY)
{
	char cTemp[21];

	// Purchase secession ticket
	if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		std::memset(cTemp, 0, sizeof(cTemp));
		strcpy(cTemp, "GuildSecessionTicket");
		bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_PURCHASEITEM, 0, 1, 0, 0, cTemp);
		Info().cMode = 0;
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	// Cancel
	if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		Info().cMode = 0;
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	return false;
}

bool DialogBox_GuildMenu::OnClickMode13(short sX, short sY, short msX, short msY)
{
	// Fightzone 1
	if ((msX > sX + ADJX + 65) && (msX < sX + ADJX + 137) && (msY > sY + ADJY + 168) && (msY < sY + ADJY + 185)) {
		bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, 0, 0, 1, 0, 0, 0);
		Info().cMode = 18;
		m_pGame->m_iFightzoneNumberTemp = 1;
		PlaySoundEffect('E', 14, 5);
		return true;
	}
	// Fightzone 2
	if ((msX > sX + ADJX + 150) && (msX < sX + ADJX + 222) && (msY > sY + ADJY + 168) && (msY < sY + ADJY + 185)) {
		bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, 0, 0, 2, 0, 0, 0);
		Info().cMode = 18;
		m_pGame->m_iFightzoneNumberTemp = 2;
		PlaySoundEffect('E', 14, 5);
		return true;
	}
	// Fightzone 3
	if ((msX > sX + ADJX + 65) && (msX < sX + ADJX + 137) && (msY > sY + ADJY + 188) && (msY < sY + ADJY + 205)) {
		bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, 0, 0, 3, 0, 0, 0);
		Info().cMode = 18;
		m_pGame->m_iFightzoneNumberTemp = 3;
		PlaySoundEffect('E', 14, 5);
		return true;
	}
	// Fightzone 4
	if ((msX > sX + ADJX + 150) && (msX < sX + ADJX + 222) && (msY > sY + ADJY + 188) && (msY < sY + ADJY + 205)) {
		bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, 0, 0, 4, 0, 0, 0);
		Info().cMode = 18;
		m_pGame->m_iFightzoneNumberTemp = 4;
		PlaySoundEffect('E', 14, 5);
		return true;
	}
	// Fightzone 5
	if ((msX > sX + ADJX + 65) && (msX < sX + ADJX + 137) && (msY > sY + ADJY + 208) && (msY < sY + ADJY + 225)) {
		bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, 0, 0, 5, 0, 0, 0);
		Info().cMode = 18;
		m_pGame->m_iFightzoneNumberTemp = 5;
		PlaySoundEffect('E', 14, 5);
		return true;
	}
	// Fightzone 6
	if ((msX > sX + ADJX + 150) && (msX < sX + ADJX + 222) && (msY > sY + ADJY + 208) && (msY < sY + ADJY + 225)) {
		bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, 0, 0, 6, 0, 0, 0);
		Info().cMode = 18;
		m_pGame->m_iFightzoneNumberTemp = 6;
		PlaySoundEffect('E', 14, 5);
		return true;
	}
	// Fightzone 7
	if ((msX > sX + ADJX + 65) && (msX < sX + ADJX + 137) && (msY > sY + ADJY + 228) && (msY < sY + ADJY + 245)) {
		bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, 0, 0, 7, 0, 0, 0);
		Info().cMode = 18;
		m_pGame->m_iFightzoneNumberTemp = 7;
		PlaySoundEffect('E', 14, 5);
		return true;
	}
	// Fightzone 8
	if ((msX > sX + ADJX + 150) && (msX < sX + ADJX + 222) && (msY > sY + ADJY + 228) && (msY < sY + ADJY + 245)) {
		bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, 0, 0, 8, 0, 0, 0);
		Info().cMode = 18;
		m_pGame->m_iFightzoneNumberTemp = 8;
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	// Cancel
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		Info().cMode = 0;
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	return false;
}

bool DialogBox_GuildMenu::OnClickModeOkOnly(short sX, short sY, short msX, short msY)
{
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		Info().cMode = 0;
		PlaySoundEffect('E', 14, 5);
		return true;
	}
	return false;
}
