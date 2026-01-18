#include "CmdIgnore.h"
#include "Game.h"
#include "ChatMsg.h"
#include "LAN_ENG.H"
#include <cstring>

bool CmdIgnoreOn::Execute(CGame* pGame, const char* pArgs)
{
	if (pArgs == nullptr || pArgs[0] == '\0')
		return true;

	// Get the player name (first token)
	char cName[12];
	std::memset(cName, 0, sizeof(cName));

	// Copy up to 10 characters or until whitespace
	int i = 0;
	while (pArgs[i] != '\0' && pArgs[i] != ' ' && pArgs[i] != '\t' && i < 10)
	{
		cName[i] = pArgs[i];
		i++;
	}

	if (i == 0)
		return true;

	if (std::strlen(pArgs) > 10)
	{
		pGame->AddEventList(BCHECK_LOCAL_CHAT_COMMAND5, 10);
		return true;
	}

	// Can't ignore yourself
	if (std::memcmp(pGame->m_cPlayerName, cName, 10) == 0)
	{
		pGame->AddEventList(BCHECK_LOCAL_CHAT_COMMAND2, 10);
		return true;
	}

	// Delete existing ignore entry
	if (pGame->m_pExID != nullptr)
		delete pGame->m_pExID;

	char cTxt[120];
	wsprintf(cTxt, BCHECK_LOCAL_CHAT_COMMAND3, cName);
	pGame->AddEventList(cTxt, 10);
	pGame->m_pExID = new class CMsg(0, cName, 0);

	return true;
}

bool CmdIgnoreOff::Execute(CGame* pGame, const char* pArgs)
{
	if (pArgs == nullptr || pArgs[0] == '\0')
		return true;

	// Get the player name (first token)
	char cName[12];
	std::memset(cName, 0, sizeof(cName));

	// Copy up to 10 characters or until whitespace
	int i = 0;
	while (pArgs[i] != '\0' && pArgs[i] != ' ' && pArgs[i] != '\t' && i < 10)
	{
		cName[i] = pArgs[i];
		i++;
	}

	if (i == 0)
		return true;

	if (std::strlen(pArgs) > 10)
	{
		pGame->AddEventList(BCHECK_LOCAL_CHAT_COMMAND5, 10);
		return true;
	}

	if (pGame->m_pExID != nullptr)
	{
		char cTemp[120];
		std::memset(cTemp, 0, sizeof(cTemp));
		std::strcpy(cTemp, pGame->m_pExID->m_pMsg);

		if (std::memcmp(cTemp, cName, 10) == 0)
		{
			char cTxt[120];
			wsprintf(cTxt, BCHECK_LOCAL_CHAT_COMMAND1, cName);
			pGame->AddEventList(cTxt, 10);
			delete pGame->m_pExID;
			pGame->m_pExID = nullptr;
		}
	}

	return true;
}
