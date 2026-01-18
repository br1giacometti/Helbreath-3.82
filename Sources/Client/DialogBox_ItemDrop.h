#pragma once
#include "IDialogBox.h"

class DialogBox_ItemDrop : public IDialogBox
{
public:
	DialogBox_ItemDrop(CGame* pGame);
	~DialogBox_ItemDrop() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;
};
