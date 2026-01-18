#pragma once
#include "IDialogBox.h"

class DialogBox_Character : public IDialogBox
{
public:
	DialogBox_Character(CGame* pGame);
	~DialogBox_Character() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

private:
	// Helper methods
	void DrawStat(int x1, int x2, int y, int baseStat, int angelicBonus);
	char DrawEquippedItem(int equipPos, int drawX, int drawY, short msX, short msY,
		const char* cEquipPoiStatus, bool useWeaponColors, int spriteOffset = 0);
	void DrawHoverButton(int sX, int sY, int btnX, int btnY,
		short msX, short msY, int hoverFrame, int normalFrame);
	void DrawMaleCharacter(short sX, short sY, short msX, short msY,
		const char* cEquipPoiStatus, char& cCollison);
	void DrawFemaleCharacter(short sX, short sY, short msX, short msY,
		const char* cEquipPoiStatus, char& cCollison);
};
