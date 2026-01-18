#pragma once

#include "ChatCommandManager.h"

// /tooff <name> - Add player to ignore list
class CmdIgnoreOn : public ChatCommand
{
public:
	const char* GetName() const override { return "ignore"; }
	bool Execute(CGame* pGame, const char* pArgs) override;
};

// /toon <name> - Remove player from ignore list
class CmdIgnoreOff : public ChatCommand
{
public:
	const char* GetName() const override { return "ignoreoff"; }
	bool Execute(CGame* pGame, const char* pArgs) override;
};
