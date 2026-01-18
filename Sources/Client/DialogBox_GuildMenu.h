#pragma once
#include "IDialogBox.h"

class DialogBox_GuildMenu : public IDialogBox
{
public:
	DialogBox_GuildMenu(CGame* pGame);
	~DialogBox_GuildMenu() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

private:
	void DrawMode0_MainMenu(short sX, short sY, short szX, short msX, short msY);
	void DrawMode1_CreateGuild(short sX, short sY, short szX, short msX, short msY);
	void DrawMode5_DisbandConfirm(short sX, short sY, short szX, short msX, short msY);
	void DrawMode9_AdmissionTicket(short sX, short sY, short szX, short msX, short msY);
	void DrawMode11_SecessionTicket(short sX, short sY, short szX, short msX, short msY);
	void DrawMode13_FightzoneSelect(short sX, short sY, short szX, short msX, short msY);
	void DrawMode20_ConfirmCancel(short sX, short sY, short szX, short msX, short msY);
	void DrawSimpleMessage(short sX, short sY, short szX, short msX, short msY, int mode);

	bool OnClickMode0(short sX, short sY, short msX, short msY);
	bool OnClickMode1(short sX, short sY, short msX, short msY);
	bool OnClickMode5(short sX, short sY, short msX, short msY);
	bool OnClickMode9(short sX, short sY, short msX, short msY);
	bool OnClickMode11(short sX, short sY, short msX, short msY);
	bool OnClickMode13(short sX, short sY, short msX, short msY);
	bool OnClickModeOkOnly(short sX, short sY, short msX, short msY);

	static constexpr int ADJX = -13;
	static constexpr int ADJY = 30;
};
