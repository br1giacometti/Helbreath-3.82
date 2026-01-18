#pragma once

#include "ChatCommandManager.h"

// /showframe - Toggle FPS display
class CmdShowFrame : public ChatCommand
{
public:
	const char* GetName() const override { return "showfps"; }
	bool Execute(CGame* pGame, const char* pArgs) override;
};
