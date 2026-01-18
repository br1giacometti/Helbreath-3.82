// EntityManager.cpp: implementation of the CEntityManager class.
//
//////////////////////////////////////////////////////////////////////

#include "CommonTypes.h"
#include "EntityManager.h"
#include "Game.h"
#include <cstdio>

extern void PutLogList(char* cMsg);

extern char G_cTxt[512];
extern char _tmp_cTmpDirX[9];
extern char _tmp_cTmpDirY[9];
extern int ITEMSPREAD_FIEXD_COORD[25][2];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEntityManager::CEntityManager()
{
    // Allocate entity array (EntityManager OWNS this)
    m_pNpcList = new CNpc*[DEF_MAXNPCS];
    for (int i = 0; i < DEF_MAXNPCS; i++) {
        m_pNpcList[i] = NULL;
        m_dwEntityGUID[i] = 0;
    }

    // Allocate active entity tracking list for performance
    m_pActiveEntityList = new int[DEF_MAXNPCS];
    m_iActiveEntityCount = 0;

    m_pMapList = NULL;
    m_pGame = NULL;
    m_iMaxMaps = 0;
    m_iTotalEntities = 0;
    m_dwNextGUID = 1; // Start GUIDs at 1 (0 = invalid)
    m_bInitialized = false;
}

CEntityManager::~CEntityManager()
{
    // Delete all entities (EntityManager owns them)
    if (m_pNpcList != NULL) {
        for (int i = 0; i < DEF_MAXNPCS; i++) {
            if (m_pNpcList[i] != NULL) {
                delete m_pNpcList[i];
                m_pNpcList[i] = NULL;
            }
        }
        delete[] m_pNpcList;
        m_pNpcList = NULL;
    }

    // Delete active entity tracking list
    if (m_pActiveEntityList != NULL) {
        delete[] m_pActiveEntityList;
        m_pActiveEntityList = NULL;
    }
}

// ========================================================================
// Configuration
// ========================================================================

void CEntityManager::SetMapList(CMap** pMapList, int iMaxMaps)
{
    m_pMapList = pMapList;
    m_iMaxMaps = iMaxMaps;
}

void CEntityManager::SetGame(CGame* pGame)
{
    m_pGame = pGame;
    m_bInitialized = (m_pNpcList != NULL && m_pMapList != NULL && m_pGame != NULL);
}

// ========================================================================
// Core Spawn System - STUBS
// ========================================================================

void CEntityManager::ProcessSpawns()
{
    if (!m_bInitialized || m_pMapList == NULL || m_pGame == NULL)
        return;

    if (m_pGame->m_bOnExitProcess)
        return;


    ProcessRandomSpawns(0);

    // Loop through all maps and process their spot spawn generators
    for (int i = 0; i < m_iMaxMaps; i++) {
        if (m_pMapList[i] != NULL) {
            ProcessSpotSpawns(i);
        }
    }
}

int CEntityManager::CreateEntity(
    char* pNpcName, char* pName, char* pMapName,
    short sClass, char cSA, char cMoveType,
    int* poX, int* poY,
    char* pWaypointList, RECT* pArea,
    int iSpotMobIndex, char cChangeSide,
    bool bHideGenMode, bool bIsSummoned,
    bool bFirmBerserk, bool bIsMaster,
    int iGuildGUID)
{
    // NOTE: This is copied from CGame::bCreateNewNpc with modifications for EntityManager

    if (!m_bInitialized) return -1;
    if (m_pGame == NULL) return -1;
    if (strlen(pName) == 0) return -1;
    if (strlen(pNpcName) == 0) return -1;

    int i, t, j, k, iMapIndex;
    char cTmpName[11], cTxt[120];
    short sX, sY, sRange;
    bool bFlag;
    SYSTEMTIME SysTime;

    GetLocalTime(&SysTime);
    std::memset(cTmpName, 0, sizeof(cTmpName));
    strcpy(cTmpName, pMapName);
    iMapIndex = -1;

    // Find map index
    for (i = 0; i < m_iMaxMaps; i++)
        if (m_pMapList[i] != 0) {
            if (memcmp(m_pMapList[i]->m_cName, cTmpName, 10) == 0)
                iMapIndex = i;
        }

    if (iMapIndex == -1) return -1;

    // Find free entity slot
    for (i = 1; i < DEF_MAXNPCS; i++)
        if (m_pNpcList[i] == 0) {
            m_pNpcList[i] = new CNpc(pName);

            // Initialize NPC attributes - call Game's _bInitNpcAttr for now
            if (InitEntityAttributes(m_pNpcList[i], pNpcName, sClass, cSA) == false) {
                std::snprintf(cTxt, sizeof(cTxt), "(!) Not existing NPC creation request! (%s) Ignored.", pNpcName);
                PutLogList(cTxt);
                delete m_pNpcList[i];
                m_pNpcList[i] = 0;
                return -1;
            }

            // Day of week check
            if (m_pNpcList[i]->m_cDayOfWeekLimit < 10) {
                if (m_pNpcList[i]->m_cDayOfWeekLimit != SysTime.wDayOfWeek) {
                    delete m_pNpcList[i];
                    m_pNpcList[i] = 0;
                    return -1;
                }
            }

            // Determine spawn location based on move type
            switch (cMoveType) {
            case DEF_MOVETYPE_GUARD:
            case DEF_MOVETYPE_RANDOM:
                if ((poX != 0) && (poY != 0) && (*poX != 0) && (*poY != 0)) {
                    sX = *poX;
                    sY = *poY;
                }
                else {
                    for (j = 0; j <= 30; j++) {
                        sX = (rand() % (m_pMapList[iMapIndex]->m_sSizeX - 50)) + 15;
                        sY = (rand() % (m_pMapList[iMapIndex]->m_sSizeY - 50)) + 15;

                        bFlag = true;
                        for (k = 0; k < DEF_MAXMGAR; k++)
                            if (m_pMapList[iMapIndex]->m_rcMobGenAvoidRect[k].left != -1) {
                                if ((sX >= m_pMapList[iMapIndex]->m_rcMobGenAvoidRect[k].left) &&
                                    (sX <= m_pMapList[iMapIndex]->m_rcMobGenAvoidRect[k].right) &&
                                    (sY >= m_pMapList[iMapIndex]->m_rcMobGenAvoidRect[k].top) &&
                                    (sY <= m_pMapList[iMapIndex]->m_rcMobGenAvoidRect[k].bottom)) {
                                    // Avoid Rect
                                    bFlag = false;
                                }
                            }
                        if (bFlag) goto GET_VALIDLOC_SUCCESS;
                    }
                    delete m_pNpcList[i];
                    m_pNpcList[i] = 0;
                    return -1;

                GET_VALIDLOC_SUCCESS:;
                    // sX, sY found
                }
                break;

            case DEF_MOVETYPE_RANDOMAREA:
                // Spawn in random area
                sRange = (short)(pArea->right - pArea->left);
                sX = (short)((rand() % sRange) + pArea->left);
                sRange = (short)(pArea->bottom - pArea->top);
                sY = (short)((rand() % sRange) + pArea->top);
                break;

            case DEF_MOVETYPE_RANDOMWAYPOINT:
                // Spawn at random waypoint
                sX = (short)m_pMapList[iMapIndex]->m_WaypointList[pWaypointList[m_pGame->iDice(1, 10) - 1]].x;
                sY = (short)m_pMapList[iMapIndex]->m_WaypointList[pWaypointList[m_pGame->iDice(1, 10) - 1]].y;
                break;

            default:
                // Use provided position or first waypoint
                if ((poX != 0) && (poY != 0) && (*poX != 0) && (*poY != 0)) {
                    sX = *poX;
                    sY = *poY;
                }
                else {
                    sX = (short)m_pMapList[iMapIndex]->m_WaypointList[pWaypointList[0]].x;
                    sY = (short)m_pMapList[iMapIndex]->m_WaypointList[pWaypointList[0]].y;
                }
                break;
            }

            // Check if position is empty
            if (m_pGame->bGetEmptyPosition(&sX, &sY, iMapIndex) == false) {
                delete m_pNpcList[i];
                m_pNpcList[i] = 0;
                return -1;
            }

            // Hide generation mode check
            if ((bHideGenMode) && (m_pGame->_iGetPlayerNumberOnSpot(sX, sY, iMapIndex, 7) != 0)) {
                delete m_pNpcList[i];
                m_pNpcList[i] = 0;
                return -1;
            }

            // Set output position
            if ((poX != 0) && (poY != 0)) {
                *poX = sX;
                *poY = sY;
            }

            // Set entity position
            m_pNpcList[i]->m_sX = sX;
            m_pNpcList[i]->m_sY = sY;
            m_pNpcList[i]->m_vX = sX;
            m_pNpcList[i]->m_vY = sY;

            // Set waypoints
            for (t = 0; t < 10; t++)
                m_pNpcList[i]->m_iWayPointIndex[t] = pWaypointList[t];

            m_pNpcList[i]->m_cTotalWaypoint = 0;
            for (t = 0; t < 10; t++)
                if (m_pNpcList[i]->m_iWayPointIndex[t] != -1) m_pNpcList[i]->m_cTotalWaypoint++;

            // Set random area if provided
            if (pArea != 0) {
                SetRect(&m_pNpcList[i]->m_rcRandomArea, pArea->left, pArea->top, pArea->right, pArea->bottom);
            }

            // Set destination based on move type
            switch (cMoveType) {
            case DEF_MOVETYPE_GUARD:
                m_pNpcList[i]->m_dX = m_pNpcList[i]->m_sX;
                m_pNpcList[i]->m_dY = m_pNpcList[i]->m_sY;
                break;

            case DEF_MOVETYPE_SEQWAYPOINT:
                m_pNpcList[i]->m_cCurWaypoint = 1;
                m_pNpcList[i]->m_dX = (short)m_pMapList[iMapIndex]->m_WaypointList[m_pNpcList[i]->m_iWayPointIndex[m_pNpcList[i]->m_cCurWaypoint]].x;
                m_pNpcList[i]->m_dY = (short)m_pMapList[iMapIndex]->m_WaypointList[m_pNpcList[i]->m_iWayPointIndex[m_pNpcList[i]->m_cCurWaypoint]].y;
                break;

            case DEF_MOVETYPE_RANDOMWAYPOINT:
                m_pNpcList[i]->m_cCurWaypoint = (rand() % (m_pNpcList[i]->m_cTotalWaypoint - 1)) + 1;
                m_pNpcList[i]->m_dX = (short)m_pMapList[iMapIndex]->m_WaypointList[m_pNpcList[i]->m_iWayPointIndex[m_pNpcList[i]->m_cCurWaypoint]].x;
                m_pNpcList[i]->m_dY = (short)m_pMapList[iMapIndex]->m_WaypointList[m_pNpcList[i]->m_iWayPointIndex[m_pNpcList[i]->m_cCurWaypoint]].y;
                break;

            case DEF_MOVETYPE_RANDOMAREA:
                m_pNpcList[i]->m_cCurWaypoint = 0;
                sRange = (short)(m_pNpcList[i]->m_rcRandomArea.right - m_pNpcList[i]->m_rcRandomArea.left);
                m_pNpcList[i]->m_dX = (short)((rand() % sRange) + m_pNpcList[i]->m_rcRandomArea.left);
                sRange = (short)(m_pNpcList[i]->m_rcRandomArea.bottom - m_pNpcList[i]->m_rcRandomArea.top);
                m_pNpcList[i]->m_dY = (short)((rand() % sRange) + m_pNpcList[i]->m_rcRandomArea.top);
                break;

            case DEF_MOVETYPE_RANDOM:
                m_pNpcList[i]->m_dX = (short)((rand() % (m_pMapList[iMapIndex]->m_sSizeX - 50)) + 15);
                m_pNpcList[i]->m_dY = (short)((rand() % (m_pMapList[iMapIndex]->m_sSizeY - 50)) + 15);
                break;
            }

            m_pNpcList[i]->m_tmp_iError = 0;
            m_pNpcList[i]->m_cMoveType = cMoveType;

            // Set behavior based on action limit
            switch (m_pNpcList[i]->m_cActionLimit) {
            case 2:
            case 3:
            case 5:
                m_pNpcList[i]->m_cBehavior = DEF_BEHAVIOR_STOP;

                switch (m_pNpcList[i]->m_sType) {
                case 15: // ShopKeeper-W
                case 19: // Gandlf
                case 20: // Howard
                case 24: // Tom
                case 25: // William
                case 26: // Kennedy
                    m_pNpcList[i]->m_cDir = static_cast<char>(4 + m_pGame->iDice(1, 3) - 1);
                    break;

                default:
                    m_pNpcList[i]->m_cDir = static_cast<char>(m_pGame->iDice(1, 8));
                    break;
                }
                break;

            default:
                m_pNpcList[i]->m_cBehavior = DEF_BEHAVIOR_MOVE;
                m_pNpcList[i]->m_cDir = 5;
                break;
            }

            m_pNpcList[i]->m_iFollowOwnerIndex = 0;
            m_pNpcList[i]->m_iTargetIndex = 0;
            m_pNpcList[i]->m_cTurn = (rand() % 2);

            // Set appearance based on type
            switch (m_pNpcList[i]->m_sType) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                m_pNpcList[i]->m_sAppr2 = static_cast<short>(0xF000);
                m_pNpcList[i]->m_sAppr2 = m_pNpcList[i]->m_sAppr2 | ((rand() % 13) << 4);
                m_pNpcList[i]->m_sAppr2 = m_pNpcList[i]->m_sAppr2 | (rand() % 9);
                break;

            case 36: // AGT
            case 37: // CGT
            case 38: // MS
            case 39: // DT
                m_pNpcList[i]->m_sAppr2 = 3;
                break;

            case 64: // Crop
                m_pNpcList[i]->m_sAppr2 = 1;
                break;

            default:
                m_pNpcList[i]->m_sAppr2 = 0;
                break;
            }

            // Set entity properties
            m_pNpcList[i]->m_cMapIndex = (char)iMapIndex;
            m_pNpcList[i]->m_dwTime = GameClock::GetTimeMS() + (rand() % 10000);
            m_pNpcList[i]->m_dwActionTime += (rand() % 300);
            m_pNpcList[i]->m_dwMPupTime = GameClock::GetTimeMS();
            m_pNpcList[i]->m_dwHPupTime = m_pNpcList[i]->m_dwMPupTime;
            m_pNpcList[i]->m_sBehaviorTurnCount = 0;
            m_pNpcList[i]->m_bIsSummoned = bIsSummoned;
            m_pNpcList[i]->m_bIsMaster = bIsMaster;
            if (bIsSummoned)
                m_pNpcList[i]->m_dwSummonedTime = GameClock::GetTimeMS();

            if (bFirmBerserk) {
                m_pNpcList[i]->m_cMagicEffectStatus[DEF_MAGICTYPE_BERSERK] = 1;
                m_pNpcList[i]->m_iStatus = m_pNpcList[i]->m_iStatus | 0x20;
            }

            if (cChangeSide != -1) m_pNpcList[i]->m_cSide = cChangeSide;

            m_pNpcList[i]->m_cBravery = (rand() % 3) + m_pNpcList[i]->m_iMinBravery;
            m_pNpcList[i]->m_iSpotMobIndex = iSpotMobIndex;
            m_pNpcList[i]->m_iGuildGUID = iGuildGUID;

            // Generate and assign GUID
            m_dwEntityGUID[i] = GenerateEntityGUID();


            // Register with map
            m_pMapList[iMapIndex]->SetOwner(i, DEF_OWNERTYPE_NPC, sX, sY);
            m_pMapList[iMapIndex]->m_iTotalActiveObject++;
            m_pMapList[iMapIndex]->m_iTotalAliveObject++;
            m_iTotalEntities++;

            // Special handling for crusade structures and crops
            switch (m_pNpcList[i]->m_sType) {
            case 36: // AGT
            case 37: // CGT
            case 38: // MS
            case 39: // DT
            case 42: // ManaStone
                m_pMapList[iMapIndex]->bAddCrusadeStructureInfo(static_cast<char>(m_pNpcList[i]->m_sType), sX, sY, m_pNpcList[i]->m_cSide);
                break;

            case 64: // Crop
                m_pMapList[iMapIndex]->bAddCropsTotalSum();
                break;
            }

            // Add to active entity list for efficient iteration (Performance!)
            AddToActiveList(i);

            m_pGame->SendEventToNearClient_TypeA(i, DEF_OWNERTYPE_NPC, MSGID_EVENT_LOG, DEF_MSGTYPE_CONFIRM, 0, 0, 0);
            return i; // Return entity handle (SUCCESS)
        }

    // No free slots - log diagnostic info
    int iUsedSlots = 0;
    for (int idx = 1; idx < DEF_MAXNPCS; idx++) {
        if (m_pNpcList[idx] != 0) iUsedSlots++;
    }
    std::snprintf(G_cTxt, sizeof(G_cTxt),
        "[SPAWN] ERROR: No free entity slots! Used: %d/%d, ActiveList: %d, TotalEntities: %d",
        iUsedSlots, DEF_MAXNPCS - 1, m_iActiveEntityCount, m_iTotalEntities);
    PutLogList(G_cTxt);
    return -1; // No free slots
}

void CEntityManager::DeleteEntity(int iEntityHandle)
{
    if (!IsValidEntity(iEntityHandle))
        return;

    if (m_pGame == NULL)
        return;

    DeleteNpcInternal(iEntityHandle);

    RemoveFromActiveList(iEntityHandle);
    m_dwEntityGUID[iEntityHandle] = 0;
    if (m_iTotalEntities > 0)
        m_iTotalEntities--;
}

