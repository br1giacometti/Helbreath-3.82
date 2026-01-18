#pragma once
#include "IDialogBox.h"

class DialogBox_SellOrRepair : public IDialogBox
{
public:
	DialogBox_SellOrRepair(CGame* pGame);
	~DialogBox_SellOrRepair() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;
};
