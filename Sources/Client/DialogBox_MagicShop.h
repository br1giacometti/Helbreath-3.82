#pragma once

#include "IDialogBox.h"

class DialogBox_MagicShop : public IDialogBox
{
public:
	DialogBox_MagicShop(CGame* pGame);
	~DialogBox_MagicShop() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

private:
	void DrawSpellList(short sX, short sY, short msX, short msY);
	void DrawPageIndicator(short sX, short sY);
	bool HandleSpellClick(short sX, short sY, short msX, short msY);
	void HandlePageClick(short sX, short sY, short msX, short msY);
};
