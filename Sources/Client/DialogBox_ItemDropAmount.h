#pragma once
#include "IDialogBox.h"

class DialogBox_ItemDropAmount : public IDialogBox
{
public:
	DialogBox_ItemDropAmount(CGame* pGame);
	~DialogBox_ItemDropAmount() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;
};
