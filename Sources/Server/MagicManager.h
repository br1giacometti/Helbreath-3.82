// MagicManager.h: Magic system orchestrator
//
// Manages all magic-related logic for players and NPCs.
// Extracted from Game.cpp and EntityManager.cpp.
//
//////////////////////////////////////////////////////////////////////

#pragma once

class CGame;

class MagicManager
{
public:
	explicit MagicManager(CGame* pGame);
	~MagicManager() = default;

	// ========================================================================
	// Public API - Entry Points
	// ========================================================================

	/**
	 * Handle player magic casting.
	 * Extracted from CGame::PlayerMagicHandler()
	 *
	 * @param iClientH - Client handle
	 * @param dX, dY - Target coordinates
	 * @param sType - Magic type ID
	 * @param bItemEffect - True if triggered by item (bypasses some checks)
	 * @param iV1 - Additional value (used by some spells)
	 */
	void HandlePlayerMagic(int iClientH, int dX, int dY, short sType, bool bItemEffect = false, int iV1 = 0);

	/**
	 * Handle NPC magic casting.
	 * Extracted from CEntityManager::NpcMagicHandler()
	 *
	 * @param iNpcH - NPC handle
	 * @param dX, dY - Target coordinates
	 * @param sType - Magic type ID
	 */
	void HandleNpcMagic(int iNpcH, short dX, short dY, short sType);

private:
	// ========================================================================
	// Implementation Methods (defined in separate .cpp files)
	// ========================================================================

	// Magic_Player.cpp
	void HandlePlayerMagicImpl(int iClientH, int dX, int dY, short sType, bool bItemEffect, int iV1);

	// Magic_Npc.cpp
	void HandleNpcMagicImpl(int iNpcH, short dX, short dY, short sType);

	// ========================================================================
	// Data Members
	// ========================================================================

	CGame* m_pGame;  // Reference, not owned (like EffectManager pattern)
};
