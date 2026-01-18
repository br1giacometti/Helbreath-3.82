#include "CmdShowFrame.h"
#include "Game.h"
#include "ConfigManager.h"

bool CmdShowFrame::Execute(CGame* pGame, const char* pArgs)
{
	(void)pGame;
	(void)pArgs;
	bool enabled = ConfigManager::Get().IsShowFpsEnabled();
	ConfigManager::Get().SetShowFpsEnabled(!enabled);
	return true;
}
