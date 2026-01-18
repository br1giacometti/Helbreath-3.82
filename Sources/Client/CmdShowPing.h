#pragma once

#include "ChatCommandManager.h"

// /showping - Toggle latency display
class CmdShowPing : public ChatCommand
{
public:
	const char* GetName() const override { return "showping"; }
	bool Execute(CGame* pGame, const char* pArgs) override;
};
