#pragma once
#include "IDialogBox.h"

class DialogBox_Exchange : public IDialogBox
{
public:
	DialogBox_Exchange(CGame* pGame);
	~DialogBox_Exchange() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

private:
	void DrawItems(short sX, short sY, short msX, short msY, int iStartIndex, int iEndIndex);
	void DrawItemInfo(short sX, short sY, short szX, short msX, short msY, int iItemIndex, short sXadd);
};
