#include "DialogBox_Quest.h"
#include "Game.h"
#include "lan_eng.h"

DialogBox_Quest::DialogBox_Quest(CGame* pGame)
	: IDialogBox(DialogBoxId::Quest, pGame)
{
	SetDefaultRect(0 + SCREENX, 0 + SCREENY, 258, 339);
}

void DialogBox_Quest::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;
	short szX = Info().sSizeX;
	char cTxt[120], cTemp[21];

	m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
	m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 4);

	switch (Info().cMode) {
	case 1:
		switch (m_pGame->m_stQuest.sQuestType) {
		case 0:
			PutAlignedString(sX, sX + szX, sY + 50 + 115 - 30, DRAW_DIALOGBOX_QUEST1, 55, 25, 25);
			break;

		case 1: // Hunt
			if (m_pGame->m_stQuest.bIsQuestCompleted == false)
				PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_QUEST2, 55, 25, 25);
			else
				PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_QUEST3, 55, 25, 25);

			std::memset(cTxt, 0, sizeof(cTxt));
			wsprintf(cTxt, "Rest Monster : %d", m_pGame->m_stQuest.sCurrentCount);
			PutAlignedString(sX, sX + szX, sY + 50 + 20, cTxt, 55, 25, 25);

			std::memset(cTemp, 0, sizeof(cTemp));
			switch (m_pGame->m_stQuest.sWho) {
			case 1:
			case 2:
			case 3: break;
			case 4: strcpy(cTemp, NPC_NAME_CITYHALL_OFFICER); break;
			case 5:
			case 6:
			case 7: break;
			}
			std::memset(cTxt, 0, sizeof(cTxt));
			wsprintf(cTxt, DRAW_DIALOGBOX_QUEST5, cTemp);
			PutAlignedString(sX, sX + szX, sY + 50 + 45, cTxt, 55, 25, 25);

			std::memset(cTemp, 0, sizeof(cTemp));
			m_pGame->GetNpcName(m_pGame->m_stQuest.sTargetType, cTemp);
			std::memset(cTxt, 0, sizeof(cTxt));
			wsprintf(cTxt, NPC_TALK_HANDLER16, m_pGame->m_stQuest.sTargetCount, cTemp);
			PutAlignedString(sX, sX + szX, sY + 50 + 60, cTxt, 55, 25, 25);

			std::memset(cTxt, 0, sizeof(cTxt));
			if (memcmp(m_pGame->m_stQuest.cTargetName, "NONE", 4) == 0) {
				strcpy(cTxt, DRAW_DIALOGBOX_QUEST31);
				PutAlignedString(sX, sX + szX, sY + 50 + 75, cTxt, 55, 25, 25);
			}
			else {
				std::memset(cTemp, 0, sizeof(cTemp));
				m_pGame->GetOfficialMapName(m_pGame->m_stQuest.cTargetName, cTemp);
				wsprintf(cTxt, DRAW_DIALOGBOX_QUEST32, cTemp);
				PutAlignedString(sX, sX + szX, sY + 50 + 75, cTxt, 55, 25, 25);

				if (m_pGame->m_stQuest.sX != 0) {
					std::memset(cTxt, 0, sizeof(cTxt));
					wsprintf(cTxt, DRAW_DIALOGBOX_QUEST33, m_pGame->m_stQuest.sX, m_pGame->m_stQuest.sY, m_pGame->m_stQuest.sRange);
					PutAlignedString(sX, sX + szX, sY + 50 + 90, cTxt, 55, 25, 25);
				}
			}

			std::memset(cTxt, 0, sizeof(cTxt));
			wsprintf(cTxt, DRAW_DIALOGBOX_QUEST34, m_pGame->m_stQuest.sContribution);
			PutAlignedString(sX, sX + szX, sY + 50 + 105, cTxt, 55, 25, 25);
			break;

		case 7:
			if (m_pGame->m_stQuest.bIsQuestCompleted == false)
				PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_QUEST26, 55, 25, 25);
			else
				PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_QUEST27, 55, 25, 25);

			std::memset(cTemp, 0, sizeof(cTemp));
			switch (m_pGame->m_stQuest.sWho) {
			case 1:
			case 2:
			case 3: break;
			case 4: strcpy(cTemp, NPC_NAME_CITYHALL_OFFICER); break;
			case 5:
			case 6:
			case 7: break;
			}
			std::memset(cTxt, 0, sizeof(cTxt));
			wsprintf(cTxt, DRAW_DIALOGBOX_QUEST29, cTemp);
			PutAlignedString(sX, sX + szX, sY + 50 + 45, cTxt, 55, 25, 25);

			PutAlignedString(sX, sX + szX, sY + 50 + 60, DRAW_DIALOGBOX_QUEST30, 55, 25, 25);

			std::memset(cTxt, 0, sizeof(cTxt));
			if (memcmp(m_pGame->m_stQuest.cTargetName, "NONE", 4) == 0) {
				strcpy(cTxt, DRAW_DIALOGBOX_QUEST31);
				PutAlignedString(sX, sX + szX, sY + 50 + 75, cTxt, 55, 25, 25);
			}
			else {
				std::memset(cTemp, 0, sizeof(cTemp));
				m_pGame->GetOfficialMapName(m_pGame->m_stQuest.cTargetName, cTemp);
				wsprintf(cTxt, DRAW_DIALOGBOX_QUEST32, cTemp);
				PutAlignedString(sX, sX + szX, sY + 50 + 75, cTxt, 55, 25, 25);

				if (m_pGame->m_stQuest.sX != 0) {
					std::memset(cTxt, 0, sizeof(cTxt));
					wsprintf(cTxt, DRAW_DIALOGBOX_QUEST33, m_pGame->m_stQuest.sX, m_pGame->m_stQuest.sY, m_pGame->m_stQuest.sRange);
					PutAlignedString(sX, sX + szX, sY + 50 + 90, cTxt, 55, 25, 25);
				}
			}

			std::memset(cTxt, 0, sizeof(cTxt));
			wsprintf(cTxt, DRAW_DIALOGBOX_QUEST34, m_pGame->m_stQuest.sContribution);
			PutAlignedString(sX, sX + szX, sY + 50 + 105, cTxt, 55, 25, 25);
			break;
		}
		break;

	case 2:
		PutAlignedString(sX, sX + szX, sY + 50 + 115 - 30, DRAW_DIALOGBOX_QUEST35, 55, 25, 25);
		break;
	}

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
	else
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

bool DialogBox_Quest::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		m_pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::Quest);
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	return false;
}
