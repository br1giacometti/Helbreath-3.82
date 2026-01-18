#pragma once
#include "IDialogBox.h"

class DialogBox_GuildHallMenu : public IDialogBox
{
public:
	DialogBox_GuildHallMenu(CGame* pGame);
	~DialogBox_GuildHallMenu() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;
};