void CEntityManager::OnEntityKilled(int iEntityHandle, short sAttackerH, char cAttackerType, short sDamage)
{
    // Extracted from Game.cpp:10810-11074 (NpcKilledHandler)

    if (!IsValidEntity(iEntityHandle)) {
        return;
    }

    CNpc* pEntity = m_pNpcList[iEntityHandle];

    // Check if already killed
    if (pEntity->m_bIsKilled) {
        return;
    }

    if (m_pGame == NULL || m_pMapList == NULL) {
        return;
    }


    // ========================================================================
    // 1. Mark entity as killed and set death state
    // ========================================================================
    pEntity->m_bIsKilled = true;
    pEntity->m_iHP = 0;
    pEntity->m_iLastDamage = sDamage;

    short sType = pEntity->m_sType;
    int iMapIndex = pEntity->m_cMapIndex;

    // Decrement alive object counter
    m_pMapList[iMapIndex]->m_iTotalAliveObject--;

    // ========================================================================
    // 2. Remove from target lists and release followers
    // ========================================================================
    m_pGame->RemoveFromTarget(iEntityHandle, DEF_OWNERTYPE_NPC);
    m_pGame->ReleaseFollowMode(iEntityHandle, DEF_OWNERTYPE_NPC);

    pEntity->m_iTargetIndex = 0;
    pEntity->m_cTargetType = 0;

    // ========================================================================
    // 3. Send death animation event
    // ========================================================================
    short sAttackerWeapon;
    if (cAttackerType == DEF_OWNERTYPE_PLAYER) {
        if (m_pGame->m_pClientList[sAttackerH] != NULL)
            sAttackerWeapon = ((m_pGame->m_pClientList[sAttackerH]->m_sAppr2 & 0x0FF0) >> 4);
        else
            sAttackerWeapon = 1;
    }
    else {
        sAttackerWeapon = 1;
    }

    m_pGame->SendEventToNearClient_TypeA(iEntityHandle, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION,
        DEF_OBJECTDYING, sDamage, sAttackerWeapon, 0);

    // ========================================================================
    // 4. Update map tiles
    // ========================================================================
    m_pMapList[iMapIndex]->ClearOwner(10, iEntityHandle, DEF_OWNERTYPE_NPC, pEntity->m_sX, pEntity->m_sY);
    m_pMapList[iMapIndex]->SetDeadOwner(iEntityHandle, DEF_OWNERTYPE_NPC, pEntity->m_sX, pEntity->m_sY);

    // ========================================================================
    // 5. Set death behavior and timer
    // ========================================================================
    pEntity->m_cBehavior = DEF_BEHAVIOR_DEAD;
    pEntity->m_sBehaviorTurnCount = 0;
    pEntity->m_dwDeadTime = GameClock::GetTimeMS();

    // ========================================================================
    // 6. Check for no-penalty/no-reward maps
    // ========================================================================
    if (m_pMapList[iMapIndex]->m_cType == DEF_MAPTYPE_NOPENALTY_NOREWARD) {
        return;
    }

    // ========================================================================
    // 7. Generate item drops (delegate to CGame for now)
    // ========================================================================
    NpcDeadItemGenerator(iEntityHandle, sAttackerH, cAttackerType);

    // ========================================================================
    // 8. Award experience and handle player-specific events
    // ========================================================================
    if ((pEntity->m_bIsSummoned != true) && (cAttackerType == DEF_OWNERTYPE_PLAYER) &&
        (m_pGame->m_pClientList[sAttackerH] != NULL)) {
        double dTmp1, dTmp2, dTmp3;
        uint32_t iExp = (pEntity->m_iExp / 3);

        if (pEntity->m_iNoDieRemainExp > 0) {
            iExp += pEntity->m_iNoDieRemainExp;
        }

        if (m_pGame->m_pClientList[sAttackerH]->m_iAddExp != 0) {
            dTmp1 = (double)m_pGame->m_pClientList[sAttackerH]->m_iAddExp;
            dTmp2 = (double)iExp;
            dTmp3 = (dTmp1 / 100.0f) * dTmp2;
            iExp += (uint32_t)dTmp3;
        }

        if (sType == 81) {
            for (int i = 1; i < DEF_MAXCLIENTS; i++) {
                if (m_pGame->m_pClientList[i] != NULL) {
                    m_pGame->SendNotifyMsg(sAttackerH, i, DEF_NOTIFY_ABADDONKILLED,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
                }
            }
        }

        if (m_pGame->m_bIsCrusadeMode) {
            if (iExp > 10) iExp = iExp / 3;
        }

        m_pGame->GetExp(sAttackerH, iExp, true);

        int iQuestIndex = m_pGame->m_pClientList[sAttackerH]->m_iQuest;
        if (iQuestIndex != 0 && m_pGame->m_pQuestConfigList[iQuestIndex] != NULL) {
            switch (m_pGame->m_pQuestConfigList[iQuestIndex]->m_iType) {
            case DEF_QUESTTYPE_MONSTERHUNT:
                if (m_pGame->m_pClientList[sAttackerH]->m_bQuestMatchFlag_Loc &&
                    m_pGame->m_pQuestConfigList[iQuestIndex]->m_iTargetType == sType) {
                    m_pGame->m_pClientList[sAttackerH]->m_iCurQuestCount++;
                    char cQuestRemain = (m_pGame->m_pQuestConfigList[iQuestIndex]->m_iMaxCount -
                        m_pGame->m_pClientList[sAttackerH]->m_iCurQuestCount);
                    m_pGame->SendNotifyMsg(0, sAttackerH, DEF_NOTIFY_QUESTCOUNTER, cQuestRemain, 0, 0, 0);
                    m_pGame->_bCheckIsQuestCompleted(sAttackerH);
                }
                break;
            }
        }

    }

    // ========================================================================
    // 9. Rating adjustments (player only)
    // ========================================================================
    if (cAttackerType == DEF_OWNERTYPE_PLAYER) {
        switch (sType) {
        case 32:
            m_pGame->m_pClientList[sAttackerH]->m_iRating -= 5;
            if (m_pGame->m_pClientList[sAttackerH]->m_iRating < -10000)
                m_pGame->m_pClientList[sAttackerH]->m_iRating = 0;
            if (m_pGame->m_pClientList[sAttackerH]->m_iRating > 10000)
                m_pGame->m_pClientList[sAttackerH]->m_iRating = 0;
            break;
        case 33:
            break;
        }
    }

    // ========================================================================
    // 10. Crusade construction points / war contribution
    // ========================================================================
    int iConstructionPoint = 0;
    int iWarContribution = 0;
    switch (sType) {
    case 1:  iConstructionPoint = 50; iWarContribution = 100; break;
    case 2:  iConstructionPoint = 50; iWarContribution = 100; break;
    case 3:  iConstructionPoint = 50; iWarContribution = 100; break;
    case 4:  iConstructionPoint = 50; iWarContribution = 100; break;
    case 5:  iConstructionPoint = 50; iWarContribution = 100; break;
    case 6:  iConstructionPoint = 50; iWarContribution = 100; break;
    case 36: iConstructionPoint = 700; iWarContribution = 4000; break;
    case 37: iConstructionPoint = 700; iWarContribution = 4000; break;
    case 38: iConstructionPoint = 500; iWarContribution = 2000; break;
    case 39: iConstructionPoint = 500; iWarContribution = 2000; break;
    case 40: iConstructionPoint = 1500; iWarContribution = 5000; break;
    case 41: iConstructionPoint = 5000; iWarContribution = 10000; break;
    case 43: iConstructionPoint = 500; iWarContribution = 1000; break;
    case 44: iConstructionPoint = 1000; iWarContribution = 2000; break;
    case 45: iConstructionPoint = 1500; iWarContribution = 3000; break;
    case 46: iConstructionPoint = 1000; iWarContribution = 2000; break;
    case 47: iConstructionPoint = 1500; iWarContribution = 3000; break;
    case 64:
        m_pMapList[iMapIndex]->bRemoveCropsTotalSum();
        break;
    }

    if (iConstructionPoint != 0) {
        switch (cAttackerType) {
        case DEF_OWNERTYPE_PLAYER:
            if (m_pGame->m_pClientList[sAttackerH]->m_cSide != pEntity->m_cSide) {
                m_pGame->m_pClientList[sAttackerH]->m_iConstructionPoint += iConstructionPoint;
                if (m_pGame->m_pClientList[sAttackerH]->m_iConstructionPoint > DEF_MAXCONSTRUCTIONPOINT)
                    m_pGame->m_pClientList[sAttackerH]->m_iConstructionPoint = DEF_MAXCONSTRUCTIONPOINT;

                m_pGame->m_pClientList[sAttackerH]->m_iWarContribution += iWarContribution;
                if (m_pGame->m_pClientList[sAttackerH]->m_iWarContribution > DEF_MAXWARCONTRIBUTION)
                    m_pGame->m_pClientList[sAttackerH]->m_iWarContribution = DEF_MAXWARCONTRIBUTION;

                std::snprintf(G_cTxt, sizeof(G_cTxt), "Enemy Npc Killed by player! Construction: +%d WarContribution: +%d",
                    iConstructionPoint, iWarContribution);
                PutLogList(G_cTxt);

                m_pGame->SendNotifyMsg(0, sAttackerH, DEF_NOTIFY_CONSTRUCTIONPOINT,
                    m_pGame->m_pClientList[sAttackerH]->m_iConstructionPoint,
                    m_pGame->m_pClientList[sAttackerH]->m_iWarContribution, 0, 0);
            }
            else {
                m_pGame->m_pClientList[sAttackerH]->m_iWarContribution -= (iWarContribution * 2);
                if (m_pGame->m_pClientList[sAttackerH]->m_iWarContribution < 0)
                    m_pGame->m_pClientList[sAttackerH]->m_iWarContribution = 0;

                std::snprintf(G_cTxt, sizeof(G_cTxt), "Friendly Npc Killed by player! WarContribution: -%d", iWarContribution);
                PutLogList(G_cTxt);

                m_pGame->SendNotifyMsg(0, sAttackerH, DEF_NOTIFY_CONSTRUCTIONPOINT,
                    m_pGame->m_pClientList[sAttackerH]->m_iConstructionPoint,
                    m_pGame->m_pClientList[sAttackerH]->m_iWarContribution, 0, 0);
            }
            break;

        case DEF_OWNERTYPE_NPC:
            if (m_pGame->m_pNpcList[sAttackerH]->m_iGuildGUID != 0) {
                if (m_pGame->m_pNpcList[sAttackerH]->m_cSide != pEntity->m_cSide) {
                    for (int i = 1; i < DEF_MAXCLIENTS; i++) {
                        if ((m_pGame->m_pClientList[i] != NULL) &&
                            (m_pGame->m_pClientList[i]->m_iGuildGUID == m_pGame->m_pNpcList[sAttackerH]->m_iGuildGUID) &&
                            (m_pGame->m_pClientList[i]->m_iCrusadeDuty == 3)) {
                            m_pGame->m_pClientList[i]->m_iConstructionPoint += iConstructionPoint;
                            if (m_pGame->m_pClientList[i]->m_iConstructionPoint > DEF_MAXCONSTRUCTIONPOINT)
                                m_pGame->m_pClientList[i]->m_iConstructionPoint = DEF_MAXCONSTRUCTIONPOINT;

                            std::snprintf(G_cTxt, sizeof(G_cTxt), "Enemy Npc Killed by Npc! Construct point +%d", iConstructionPoint);
                            PutLogList(G_cTxt);
                            m_pGame->SendNotifyMsg(0, i, DEF_NOTIFY_CONSTRUCTIONPOINT,
                                m_pGame->m_pClientList[i]->m_iConstructionPoint,
                                m_pGame->m_pClientList[i]->m_iWarContribution, 0, 0);
                            break;
                        }
                    }
                }
            }
            break;
        }
    }

    // ========================================================================
    // 11. Handle special ability death triggers (explosive NPCs)
    // ========================================================================
    if (pEntity->m_cSpecialAbility == 7) {
        // Explosive ability - triggers magic on death
        pEntity->m_iMana = 100;
        pEntity->m_iMagicHitRatio = 100;
        NpcMagicHandler(iEntityHandle, pEntity->m_sX, pEntity->m_sY, 30);
    }
    else if (pEntity->m_cSpecialAbility == 8) {
        // Powerful explosive ability
        pEntity->m_iMana = 100;
        pEntity->m_iMagicHitRatio = 100;
        NpcMagicHandler(iEntityHandle, pEntity->m_sX, pEntity->m_sY, 61);
    }

    // ========================================================================
    // 12. Heldenian mode tower tracking
    // ========================================================================
    if (m_pGame->m_bIsHeldenianMode &&
        m_pMapList[iMapIndex]->m_bIsHeldenianMap &&
        m_pGame->m_cHeldenianModeType == 1) {
        int iHeldenMapIndex = pEntity->m_cMapIndex;
        if (sType == 87 || sType == 89) {
            if (pEntity->m_cSide == 1) {
                m_pGame->m_iHeldenianAresdenLeftTower--;
                std::snprintf(G_cTxt, sizeof(G_cTxt), "Aresden Tower Broken, Left TOWER %d", m_pGame->m_iHeldenianAresdenLeftTower);
            }
            else if (pEntity->m_cSide == 2) {
                m_pGame->m_iHeldenianElvineLeftTower--;
                std::snprintf(G_cTxt, sizeof(G_cTxt), "Elvine Tower Broken, Left TOWER %d", m_pGame->m_iHeldenianElvineLeftTower);
            }
            PutLogList(G_cTxt);
            m_pGame->UpdateHeldenianStatus();
        }

        if ((m_pGame->m_iHeldenianElvineLeftTower == 0) ||
            (m_pGame->m_iHeldenianAresdenLeftTower == 0)) {
            m_pGame->GlobalEndHeldenianMode();
        }
    }

}

// ========================================================================
// Update & Behavior System - STUBS
// ========================================================================

void CEntityManager::ProcessEntities()
{
    if (m_pGame == NULL)
        return;

    if (m_pGame->m_bOnExitProcess)
        return;

    int i, iMaxHP;
    uint32_t dwTime, dwActionTime;

    dwTime = GameClock::GetTimeMS();

    for (i = 1; i < DEF_MAXNPCS; i++) {
        if (m_pNpcList[i] == 0)
            continue;

        if (i % 10 == 0) {
            extern void PollAllSockets();
            PollAllSockets();
        }

        if (m_pNpcList[i]->m_cBehavior == DEF_BEHAVIOR_ATTACK) {
            switch (m_pGame->iDice(1, 7)) {
            case 1: dwActionTime = m_pNpcList[i]->m_dwActionTime; break;
            case 2: dwActionTime = m_pNpcList[i]->m_dwActionTime - 100; break;
            case 3: dwActionTime = m_pNpcList[i]->m_dwActionTime - 200; break;
            case 4: dwActionTime = m_pNpcList[i]->m_dwActionTime - 300; break;
            case 5: dwActionTime = m_pNpcList[i]->m_dwActionTime - 400; break;
            case 6: dwActionTime = m_pNpcList[i]->m_dwActionTime - 600; break;
            case 7: dwActionTime = m_pNpcList[i]->m_dwActionTime - 700; break;
            }
            if (dwActionTime < 600) dwActionTime = 600;
        }
        else {
            dwActionTime = m_pNpcList[i]->m_dwActionTime;
        }

        if (m_pNpcList[i]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] != 0)
            dwActionTime += (dwActionTime / 2);

        if ((dwTime - m_pNpcList[i]->m_dwTime) > dwActionTime) {
            m_pNpcList[i]->m_dwTime = dwTime;

            if (abs(m_pNpcList[i]->m_cMagicLevel) > 0) {
                if ((dwTime - m_pNpcList[i]->m_dwMPupTime) > DEF_MPUPTIME) {
                    m_pNpcList[i]->m_dwMPupTime = dwTime;
                    m_pNpcList[i]->m_iMana += m_pGame->iDice(1, (m_pNpcList[i]->m_iMaxMana / 5));

                    if (m_pNpcList[i]->m_iMana > m_pNpcList[i]->m_iMaxMana)
                        m_pNpcList[i]->m_iMana = m_pNpcList[i]->m_iMaxMana;
                }
            }

            if (((dwTime - m_pNpcList[i]->m_dwHPupTime) > DEF_HPUPTIME) && (m_pNpcList[i]->m_bIsKilled == false)) {
                m_pNpcList[i]->m_dwHPupTime = dwTime;

                iMaxHP = m_pGame->iDice(m_pNpcList[i]->m_iHitDice, 8) + m_pNpcList[i]->m_iHitDice;
                if (m_pNpcList[i]->m_iHP < iMaxHP) {
                    if (m_pNpcList[i]->m_bIsSummoned == false)
                        m_pNpcList[i]->m_iHP += m_pGame->iDice(1, m_pNpcList[i]->m_iHitDice);

                    if (m_pNpcList[i]->m_iHP > iMaxHP) m_pNpcList[i]->m_iHP = iMaxHP;
                    if (m_pNpcList[i]->m_iHP <= 0)     m_pNpcList[i]->m_iHP = 1;
                }
            }

            switch (m_pNpcList[i]->m_cBehavior) {
            case DEF_BEHAVIOR_DEAD:
                UpdateDeadBehavior(i);
                break;
            case DEF_BEHAVIOR_STOP:
                UpdateStopBehavior(i);
                break;
            case DEF_BEHAVIOR_MOVE:
                UpdateMoveBehavior(i);
                break;
            case DEF_BEHAVIOR_ATTACK:
                UpdateAttackBehavior(i);
                break;
            case DEF_BEHAVIOR_FLEE:
                UpdateFleeBehavior(i);
                break;
            }

            if ((m_pNpcList[i] != 0) && (m_pNpcList[i]->m_iHP != 0) && (m_pNpcList[i]->m_bIsSummoned)) {
                switch (m_pNpcList[i]->m_sType) {
                case 29:
                    if ((dwTime - m_pNpcList[i]->m_dwSummonedTime) > 1000 * 90)
                        OnEntityKilled(i, 0, 0, 0);
                    break;

                default:
                    if ((dwTime - m_pNpcList[i]->m_dwSummonedTime) > DEF_SUMMONTIME)
                        OnEntityKilled(i, 0, 0, 0);
                    break;
                }
            }
        }
    }
}

void CEntityManager::UpdateDeadBehavior(int iEntityHandle)
{
    NpcBehavior_Dead(iEntityHandle);
}

void CEntityManager::UpdateMoveBehavior(int iEntityHandle)
{
    NpcBehavior_Move(iEntityHandle);
}

void CEntityManager::UpdateAttackBehavior(int iEntityHandle)
{
    NpcBehavior_Attack(iEntityHandle);
}

void CEntityManager::UpdateStopBehavior(int iEntityHandle)
{
    NpcBehavior_Stop(iEntityHandle);
}

void CEntityManager::UpdateFleeBehavior(int iEntityHandle)
{
    NpcBehavior_Flee(iEntityHandle);
}


// ========================================================================
// NPC Behavior & Helpers (ported from CGame)
// ========================================================================

void CEntityManager::NpcBehavior_Move(int iNpcH)
{
	char  cDir;
	short sX, sY, dX, dY, absX, absY;
	short sTarget, sDistance;
	char  cTargetType;

	if (m_pNpcList[iNpcH] == 0) return;
	if (m_pNpcList[iNpcH]->m_bIsKilled) return;
	if ((m_pNpcList[iNpcH]->m_bIsSummoned) &&
		(m_pNpcList[iNpcH]->m_iSummonControlMode == 1)) return;
	if (m_pNpcList[iNpcH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0) return;

	switch (m_pNpcList[iNpcH]->m_cActionLimit) {
	case 2:
	case 3:
	case 5:
		m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_STOP;
		m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
		return;
	}

	// v1.432-2
	int iStX, iStY;
	if (m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex] != 0) {
		iStX = m_pNpcList[iNpcH]->m_sX / 20;
		iStY = m_pNpcList[iNpcH]->m_sY / 20;
		m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_stTempSectorInfo[iStX][iStY].iMonsterActivity++;
	}

	m_pNpcList[iNpcH]->m_sBehaviorTurnCount++;
	if (m_pNpcList[iNpcH]->m_sBehaviorTurnCount > 5) {
		m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;

		absX = abs(m_pNpcList[iNpcH]->m_vX - m_pNpcList[iNpcH]->m_sX);
		absY = abs(m_pNpcList[iNpcH]->m_vY - m_pNpcList[iNpcH]->m_sY);

		if ((absX <= 2) && (absY <= 2)) {
			CalcNextWayPointDestination(iNpcH);
		}

		m_pNpcList[iNpcH]->m_vX = m_pNpcList[iNpcH]->m_sX;
		m_pNpcList[iNpcH]->m_vY = m_pNpcList[iNpcH]->m_sY;
	}

	TargetSearch(iNpcH, &sTarget, &cTargetType);
	if (sTarget != 0) {
		if (m_pNpcList[iNpcH]->m_dwActionTime < 1000) {
			if (m_pGame->iDice(1, 3) == 3) {
				m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_ATTACK;
				m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
				m_pNpcList[iNpcH]->m_iTargetIndex = sTarget;
				m_pNpcList[iNpcH]->m_cTargetType = cTargetType;
				return;
			}
		}
		else {
			m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_ATTACK;
			m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
			m_pNpcList[iNpcH]->m_iTargetIndex = sTarget;
			m_pNpcList[iNpcH]->m_cTargetType = cTargetType;
			return;
		}
	}

	if ((m_pNpcList[iNpcH]->m_bIsMaster) && (m_pGame->iDice(1, 3) == 2)) return;

	if (m_pNpcList[iNpcH]->m_cMoveType == DEF_MOVETYPE_FOLLOW) {
		sX = m_pNpcList[iNpcH]->m_sX;
		sY = m_pNpcList[iNpcH]->m_sY;
		switch (m_pNpcList[iNpcH]->m_cFollowOwnerType) {
		case DEF_OWNERTYPE_PLAYER:
			if (m_pGame->m_pClientList[m_pNpcList[iNpcH]->m_iFollowOwnerIndex] == 0) {
				m_pNpcList[iNpcH]->m_cMoveType = DEF_MOVETYPE_RANDOM;
				return;
			}

			dX = m_pGame->m_pClientList[m_pNpcList[iNpcH]->m_iFollowOwnerIndex]->m_sX;
			dY = m_pGame->m_pClientList[m_pNpcList[iNpcH]->m_iFollowOwnerIndex]->m_sY;
			break;
		case DEF_OWNERTYPE_NPC:
			if (m_pNpcList[m_pNpcList[iNpcH]->m_iFollowOwnerIndex] == 0) {
				m_pNpcList[iNpcH]->m_cMoveType = DEF_MOVETYPE_RANDOM;
				m_pNpcList[iNpcH]->m_iFollowOwnerIndex = 0;
				//bSerchMaster(iNpcH);
				return;
			}

			dX = m_pNpcList[m_pNpcList[iNpcH]->m_iFollowOwnerIndex]->m_sX;
			dY = m_pNpcList[m_pNpcList[iNpcH]->m_iFollowOwnerIndex]->m_sY;
			break;
		}

		if (abs(sX - dX) >= abs(sY - dY))
			sDistance = abs(sX - dX);
		else sDistance = abs(sY - dY);

		if (sDistance >= 3) {
			cDir = m_pGame->cGetNextMoveDir(sX, sY, dX, dY, m_pNpcList[iNpcH]->m_cMapIndex, m_pNpcList[iNpcH]->m_cTurn, &m_pNpcList[iNpcH]->m_tmp_iError);
			if (cDir == 0) {
			}
			else {
				dX = m_pNpcList[iNpcH]->m_sX + _tmp_cTmpDirX[cDir];
				dY = m_pNpcList[iNpcH]->m_sY + _tmp_cTmpDirY[cDir];

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->ClearOwner(3, iNpcH, DEF_OWNERTYPE_NPC, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY);
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->SetOwner(iNpcH, DEF_OWNERTYPE_NPC, dX, dY);
				m_pNpcList[iNpcH]->m_sX = dX;
				m_pNpcList[iNpcH]->m_sY = dY;
				m_pNpcList[iNpcH]->m_cDir = cDir;

				m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTMOVE, 0, 0, 0);
			}
		}
	}
	else
	{
		cDir = m_pGame->cGetNextMoveDir(m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY,
			m_pNpcList[iNpcH]->m_dX, m_pNpcList[iNpcH]->m_dY,
			m_pNpcList[iNpcH]->m_cMapIndex, m_pNpcList[iNpcH]->m_cTurn, &m_pNpcList[iNpcH]->m_tmp_iError);

		if (cDir == 0) {
			if (m_pGame->iDice(1, 10) == 3) CalcNextWayPointDestination(iNpcH);
		}
		else {
			dX = m_pNpcList[iNpcH]->m_sX + _tmp_cTmpDirX[cDir];
			dY = m_pNpcList[iNpcH]->m_sY + _tmp_cTmpDirY[cDir];

			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->ClearOwner(4, iNpcH, DEF_OWNERTYPE_NPC, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY);
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->SetOwner(iNpcH, DEF_OWNERTYPE_NPC, dX, dY);
			m_pNpcList[iNpcH]->m_sX = dX;
			m_pNpcList[iNpcH]->m_sY = dY;
			m_pNpcList[iNpcH]->m_cDir = cDir;

			m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTMOVE, 0, 0, 0);
		}
	}
}

