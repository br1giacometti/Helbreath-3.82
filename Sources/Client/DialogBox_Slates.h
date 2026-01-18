#pragma once
#include "IDialogBox.h"

class DialogBox_Slates : public IDialogBox
{
public:
	DialogBox_Slates(CGame* pGame);
	~DialogBox_Slates() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;
};
