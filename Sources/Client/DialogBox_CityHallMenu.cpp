#include "DialogBox_CityHallMenu.h"
#include "Game.h"
#include "lan_eng.h"

DialogBox_CityHallMenu::DialogBox_CityHallMenu(CGame* pGame)
	: IDialogBox(DialogBoxId::CityHallMenu, pGame)
{
	SetDefaultRect(337 + SCREENX, 57 + SCREENY, 258, 339);
}

void DialogBox_CityHallMenu::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).sX;
	short sY = m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).sY;
	short szX = m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).sSizeX;

	m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
	m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 18);

	switch (m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode)
	{
	case 0:  DrawMode0_MainMenu(sX, sY, szX, msX, msY); break;
	case 1:  DrawMode1_CitizenshipWarning(sX, sY, szX, msX, msY); break;
	case 2:  DrawMode2_OfferingCitizenship(sX, sY, szX); break;
	case 3:  DrawMode3_CitizenshipSuccess(sX, sY, szX, msX, msY); break;
	case 4:  DrawMode4_CitizenshipFailed(sX, sY, szX, msX, msY); break;
	case 5:  DrawMode5_RewardGold(sX, sY, szX, msX, msY); break;
	case 7:  DrawMode7_HeroItems(sX, sY, szX, msX, msY); break;
	case 8:  DrawMode8_CancelQuest(sX, sY, szX, msX, msY); break;
	case 9:  DrawMode9_ChangePlayMode(sX, sY, szX, msX, msY); break;
	case 10: DrawMode10_TeleportMenu(sX, sY, szX, msX, msY); break;
	case 11: DrawMode11_HeroItemConfirm(sX, sY, szX, msX, msY); break;
	}
}