void CEntityManager::TargetSearch(int iNpcH, short* pTarget, char* pTargetType)
{
	int ix, iy, iPKCount;
	short sX, sY, rX, rY, dX, dY;
	short sOwner, sTargetOwner, sDistance, sTempDistance;
	char  cOwnerType, cTargetType, cTargetSide;
	int   iInv;

	sTargetOwner = 0;
	cTargetType = 0;
	sDistance = 100;

	sX = m_pNpcList[iNpcH]->m_sX;
	sY = m_pNpcList[iNpcH]->m_sY;

	rX = m_pNpcList[iNpcH]->m_sX - m_pNpcList[iNpcH]->m_cTargetSearchRange;
	rY = m_pNpcList[iNpcH]->m_sY - m_pNpcList[iNpcH]->m_cTargetSearchRange;

	for (ix = rX; ix < rX + m_pNpcList[iNpcH]->m_cTargetSearchRange * 2 + 1; ix++)
		for (iy = rY; iy < rY + m_pNpcList[iNpcH]->m_cTargetSearchRange * 2 + 1; iy++) {

			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwner, &cOwnerType, ix, iy);
			if (sOwner != 0) {
				if ((sOwner == iNpcH) && (cOwnerType == DEF_OWNERTYPE_NPC)) break; // ÀÚ±â ÀÚ½ÅÀÌ¸é ¹«½Ã 

				iPKCount = 0;
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pGame->m_pClientList[sOwner] == 0) {
						m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->ClearOwner(5, sOwner, DEF_OWNERTYPE_PLAYER, ix, iy);
					}
					else {
						if (m_pGame->m_pClientList[sOwner]->m_iAdminUserLevel > 0) goto SKIP_SEARCH;

						dX = m_pGame->m_pClientList[sOwner]->m_sX;
						dY = m_pGame->m_pClientList[sOwner]->m_sY;
						cTargetSide = m_pGame->m_pClientList[sOwner]->m_cSide;
						iPKCount = m_pGame->m_pClientList[sOwner]->m_iPKCount;
						iInv = m_pGame->m_pClientList[sOwner]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY];
					}
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwner] == 0) {
						m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->ClearOwner(6, sOwner, DEF_OWNERTYPE_NPC, ix, iy);
					}
					else {
						dX = m_pNpcList[sOwner]->m_sX;
						dY = m_pNpcList[sOwner]->m_sY;
						cTargetSide = m_pNpcList[sOwner]->m_cSide;
						iPKCount = 0;
						iInv = m_pNpcList[sOwner]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY];

						if (m_pNpcList[iNpcH]->m_sType == 21) {
							if (m_pGame->_iCalcPlayerNum(m_pNpcList[sOwner]->m_cMapIndex, dX, dY, 2) != 0) {
								sOwner = 0;
								cOwnerType = 0;
							}
						}
					}
					break;
				}

				if (m_pNpcList[iNpcH]->m_cSide < 10) {
					// NPC
					if (cTargetSide == 0) {
						if (iPKCount == 0) goto SKIP_SEARCH;
					}
					else {
						if ((iPKCount == 0) && (cTargetSide == m_pNpcList[iNpcH]->m_cSide)) goto SKIP_SEARCH;
						if (m_pNpcList[iNpcH]->m_cSide == 0) goto SKIP_SEARCH;
					}
				}
				else {
					if ((cOwnerType == DEF_OWNERTYPE_NPC) && (cTargetSide == 0)) goto SKIP_SEARCH;
					if (cTargetSide == m_pNpcList[iNpcH]->m_cSide) goto SKIP_SEARCH;
				}

				if ((iInv != 0) && (m_pNpcList[iNpcH]->m_cSpecialAbility != 1)) goto SKIP_SEARCH;

				if (abs(sX - dX) >= abs(sY - dY))
					sTempDistance = abs(sX - dX);
				else sTempDistance = abs(sY - dY);

				if (sTempDistance < sDistance) {
					sDistance = sTempDistance;
					sTargetOwner = sOwner;
					cTargetType = cOwnerType;
				}
			SKIP_SEARCH:;
			}
		}

	*pTarget = sTargetOwner;
	*pTargetType = cTargetType;
	return;
}

