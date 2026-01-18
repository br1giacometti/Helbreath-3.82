#pragma once
#include "IDialogBox.h"

class DialogBox_Quest : public IDialogBox
{
public:
	DialogBox_Quest(CGame* pGame);
	~DialogBox_Quest() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;
};
