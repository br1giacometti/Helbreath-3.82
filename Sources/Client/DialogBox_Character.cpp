#include "DialogBox_Character.h"
#include "ConfigManager.h"
#include "Game.h"
#include "lan_eng.h"
#include "SharedCalculations.h"

DialogBox_Character::DialogBox_Character(CGame* pGame)
	: IDialogBox(DialogBoxId::CharacterInfo, pGame)
{
	SetDefaultRect(30 + SCREENX, 30 + SCREENY, 270, 376);
}

// Helper: Display stat with optional angelic bonus (blue if boosted)
void DialogBox_Character::DrawStat(int x1, int x2, int y, int baseStat, int angelicBonus)
{
	if (angelicBonus == 0)
	{
		wsprintf(m_pGame->G_cTxt, "%d", baseStat);
		PutAlignedString(x1, x2, y, m_pGame->G_cTxt, 45, 25, 25);
	}
	else
	{
		wsprintf(m_pGame->G_cTxt, "%d", baseStat + angelicBonus);
		PutAlignedString(x1, x2, y, m_pGame->G_cTxt, 0, 0, 192);
	}
}

// Helper: Render equipped item and check collision
char DialogBox_Character::DrawEquippedItem(int equipPos, int drawX, int drawY, short msX, short msY,
	const char* cEquipPoiStatus, bool useWeaponColors, int spriteOffset)
{
	int itemIdx = cEquipPoiStatus[equipPos];
	if (itemIdx == -1) return -1;

	short sSprH = m_pGame->m_pItemList[itemIdx]->m_sSprite;
	short sFrame = m_pGame->m_pItemList[itemIdx]->m_sSpriteFrame;
	char cItemColor = m_pGame->m_pItemList[itemIdx]->m_cItemColor;
	bool bDisabled = m_pGame->m_bIsItemDisabled[itemIdx];

	// Select color array based on item type (weapons use different colors)
	uint16_t* wR = useWeaponColors ? m_pGame->m_wWR : m_pGame->m_wR;
	uint16_t* wG = useWeaponColors ? m_pGame->m_wWG : m_pGame->m_wG;
	uint16_t* wB = useWeaponColors ? m_pGame->m_wWB : m_pGame->m_wB;

	auto* pSprite = m_pGame->m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + spriteOffset];

	if (!bDisabled)
	{
		if (cItemColor == 0)
			pSprite->PutSpriteFast(drawX, drawY, sFrame, m_pGame->m_dwCurTime);
		else
			pSprite->PutSpriteRGB(drawX, drawY, sFrame,
				wR[cItemColor] - m_pGame->m_wR[0],
				wG[cItemColor] - m_pGame->m_wG[0],
				wB[cItemColor] - m_pGame->m_wB[0], m_pGame->m_dwCurTime);
	}
	else
	{
		if (cItemColor == 0)
			pSprite->PutTransSprite2(drawX, drawY, sFrame, m_pGame->m_dwCurTime);
		else
			pSprite->PutTransSpriteRGB(drawX, drawY, sFrame,
				wR[cItemColor] - m_pGame->m_wR[0],
				wG[cItemColor] - m_pGame->m_wG[0],
				wB[cItemColor] - m_pGame->m_wB[0], m_pGame->m_dwCurTime);
	}

	if (pSprite->_bCheckCollison(drawX, drawY, sFrame, msX, msY))
		return (char)equipPos;

	return -1;
}

// Helper: Draw hover button
void DialogBox_Character::DrawHoverButton(int sX, int sY, int btnX, int btnY,
	short msX, short msY, int hoverFrame, int normalFrame)
{
	bool bHover = (msX >= sX + btnX) && (msX <= sX + btnX + DEF_BTNSZX) &&
	              (msY >= sY + btnY) && (msY <= sY + btnY + DEF_BTNSZY);
	const bool dialogTrans = ConfigManager::Get().IsDialogTransparencyEnabled();
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + btnX, sY + btnY,
		bHover ? hoverFrame : normalFrame, false, dialogTrans);
}

