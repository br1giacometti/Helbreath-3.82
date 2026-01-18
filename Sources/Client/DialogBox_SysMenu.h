#pragma once
#include "IDialogBox.h"

// 4:3 resolution options
struct Resolution {
	int width;
	int height;
};

class DialogBox_SysMenu : public IDialogBox
{
public:
	DialogBox_SysMenu(CGame* pGame);
	~DialogBox_SysMenu() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

	// Resolution management
	static const Resolution s_Resolutions[];
	static const int s_NumResolutions;
	static int GetCurrentResolutionIndex();
	static int GetNearestResolutionIndex(int width, int height);
	static void CycleResolution();
	static void ApplyResolution(int index);

private:
	void DrawDetailLevel(short sX, short sY);
	void DrawSoundSettings(short sX, short sY);
	void DrawChatSettings(short sX, short sY);
	void DrawVolumeSliders(short sX, short sY, short msX, short msY, char cLB);
	void DrawMiscSettings(short sX, short sY);
	void DrawServerName(short sX, short sY);
	void DrawButtons(short sX, short sY, short msX, short msY);
	void DrawDisplayModeButtons(short sX, short sY, short msX, short msY);
	void DrawResolutionButton(short sX, short sY, short msX, short msY);
};
