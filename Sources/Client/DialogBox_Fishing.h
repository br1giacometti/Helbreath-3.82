#pragma once
#include "IDialogBox.h"

class DialogBox_Fishing : public IDialogBox
{
public:
	DialogBox_Fishing(CGame* pGame);
	~DialogBox_Fishing() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;
};