void DialogBox_Character::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;
	char cCollison = -1;
	const bool dialogTrans = ConfigManager::Get().IsDialogTransparencyEnabled();

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 0, false, dialogTrans);

	// Player name and PK/contribution
	std::memset(m_pGame->G_cTxt, 0, sizeof(m_pGame->G_cTxt));
	strcpy(m_pGame->G_cTxt, m_pGame->m_cPlayerName);
	strcat(m_pGame->G_cTxt, " : ");

	char cTxt2[120];
	if (m_pGame->m_iPKCount > 0) {
		wsprintf(cTxt2, DRAW_DIALOGBOX_CHARACTER1, m_pGame->m_iPKCount);
		strcat(m_pGame->G_cTxt, cTxt2);
	}
	wsprintf(cTxt2, DRAW_DIALOGBOX_CHARACTER2, m_pGame->m_iContribution);
	strcat(m_pGame->G_cTxt, cTxt2);
	PutAlignedString(sX + 24, sX + 252, sY + 52, m_pGame->G_cTxt, 45, 20, 20);

	// Citizenship / Guild status
	std::memset(m_pGame->G_cTxt, 0, sizeof(m_pGame->G_cTxt));
	if (!m_pGame->m_bCitizen)
	{
		strcpy(m_pGame->G_cTxt, DRAW_DIALOGBOX_CHARACTER7);
	}
	else
	{
		strcat(m_pGame->G_cTxt, m_pGame->m_bHunter
			? (m_pGame->m_bAresden ? DEF_MSG_ARECIVIL : DEF_MSG_ELVCIVIL)
			: (m_pGame->m_bAresden ? DEF_MSG_ARESOLDIER : DEF_MSG_ELVSOLDIER));

		if (m_pGame->m_iGuildRank >= 0)
		{
			strcat(m_pGame->G_cTxt, "(");
			strcat(m_pGame->G_cTxt, m_pGame->m_cGuildName);
			strcat(m_pGame->G_cTxt, m_pGame->m_iGuildRank == 0 ? DEF_MSG_GUILDMASTER1 : DEF_MSG_GUILDSMAN1);
		}
	}
	PutAlignedString(sX, sX + 275, sY + 69, m_pGame->G_cTxt, 45, 25, 25);

	// Level, Exp, Next Exp
	wsprintf(m_pGame->G_cTxt, "%d", m_pGame->m_iLevel);
	PutAlignedString(sX + 180, sX + 250, sY + 106, m_pGame->G_cTxt, 45, 25, 25);

	m_pGame->DisplayCommaNumber_G_cTxt(m_pGame->m_iExp);
	PutAlignedString(sX + 180, sX + 250, sY + 125, m_pGame->G_cTxt, 45, 25, 25);

	m_pGame->DisplayCommaNumber_G_cTxt(m_pGame->iGetLevelExp(m_pGame->m_iLevel + 1));
	PutAlignedString(sX + 180, sX + 250, sY + 142, m_pGame->G_cTxt, 45, 25, 25);

	// Calculate max stats
	int iMaxHP = CalculateMaxHP(m_pGame->m_iVit, m_pGame->m_iLevel, m_pGame->m_iStr, m_pGame->m_iAngelicStr);
	int iMaxMP = CalculateMaxMP(m_pGame->m_iMag, m_pGame->m_iAngelicMag, m_pGame->m_iLevel, m_pGame->m_iInt, m_pGame->m_iAngelicInt);
	int iMaxSP = CalculateMaxSP(m_pGame->m_iStr, m_pGame->m_iAngelicStr, m_pGame->m_iLevel);
	int iMaxLoad = CalculateMaxLoad(m_pGame->m_iStr, m_pGame->m_iAngelicStr, m_pGame->m_iLevel);

	// HP, MP, SP
	wsprintf(m_pGame->G_cTxt, "%d/%d", m_pGame->m_iHP, iMaxHP);
	PutAlignedString(sX + 180, sX + 250, sY + 173, m_pGame->G_cTxt, 45, 25, 25);

	wsprintf(m_pGame->G_cTxt, "%d/%d", m_pGame->m_iMP, iMaxMP);
	PutAlignedString(sX + 180, sX + 250, sY + 191, m_pGame->G_cTxt, 45, 25, 25);

	wsprintf(m_pGame->G_cTxt, "%d/%d", m_pGame->m_iSP, iMaxSP);
	PutAlignedString(sX + 180, sX + 250, sY + 208, m_pGame->G_cTxt, 45, 25, 25);

	// Max Load
	int iTotalWeight = m_pGame->_iCalcTotalWeight();
	wsprintf(m_pGame->G_cTxt, "%d/%d", (iTotalWeight / 100), iMaxLoad);
	PutAlignedString(sX + 180, sX + 250, sY + 240, m_pGame->G_cTxt, 45, 25, 25);

	// Enemy Kills
	wsprintf(m_pGame->G_cTxt, "%d", m_pGame->m_iEnemyKillCount);
	PutAlignedString(sX + 180, sX + 250, sY + 257, m_pGame->G_cTxt, 45, 25, 25);

	// Stats with angelic bonuses
	DrawStat(sX + 48, sX + 82, sY + 285, m_pGame->m_iStr, m_pGame->m_iAngelicStr);   // Str
	DrawStat(sX + 48, sX + 82, sY + 302, m_pGame->m_iDex, m_pGame->m_iAngelicDex);   // Dex
	DrawStat(sX + 135, sX + 167, sY + 285, m_pGame->m_iInt, m_pGame->m_iAngelicInt); // Int
	DrawStat(sX + 135, sX + 167, sY + 302, m_pGame->m_iMag, m_pGame->m_iAngelicMag); // Mag

	// Vit and Chr (no angelic bonus)
	wsprintf(m_pGame->G_cTxt, "%d", m_pGame->m_iVit);
	PutAlignedString(sX + 218, sX + 251, sY + 285, m_pGame->G_cTxt, 45, 25, 25);
	wsprintf(m_pGame->G_cTxt, "%d", m_pGame->m_iCharisma);
	PutAlignedString(sX + 218, sX + 251, sY + 302, m_pGame->G_cTxt, 45, 25, 25);

	// Build equipment status array
	char cEquipPoiStatus[DEF_MAXITEMEQUIPPOS];
	std::memset(cEquipPoiStatus, -1, sizeof(cEquipPoiStatus));
	for (int i = 0; i < DEF_MAXITEMS; i++)
	{
		if (m_pGame->m_pItemList[i] != nullptr && m_pGame->m_bIsItemEquipped[i])
			cEquipPoiStatus[m_pGame->m_pItemList[i]->m_cEquipPos] = i;
	}

	// Draw character model based on gender
	if (m_pGame->m_sPlayerType >= 1 && m_pGame->m_sPlayerType <= 3)
	{
		DrawMaleCharacter(sX, sY, msX, msY, cEquipPoiStatus, cCollison);
	}
	else if (m_pGame->m_sPlayerType >= 4 && m_pGame->m_sPlayerType <= 6)
	{
		DrawFemaleCharacter(sX, sY, msX, msY, cEquipPoiStatus, cCollison);
	}

	// Draw buttons (Quest, Party, LevelUp)
	DrawHoverButton(sX, sY, 15, 340, msX, msY, 5, 4);   // Quest
	DrawHoverButton(sX, sY, 98, 340, msX, msY, 45, 44); // Party
	DrawHoverButton(sX, sY, 180, 340, msX, msY, 11, 10); // LevelUp
}

