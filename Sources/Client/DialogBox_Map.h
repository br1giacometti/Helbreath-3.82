#pragma once
#include "IDialogBox.h"

class DialogBox_Map : public IDialogBox
{
public:
	DialogBox_Map(CGame* pGame);
	~DialogBox_Map() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

	void OnEnable(int cType, int sV1, int sV2, char* pString) override;
};
