#include "DialogBox_Slates.h"
#include "Game.h"
#include "SpriteID.h"
#include "NetMessages.h"

DialogBox_Slates::DialogBox_Slates(CGame* pGame)
	: IDialogBox(DialogBoxId::Slates, pGame)
{
}

void DialogBox_Slates::OnDraw(short msX, short msY, short msZ, char cLB)
{
	int iAdjX, iAdjY;
	short sX, sY;
	uint32_t dwTime = m_pGame->m_dwCurTime;

	iAdjX = 5;
	iAdjY = 8;

	switch (Info().cMode) {
	case 1:
		sX = Info().sX;
		sY = Info().sY;
		iAdjX = -1;
		iAdjY = -7;

		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX, sY, 4);

		if (Info().sV1 != -1) {
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX + 20, sY + 12, 5);
		}
		if (Info().sV2 != -1) {
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX + 20, sY + 87, 6);
		}
		if (Info().sV3 != -1) {
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX + 85, sY + 32, 7);
		}
		if (Info().sV4 != -1) {
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX + 70, sY + 97, 8);
		}

		if ((Info().sV1 != -1) && (Info().sV2 != -1) && (Info().sV3 != -1) && (Info().sV4 != -1)) {
			if ((msX >= sX + 120) && (msX <= sX + 180) && (msY >= sY + 150) && (msY <= sY + 165))
				m_pGame->PutString_SprFont(sX + 120, sY + 150, "Casting", 6, 6, 20);
			else m_pGame->PutString_SprFont(sX + 120, sY + 150, "Casting", 0, 0, 7);
		}
		break;

	case 2:
		m_pGame->PlaySound('E', 16, 0);
		if (Info().cStr[0] != 0)
		{
			sX = Info().sX + iAdjX + (Info().cStr[0] - (rand() % (Info().cStr[0] * 2)));
			sY = Info().sY + iAdjY + (Info().cStr[0] - (rand() % (Info().cStr[0] * 2)));
		}
		else
		{
			sX = Info().sX;
			sY = Info().sY;
		}
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_INVENTORY]->PutSpriteFast(sX, sY, 4, dwTime);
		m_pGame->m_pSprite[DEF_SPRID_INTERFACE_ND_INVENTORY]->PutSpriteFast(sX + 22, sY + 14, 3, dwTime);
		PutAlignedString(199, 438, 201, "KURURURURURURURURU!!!", 220, 140, 160);
		PutAlignedString(200, 439, 200, "KURURURURURURURURU!!!", 90, 220, 200);

		if ((dwTime - Info().dwT1) > 1000)
		{
			Info().dwT1 = dwTime;
			Info().cStr[0]++;
		}
		if (Info().cStr[0] >= 5)
		{
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_CREATESLATE, 0, Info().sV1, Info().sV2, Info().sV3, 0, Info().sV4);
			DisableDialogBox(DialogBoxId::Slates);
		}
		break;
	}
}

bool DialogBox_Slates::OnClick(short msX, short msY)
{
	short sX, sY;

	sX = Info().sX;
	sY = Info().sY;

	switch (Info().cMode) {
	case 1:
		if ((Info().sV1 != -1) && (Info().sV2 != -1) && (Info().sV3 != -1) && (Info().sV4 != -1)) {
			if ((msX >= sX + 120) && (msX <= sX + 180) && (msY >= sY + 150) && (msY <= sY + 165)) {
				Info().cMode = 2;
				PlaySoundEffect('E', 14, 5);
			}
		}
		break;
	}
	return false;
}