void DialogBox_CityHallMenu::DrawMode0_MainMenu(short sX, short sY, short szX, short msX, short msY)
{
	// Citizenship request
	if (m_pGame->m_bCitizen == false)
	{
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 70) && (msY < sY + 95))
			m_pGame->PutAlignedString(sX, sX + szX, sY + 70, DRAW_DIALOGBOX_CITYHALL_MENU1, 255, 255, 255);
		else
			m_pGame->PutAlignedString(sX, sX + szX, sY + 70, DRAW_DIALOGBOX_CITYHALL_MENU1, 4, 0, 50);
	}
	else
		m_pGame->PutAlignedString(sX, sX + szX, sY + 70, DRAW_DIALOGBOX_CITYHALL_MENU1, 65, 65, 65);

	// Reward gold
	if (m_pGame->m_iRewardGold > 0)
	{
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 95) && (msY < sY + 120))
			m_pGame->PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU4, 255, 255, 255);
		else
			m_pGame->PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU4, 4, 0, 50);
	}
	else
		m_pGame->PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU4, 65, 65, 65);

	// Hero's Items
	if ((m_pGame->m_iEnemyKillCount >= 100) && (m_pGame->m_iContribution >= 10))
	{
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 120) && (msY < sY + 145))
			m_pGame->PutAlignedString(sX, sX + szX, sY + 120, DRAW_DIALOGBOX_CITYHALL_MENU8, 255, 255, 255);
		else
			m_pGame->PutAlignedString(sX, sX + szX, sY + 120, DRAW_DIALOGBOX_CITYHALL_MENU8, 4, 0, 50);
	}
	else
		m_pGame->PutAlignedString(sX, sX + szX, sY + 120, DRAW_DIALOGBOX_CITYHALL_MENU8, 65, 65, 65);

	// Cancel quest
	if (m_pGame->m_stQuest.sQuestType != 0)
	{
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 145) && (msY < sY + 170))
			m_pGame->PutAlignedString(sX, sX + szX, sY + 145, DRAW_DIALOGBOX_CITYHALL_MENU11, 255, 255, 255);
		else
			m_pGame->PutAlignedString(sX, sX + szX, sY + 145, DRAW_DIALOGBOX_CITYHALL_MENU11, 4, 0, 50);
	}
	else
		m_pGame->PutAlignedString(sX, sX + szX, sY + 145, DRAW_DIALOGBOX_CITYHALL_MENU11, 65, 65, 65);

	// Change playmode
	if ((m_pGame->m_bIsCrusadeMode == false) && m_pGame->m_bCitizen && (m_pGame->m_iPKCount == 0))
	{
		if (m_pGame->m_bHunter == true)
		{
			if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 170) && (msY < sY + 195))
				m_pGame->PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU56, 255, 255, 255);
			else
				m_pGame->PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU56, 4, 0, 50);
		}
		else if (m_pGame->m_iLevel < 100)
		{
			if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 170) && (msY < sY + 195))
				m_pGame->PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU56, 255, 255, 255);
			else
				m_pGame->PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU56, 4, 0, 50);
		}
		else
			m_pGame->PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU56, 65, 65, 65);
	}
	else
		m_pGame->PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU56, 65, 65, 65);

	// Teleport menu
	if ((m_pGame->m_bIsCrusadeMode == false) && m_pGame->m_bCitizen && (m_pGame->m_iPKCount == 0))
	{
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 195) && (msY < sY + 220))
			m_pGame->PutAlignedString(sX, sX + szX, sY + 195, DRAW_DIALOGBOX_CITYHALL_MENU69, 255, 255, 255);
		else
			m_pGame->PutAlignedString(sX, sX + szX, sY + 195, DRAW_DIALOGBOX_CITYHALL_MENU69, 4, 0, 50);
	}
	else
		m_pGame->PutAlignedString(sX, sX + szX, sY + 195, DRAW_DIALOGBOX_CITYHALL_MENU69, 65, 65, 65);

	// Change crusade role
	if (m_pGame->m_bIsCrusadeMode && m_pGame->m_bCitizen)
	{
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 220) && (msY < sY + 220))
			m_pGame->PutAlignedString(sX, sX + szX, sY + 220, DRAW_DIALOGBOX_CITYHALL_MENU14, 255, 255, 255);
		else
			m_pGame->PutAlignedString(sX, sX + szX, sY + 220, DRAW_DIALOGBOX_CITYHALL_MENU14, 4, 0, 50);
	}
	else
		m_pGame->PutAlignedString(sX, sX + szX, sY + 220, DRAW_DIALOGBOX_CITYHALL_MENU14, 65, 65, 65);

	m_pGame->PutAlignedString(sX, sX + szX, sY + 270, DRAW_DIALOGBOX_CITYHALL_MENU17);
}

void DialogBox_CityHallMenu::DrawMode1_CitizenshipWarning(short sX, short sY, short szX, short msX, short msY)
{
	m_pGame->PutAlignedString(sX, sX + szX, sY + 80, DRAW_DIALOGBOX_CITYHALL_MENU18, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU19, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_CITYHALL_MENU20, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU21, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_CITYHALL_MENU22, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_CITYHALL_MENU23, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU24, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 200, DRAW_DIALOGBOX_CITYHALL_MENU25, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 215, DRAW_DIALOGBOX_CITYHALL_MENU26, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 230, DRAW_DIALOGBOX_CITYHALL_MENU27, 55, 25, 25);

	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
	else
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
	else
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
}

void DialogBox_CityHallMenu::DrawMode2_OfferingCitizenship(short sX, short sY, short szX)
{
	m_pGame->PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_CITYHALL_MENU28, 55, 25, 25);
}

void DialogBox_CityHallMenu::DrawMode3_CitizenshipSuccess(short sX, short sY, short szX, short msX, short msY)
{
	m_pGame->PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_CITYHALL_MENU29, 55, 25, 25);

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
	else
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

