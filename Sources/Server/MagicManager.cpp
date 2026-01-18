// MagicManager.cpp: Magic system implementation (Orchestrator)
//
// This file contains only orchestrator logic - delegation to implementation methods.
// Implementation methods are defined in separate .cpp files:
//   - Magic_Player.cpp: HandlePlayerMagicImpl()
//   - Magic_Npc.cpp: HandleNpcMagicImpl()
//
//////////////////////////////////////////////////////////////////////

#include "MagicManager.h"
#include "Game.h"

MagicManager::MagicManager(CGame* pGame)
	: m_pGame(pGame)
{
}

// ============================================================================
// Public API: Orchestrator methods that delegate to private implementation
// ============================================================================

void MagicManager::HandlePlayerMagic(int iClientH, int dX, int dY, short sType, bool bItemEffect, int iV1)
{
	HandlePlayerMagicImpl(iClientH, dX, dY, sType, bItemEffect, iV1);
}

void MagicManager::HandleNpcMagic(int iNpcH, short dX, short dY, short sType)
{
	HandleNpcMagicImpl(iNpcH, dX, dY, sType);
}
