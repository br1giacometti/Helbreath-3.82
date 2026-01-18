#include "DialogBox_Resurrect.h"
#include "Game.h"

DialogBox_Resurrect::DialogBox_Resurrect(CGame* pGame)
	: IDialogBox(DialogBoxId::Resurrect, pGame)
{
	SetDefaultRect(185 + SCREENX, 100 + SCREENY, 270, 105);
}

void DialogBox_Resurrect::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME1, sX, sY, 2);

	PutString(sX + 50, sY + 20, "Someone intend to resurrect you.", RGB(4, 0, 50));
	PutString(sX + 80, sY + 35, "Will you revive here?", RGB(4, 0, 50));

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

bool DialogBox_Resurrect::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;

	// Yes button
	if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
	{
		bSendCommand(DEF_REQUEST_RESURRECTPLAYER_YES, 0, 0, 0, 0, 0, nullptr, 0);
		DisableThisDialog();
		return true;
	}

	// No button
	if ((msX >= sX + 170) && (msX <= sX + 170 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
	{
		bSendCommand(DEF_REQUEST_RESURRECTPLAYER_NO, 0, 0, 0, 0, 0, nullptr, 0);
		DisableThisDialog();
		return true;
	}

	return false;
}
