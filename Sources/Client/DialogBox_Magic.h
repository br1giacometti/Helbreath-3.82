#pragma once
#include "IDialogBox.h"

class DialogBox_Magic : public IDialogBox
{
public:
	DialogBox_Magic(CGame* pGame);
	~DialogBox_Magic() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;
};