void DialogBox_Character::DrawMaleCharacter(short sX, short sY, short msX, short msY,
	const char* cEquipPoiStatus, char& cCollison)
{
	int iR, iG, iB;
	short sSprH, sFrame;
	char cItemColor;

	// Base body
	m_pGame->m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 0]->PutSpriteFast(sX + 171, sY + 290, m_pGame->m_sPlayerType - 1, m_pGame->m_dwCurTime);

	// Hair (if no helmet)
	if (cEquipPoiStatus[DEF_EQUIPPOS_HEAD] == -1)
	{
		m_pGame->_GetHairColorRGB(((m_pGame->m_sPlayerAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
		m_pGame->m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 18]->PutSpriteRGB(sX + 171, sY + 290, (m_pGame->m_sPlayerAppr1 & 0x0F00) >> 8, iR, iG, iB, m_pGame->m_dwCurTime);
	}

	// Underwear
	m_pGame->m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 19]->PutSpriteFast(sX + 171, sY + 290, (m_pGame->m_sPlayerAppr1 & 0x000F), m_pGame->m_dwCurTime);

	// Equipment slots at character position (171, 290)
	char result;
	result = DrawEquippedItem(DEF_EQUIPPOS_BACK, sX + 41, sY + 137, msX, msY, cEquipPoiStatus, false);
	if (result != -1) cCollison = result;

	result = DrawEquippedItem(DEF_EQUIPPOS_PANTS, sX + 171, sY + 290, msX, msY, cEquipPoiStatus, false);
	if (result != -1) cCollison = result;

	result = DrawEquippedItem(DEF_EQUIPPOS_ARMS, sX + 171, sY + 290, msX, msY, cEquipPoiStatus, false);
	if (result != -1) cCollison = result;

	result = DrawEquippedItem(DEF_EQUIPPOS_BOOTS, sX + 171, sY + 290, msX, msY, cEquipPoiStatus, false);
	if (result != -1) cCollison = result;

	result = DrawEquippedItem(DEF_EQUIPPOS_BODY, sX + 171, sY + 290, msX, msY, cEquipPoiStatus, false);
	if (result != -1) cCollison = result;

	result = DrawEquippedItem(DEF_EQUIPPOS_FULLBODY, sX + 171, sY + 290, msX, msY, cEquipPoiStatus, false);
	if (result != -1) cCollison = result;

	// Weapons use weapon colors
	result = DrawEquippedItem(DEF_EQUIPPOS_LHAND, sX + 90, sY + 170, msX, msY, cEquipPoiStatus, true);
	if (result != -1) cCollison = result;

	result = DrawEquippedItem(DEF_EQUIPPOS_RHAND, sX + 57, sY + 186, msX, msY, cEquipPoiStatus, true);
	if (result != -1) cCollison = result;

	result = DrawEquippedItem(DEF_EQUIPPOS_TWOHAND, sX + 57, sY + 186, msX, msY, cEquipPoiStatus, true);
	if (result != -1) cCollison = result;

	// Accessories
	result = DrawEquippedItem(DEF_EQUIPPOS_NECK, sX + 35, sY + 120, msX, msY, cEquipPoiStatus, false);
	if (result != -1) cCollison = result;

	result = DrawEquippedItem(DEF_EQUIPPOS_RFINGER, sX + 32, sY + 193, msX, msY, cEquipPoiStatus, false);
	if (result != -1) cCollison = result;

	result = DrawEquippedItem(DEF_EQUIPPOS_LFINGER, sX + 98, sY + 182, msX, msY, cEquipPoiStatus, false);
	if (result != -1) cCollison = result;

	// HEAD at position (72, 135)
	result = DrawEquippedItem(DEF_EQUIPPOS_HEAD, sX + 72, sY + 135, msX, msY, cEquipPoiStatus, false);
	if (result != -1) cCollison = result;

	// Angel staff special case
	if (cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND] != -1)
	{
		int itemIdx = cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND];
		sSprH = m_pGame->m_pItemList[itemIdx]->m_sSprite;
		sFrame = m_pGame->m_pItemList[itemIdx]->m_sSpriteFrame;
		cItemColor = m_pGame->m_pItemList[itemIdx]->m_cItemColor;
		if (sSprH == 8) // Angel staff
		{
			if (!m_pGame->m_bIsItemDisabled[itemIdx])
				m_pGame->m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteFast(sX + 45, sY + 143, sFrame, m_pGame->m_dwCurTime);
			else
				m_pGame->m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite(sX + 45, sY + 143, sFrame, m_pGame->m_dwCurTime);
		}
	}
}

