#pragma once

#include "ChatCommandManager.h"

// /weather <type> - Change weather for debugging
// Legacy values: 0=Clear, 1-3=Rain, 4-6=Snow, 7-9=Storm
class CmdWeather : public ChatCommand
{
public:
	const char* GetName() const override { return "weather"; }
	bool Execute(CGame* pGame, const char* pArgs) override;
};
