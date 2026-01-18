#pragma once

#include <string>

struct sqlite3;
class CItem;
class CGame;

bool EnsureGameConfigDatabase(sqlite3** outDb, std::string& outPath, bool* outCreated);
bool SaveItemConfigs(sqlite3* db, CItem* const* itemList, int maxItems);
bool LoadItemConfigs(sqlite3* db, CItem** itemList, int maxItems);
bool SaveRealmConfig(sqlite3* db, const CGame* game);
bool LoadRealmConfig(sqlite3* db, CGame* game);
bool SaveSettingsConfig(sqlite3* db, const CGame* game);
bool LoadSettingsConfig(sqlite3* db, CGame* game);
bool SaveAdminListConfig(sqlite3* db, const CGame* game);
bool LoadAdminListConfig(sqlite3* db, CGame* game);
bool SaveBannedListConfig(sqlite3* db, const CGame* game);
bool LoadBannedListConfig(sqlite3* db, CGame* game);
bool SaveAdminSettingsConfig(sqlite3* db, const CGame* game);
bool LoadAdminSettingsConfig(sqlite3* db, CGame* game);
bool SaveNpcConfigs(sqlite3* db, const CGame* game);
bool LoadNpcConfigs(sqlite3* db, CGame* game);
bool LoadDropTables(sqlite3* db, CGame* game);
bool LoadShopConfigs(sqlite3* db, CGame* game);
bool SaveMagicConfigs(sqlite3* db, const CGame* game);
bool LoadMagicConfigs(sqlite3* db, CGame* game);
bool SaveSkillConfigs(sqlite3* db, const CGame* game);
bool LoadSkillConfigs(sqlite3* db, CGame* game);
bool SaveQuestConfigs(sqlite3* db, const CGame* game);
bool LoadQuestConfigs(sqlite3* db, CGame* game);
bool SavePortionConfigs(sqlite3* db, const CGame* game);
bool LoadPortionConfigs(sqlite3* db, CGame* game);
bool SaveBuildItemConfigs(sqlite3* db, const CGame* game);
bool LoadBuildItemConfigs(sqlite3* db, CGame* game);
bool SaveCrusadeConfig(sqlite3* db, const CGame* game);
bool LoadCrusadeConfig(sqlite3* db, CGame* game);
bool SaveScheduleConfig(sqlite3* db, const CGame* game);
bool LoadScheduleConfig(sqlite3* db, CGame* game);
bool HasGameConfigRows(sqlite3* db, const char* tableName);
void CloseGameConfigDatabase(sqlite3* db);
