#pragma once
#include "IDialogBox.h"

class DialogBox_Soldier : public IDialogBox
{
public:
	DialogBox_Soldier(CGame* pGame);
	~DialogBox_Soldier() override = default;

	void OnUpdate() override;
	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;
};
