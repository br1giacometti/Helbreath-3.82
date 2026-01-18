#pragma once
#include "IDialogBox.h"

class DialogBox_Manufacture : public IDialogBox
{
public:
	DialogBox_Manufacture(CGame* pGame);
	~DialogBox_Manufacture() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

private:
	void DrawAlchemyWaiting(short sX, short sY, short msX, short msY);
	void DrawAlchemyCreating(short sX, short sY);
	void DrawManufactureList(short sX, short sY, short msX, short msY, short msZ, char cLB);
	void DrawManufactureWaiting(short sX, short sY, short msX, short msY);
	void DrawManufactureInProgress(short sX, short sY);
	void DrawManufactureDone(short sX, short sY, short msX, short msY);
	void DrawCraftingWaiting(short sX, short sY, short msX, short msY);
	void DrawCraftingInProgress(short sX, short sY);
	void ResetItemSlots();
};
