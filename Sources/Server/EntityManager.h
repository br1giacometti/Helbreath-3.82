// EntityManager.h: interface for the CEntityManager class.
//
// Manages all NPC/entity spawning, deletion, and behavior.
// Extracted from Game.cpp to improve maintainability and fix spawn bugs.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include "CommonTypes.h"

#include "Npc.h"
#include "Map.h"
#include "Game.h"  // For DEF_MAXNPCS

struct DropTable;

class CEntityManager
{
public:
    CEntityManager();
    ~CEntityManager();

    // ========================================================================
    // Core Spawn System
    // ========================================================================

    /**
     * Main spawn generation loop. Called each game tick.
     * Processes all maps and spawn points, creating new NPCs as needed.
     */
    void ProcessSpawns();

    /**
     * Create a new NPC entity.
     *
     * @param pNpcName - Config name (e.g., "Slime", "Orc")
     * @param pName - Unique ID (e.g., "_A0001")
     * @param pMapName - Map to spawn on
     * @param sClass - Movement class
     * @param cSA - Special ability
     * @param cMoveType - Movement behavior
     * @param poX, poY - Spawn position (output)
     * @param pWaypointList - Waypoint array
     * @param pArea - Spawn area bounds
     * @param iSpotMobIndex - Spawn point index (0=random, 1-99=spot)
     * @param cChangeSide - Faction override
     * @param bHideGenMode - Hide if players nearby
     * @param bIsSummoned - Summoned or natural spawn
     * @param bFirmBerserk - Start with berserk
     * @param bIsMaster - Guild war summon
     * @param iGuildGUID - Guild ID
     * @return NPC handle (1-4999) or -1 on failure
     */
    int CreateEntity(
        char* pNpcName, char* pName, char* pMapName,
        short sClass, char cSA, char cMoveType,
        int* poX, int* poY,
        char* pWaypointList, RECT* pArea,
        int iSpotMobIndex, char cChangeSide,
        bool bHideGenMode, bool bIsSummoned,
        bool bFirmBerserk, bool bIsMaster,
        int iGuildGUID
    );

    /**
     * Remove entity from world and free resources.
     * Handles item drops, counter updates, and cleanup.
     *
     * @param iEntityHandle - Entity to delete (1-4999)
     */
    void DeleteEntity(int iEntityHandle);

    /**
     * Handle entity death event.
     * Awards XP, updates quests, generates loot.
     *
     * @param iEntityHandle - Entity that died
     * @param sAttackerH - Attacker handle
     * @param cAttackerType - Attacker type (player/npc)
     * @param sDamage - Final damage dealt
     */
    void OnEntityKilled(int iEntityHandle, short sAttackerH, char cAttackerType, short sDamage);

    // ========================================================================
    // Update & Behavior System
    // ========================================================================

    /**
     * Main entity update loop. Called each game tick.
     * Processes all active entities, updates AI, timers, etc.
     */
    void ProcessEntities();

    /**
     * Execute behavior for dead entity (respawn timer).
     */
    void UpdateDeadBehavior(int iEntityHandle);

    /**
     * Execute movement behavior.
     */
    void UpdateMoveBehavior(int iEntityHandle);

    /**
     * Execute combat behavior.
     */
    void UpdateAttackBehavior(int iEntityHandle);

    /**
     * Execute idle behavior.
     */
    void UpdateStopBehavior(int iEntityHandle);

    /**
     * Execute flee behavior.
     */
    void UpdateFleeBehavior(int iEntityHandle);

    // ========================================================================
    // NPC Behavior & Helpers
    // ========================================================================

    void NpcBehavior_Move(int iNpcH);
    void TargetSearch(int iNpcH, short* pTarget, char* pTargetType);
    void NpcBehavior_Attack(int iNpcH);
    void NpcBehavior_Flee(int iNpcH);
    void NpcBehavior_Stop(int iNpcH);
    void NpcBehavior_Dead(int iNpcH);
    void CalcNextWayPointDestination(int iNpcH);
    void NpcMagicHandler(int iNpcH, short dX, short dY, short sType);
    int iGetNpcRelationship(int iWhatH, int iRecvH);
    int iGetNpcRelationship_SendEvent(int iNpcH, int iOpponentH);
    void NpcRequestAssistance(int iNpcH);
    bool _bNpcBehavior_ManaCollector(int iNpcH);
    bool _bNpcBehavior_Detector(int iNpcH);
    void _NpcBehavior_GrandMagicGenerator(int iNpcH);
    bool bSetNpcFollowMode(char* pName, char* pFollowName, char cFollowOwnerType);
    void bSetNpcAttackMode(char* cName, int iTargetH, char cTargetType, bool bIsPermAttack);

    // ========================================================================
    // Query & Access
    // ========================================================================

    /**
     * Get entity pointer by handle.
     * @return CNpc pointer or NULL if invalid
     */
    CNpc* GetEntity(int iEntityHandle) const;

    /**
     * Get entity pointer by GUID.
     * @return CNpc pointer or NULL if not found
     */
    CNpc* GetEntityByGUID(uint32_t dwGUID) const;

