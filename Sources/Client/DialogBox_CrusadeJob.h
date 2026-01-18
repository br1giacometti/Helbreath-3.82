#pragma once
#include "IDialogBox.h"

class DialogBox_CrusadeJob : public IDialogBox
{
public:
	DialogBox_CrusadeJob(CGame* pGame);
	~DialogBox_CrusadeJob() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

private:
	void DrawModeSelectJob(short sX, short sY, short msX, short msY);
	void DrawModeConfirm(short sX, short sY, short msX, short msY);
};