void DialogBox_CityHallMenu::DrawMode4_CitizenshipFailed(short sX, short sY, short szX, short msX, short msY)
{
	m_pGame->PutAlignedString(sX, sX + szX, sY + 80, DRAW_DIALOGBOX_CITYHALL_MENU30, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 100, DRAW_DIALOGBOX_CITYHALL_MENU31, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 115, DRAW_DIALOGBOX_CITYHALL_MENuint32_t, 55, 25, 25);

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
	else
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

void DialogBox_CityHallMenu::DrawMode5_RewardGold(short sX, short sY, short szX, short msX, short msY)
{
	char cTxt[120];

	m_pGame->PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU33, 55, 25, 25);
	wsprintf(cTxt, DRAW_DIALOGBOX_CITYHALL_MENU34, m_pGame->m_iRewardGold);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 140, cTxt, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_CITYHALL_MENU35, 55, 25, 25);

	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
	else
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
	else
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
}

void DialogBox_CityHallMenu::DrawMode7_HeroItems(short sX, short sY, short szX, short msX, short msY)
{
	m_pGame->PutAlignedString(sX, sX + szX, sY + 60, DRAW_DIALOGBOX_CITYHALL_MENU46, 255, 255, 255);

	// Hero's Cape (EK 300)
	if (m_pGame->m_iEnemyKillCount >= 300)
	{
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 95) && (msY < sY + 110))
			m_pGame->PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU47, 255, 255, 255);
		else
			m_pGame->PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU47, 4, 0, 50);
	}
	else
		m_pGame->PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU47, 65, 65, 65);

	// Hero's Helm (EK 150 - Contrib 20)
	if ((m_pGame->m_iEnemyKillCount >= 150) && (m_pGame->m_iContribution >= 20))
	{
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 125) && (msY < sY + 140))
			m_pGame->PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU48, 255, 255, 255);
		else
			m_pGame->PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU48, 4, 0, 50);
	}
	else
		m_pGame->PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU48, 65, 65, 65);

	// Hero's Cap (EK 100 - Contrib 20)
	if ((m_pGame->m_iEnemyKillCount >= 100) && (m_pGame->m_iContribution >= 20))
	{
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 155) && (msY < sY + 170))
			m_pGame->PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_CITYHALL_MENU49, 255, 255, 255);
		else
			m_pGame->PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_CITYHALL_MENU49, 4, 0, 50);
	}
	else
		m_pGame->PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_CITYHALL_MENU49, 65, 65, 65);

	// Hero's Armor (EK 300 - Contrib 30)
	if ((m_pGame->m_iEnemyKillCount >= 300) && (m_pGame->m_iContribution >= 30))
	{
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 185) && (msY < sY + 200))
			m_pGame->PutAlignedString(sX, sX + szX, sY + 185, DRAW_DIALOGBOX_CITYHALL_MENU50, 255, 255, 255);
		else
			m_pGame->PutAlignedString(sX, sX + szX, sY + 185, DRAW_DIALOGBOX_CITYHALL_MENU50, 4, 0, 50);
	}
	else
		m_pGame->PutAlignedString(sX, sX + szX, sY + 185, DRAW_DIALOGBOX_CITYHALL_MENU50, 65, 65, 65);

	// Hero's Robe (EK 200 - Contrib 20)
	if ((m_pGame->m_iEnemyKillCount >= 200) && (m_pGame->m_iContribution >= 20))
	{
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 215) && (msY < sY + 230))
			m_pGame->PutAlignedString(sX, sX + szX, sY + 215, DRAW_DIALOGBOX_CITYHALL_MENU51, 255, 255, 255);
		else
			m_pGame->PutAlignedString(sX, sX + szX, sY + 215, DRAW_DIALOGBOX_CITYHALL_MENU51, 4, 0, 50);
	}
	else
		m_pGame->PutAlignedString(sX, sX + szX, sY + 215, DRAW_DIALOGBOX_CITYHALL_MENU51, 65, 65, 65);

	// Hero's Hauberk (EK 100 - Contrib 10)
	if ((m_pGame->m_iEnemyKillCount >= 100) && (m_pGame->m_iContribution >= 10))
	{
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 245) && (msY < sY + 260))
			m_pGame->PutAlignedString(sX, sX + szX, sY + 245, DRAW_DIALOGBOX_CITYHALL_MENU52, 255, 255, 255);
		else
			m_pGame->PutAlignedString(sX, sX + szX, sY + 245, DRAW_DIALOGBOX_CITYHALL_MENU52, 4, 0, 50);
	}
	else
		m_pGame->PutAlignedString(sX, sX + szX, sY + 245, DRAW_DIALOGBOX_CITYHALL_MENU52, 65, 65, 65);

	// Hero's Leggings (EK 150 - Contrib 15)
	if ((m_pGame->m_iEnemyKillCount >= 150) && (m_pGame->m_iContribution >= 15))
	{
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 275) && (msY < sY + 290))
			m_pGame->PutAlignedString(sX, sX + szX, sY + 275, DRAW_DIALOGBOX_CITYHALL_MENU53, 255, 255, 255);
		else
			m_pGame->PutAlignedString(sX, sX + szX, sY + 275, DRAW_DIALOGBOX_CITYHALL_MENU53, 4, 0, 50);
	}
	else
		m_pGame->PutAlignedString(sX, sX + szX, sY + 275, DRAW_DIALOGBOX_CITYHALL_MENU53, 65, 65, 65);
}

