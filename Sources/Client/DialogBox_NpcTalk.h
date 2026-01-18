#pragma once
#include "IDialogBox.h"

class DialogBox_NpcTalk : public IDialogBox
{
public:
	DialogBox_NpcTalk(CGame* pGame);
	~DialogBox_NpcTalk() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

private:
	int GetTotalLines() const;
	void DrawButtons(short sX, short sY, short msX, short msY);
	void DrawTextContent(short sX, short sY);
	void DrawScrollBar(short sX, short sY, int iTotalLines);
	void HandleScrollBarDrag(short sX, short sY, short msX, short msY, int iTotalLines, char cLB);
};
