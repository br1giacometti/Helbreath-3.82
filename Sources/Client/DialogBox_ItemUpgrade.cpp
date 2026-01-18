#include "DialogBox_ItemUpgrade.h"
#include "Game.h"
#include "lan_eng.h"

DialogBox_ItemUpgrade::DialogBox_ItemUpgrade(CGame* pGame)
	: IDialogBox(DialogBoxId::ItemUpgrade, pGame)
{
	SetDefaultRect(60 + SCREENX, 50 + SCREENY, 258, 339);
}

void DialogBox_ItemUpgrade::OnDraw(short msX, short msY, short msZ, char cLB)
{
    int sX = m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).sX;
    int sY = m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).sY;

    m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);
    m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 5); // Item Upgrade Text

    switch (m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).cMode) {
    case 1:
        DrawMode1_GizonUpgrade(sX, sY, msX, msY);
        break;
    case 2:
        DrawMode2_InProgress(sX, sY);
        break;
    case 3:
        DrawMode3_Success(sX, sY, msX, msY);
        break;
    case 4:
        DrawMode4_Failed(sX, sY, msX, msY);
        break;
    case 5:
        DrawMode5_SelectUpgradeType(sX, sY, msX, msY);
        break;
    case 6:
        DrawMode6_StoneUpgrade(sX, sY, msX, msY);
        break;
    case 7:
        DrawMode7_ItemLost(sX, sY, msX, msY);
        break;
    case 8:
        DrawMode8_MaxUpgrade(sX, sY, msX, msY);
        break;
    case 9:
        DrawMode9_CannotUpgrade(sX, sY, msX, msY);
        break;
    case 10:
        DrawMode10_NoPoints(sX, sY, msX, msY);
        break;
    }
}

int DialogBox_ItemUpgrade::CalculateUpgradeCost(int iItemIndex)
{
    int iValue = (m_pGame->m_pItemList[iItemIndex]->m_dwAttribute & 0xF0000000) >> 28;
    iValue = iValue * (iValue + 6) / 8 + 2;

    // Special handling for Angelic Pendants
    if ((m_pGame->m_pItemList[iItemIndex]->m_cEquipPos >= 11)
        && (m_pGame->m_pItemList[iItemIndex]->m_cItemType == 1))
    {
        if ((memcmp(m_pGame->m_pItemList[iItemIndex]->m_cName, "AngelicPandent(STR)", 19) == 0)
            || (memcmp(m_pGame->m_pItemList[iItemIndex]->m_cName, "AngelicPandent(DEX)", 19) == 0)
            || (memcmp(m_pGame->m_pItemList[iItemIndex]->m_cName, "AngelicPandent(INT)", 19) == 0)
            || (memcmp(m_pGame->m_pItemList[iItemIndex]->m_cName, "AngelicPandent(MAG)", 19) == 0))
        {
            iValue = (m_pGame->m_pItemList[iItemIndex]->m_dwAttribute & 0xF0000000) >> 28;
            switch (iValue) {
            case 0: iValue = 10; break;
            case 1: iValue = 11; break;
            case 2: iValue = 13; break;
            case 3: iValue = 16; break;
            case 4: iValue = 20; break;
            case 5: iValue = 25; break;
            case 6: iValue = 31; break;
            case 7: iValue = 38; break;
            case 8: iValue = 46; break;
            case 9: iValue = 55; break;
            }
        }
    }
    return iValue;
}

void DialogBox_ItemUpgrade::DrawItemPreview(int sX, int sY, int iItemIndex)
{
    uint32_t dwTime = m_pGame->m_dwCurTime;
    char cStr1[120], cStr2[120], cStr3[120];

    char cItemColor = m_pGame->m_pItemList[iItemIndex]->m_cItemColor;
    if ((m_pGame->m_pItemList[iItemIndex]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
        || (m_pGame->m_pItemList[iItemIndex]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
        || (m_pGame->m_pItemList[iItemIndex]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
    {
        m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[iItemIndex]->m_sSprite]->PutSpriteRGB(
            sX + 134, sY + 182,
            m_pGame->m_pItemList[iItemIndex]->m_sSpriteFrame,
            m_pGame->m_wWR[cItemColor] - m_pGame->m_wR[0],
            m_pGame->m_wWG[cItemColor] - m_pGame->m_wG[0],
            m_pGame->m_wWB[cItemColor] - m_pGame->m_wB[0], dwTime);
    }
    else
    {
        m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[iItemIndex]->m_sSprite]->PutSpriteRGB(
            sX + 134, sY + 182,
            m_pGame->m_pItemList[iItemIndex]->m_sSpriteFrame,
            m_pGame->m_wR[cItemColor] - m_pGame->m_wR[0],
            m_pGame->m_wG[cItemColor] - m_pGame->m_wG[0],
            m_pGame->m_wB[cItemColor] - m_pGame->m_wB[0], dwTime);
    }

    std::memset(cStr1, 0, sizeof(cStr1));
    std::memset(cStr2, 0, sizeof(cStr2));
    std::memset(cStr3, 0, sizeof(cStr3));
    m_pGame->GetItemName(m_pGame->m_pItemList[iItemIndex], cStr1, cStr2, cStr3);
    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 230 + 20, cStr1);
    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 245 + 20, cStr2);
    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 260 + 20, cStr3);
}

