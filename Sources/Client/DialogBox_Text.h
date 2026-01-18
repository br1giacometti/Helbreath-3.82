#pragma once

#include "IDialogBox.h"

class DialogBox_Text : public IDialogBox
{
public:
	DialogBox_Text(CGame* pGame);
	~DialogBox_Text() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

private:
	int GetTotalLines() const;
};
