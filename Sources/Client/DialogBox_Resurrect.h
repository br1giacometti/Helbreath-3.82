#pragma once

#include "IDialogBox.h"

class DialogBox_Resurrect : public IDialogBox
{
public:
	explicit DialogBox_Resurrect(CGame* pGame);

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;
};
