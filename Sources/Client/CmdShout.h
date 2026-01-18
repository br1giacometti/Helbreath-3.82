#pragma once

#include "ChatCommandManager.h"

// /shon - Enable shout/public chat
class CmdShoutOn : public ChatCommand
{
public:
	const char* GetName() const override { return "shouton"; }
	bool Execute(CGame* pGame, const char* pArgs) override;
};

// /shoff - Disable shout/public chat
class CmdShoutOff : public ChatCommand
{
public:
	const char* GetName() const override { return "shoutoff"; }
	bool Execute(CGame* pGame, const char* pArgs) override;
};
