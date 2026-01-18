#include "CmdShout.h"
#include "Game.h"
#include "LAN_ENG.H"

bool CmdShoutOn::Execute(CGame* pGame, const char* pArgs)
{
	(void)pArgs;
	pGame->m_bShout = true;
	pGame->AddEventList(BCHECK_LOCAL_CHAT_COMMAND8, 10);
	return true;
}

bool CmdShoutOff::Execute(CGame* pGame, const char* pArgs)
{
	(void)pArgs;
	pGame->m_bShout = false;
	pGame->AddEventList(BCHECK_LOCAL_CHAT_COMMAND9, 10);
	return true;
}
