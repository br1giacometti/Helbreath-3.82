#include "DialogBox_ConfirmExchange.h"
#include "Game.h"

DialogBox_ConfirmExchange::DialogBox_ConfirmExchange(CGame* pGame)
	: IDialogBox(DialogBoxId::ConfirmExchange, pGame)
{
	SetDefaultRect(285 + SCREENX, 200 + SCREENY, 270, 105);
}

void DialogBox_ConfirmExchange::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME1, sX, sY, 2);

	switch (Info().cMode)
	{
	case 1: // Question
		PutString(sX + 35, sY + 30, "Do you really want to exchange?", RGB(4, 0, 50));
		PutString(sX + 36, sY + 30, "Do you really want to exchange?", RGB(4, 0, 50));

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
		break;

	case 2: // Waiting for response
		PutString(sX + 45, sY + 36, "Waiting for response...", RGB(4, 0, 50));
		PutString(sX + 46, sY + 36, "Waiting for response...", RGB(4, 0, 50));
		break;
	}
}

bool DialogBox_ConfirmExchange::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;

	switch (Info().cMode)
	{
	case 1: // Not yet confirmed the exchange
		// Yes button
		if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
		{
			if ((m_pGame->m_stDialogBoxExchangeInfo[0].sV1 != -1) && (m_pGame->m_stDialogBoxExchangeInfo[4].sV1 != -1))
			{
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_CONFIRMEXCHANGEITEM, 0,
					m_pGame->m_stDialogBoxExchangeInfo[0].sV1,  // ItemID
					m_pGame->m_stDialogBoxExchangeInfo[0].sV3,  // Amount
					0, 0);
				PlaySoundEffect('E', 14, 5);
				m_pGame->m_dialogBoxManager.Info(DialogBoxId::Exchange).cMode = 2;
				Info().cMode = 2;
			}
			return true;
		}

		// No button
		if ((msX >= sX + 170) && (msX <= sX + 170 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
		{
			DisableThisDialog();
			DisableDialogBox(DialogBoxId::Exchange);
			DisableDialogBox(DialogBoxId::Map);
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_CANCELEXCHANGEITEM, 0, 0, 0, 0, 0);
			PlaySoundEffect('E', 14, 5);
			return true;
		}
		break;

	case 2: // Waiting for other side to confirm
		break;
	}

	return false;
}