void CEntityManager::NpcBehavior_Attack(int iNpcH)
{
	int   iMagicType;
	short sX, sY, dX, dY;
	char  cDir;
	uint32_t dwTime = GameClock::GetTimeMS();

	if (m_pNpcList[iNpcH] == 0) return;
	if (m_pNpcList[iNpcH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0) return;
	if (m_pNpcList[iNpcH]->m_bIsKilled) return;

	switch (m_pNpcList[iNpcH]->m_cActionLimit) {
	case 1:
	case 2:
	case 3:
	case 4:
		return;

	case 5:
		if (m_pNpcList[iNpcH]->m_iBuildCount > 0) return;
	}

	// v1.432-2
	int iStX, iStY;
	if (m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex] != 0) {
		iStX = m_pNpcList[iNpcH]->m_sX / 20;
		iStY = m_pNpcList[iNpcH]->m_sY / 20;
		m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_stTempSectorInfo[iStX][iStY].iMonsterActivity++;
	}

	if (m_pNpcList[iNpcH]->m_sBehaviorTurnCount == 0)
		m_pNpcList[iNpcH]->m_iAttackCount = 0;

	m_pNpcList[iNpcH]->m_sBehaviorTurnCount++;
	if (m_pNpcList[iNpcH]->m_sBehaviorTurnCount > 20) {
		m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;

		if ((m_pNpcList[iNpcH]->m_bIsPermAttackMode == false))
			m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_MOVE;

		return;
	}

	sX = m_pNpcList[iNpcH]->m_sX;
	sY = m_pNpcList[iNpcH]->m_sY;

	switch (m_pNpcList[iNpcH]->m_cTargetType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pGame->m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex] == 0) {
			m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
			m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_MOVE;
			return;
		}
		dX = m_pGame->m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_sX;
		dY = m_pGame->m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_sY;
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex] == 0) {
			m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
			m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_MOVE;
			return;
		}
		dX = m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_sX;
		dY = m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_sY;
		break;
	}

	if ((m_pGame->iGetDangerValue(iNpcH, dX, dY) > m_pNpcList[iNpcH]->m_cBravery) &&
		(m_pNpcList[iNpcH]->m_bIsPermAttackMode == false) &&
		(m_pNpcList[iNpcH]->m_cActionLimit != 5)) {

		m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
		m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_FLEE;
		return;
	}

	if ((m_pNpcList[iNpcH]->m_iHP <= 2) && (m_pGame->iDice(1, m_pNpcList[iNpcH]->m_cBravery) <= 3) &&
		(m_pNpcList[iNpcH]->m_bIsPermAttackMode == false) &&
		(m_pNpcList[iNpcH]->m_cActionLimit != 5)) {

		m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
		m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_FLEE;
		return;
	}

	if ((abs(sX - dX) <= 1) && (abs(sY - dY) <= 1)) {

		cDir = CMisc::cGetNextMoveDir(sX, sY, dX, dY);
		if (cDir == 0) return;
		m_pNpcList[iNpcH]->m_cDir = cDir;

		if (m_pNpcList[iNpcH]->m_cActionLimit == 5) {
			switch (m_pNpcList[iNpcH]->m_sType) {
			case 89:
				m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, dX, dY, 1);
				m_pNpcList[iNpcH]->m_iMagicHitRatio = 1000;
				NpcMagicHandler(iNpcH, dX, dY, 61);
				break;

			case 87:
				m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, dX, dY, 2);
				m_pGame->iCalculateAttackEffect(m_pNpcList[iNpcH]->m_iTargetIndex, m_pNpcList[iNpcH]->m_cTargetType, iNpcH, DEF_OWNERTYPE_NPC, dX, dY, 2);
				break;

			case 36: // Crossbow Guard Tower: Ȱ ����
				m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, m_pNpcList[iNpcH]->m_sX + _tmp_cTmpDirX[cDir], m_pNpcList[iNpcH]->m_sY + _tmp_cTmpDirY[cDir], 2); // Ȱ
				m_pGame->iCalculateAttackEffect(m_pNpcList[iNpcH]->m_iTargetIndex, m_pNpcList[iNpcH]->m_cTargetType, iNpcH, DEF_OWNERTYPE_NPC, dX, dY, 2, false, false, false);
				break;

			case 37: // Cannon Guard Tower: 
				m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, dX, dY, 1);
				m_pNpcList[iNpcH]->m_iMagicHitRatio = 1000;
				NpcMagicHandler(iNpcH, dX, dY, 61);
				break;
			}
		}
		else {
			m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, m_pNpcList[iNpcH]->m_sX + _tmp_cTmpDirX[cDir], m_pNpcList[iNpcH]->m_sY + _tmp_cTmpDirY[cDir], 1); // 1 : Į���� ��������� �����ϴ� �ǹ� 
			m_pGame->iCalculateAttackEffect(m_pNpcList[iNpcH]->m_iTargetIndex, m_pNpcList[iNpcH]->m_cTargetType, iNpcH, DEF_OWNERTYPE_NPC, dX, dY, 1, false, false); // ���ݿ� ���� ȿ���� ����Ѵ�. 
		}
		m_pNpcList[iNpcH]->m_iAttackCount++;

		if ((m_pNpcList[iNpcH]->m_bIsPermAttackMode == false) && (m_pNpcList[iNpcH]->m_cActionLimit == 0)) {
			switch (m_pNpcList[iNpcH]->m_iAttackStrategy) {
			case DEF_ATTACKAI_EXCHANGEATTACK:
				m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
				m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_FLEE;
				break;

			case DEF_ATTACKAI_TWOBYONEATTACK:
				if (m_pNpcList[iNpcH]->m_iAttackCount >= 2) {
					m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
					m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_FLEE;
				}
				break;
			}
		}
	}
	else {
		cDir = CMisc::cGetNextMoveDir(sX, sY, dX, dY);
		if (cDir == 0) return;
		m_pNpcList[iNpcH]->m_cDir = cDir;

		if ((m_pNpcList[iNpcH]->m_cMagicLevel > 0) && (m_pGame->iDice(1, 2) == 1) &&
			(abs(sX - dX) <= 9) && (abs(sY - dY) <= 7)) {
			iMagicType = -1;
			switch (m_pNpcList[iNpcH]->m_cMagicLevel) {
			case 1:
				if (m_pGame->m_pMagicConfigList[0]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 0;
				break;

			case 2:
				if (m_pGame->m_pMagicConfigList[10]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 10;
				else if (m_pGame->m_pMagicConfigList[0]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 0;
				break;

			case 3: // Orc-Mage
				if (m_pGame->m_pMagicConfigList[20]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 20;
				else if (m_pGame->m_pMagicConfigList[10]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 10;
				break;

			case 4:
				if (m_pGame->m_pMagicConfigList[30]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 30;
				else if (m_pGame->m_pMagicConfigList[37]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 37;
				else if (m_pGame->m_pMagicConfigList[20]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 20;
				else if (m_pGame->m_pMagicConfigList[10]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 10;
				break;

			case 5: // Rudolph, Cannibal-Plant, Cyclops
				if (m_pGame->m_pMagicConfigList[43]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 43;
				else if (m_pGame->m_pMagicConfigList[30]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 30;
				else if (m_pGame->m_pMagicConfigList[37]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 37;
				else if (m_pGame->m_pMagicConfigList[20]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 20;
				else if (m_pGame->m_pMagicConfigList[10]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 10;
				break;

			case 6: // Tentocle, Liche
				if (m_pGame->m_pMagicConfigList[51]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 51;
				else if (m_pGame->m_pMagicConfigList[43]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 43;
				else if (m_pGame->m_pMagicConfigList[30]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 30;
				else if (m_pGame->m_pMagicConfigList[37]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 37;
				else if (m_pGame->m_pMagicConfigList[20]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 20;
				else if (m_pGame->m_pMagicConfigList[10]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 10;
				break;

			case 7: // Barlog, Fire-Wyvern, MasterMage-Orc , LightWarBeatle, GHK, GHKABS, TK, BG
				// Sor, Gagoyle, Demon
				if ((m_pGame->m_pMagicConfigList[70]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana) && (m_pGame->iDice(1, 5) == 3))
					iMagicType = 70;
				else if (m_pGame->m_pMagicConfigList[61]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 61;
				else if (m_pGame->m_pMagicConfigList[60]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 60;
				else if (m_pGame->m_pMagicConfigList[51]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 51;
				else if (m_pGame->m_pMagicConfigList[43]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 43;
				break;

			case 8: // Unicorn, Centaurus
				if ((m_pGame->m_pMagicConfigList[35]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana) && (m_pGame->iDice(1, 3) == 2))
					iMagicType = 35;
				else if (m_pGame->m_pMagicConfigList[60]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 60;
				else if (m_pGame->m_pMagicConfigList[51]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 51;
				else if (m_pGame->m_pMagicConfigList[43]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 43;
				break;

			case 9: // Tigerworm
				if ((m_pGame->m_pMagicConfigList[74]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana) && (m_pGame->iDice(1, 3) == 2))
					iMagicType = 74; // Lightning-Strike
				break;

			case 10: // Frost, Nizie
				break;

			case 11: // Ice-Golem
				break;

			case 12: // Wyvern
				if ((m_pGame->m_pMagicConfigList[91]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana) && (m_pGame->iDice(1, 3) == 2))
					iMagicType = 91; // Blizzard
				else if (m_pGame->m_pMagicConfigList[63]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 63; // Mass-Chill-Wind
				break;

			case 13: // Abaddon
				if ((m_pGame->m_pMagicConfigList[96]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana) && (m_pGame->iDice(1, 3) == 2))
					iMagicType = 96; // Earth Shock Wave
				else if (m_pGame->m_pMagicConfigList[81]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 81; // Metoer Strike
				break;

			}

			if (iMagicType != -1) {

				if (m_pNpcList[iNpcH]->m_iAILevel >= 2) {
					switch (m_pNpcList[iNpcH]->m_cTargetType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pGame->m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] == 2) {
							if ((abs(sX - dX) > m_pNpcList[iNpcH]->m_iAttackRange) || (abs(sY - dY) > m_pNpcList[iNpcH]->m_iAttackRange)) {
								m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
								m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_MOVE;
								return;
							}
							else goto NBA_CHASE;
						}
						if ((iMagicType == 35) && (m_pGame->m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0)) goto NBA_CHASE;
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] == 2) {
							if ((abs(sX - dX) > m_pNpcList[iNpcH]->m_iAttackRange) || (abs(sY - dY) > m_pNpcList[iNpcH]->m_iAttackRange)) {
								m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
								m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_MOVE;
								return;
							}
							else goto NBA_CHASE;
						}
						if ((iMagicType == 35) && (m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0)) goto NBA_CHASE;
						break;
					}
				}

				m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, m_pNpcList[iNpcH]->m_sX + _tmp_cTmpDirX[cDir], m_pNpcList[iNpcH]->m_sY + _tmp_cTmpDirY[cDir], 1); // 1 : Į���� ��������� �����ϴ� �ǹ� 
				NpcMagicHandler(iNpcH, dX, dY, iMagicType);
				m_pNpcList[iNpcH]->m_dwTime = dwTime + 2000;
				return;
			}
		}

		if ((m_pNpcList[iNpcH]->m_cMagicLevel < 0) && (m_pGame->iDice(1, 2) == 1) &&
			(abs(sX - dX) <= 9) && (abs(sY - dY) <= 7)) {
			iMagicType = -1;
			if (m_pGame->m_pMagicConfigList[43]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
				iMagicType = 43;
			else if (m_pGame->m_pMagicConfigList[37]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
				iMagicType = 37;
			else if (m_pGame->m_pMagicConfigList[0]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
				iMagicType = 0;

			if (iMagicType != -1) {
				m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, m_pNpcList[iNpcH]->m_sX + _tmp_cTmpDirX[cDir], m_pNpcList[iNpcH]->m_sY + _tmp_cTmpDirY[cDir], 1); // 1 : Į���� ��������� �����ϴ� �ǹ� 
				NpcMagicHandler(iNpcH, dX, dY, iMagicType);
				m_pNpcList[iNpcH]->m_dwTime = dwTime + 2000;
				return;
			}
		}

		// v1.41
		if ((m_pNpcList[iNpcH]->m_iAttackRange > 1) &&
			(abs(sX - dX) <= m_pNpcList[iNpcH]->m_iAttackRange) && (abs(sY - dY) <= m_pNpcList[iNpcH]->m_iAttackRange)) {

			cDir = CMisc::cGetNextMoveDir(sX, sY, dX, dY);
			if (cDir == 0) return;
			m_pNpcList[iNpcH]->m_cDir = cDir;

			if (m_pNpcList[iNpcH]->m_cActionLimit == 5) {
				switch (m_pNpcList[iNpcH]->m_sType) {
				case 36: // Crossbow Guard Tower
					m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, dX, dY, 2);
					m_pGame->iCalculateAttackEffect(m_pNpcList[iNpcH]->m_iTargetIndex, m_pNpcList[iNpcH]->m_cTargetType, iNpcH, DEF_OWNERTYPE_NPC, dX, dY, 2);
					break;

				case 37: // Cannon Guard Tower
					m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, dX, dY, 1);
					m_pNpcList[iNpcH]->m_iMagicHitRatio = 1000;
					NpcMagicHandler(iNpcH, dX, dY, 61);
					break;
				}
			}
			else {
				switch (m_pNpcList[iNpcH]->m_sType) {
				case 51: // v2.05 Catapult
					m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, dX, dY, 1);
					m_pNpcList[iNpcH]->m_iMagicHitRatio = 1000;
					NpcMagicHandler(iNpcH, dX, dY, 61);
					break;

				case 54: // Dark Elf: Ȱ ������ �Ѵ�.
					m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, dX, dY, 2); // 2: Ȱ���� 
					m_pGame->iCalculateAttackEffect(m_pNpcList[iNpcH]->m_iTargetIndex, m_pNpcList[iNpcH]->m_cTargetType, iNpcH, DEF_OWNERTYPE_NPC, dX, dY, 2);
					break;

				case 63: // Frost
				case 79: // Nizie
					switch (m_pNpcList[iNpcH]->m_cTargetType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pGame->m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex] == 0) goto NBA_BREAK1;
						if ((m_pGame->m_pMagicConfigList[57]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana) && (m_pGame->iDice(1, 3) == 2))
							NpcMagicHandler(iNpcH, dX, dY, 57);
						if ((m_pGame->m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_iHP > 0) &&
							(m_pGame->bCheckResistingIceSuccess(m_pNpcList[iNpcH]->m_cDir, m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_PLAYER, m_pNpcList[iNpcH]->m_iMagicHitRatio) == false)) {
							if (m_pGame->m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pGame->m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
							m_pGame->SetIceFlag(m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_PLAYER, true);
								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (5 * 1000),
									m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_PLAYER, 0, 0, 0, 1, 0, 0);
								m_pGame->SendNotifyMsg(0, m_pNpcList[iNpcH]->m_iTargetIndex, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex] == 0) goto NBA_BREAK1;
						if ((m_pGame->m_pMagicConfigList[57]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana) && (m_pGame->iDice(1, 3) == 2))
							NpcMagicHandler(iNpcH, dX, dY, 57);
						if ((m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_iHP > 0) &&
							(m_pGame->bCheckResistingIceSuccess(m_pNpcList[iNpcH]->m_cDir, m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_NPC, m_pNpcList[iNpcH]->m_iMagicHitRatio) == false)) {
							if (m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
							m_pGame->SetIceFlag(m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_NPC, true);
								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (5 * 1000),
									m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_NPC, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
				case 53: //Beholder
					switch (m_pNpcList[iNpcH]->m_cTargetType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pGame->m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex] == 0) goto NBA_BREAK1;
						if ((m_pGame->m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_iHP > 0) &&
							(m_pGame->bCheckResistingIceSuccess(m_pNpcList[iNpcH]->m_cDir, m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_PLAYER, m_pNpcList[iNpcH]->m_iMagicHitRatio) == false)) {
							if (m_pGame->m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pGame->m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
							m_pGame->SetIceFlag(m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_PLAYER, true);
								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (5 * 1000),
									m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_PLAYER, 0, 0, 0, 1, 0, 0);
								m_pGame->SendNotifyMsg(0, m_pNpcList[iNpcH]->m_iTargetIndex, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex] == 0) goto NBA_BREAK1;
						if ((m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_iHP > 0) &&
							(m_pGame->bCheckResistingIceSuccess(m_pNpcList[iNpcH]->m_cDir, m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_NPC, m_pNpcList[iNpcH]->m_iMagicHitRatio) == false)) {
							if (m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
							m_pGame->SetIceFlag(m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_NPC, true);
								m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (5 * 1000),
									m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_NPC, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
				NBA_BREAK1:
					m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, dX, dY, 20); // 20: �ʻ��
					m_pGame->iCalculateAttackEffect(m_pNpcList[iNpcH]->m_iTargetIndex, m_pNpcList[iNpcH]->m_cTargetType, iNpcH, DEF_OWNERTYPE_NPC, dX, dY, 20);
					break;

				default:
					m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, dX, dY, 20); // 20: �ʻ�� 
					m_pGame->iCalculateAttackEffect(m_pNpcList[iNpcH]->m_iTargetIndex, m_pNpcList[iNpcH]->m_cTargetType, iNpcH, DEF_OWNERTYPE_NPC, dX, dY, 20);
					break;
				}
			}
			m_pNpcList[iNpcH]->m_iAttackCount++;

			if ((m_pNpcList[iNpcH]->m_bIsPermAttackMode == false) && (m_pNpcList[iNpcH]->m_cActionLimit == 0)) {
				switch (m_pNpcList[iNpcH]->m_iAttackStrategy) {
				case DEF_ATTACKAI_EXCHANGEATTACK:
					m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
					m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_FLEE;
					break;

				case DEF_ATTACKAI_TWOBYONEATTACK:
					if (m_pNpcList[iNpcH]->m_iAttackCount >= 2) {
						m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
						m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_FLEE;
					}
					break;
				}
			}
			return;
		}

	NBA_CHASE:

		if (m_pNpcList[iNpcH]->m_cActionLimit != 0) return;

		m_pNpcList[iNpcH]->m_iAttackCount = 0;

		{
			cDir = m_pGame->cGetNextMoveDir(sX, sY, dX, dY, m_pNpcList[iNpcH]->m_cMapIndex, m_pNpcList[iNpcH]->m_cTurn, &m_pNpcList[iNpcH]->m_tmp_iError);
			if (cDir == 0) {
				return;
			}
			dX = m_pNpcList[iNpcH]->m_sX + _tmp_cTmpDirX[cDir];
			dY = m_pNpcList[iNpcH]->m_sY + _tmp_cTmpDirY[cDir];
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->ClearOwner(9, iNpcH, DEF_OWNERTYPE_NPC, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY);
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->SetOwner(iNpcH, DEF_OWNERTYPE_NPC, dX, dY);
			m_pNpcList[iNpcH]->m_sX = dX;
			m_pNpcList[iNpcH]->m_sY = dY;
			m_pNpcList[iNpcH]->m_cDir = cDir;
			m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTMOVE, 0, 0, 0);
		}
	}
}

void CEntityManager::NpcBehavior_Flee(int iNpcH)
{
	char cDir;
	short sX, sY, dX, dY;
	short sTarget;
	char  cTargetType;

	if (m_pNpcList[iNpcH] == 0) return;
	if (m_pNpcList[iNpcH]->m_bIsKilled) return;

	m_pNpcList[iNpcH]->m_sBehaviorTurnCount++;

	switch (m_pNpcList[iNpcH]->m_iAttackStrategy) {
	case DEF_ATTACKAI_EXCHANGEATTACK:
	case DEF_ATTACKAI_TWOBYONEATTACK:
		if (m_pNpcList[iNpcH]->m_sBehaviorTurnCount >= 2) {
			m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_ATTACK;
			m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
			return;
		}
		break;

	default:
		if (m_pGame->iDice(1, 2) == 1) NpcRequestAssistance(iNpcH);
		break;
	}

	if (m_pNpcList[iNpcH]->m_sBehaviorTurnCount > 10) {
		// 10
		m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
		m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_MOVE;
		m_pNpcList[iNpcH]->m_tmp_iError = 0;
		if (m_pNpcList[iNpcH]->m_iHP <= 3) {
			m_pNpcList[iNpcH]->m_iHP += m_pGame->iDice(1, m_pNpcList[iNpcH]->m_iHitDice); // ! ������ �������� ���������� ���������� ���������Ƿ� ������ ����.
			if (m_pNpcList[iNpcH]->m_iHP <= 0) m_pNpcList[iNpcH]->m_iHP = 1;
		}
		return;
	}

	TargetSearch(iNpcH, &sTarget, &cTargetType);
	if (sTarget != 0) {
		m_pNpcList[iNpcH]->m_iTargetIndex = sTarget;
		m_pNpcList[iNpcH]->m_cTargetType = cTargetType;
	}

	sX = m_pNpcList[iNpcH]->m_sX;
	sY = m_pNpcList[iNpcH]->m_sY;
	switch (m_pNpcList[iNpcH]->m_cTargetType) {
	case DEF_OWNERTYPE_PLAYER:
		dX = m_pGame->m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_sX;
		dY = m_pGame->m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_sY;
		break;
	case DEF_OWNERTYPE_NPC:
		dX = m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_sX;
		dY = m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_sY;
		break;
	}
	dX = sX - (dX - sX);
	dY = sY - (dY - sY);

	cDir = m_pGame->cGetNextMoveDir(sX, sY, dX, dY, m_pNpcList[iNpcH]->m_cMapIndex, m_pNpcList[iNpcH]->m_cTurn, &m_pNpcList[iNpcH]->m_tmp_iError);
	if (cDir == 0) {
	}
	else {
		dX = m_pNpcList[iNpcH]->m_sX + _tmp_cTmpDirX[cDir];
		dY = m_pNpcList[iNpcH]->m_sY + _tmp_cTmpDirY[cDir];
		m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->ClearOwner(11, iNpcH, DEF_OWNERTYPE_NPC, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY);
		m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->SetOwner(iNpcH, DEF_OWNERTYPE_NPC, dX, dY);
		m_pNpcList[iNpcH]->m_sX = dX;
		m_pNpcList[iNpcH]->m_sY = dY;
		m_pNpcList[iNpcH]->m_cDir = cDir;
		m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTMOVE, 0, 0, 0);
	}
}

void CEntityManager::NpcBehavior_Stop(int iNpcH)
{
	char  cTargetType;
	short sTarget = 0;
	bool  bFlag;

	if (m_pNpcList[iNpcH] == 0) return;

	m_pNpcList[iNpcH]->m_sBehaviorTurnCount++;

	switch (m_pNpcList[iNpcH]->m_cActionLimit) {
	case 5:
		switch (m_pNpcList[iNpcH]->m_sType) {
		case 38:
			if (m_pNpcList[iNpcH]->m_sBehaviorTurnCount >= 3) {
				m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
				bFlag = _bNpcBehavior_ManaCollector(iNpcH);
				if (bFlag) {
					m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY, 1);
				}
			}
			break;

		case 39: // Detector
			if (m_pNpcList[iNpcH]->m_sBehaviorTurnCount >= 3) {
				m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
				bFlag = _bNpcBehavior_Detector(iNpcH);

				if (bFlag) {
					// ���� �߰��ߴ�. ���� �������� �˷��� �Ѵ�.	
					m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY, 1);
				}
			}
			break;

		case 40: // Energy Shield Generator
			break;

		case 41: // Grand Magic Generator
			if (m_pNpcList[iNpcH]->m_sBehaviorTurnCount >= 3) {
				m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
				_NpcBehavior_GrandMagicGenerator(iNpcH);
			}
			break;

		case 42: // ManaStone: v2.05 ���������� ���������� �������� 5�� �����Ѵ�.
			m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
			m_pNpcList[iNpcH]->m_iV1 += 5;
			if (m_pNpcList[iNpcH]->m_iV1 >= 5) m_pNpcList[iNpcH]->m_iV1 = 5;
			break;

		default:
			TargetSearch(iNpcH, &sTarget, &cTargetType);
			break;
		}
		break;
	}

	if ((sTarget != 0)) {

		// ���ݸ�ǥ �߰�. 
		m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_ATTACK;
		m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
		m_pNpcList[iNpcH]->m_iTargetIndex = sTarget;
		m_pNpcList[iNpcH]->m_cTargetType = cTargetType;
		// ���⼭ ǥȿ ���۰������� ���� �޽��� �߼�. 
		return;
	}
}

void CEntityManager::NpcBehavior_Dead(int iNpcH)
{
	uint32_t dwTime;

	if (m_pNpcList[iNpcH] == 0) return;

	dwTime = GameClock::GetTimeMS();
	m_pNpcList[iNpcH]->m_sBehaviorTurnCount++;
	if (m_pNpcList[iNpcH]->m_sBehaviorTurnCount > 5) {
		m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
	}

	uint32_t dwTimeSinceDeath = dwTime - m_pNpcList[iNpcH]->m_dwDeadTime;
	if (dwTimeSinceDeath > m_pNpcList[iNpcH]->m_dwRegenTime) {
		DeleteEntity(iNpcH);
	}
}

void CEntityManager::CalcNextWayPointDestination(int iNpcH)
{
	short sRange, sX, sY;
	int i, j, iMapIndex;
	bool bFlag;

	switch (m_pNpcList[iNpcH]->m_cMoveType) {
	case DEF_MOVETYPE_GUARD:
		// ÁöÁ¤µÈ À§Ä¡¸¦ ¹þ¾î³ªÁö ¾ÊÀ¸¸ç Ãß°ÝÀÌ ³¡³­ ÈÄ¿¡ µ¹¾Æ¿Â´Ù.
		break;

	case DEF_MOVETYPE_SEQWAYPOINT:

		m_pNpcList[iNpcH]->m_cCurWaypoint++;
		if (m_pNpcList[iNpcH]->m_cCurWaypoint >= m_pNpcList[iNpcH]->m_cTotalWaypoint)
			m_pNpcList[iNpcH]->m_cCurWaypoint = 1;
		m_pNpcList[iNpcH]->m_dX = (short)(m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_WaypointList[m_pNpcList[iNpcH]->m_iWayPointIndex[m_pNpcList[iNpcH]->m_cCurWaypoint]].x);
		m_pNpcList[iNpcH]->m_dY = (short)(m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_WaypointList[m_pNpcList[iNpcH]->m_iWayPointIndex[m_pNpcList[iNpcH]->m_cCurWaypoint]].y);
		break;

	case DEF_MOVETYPE_RANDOMWAYPOINT:

		m_pNpcList[iNpcH]->m_cCurWaypoint = (short)((rand() % (m_pNpcList[iNpcH]->m_cTotalWaypoint - 1)) + 1);
		m_pNpcList[iNpcH]->m_dX = (short)(m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_WaypointList[m_pNpcList[iNpcH]->m_iWayPointIndex[m_pNpcList[iNpcH]->m_cCurWaypoint]].x);
		m_pNpcList[iNpcH]->m_dY = (short)(m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_WaypointList[m_pNpcList[iNpcH]->m_iWayPointIndex[m_pNpcList[iNpcH]->m_cCurWaypoint]].y);
		break;

	case DEF_MOVETYPE_RANDOMAREA:

		sRange = (short)(m_pNpcList[iNpcH]->m_rcRandomArea.right - m_pNpcList[iNpcH]->m_rcRandomArea.left);
		m_pNpcList[iNpcH]->m_dX = (short)((rand() % sRange) + m_pNpcList[iNpcH]->m_rcRandomArea.left);
		sRange = (short)(m_pNpcList[iNpcH]->m_rcRandomArea.bottom - m_pNpcList[iNpcH]->m_rcRandomArea.top);
		m_pNpcList[iNpcH]->m_dY = (short)((rand() % sRange) + m_pNpcList[iNpcH]->m_rcRandomArea.top);
		break;

	case DEF_MOVETYPE_RANDOM:
		// ¿ÏÀü ·£´ý 
		//m_pNpcList[iNpcH]->m_dX = (rand() % (m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_sSizeX - 50)) + 15;
		//m_pNpcList[iNpcH]->m_dY = (rand() % (m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_sSizeY - 50)) + 15;
		iMapIndex = m_pNpcList[iNpcH]->m_cMapIndex;

		for (i = 0; i <= 30; i++) {
			// °¥ ¼ö ÀÖ´Â ÁÂÇ¥°¡ ³ª¿Ã¶§ ±îÁö 30¹ø ¹Ýº¹ 
			sX = (rand() % (m_pMapList[iMapIndex]->m_sSizeX - 50)) + 15;
			sY = (rand() % (m_pMapList[iMapIndex]->m_sSizeY - 50)) + 15;

			bFlag = true;
			for (j = 0; j < DEF_MAXMGAR; j++)
				if (m_pMapList[iMapIndex]->m_rcMobGenAvoidRect[j].left != -1) {
					// ÇÇÇØ¾ß ÇÒ ÁÂÇ¥°¡ ÀÖ´Ù. 
					if ((sX >= m_pMapList[iMapIndex]->m_rcMobGenAvoidRect[j].left) &&
						(sX <= m_pMapList[iMapIndex]->m_rcMobGenAvoidRect[j].right) &&
						(sY >= m_pMapList[iMapIndex]->m_rcMobGenAvoidRect[j].top) &&
						(sY <= m_pMapList[iMapIndex]->m_rcMobGenAvoidRect[j].bottom)) {
						// Avoid Rect¾ÈÀÌ¹Ç·Î ÀÌ À§Ä¡¿¡´Â »ý¼º½ÃÅ³ ¼ö ¾ø´Ù.	
						bFlag = false;
					}
				}
			if (bFlag) goto CNW_GET_VALIDLOC_SUCCESS;
		}
		// Fail! 
		m_pNpcList[iNpcH]->m_tmp_iError = 0;
		return;

	CNW_GET_VALIDLOC_SUCCESS:
		m_pNpcList[iNpcH]->m_dX = sX;
		m_pNpcList[iNpcH]->m_dY = sY;
		break;
	}

	m_pNpcList[iNpcH]->m_tmp_iError = 0; // @@@ !!! @@@
}

void CEntityManager::NpcMagicHandler(int iNpcH, short dX, short dY, short sType)
{
	short  sOwnerH;
	char   cOwnerType;
	int i, iErr, ix, iy, sX, sY, tX, tY, iResult, iWhetherBonus, iMagicAttr;
	uint32_t  dwTime = GameClock::GetTimeMS();

	if (m_pNpcList[iNpcH] == 0) return;
	if ((dX < 0) || (dX >= m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_sSizeX) ||
		(dY < 0) || (dY >= m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_sSizeY)) return;

	if ((sType < 0) || (sType >= 100))     return;
	if (m_pGame->m_pMagicConfigList[sType] == 0) return;

	// ������ġ�� ���� �Ұ��� ���̶�� ���� �Ұ��� 
	if (m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_bIsAttackEnabled == false) return;

	// ���� �� ���� ���߷� �Է� 
	iResult = m_pNpcList[iNpcH]->m_iMagicHitRatio;

	// ������ ���� ���� ���ݷ� ����  
	iWhetherBonus = m_pGame->iGetWhetherMagicBonusEffect(sType, m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_cWhetherStatus);

	// v1.41 ���� �Ӽ� 
	iMagicAttr = m_pGame->m_pMagicConfigList[sType]->m_iAttribute;

	if (m_pGame->m_pMagicConfigList[sType]->m_dwDelayTime == 0) {
		// ��� ȿ���� ���� ���� 
		switch (m_pGame->m_pMagicConfigList[sType]->m_sType) {
		case DEF_MAGICTYPE_INVISIBILITY:
			switch (m_pGame->m_pMagicConfigList[sType]->m_sValue4) {
			case 1:
				// ������ �ʴ� ���·� �����. 
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);

				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pGame->m_pClientList[sOwnerH] == 0) goto NMH_NOEFFECT;
					if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) goto NMH_NOEFFECT;
					m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
					m_pGame->SetInvisibilityFlag(sOwnerH, cOwnerType, true);
					// �� ĳ���͸� �����ϰ� �ִ� ���͸� ������Ų��.
					m_pGame->RemoveFromTarget(sOwnerH, DEF_OWNERTYPE_PLAYER);
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) goto NMH_NOEFFECT;
					if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) goto NMH_NOEFFECT;
					m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
					m_pGame->SetInvisibilityFlag(sOwnerH, cOwnerType, true);
					// �� NPC�� �����ϰ� �ִ� ���͸� ������Ų��.
					m_pGame->RemoveFromTarget(sOwnerH, DEF_OWNERTYPE_NPC);
					break;
				}

				// ȿ���� ������ �� �߻��� ������ �̺�Ʈ�� ����Ѵ�.
				m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_INVISIBILITY, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000),
					sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				if (cOwnerType == DEF_OWNERTYPE_PLAYER)
					m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_INVISIBILITY, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);
				break;

			case 2:
				// dX, dY �ݰ� 8 �ֺ��� Invisibility ������ Object�� ������ ���� ��Ų��.
				for (ix = dX - 8; ix <= dX + 8; ix++)
					for (iy = dY - 8; iy <= dY + 8; iy++) {
						m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
						if (sOwnerH != 0) {
							switch (cOwnerType) {
							case DEF_OWNERTYPE_PLAYER:
								if (m_pGame->m_pClientList[sOwnerH] == 0) goto NMH_NOEFFECT;
								if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) {
									if (m_pGame->m_pClientList[sOwnerH]->m_sType != 66) {
										m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = 0;
										m_pGame->SetInvisibilityFlag(sOwnerH, cOwnerType, false);
										m_pGame->bRemoveFromDelayEventList(sOwnerH, cOwnerType, DEF_MAGICTYPE_INVISIBILITY);
									}
								}
								break;

							case DEF_OWNERTYPE_NPC:
								if (m_pNpcList[sOwnerH] == 0) goto NMH_NOEFFECT;
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) {
									if (m_pGame->m_pClientList[sOwnerH]->m_sType != 66) {
										m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = 0;
										m_pGame->SetInvisibilityFlag(sOwnerH, cOwnerType, false);
										m_pGame->bRemoveFromDelayEventList(sOwnerH, cOwnerType, DEF_MAGICTYPE_INVISIBILITY);
									}
								}
								break;
							}
						}
					}
				break;
			}
			break;

		case DEF_MAGICTYPE_HOLDOBJECT:
			// ������Ʈ�� �������� �����Ѵ�. 
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {

				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pGame->m_pClientList[sOwnerH] == 0) goto NMH_NOEFFECT;
					if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0) goto NMH_NOEFFECT;
					if (m_pGame->m_pClientList[sOwnerH]->m_iAddPR >= 500) goto NMH_NOEFFECT;
					m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) goto NMH_NOEFFECT;
					if (m_pNpcList[sOwnerH]->m_cMagicLevel >= 6) goto NMH_NOEFFECT; // v1.4 ���� ���� 6�̻��� ��ġ�� �̻��� ���� ���Ϳ��Դ� ���� ���� ������ �ʴ´�.
					if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0) goto NMH_NOEFFECT;
					m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] = (char)m_pGame->m_pMagicConfigList[sType]->m_sValue4;
					break;
				}

				// ���� ȿ���� ������ �� �߻��� ������ �̺�Ʈ�� ����Ѵ�.
				m_pGame->bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_HOLDOBJECT, dwTime + (m_pGame->m_pMagicConfigList[sType]->m_dwLastTime * 1000),
					sOwnerH, cOwnerType, 0, 0, 0, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				// ȿ���� �������� �˷��ش�.
				if (cOwnerType == DEF_OWNERTYPE_PLAYER)
					m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_HOLDOBJECT, m_pGame->m_pMagicConfigList[sType]->m_sValue4, 0, 0);
			}
			break;


		case DEF_MAGICTYPE_DAMAGE_LINEAR:
			// ������ �� �ִ� ��ǥ�� ��� �����Ѵ�.
			sX = m_pNpcList[iNpcH]->m_sX;
			sY = m_pNpcList[iNpcH]->m_sY;

			for (i = 2; i < 10; i++) {
				iErr = 0;
				CMisc::GetPoint2(sX, sY, dX, dY, &tX, &tY, &iErr, i);

				// tx, ty
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY);
				if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// ���� ô�ϰ� �ִ� �÷��̾��.
					if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				// tx-1, ty
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// ���� ô�ϰ� �ִ� �÷��̾��.
					if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				// tx+1, ty
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// ���� ô�ϰ� �ִ� �÷��̾��.
					if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				// tx, ty-1
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// ���� ô�ϰ� �ִ� �÷��̾��.
					if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				// tx, ty+1
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
					(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
					// ���� ô�ϰ� �ִ� �÷��̾��.
					if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				if ((abs(tX - dX) <= 1) && (abs(tY - dY) <= 1)) break;
			}

			// �ֺ� ���� ȿ�� 
			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// �ڽŵ� ������ �� ������ ����.
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
						(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
						// ���� ô�ϰ� �ִ� �÷��̾��.
						if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
							m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					}
				}

			// dX, dY
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);

			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
				(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
				// ���� ô�ϰ� �ִ� �÷��̾��.
				if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);
			}
			break;

		case DEF_MAGICTYPE_DAMAGE_SPOT:
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);

			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
				(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
				// ���� ô�ϰ� �ִ� �÷��̾��.
				if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
			}
			break;

		case DEF_MAGICTYPE_HPUP_SPOT:
			// �� ������ ���߷����� ����� ����.
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			m_pGame->Effect_HpUp_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6);
			break;

		case DEF_MAGICTYPE_DAMAGE_AREA:
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);

			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
				(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
				// ���� ô�ϰ� �ִ� �÷��̾��.
				if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					m_pGame->Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
			}

			// �ֺ� ���� ȿ�� 
			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// �ڽŵ� ������ �� ������ ����.
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
						(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
						// ���� ô�ϰ� �ִ� �÷��̾��.
						if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
							m_pGame->Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					}
				}
			break;

		case DEF_MAGICTYPE_DAMAGE_AREA_NOSPOT:
			// ������ ������� �ʴ´�.			
			// �ֺ� ���� ȿ�� 
			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// �ڽŵ� ������ �� ������ ����.
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pGame->m_pClientList[sOwnerH] != 0) &&
						(m_pGame->m_pClientList[sOwnerH]->m_iHP > 0)) {
						// ���� ô�ϰ� �ִ� �÷��̾��.
						if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
							m_pGame->Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, dX, dY, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					}
				}
			break;

		case DEF_MAGICTYPE_SPDOWN_AREA:
			// Sp�� �پ���.
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				m_pGame->Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6);
			// �ֺ� ���� ȿ�� 
			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// �ڽŵ� ������ �� ������ ����.
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (m_pGame->bCheckResistingMagicSuccess(m_pNpcList[iNpcH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						m_pGame->Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
				}
			break;

		case DEF_MAGICTYPE_SPUP_AREA:
			// Sp�� ����Ѵ�.
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			// ���� ������ �ʿ����. 
			m_pGame->Effect_SpUp_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue4, m_pGame->m_pMagicConfigList[sType]->m_sValue5, m_pGame->m_pMagicConfigList[sType]->m_sValue6);
			// �ֺ� ���� ȿ�� 
			for (iy = dY - m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pGame->m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pGame->m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// �ڽŵ� ������ �� ������ ����.
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					// ���������� �ʿ� ����.
					m_pGame->Effect_SpUp_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pGame->m_pMagicConfigList[sType]->m_sValue7, m_pGame->m_pMagicConfigList[sType]->m_sValue8, m_pGame->m_pMagicConfigList[sType]->m_sValue9);
				}
			break;

		}
	}
	else {
		// Casting �� �����̰� �ɸ��� ����

	}

