#pragma once

#include "ChatCommandManager.h"

// /profile - Toggle performance profiling display
class CmdProfile : public ChatCommand
{
public:
	const char* GetName() const override { return "profile"; }
	bool Execute(CGame* pGame, const char* pArgs) override;
};
