#pragma once
#include "IDialogBox.h"

class DialogBox_LevelUpSetting : public IDialogBox
{
public:
	DialogBox_LevelUpSetting(CGame* pGame);
	~DialogBox_LevelUpSetting() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

private:
	void DrawStatRow(short sX, short sY, int iYOffset, const char* pLabel,
	                 int iCurrentStat, int iPendingChange, short msX, short msY,
	                 int iArrowYOffset, bool bCanIncrease, bool bCanDecrease);

	bool HandleStatClick(short msX, short msY, short sX, short sY,
	                     int iYOffset, int& iCurrentStat, uint16_t& cPendingChange);
};
