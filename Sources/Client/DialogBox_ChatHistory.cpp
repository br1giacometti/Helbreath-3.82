#include "DialogBox_ChatHistory.h"
#include "ConfigManager.h"
#include "Game.h"
#include "InputManager.h"

#define DEF_CHAT_VISIBLE_LINES 8
#define DEF_CHAT_SCROLLBAR_HEIGHT 105

DialogBox_ChatHistory::DialogBox_ChatHistory(CGame* pGame)
	: IDialogBox(DialogBoxId::ChatHistory, pGame)
{
	SetDefaultRect(135 + SCREENX, 273 + SCREENY + SCREENY, 364, 162);
}

void DialogBox_ChatHistory::OnDraw(short msX, short msY, short msZ, char cLB)
{
	short sX = m_pGame->m_dialogBoxManager.Info(DialogBoxId::ChatHistory).sX;
	short sY = m_pGame->m_dialogBoxManager.Info(DialogBoxId::ChatHistory).sY;

	const bool dialogTrans = ConfigManager::Get().IsDialogTransparencyEnabled();
	m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 4, false, dialogTrans);
	m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 22, false, dialogTrans);

	HandleScrollInput(sX, sY, msX, msY, msZ, cLB);
	DrawScrollBar(sX, sY);
	DrawChatMessages(sX, sY);
}

void DialogBox_ChatHistory::HandleScrollInput(short sX, short sY, short msX, short msY, short msZ, char cLB)
{
	// Mouse wheel scrolling
	if (m_pGame->m_dialogBoxManager.iGetTopDialogBoxIndex() == DialogBoxId::ChatHistory)
	{
		short sWheelDelta = InputManager::Get().GetWheelDelta();
		if (sWheelDelta != 0)
		{
			m_pGame->m_dialogBoxManager.Info(DialogBoxId::ChatHistory).sView += sWheelDelta / 30;
			InputManager::Get().ClearWheelDelta();
		}
	}

	// Clamp scroll view
	if (m_pGame->m_dialogBoxManager.Info(DialogBoxId::ChatHistory).sView < 0)
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::ChatHistory).sView = 0;
	if (m_pGame->m_dialogBoxManager.Info(DialogBoxId::ChatHistory).sView > DEF_MAXCHATSCROLLMSGS - DEF_CHAT_VISIBLE_LINES)
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::ChatHistory).sView = DEF_MAXCHATSCROLLMSGS - DEF_CHAT_VISIBLE_LINES;

	// Scroll bar dragging
	if ((cLB != 0) && (m_pGame->m_dialogBoxManager.iGetTopDialogBoxIndex() == DialogBoxId::ChatHistory))
	{
		// Drag scrollbar track
		if ((msX >= sX + 336) && (msX <= sX + 361) && (msY >= sY + 28) && (msY <= sY + 140))
		{
			double d1 = (double)(msY - (sY + 28));
			double d2 = ((DEF_MAXCHATSCROLLMSGS - DEF_CHAT_VISIBLE_LINES) * d1) / (double)DEF_CHAT_SCROLLBAR_HEIGHT;
			m_pGame->m_dialogBoxManager.Info(DialogBoxId::ChatHistory).sView = DEF_MAXCHATSCROLLMSGS - DEF_CHAT_VISIBLE_LINES - (int)d2;
		}

		// Scroll to top button
		if ((msX >= sX + 336) && (msX <= sX + 361) && (msY > sY + 18) && (msY < sY + 28))
			m_pGame->m_dialogBoxManager.Info(DialogBoxId::ChatHistory).sView = DEF_MAXCHATSCROLLMSGS - DEF_CHAT_VISIBLE_LINES;

		// Scroll to bottom button
		if ((msX >= sX + 336) && (msX <= sX + 361) && (msY > sY + 140) && (msY < sY + 163))
			m_pGame->m_dialogBoxManager.Info(DialogBoxId::ChatHistory).sView = 0;
	}
	else
	{
		m_pGame->m_dialogBoxManager.Info(DialogBoxId::ChatHistory).bIsScrollSelected = false;
	}
}

void DialogBox_ChatHistory::DrawScrollBar(short sX, short sY)
{
	double d1 = (double)m_pGame->m_dialogBoxManager.Info(DialogBoxId::ChatHistory).sView;
	double d2 = (double)DEF_CHAT_SCROLLBAR_HEIGHT;
	double d3 = (d1 * d2) / (DEF_MAXCHATSCROLLMSGS - DEF_CHAT_VISIBLE_LINES);
	int iPointerLoc = (int)d3;
	iPointerLoc = DEF_CHAT_SCROLLBAR_HEIGHT - iPointerLoc;
	m_pGame->DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX + 346, sY + 33 + iPointerLoc, 7);
}

void DialogBox_ChatHistory::DrawChatMessages(short sX, short sY)
{
	short sView = m_pGame->m_dialogBoxManager.Info(DialogBoxId::ChatHistory).sView;

	for (int i = 0; i < DEF_CHAT_VISIBLE_LINES; i++)
	{
		if (m_pGame->m_pChatScrollList[i + sView] != nullptr)
		{
			int iYPos = sY + 127 - i * 13;
			char* pMsg = m_pGame->m_pChatScrollList[i + sView]->m_pMsg;

			switch (m_pGame->m_pChatScrollList[i + sView]->m_dwTime)
			{
			case 0:  m_pGame->PutString2(sX + 25, iYPos, pMsg, 230, 230, 230); break; // Normal
			case 1:  m_pGame->PutString2(sX + 25, iYPos, pMsg, 130, 200, 130); break; // Green
			case 2:  m_pGame->PutString2(sX + 25, iYPos, pMsg, 255, 130, 130); break; // Red
			case 3:  m_pGame->PutString2(sX + 25, iYPos, pMsg, 130, 130, 255); break; // Blue
			case 4:  m_pGame->PutString2(sX + 25, iYPos, pMsg, 230, 230, 130); break; // Yellow
			case 10: m_pGame->PutString2(sX + 25, iYPos, pMsg, 180, 255, 180); break; // Light green
			case 20: m_pGame->PutString2(sX + 25, iYPos, pMsg, 150, 150, 170); break; // Gray
			}
		}
	}
}

bool DialogBox_ChatHistory::OnClick(short msX, short msY)
{
	// Chat history dialog has no click actions - scrolling is handled in OnDraw
	return false;
}