void DialogBox_ItemUpgrade::DrawMode1_GizonUpgrade(int sX, int sY, int msX, int msY)
{
    uint32_t dwTime = m_pGame->m_dwCurTime;
    int iItemIndex = m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).sV1;
    char cTxt[256];

    m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 20 + 30, DRAW_DIALOGBOX_ITEMUPGRADE1);
    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 20 + 45, DRAW_DIALOGBOX_ITEMUPGRADE2);
    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 20 + 60, DRAW_DIALOGBOX_ITEMUPGRADE3);
    m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);

    wsprintf(cTxt, DRAW_DIALOGBOX_ITEMUPGRADE11, m_pGame->m_iGizonItemUpgradeLeft);
    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 100, cTxt);

    if (iItemIndex != -1)
    {
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
        int iValue = CalculateUpgradeCost(iItemIndex);

        wsprintf(cTxt, DRAW_DIALOGBOX_ITEMUPGRADE12, iValue);
        if (m_pGame->m_iGizonItemUpgradeLeft < iValue)
            m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 115, cTxt, 195, 25, 25);
        else
            m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 115, cTxt);

        DrawItemPreview(sX, sY, iItemIndex);

        if (m_pGame->m_iGizonItemUpgradeLeft < iValue)
            m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);
        else
        {
            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 47);
            else
                m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);
        }
    }
    else
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);

    // Cancel button
    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
    else
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
}

void DialogBox_ItemUpgrade::DrawMode2_InProgress(int sX, int sY)
{
    uint32_t dwTime = m_pGame->m_dwCurTime;
    int iItemIndex = m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).sV1;

    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 55 + 30 + 282 - 117 - 170, DRAW_DIALOGBOX_ITEMUPGRADE5);
    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 55 + 45 + 282 - 117 - 170, DRAW_DIALOGBOX_ITEMUPGRADE6);

    if (iItemIndex != -1)
    {
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
        char cItemColor = m_pGame->m_pItemList[iItemIndex]->m_cItemColor;

        if ((m_pGame->m_pItemList[iItemIndex]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
            || (m_pGame->m_pItemList[iItemIndex]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
            || (m_pGame->m_pItemList[iItemIndex]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
        {
            m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[iItemIndex]->m_sSprite]->PutSpriteRGB(
                sX + 134, sY + 182,
                m_pGame->m_pItemList[iItemIndex]->m_sSpriteFrame,
                m_pGame->m_wWR[cItemColor] - m_pGame->m_wR[0],
                m_pGame->m_wWG[cItemColor] - m_pGame->m_wG[0],
                m_pGame->m_wWB[cItemColor] - m_pGame->m_wB[0], dwTime);
        }
        else
        {
            m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[iItemIndex]->m_sSprite]->PutSpriteRGB(
                sX + 134, sY + 182,
                m_pGame->m_pItemList[iItemIndex]->m_sSpriteFrame,
                m_pGame->m_wR[cItemColor] - m_pGame->m_wR[0],
                m_pGame->m_wG[cItemColor] - m_pGame->m_wG[0],
                m_pGame->m_wB[cItemColor] - m_pGame->m_wB[0], dwTime);
        }

        // Flickering effect
        if ((rand() % 5) == 0)
            m_pGame->m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pGame->m_pItemList[iItemIndex]->m_sSprite]->PutTransSprite25(
                sX + 134, sY + 182,
                m_pGame->m_pItemList[iItemIndex]->m_sSpriteFrame, dwTime);

        char cStr1[120], cStr2[120], cStr3[120];
        std::memset(cStr1, 0, sizeof(cStr1));
        std::memset(cStr2, 0, sizeof(cStr2));
        std::memset(cStr3, 0, sizeof(cStr3));
        m_pGame->GetItemName(m_pGame->m_pItemList[iItemIndex], cStr1, cStr2, cStr3);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 230 + 20, cStr1);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 245 + 20, cStr2);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 260 + 20, cStr3);
    }

    // Send upgrade command after 4 seconds
    if (((dwTime - m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).dwV1) / 1000 > 4)
        && (m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).dwV1 != 0))
    {
        m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).dwV1 = 0;
        m_pGame->bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_UPGRADEITEM, 0, iItemIndex, 0, 0, 0);
    }
}

