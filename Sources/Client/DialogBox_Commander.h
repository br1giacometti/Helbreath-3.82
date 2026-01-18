#pragma once
#include "IDialogBox.h"

class DialogBox_Commander : public IDialogBox
{
public:
	DialogBox_Commander(CGame* pGame);
	~DialogBox_Commander() override = default;

	void OnUpdate() override;
	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;
};
