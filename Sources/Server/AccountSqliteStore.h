#pragma once

#include <string>
#include <vector>

struct sqlite3;

struct AccountDbAccountData
{
    char name[11];
    char password[11];
    char email[52];
    char quiz[47];
    char answer[27];
    char createdAt[32];
    char passwordChangedAt[32];
    char lastIp[32];
};

struct AccountDbCharacterData
{
    char accountName[11];
    char characterName[11];
    char createdAt[32];
    short appr1;
    short appr2;
    short appr3;
    short appr4;
    uint32_t apprColor;
    int level;
    uint32_t exp;
    char mapName[11];
    int mapX;
    int mapY;
    int hp;
    int mp;
    int sp;
    int str;
    int vit;
    int dex;
    int intl;
    int mag;
    int chr;
    int gender;
    int skin;
    int hairStyle;
    int hairColor;
    int underwear;
};

struct AccountDbCharacterSummary
{
    char characterName[11];
    short appr1;
    short appr2;
    short appr3;
    short appr4;
    uint32_t apprColor;
    uint16_t sex;
    uint16_t skin;
    uint16_t level;
    uint32_t exp;
    char mapName[11];
};

struct AccountDbCharacterState
{
    char accountName[11];
    char characterName[11];
    char profile[256];
    char location[11];
    char guildName[21];
    int guildGuid;
    int guildRank;
    char mapName[11];
    int mapX;
    int mapY;
    int hp;
    int mp;
    int sp;
    int level;
    int rating;
    int str;
    int intl;
    int vit;
    int dex;
    int mag;
    int chr;
    int luck;
    uint32_t exp;
    int luPool;
    int enemyKillCount;
    int pkCount;
    uint32_t rewardGold;
    int downSkillIndex;
    int idnum1;
    int idnum2;
    int idnum3;
    int sex;
    int skin;
    int hairStyle;
    int hairColor;
    int underwear;
    int hungerStatus;
    int timeleftShutup;
    int timeleftRating;
    int timeleftForceRecall;
    int timeleftFirmStaminar;
    int adminUserLevel;
    int penaltyBlockYear;
    int penaltyBlockMonth;
    int penaltyBlockDay;
    int questNumber;
    int questId;
    int currentQuestCount;
    int questRewardType;
    int questRewardAmount;
    int contribution;
    int warContribution;
    int questCompleted;
    int specialEventId;
    int superAttackLeft;
    int fightzoneNumber;
    int reserveTime;
    int fightzoneTicketNumber;
    int specialAbilityTime;
    char lockedMapName[11];
    int lockedMapTime;
    int crusadeJob;
    uint32_t crusadeGuid;
    int constructPoint;
    int deadPenaltyTime;
    int partyId;
    int gizonItemUpgradeLeft;
    short appr1;
    short appr2;
    short appr3;
    short appr4;
    uint32_t apprColor;
};

struct AccountDbItemRow
{
    int slot;
    int itemId;
    int count;
    int touchEffectType;
    int touchEffectValue1;
    int touchEffectValue2;
    int touchEffectValue3;
    int itemColor;
    int specEffectValue1;
    int specEffectValue2;
    int specEffectValue3;
    int curLifeSpan;
    uint32_t attribute;
    int posX;
    int posY;
    int isEquipped;
};

struct AccountDbBankItemRow
{
    int slot;
    int itemId;
    int count;
    int touchEffectType;
    int touchEffectValue1;
    int touchEffectValue2;
    int touchEffectValue3;
    int itemColor;
    int specEffectValue1;
    int specEffectValue2;
    int specEffectValue3;
    int curLifeSpan;
    uint32_t attribute;
};

struct AccountDbIndexedValue
{
    int index;
    int value;
};

class CClient;

bool EnsureAccountDatabase(const char* accountName, sqlite3** outDb, std::string& outPath);
bool LoadAccountRecord(sqlite3* db, const char* accountName, AccountDbAccountData& outData);
bool UpdateAccountPassword(sqlite3* db, const char* accountName, const char* newPassword);
bool ListCharacterSummaries(sqlite3* db, const char* accountName, std::vector<AccountDbCharacterSummary>& outChars);
bool LoadCharacterState(sqlite3* db, const char* characterName, AccountDbCharacterState& outState);
bool LoadCharacterItems(sqlite3* db, const char* characterName, std::vector<AccountDbItemRow>& outItems);
bool LoadCharacterBankItems(sqlite3* db, const char* characterName, std::vector<AccountDbBankItemRow>& outItems);
bool LoadCharacterItemPositions(sqlite3* db, const char* characterName, std::vector<AccountDbIndexedValue>& outPositionsX, std::vector<AccountDbIndexedValue>& outPositionsY);
bool LoadCharacterItemEquips(sqlite3* db, const char* characterName, std::vector<AccountDbIndexedValue>& outEquips);
bool LoadCharacterMagicMastery(sqlite3* db, const char* characterName, std::vector<AccountDbIndexedValue>& outMastery);
bool LoadCharacterSkillMastery(sqlite3* db, const char* characterName, std::vector<AccountDbIndexedValue>& outMastery);
bool LoadCharacterSkillSSN(sqlite3* db, const char* characterName, std::vector<AccountDbIndexedValue>& outValues);
bool InsertCharacterState(sqlite3* db, const AccountDbCharacterState& state);
bool InsertCharacterItems(sqlite3* db, const char* characterName, const std::vector<AccountDbItemRow>& items);
bool InsertCharacterBankItems(sqlite3* db, const char* characterName, const std::vector<AccountDbBankItemRow>& items);
bool InsertCharacterItemPositions(sqlite3* db, const char* characterName, const std::vector<AccountDbIndexedValue>& positionsX, const std::vector<AccountDbIndexedValue>& positionsY);
bool InsertCharacterItemEquips(sqlite3* db, const char* characterName, const std::vector<AccountDbIndexedValue>& equips);
bool InsertCharacterMagicMastery(sqlite3* db, const char* characterName, const std::vector<AccountDbIndexedValue>& mastery);
bool InsertCharacterSkillMastery(sqlite3* db, const char* characterName, const std::vector<AccountDbIndexedValue>& mastery);
bool InsertCharacterSkillSSN(sqlite3* db, const char* characterName, const std::vector<AccountDbIndexedValue>& values);
bool InsertAccountRecord(sqlite3* db, const AccountDbAccountData& data);
bool InsertCharacterRecord(sqlite3* db, const AccountDbCharacterData& data);
bool SaveCharacterSnapshot(sqlite3* db, const CClient* client);
bool DeleteCharacterData(sqlite3* db, const char* characterName);
void CloseAccountDatabase(sqlite3* db);