void DialogBox_ItemUpgrade::DrawMode3_Success(int sX, int sY, int msX, int msY)
{
    int iItemIndex = m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).sV1;

    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 55 + 30 + 282 - 117 - 170, DRAW_DIALOGBOX_ITEMUPGRADE7);
    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 55 + 45 + 282 - 117 - 170, DRAW_DIALOGBOX_ITEMUPGRADE8);

    if (iItemIndex != -1)
    {
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
        DrawItemPreview(sX, sY, iItemIndex);
    }

    // OK button
    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
    else
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

void DialogBox_ItemUpgrade::DrawMode4_Failed(int sX, int sY, int msX, int msY)
{
    int iItemIndex = m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).sV1;

    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 55 + 30 + 282 - 117 - 170, DRAW_DIALOGBOX_ITEMUPGRADE9);

    // Check if item was destroyed
    if ((iItemIndex != -1) && (m_pGame->m_pItemList[iItemIndex] == 0))
    {
        m_pGame->PlaySound('E', 24, 0, 0);
        m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).cMode = 7;
        return;
    }

    if (iItemIndex != -1)
    {
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
        DrawItemPreview(sX, sY, iItemIndex);
    }

    // OK button
    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
    else
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

void DialogBox_ItemUpgrade::DrawMode5_SelectUpgradeType(int sX, int sY, int msX, int msY)
{
    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 20 + 45, DRAW_DIALOGBOX_ITEMUPGRADE13);

    // Normal item upgrade option
    if ((msX > sX + 24) && (msX < sX + 248) && (msY > sY + 100) && (msY < sY + 115))
    {
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 100, DRAW_DIALOGBOX_ITEMUPGRADE14, 255, 255, 255);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 150, DRAW_DIALOGBOX_ITEMUPGRADE16);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 165, DRAW_DIALOGBOX_ITEMUPGRADE17);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 180, DRAW_DIALOGBOX_ITEMUPGRADE18);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 195, DRAW_DIALOGBOX_ITEMUPGRADE19);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 210, DRAW_DIALOGBOX_ITEMUPGRADE20);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 225, DRAW_DIALOGBOX_ITEMUPGRADE21);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 255, DRAW_DIALOGBOX_ITEMUPGRADE26);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 270, DRAW_DIALOGBOX_ITEMUPGRADE27);
    }
    else
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 100, DRAW_DIALOGBOX_ITEMUPGRADE14, 4, 0, 50);

    // Majestic item upgrade option
    if ((msX > sX + 24) && (msX < sX + 248) && (msY > sY + 120) && (msY < sY + 135))
    {
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 120, DRAW_DIALOGBOX_ITEMUPGRADE15, 255, 255, 255);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 150, DRAW_DIALOGBOX_ITEMUPGRADE22);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 165, DRAW_DIALOGBOX_ITEMUPGRADE23);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 180, DRAW_DIALOGBOX_ITEMUPGRADE24);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 195, DRAW_DIALOGBOX_ITEMUPGRADE25);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 225, DRAW_DIALOGBOX_ITEMUPGRADE28);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 240, DRAW_DIALOGBOX_ITEMUPGRADE29);
    }
    else
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 120, DRAW_DIALOGBOX_ITEMUPGRADE15, 4, 0, 50);

    // Cancel button
    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
    else
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
}

void DialogBox_ItemUpgrade::DrawMode6_StoneUpgrade(int sX, int sY, int msX, int msY)
{
    int iItemIndex = m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).sV1;
    int iSoX = m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).sV2;
    int iSoM = m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).sV3;
    char cTxt[256];

    m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 20 + 30, DRAW_DIALOGBOX_ITEMUPGRADE31);
    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 20 + 45, DRAW_DIALOGBOX_ITEMUPGRADE32);
    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 20 + 60, DRAW_DIALOGBOX_ITEMUPGRADE33);

    if (iSoX == 0)
    {
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 20 + 80, DRAW_DIALOGBOX_ITEMUPGRADE41, 195, 25, 25);
    }
    else
    {
        wsprintf(cTxt, DRAW_DIALOGBOX_ITEMUPGRADE34, iSoX);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 20 + 80, cTxt);
    }

    if (iSoM == 0)
    {
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 20 + 95, DRAW_DIALOGBOX_ITEMUPGRADE42, 195, 25, 25);
    }
    else
    {
        wsprintf(cTxt, DRAW_DIALOGBOX_ITEMUPGRADE35, iSoM);
        m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 20 + 95, cTxt);
    }

    m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);

    if (iItemIndex != -1)
    {
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
        DrawItemPreview(sX, sY, iItemIndex);

        if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 47);
        else
            m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);
    }

    // Cancel button
    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
    else
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
}

