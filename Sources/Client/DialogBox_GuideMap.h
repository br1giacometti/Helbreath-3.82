#pragma once
#include "IDialogBox.h"

class DialogBox_GuideMap : public IDialogBox
{
public:
	DialogBox_GuideMap(CGame* pGame);
	~DialogBox_GuideMap() override = default;

	void OnUpdate() override;
	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

private:
	void DrawBorder(short sX, short sY);
	void DrawZoomedMap(short sX, short sY);
	void DrawFullMap(short sX, short sY);
	void DrawLocationTooltip(short msX, short msY, short sX, short sY);
};
