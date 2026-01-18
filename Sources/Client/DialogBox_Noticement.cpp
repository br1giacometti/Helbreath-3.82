#include "DialogBox_Noticement.h"
#include "Game.h"
#include "lan_eng.h"

DialogBox_Noticement::DialogBox_Noticement(CGame* pGame)
	: IDialogBox(DialogBoxId::Noticement, pGame)
{
	SetDefaultRect(162 + SCREENX, 40 + SCREENY, 315, 171);
}

void DialogBox_Noticement::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;
	short szX = Info().sSizeX;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, sX, sY, 2);

	switch (Info().cMode)
	{
	case 1: // Server shutting down in X minutes
		std::memset(m_pGame->G_cTxt, 0, sizeof(m_pGame->G_cTxt));
		if (Info().sV1 != 0)
			wsprintf(m_pGame->G_cTxt, DRAW_DIALOGBOX_NOTICEMSG1, Info().sV1);
		else
			strcpy(m_pGame->G_cTxt, DRAW_DIALOGBOX_NOTICEMSG2);
		PutAlignedString(sX, sX + szX, sY + 31, m_pGame->G_cTxt, 100, 10, 10);
		PutAlignedString(sX, sX + szX, sY + 48, DRAW_DIALOGBOX_NOTICEMSG3);
		PutAlignedString(sX, sX + szX, sY + 65, DRAW_DIALOGBOX_NOTICEMSG4);
		PutAlignedString(sX, sX + szX, sY + 82, DRAW_DIALOGBOX_NOTICEMSG5);
		PutAlignedString(sX, sX + szX, sY + 99, DRAW_DIALOGBOX_NOTICEMSG6);
		break;

	case 2: // Shutdown has started
		PutAlignedString(sX, sX + szX, sY + 31, DRAW_DIALOGBOX_NOTICEMSG7, 100, 10, 10);
		PutAlignedString(sX, sX + szX, sY + 48, DRAW_DIALOGBOX_NOTICEMSG8);
		PutAlignedString(sX, sX + szX, sY + 65, DRAW_DIALOGBOX_NOTICEMSG9);
		PutAlignedString(sX, sX + szX, sY + 82, DRAW_DIALOGBOX_NOTICEMSG10);
		PutAlignedString(sX, sX + szX, sY + 99, DRAW_DIALOGBOX_NOTICEMSG11);
		break;
	}

	// OK button (same position for both modes)
	if ((msX >= sX + 210) && (msX <= sX + 210 + DEF_BTNSZX) && (msY > sY + 127) && (msY < sY + 127 + DEF_BTNSZY))
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 210, sY + 127, 1);
	else
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 210, sY + 127, 0);
}

bool DialogBox_Noticement::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;

	// OK button
	if ((msX >= sX + 210) && (msX <= sX + 210 + DEF_BTNSZX) && (msY > sY + 127) && (msY < sY + 127 + DEF_BTNSZY))
	{
		PlaySoundEffect('E', 14, 5);
		DisableThisDialog();
		return true;
	}

	return false;
}
