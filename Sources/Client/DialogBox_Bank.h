#pragma once
#include "IDialogBox.h"

class DialogBox_Bank : public IDialogBox
{
public:
	DialogBox_Bank(CGame* pGame);
	~DialogBox_Bank() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

private:
	void DrawItemList(short sX, short sY, short szX, short msX, short msY, short msZ, char cLB);
	void DrawItemDetails(short sX, short sY, short szX, int iItemIndex, int yPos);
	void DrawScrollbar(short sX, short sY, int iTotalLines, short msX, short msY, short msZ, char cLB);
};
