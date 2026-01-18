#include "CmdWhisper.h"
#include "Game.h"
#include "LAN_ENG.H"

bool CmdWhisperOn::Execute(CGame* pGame, const char* pArgs)
{
	(void)pArgs;
	pGame->m_bWhisper = true;
	pGame->AddEventList(BCHECK_LOCAL_CHAT_COMMAND6, 10);
	return true;
}

bool CmdWhisperOff::Execute(CGame* pGame, const char* pArgs)
{
	(void)pArgs;
	pGame->m_bWhisper = false;
	pGame->AddEventList(BCHECK_LOCAL_CHAT_COMMAND7, 10);
	return true;
}
