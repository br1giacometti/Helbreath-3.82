#include "DialogBox_Inventory.h"
#include "Game.h"
#include "lan_eng.h"

DialogBox_Inventory::DialogBox_Inventory(CGame* pGame)
	: IDialogBox(DialogBoxId::Inventory, pGame)
{
	SetDefaultRect(380 + SCREENX, 210 + SCREENY, 225, 185);
}

// Helper: Draw a single inventory item with proper coloring and state
void DialogBox_Inventory::DrawInventoryItem(CItem* pItem, int itemIdx, int baseX, int baseY)
{
	char cItemColor = pItem->m_cItemColor;
	bool bDisabled = m_pGame->m_bIsItemDisabled[itemIdx];
	bool bIsWeapon = (pItem->m_cEquipPos == DEF_EQUIPPOS_LHAND) ||
	                 (pItem->m_cEquipPos == DEF_EQUIPPOS_RHAND) ||
	                 (pItem->m_cEquipPos == DEF_EQUIPPOS_TWOHAND);

	int drawX = baseX + ITEM_OFFSET_X + pItem->m_sX;
	int drawY = baseY + ITEM_OFFSET_Y + pItem->m_sY;
	auto* pSprite = m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + pItem->m_sSprite];
	uint32_t dwTime = m_pGame->m_dwCurTime;

	// Select color arrays (weapons use different color set)
	uint16_t* wR = bIsWeapon ? m_pGame->m_wWR : m_pGame->m_wR;
	uint16_t* wG = bIsWeapon ? m_pGame->m_wWG : m_pGame->m_wG;
	uint16_t* wB = bIsWeapon ? m_pGame->m_wWB : m_pGame->m_wB;

	if (cItemColor == 0)
	{
		// No color tint
		if (bDisabled)
			pSprite->PutTransSprite2(drawX, drawY, pItem->m_sSpriteFrame, dwTime);
		else
			pSprite->PutSpriteFast(drawX, drawY, pItem->m_sSpriteFrame, dwTime);
	}
	else
	{
		// Apply color tint
		int r = wR[cItemColor] - m_pGame->m_wR[0];
		int g = wG[cItemColor] - m_pGame->m_wG[0];
		int b = wB[cItemColor] - m_pGame->m_wB[0];

		if (bDisabled)
			pSprite->PutTransSpriteRGB(drawX, drawY, pItem->m_sSpriteFrame, r, g, b, dwTime);
		else
			pSprite->PutSpriteRGB(drawX, drawY, pItem->m_sSpriteFrame, r, g, b, dwTime);
	}

	// Show item count for consumables and arrows
	if ((pItem->m_cItemType == DEF_ITEMTYPE_CONSUME) || (pItem->m_cItemType == DEF_ITEMTYPE_ARROW))
	{
		m_pGame->DisplayCommaNumber_G_cTxt((int)pItem->m_dwCount);
		PutString2(baseX + COUNT_OFFSET_X + pItem->m_sX,
		           baseY + COUNT_OFFSET_Y + pItem->m_sY,
		           m_pGame->G_cTxt, 200, 200, 200);
	}
}

void DialogBox_Inventory::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = Info().sX;
	short sY = Info().sY;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX, sY, 0);

	// Draw all inventory items
	for (int i = 0; i < DEF_MAXITEMS; i++)
	{
		int itemIdx = m_pGame->m_cItemOrder[i];
		if (itemIdx == -1) continue;

		CItem* pItem = m_pGame->m_pItemList[itemIdx];
		if (pItem == nullptr) continue;

		// Skip items that are selected (being dragged) or equipped
		bool bSelected = (m_pGame->m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_ITEM) &&
		                 (m_pGame->m_stMCursor.sSelectedObjectID == itemIdx);
		bool bEquipped = m_pGame->m_bIsItemEquipped[itemIdx];

		if (!bSelected && !bEquipped)
		{
			DrawInventoryItem(pItem, itemIdx, sX, sY);
		}
	}

	// Item Upgrade button hover
	if ((msX >= sX + BTN_UPGRADE_X1) && (msX <= sX + BTN_UPGRADE_X2) &&
	    (msY >= sY + BTN_Y1) && (msY <= sY + BTN_Y2))
	{
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX + BTN_UPGRADE_X1, sY + BTN_Y1, 1);
	}

	// Manufacture button hover
	if ((msX >= sX + BTN_MANUFACTURE_X1) && (msX <= sX + BTN_MANUFACTURE_X2) &&
	    (msY >= sY + BTN_Y1) && (msY <= sY + BTN_Y2))
	{
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX + BTN_MANUFACTURE_X1, sY + BTN_Y1, 2);
	}
}

bool DialogBox_Inventory::OnClick(short msX, short msY)
{
	short sX = Info().sX;
	short sY = Info().sY;

	// Item Upgrade button
	if ((msX >= sX + BTN_UPGRADE_X1) && (msX <= sX + BTN_UPGRADE_X2) &&
	    (msY >= sY + BTN_Y1) && (msY <= sY + BTN_Y2))
	{
		EnableDialogBox(DialogBoxId::ItemUpgrade, 5, 0, 0);
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	// Manufacture button
	if ((msX >= sX + BTN_MANUFACTURE_X1) && (msX <= sX + BTN_MANUFACTURE_X2) &&
	    (msY >= sY + BTN_Y1) && (msY <= sY + BTN_Y2))
	{
		if (m_pGame->m_cSkillMastery[13] == 0)
		{
			AddEventList(DLGBOXCLICK_INVENTORY1, 10);
			AddEventList(DLGBOXCLICK_INVENTORY2, 10);
		}
		else if (m_pGame->m_bSkillUsingStatus)
		{
			AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY5, 10);
			return true;
		}
		else if (m_pGame->_bIsItemOnHand())
		{
			AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY4, 10);
			return true;
		}
		else
		{
			// Look for manufacturing hammer
			for (int i = 0; i < DEF_MAXITEMS; i++)
			{
				CItem* pItem = m_pGame->m_pItemList[i];
				if (pItem != nullptr &&
				    pItem->m_cItemType == DEF_ITEMTYPE_USE_SKILL_ENABLEDIALOGBOX &&
				    pItem->m_sSpriteFrame == 113 &&
				    pItem->m_wCurLifeSpan > 0)
				{
					EnableDialogBox(DialogBoxId::Manufacture, 3, 0, 0);
					AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY12, 10);
					PlaySoundEffect('E', 14, 5);
					return true;
				}
			}
			AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY14, 10);
		}
		PlaySoundEffect('E', 14, 5);
		return true;
	}

	return false;
}
