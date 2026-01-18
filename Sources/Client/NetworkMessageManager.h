#pragma once
#include <cstdint>

class CGame;

// NetworkMessageManager: Lightweight orchestrator for network message handling
class NetworkMessageManager
{
public:
	explicit NetworkMessageManager(CGame* pGame);
	~NetworkMessageManager() = default;

	// Main entry point: processes incoming network messages
	bool ProcessMessage(uint32_t dwMsgID, char* pData, uint32_t dwMsgSize);

private:
	CGame* m_pGame;
};
