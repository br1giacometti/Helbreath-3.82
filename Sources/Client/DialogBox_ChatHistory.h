#pragma once
#include "IDialogBox.h"

class DialogBox_ChatHistory : public IDialogBox
{
public:
	DialogBox_ChatHistory(CGame* pGame);
	~DialogBox_ChatHistory() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

private:
	void DrawScrollBar(short sX, short sY);
	void DrawChatMessages(short sX, short sY);
	void HandleScrollInput(short sX, short sY, short msX, short msY, short msZ, char cLB);
};
