#include "CmdShowPing.h"
#include "ConfigManager.h"
#include "Game.h"

bool CmdShowPing::Execute(CGame* pGame, const char* pArgs)
{
	(void)pGame;
	(void)pArgs;
	bool enabled = ConfigManager::Get().IsShowLatencyEnabled();
	ConfigManager::Get().SetShowLatencyEnabled(!enabled);
	return true;
}