void DialogBox_CityHallMenu::DrawMode8_CancelQuest(short sX, short sY, short szX, short msX, short msY)
{
	m_pGame->PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU54, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_CITYHALL_MENU55, 55, 25, 25);

	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
	else
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
	else
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
}

void DialogBox_CityHallMenu::DrawMode9_ChangePlayMode(short sX, short sY, short szX, short msX, short msY)
{
	if (m_pGame->m_bHunter)
		m_pGame->PutAlignedString(sX, sX + szX, sY + 53, DRAW_DIALOGBOX_CITYHALL_MENU57, 200, 200, 25);
	else
		m_pGame->PutAlignedString(sX, sX + szX, sY + 53, DRAW_DIALOGBOX_CITYHALL_MENU58, 200, 200, 25);

	m_pGame->PutAlignedString(sX, sX + szX, sY + 78, DRAW_DIALOGBOX_CITYHALL_MENU59, 55, 25, 25);
	m_pGame->PutString(sX + 35, sY + 108, DRAW_DIALOGBOX_CITYHALL_MENU60, RGB(220, 130, 45));
	m_pGame->PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU61, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_CITYHALL_MENU62, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_CITYHALL_MENU63, 55, 25, 25);
	m_pGame->PutString(sX + 35, sY + 177, DRAW_DIALOGBOX_CITYHALL_MENU64, RGB(220, 130, 45));
	m_pGame->PutAlignedString(sX, sX + szX, sY + 194, DRAW_DIALOGBOX_CITYHALL_MENU65, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 209, DRAW_DIALOGBOX_CITYHALL_MENU66, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 224, DRAW_DIALOGBOX_CITYHALL_MENU67, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 252, DRAW_DIALOGBOX_CITYHALL_MENU68, 55, 25, 25);

	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
	else
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
	else
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
}

