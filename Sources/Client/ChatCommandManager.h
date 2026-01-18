#pragma once

#include <string>
#include <vector>
#include <memory>

// Forward declaration
class CGame;

// Base class for all chat commands
class ChatCommand
{
public:
	virtual ~ChatCommand() = default;

	// Get the command name (without leading slash)
	virtual const char* GetName() const = 0;

	// Execute the command
	// pGame: pointer to game instance
	// pArgs: arguments after the command (may be nullptr or empty)
	// Returns: true if command was handled
	virtual bool Execute(CGame* pGame, const char* pArgs) = 0;
};

class ChatCommandManager
{
public:
	static ChatCommandManager& Get();

	// Initialize with game pointer and register built-in commands
	void Initialize(CGame* pGame);

	// Register a command (takes ownership)
	void RegisterCommand(std::unique_ptr<ChatCommand> command);

	// Process a chat message, returns true if it was a command
	bool ProcessCommand(const char* pMessage);

private:
	ChatCommandManager() = default;
	~ChatCommandManager() = default;
	ChatCommandManager(const ChatCommandManager&) = delete;
	ChatCommandManager& operator=(const ChatCommandManager&) = delete;

	// Register all built-in commands
	void RegisterBuiltInCommands();

	// Pointer to game instance
	CGame* m_pGame = nullptr;

	// Registered commands
	std::vector<std::unique_ptr<ChatCommand>> m_commands;

	bool m_bInitialized = false;
};
