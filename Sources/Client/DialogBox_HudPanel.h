#pragma once
#include "IDialogBox.h"
#include "DialogBoxIDs.h"

class DialogBox_HudPanel : public IDialogBox
{
public:
	DialogBox_HudPanel(CGame* pGame);
	~DialogBox_HudPanel() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

private:
	// Bar dimensions
	static constexpr int HP_MP_BAR_WIDTH = 101;
	static constexpr int SP_BAR_WIDTH = 167;

	// Bar positions
	static constexpr int HP_BAR_X = 23;
	static constexpr int HP_BAR_Y = 437;
	static constexpr int MP_BAR_Y = 459;
	static constexpr int SP_BAR_X = 147;
	static constexpr int SP_BAR_Y = 434;
	static constexpr int EXP_BAR_Y = 429;

	// HP/MP/SP number positions
	static constexpr int HP_NUM_X = 80;
	static constexpr int HP_NUM_Y = 441;
	static constexpr int MP_NUM_Y = 463;
	static constexpr int SP_NUM_X = 228;
	static constexpr int SP_NUM_Y = 435;

	// Combat mode icon position
	static constexpr int COMBAT_ICON_X = 368;
	static constexpr int COMBAT_ICON_Y = 440;

	// Map message text position
	static constexpr int MAP_MSG_X1 = 140;
	static constexpr int MAP_MSG_X2 = 323;
	static constexpr int MAP_MSG_Y = 456;

	// Button regions (Y is shared)
	static constexpr int BTN_Y1 = 434;
	static constexpr int BTN_Y2 = 475;
	static constexpr int BTN_CRUSADE_X1 = 322;
	static constexpr int BTN_CRUSADE_X2 = 355;
	static constexpr int BTN_COMBAT_X1 = 362;
	static constexpr int BTN_COMBAT_X2 = 404;

	// Toggle button info structure
	struct ToggleButtonInfo {
		int x1, x2;
		int spriteX;
		int spriteFrame;
		const char* tooltip;
		DialogBoxId::Type dialogId;
	};

	static const ToggleButtonInfo TOGGLE_BUTTONS[];
	static constexpr int TOGGLE_BUTTON_COUNT = 6;

	// Level up text position
	static constexpr int LEVELUP_TEXT_X = 32;
	static constexpr int LEVELUP_TEXT_Y = 448;

	// Helper methods
	void DrawGaugeBars();
	void DrawIconButtons(short msX, short msY);
	void DrawStatusIcons(short msX, short msY);
	bool IsInButton(short msX, short msY, int x1, int x2) const;
	void ToggleDialogWithSound(DialogBoxId::Type dialogId);
};