void DialogBox_CityHallMenu::DrawMode10_TeleportMenu(short sX, short sY, short szX, short msX, short msY)
{
	char cTxt[120];

	if (m_pGame->m_iTeleportMapCount > 0)
	{
		m_pGame->PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_CITYHALL_MENU69, 55, 25, 25);
		m_pGame->PutAlignedString(sX, sX + szX, sY + 80, DRAW_DIALOGBOX_CITYHALL_MENU70, 55, 25, 25);
		m_pGame->PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU71, 55, 25, 25);
		m_pGame->PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_CITYHALL_MENU72, 55, 25, 25);
		m_pGame->PutString2(sX + 35, sY + 250, DRAW_DIALOGBOX_CITYHALL_MENU72_1, 55, 25, 25);

		for (int i = 0; i < m_pGame->m_iTeleportMapCount; i++)
		{
			std::memset(cTxt, 0, sizeof(cTxt));
			m_pGame->GetOfficialMapName(m_pGame->m_stTeleportList[i].mapname, cTxt);
			wsprintf(m_pGame->G_cTxt, DRAW_DIALOGBOX_CITYHALL_MENU77, cTxt, m_pGame->m_stTeleportList[i].iCost);

			if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 130 + i * 15) && (msY <= sY + 144 + i * 15))
				m_pGame->PutAlignedString(sX, sX + szX, sY + 130 + i * 15, m_pGame->G_cTxt, 255, 255, 255);
			else
				m_pGame->PutAlignedString(sX, sX + szX, sY + 130 + i * 15, m_pGame->G_cTxt, 250, 250, 0);
		}
	}
	else if (m_pGame->m_iTeleportMapCount == -1)
	{
		m_pGame->PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU73, 55, 25, 25);
		m_pGame->PutAlignedString(sX, sX + szX, sY + 150, DRAW_DIALOGBOX_CITYHALL_MENU74, 55, 25, 25);
		m_pGame->PutAlignedString(sX, sX + szX, sY + 175, DRAW_DIALOGBOX_CITYHALL_MENU75, 55, 25, 25);
	}
	else
	{
		m_pGame->PutAlignedString(sX, sX + szX, sY + 175, DRAW_DIALOGBOX_CITYHALL_MENU76, 55, 25, 25);
	}
}

void DialogBox_CityHallMenu::DrawMode11_HeroItemConfirm(short sX, short sY, short szX, short msX, short msY)
{
	m_pGame->PutAlignedString(sX, sX + szX - 1, sY + 125, m_pGame->m_cTakeHeroItemName, 55, 25, 25);
	m_pGame->PutAlignedString(sX + 1, sX + szX, sY + 125, m_pGame->m_cTakeHeroItemName, 55, 25, 25);
	m_pGame->PutAlignedString(sX, sX + szX, sY + 260, DRAW_DIALOGBOX_CITYHALL_MENU46A, 55, 25, 25);

	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
	else
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
	else
		m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
}

bool DialogBox_CityHallMenu::OnClick(short msX, short msY)
{
	short sX = m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).sX;
	short sY = m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).sY;

	switch (m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode)
	{
	case 0:  return OnClickMode0(sX, sY, msX, msY);
	case 1:  return OnClickMode1(sX, sY, msX, msY);
	case 3:
	case 4:  return OnClickMode3_4(sX, sY, msX, msY);
	case 5:  return OnClickMode5(sX, sY, msX, msY);
	case 7:  return OnClickMode7(sX, sY, msX, msY);
	case 8:  return OnClickMode8(sX, sY, msX, msY);
	case 9:  return OnClickMode9(sX, sY, msX, msY);
	case 10: return OnClickMode10(sX, sY, msX, msY);
	case 11: return OnClickMode11(sX, sY, msX, msY);
	}
	return false;
}

bool DialogBox_CityHallMenu::OnClickMode0(short sX, short sY, short msX, short msY)
{
	// Citizenship request
	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 70) && (msY < sY + 95))
	{
		if (m_pGame->m_bCitizen == true) return false;
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 1;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// Reward gold
	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 95) && (msY < sY + 120))
	{
		if (m_pGame->m_iRewardGold <= 0) return false;
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 5;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// Hero items
	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 120) && (msY < sY + 145))
	{
		if (m_pGame->m_iEnemyKillCount < 100) return false;
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 7;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// Cancel quest
	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 145) && (msY < sY + 170))
	{
		if (m_pGame->m_stQuest.sQuestType == 0) return false;
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 8;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// Change playmode
	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 170) && (msY < sY + 195))
	{
		if (m_pGame->m_bIsCrusadeMode) return false;
		if (m_pGame->m_iPKCount != 0) return false;
		if (m_pGame->m_bCitizen == false) return false;
		if ((m_pGame->m_iLevel > 100) && (m_pGame->m_bHunter == false)) return false;
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 9;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// Teleport menu
	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 195) && (msY < sY + 220))
	{
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 10;
		m_pGame->m_iTeleportMapCount = -1;
		m_pGame->bSendCommand(MSGID_REQUEST_TELEPORT_LIST, 0, 0, 0, 0, 0, 0);
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// Crusade job
	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 220) && (msY < sY + 245))
	{
		if (m_pGame->m_bIsCrusadeMode == false) return false;
		m_pGame->m_dialogBoxManager.EnableDialogBox(DialogBoxId::CrusadeJob, 1, 0, 0);
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	return false;
}

