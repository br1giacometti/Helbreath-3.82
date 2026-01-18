#pragma once
#include "IDialogBox.h"

class DialogBox_Constructor : public IDialogBox
{
public:
	DialogBox_Constructor(CGame* pGame);
	~DialogBox_Constructor() override = default;

	void OnUpdate() override;
	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;
};
