#pragma once
#include "IDialogBox.h"

class DialogBox_GuildOperation : public IDialogBox
{
public:
	DialogBox_GuildOperation(CGame* pGame);
	~DialogBox_GuildOperation() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

private:
	void DrawJoinRequest(short sX, short sY, short msX, short msY);
	void DrawDismissRequest(short sX, short sY, short msX, short msY);
	void DrawInfoMessage(short sX, short sY, short msX, short msY, int mode);
};
