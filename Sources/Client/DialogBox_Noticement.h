#pragma once

#include "IDialogBox.h"

class DialogBox_Noticement : public IDialogBox
{
public:
	explicit DialogBox_Noticement(CGame* pGame);

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;
};
