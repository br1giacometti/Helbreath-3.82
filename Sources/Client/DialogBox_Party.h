#pragma once
#include "IDialogBox.h"

class DialogBox_Party : public IDialogBox
{
public:
	DialogBox_Party(CGame* pGame);
	~DialogBox_Party() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;
};