NMH_NOEFFECT:

	// Mana�� ���ҽ�Ų��.
	m_pNpcList[iNpcH]->m_iMana -= m_pGame->m_pMagicConfigList[sType]->m_sValue1; // sValue1�� Mana Cost
	if (m_pNpcList[iNpcH]->m_iMana < 0)
		m_pNpcList[iNpcH]->m_iMana = 0;

	// ���� ȿ���� �ٸ� Ŭ���̾�Ʈ���� �����Ѵ�. ������ȣ + 100�� ����Ʈ ��ȣ 
	m_pGame->SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pNpcList[iNpcH]->m_cMapIndex,
		m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY, dX, dY, (sType + 100), m_pNpcList[iNpcH]->m_sType);

}

int CEntityManager::iGetNpcRelationship(int iWhatH, int iRecvH)
{
	int iRet;

	if (m_pGame->m_pClientList[iRecvH] == 0) return 0;
	if (m_pNpcList[iWhatH] == 0) return 0;

	iRet = 0;
	switch (m_pNpcList[iWhatH]->m_cSide) {
	case 10: iRet |= 8; //Fixed, Original 15 
	case 1:  iRet = (iRet | 4) | 2; //Fixed, Original 1 
	case 2:  iRet |= 4; //Fixed, Orignal 8 
	}

	return iRet;
}

int CEntityManager::iGetNpcRelationship_SendEvent(int iNpcH, int iOpponentH)
{
	int iRet;

	if (m_pGame->m_pClientList[iOpponentH] == 0) return 0;
	if (m_pGame->m_pClientList[iOpponentH]->m_bIsInitComplete == false) return 0;

	if (m_pNpcList[iNpcH] == 0) return 0;

	iRet = 0;

	if (m_pGame->m_pClientList[iOpponentH]->m_iPKCount != 0) {
		if (m_pNpcList[iNpcH]->m_cSide == m_pGame->m_pClientList[iOpponentH]->m_cSide)
			iRet = 7;
		else iRet = 2;
	}
	else {
		if (m_pNpcList[iNpcH]->m_cSide != m_pGame->m_pClientList[iOpponentH]->m_cSide) {
			if (m_pNpcList[iNpcH]->m_cSide == 10)
				iRet = 2;
			else
				if (m_pNpcList[iNpcH]->m_cSide == 0) iRet = 0;
				else
					if (m_pGame->m_pClientList[iOpponentH]->m_cSide == 0)
						iRet = 0;
					else iRet = 2;

		}
		else iRet = 1; // °°Àº Æí 
	}

	return iRet;
}

void CEntityManager::NpcRequestAssistance(int iNpcH)
{
	int ix, iy, sX, sY;
	short sOwnerH;
	char  cOwnerType;

	// iNpc ±Ù¹æ¿¡ ÀÖ´Â ÀüÅõÁßÀÌ ¾Æ´Ñ NPC¿¡°Ô µµ¿òÀ» ¿äÃ»ÇÑ´Ù. 
	if (m_pNpcList[iNpcH] == 0) return;

	sX = m_pNpcList[iNpcH]->m_sX;
	sY = m_pNpcList[iNpcH]->m_sY;

	for (ix = sX - 8; ix <= sX + 8; ix++)
		for (iy = sY - 8; iy <= sY + 8; iy++) {
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
			if ((sOwnerH != 0) && (m_pNpcList[sOwnerH] != 0) && (cOwnerType == DEF_OWNERTYPE_NPC) &&
				(iNpcH != sOwnerH) && (m_pNpcList[sOwnerH]->m_cSide == m_pNpcList[iNpcH]->m_cSide) &&
				(m_pNpcList[sOwnerH]->m_bIsPermAttackMode == false) && (m_pNpcList[sOwnerH]->m_cBehavior == DEF_BEHAVIOR_MOVE)) {

				// Á¶°Ç¿¡ ºÎÇÕÇÏ´Â NPC¸¦ Ã£¾Ò´Ù. 
				m_pNpcList[sOwnerH]->m_cBehavior = DEF_BEHAVIOR_ATTACK;
				m_pNpcList[sOwnerH]->m_sBehaviorTurnCount = 0;
				m_pNpcList[sOwnerH]->m_iTargetIndex = m_pNpcList[iNpcH]->m_iTargetIndex;
				m_pNpcList[sOwnerH]->m_cTargetType = m_pNpcList[iNpcH]->m_cTargetType;

				return;
			}
		}
}

bool CEntityManager::_bNpcBehavior_ManaCollector(int iNpcH)
{
	int dX, dY, iMaxMP, iTotal;
	short sOwnerH;
	char  cOwnerType;
	double dV1, dV2, dV3;
	bool bRet;

	if (m_pNpcList[iNpcH] == 0) return false;
	if (m_pNpcList[iNpcH]->m_sAppr2 != 0) return false;

	bRet = false;
	for (dX = m_pNpcList[iNpcH]->m_sX - 5; dX <= m_pNpcList[iNpcH]->m_sX + 5; dX++)
		for (dY = m_pNpcList[iNpcH]->m_sY - 5; dY <= m_pNpcList[iNpcH]->m_sY + 5; dY++) {
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (sOwnerH != 0) {
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pNpcList[iNpcH]->m_cSide == m_pGame->m_pClientList[sOwnerH]->m_cSide) {
						iMaxMP = m_pGame->iGetMaxMP(sOwnerH);
						if (m_pGame->m_pClientList[sOwnerH]->m_iMP < iMaxMP) {
							iTotal = m_pGame->iDice(1, (m_pGame->m_pClientList[sOwnerH]->m_iMag + m_pGame->m_pClientList[sOwnerH]->m_iAngelicMag));
							if (m_pGame->m_pClientList[sOwnerH]->m_iAddMP != 0) {
								dV2 = (double)iTotal;
								dV3 = (double)m_pGame->m_pClientList[sOwnerH]->m_iAddMP;
								dV1 = (dV3 / 100.0f) * dV2;
								iTotal += (int)dV1;
							}

							m_pGame->m_pClientList[sOwnerH]->m_iMP += iTotal;

							if (m_pGame->m_pClientList[sOwnerH]->m_iMP > iMaxMP)
								m_pGame->m_pClientList[sOwnerH]->m_iMP = iMaxMP;

							m_pGame->SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MP, 0, 0, 0, 0);
						}
					}
					break;

				case DEF_OWNERTYPE_NPC:
					if ((m_pNpcList[sOwnerH]->m_sType == 42) && (m_pNpcList[sOwnerH]->m_iV1 > 0)) {
						if (m_pNpcList[sOwnerH]->m_iV1 >= 3) {
							m_pGame->m_iCollectedMana[m_pNpcList[iNpcH]->m_cSide] += 3;
							m_pNpcList[sOwnerH]->m_iV1 -= 3;
							bRet = true;
						}
						else {
							m_pGame->m_iCollectedMana[m_pNpcList[iNpcH]->m_cSide] += m_pNpcList[sOwnerH]->m_iV1;
							m_pNpcList[sOwnerH]->m_iV1 = 0;
							bRet = true;
						}
					}
					break;
				}
			}
	}
	return bRet;
}

void CEntityManager::_NpcBehavior_GrandMagicGenerator(int iNpcH)
{
	switch (m_pNpcList[iNpcH]->m_cSide) {
	case 1:
		if (m_pGame->m_iAresdenMana > DEF_GMGMANACONSUMEUNIT) {
			m_pGame->m_iAresdenMana = 0;
			m_pNpcList[iNpcH]->m_iManaStock++;
			if (m_pNpcList[iNpcH]->m_iManaStock > m_pNpcList[iNpcH]->m_iMaxMana) {
				m_pGame->_GrandMagicLaunchMsgSend(1, 1);
				m_pGame->MeteorStrikeMsgHandler(1);
				m_pNpcList[iNpcH]->m_iManaStock = 0;
				m_pGame->m_iAresdenMana = 0;
			}
			std::snprintf(G_cTxt, sizeof(G_cTxt), "(!) Aresden GMG %d/%d", m_pNpcList[iNpcH]->m_iManaStock, m_pNpcList[iNpcH]->m_iMaxMana);
			PutLogList(G_cTxt);
		}
		break;

	case 2:
		if (m_pGame->m_iElvineMana > DEF_GMGMANACONSUMEUNIT) {
			m_pGame->m_iElvineMana = 0;
			m_pNpcList[iNpcH]->m_iManaStock++;
			if (m_pNpcList[iNpcH]->m_iManaStock > m_pNpcList[iNpcH]->m_iMaxMana) {
				m_pGame->_GrandMagicLaunchMsgSend(1, 2);
				m_pGame->MeteorStrikeMsgHandler(2);
				m_pNpcList[iNpcH]->m_iManaStock = 0;
				m_pGame->m_iElvineMana = 0;
			}
			std::snprintf(G_cTxt, sizeof(G_cTxt), "(!) Elvine GMG %d/%d", m_pNpcList[iNpcH]->m_iManaStock, m_pNpcList[iNpcH]->m_iMaxMana);
			PutLogList(G_cTxt);
		}
		break;
	}
}

bool CEntityManager::_bNpcBehavior_Detector(int iNpcH)
{
	int dX, dY;
	short sOwnerH;
	char  cOwnerType, cSide;
	bool  bFlag = false;

	if (m_pNpcList[iNpcH] == 0) return false;
	if (m_pNpcList[iNpcH]->m_sAppr2 != 0) return false;

	for (dX = m_pNpcList[iNpcH]->m_sX - 10; dX <= m_pNpcList[iNpcH]->m_sX + 10; dX++)
		for (dY = m_pNpcList[iNpcH]->m_sY - 10; dY <= m_pNpcList[iNpcH]->m_sY + 10; dY++) {
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);

			cSide = 0;
			if (sOwnerH != 0) {
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					cSide = m_pGame->m_pClientList[sOwnerH]->m_cSide;
					break;

				case DEF_OWNERTYPE_NPC:
					cSide = m_pNpcList[sOwnerH]->m_cSide;
					break;
				}
			}

			if ((cSide != 0) && (cSide != m_pNpcList[iNpcH]->m_cSide)) {
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) {
						m_pGame->m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = 0;
						m_pGame->SetInvisibilityFlag(sOwnerH, cOwnerType, false);
					}
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) {
						m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = 0;
						m_pGame->SetInvisibilityFlag(sOwnerH, cOwnerType, false);
					}
					break;
				}

				bFlag = true;
			}
		}

	return bFlag;
}



// ========================================================================
// NPC Spawns & Drops (ported from CGame)
// ========================================================================

bool CEntityManager::bSetNpcFollowMode(char* pName, char* pFollowName, char cFollowOwnerType)
{
	int i, iIndex, iMapIndex, iFollowIndex;
	char cTmpName[11], cFollowSide;

	std::memset(cTmpName, 0, sizeof(cTmpName));
	iMapIndex = -1;
	iFollowIndex = -1;

	for (i = 1; i < DEF_MAXNPCS; i++)
		if ((m_pNpcList[i] != 0) && (memcmp(m_pNpcList[i]->m_cName, pName, 5) == 0)) {
			iIndex = i;
			iMapIndex = m_pNpcList[i]->m_cMapIndex;
			goto NEXT_STEP_SNFM1;
		}

NEXT_STEP_SNFM1:

	switch (cFollowOwnerType) {
	case DEF_OWNERTYPE_NPC:
		for (i = 1; i < DEF_MAXNPCS; i++)
			if ((m_pNpcList[i] != 0) && (memcmp(m_pNpcList[i]->m_cName, pFollowName, 5) == 0)) {
				if (m_pNpcList[i]->m_cMapIndex != iMapIndex) return false;
				iFollowIndex = i;
				cFollowSide = m_pNpcList[i]->m_cSide;
				goto NEXT_STEP_SNFM2;
			}
		break;

	case DEF_OWNERTYPE_PLAYER:
		for (i = 1; i < DEF_MAXCLIENTS; i++)
			if ((m_pGame->m_pClientList[i] != 0) && (memcmp(m_pGame->m_pClientList[i]->m_cCharName, pFollowName, 10) == 0)) {
				if (m_pGame->m_pClientList[i]->m_cMapIndex != iMapIndex) return false;
				iFollowIndex = i;
				cFollowSide = m_pGame->m_pClientList[i]->m_cSide;
				goto NEXT_STEP_SNFM2;
			}
		break;
	}

NEXT_STEP_SNFM2:

	if ((iIndex == -1) || (iFollowIndex == -1)) return false;

	m_pNpcList[iIndex]->m_cMoveType = DEF_MOVETYPE_FOLLOW;
	m_pNpcList[iIndex]->m_cFollowOwnerType = cFollowOwnerType;
	m_pNpcList[iIndex]->m_iFollowOwnerIndex = iFollowIndex;
	m_pNpcList[iIndex]->m_cSide = cFollowSide;


	return true;
}

void CEntityManager::bSetNpcAttackMode(char* cName, int iTargetH, char cTargetType, bool bIsPermAttack)
{
	int i, iIndex;

	for (i = 1; i < DEF_MAXNPCS; i++)
		if ((m_pNpcList[i] != 0) && (memcmp(m_pNpcList[i]->m_cName, cName, 5) == 0)) {
			iIndex = i;
			goto NEXT_STEP_SNAM1;

			//testcode
			//PutLogList("bSetNpcAttackMode - Npc found");
		}
	// °°Àº ÀÌ¸§À» °¡Áø NPC°¡ ¾ø´Ù.
	return;

NEXT_STEP_SNAM1:

	switch (cTargetType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pGame->m_pClientList[iTargetH] == 0) return;
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[iTargetH] == 0) return;
		break;
	}

	// ¸ñÇ¥¹°À» ÇÒ´çÇÑ´Ù. 
	m_pNpcList[iIndex]->m_cBehavior = DEF_BEHAVIOR_ATTACK;
	m_pNpcList[iIndex]->m_sBehaviorTurnCount = 0;
	m_pNpcList[iIndex]->m_iTargetIndex = iTargetH;
	m_pNpcList[iIndex]->m_cTargetType = cTargetType;

	// ¿µ±¸ °ø°Ý ¸ðµå ¿©ºÎ ¼³Á¤ 
	m_pNpcList[iIndex]->m_bIsPermAttackMode = bIsPermAttack;

	//testcode
	//PutLogList("bSetNpcAttackMode - complete");
}

void CEntityManager::DeleteNpcInternal(int iNpcH)
{
	int  i, iNamingValue;
	char cTmp[21];
	uint32_t dwTime;
	if (m_pNpcList[iNpcH] == 0) return;

	dwTime = GameClock::GetTimeMS();


	//ì£½ì–´ìžˆë˜ ìœ„ì¹˜ì—ì„œ ì‚­ì œ 
	m_pGame->SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_LOG, DEF_MSGTYPE_REJECT, 0, 0, 0);
	m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->ClearOwner(11, iNpcH, DEF_OWNERTYPE_NPC, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY);

	std::memset(cTmp, 0, sizeof(cTmp));
	strcpy(cTmp, (char*)(m_pNpcList[iNpcH]->m_cName + 2));
	// NPCì˜ NamigValueë¥¼ ì–»ì–´ì™€ ì‚¬ìš©ì¤‘ì¸ í‘œì‹œë¥¼ í•´ì§€í•œë‹¤.
	iNamingValue = atoi(cTmp);

	// NamingValueë¥¼ ë¹„ìš°ê³  ë™ìž‘ì¤‘ì¸ ê°œì²´ ìˆ˜ë¥¼ ê°ì†Œì‹œí‚¨ë‹¤.
	m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->SetNamingValueEmpty(iNamingValue);
	m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_iTotalActiveObject--;

	// Spot-mob-generatorì •ë³´ 
	if (m_pNpcList[iNpcH]->m_iSpotMobIndex != 0) {
		int iSpotIdx = m_pNpcList[iNpcH]->m_iSpotMobIndex;
		int iMapIdx = m_pNpcList[iNpcH]->m_cMapIndex;
		m_pMapList[iMapIdx]->m_stSpotMobGenerator[iSpotIdx].iCurMobs--;
	}

	m_pGame->RemoveFromTarget(iNpcH, DEF_OWNERTYPE_NPC);

	// í¬ë£¨ì„¸ì´ë“œìš© ê±´ì¶•ë¬¼ì´ë¼ë©´ ì§€íœ˜ê´€ í†µë³´ìš© ê±´ì¶•ë¬¼ ë¦¬ìŠ¤íŠ¸ë¥¼ í•´ì œ
	switch (m_pNpcList[iNpcH]->m_sType) {
	case 36:
	case 37:
	case 38:
	case 39:
	case 42:
		m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->bRemoveCrusadeStructureInfo(m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY);
		// ê¸¸ë“œ ê±´ì¶•ë¬¼ ê°œìˆ˜ë„ ê°ì†Œì‹œí‚´ 
		for (i = 0; i < DEF_MAXGUILDS; i++)
			if (m_pGame->m_pGuildTeleportLoc[i].m_iV1 == m_pNpcList[iNpcH]->m_iGuildGUID) {
				m_pGame->m_pGuildTeleportLoc[i].m_dwTime = dwTime;
				m_pGame->m_pGuildTeleportLoc[i].m_iV2--;
				if (m_pGame->m_pGuildTeleportLoc[i].m_iV2 < 0) m_pGame->m_pGuildTeleportLoc[i].m_iV2 = 0;
				break;
			}
		break;
	case 64: m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->bRemoveCropsTotalSum(); break;

	}

	// DelayEventë¥¼ ì‚­ì œ 
	m_pGame->bRemoveFromDelayEventList(iNpcH, DEF_OWNERTYPE_NPC, 0);
	delete m_pNpcList[iNpcH];
	m_pNpcList[iNpcH] = 0;
}