bool DialogBox_CityHallMenu::OnClickMode1(short sX, short sY, short msX, short msY)
{
	// Yes button
	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
	{
		m_pGame->bSendCommand(MSGID_REQUEST_CIVILRIGHT, DEF_MSGTYPE_CONFIRM, 0, 0, 0, 0, 0);
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 2;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// No button
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
	{
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 0;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	return false;
}

bool DialogBox_CityHallMenu::OnClickMode3_4(short sX, short sY, short msX, short msY)
{
	// OK button
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
	{
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 0;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}
	return false;
}

bool DialogBox_CityHallMenu::OnClickMode5(short sX, short sY, short msX, short msY)
{
	// Yes button
	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
	{
		m_pGame->bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_GETREWARDMONEY, 0, 0, 0, 0, 0);
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 0;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// No button
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
	{
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 0;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	return false;
}

bool DialogBox_CityHallMenu::OnClickMode7(short sX, short sY, short msX, short msY)
{
	int iReqHeroItemID = 0;

	// Hero's Cape
	if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 95) && (msY <= sY + 110))
	{
		if (m_pGame->m_bAresden == true) iReqHeroItemID = 400;
		else iReqHeroItemID = 401;
		std::memset(m_pGame->m_cTakeHeroItemName, 0, sizeof(m_pGame->m_cTakeHeroItemName));
		memcpy(m_pGame->m_cTakeHeroItemName, DRAW_DIALOGBOX_CITYHALL_MENU47, strlen(DRAW_DIALOGBOX_CITYHALL_MENU47));
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 11;
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).sV1 = iReqHeroItemID;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// Hero's Helm
	if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 125) && (msY <= sY + 140))
	{
		if ((m_pGame->m_bAresden == true) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 403;
		if ((m_pGame->m_bAresden == true) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 404;
		if ((m_pGame->m_bAresden == false) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 405;
		if ((m_pGame->m_bAresden == false) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 406;
		std::memset(m_pGame->m_cTakeHeroItemName, 0, sizeof(m_pGame->m_cTakeHeroItemName));
		memcpy(m_pGame->m_cTakeHeroItemName, DRAW_DIALOGBOX_CITYHALL_MENU48, strlen(DRAW_DIALOGBOX_CITYHALL_MENU48));
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 11;
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).sV1 = iReqHeroItemID;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// Hero's Cap
	if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 155) && (msY <= sY + 170))
	{
		if ((m_pGame->m_bAresden == true) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 407;
		if ((m_pGame->m_bAresden == true) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 408;
		if ((m_pGame->m_bAresden == false) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 409;
		if ((m_pGame->m_bAresden == false) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 410;
		std::memset(m_pGame->m_cTakeHeroItemName, 0, sizeof(m_pGame->m_cTakeHeroItemName));
		memcpy(m_pGame->m_cTakeHeroItemName, DRAW_DIALOGBOX_CITYHALL_MENU49, strlen(DRAW_DIALOGBOX_CITYHALL_MENU49));
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 11;
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).sV1 = iReqHeroItemID;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// Hero's Armor
	if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 185) && (msY <= sY + 200))
	{
		if ((m_pGame->m_bAresden == true) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 411;
		if ((m_pGame->m_bAresden == true) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 412;
		if ((m_pGame->m_bAresden == false) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 413;
		if ((m_pGame->m_bAresden == false) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 414;
		std::memset(m_pGame->m_cTakeHeroItemName, 0, sizeof(m_pGame->m_cTakeHeroItemName));
		memcpy(m_pGame->m_cTakeHeroItemName, DRAW_DIALOGBOX_CITYHALL_MENU50, strlen(DRAW_DIALOGBOX_CITYHALL_MENU50));
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 11;
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).sV1 = iReqHeroItemID;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// Hero's Robe
	if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 215) && (msY <= sY + 230))
	{
		if ((m_pGame->m_bAresden == true) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 415;
		if ((m_pGame->m_bAresden == true) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 416;
		if ((m_pGame->m_bAresden == false) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 417;
		if ((m_pGame->m_bAresden == false) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 418;
		std::memset(m_pGame->m_cTakeHeroItemName, 0, sizeof(m_pGame->m_cTakeHeroItemName));
		memcpy(m_pGame->m_cTakeHeroItemName, DRAW_DIALOGBOX_CITYHALL_MENU51, strlen(DRAW_DIALOGBOX_CITYHALL_MENU51));
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 11;
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).sV1 = iReqHeroItemID;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// Hero's Hauberk
	if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 245) && (msY <= sY + 260))
	{
		if ((m_pGame->m_bAresden == true) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 419;
		if ((m_pGame->m_bAresden == true) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 420;
		if ((m_pGame->m_bAresden == false) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 421;
		if ((m_pGame->m_bAresden == false) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 422;
		std::memset(m_pGame->m_cTakeHeroItemName, 0, sizeof(m_pGame->m_cTakeHeroItemName));
		memcpy(m_pGame->m_cTakeHeroItemName, DRAW_DIALOGBOX_CITYHALL_MENU52, strlen(DRAW_DIALOGBOX_CITYHALL_MENU52));
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 11;
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).sV1 = iReqHeroItemID;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// Hero's Leggings
	if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 275) && (msY <= sY + 290))
	{
		if ((m_pGame->m_bAresden == true) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 423;
		if ((m_pGame->m_bAresden == true) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 424;
		if ((m_pGame->m_bAresden == false) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 425;
		if ((m_pGame->m_bAresden == false) && (m_pGame->m_pCharList[m_pGame->m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 426;
		std::memset(m_pGame->m_cTakeHeroItemName, 0, sizeof(m_pGame->m_cTakeHeroItemName));
		memcpy(m_pGame->m_cTakeHeroItemName, DRAW_DIALOGBOX_CITYHALL_MENU53, strlen(DRAW_DIALOGBOX_CITYHALL_MENU53));
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 11;
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).sV1 = iReqHeroItemID;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	return false;
}

bool DialogBox_CityHallMenu::OnClickMode8(short sX, short sY, short msX, short msY)
{
	// Yes button
	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
	{
		m_pGame->bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_CANCELQUEST, 0, 0, 0, 0, 0);
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 0;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// No button
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
	{
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 0;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	return false;
}

bool DialogBox_CityHallMenu::OnClickMode9(short sX, short sY, short msX, short msY)
{
	// Yes button
	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
	{
		m_pGame->bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_HUNTMODE, 0, 0, 0, 0, 0);
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 0;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// No button
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
	{
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 0;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	return false;
}

bool DialogBox_CityHallMenu::OnClickMode10(short sX, short sY, short msX, short msY)
{
	if (m_pGame->m_iTeleportMapCount > 0)
	{
		for (int i = 0; i < m_pGame->m_iTeleportMapCount; i++)
		{
			if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 130 + i * 15) && (msY <= sY + 144 + i * 15))
			{
				m_pGame->bSendCommand(MSGID_REQUEST_CHARGED_TELEPORT, 0, 0, m_pGame->m_stTeleportList[i].iIndex, 0, 0, 0);
				m_pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::CityHallMenu);
				return true;
			}
		}
	}
	return false;
}

bool DialogBox_CityHallMenu::OnClickMode11(short sX, short sY, short msX, short msY)
{
	// Yes button
	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
	{
		m_pGame->bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_GETHEROMANTLE, 0, m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).sV1, 0, 0, 0);
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 0;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	// No button
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
	{
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::CityHallMenu).cMode = 7;
		m_pGame->PlaySound('E', 14, 5);
		return true;
	}

	return false;
}
