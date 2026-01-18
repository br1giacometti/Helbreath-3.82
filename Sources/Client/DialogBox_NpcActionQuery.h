#pragma once
#include "IDialogBox.h"

class DialogBox_NpcActionQuery : public IDialogBox
{
public:
	DialogBox_NpcActionQuery(CGame* pGame);
	~DialogBox_NpcActionQuery() override = default;

	void OnDraw(short msX, short msY, short msZ, char cLB) override;
	bool OnClick(short msX, short msY) override;

private:
	void DrawMode0_NpcMenu(short sX, short sY, short msX, short msY);
	void DrawMode1_GiveToPlayer(short sX, short sY, short msX, short msY);
	void DrawMode2_SellToShop(short sX, short sY, short msX, short msY);
	void DrawMode3_DepositToWarehouse(short sX, short sY, short msX, short msY);
	void DrawMode4_TalkToNpcOrUnicorn(short sX, short sY, short msX, short msY);
	void DrawMode5_ShopWithSell(short sX, short sY, short msX, short msY);
	void DrawMode6_Gail(short sX, short sY, short msX, short msY);

	void DrawHighlightedText(short sX, short sY, const char* text, short msX, short msY, short hitX1, short hitX2, short hitY1, short hitY2);
};