void CEntityManager::NpcDeadItemGenerator(int iNpcH, short sAttackerH, char cAttackerType)
{
	if (m_pNpcList[iNpcH] == 0) return;
	if ((cAttackerType != DEF_OWNERTYPE_PLAYER) || (m_pNpcList[iNpcH]->m_bIsSummoned)) return;
	if (m_pNpcList[iNpcH]->m_bIsUnsummoned) return;

	switch (m_pNpcList[iNpcH]->m_sType) {
	case 21: // Guard
	case 34: // Dummy
	case 64: // Crop
		return;
	}

	const DropTable* table = m_pGame->GetDropTable(m_pNpcList[iNpcH]->m_iDropTableId);
	if (m_pGame->iDice(1, 10000) < static_cast<uint32_t>(m_pGame->m_iPrimaryDropRate)) {
		return;
	}

	bool droppedGold = false;
	if (m_pGame->iDice(1, 10000) <= 6000) {
		int minGold = static_cast<int>(m_pNpcList[iNpcH]->m_iGoldDiceMin);
		int maxGold = static_cast<int>(m_pNpcList[iNpcH]->m_iGoldDiceMax);
		if (minGold < 0) minGold = 0;
		if (maxGold < minGold) maxGold = minGold;
		if (maxGold > 0) {
			int amount = minGold;
			if (maxGold > minGold) {
				amount = m_pGame->iDice(1, (maxGold - minGold)) + minGold;
			}
			if (amount > 0) {
				if ((cAttackerType == DEF_OWNERTYPE_PLAYER) &&
					(m_pGame->m_pClientList[sAttackerH] != nullptr) &&
					(m_pGame->m_pClientList[sAttackerH]->m_iAddGold != 0)) {
					double bonus = (double)m_pGame->m_pClientList[sAttackerH]->m_iAddGold;
					amount += static_cast<int>((bonus / 100.0f) * static_cast<double>(amount));
				}
				SpawnNpcDropItem(iNpcH, 90, amount, amount);
				droppedGold = true;
			}
		}
	}

	if (!droppedGold && table != nullptr) {
		int minCount = 1;
		int maxCount = 1;
		int itemId = RollDropTableItem(table, 1, minCount, maxCount);
		if (itemId != 0) {
			if (itemId == 90) {
				minCount = static_cast<int>(m_pNpcList[iNpcH]->m_iGoldDiceMin);
				maxCount = static_cast<int>(m_pNpcList[iNpcH]->m_iGoldDiceMax);
			}
			SpawnNpcDropItem(iNpcH, itemId, minCount, maxCount);
		}
	}

	if (table != nullptr) {
		double dTmp1 = 0.0f;
		double dTmp2 = 0.0f;
		if (m_pGame->m_pClientList[sAttackerH] != nullptr) {
			dTmp1 = m_pGame->m_pClientList[sAttackerH]->m_iRating * m_pGame->m_cRepDropModifier;
			if (dTmp1 > 1000) dTmp1 = 1000;
			if (dTmp1 < -1000) dTmp1 = -1000;
			dTmp2 = (m_pGame->m_iSecondaryDropRate - (dTmp1));
		} else {
			dTmp2 = m_pGame->m_iSecondaryDropRate;
		}

		if (m_pGame->iDice(1, 10000) <= dTmp2) {
			int minCount = 1;
			int maxCount = 1;
			int itemId = RollDropTableItem(table, 2, minCount, maxCount);
			if (itemId != 0) {
				if (itemId == 90) {
					minCount = static_cast<int>(m_pNpcList[iNpcH]->m_iGoldDiceMin);
					maxCount = static_cast<int>(m_pNpcList[iNpcH]->m_iGoldDiceMax);
				}
				SpawnNpcDropItem(iNpcH, itemId, minCount, maxCount);
			}
		}
	}
}

int CEntityManager::RollDropTableItem(const DropTable* table, int tier, int& outMinCount, int& outMaxCount) const
{
	if (table == nullptr) return 0;
	if (tier < 1 || tier > 2) return 0;
	int total = table->totalWeight[tier];
	if (total <= 0) return 0;
	int roll = m_pGame->iDice(1, total);
	int cumulative = 0;
	for (const auto& entry : table->tierEntries[tier]) {
		cumulative += entry.weight;
		if (roll <= cumulative) {
			outMinCount = entry.minCount;
			outMaxCount = entry.maxCount;
			return entry.itemId;
		}
	}
	return 0;
}

bool CEntityManager::SpawnNpcDropItem(int iNpcH, int itemId, int minCount, int maxCount)
{
	if (itemId <= 0) return false;
	if (m_pNpcList[iNpcH] == 0) return false;

	if (minCount < 0) minCount = 0;
	if (maxCount < minCount) maxCount = minCount;

	class CItem* pItem = new class CItem;
	if (m_pGame->_bInitItemAttr(pItem, itemId) == false) {
		delete pItem;
		return false;
	}

	uint32_t count = 1;
	if (itemId == 90) {
		if (maxCount == 0) {
			delete pItem;
			return false;
		}
		count = static_cast<uint32_t>(maxCount);
		if (maxCount > minCount) {
			count = static_cast<uint32_t>(m_pGame->iDice(1, (maxCount - minCount)) + minCount);
		}
	} else {
		if (minCount <= 0) minCount = 1;
		count = static_cast<uint32_t>(maxCount);
		if (maxCount > minCount) {
			count = static_cast<uint32_t>(m_pGame->iDice(1, (maxCount - minCount)) + minCount);
		}
	}
	if (count == 0) {
		delete pItem;
		return false;
	}
	pItem->m_dwCount = count;
	pItem->m_sTouchEffectType = DEF_ITET_ID;
	pItem->m_sTouchEffectValue1 = static_cast<short>(m_pGame->iDice(1, 100000));
	pItem->m_sTouchEffectValue2 = static_cast<short>(m_pGame->iDice(1, 100000));
	pItem->m_sTouchEffectValue3 = (short)GameClock::GetTimeMS();
	m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->bSetItem(m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY, pItem);
	m_pGame->SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_ITEMDROP, m_pNpcList[iNpcH]->m_cMapIndex,
		m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY, pItem->m_sIDnum, 0, pItem->m_cItemColor, pItem->m_dwAttribute);
	m_pGame->_bItemLog(DEF_ITEMLOG_NEWGENDROP, 0, m_pNpcList[iNpcH]->m_cNpcName, pItem);
	return true;
}

int CEntityManager::GetEntityHandleByGUID(uint32_t dwGUID) const
{
    if (dwGUID == 0)
        return -1;

    for (int i = 1; i < DEF_MAXNPCS; i++) {
        if (m_dwEntityGUID[i] == dwGUID && m_pNpcList[i] != NULL)
            return i;
    }

    return -1;
}

uint32_t CEntityManager::GetEntityGUID(int iEntityHandle) const
{
    if (iEntityHandle < 1 || iEntityHandle >= DEF_MAXNPCS)
        return 0;

    return m_dwEntityGUID[iEntityHandle];
}

int CEntityManager::GetTotalActiveEntities() const
{
    return m_iTotalEntities;
}

int CEntityManager::GetMapEntityCount(int iMapIndex) const
{
    if (!m_bInitialized || iMapIndex < 0 || iMapIndex >= m_iMaxMaps)
        return 0;

    if (m_pMapList[iMapIndex] == NULL)
        return 0;

    return m_pMapList[iMapIndex]->m_iTotalActiveObject;
}

int CEntityManager::FindEntityByName(const char* pName) const
{
    if (pName == NULL)
        return -1;

    for (int i = 1; i < DEF_MAXNPCS; i++) {
        if (m_pNpcList[i] != NULL) {
            if (memcmp(m_pNpcList[i]->m_cName, pName, 6) == 0)
                return i;
        }
    }

    return -1;
}

// ========================================================================
// Internal Helpers - STUBS
// ========================================================================

bool CEntityManager::InitEntityAttributes(CNpc* pNpc, const char* pNpcName, short sClass, char cSA)
{
    if (m_pGame == NULL)
        return false;

    return m_pGame->_bInitNpcAttr(pNpc, const_cast<char*>(pNpcName), sClass, cSA);
}

int CEntityManager::GetFreeEntitySlot() const
{
    for (int i = 1; i < DEF_MAXNPCS; i++) {
        if (m_pNpcList[i] == NULL)
            return i;
    }
    return -1; // No free slots
}

bool CEntityManager::IsValidEntity(int iEntityHandle) const
{
    if (iEntityHandle < 1 || iEntityHandle >= DEF_MAXNPCS)
        return false;

    return (m_pNpcList[iEntityHandle] != NULL);
}

void CEntityManager::GenerateEntityLoot(int iEntityHandle, short sAttackerH, char cAttackerType)
{
    if (m_pGame == NULL)
        return;

    NpcDeadItemGenerator(iEntityHandle, sAttackerH, cAttackerType);
}

// ========================================================================
// Active Entity List Management (Performance Optimization)
// ========================================================================

void CEntityManager::AddToActiveList(int iEntityHandle)
{
    // Add entity to active list for fast iteration
    // This allows us to iterate only active entities (e.g., 70) instead of all slots (5000)

    if (iEntityHandle < 1 || iEntityHandle >= DEF_MAXNPCS) {
        return; // Invalid handle
    }

    // Check if already in list (shouldn't happen, but safety check)
    for (int i = 0; i < m_iActiveEntityCount; i++) {
        if (m_pActiveEntityList[i] == iEntityHandle) {
            return; // Already in list
        }
    }

    // Add to end of list
    m_pActiveEntityList[m_iActiveEntityCount] = iEntityHandle;
    m_iActiveEntityCount++;

}

void CEntityManager::RemoveFromActiveList(int iEntityHandle)
{
    // Remove entity from active list when deleted
    // Uses swap-and-pop for O(1) removal

    if (iEntityHandle < 1 || iEntityHandle >= DEF_MAXNPCS) {
        return; // Invalid handle
    }

    // Find entity in list
    for (int i = 0; i < m_iActiveEntityCount; i++) {
        if (m_pActiveEntityList[i] == iEntityHandle) {
            // Swap with last element and decrement count (O(1) removal)
            m_pActiveEntityList[i] = m_pActiveEntityList[m_iActiveEntityCount - 1];
            m_iActiveEntityCount--;

            return;
        }
    }

}

// ========================================================================
// Spawn Point Management - STUBS
// ========================================================================

