#pragma once
#include "IDialogBox.h"

class DialogBox_ItemUpgrade : public IDialogBox
{
public:
    DialogBox_ItemUpgrade(CGame* pGame);
    ~DialogBox_ItemUpgrade() override = default;

    void OnDraw(short msX, short msY, short msZ, char cLB) override;
    bool OnClick(short msX, short msY) override;

private:
    // Draw helpers for each mode
    void DrawMode1_GizonUpgrade(int sX, int sY, int msX, int msY);
    void DrawMode2_InProgress(int sX, int sY);
    void DrawMode3_Success(int sX, int sY, int msX, int msY);
    void DrawMode4_Failed(int sX, int sY, int msX, int msY);
    void DrawMode5_SelectUpgradeType(int sX, int sY, int msX, int msY);
    void DrawMode6_StoneUpgrade(int sX, int sY, int msX, int msY);
    void DrawMode7_ItemLost(int sX, int sY, int msX, int msY);
    void DrawMode8_MaxUpgrade(int sX, int sY, int msX, int msY);
    void DrawMode9_CannotUpgrade(int sX, int sY, int msX, int msY);
    void DrawMode10_NoPoints(int sX, int sY, int msX, int msY);

    // Shared drawing helper
    void DrawItemPreview(int sX, int sY, int iItemIndex);
    int CalculateUpgradeCost(int iItemIndex);
};
