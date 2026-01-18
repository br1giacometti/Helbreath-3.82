#pragma once
#include "IDialogBox.h"

class DialogBox_Shop : public IDialogBox
{
public:
    DialogBox_Shop(CGame* pGame);
    ~DialogBox_Shop() override = default;

    void OnDraw(short msX, short msY, short msZ, char cLB) override;
    bool OnClick(short msX, short msY) override;

private:
    void DrawItemList(short sX, short sY, short msX, short msY, short msZ, char cLB);
    void DrawItemDetails(short sX, short sY, short msX, short msY, short msZ);
    void DrawWeaponStats(short sX, short sY, int iItemIndex, bool& bFlagRedShown);
    void DrawShieldStats(short sX, short sY, int iItemIndex, bool& bFlagRedShown);
    void DrawArmorStats(short sX, short sY, int iItemIndex, bool& bFlagStatLow, bool& bFlagRedShown);
    void DrawLevelRequirement(short sX, short sY, int iItemIndex, bool& bFlagRedShown);
    void DrawQuantitySelector(short sX, short sY, short msX, short msY, short msZ);
    int CalculateDiscountedPrice(int iItemIndex);

    bool OnClickItemList(short sX, short sY, short msX, short msY);
    bool OnClickItemDetails(short sX, short sY, short msX, short msY);
};
