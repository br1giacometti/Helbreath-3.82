#pragma once

#include "ChatCommandManager.h"

// /whon - Enable whispers
class CmdWhisperOn : public ChatCommand
{
public:
	const char* GetName() const override { return "whisperon"; }
	bool Execute(CGame* pGame, const char* pArgs) override;
};

// /whoff - Disable whispers
class CmdWhisperOff : public ChatCommand
{
public:
	const char* GetName() const override { return "whisperoff"; }
	bool Execute(CGame* pGame, const char* pArgs) override;
};