void DialogBox_ItemUpgrade::DrawMode7_ItemLost(int sX, int sY, int msX, int msY)
{
    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 20 + 130, DRAW_DIALOGBOX_ITEMUPGRADE36);
    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 20 + 145, DRAW_DIALOGBOX_ITEMUPGRADE37);

    // OK button
    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
    else
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

void DialogBox_ItemUpgrade::DrawMode8_MaxUpgrade(int sX, int sY, int msX, int msY)
{
    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 20 + 130, DRAW_DIALOGBOX_ITEMUPGRADE38);

    // OK button
    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
    else
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

void DialogBox_ItemUpgrade::DrawMode9_CannotUpgrade(int sX, int sY, int msX, int msY)
{
    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 20 + 130, DRAW_DIALOGBOX_ITEMUPGRADE39);

    // OK button
    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
    else
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

void DialogBox_ItemUpgrade::DrawMode10_NoPoints(int sX, int sY, int msX, int msY)
{
    m_pGame->PutAlignedString(sX + 24, sX + 248, sY + 20 + 130, DRAW_DIALOGBOX_ITEMUPGRADE40);

    // OK button
    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
    else
        m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

bool DialogBox_ItemUpgrade::OnClick(short msX, short msY)
{
    short sX = m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).sX;
    short sY = m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).sY;
    int iItemIndex = m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).sV1;

    switch (m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).cMode) {
    case 1: // Gizon upgrade
        if ((iItemIndex != -1) && (msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX)
            && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
        {
            int iValue = (m_pGame->m_pItemList[iItemIndex]->m_dwAttribute & 0xF0000000) >> 28;
            iValue = iValue * (iValue + 6) / 8 + 2;
            if (m_pGame->m_iGizonItemUpgradeLeft < iValue) break;

            m_pGame->PlaySound('E', 14, 5);
            m_pGame->PlaySound('E', 44, 0);
            m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).cMode = 2;
            m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).dwV1 = m_pGame->m_dwCurTime;
            return true;
        }
        if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX)
            && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
        {
            m_pGame->PlaySound('E', 14, 5);
            m_pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::ItemUpgrade);
            return true;
        }
        break;

    case 3:  // Success
    case 4:  // Failed
    case 7:  // Item lost
    case 8:  // Max upgrade
    case 9:  // Cannot upgrade
    case 10: // No points
    case 12: // Need stone
        if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX)
            && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
        {
            m_pGame->PlaySound('E', 14, 5);
            m_pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::ItemUpgrade);
            return true;
        }
        break;

    case 5: // Main menu - select upgrade type
        // Normal item upgrade (Stone)
        if ((msX > sX + 24) && (msX < sX + 248) && (msY > sY + 100) && (msY < sY + 115))
        {
            m_pGame->PlaySound('E', 14, 5);
            int iSoX = 0, iSoM = 0;
            for (int i = 0; i < DEF_MAXITEMS; i++)
                if (m_pGame->m_pItemList[i] != 0)
                {
                    if ((m_pGame->m_pItemList[i]->m_sSprite == 6) && (m_pGame->m_pItemList[i]->m_sSpriteFrame == 128)) iSoX++;
                    if ((m_pGame->m_pItemList[i]->m_sSprite == 6) && (m_pGame->m_pItemList[i]->m_sSpriteFrame == 129)) iSoM++;
                }

            if ((iSoX > 0) || (iSoM > 0))
            {
                m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).cMode = 6;
                m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).sV2 = iSoX;
                m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).sV3 = iSoM;
            }
            else
                m_pGame->AddEventList(DRAW_DIALOGBOX_ITEMUPGRADE30, 10);
            return true;
        }
        // Majestic item upgrade (Gizon)
        if ((msX > sX + 24) && (msX < sX + 248) && (msY > sY + 120) && (msY < sY + 135))
        {
            m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).cMode = 1;
            m_pGame->PlaySound('E', 14, 5);
            return true;
        }
        // Cancel
        if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX)
            && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
        {
            m_pGame->PlaySound('E', 14, 5);
            m_pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::ItemUpgrade);
            return true;
        }
        break;

    case 6: // Stone upgrade
        if ((iItemIndex != -1) && (msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX)
            && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
        {
            m_pGame->PlaySound('E', 14, 5);
            m_pGame->PlaySound('E', 44, 0);
            m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).cMode = 2;
            m_pGame->m_dialogBoxManager.Info(DialogBoxId::ItemUpgrade).dwV1 = m_pGame->m_dwCurTime;
            return true;
        }
        if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX)
            && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
        {
            m_pGame->PlaySound('E', 14, 5);
            m_pGame->m_dialogBoxManager.DisableDialogBox(DialogBoxId::ItemUpgrade);
            return true;
        }
        break;
    }

    return false;
}