void CEntityManager::ProcessRandomSpawns(int iMapIndex)
{
	int i, x, j, iNamingValue, iResult, iTotalMob;
	char cNpcName[21], cName_Master[11], cName_Slave[11], cWaypoint[11];
	char cSA;
	int  pX, pY, iMapLevel, iProbSA, iKindSA, iResultNum, iNpcID;
	bool bMaster, bFirmBerserk, bIsSpecialEvent;

	if (m_pGame == NULL || m_pGame->m_bOnExitProcess) return;

	for (i = 0; i < m_iMaxMaps; i++) {
		// Random Mob Generator

		//if ( (m_pMapList[i] != 0) && (m_pMapList[i]->m_bRandomMobGenerator ) && 
		//	 ((m_pMapList[i]->m_iMaximumObject - 30) > m_pMapList[i]->m_iTotalActiveObject) ) {

		if (m_pMapList[i] != 0) {
			//if (m_pGame->m_bIsCrusadeMode ) 
			//	 iResultNum = (m_pMapList[i]->m_iMaximumObject - 30) / 3;
			//else iResultNum = (m_pMapList[i]->m_iMaximumObject - 30);
			iResultNum = (m_pMapList[i]->m_iMaximumObject - 30);
		}

		if ( (m_pMapList[i] != 0) && (m_pMapList[i]->m_bRandomMobGenerator ) && (iResultNum > m_pMapList[i]->m_iTotalActiveObject) ) {
			if ((m_pGame->m_iMiddlelandMapIndex != -1) && (m_pGame->m_iMiddlelandMapIndex == i) && (m_pGame->m_bIsCrusadeMode )) break;

			iNamingValue = m_pMapList[i]->iGetEmptyNamingValue();
			if (iNamingValue != -1) {
				// Master Mob????????.
				ZeroMemory(cName_Master, sizeof(cName_Master));
				wsprintf(cName_Master, "XX%d", iNamingValue);
				cName_Master[0] = '_';
				cName_Master[1] = i + 65;

				ZeroMemory(cNpcName, sizeof(cNpcName));

				bFirmBerserk = false;
				iResult = m_pGame->iDice(1,100);
				switch (m_pMapList[i]->m_cRandomMobGeneratorLevel) {

				case 1: // arefarm, elvfarm, aresden, elvine
					if ((iResult >= 1) && (iResult < 20)) {
						iResult = 1; // Slime
					}
					else if ((iResult >= 20) && (iResult < 40)) {
						iResult = 2; // Giant-Ant
					}
					else if ((iResult >= 40) && (iResult < 85)) {
						iResult = 24; // Rabbit
					}
					else if ((iResult >= 85) && (iResult < 95)) {
						iResult = 25; // Cat
					}
					else if ((iResult >= 95) && (iResult <= 100)) {
						iResult = 3; // Orc
					}
					iMapLevel = 1;
					break;

				case 2:
					if ((iResult >= 1) && (iResult < 40)) {
						iResult = 1;
					}
					else if ((iResult >= 40) && (iResult < 80)) {
						iResult = 2;
					}
					else iResult = 10;
					iMapLevel = 1;
					break;

				case 3:     // v1.4334 ????????? ????
					if ((iResult >= 1) && (iResult < 20)) {
						switch (m_pGame->iDice(1,2)) {
				case 1: iResult = 3;  break;
				case 2: iResult = 4;  break;
						}
					}
					else if ((iResult >= 20) && (iResult < 25)) {
						iResult = 30;
					}
					else if ((iResult >= 25) && (iResult < 50)) {
						switch (m_pGame->iDice(1,3)) {	
				case 1: iResult = 5;  break;
				case 2: iResult = 6;  break;
				case 3:	iResult = 7;  break;
						}
					}
					else if ((iResult >= 50) && (iResult < 75)) {
						switch (m_pGame->iDice(1,7)) {
				case 1:
				case 2:	iResult = 8;  break;
				case 3:	iResult = 11; break;
				case 4: iResult = 12; break;
				case 5:	iResult = 18; break;
				case 6:	iResult = 26; break;
				case 7: iResult = 28; break;
						}
					}
					else if ((iResult >= 75) && (iResult <= 100)) {
						switch (m_pGame->iDice(1,5)) {	
				case 1:
				case 2: iResult = 9;  break;
				case 3:	iResult = 13; break;
				case 4: iResult = 14; break;
				case 5:	iResult = 27; break;
						}
					}
					iMapLevel = 3;
					break;

				case 4:
					if ((iResult >= 1) && (iResult < 50)) {
						switch (m_pGame->iDice(1,2)) {
				case 1:	iResult = 2;  break;
				case 2: iResult = 10; break;
						}
					}
					else if ((iResult >= 50) && (iResult < 80)) {
						switch (m_pGame->iDice(1,2)) {
				case 1: iResult = 8;  break;
				case 2: iResult = 11; break;
						}
					}
					else if ((iResult >= 80) && (iResult <= 100)) {
						switch (m_pGame->iDice(1,2)) {
				case 1: iResult = 14; break;
				case 2:	iResult = 9;  break;
						}
					}
					iMapLevel = 2;
					break;

				case 5:
					if ((iResult >= 1) && (iResult < 30)) {
						switch (m_pGame->iDice(1,5)) {
				case 1:
				case 2: 
				case 3:
				case 4: 
				case 5: iResult = 2;  break;
						}
					}
					else if ((iResult >= 30) && (iResult < 60)) {
						switch (m_pGame->iDice(1,2)) {
				case 1: iResult = 3;  break;
				case 2: iResult = 4;  break;
						}
					}
					else if ((iResult >= 60) && (iResult < 80)) {
						switch (m_pGame->iDice(1,2)) {
				case 1: iResult = 5;  break;
				case 2: iResult = 7;  break;
						}
					}
					else if ((iResult >= 80) && (iResult < 95)) {
						switch (m_pGame->iDice(1,3)) {
				case 1:
				case 2: iResult = 8;  break;
				case 3:	iResult = 11; break;
						}
					}
					else if ((iResult >= 95) && (iResult <= 100)) {
						switch (m_pGame->iDice(1,3)) {
				case 1: iResult = 11; break;
				case 2: iResult = 14; break;
				case 3: iResult = 9;  break;
						}
					}
					iMapLevel = 3;
					break;

				case 6: // huntzone3, huntzone4
					if ((iResult >= 1) && (iResult < 60)) {
						switch (m_pGame->iDice(1,4)) {
				case 1: iResult = 5;  break; // Skeleton
				case 2:	iResult = 6;  break; // Orc-Mage
				case 3: iResult = 12; break; // Cyclops
				case 4: iResult = 11; break; // Troll
						}
					}
					else if ((iResult >= 60) && (iResult < 90)) {
						switch (m_pGame->iDice(1,5)) {
				case 1:
				case 2: iResult = 8;  break; // Stone-Golem
				case 3:	iResult = 11; break; // Troll
				case 4:	iResult = 12; break; // Cyclops 
				case 5:	iResult = 43; break; // Tentocle
						}
					}
					else if ((iResult >= 90) && (iResult <= 100)) {
						switch (m_pGame->iDice(1,9)) {
				case 1:	iResult = 26; break;
				case 2:	iResult = 9;  break;
				case 3: iResult = 13; break;
				case 4: iResult = 14; break;
				case 5:	iResult = 18; break;
				case 6:	iResult = 28; break;
				case 7: iResult = 27; break;
				case 8: iResult = 29; break;
						}
					}
					iMapLevel = 4;
					break;

				case 7: // areuni, elvuni
					if ((iResult >= 1) && (iResult < 50)) {
						switch (m_pGame->iDice(1,5)) {
						case 1: iResult = 3;  break; // Orc
						case 2: iResult = 6;  break; // Orc-Mage
						case 3: iResult = 10; break; // Amphis
						case 4: iResult = 3;  break; // Orc
						case 5: iResult = 50; break; // Giant-Tree
						}
					}
					//else if ((iResult >= 50) && (iResult < 60)) { 
					//	iResult = 29; // Rudolph
					//}
					else if ((iResult >= 50) && (iResult < 85)) { 
						switch (m_pGame->iDice(1,4)) {
						case 1: iResult = 50; break; // Giant-Tree
						case 2: 
						case 3: iResult = 6;  break; // Orc-Mage
						case 4: iResult = 12; break; // Troll
						}
					}
					else if ((iResult >= 85) && (iResult <= 100)) {
						switch (m_pGame->iDice(1,4)) {
				case 1: iResult = 12;  break; // Troll
				case 2:
				case 3:
					if (m_pGame->iDice(1,100) < 3) 
						iResult = 17; // Unicorn
					else iResult = 12; // Troll
					break;
				case 4: iResult = 29;  break; // Cannibal-Plant
						}
					}
					iMapLevel = 4;
					break;

				case 8:
					if ((iResult >= 1) && (iResult < 70)) {
						switch (m_pGame->iDice(1,2)) {
						case 1:	iResult = 4;  break;
						case 2: iResult = 5;  break;
						}
					}
					else if ((iResult >= 70) && (iResult < 95)) {
						switch (m_pGame->iDice(1,2)) {
						case 1: iResult = 8;  break;
						case 2: iResult = 11; break;
						}
					}
					else if ((iResult >= 95) && (iResult <= 100)) {
						iResult = 14; break;
					}
					iMapLevel = 4;
					break;

				case 9:
					if ((iResult >= 1) && (iResult < 70)) {
						switch (m_pGame->iDice(1,2)) {
				case 1:	iResult = 4;  break;
				case 2: iResult = 5;  break;
						}
					}
					else if ((iResult >= 70) && (iResult < 95)) {
						switch (m_pGame->iDice(1,3)) {
				case 1: iResult = 8;  break;
				case 2: iResult = 9;  break;
				case 3: iResult = 13; break;
						}
					}
					else if ((iResult >= 95) && (iResult <= 100)) {
						switch (m_pGame->iDice(1,6)) {
				case 1: 
				case 2: 
				case 3: iResult = 9;  break;
				case 4: 
				case 5: iResult = 14; break;
				case 6: iResult = 15; break;
						}
					}

					if ((m_pGame->iDice(1,3) == 1) && (iResult != 16)) bFirmBerserk = true;
					iMapLevel = 5;
					break;

				case 10:
					if ((iResult >= 1) && (iResult < 70)) {
						switch (m_pGame->iDice(1,3)) {
				case 1:	iResult = 9; break;
				case 2: iResult = 5; break;
				case 3: iResult = 8; break;
						}
					}
					else if ((iResult >= 70) && (iResult < 95)) {
						switch (m_pGame->iDice(1,3)) {
				case 1:
				case 2:	iResult = 13; break;
				case 3: iResult = 14; break;
						}
					}
					else if ((iResult >= 95) && (iResult <= 100)) {
						switch (m_pGame->iDice(1,3)) {
				case 1:
				case 2: iResult = 14; break;
				case 3: iResult = 15; break;
						}
					}
					// Demon?? Berserk ????? ??? ?????
					if ((m_pGame->iDice(1,3) == 1) && (iResult != 16)) bFirmBerserk = true;
					iMapLevel = 5;
					break;

				case 11:
					if ((iResult >= 1) && (iResult < 30)) {
						switch (m_pGame->iDice(1,5)) {
				case 1:
				case 2: 
				case 3:
				case 4: 
				case 5: iResult = 2; break;
						}
					}
					else if ((iResult >= 30) && (iResult < 60)) {
						switch (m_pGame->iDice(1,2)) {
				case 1: iResult = 3; break;
				case 2: iResult = 4; break;
						}
					}
					else if ((iResult >= 60) && (iResult < 80)) {
						switch (m_pGame->iDice(1,2)) {
				case 1: iResult = 5; break;
				case 2: iResult = 7; break;
						}
					}
					else if ((iResult >= 80) && (iResult < 95)) {
						switch (m_pGame->iDice(1,3)) {
				case 1:
				case 2: iResult = 10;  break;
				case 3:	iResult = 11; break;
						}
					}
					else if ((iResult >= 95) && (iResult <= 100)) {
						switch (m_pGame->iDice(1,3)) {
				case 1: iResult = 11; break;
				case 2: iResult = 7; break;
				case 3: iResult = 8; break;
						}
					}
					iMapLevel = 4;
					break;

				case 12:
					if ((iResult >= 1) && (iResult < 50)) {
						switch (m_pGame->iDice(1,3)) {
				case 1:	iResult = 1 ; break;
				case 2: iResult = 2 ; break;
				case 3: iResult = 10; break;
						}
					}
					else if ((iResult >= 50) && (iResult < 85)) {
						switch (m_pGame->iDice(1,2)) {
				case 1: iResult = 5; break;
				case 2: iResult = 4; break;
						}
					}
					else if ((iResult >= 85) && (iResult <= 100)) {
						switch (m_pGame->iDice(1,3)) {
				case 1: iResult = 8; break;
				case 2: iResult = 11; break;
				case 3: iResult = 26; break;
						}
					}
					iMapLevel = 4;
					break;

				case 13:
					if ((iResult >= 1) && (iResult < 15)) {
						iResult = 4;
						bFirmBerserk = true;
						iTotalMob = 4 - (m_pGame->iDice(1,2) - 1);
						break;
					}
					else if ((iResult >= 15) && (iResult < 40)) {
						iResult = 14;
						bFirmBerserk = true;
						iTotalMob = 4 - (m_pGame->iDice(1,2) - 1);
						break;
					}
					else if ((iResult >= 40) && (iResult < 60)) {
						iResult = 9;
						bFirmBerserk = true;
						iTotalMob = 4 - (m_pGame->iDice(1,2) - 1);
						break;
					}						
					else if ((iResult >= 60) && (iResult < 75)) {
						iResult = 13;
						bFirmBerserk = true;
						iTotalMob = 4 - (m_pGame->iDice(1,2) - 1);
						break;
					}
					else if ((iResult >= 75) && (iResult < 95)) {
						iResult = 23;
					}
					else if ((iResult >= 95) && (iResult <= 100)) {
						iResult = 22;
					}
					iMapLevel = 5;
					break;

				case 14: // icebound
					if ((iResult >= 1) && (iResult < 30)) {
						iResult = 23; // Dark-Elf
					}
					else if ((iResult >= 30) && (iResult < 50)) {
						iResult = 31; // Ice-Golem
					}
					else if ((iResult >= 50) && (iResult < 70)) {
						iResult = 22; // Beholder
						bFirmBerserk = true;
						iTotalMob = 4 - (m_pGame->iDice(1,2) - 1);
					}
					else if ((iResult >= 70) && (iResult < 90)) {
						iResult = 32; // DireBoar
					}
					else if ((iResult >= 90) && (iResult <= 100)) {
						iResult = 33; // Frost
					}
					iMapLevel = 5;
					break;

				case 15:
					if ((iResult >= 1) && (iResult < 35)) {
						iResult = 23; 
						bFirmBerserk = true;
					}
					else if ((iResult >= 35) && (iResult < 50)) {
						iResult = 22;
						bFirmBerserk = true;
					}
					else if ((iResult >= 50) && (iResult < 80)) {
						iResult = 15;
					}
					else if ((iResult >= 80) && (iResult <= 100)) {
						iResult = 21;
					}
					iMapLevel = 4;
					break;

				case 16: // 2ndmiddle, huntzone1, huntzone2, 
					if ((iResult >= 1) && (iResult < 40)) {
						switch (m_pGame->iDice(1,3)) {
						case 1:	iResult = 7;  break; // Scorpion
						case 2: iResult = 2;  break; // Giant-Ant
						case 3: iResult = 10; break; // Amphis
						}
					}
					else if ((iResult >= 40) && (iResult < 50)) {
						iResult = 30; // Rudolph
					}
					else if ((iResult >= 50) && (iResult < 85)) {
						switch (m_pGame->iDice(1,2)) {
						case 1: iResult = 5;  break; // Skeleton
						case 2: iResult = 4;  break; // Zombie
						}
					}
					else if ((iResult >= 85) && (iResult <= 100)) {
						switch (m_pGame->iDice(1,3)) {
						case 1: iResult = 8;  break; // Stone-Golem
						case 2: iResult = 11; break; // Clay-Golem
						case 3: iResult = 7;  break; // Scorpion
						}
					}
					iMapLevel = 1;
					break;

				case 17:
					if ((iResult >= 1) && (iResult < 30)) {
						switch (m_pGame->iDice(1,4)) {
						case 1:	iResult = 22;  break; // Giant-Frog
						case 2: iResult = 8;   break; // Stone-Golem
						case 3: iResult = 24;  break; // Rabbit
						case 4: iResult = 5;   break;
						}
					}
					else if ((iResult >= 30) && (iResult < 40)) {
						iResult = 30;
					}
					else if ((iResult >= 40) && (iResult < 70)) {
						iResult = 32;
					}
					else if ((iResult >= 70) && (iResult < 90)) {
						iResult = 31;
						if (m_pGame->iDice(1,5) == 1) {
							bFirmBerserk = true;
						}
					}
					else if ((iResult >= 90) && (iResult <= 100)) {
						iResult = 33;
					}
					iMapLevel = 1;
					break;

				case 18: // druncncity
					if ((iResult >= 1) && (iResult < 2)) {
						iResult = 39; // Tentocle
					}
					else if ((iResult >= 2) && (iResult < 12)) {
						iResult = 44; // ClawTurtle
					}
					else if ((iResult >= 12) && (iResult < 50)) {
						iResult = 48; // Nizie
					}
					else if ((iResult >= 50) && (iResult < 80)) {
						iResult = 45; // Giant-Crayfish
					}
					else if ((iResult >= 80) && (iResult < 90)) {
						iResult = 34; // Stalker
					}			
					else if ((iResult >= 90) && (iResult <= 100)) {
						iResult = 26; // Giant-Frog
					}					
					iMapLevel = 4;
					break;

				case 19:
					if ((iResult >= 1) && (iResult < 15)) {
						iResult = 44;
					}
					else if ((iResult >= 15) && (iResult < 25)) {
						iResult = 46;
					}
					else if ((iResult >= 25) && (iResult < 35)) {
						iResult = 21;
					}
					else if ((iResult >= 35) && (iResult < 60)) {
						iResult = 43;
					}				
					else if ((iResult >= 60) && (iResult < 85)) {
						iResult = 23;
					}		
					else if ((iResult >= 85) && (iResult <= 100)) {
						iResult = 22;
					}
					iMapLevel = 4;
					break;

				case 20:
					if ((iResult >= 1) && (iResult < 2)) {
						iResult = 41;
					}
					else if ((iResult >= 2) && (iResult < 3)) {
						iResult = 40;
					}
					else if ((iResult >= 3) && (iResult < 8)) {
						iResult = 53;
					}
					else if ((iResult >= 8) && (iResult < 9)) {
						iResult = 39;
					}
					else if ((iResult >= 9) && (iResult < 20)) {
						iResult = 21;
					}
					else if ((iResult >= 20) && (iResult < 35)) {
						iResult = 16;
					}
					else if ((iResult >= 35) && (iResult < 45)) {
						iResult = 44;
					}
					else if ((iResult >= 45) && (iResult < 55)) {
						iResult = 45;
					}
					else if ((iResult >= 55) && (iResult < 75)) {
						iResult = 28;
					}
					else if ((iResult >= 75) && (iResult < 95)) {
						iResult = 43;
					}
					else if ((iResult >= 95) && (iResult < 100)) {
						iResult = 22;
					}
					iMapLevel = 4;
					break;

				case 21:
					if ((iResult >= 1) && (iResult < 94)) {
						iResult = 17; // Unicorn
						bFirmBerserk = true;
					}
					else if ((iResult >= 94) && (iResult < 95)) {
						iResult = 36; // Wyvern
					}
					else if ((iResult >= 95) && (iResult < 96)) {
						iResult = 37; // Fire-Wyvern
					}
					else if ((iResult >= 96) && (iResult < 97)) {
						iResult = 47; // MasterMage-Orc
					}
					else if ((iResult >= 97) && (iResult < 98)) {
						iResult = 35; // Hellclaw
					}				
					else if ((iResult >= 98) && (iResult < 99)) {
						iResult = 49; // Tigerworm
					}		
					else if ((iResult >= 99) && (iResult <= 100)) {
						iResult = 51; // Abaddon
					}
					iMapLevel = 4;
					break;
	
				}			

				pX = 0;
				pY = 0;

//				bIsSpecialEvent = true;
				if ((m_pGame->m_bIsSpecialEventTime ) && (m_pGame->iDice(1,10) == 3)) bIsSpecialEvent = true;

				if (bIsSpecialEvent ) {
					switch (m_pGame->m_cSpecialEventType) {
					case 1:
						if (m_pMapList[i]->m_iMaxPx != 0) {
							pX = m_pMapList[i]->m_iMaxPx*20 +10;
							pY = m_pMapList[i]->m_iMaxPy*20 +10;

							if (pX < 0) pX = 0;
							if (pY < 0) pY = 0;

							if (m_pGame->m_bIsCrusadeMode ) {
								if (strcmp(m_pMapList[i]->m_cName, "aresden") == 0)
									switch(m_pGame->iDice(1,6)) {
									case 1: iResult = 20; break;
									case 2: iResult = 53; break;
									case 3: iResult = 55; break;
									case 4: iResult = 57; break;
									case 5: iResult = 59; break;
									case 6: iResult = 61; break;
								}
								else if (strcmp(m_pMapList[i]->m_cName, "elvine") == 0)
									switch(m_pGame->iDice(1,6)) {
									case 1: iResult = 19; break;
									case 2: iResult = 52; break;
									case 3: iResult = 54; break;
									case 4: iResult = 56; break;
									case 5: iResult = 58; break;
									case 6: iResult = 60; break;
								}
							}
							wsprintf(G_cTxt, "(!) Mob-Event Map(%s)[%d (%d,%d)]", m_pMapList[i]->m_cName, iResult, pX, pY);
						}
						break;

					case 2:
						if (m_pGame->iDice(1,3) == 2) {
							if ((memcmp(m_pMapList[i]->m_cLocationName, "aresden", 7)   == 0) ||
								(memcmp(m_pMapList[i]->m_cLocationName, "middled1n", 9) == 0) ||
								(memcmp(m_pMapList[i]->m_cLocationName, "arefarm", 7) == 0) ||
								(memcmp(m_pMapList[i]->m_cLocationName, "elvfarm", 7) == 0) ||
								(memcmp(m_pMapList[i]->m_cLocationName, "elvine", 6)    == 0)) {
									if (m_pGame->iDice(1,30) == 5) 
										iResult = 16;
									else iResult = 5;
								}
							else iResult = 16;
						}
						else iResult = 17;

						m_pGame->m_bIsSpecialEventTime = false;
						break;
					}
				}

				ZeroMemory(cNpcName, sizeof(cNpcName));
				//Random Monster Spawns
				switch (iResult) {
				case 1:  strcpy(cNpcName, "Slime");				iNpcID = 10; iProbSA = 5;  iKindSA = 1; break;
				case 2:  strcpy(cNpcName, "Giant-Ant");			iNpcID = 16; iProbSA = 10; iKindSA = 2; break;
				case 3:  strcpy(cNpcName, "Orc");				iNpcID = 14; iProbSA = 15; iKindSA = 1; break;
				case 4:  strcpy(cNpcName, "Zombie");			iNpcID = 18; iProbSA = 15; iKindSA = 3; break;
				case 5:  strcpy(cNpcName, "Skeleton");			iNpcID = 11; iProbSA = 35; iKindSA = 8; break;
				case 6:  strcpy(cNpcName, "Orc-Mage");			iNpcID = 14; iProbSA = 30; iKindSA = 7; break;
				case 7:  strcpy(cNpcName, "Scorpion");			iNpcID = 17; iProbSA = 15; iKindSA = 3; break;
				case 8:  strcpy(cNpcName, "Stone-Golem");		iNpcID = 12; iProbSA = 25; iKindSA = 5; break;
				case 9:  strcpy(cNpcName, "Cyclops");			iNpcID = 13; iProbSA = 35; iKindSA = 8; break;
				case 10: strcpy(cNpcName, "Amphis");			iNpcID = 22; iProbSA = 20; iKindSA = 3; break;
				case 11: strcpy(cNpcName, "Clay-Golem");		iNpcID = 23; iProbSA = 20; iKindSA = 5; break;
				case 12: strcpy(cNpcName, "Troll");				iNpcID = 28; iProbSA = 25; iKindSA = 3; break; 
				case 13: strcpy(cNpcName, "Orge");				iNpcID = 29; iProbSA = 25; iKindSA = 1; break;
				case 14: strcpy(cNpcName, "Hellbound");			iNpcID = 27; iProbSA = 25; iKindSA = 8; break;
				case 15: strcpy(cNpcName, "Liche");				iNpcID = 30; iProbSA = 30; iKindSA = 8; break;
				case 16: strcpy(cNpcName, "Demon");				iNpcID = 31; iProbSA = 20; iKindSA = 8; break;
				case 17: strcpy(cNpcName, "Unicorn");			iNpcID = 32; iProbSA = 35; iKindSA = 7; break;
				case 18: strcpy(cNpcName, "WereWolf");			iNpcID = 33; iProbSA = 25; iKindSA = 1; break;
				case 19: strcpy(cNpcName, "YB-Aresden");		iNpcID = -1;  iProbSA = 15; iKindSA = 1; break;
				case 20: strcpy(cNpcName, "YB-Elvine");			iNpcID = -1;  iProbSA = 15; iKindSA = 1; break;
				case 21: strcpy(cNpcName, "Gagoyle");			iNpcID = 52; iProbSA = 20; iKindSA = 8; break;
				case 22: strcpy(cNpcName, "Beholder");			iNpcID = 53; iProbSA = 20; iKindSA = 5; break;
				case 23: strcpy(cNpcName, "Dark-Elf");			iNpcID = 54; iProbSA = 20; iKindSA = 3; break;
				case 24: strcpy(cNpcName, "Rabbit");			iNpcID = -1; iProbSA = 5;  iKindSA = 1; break;
				case 25: strcpy(cNpcName, "Cat");				iNpcID = -1; iProbSA = 10; iKindSA = 2; break;
				case 26: strcpy(cNpcName, "Giant-Frog");		iNpcID = 57; iProbSA = 10; iKindSA = 2; break;
				case 27: strcpy(cNpcName, "Mountain-Giant");	iNpcID = 58; iProbSA = 25; iKindSA = 1; break;
				case 28: strcpy(cNpcName, "Ettin");				iNpcID = 59; iProbSA = 20; iKindSA = 8; break;
				case 29: strcpy(cNpcName, "Cannibal-Plant");	iNpcID = 60; iProbSA = 20; iKindSA = 5; break;
				case 30: strcpy(cNpcName, "Rudolph");			iNpcID = -1; iProbSA = 20; iKindSA = 5; break;
				case 31: strcpy(cNpcName, "Ice-Golem");			iNpcID = 65; iProbSA = 35; iKindSA = 8; break;
				case 32: strcpy(cNpcName, "DireBoar");			iNpcID = 62; iProbSA = 20; iKindSA = 5; break;
				case 33: strcpy(cNpcName, "Frost");				iNpcID = 63; iProbSA = 30; iKindSA = 8; break;
				case 34: strcpy(cNpcName, "Stalker");           iNpcID = 48; iProbSA = 20; iKindSA = 1; break;
				case 35: strcpy(cNpcName, "Hellclaw");			iNpcID = 49; iProbSA = 20; iKindSA = 1; break;
				case 36: strcpy(cNpcName, "Wyvern");			iNpcID = 66; iProbSA = 20; iKindSA = 1; break;
				case 37: strcpy(cNpcName, "Fire-Wyvern");		iNpcID = -1; iProbSA = 20; iKindSA = 1; break; 
				case 38: strcpy(cNpcName, "Barlog");			iNpcID = -1; iProbSA = 20; iKindSA = 1; break;
				case 39: strcpy(cNpcName, "Tentocle");			iNpcID = -1; iProbSA = 20; iKindSA = 1; break;
				case 40: strcpy(cNpcName, "Centaurus");			iNpcID = -1; iProbSA = 20; iKindSA = 1; break;
				case 41: strcpy(cNpcName, "Giant-Lizard");		iNpcID = -1; iProbSA = 20; iKindSA = 1; break;
				case 42: strcpy(cNpcName, "Minotaurs");			iNpcID = -1; iProbSA = 20; iKindSA = 1; break;
				case 43: strcpy(cNpcName, "Tentocle");			iNpcID = -1; iProbSA = 20; iKindSA = 1; break;
				case 44: strcpy(cNpcName, "Claw-Turtle");		iNpcID = -1; iProbSA = 20; iKindSA = 1; break;
				case 45: strcpy(cNpcName, "Giant-Crayfish");	iNpcID = -1; iProbSA = 20; iKindSA = 1; break;
				case 46: strcpy(cNpcName, "Giant-Plant");		iNpcID = -1; iProbSA = 20; iKindSA = 1; break;
				case 47: strcpy(cNpcName, "MasterMage-Orc");	iNpcID = -1; iProbSA = 20; iKindSA = 1; break;
				case 48: strcpy(cNpcName, "Nizie");				iNpcID = -1; iProbSA = 20; iKindSA = 1; break;
				case 49: strcpy(cNpcName, "Tigerworm");			iNpcID = 50; iProbSA = 20; iKindSA = 1; break;
				case 50: strcpy(cNpcName, "Giant-Plant");		iNpcID = -1; iProbSA = 20; iKindSA = 1; break;
				case 51: strcpy(cNpcName, "Abaddon");			iNpcID = -1; iProbSA = 20; iKindSA = 1; break;
				case 52: strcpy(cNpcName, "YW-Aresden");		iNpcID = -1; iProbSA = 15; iKindSA = 1; break;
				case 53: strcpy(cNpcName, "YW-Elvine");			iNpcID = -1; iProbSA = 15; iKindSA = 1; break;
				case 54: strcpy(cNpcName, "YY-Aresden");		iNpcID = -1; iProbSA = 15; iKindSA = 1; break;
				case 55: strcpy(cNpcName, "YY-Elvine");			iNpcID = -1; iProbSA = 15; iKindSA = 1; break;
				case 56: strcpy(cNpcName, "XB-Aresden");		iNpcID = -1; iProbSA = 15; iKindSA = 1; break;
				case 57: strcpy(cNpcName, "XB-Elvine");			iNpcID = -1; iProbSA = 15; iKindSA = 1; break;
				case 58: strcpy(cNpcName, "XW-Aresden");		iNpcID = -1; iProbSA = 15; iKindSA = 1; break;
				case 59: strcpy(cNpcName, "XW-Elvine");			iNpcID = -1; iProbSA = 15; iKindSA = 1; break;
				case 60: strcpy(cNpcName, "XY-Aresden");		iNpcID = -1; iProbSA = 15; iKindSA = 1; break;
				case 61: strcpy(cNpcName, "XY-Elvine");			iNpcID = -1; iProbSA = 15; iKindSA = 1; break;
				default: strcpy(cNpcName, "Orc");				iNpcID = 14; iProbSA = 15; iKindSA = 1; break;
				}

				cSA = 0;
				if (m_pGame->iDice(1, 100) <= static_cast<uint32_t>(iProbSA)) {
					cSA = m_pGame->_cGetSpecialAbility(iKindSA);
				}

				bMaster = (CreateEntity(cNpcName, cName_Master, m_pMapList[i]->m_cName, (rand() % 3), cSA,
					DEF_MOVETYPE_RANDOM, &pX, &pY, cWaypoint, 0, 0, -1, false, false, bFirmBerserk, true, 0) > 0);
				if (bMaster == false) {
					m_pMapList[i]->SetNamingValueEmpty(iNamingValue);
				}
				else {

				}
			}	

			switch (iResult) {
			case 1:	 iTotalMob = m_pGame->iDice(1,5)-1; break;
			case 2:	 iTotalMob = m_pGame->iDice(1,5)-1; break;
			case 3:	 iTotalMob = m_pGame->iDice(1,5)-1; break;
			case 4:	 iTotalMob = m_pGame->iDice(1,3)-1; break;
			case 5:	 iTotalMob = m_pGame->iDice(1,3)-1; break;

			case 6:  iTotalMob = m_pGame->iDice(1,3)-1; break;
			case 7:  iTotalMob = m_pGame->iDice(1,3)-1; break;
			case 8:  iTotalMob = m_pGame->iDice(1,2)-1; break;
			case 9:  iTotalMob = m_pGame->iDice(1,2)-1; break;
			case 10: iTotalMob = m_pGame->iDice(1,5)-1; break;
			case 11: iTotalMob = m_pGame->iDice(1,3)-1; break;
			case 12: iTotalMob = m_pGame->iDice(1,5)-1; break;
			case 13: iTotalMob = m_pGame->iDice(1,3)-1; break;
			case 14: iTotalMob = m_pGame->iDice(1,2)-1; break;
			case 15: iTotalMob = m_pGame->iDice(1,3)-1; break;
			case 16: iTotalMob = m_pGame->iDice(1,2)-1; break;
			case 17: iTotalMob = m_pGame->iDice(1,2)-1; break;

			case 18: iTotalMob = m_pGame->iDice(1,5)-1; break;
			case 19: iTotalMob = m_pGame->iDice(1,2)-1; break;
			case 20: iTotalMob = m_pGame->iDice(1,2)-1; break;
			case 21: iTotalMob = m_pGame->iDice(1,5)-1; break;
			case 22: iTotalMob = m_pGame->iDice(1,2)-1; break;
			case 23: iTotalMob = m_pGame->iDice(1,2)-1; break;

			case 24: iTotalMob = m_pGame->iDice(1,4)-1; break;
			case 25: iTotalMob = m_pGame->iDice(1,2)-1; break;
			case 26: iTotalMob = m_pGame->iDice(1,3)-1; break;
			case 27: iTotalMob = m_pGame->iDice(1,3)-1; break;

			case 28: iTotalMob = m_pGame->iDice(1,3)-1; break;
			case 29: iTotalMob = m_pGame->iDice(1,5)-1; break;
			case 30: iTotalMob = m_pGame->iDice(1,3)-1; break;
			case 31: iTotalMob = m_pGame->iDice(1,3)-1; break;

			case 32: iTotalMob = 1; break;
			case 33: iTotalMob = 1; break;
			case 34: iTotalMob = 1; break;
			case 35: iTotalMob = 1; break;
			case 36: iTotalMob = 1; break;

			case 37: iTotalMob = 1; break;
			case 38: iTotalMob = 1; break;
			case 39: iTotalMob = 1; break;
			case 40: iTotalMob = 1; break;
			case 41: iTotalMob = 1; break;

			case 42: iTotalMob = m_pGame->iDice(1,3)-1; break;
			case 43: iTotalMob = 1; break;
			case 44: iTotalMob = m_pGame->iDice(1,3)-1; break; 
			case 45: iTotalMob = 1; break;
			default: iTotalMob = 0; break;
			}

			if (bMaster == false) iTotalMob = 0;

			if (iTotalMob > 2) {
				switch (iResult) {
				case 1:  // Slime 
				case 2:  // Giant-Ant
				case 3:  // Orc
				case 4:  // Zombie
				case 5:  // Skeleton
				case 6:  // Orc-Mage
				case 7:  // Scorpion
				case 8:  // Stone-Golem
				case 9:  // Cyclops
				case 10: // Amphis
				case 11: // Clay-Golem
				case 12: // Troll
				case 13: // Orge
				case 14: // Hellbound
				case 15: // Liche
				case 16: // Demon
				case 17: // Unicorn
				case 18: // WereWolf
				case 19:
				case 20:
				case 21:
				case 22:
				case 23:
				case 24:
				case 25:
				case 26:
				case 27:
				case 28:
				case 29:
				case 30:
				case 31:
				case 32:
					if (m_pGame->iDice(1,5) == 1) iTotalMob = 0;  // 75% ???????? ???.
					break;

				case 33:
				case 34:
				case 35:
				case 36:
				case 37:
				case 38:
				case 39:
				case 40:
				case 41:
				case 42:
				case 44:
				case 45:
				case 46:
				case 47:
				case 48:
				case 49:
					if (m_pGame->iDice(1,5) != 1) iTotalMob = 0;  // 75% ???????????????
					break;
				}
			}

			if (bIsSpecialEvent ) {
				switch (m_pGame->m_cSpecialEventType) {
				case 1:
					if ((iResult != 35) && (iResult != 36) && (iResult != 37) && (iResult != 49) 
						&& (iResult != 51) && (iResult != 15) && (iResult != 16) && (iResult != 21)) iTotalMob = 12;
					for (x = 1; x < DEF_MAXCLIENTS; x++)
					if ((iNpcID != -1) && (m_pGame->m_pClientList[x] != 0) && (m_pGame->m_pClientList[x]->m_bIsInitComplete )) {
						m_pGame->SendNotifyMsg(0, x, DEF_NOTIFY_SPAWNEVENT, pX, pY, iNpcID, 0, 0, 0);
					}
					break;

				case 2:
					if ((memcmp(m_pMapList[i]->m_cLocationName, "aresden", 7) == 0) ||
						(memcmp(m_pMapList[i]->m_cLocationName, "elvine",  6) == 0) ||
						(memcmp(m_pMapList[i]->m_cLocationName, "elvfarm",  7) == 0) ||
						(memcmp(m_pMapList[i]->m_cLocationName, "arefarm",  7) == 0) ) {
							iTotalMob = 0;
						}
						break;
				}
				m_pGame->m_bIsSpecialEventTime = false;
			}

			for (j = 0; j < iTotalMob; j++) {
				iNamingValue = m_pMapList[i]->iGetEmptyNamingValue();
				if (iNamingValue != -1) {
					ZeroMemory(cName_Slave, sizeof(cName_Slave));
					wsprintf(cName_Slave, "XX%d", iNamingValue);
					cName_Slave[0] = 95; // original '_';
					cName_Slave[1] = i + 65;

					cSA = 0;

					if (m_pGame->iDice(1, 100) <= static_cast<uint32_t>(iProbSA)) {
						cSA = m_pGame->_cGetSpecialAbility(iKindSA);
					}

					if (CreateEntity(cNpcName, cName_Slave, m_pMapList[i]->m_cName, (rand() % 3), cSA,
						DEF_MOVETYPE_RANDOM, &pX, &pY, cWaypoint, 0, 0, -1, false, false, bFirmBerserk, false, 0) <= 0) {
						m_pMapList[i]->SetNamingValueEmpty(iNamingValue);
					}
					else {
						bSetNpcFollowMode(cName_Slave, cName_Master, DEF_OWNERTYPE_NPC);
					}
				}
			}
		}

		
	}
}



