#include "DialogBox_Help.h"
#include "Game.h"
#include "lan_eng.h"

DialogBox_Help::DialogBox_Help(CGame* pGame)
	: IDialogBox(DialogBoxId::Help, pGame)
{
	SetDefaultRect(358 + SCREENX, 65 + SCREENY, 258, 339);
}

bool DialogBox_Help::IsMouseOverItem(short msX, short msY, short sX, short sY, int iItem)
{
	return (msX >= sX + 25) && (msX <= sX + 248) &&
	       (msY >= sY + 50 + 15 * iItem) && (msY < sY + 50 + 15 * (iItem + 1));
}

void DialogBox_Help::DrawHelpItem(short sX, short szX, short sY, int iItem, const char* pText, bool bHighlight)
{
	if (bHighlight)
		PutAlignedString(sX, sX + szX, sY + 50 + 15 * iItem, (char*)pText, 255, 255, 255);
	else
		PutAlignedString(sX, sX + szX, sY + 50 + 15 * iItem, (char*)pText, 4, 0, 50);
}

void DialogBox_Help::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;
	short szX = Info().sSizeX;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);

	// Help topics list
	DrawHelpItem(sX, szX, sY, 0, DRAW_DIALOGBOX_HELP2, IsMouseOverItem(msX, msY, sX, sY, 0));
	DrawHelpItem(sX, szX, sY, 1, DRAW_DIALOGBOX_HELP1, IsMouseOverItem(msX, msY, sX, sY, 1));
	DrawHelpItem(sX, szX, sY, 2, DRAW_DIALOGBOX_HELP3, IsMouseOverItem(msX, msY, sX, sY, 2));
	DrawHelpItem(sX, szX, sY, 3, DRAW_DIALOGBOX_HELP4, IsMouseOverItem(msX, msY, sX, sY, 3));
	DrawHelpItem(sX, szX, sY, 4, DRAW_DIALOGBOX_HELP5, IsMouseOverItem(msX, msY, sX, sY, 4));
	DrawHelpItem(sX, szX, sY, 5, DRAW_DIALOGBOX_HELP6, IsMouseOverItem(msX, msY, sX, sY, 5));
	DrawHelpItem(sX, szX, sY, 6, DRAW_DIALOGBOX_HELP7, IsMouseOverItem(msX, msY, sX, sY, 6));
	DrawHelpItem(sX, szX, sY, 7, DRAW_DIALOGBOX_HELP8, IsMouseOverItem(msX, msY, sX, sY, 7));
	DrawHelpItem(sX, szX, sY, 8, DRAW_DIALOGBOX_HELP9, IsMouseOverItem(msX, msY, sX, sY, 8));
	DrawHelpItem(sX, szX, sY, 9, DRAW_DIALOGBOX_HELP10, IsMouseOverItem(msX, msY, sX, sY, 9));
	DrawHelpItem(sX, szX, sY, 10, DRAW_DIALOGBOX_HELP11, IsMouseOverItem(msX, msY, sX, sY, 10));
	DrawHelpItem(sX, szX, sY, 11, DRAW_DIALOGBOX_HELP12, IsMouseOverItem(msX, msY, sX, sY, 11));
	DrawHelpItem(sX, szX, sY, 12, "F.A.Q.", IsMouseOverItem(msX, msY, sX, sY, 12));
	DrawHelpItem(sX, szX, sY, 13, DRAW_DIALOGBOX_HELP13, IsMouseOverItem(msX, msY, sX, sY, 13));

	// Close button
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) &&
	    (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
	else
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

bool DialogBox_Help::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;

	// Help topic clicks - each opens a different Text dialog
	if (IsMouseOverItem(msX, msY, sX, sY, 0)) {
		DisableDialogBox(DialogBoxId::Text);
		EnableDialogBox(DialogBoxId::Text, 1000, 0, 0);
		return true;
	}

	if (IsMouseOverItem(msX, msY, sX, sY, 1)) {
		DisableDialogBox(DialogBoxId::Text);
		EnableDialogBox(DialogBoxId::Text, 900, 0, 0);
		return true;
	}

	if (IsMouseOverItem(msX, msY, sX, sY, 2)) {
		DisableDialogBox(DialogBoxId::Text);
		EnableDialogBox(DialogBoxId::Text, 901, 0, 0);
		return true;
	}

	if (IsMouseOverItem(msX, msY, sX, sY, 3)) {
		DisableDialogBox(DialogBoxId::Text);
		EnableDialogBox(DialogBoxId::Text, 902, 0, 0);
		return true;
	}

	if (IsMouseOverItem(msX, msY, sX, sY, 4)) {
		DisableDialogBox(DialogBoxId::Text);
		EnableDialogBox(DialogBoxId::Text, 903, 0, 0);
		m_pGame->m_bIsF1HelpWindowEnabled = true;
		return true;
	}

	if (IsMouseOverItem(msX, msY, sX, sY, 5)) {
		DisableDialogBox(DialogBoxId::Text);
		EnableDialogBox(DialogBoxId::Text, 904, 0, 0);
		return true;
	}

	if (IsMouseOverItem(msX, msY, sX, sY, 6)) {
		DisableDialogBox(DialogBoxId::Text);
		EnableDialogBox(DialogBoxId::Text, 905, 0, 0);
		return true;
	}

	if (IsMouseOverItem(msX, msY, sX, sY, 7)) {
		DisableDialogBox(DialogBoxId::Text);
		EnableDialogBox(DialogBoxId::Text, 906, 0, 0);
		return true;
	}

	if (IsMouseOverItem(msX, msY, sX, sY, 8)) {
		DisableDialogBox(DialogBoxId::Text);
		EnableDialogBox(DialogBoxId::Text, 907, 0, 0);
		return true;
	}

	if (IsMouseOverItem(msX, msY, sX, sY, 9)) {
		DisableDialogBox(DialogBoxId::Text);
		EnableDialogBox(DialogBoxId::Text, 908, 0, 0);
		return true;
	}

	if (IsMouseOverItem(msX, msY, sX, sY, 10)) {
		DisableDialogBox(DialogBoxId::Text);
		EnableDialogBox(DialogBoxId::Text, 909, 0, 0);
		return true;
	}

	if (IsMouseOverItem(msX, msY, sX, sY, 11)) {
		DisableDialogBox(DialogBoxId::Text);
		EnableDialogBox(DialogBoxId::Text, 910, 0, 0);
		return true;
	}

	if (IsMouseOverItem(msX, msY, sX, sY, 12)) {
		DisableDialogBox(DialogBoxId::Text);
		EnableDialogBox(DialogBoxId::Text, 911, 0, 0); // FAQ
		return true;
	}

	if (IsMouseOverItem(msX, msY, sX, sY, 13)) {
		DisableDialogBox(DialogBoxId::Text);
		EnableDialogBox(DialogBoxId::Text, 912, 0, 0);
		return true;
	}

	// Close button
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) &&
	    (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		PlaySoundEffect('E', 14, 5);
		DisableThisDialog();
		return true;
	}

	return false;
}
