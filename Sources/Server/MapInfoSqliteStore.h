#pragma once

#include <string>

struct sqlite3;
class CMap;

// Database management
bool EnsureMapInfoDatabase(sqlite3** outDb, std::string& outPath, bool* outCreated);
void CloseMapInfoDatabase(sqlite3* db);

// Load all map names from database (returns count, fills mapNames array)
int GetMapNamesFromDatabase(sqlite3* db, char mapNames[][11], int maxMaps);

// Load complete map configuration from database into CMap object
bool LoadMapConfig(sqlite3* db, const char* mapName, CMap* pMap);

// Individual loaders (used internally by LoadMapConfig)
bool LoadMapBaseSettings(sqlite3* db, const char* mapName, CMap* pMap);
bool LoadMapTeleportLocations(sqlite3* db, const char* mapName, CMap* pMap);
bool LoadMapInitialPoints(sqlite3* db, const char* mapName, CMap* pMap);
bool LoadMapWaypoints(sqlite3* db, const char* mapName, CMap* pMap);
bool LoadMapNoAttackAreas(sqlite3* db, const char* mapName, CMap* pMap);
bool LoadMapNpcAvoidRects(sqlite3* db, const char* mapName, CMap* pMap);
bool LoadMapSpotMobGenerators(sqlite3* db, const char* mapName, CMap* pMap);
bool LoadMapFishPoints(sqlite3* db, const char* mapName, CMap* pMap);
bool LoadMapMineralPoints(sqlite3* db, const char* mapName, CMap* pMap);
bool LoadMapStrategicPoints(sqlite3* db, const char* mapName, CMap* pMap);
bool LoadMapEnergySphereCreationPoints(sqlite3* db, const char* mapName, CMap* pMap);
bool LoadMapEnergySphereGoalPoints(sqlite3* db, const char* mapName, CMap* pMap);
bool LoadMapStrikePoints(sqlite3* db, const char* mapName, CMap* pMap);
bool LoadMapItemEvents(sqlite3* db, const char* mapName, CMap* pMap);
bool LoadMapHeldenianTowers(sqlite3* db, const char* mapName, CMap* pMap);
bool LoadMapHeldenianGateDoors(sqlite3* db, const char* mapName, CMap* pMap);
bool LoadMapNpcs(sqlite3* db, const char* mapName, CMap* pMap);
bool LoadMapApocalypseBoss(sqlite3* db, const char* mapName, CMap* pMap);
bool LoadMapDynamicGate(sqlite3* db, const char* mapName, CMap* pMap);

// Save functions (for admin tools / future use)
bool SaveMapConfig(sqlite3* db, const CMap* pMap);
bool SaveAllMapConfigs(sqlite3* db, CMap** pMapList, int mapCount);

// Utility
bool HasMapInfoRows(sqlite3* db, const char* tableName);