void CEntityManager::ProcessSpotSpawns(int iMapIndex)
{
    // Extracted from Game.cpp:26370-26518 (MobGenerator spot spawn logic)

    if (iMapIndex < 0 || iMapIndex >= m_iMaxMaps)
        return;

    if (m_pMapList[iMapIndex] == NULL)
        return;


    // Check if map has room for more objects
    if (m_pMapList[iMapIndex]->m_iMaximumObject <= m_pMapList[iMapIndex]->m_iTotalActiveObject) {
        return;
    }

    int iNamingValue, pX, pY, iProbSA, iKindSA;
    char cNpcName[21], cName_Master[11], cWaypoint[11];
    char cSA;
    bool bFirmBerserk;

    // Loop through all spot mob generators
    for (int j = 1; j < DEF_MAXSPOTMOBGENERATOR; j++) {
        // Check if generator is defined and has room for more mobs
        if (!m_pMapList[iMapIndex]->m_stSpotMobGenerator[j].bDefined) {
            continue;  // Generator not defined
        }

        if (m_pMapList[iMapIndex]->m_stSpotMobGenerator[j].iMaxMobs <=
            m_pMapList[iMapIndex]->m_stSpotMobGenerator[j].iCurMobs) {
            continue;  // Generator at capacity
        }

        // Random chance (1 in 3) to spawn this tick - rate limiting
        if (m_pGame->iDice(1, 3) != 2) {
            continue;  // Skip this tick, try again next time
        }

        // If we reach here, we're attempting a spawn
        {
            iNamingValue = m_pMapList[iMapIndex]->iGetEmptyNamingValue();
            if (iNamingValue == -1) {
                continue; // No naming value available, try next generator
            }

            // Determine NPC type and special ability probabilities
            std::memset(cNpcName, 0, sizeof(cNpcName));
            switch (m_pMapList[iMapIndex]->m_stSpotMobGenerator[j].iMobType) {
                case 10:  strcpy(cNpcName, "Slime");               iProbSA = 5;  iKindSA = 1;  break;
                case 16:  strcpy(cNpcName, "Giant-Ant");           iProbSA = 10; iKindSA = 2;  break;
                case 14:  strcpy(cNpcName, "Orc");                 iProbSA = 15; iKindSA = 1;  break;
                case 18:  strcpy(cNpcName, "Zombie");              iProbSA = 15; iKindSA = 3;  break;
                case 11:  strcpy(cNpcName, "Skeleton");            iProbSA = 35; iKindSA = 8;  break;
                case 6:   strcpy(cNpcName, "Orc-Mage");            iProbSA = 30; iKindSA = 7;  break;
                case 17:  strcpy(cNpcName, "Scorpion");            iProbSA = 15; iKindSA = 3;  break;
                case 12:  strcpy(cNpcName, "Stone-Golem");         iProbSA = 25; iKindSA = 5;  break;
                case 13:  strcpy(cNpcName, "Cyclops");             iProbSA = 35; iKindSA = 8;  break;
                case 22:  strcpy(cNpcName, "Amphis");              iProbSA = 20; iKindSA = 3;  break;
                case 23:  strcpy(cNpcName, "Clay-Golem");          iProbSA = 20; iKindSA = 5;  break;
                case 24:  strcpy(cNpcName, "Guard-Aresden");       iProbSA = 20; iKindSA = 1;  break;
                case 25:  strcpy(cNpcName, "Guard-Elvine");        iProbSA = 20; iKindSA = 1;  break;
                case 26:  strcpy(cNpcName, "Guard-Neutral");       iProbSA = 20; iKindSA = 1;  break;
                case 27:  strcpy(cNpcName, "Hellbound");           iProbSA = 20; iKindSA = 1;  break;
                case 28:  strcpy(cNpcName, "Troll");               iProbSA = 25; iKindSA = 3;  break;
                case 29:  strcpy(cNpcName, "Orge");                iProbSA = 20; iKindSA = 1;  break;
                case 30:  strcpy(cNpcName, "Liche");               iProbSA = 30; iKindSA = 8;  break;
                case 31:  strcpy(cNpcName, "Demon");               iProbSA = 20; iKindSA = 8;  break;
                case 32:  strcpy(cNpcName, "Unicorn");             iProbSA = 35; iKindSA = 7;  break;
                case 33:  strcpy(cNpcName, "WereWolf");            iProbSA = 25; iKindSA = 1;  break;
                case 34:  strcpy(cNpcName, "Dummy");               iProbSA = 5;  iKindSA = 1;  break;
                case 35:  strcpy(cNpcName, "Attack-Dummy");        iProbSA = 5;  iKindSA = 1;  break;
                case 48:  strcpy(cNpcName, "Stalker");             iProbSA = 20; iKindSA = 3;  break;
                case 49:  strcpy(cNpcName, "Hellclaw");            iProbSA = 20; iKindSA = 8;  break;
                case 50:  strcpy(cNpcName, "Tigerworm");           iProbSA = 20; iKindSA = 8;  break;
                case 52:  strcpy(cNpcName, "Gagoyle");             iProbSA = 20; iKindSA = 8;  break;
                case 53:  strcpy(cNpcName, "Beholder");            iProbSA = 20; iKindSA = 8;  break;
                case 54:  strcpy(cNpcName, "Dark-Elf");            iProbSA = 20; iKindSA = 8;  break;
                case 55:  strcpy(cNpcName, "Rabbit");              iProbSA = 20; iKindSA = 1;  break;
                case 57:  strcpy(cNpcName, "Giant-Frog");          iProbSA = 10; iKindSA = 2;  break;
                case 58:  strcpy(cNpcName, "Mountain-Giant");      iProbSA = 25; iKindSA = 1;  break;
                case 59:  strcpy(cNpcName, "Ettin");               iProbSA = 20; iKindSA = 8;  break;
                case 60:  strcpy(cNpcName, "Cannibal-Plant");      iProbSA = 20; iKindSA = 5;  break;
                case 61:  strcpy(cNpcName, "Rudolph");             iProbSA = 20; iKindSA = 1;  break;
                case 62:  strcpy(cNpcName, "DireBoar");            iProbSA = 20; iKindSA = 1;  break;
                case 63:  strcpy(cNpcName, "Frost");               iProbSA = 20; iKindSA = 8;  break;
                case 65:  strcpy(cNpcName, "Ice-Golem");           iProbSA = 20; iKindSA = 8;  break;
                case 66:  strcpy(cNpcName, "Wyvern");              iProbSA = 20; iKindSA = 1;  break;
                case 67:  strcpy(cNpcName, "McGaffin");            iProbSA = 20; iKindSA = 1;  break;
                case 68:  strcpy(cNpcName, "Perry");               iProbSA = 20; iKindSA = 1;  break;
                case 69:  strcpy(cNpcName, "Devlin");              iProbSA = 20; iKindSA = 1;  break;
                case 70:  strcpy(cNpcName, "Barlog");              iProbSA = 20; iKindSA = 1;  break;
                case 71:  strcpy(cNpcName, "Centaurus");           iProbSA = 20; iKindSA = 1;  break;
                case 72:  strcpy(cNpcName, "Claw-Turtle");         iProbSA = 20; iKindSA = 1;  break;
                case 73:  strcpy(cNpcName, "Fire-Wyvern");         iProbSA = 20; iKindSA = 1;  break;
                case 74:  strcpy(cNpcName, "Giant-Crayfish");      iProbSA = 20; iKindSA = 1;  break;
                case 75:  strcpy(cNpcName, "Giant-Lizard");        iProbSA = 20; iKindSA = 1;  break;
                case 76:  strcpy(cNpcName, "Giant-Plant");         iProbSA = 20; iKindSA = 1;  break;
                case 77:  strcpy(cNpcName, "MasterMage-Orc");      iProbSA = 20; iKindSA = 1;  break;
                case 78:  strcpy(cNpcName, "Minotaurs");           iProbSA = 20; iKindSA = 1;  break;
                case 79:  strcpy(cNpcName, "Nizie");               iProbSA = 20; iKindSA = 1;  break;
                case 80:  strcpy(cNpcName, "Tentocle");            iProbSA = 20; iKindSA = 1;  break;
                case 81:  strcpy(cNpcName, "Abaddon");             iProbSA = 20; iKindSA = 1;  break;
                default:
                    strcpy(cNpcName, "Orc");
                    iProbSA = 15;
                    iKindSA = 1;
                    break;
            }

            bFirmBerserk = false;

            // Generate entity name
            std::memset(cName_Master, 0, sizeof(cName_Master));
            std::snprintf(cName_Master, sizeof(cName_Master), "XX%d", iNamingValue);
            cName_Master[0] = '_';
            cName_Master[1] = iMapIndex + 65;

            // Determine special ability
            cSA = 0;
            if ((m_pMapList[iMapIndex]->m_stSpotMobGenerator[j].iMobType != 34) &&
                (m_pGame->iDice(1, 100) <= static_cast<uint32_t>(iProbSA))) {
                cSA = m_pGame->_cGetSpecialAbility(iKindSA);
            }

            // Create entity based on generator type
            int iResult = -1;
            pX = 0;
            pY = 0;
            std::memset(cWaypoint, 0, sizeof(cWaypoint));

            switch (m_pMapList[iMapIndex]->m_stSpotMobGenerator[j].cType) {
                case 1: // RECT-based spawn (RANDOMAREA)
                    iResult = CreateEntity(
                        cNpcName, cName_Master, m_pMapList[iMapIndex]->m_cName,
                        (rand() % 3), cSA, DEF_MOVETYPE_RANDOMAREA,
                        &pX, &pY, cWaypoint,
                        &m_pMapList[iMapIndex]->m_stSpotMobGenerator[j].rcRect,
                        j, -1, false, false, bFirmBerserk, false, 0
                    );
                    break;

                case 2: // Waypoint-based spawn (RANDOMWAYPOINT)
                    // Convert waypoint array to string
                    for (int k = 0; k < 10; k++) {
                        cWaypoint[k] = (char)m_pMapList[iMapIndex]->m_stSpotMobGenerator[j].cWaypoint[k];
                    }
                    iResult = CreateEntity(
                        cNpcName, cName_Master, m_pMapList[iMapIndex]->m_cName,
                        (rand() % 3), cSA, DEF_MOVETYPE_RANDOMWAYPOINT,
                        &pX, &pY, cWaypoint, 0,
                        j, -1, false, false, bFirmBerserk, false, 0
                    );
                    break;
            }

            if (iResult == -1) {
                // Spawn failed, free naming value
                m_pMapList[iMapIndex]->SetNamingValueEmpty(iNamingValue);
            }
            else {
                // Spawn succeeded, increment counter
                m_pMapList[iMapIndex]->m_stSpotMobGenerator[j].iCurMobs++;
            }
        }
    }
}

bool CEntityManager::CanSpawnAtSpot(int iMapIndex, int iSpotIndex) const
{
    // TODO: Implement spawn condition checking
    // This will be implemented in Phase 2
    return false;
}

uint32_t CEntityManager::GenerateEntityGUID()
{
    uint32_t dwGUID = m_dwNextGUID++;

    // Handle wraparound (extremely unlikely, but safe)
    if (m_dwNextGUID == 0)
        m_dwNextGUID = 1;


    return dwGUID;
}
