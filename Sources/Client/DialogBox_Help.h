#pragma once
#include "IDialogBox.h"

class DialogBox_Help : public IDialogBox
{
public:
	DialogBox_Help(CGame* pGame);
	~DialogBox_Help() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

private:
	bool IsMouseOverItem(short msX, short msY, short sX, short sY, int iItem);
	void DrawHelpItem(short sX, short szX, short sY, int iItem, const char* pText, bool bHighlight);
};