void DialogBox_Character::DrawFemaleCharacter(short sX, short sY, short msX, short msY,
	const char* cEquipPoiStatus, char& cCollison)
{
	int iR, iG, iB;
	short sSprH, sFrame;
	char cItemColor;
	int iSkirtDraw = 0;

	// Base body (female uses +40 offset from male sprites)
	m_pGame->m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 40]->PutSpriteFast(sX + 171, sY + 290, m_pGame->m_sPlayerType - 4, m_pGame->m_dwCurTime);

	// Hair (if no helmet) - female hair is at +18+40 = +58
	if (cEquipPoiStatus[DEF_EQUIPPOS_HEAD] == -1)
	{
		m_pGame->_GetHairColorRGB(((m_pGame->m_sPlayerAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
		m_pGame->m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 18 + 40]->PutSpriteRGB(sX + 171, sY + 290, (m_pGame->m_sPlayerAppr1 & 0x0F00) >> 8, iR, iG, iB, m_pGame->m_dwCurTime);
	}

	// Underwear - female underwear is at +19+40 = +59
	m_pGame->m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 19 + 40]->PutSpriteFast(sX + 171, sY + 290, (m_pGame->m_sPlayerAppr1 & 0x000F), m_pGame->m_dwCurTime);

	// Check for skirt in pants slot (sprite 12, frame 0 = skirt)
	if (cEquipPoiStatus[DEF_EQUIPPOS_PANTS] != -1)
	{
		sSprH = m_pGame->m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSprite;
		sFrame = m_pGame->m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSpriteFrame;
		if ((sSprH == 12) && (sFrame == 0)) iSkirtDraw = 1;
	}

	// Back item - female position is different (45, 143)
	char result;
	result = DrawEquippedItem(DEF_EQUIPPOS_BACK, sX + 45, sY + 143, msX, msY, cEquipPoiStatus, false, 40);
	if (result != -1) cCollison = result;

	// If wearing skirt, draw boots first (before pants)
	if ((cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] != -1) && (iSkirtDraw == 1))
	{
		result = DrawEquippedItem(DEF_EQUIPPOS_BOOTS, sX + 171, sY + 290, msX, msY, cEquipPoiStatus, false, 40);
		if (result != -1) cCollison = result;
	}

	// Pants
	result = DrawEquippedItem(DEF_EQUIPPOS_PANTS, sX + 171, sY + 290, msX, msY, cEquipPoiStatus, false, 40);
	if (result != -1) cCollison = result;

	// Arms
	result = DrawEquippedItem(DEF_EQUIPPOS_ARMS, sX + 171, sY + 290, msX, msY, cEquipPoiStatus, false, 40);
	if (result != -1) cCollison = result;

	// If not wearing skirt, draw boots after arms
	if ((cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] != -1) && (iSkirtDraw == 0))
	{
		result = DrawEquippedItem(DEF_EQUIPPOS_BOOTS, sX + 171, sY + 290, msX, msY, cEquipPoiStatus, false, 40);
		if (result != -1) cCollison = result;
	}

	// Body
	result = DrawEquippedItem(DEF_EQUIPPOS_BODY, sX + 171, sY + 290, msX, msY, cEquipPoiStatus, false, 40);
	if (result != -1) cCollison = result;

	// Fullbody
	result = DrawEquippedItem(DEF_EQUIPPOS_FULLBODY, sX + 171, sY + 290, msX, msY, cEquipPoiStatus, false, 40);
	if (result != -1) cCollison = result;

	// Weapons (use weapon colors) - female positions are different
	result = DrawEquippedItem(DEF_EQUIPPOS_LHAND, sX + 84, sY + 175, msX, msY, cEquipPoiStatus, true, 40);
	if (result != -1) cCollison = result;

	result = DrawEquippedItem(DEF_EQUIPPOS_RHAND, sX + 60, sY + 191, msX, msY, cEquipPoiStatus, true, 40);
	if (result != -1) cCollison = result;

	result = DrawEquippedItem(DEF_EQUIPPOS_TWOHAND, sX + 60, sY + 191, msX, msY, cEquipPoiStatus, true, 40);
	if (result != -1) cCollison = result;

	// Accessories - female positions
	result = DrawEquippedItem(DEF_EQUIPPOS_NECK, sX + 35, sY + 120, msX, msY, cEquipPoiStatus, false, 40);
	if (result != -1) cCollison = result;

	result = DrawEquippedItem(DEF_EQUIPPOS_RFINGER, sX + 32, sY + 193, msX, msY, cEquipPoiStatus, false, 40);
	if (result != -1) cCollison = result;

	result = DrawEquippedItem(DEF_EQUIPPOS_LFINGER, sX + 98, sY + 182, msX, msY, cEquipPoiStatus, false, 40);
	if (result != -1) cCollison = result;

	// HEAD at position (72, 139) with female sprite offset (+40)
	result = DrawEquippedItem(DEF_EQUIPPOS_HEAD, sX + 72, sY + 139, msX, msY, cEquipPoiStatus, false, 40);
	if (result != -1) cCollison = result;

	// Angel staff special case
	if (cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND] != -1)
	{
		int itemIdx = cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND];
		sSprH = m_pGame->m_pItemList[itemIdx]->m_sSprite;
		sFrame = m_pGame->m_pItemList[itemIdx]->m_sSpriteFrame;
		cItemColor = m_pGame->m_pItemList[itemIdx]->m_cItemColor;
		if (sSprH == 8) // Angel staff
		{
			if (!m_pGame->m_bIsItemDisabled[itemIdx])
				m_pGame->m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteFast(sX + 45, sY + 143, sFrame, m_pGame->m_dwCurTime);
			else
				m_pGame->m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite(sX + 45, sY + 143, sFrame, m_pGame->m_dwCurTime);
		}
	}
}

bool DialogBox_Character::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;

	// Quest button
	if ((msX >= sX + 15) && (msX <= sX + 15 + DEF_BTNSZX) && (msY >= sY + 340) && (msY <= sY + 340 + DEF_BTNSZY)) {
		EnableDialogBox(DialogBoxId::Quest, 1, 0, 0);
		DisableThisDialog();
		PlaySoundEffect('E', 14, 5);
		return true;
	}
	// Party button
	if ((msX >= sX + 98) && (msX <= sX + 98 + DEF_BTNSZX) && (msY >= sY + 340) && (msY <= sY + 340 + DEF_BTNSZY)) {
		EnableDialogBox(DialogBoxId::Party, 0, 0, 0);
		DisableThisDialog();
		PlaySoundEffect('E', 14, 5);
		return true;
	}
	// LevelUp button
	if ((msX >= sX + 180) && (msX <= sX + 180 + DEF_BTNSZX) && (msY >= sY + 340) && (msY <= sY + 340 + DEF_BTNSZY)) {
		EnableDialogBox(DialogBoxId::LevelUpSetting, 0, 0, 0);
		DisableThisDialog();
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	return false;
}
