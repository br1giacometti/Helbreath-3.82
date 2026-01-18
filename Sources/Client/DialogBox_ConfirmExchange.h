#pragma once
#include "IDialogBox.h"

class DialogBox_ConfirmExchange : public IDialogBox
{
public:
	DialogBox_ConfirmExchange(CGame* pGame);
	~DialogBox_ConfirmExchange() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;
};
