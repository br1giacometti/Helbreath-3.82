#pragma once
#include "IDialogBox.h"

class DialogBox_CityHallMenu : public IDialogBox
{
public:
	DialogBox_CityHallMenu(CGame* pGame);
	~DialogBox_CityHallMenu() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

private:
	void DrawMode0_MainMenu(short sX, short sY, short szX, short msX, short msY);
	void DrawMode1_CitizenshipWarning(short sX, short sY, short szX, short msX, short msY);
	void DrawMode2_OfferingCitizenship(short sX, short sY, short szX);
	void DrawMode3_CitizenshipSuccess(short sX, short sY, short szX, short msX, short msY);
	void DrawMode4_CitizenshipFailed(short sX, short sY, short szX, short msX, short msY);
	void DrawMode5_RewardGold(short sX, short sY, short szX, short msX, short msY);
	void DrawMode7_HeroItems(short sX, short sY, short szX, short msX, short msY);
	void DrawMode8_CancelQuest(short sX, short sY, short szX, short msX, short msY);
	void DrawMode9_ChangePlayMode(short sX, short sY, short szX, short msX, short msY);
	void DrawMode10_TeleportMenu(short sX, short sY, short szX, short msX, short msY);
	void DrawMode11_HeroItemConfirm(short sX, short sY, short szX, short msX, short msY);

	bool OnClickMode0(short sX, short sY, short msX, short msY);
	bool OnClickMode1(short sX, short sY, short msX, short msY);
	bool OnClickMode3_4(short sX, short sY, short msX, short msY);
	bool OnClickMode5(short sX, short sY, short msX, short msY);
	bool OnClickMode7(short sX, short sY, short msX, short msY);
	bool OnClickMode8(short sX, short sY, short msX, short msY);
	bool OnClickMode9(short sX, short sY, short msX, short msY);
	bool OnClickMode10(short sX, short sY, short msX, short msY);
	bool OnClickMode11(short sX, short sY, short msX, short msY);
};
