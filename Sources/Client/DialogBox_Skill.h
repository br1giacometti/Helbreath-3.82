#pragma once
#include "IDialogBox.h"

class DialogBox_Skill : public IDialogBox
{
public:
	DialogBox_Skill(CGame* pGame);
	~DialogBox_Skill() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;
};
