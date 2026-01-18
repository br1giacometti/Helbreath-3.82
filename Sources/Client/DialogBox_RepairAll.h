#pragma once
#include "IDialogBox.h"

class DialogBox_RepairAll : public IDialogBox
{
public:
	DialogBox_RepairAll(CGame* pGame);
	~DialogBox_RepairAll() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;
};
