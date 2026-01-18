#pragma once
#include "IDialogBox.h"

class DialogBox_SellList : public IDialogBox
{
public:
	DialogBox_SellList(CGame* pGame);
	~DialogBox_SellList() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

private:
	void DrawItemList(short sX, short sY, short szX, short msX, short msY, int& iEmptyCount);
	void DrawEmptyListMessage(short sX, short sY, short szX);
	void DrawButtons(short sX, short sY, short msX, short msY, bool bHasItems);
};
