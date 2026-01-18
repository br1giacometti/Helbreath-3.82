#include "DialogBox_Fishing.h"
#include "Game.h"
#include "GlobalDef.h"
#include "lan_eng.h"

DialogBox_Fishing::DialogBox_Fishing(CGame* pGame)
	: IDialogBox(DialogBoxId::Fishing, pGame)
{
	SetDefaultRect(193 + SCREENX, 241 + SCREENY, 263, 100);
}

void DialogBox_Fishing::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;
	uint32_t dwTime = m_pGame->m_dwCurTime;
	char cTxt[120];

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME1, sX, sY, 2);

	char cStr1[64], cStr2[64], cStr3[64];
	m_pGame->GetItemName(m_pGame->FindItemIdByName(Info().cStr), 0, cStr1, cStr2, cStr3);

	switch (Info().cMode)
	{
	case 0:
		m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + Info().sV3]->PutSpriteFast(
			sX + 18 + 35, sY + 18 + 17, Info().sV4, dwTime);

		wsprintf(cTxt, "%s", cStr1);
		PutString(sX + 98, sY + 14, cTxt, RGB(255, 255, 255));

		wsprintf(cTxt, DRAW_DIALOGBOX_FISHING1, Info().sV2);
		PutString(sX + 98, sY + 28, cTxt, RGB(0, 0, 0));

		PutString(sX + 97, sY + 43, DRAW_DIALOGBOX_FISHING2, RGB(0, 0, 0));

		wsprintf(cTxt, "%d %%", Info().sV1);
		m_pGame->PutString_SprFont(sX + 157, sY + 40, cTxt, 10, 0, 0);

		// "Try Now!" button
		if ((msX >= sX + 160) && (msX <= sX + 253) && (msY >= sY + 70) && (msY <= sY + 90))
			m_pGame->PutString_SprFont(sX + 160, sY + 70, "Try Now!", 6, 6, 20);
		else
			m_pGame->PutString_SprFont(sX + 160, sY + 70, "Try Now!", 0, 0, 7);
		break;
	}
}

bool DialogBox_Fishing::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;

	switch (Info().cMode)
	{
	case 0:
		if ((msX >= sX + 160) && (msX <= sX + 253) && (msY >= sY + 70) && (msY <= sY + 90))
		{
			m_pGame->bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_GETFISHTHISTIME, 0, 0, 0, 0, 0);
			m_pGame->AddEventList(DLGBOX_CLICK_FISH1, 10);
			DisableDialogBox(DialogBoxId::Fishing);
			m_pGame->PlaySound('E', 14, 5);
			return true;
		}
		break;
	}

	return false;
}