    /**
     * Get entity handle by GUID.
     * @return Entity handle (1-4999) or -1 if not found
     */
    int GetEntityHandleByGUID(uint32_t dwGUID) const;

    /**
     * Get entity GUID by handle.
     * @return GUID or 0 if invalid handle
     */
    uint32_t GetEntityGUID(int iEntityHandle) const;

    /**
     * Get total active entities across all maps.
     */
    int GetTotalActiveEntities() const;

    /**
     * Get total entities on specific map.
     */
    int GetMapEntityCount(int iMapIndex) const;

    /**
     * Find entity by name.
     * @return Entity handle or -1 if not found
     */
    int FindEntityByName(const char* pName) const;

    /**
     * Get active entity list for efficient iteration.
     * Returns array of active entity indices (not handles!).
     * Use with GetActiveEntityCount() to iterate only active entities.
     *
     * Performance: O(active_count) instead of O(DEF_MAXNPCS)
     *
     * Example:
     *   int* pActiveList = m_pEntityManager->GetActiveEntityList();
     *   int iCount = m_pEntityManager->GetActiveEntityCount();
     *   for (int i = 0; i < iCount; i++) {
     *       int iHandle = pActiveList[i];
     *       NpcProcess(iHandle);
     *   }
     */
    int* GetActiveEntityList() const { return m_pActiveEntityList; }

    /**
     * Get number of active entities.
     * Use with GetActiveEntityList() for efficient iteration.
     */
    int GetActiveEntityCount() const { return m_iActiveEntityCount; }

    /**
     * Get direct access to entity array for backward compatibility.
     * WARNING: Direct array access bypasses EntityManager logic.
     * Prefer using GetEntity() or GetActiveEntityList().
     *
     * @return CNpc** array (indices 0-4999, index 0 unused)
     */
    CNpc** GetEntityArray() const { return m_pNpcList; }

    // ========================================================================
    // Configuration
    // ========================================================================

    /**
     * Set map list pointer (from CGame).
     * Required for spawn system to access map data.
     */
    void SetMapList(class CMap** pMapList, int iMaxMaps);

    /**
     * Set game instance pointer for callbacks.
     */
    void SetGame(class CGame* pGame);

private:
    // ========================================================================
    // Internal Helpers
    // ========================================================================

    /**
     * Initialize NPC attributes from configuration.
     */
    bool InitEntityAttributes(CNpc* pNpc, const char* pNpcName, short sClass, char cSA);

    /**
     * Find first available entity slot.
     * @return Slot index (1-4999) or -1 if full
     */
    int GetFreeEntitySlot() const;

    /**
     * Validate entity handle is in range and exists.
     */
    bool IsValidEntity(int iEntityHandle) const;

    /**
     * Generate item drops when entity dies.
     */
    void GenerateEntityLoot(int iEntityHandle, short sAttackerH, char cAttackerType);

    /**
     * Internal cleanup for entity deletion (drops, counters, naming value).
     */
    void DeleteNpcInternal(int iNpcH);

    void NpcDeadItemGenerator(int iNpcH, short sAttackerH, char cAttackerType);
    int RollDropTableItem(const DropTable* table, int tier, int& outMinCount, int& outMaxCount) const;
    bool SpawnNpcDropItem(int iNpcH, int itemId, int minCount, int maxCount);

    // ========================================================================
    // Spawn Point Management
    // ========================================================================

    /**
     * Process random mob generators for a map.
     */
    void ProcessRandomSpawns(int iMapIndex);

    /**
     * Process spot mob generators for a map.
     */
    void ProcessSpotSpawns(int iMapIndex);

    /**
     * Check if spawn point can spawn (limits, timers).
     */
    bool CanSpawnAtSpot(int iMapIndex, int iSpotIndex) const;

    /**
     * Generate next unique GUID for new entity.
     */
    uint32_t GenerateEntityGUID();

    // ========================================================================
    // Data Members
    // ========================================================================

    // Entity Storage (OWNED by EntityManager)
    class CNpc** m_pNpcList;                // Entity array (indices 0-4999, index 0 unused)
    uint32_t m_dwEntityGUID[DEF_MAXNPCS];  // GUID for each entity slot

    // Performance: Active Entity Tracking
    // Instead of iterating 5,000 slots, iterate only active entities
    int* m_pActiveEntityList;               // Indices of active entities
    int m_iActiveEntityCount;               // Number of active entities

    // External References
    class CMap** m_pMapList;                // Reference to map list (from CGame)
    class CGame* m_pGame;                   // Reference to game instance
    int m_iMaxMaps;                         // Number of maps

    // Entity Statistics
    int m_iTotalEntities;                   // Total active entities (same as m_iActiveEntityCount)
    uint32_t m_dwNextGUID;                     // Next GUID to assign (monotonically increasing)

    bool m_bInitialized;                    // Initialization flag

    // ========================================================================
    // Active Entity List Management (Private Helpers)
    // ========================================================================

    /**
     * Add entity to active list when created.
     * Called by CreateEntity().
     */
    void AddToActiveList(int iEntityHandle);

    /**
     * Remove entity from active list when deleted.
     * Called by DeleteEntity().
     */
    void RemoveFromActiveList(int iEntityHandle);
};
