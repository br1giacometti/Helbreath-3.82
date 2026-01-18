#include "ChatCommandManager.h"
#include "CmdShowFrame.h"
#include "CmdShowPing.h"
#include "CmdWhisper.h"
#include "CmdShout.h"
#include "CmdIgnore.h"
#include "CmdWeather.h"
#include "CmdProfile.h"
#include "Game.h"
#include <cstring>

ChatCommandManager& ChatCommandManager::Get()
{
	static ChatCommandManager instance;
	return instance;
}

void ChatCommandManager::Initialize(CGame* pGame)
{
	if (m_bInitialized)
		return;

	m_pGame = pGame;
	RegisterBuiltInCommands();
	m_bInitialized = true;
}

void ChatCommandManager::RegisterCommand(std::unique_ptr<ChatCommand> command)
{
	m_commands.push_back(std::move(command));
}

bool ChatCommandManager::ProcessCommand(const char* pMessage)
{
	if (m_pGame == nullptr || pMessage == nullptr)
		return false;

	if (pMessage[0] != '/')
		return false;

	// Skip the leading slash
	const char* pCommand = pMessage + 1;

	// Find the command that matches
	for (const auto& cmd : m_commands)
	{
		const char* cmdName = cmd->GetName();
		size_t cmdLen = std::strlen(cmdName);

		// Check if message starts with this command
		if (std::strncmp(pCommand, cmdName, cmdLen) == 0)
		{
			// Make sure it's a complete match (followed by space, null, or end)
			char nextChar = pCommand[cmdLen];
			if (nextChar == '\0' || nextChar == ' ' || nextChar == '\t')
			{
				// Get arguments (skip command and any leading whitespace)
				const char* pArgs = pCommand + cmdLen;
				while (*pArgs == ' ' || *pArgs == '\t')
					pArgs++;

				return cmd->Execute(m_pGame, pArgs);
			}
		}
	}

	return false;
}

void ChatCommandManager::RegisterBuiltInCommands()
{
	RegisterCommand(std::make_unique<CmdShowFrame>());
	RegisterCommand(std::make_unique<CmdShowPing>());
	RegisterCommand(std::make_unique<CmdWhisperOn>());
	RegisterCommand(std::make_unique<CmdWhisperOff>());
	RegisterCommand(std::make_unique<CmdShoutOn>());
	RegisterCommand(std::make_unique<CmdShoutOff>());
	RegisterCommand(std::make_unique<CmdIgnoreOn>());
	RegisterCommand(std::make_unique<CmdIgnoreOff>());
	RegisterCommand(std::make_unique<CmdWeather>());
	RegisterCommand(std::make_unique<CmdProfile>());
}
