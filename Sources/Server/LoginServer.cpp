#include "CommonTypes.h"
#include "LoginServer.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

#include "AccountSqliteStore.h"
#include "sqlite3.h"
#include "../../Dependencies/Shared/Packet/SharedPackets.h"

extern char	G_cData50000[50000];
//extern void PutLogList(char* cMsg);
extern char G_cTxt[512];
extern class CGame* G_pGame;

#define WORLDNAMELS   "WS1"
#define WORLDNAMELS2   "WS2"

LoginServer::LoginServer()
{

}

LoginServer::~LoginServer()
{

}

bool IsValidName(char* pStr)
{
	int i, iLen;
	iLen = strlen(pStr);
	for (i = 0; i < iLen; i++)
	{
		//if (pStr[i] < 0)	return false;
		if ((pStr[i] == ',') || (pStr[i] == '=') || (pStr[i] == ' ') || (pStr[i] == '\n') ||
			(pStr[i] == '\t') || (pStr[i] == '.') || (pStr[i] == '\\') || (pStr[i] == '/') ||
			(pStr[i] == ':') || (pStr[i] == '*') || (pStr[i] == '?') || (pStr[i] == '<') ||
			(pStr[i] == '>') || (pStr[i] == '|') || (pStr[i] == '"') || (pStr[i] == '`') ||
			(pStr[i] == ';') || (pStr[i] == '=') || (pStr[i] == '@') || (pStr[i] == '[') ||
			(pStr[i] == ']') || (pStr[i] == '^') || (pStr[i] == '_') || (pStr[i] == '\'')) return false;
		//if ((pStr[i] < '0') || (pStr[i] > 'z')) return false;
	}
	return true;
}

void FormatTimestamp(const SYSTEMTIME& sysTime, char* outBuffer, size_t outBufferSize)
{
	std::snprintf(outBuffer, outBufferSize, "%04d-%02d-%02d %02d:%02d:%02d",
		sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
}

bool AccountDbExists(const char* accountName)
{
	char dbPath[MAX_PATH] = {};
	std::snprintf(dbPath, sizeof(dbPath), "Accounts\\%s.db", accountName);
	DWORD attrs = GetFileAttributes(dbPath);
	return (attrs != INVALID_FILE_ATTRIBUTES) && ((attrs & FILE_ATTRIBUTE_DIRECTORY) == 0);
}

bool OpenAccountDatabaseIfExists(const char* accountName, sqlite3** outDb)
{
	if (!AccountDbExists(accountName)) {
		return false;
	}
	std::string dbPath;
	return EnsureAccountDatabase(accountName, outDb, dbPath);
}

void LoginServer::Activated()
{
	
}

void LoginServer::RequestLogin(int h, char* pData)
{
	if (G_pGame->_lclients[h] == 0)
		return;

	char cName[11] = {};
	char cPassword[11] = {};
	char world_name[32] = {};

	const auto* req = hb::net::PacketCast<hb::net::LoginRequest>(pData, sizeof(hb::net::LoginRequest));
	if (!req) return;

	std::memcpy(cName, req->account_name, 10);
	std::memcpy(cPassword, req->password, 10);
	std::memcpy(world_name, req->world_name, 30);

	if (string(world_name) != WORLDNAMELS)
		return;

	if (!IsValidName(cName) || !IsValidName(cPassword) || !IsValidName(world_name))
		return;

	std::snprintf(G_cTxt, sizeof(G_cTxt), "(!) Account Request Login: %s", cName);
	PutLogList(G_cTxt);

	std::vector<AccountDbCharacterSummary> chars;
	auto status = AccountLogIn(cName, cPassword, chars);
	switch (status)
	{
	case LogIn::Ok:
	{
		char pData[512] = {};
		char* cp2 = pData;
		Push(cp2, (int)chars.size());
		GetCharList(cName, cp2, chars);
		SendLoginMsg(DEF_LOGRESMSGTYPE_CONFIRM, DEF_LOGRESMSGTYPE_CONFIRM, pData, cp2 - pData, h);
		//PutLogList("Ok");
		break;
	}

	case LogIn::NoAcc:
		SendLoginMsg(DEF_LOGRESMSGTYPE_NOTEXISTINGACCOUNT, DEF_LOGRESMSGTYPE_NOTEXISTINGACCOUNT, 0, 0, h);
		PutLogList("No Acc");
		break;

	case LogIn::NoPass:
		SendLoginMsg(DEF_LOGRESMSGTYPE_PASSWORDMISMATCH, DEF_LOGRESMSGTYPE_PASSWORDMISMATCH, 0, 0, h);
		PutLogList("No Pass");
		break;
	}
}

void LoginServer::GetCharList(string acc, char*& cp2, const std::vector<AccountDbCharacterSummary>& chars)
{
	for (const auto& entry : chars)
	{
		Push(cp2, entry.characterName, 10);
		Push(cp2, entry.appr1);
		Push(cp2, entry.appr2);
		Push(cp2, entry.appr3);
		Push(cp2, entry.appr4);
		Push(cp2, entry.sex);
		Push(cp2, entry.skin);
		Push(cp2, entry.level);
		Push(cp2, entry.exp);
		Push(cp2, entry.apprColor);
		Push(cp2, entry.mapName, 10);
	}
}


LogIn LoginServer::AccountLogIn(string acc, string pass, std::vector<AccountDbCharacterSummary>& chars)
{
	if (acc.size() == 0)
		return LogIn::NoAcc;

	if (pass.size() == 0)
		return LogIn::NoPass;

	sqlite3* db = nullptr;
	if (!OpenAccountDatabaseIfExists(acc.c_str(), &db)) {
		return LogIn::NoAcc;
	}

	AccountDbAccountData account = {};
	if (!LoadAccountRecord(db, acc.c_str(), account)) {
		CloseAccountDatabase(db);
		return LogIn::NoAcc;
	}

	if (pass != account.password) {
		CloseAccountDatabase(db);
		return LogIn::NoPass;
	}

	chars.clear();
	if (!ListCharacterSummaries(db, acc.c_str(), chars)) {
		CloseAccountDatabase(db);
		return LogIn::NoAcc;
	}

	CloseAccountDatabase(db);
	PutLogList("Account Login!");
	return LogIn::Ok;
}

void LoginServer::ResponseCharacter(int h, char* pData)
{
	char cName[11] = {};
	char cAcc[11] = {};
	char cPassword[11] = {};
	char world_name[32] = {};

	char gender, skin, hairstyle, haircolor, under, str, vit, dex, intl, mag, chr;

	const auto* req = hb::net::PacketCast<hb::net::CreateCharacterRequest>(pData, sizeof(hb::net::CreateCharacterRequest));
	if (!req) return;

	std::memcpy(cName, req->character_name, 10);
	std::memcpy(cAcc, req->account_name, 10);
	std::memcpy(cPassword, req->password, 10);
	std::memcpy(world_name, req->world_name, 30);
	gender = static_cast<char>(req->gender);
	skin = static_cast<char>(req->skin);
	hairstyle = static_cast<char>(req->hairstyle);
	haircolor = static_cast<char>(req->haircolor);
	under = static_cast<char>(req->underware);
	str = static_cast<char>(req->str);
	vit = static_cast<char>(req->vit);
	dex = static_cast<char>(req->dex);
	intl = static_cast<char>(req->intl);
	mag = static_cast<char>(req->mag);
	chr = static_cast<char>(req->chr);

	if (string(world_name) != WORLDNAMELS)
		return;

	std::snprintf(G_cTxt, sizeof(G_cTxt), "(!) Request create new Character: %s", cName);
	PutLogList(G_cTxt);

	std::vector<AccountDbCharacterSummary> chars;
	auto status = AccountLogIn(cAcc, cPassword, chars);
	if (status != LogIn::Ok)
		return;

	if (chars.size() >= 4)
		return;

	if (!IsValidName(cAcc) || !IsValidName(cPassword) || !IsValidName(cName))
		return;

	for (const auto& entry : chars) {
		if (std::strncmp(entry.characterName, cName, 10) == 0) {
			SendLoginMsg(DEF_LOGRESMSGTYPE_NEWCHARACTERFAILED, DEF_LOGRESMSGTYPE_NEWCHARACTERFAILED, 0, 0, h);
			return;
		}
	}

	sqlite3* db = nullptr;
	std::string dbPath;
	if (!EnsureAccountDatabase(cAcc, &db, dbPath)) {
		SendLoginMsg(DEF_LOGRESMSGTYPE_NEWCHARACTERFAILED, DEF_LOGRESMSGTYPE_NEWCHARACTERFAILED, 0, 0, h);
		return;
	}

	AccountDbCharacterState state = {};
	std::snprintf(state.accountName, sizeof(state.accountName), "%s", cAcc);
	std::snprintf(state.characterName, sizeof(state.characterName), "%s", cName);
	std::snprintf(state.profile, sizeof(state.profile), "__________");
	std::snprintf(state.location, sizeof(state.location), "NONE");
	std::snprintf(state.guildName, sizeof(state.guildName), "NONE");
	state.guildGuid = -1;
	state.guildRank = -1;
	std::snprintf(state.mapName, sizeof(state.mapName), "default");
	state.mapX = -1;
	state.mapY = -1;
	state.hp = vit * 3 + 1 * 2 + str / 2;
	state.mp = (mag) * 2 + 1 * 2 + (intl) / 2;
	state.sp = 1 * 2 + str * 2;
	state.level = 1;
	state.rating = 0;
	state.str = str;
	state.intl = intl;
	state.vit = vit;
	state.dex = dex;
	state.mag = mag;
	state.chr = chr;
	state.luck = 10;
	state.exp = 0;
	state.luPool = 0;
	state.enemyKillCount = 0;
	state.pkCount = 0;
	state.rewardGold = 0;
	state.downSkillIndex = -1;
	state.idnum1 = 0;
	state.idnum2 = 0;
	state.idnum3 = 0;
	state.sex = gender;
	state.skin = skin;
	state.hairStyle = hairstyle;
	state.hairColor = haircolor;
	state.underwear = under;
	state.hungerStatus = 100;
	state.timeleftShutup = 0;
	state.timeleftRating = 0;
	state.timeleftForceRecall = 0;
	state.timeleftFirmStaminar = 0;
	state.adminUserLevel = 0;
	state.penaltyBlockYear = 0;
	state.penaltyBlockMonth = 0;
	state.penaltyBlockDay = 0;
	state.questNumber = 0;
	state.questId = 0;
	state.currentQuestCount = 0;
	state.questRewardType = 0;
	state.questRewardAmount = 0;
	state.contribution = 0;
	state.warContribution = 0;
	state.questCompleted = 0;
	state.specialEventId = 200081;
	state.superAttackLeft = 0;
	state.fightzoneNumber = 0;
	state.reserveTime = 0;
	state.fightzoneTicketNumber = 0;
	state.specialAbilityTime = DEF_SPECABLTYTIMESEC;
	std::snprintf(state.lockedMapName, sizeof(state.lockedMapName), "NONE");
	state.lockedMapTime = 0;
	state.crusadeJob = 0;
	state.crusadeGuid = 0;
	state.constructPoint = 0;
	state.deadPenaltyTime = 0;
	state.partyId = 0;
	state.gizonItemUpgradeLeft = 0;
	state.appr1 = 1187;
	state.appr2 = 0;
	state.appr3 = 0;
	state.appr4 = 0;
	state.apprColor = 0;

	bool ok = InsertCharacterState(db, state);

	// Starter item IDs from GameConfigs.db
	constexpr int ITEM_DAGGER = 1;
	constexpr int ITEM_BIG_RED_POTION = 92;    // Health potion
	constexpr int ITEM_BIG_BLUE_POTION = 94;   // Mana potion
	constexpr int ITEM_MAP = 104;
	constexpr int ITEM_RECALL_SCROLL = 114;
	constexpr int ITEM_KNEE_TROUSERS_M = 460;  // Shorts for males
	constexpr int ITEM_BODICE_W = 473;         // Bodice for females

	std::vector<AccountDbItemRow> items;
	auto addItem = [&](int itemId, int itemColor) {
		AccountDbItemRow item = {};
		item.slot = static_cast<int>(items.size());
		item.itemId = itemId;
		item.count = 1;
		item.touchEffectType = 0;
		item.touchEffectValue1 = 0;
		item.touchEffectValue2 = 0;
		item.touchEffectValue3 = 0;
		item.itemColor = itemColor;
		item.specEffectValue1 = 0;
		item.specEffectValue2 = 0;
		item.specEffectValue3 = 0;
		item.curLifeSpan = 300;
		item.attribute = 0;
		item.posX = 40;
		item.posY = 30;
		item.isEquipped = 0;
		items.push_back(item);
	};

	addItem(ITEM_DAGGER, 0);
	addItem(ITEM_RECALL_SCROLL, 0);
	addItem(ITEM_BIG_RED_POTION, 0);
	addItem(ITEM_BIG_BLUE_POTION, 0);
	addItem(ITEM_MAP, 0);

	// Gender-specific clothing: males get shorts, females get bodice
	if (gender == 1) {
		addItem(ITEM_KNEE_TROUSERS_M, 0);
	} else {
		addItem(ITEM_BODICE_W, 0);
	}

	const char* equipStatus = "00000110000000000000000000000000000000000000000000";
	const size_t equipLen = std::strlen(equipStatus);
	for (auto& item : items) {
		if (item.slot < static_cast<int>(equipLen) && equipStatus[item.slot] == '1') {
			item.isEquipped = 1;
		}
	}

	std::vector<AccountDbIndexedValue> positionsX;
	std::vector<AccountDbIndexedValue> positionsY;
	std::vector<AccountDbIndexedValue> equips;
	for (int i = 0; i < DEF_MAXITEMS; i++) {
		AccountDbIndexedValue posX = {};
		AccountDbIndexedValue posY = {};
		AccountDbIndexedValue equip = {};
		posX.index = i;
		posY.index = i;
		equip.index = i;
		posX.value = 40;
		posY.value = 30;
		equip.value = (i < static_cast<int>(equipLen) && equipStatus[i] == '1') ? 1 : 0;
		positionsX.push_back(posX);
		positionsY.push_back(posY);
		equips.push_back(equip);
	}

	std::vector<AccountDbIndexedValue> magicMastery;
	for (int i = 0; i < DEF_MAXMAGICTYPE; i++) {
		AccountDbIndexedValue entry = {};
		entry.index = i;
		entry.value = 0;
		magicMastery.push_back(entry);
	}

	std::vector<AccountDbIndexedValue> skillMastery;
	std::vector<AccountDbIndexedValue> skillSsn;
	const char* skillSeed = "0 0 0 3 20 24 0 24 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0";
	char skillBuf[512] = {};
	std::snprintf(skillBuf, sizeof(skillBuf), "%s", skillSeed);
	char* token = std::strtok(skillBuf, " " );
	int skillIndex = 0;
	while (token != nullptr && skillIndex < DEF_MAXSKILLTYPE) {
		AccountDbIndexedValue entry = {};
		entry.index = skillIndex;
		entry.value = std::atoi(token);
		skillMastery.push_back(entry);
		skillIndex++;
		token = std::strtok(nullptr, " " );
	}
	for (; skillIndex < DEF_MAXSKILLTYPE; skillIndex++) {
		AccountDbIndexedValue entry = {};
		entry.index = skillIndex;
		entry.value = 0;
		skillMastery.push_back(entry);
	}
	for (int i = 0; i < DEF_MAXSKILLTYPE; i++) {
		AccountDbIndexedValue entry = {};
		entry.index = i;
		entry.value = 0;
		skillSsn.push_back(entry);
	}

	if (ok) {
		ok &= InsertCharacterItems(db, cName, items);
		ok &= InsertCharacterItemPositions(db, cName, positionsX, positionsY);
		ok &= InsertCharacterItemEquips(db, cName, equips);
		ok &= InsertCharacterMagicMastery(db, cName, magicMastery);
		ok &= InsertCharacterSkillMastery(db, cName, skillMastery);
		ok &= InsertCharacterSkillSSN(db, cName, skillSsn);
	}

	CloseAccountDatabase(db);

	if (!ok) {
		SendLoginMsg(DEF_LOGRESMSGTYPE_NEWCHARACTERFAILED, DEF_LOGRESMSGTYPE_NEWCHARACTERFAILED, 0, 0, h);
		return;
	}

	AccountDbCharacterSummary summary = {};
	std::snprintf(summary.characterName, sizeof(summary.characterName), "%s", cName);
	summary.appr1 = state.appr1;
	summary.appr2 = state.appr2;
	summary.appr3 = state.appr3;
	summary.appr4 = state.appr4;
	summary.apprColor = state.apprColor;
	summary.sex = static_cast<uint16_t>(state.sex);
	summary.skin = static_cast<uint16_t>(state.skin);
	summary.level = static_cast<uint16_t>(state.level);
	summary.exp = state.exp;
	std::snprintf(summary.mapName, sizeof(summary.mapName), "%s", state.mapName);
	chars.push_back(summary);

	char cData[512] = {};
	char* cp2 = cData;
	Push(cp2, cName, 10);
	Push(cp2, (int)chars.size());
	GetCharList(cAcc, cp2, chars);
	SendLoginMsg(DEF_LOGRESMSGTYPE_NEWCHARACTERCREATED, DEF_LOGRESMSGTYPE_NEWCHARACTERCREATED, cData, cp2 - cData, h);
}

void LoginServer::DeleteCharacter(int h, char* pData)
{
	char cName[11] = {};
	char cAcc[11] = {};
	char cPassword[11] = {};
	char world_name[32] = {};

	const auto* req = hb::net::PacketCast<hb::net::DeleteCharacterRequest>(pData, sizeof(hb::net::DeleteCharacterRequest));
	if (!req) return;

	std::memcpy(cName, req->character_name, 10);
	std::memcpy(cAcc, req->account_name, 10);
	std::memcpy(cPassword, req->password, 10);
	std::memcpy(world_name, req->world_name, 30);

	std::snprintf(G_cTxt, sizeof(G_cTxt), "(!) Request delete Character: %s", cName);
	PutLogList(G_cTxt);

	std::vector<AccountDbCharacterSummary> chars;
	auto status = AccountLogIn(cAcc, cPassword, chars);
	if (status != LogIn::Ok)
		return;

	if (chars.size() == 0)
		return;

	sqlite3* db = nullptr;
	if (!OpenAccountDatabaseIfExists(cAcc, &db)) {
		return;
	}

	if (!DeleteCharacterData(db, cName)) {
		CloseAccountDatabase(db);
		return;
	}

	CloseAccountDatabase(db);

	for (auto it = chars.begin(); it != chars.end();) {
		if (std::strncmp(it->characterName, cName, 10) == 0) {
			it = chars.erase(it);
			continue;
		}
		++it;
	}

	char cData[512] = {};
	char* cp2 = cData;
	Push(cp2, (int)chars.size());
	GetCharList(cAcc, cp2, chars);
	SendLoginMsg(DEF_LOGRESMSGTYPE_CHARACTERDELETED, DEF_LOGRESMSGTYPE_CHARACTERDELETED, cData, cp2 - cData, h);
}

void LoginServer::ChangePassword(int h, char* pData)
{
	char cAcc[11] = {};
	char cPassword[11] = {};
	char cNewPw[11] = {};
	char cNewPwConf[11] = {};

	const auto* req = hb::net::PacketCast<hb::net::ChangePasswordRequest>(pData, sizeof(hb::net::ChangePasswordRequest));
	if (!req) return;

	std::memcpy(cAcc, req->account_name, 10);
	std::memcpy(cPassword, req->password, 10);
	std::memcpy(cNewPw, req->new_password, 10);
	std::memcpy(cNewPwConf, req->new_password_confirm, 10);

	std::snprintf(G_cTxt, sizeof(G_cTxt), "(!) Request change password: %s", cAcc);
	PutLogList(G_cTxt);

	std::vector<AccountDbCharacterSummary> chars;
	auto status = AccountLogIn(cAcc, cPassword, chars);
	if (status != LogIn::Ok)
		return;

	if (string(cNewPw) != cNewPwConf) {
		SendLoginMsg(DEF_LOGRESMSGTYPE_PASSWORDCHANGEFAIL, DEF_LOGRESMSGTYPE_PASSWORDCHANGEFAIL, 0, 0, h);
		return;
	}

	sqlite3* db = nullptr;
	if (!OpenAccountDatabaseIfExists(cAcc, &db)) {
		SendLoginMsg(DEF_LOGRESMSGTYPE_PASSWORDCHANGEFAIL, DEF_LOGRESMSGTYPE_PASSWORDCHANGEFAIL, 0, 0, h);
		return;
	}

	if (UpdateAccountPassword(db, cAcc, cNewPw)) {
		SendLoginMsg(DEF_LOGRESMSGTYPE_PASSWORDCHANGESUCCESS, DEF_LOGRESMSGTYPE_PASSWORDCHANGESUCCESS, 0, 0, h);
	}
	else {
		SendLoginMsg(DEF_LOGRESMSGTYPE_PASSWORDCHANGEFAIL, DEF_LOGRESMSGTYPE_PASSWORDCHANGEFAIL, 0, 0, h);
	}

	CloseAccountDatabase(db);
}

void LoginServer::CreateNewAccount(int h, char* pData)
{
	char cName[12] = {};
	char cPassword[12] = {};
	char cEmailAddr[52] = {};
	char cQuiz[47] = {};
	char cAnswer[27] = {};

	if (G_pGame->_lclients[h] == 0)
		return;

	const auto* req = hb::net::PacketCast<hb::net::CreateAccountRequest>(pData, sizeof(hb::net::CreateAccountRequest));
	if (!req) return;

	std::memcpy(cName, req->account_name, 10);
	std::memcpy(cPassword, req->password, 10);
	std::memcpy(cEmailAddr, req->email, 50);
	std::memcpy(cQuiz, req->quiz, 45);
	std::memcpy(cAnswer, req->answer, 25);

	if ((strlen(cName) == 0) || (strlen(cPassword) == 0) ||
		(strlen(cEmailAddr) == 0) || (strlen(cQuiz) == 0) ||
		(strlen(cAnswer) == 0))
		return;

	std::snprintf(G_cTxt, sizeof(G_cTxt), "(!) Request create new Account: %s", cName);
	PutLogList(G_cTxt);

	if (!IsValidName(cName) || !IsValidName(cPassword))
		return;

	if (AccountDbExists(cName)) {
		SendLoginMsg(DEF_LOGRESMSGTYPE_NEWACCOUNTFAILED, DEF_LOGRESMSGTYPE_NEWACCOUNTFAILED, 0, 0, h);
		return;
	}

	sqlite3* db = nullptr;
	std::string dbPath;
	if (!EnsureAccountDatabase(cName, &db, dbPath)) {
		SendLoginMsg(DEF_LOGRESMSGTYPE_NEWACCOUNTFAILED, DEF_LOGRESMSGTYPE_NEWACCOUNTFAILED, 0, 0, h);
		return;
	}

	AccountDbAccountData data = {};
	std::snprintf(data.name, sizeof(data.name), "%s", cName);
	std::snprintf(data.password, sizeof(data.password), "%s", cPassword);
	std::snprintf(data.email, sizeof(data.email), "%s", cEmailAddr);
	std::snprintf(data.quiz, sizeof(data.quiz), "%s", cQuiz);
	std::snprintf(data.answer, sizeof(data.answer), "%s", cAnswer);

	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	FormatTimestamp(sysTime, data.createdAt, sizeof(data.createdAt));
	FormatTimestamp(sysTime, data.passwordChangedAt, sizeof(data.passwordChangedAt));
	std::snprintf(data.lastIp, sizeof(data.lastIp), "%s", G_pGame->_lclients[h]->_ip);

	if (!InsertAccountRecord(db, data)) {
		CloseAccountDatabase(db);
		SendLoginMsg(DEF_LOGRESMSGTYPE_NEWACCOUNTFAILED, DEF_LOGRESMSGTYPE_NEWACCOUNTFAILED, 0, 0, h);
		return;
	}

	CloseAccountDatabase(db);
	SendLoginMsg(DEF_LOGRESMSGTYPE_NEWACCOUNTCREATED, DEF_LOGRESMSGTYPE_NEWACCOUNTCREATED, 0, 0, h);
}

void LoginServer::SendLoginMsg(uint32_t msg_id, uint16_t msg_type, char* data, int sz, int h)
{

	int iRet;
	char* cp;
	int index = h;

	if (!G_pGame->_lclients[h])
		return;

	std::memset(G_cData50000, 0, sizeof(G_cData50000));

	auto* header = reinterpret_cast<hb::net::PacketHeader*>(G_cData50000);
	header->msg_id = msg_id;
	header->msg_type = msg_type;

	cp = reinterpret_cast<char*>(G_cData50000) + sizeof(hb::net::PacketHeader);

	memcpy((char*)cp, data, sz);

	//if is registered
	if (true)
	{
		iRet = G_pGame->_lclients[index]->_sock->iSendMsg(G_cData50000, sz + 6);

		switch (iRet)
		{
		case DEF_XSOCKEVENT_QUENEFULL:
		case DEF_XSOCKEVENT_SOCKETERROR:
		case DEF_XSOCKEVENT_CRITICALERROR:
		case DEF_XSOCKEVENT_SOCKETCLOSED:
			std::snprintf(G_cTxt, sizeof(G_cTxt), "(!) Login Connection Lost on Send (%d)", index);
			PutLogList(G_cTxt);
			delete G_pGame->_lclients[index];
			G_pGame->_lclients[index] = 0;
			return;
		}
	}
}

void LoginServer::RequestEnterGame(int h, char* pData)
{
	//	PutLogList("RequestEnterGame()");

	char cName[11] = {};
	char cMapName[11] = {};
	char cAcc[11] = {};
	char cPass[11] = {};
	int lvl;
	char ws_name[31] = {};
	char cmd_line[121] = {};

	const auto* req = hb::net::PacketCast<hb::net::EnterGameRequest>(pData, sizeof(hb::net::EnterGameRequest));
	if (!req) return;

	std::memcpy(cName, req->character_name, 10);
	std::memcpy(cMapName, req->map_name, 10);
	std::memcpy(cAcc, req->account_name, 10);
	std::memcpy(cPass, req->password, 10);
	lvl = req->level;
	std::memcpy(ws_name, req->world_name, 10);
	std::memcpy(cmd_line, req->cmd_line, 120);

	char cData[112] = {};
	char* cp2 = cData;
	if (string(ws_name) != WORLDNAMELS)
	{
		//SendEventToWLS(ENTERGAMERESTYPE_REJECT, ENTERGAMERESTYPE_REJECT, 0, 0, h);
		return;
	}

	std::snprintf(G_cTxt, sizeof(G_cTxt), "(!) Request enter Game: %s", cName);
	PutLogList(G_cTxt);

	std::vector<AccountDbCharacterSummary> chars;
	auto status = AccountLogIn(cAcc, cPass, chars);
	if (status != LogIn::Ok)
		return;

	for (int i = 0; i < DEF_MAXCLIENTS; i++)
	{
		if (!G_pGame->m_pClientList[i])
			continue;

		if (string(G_pGame->m_pClientList[i]->m_cAccountName) == cAcc)
		{
			G_pGame->DeleteClient(i, true, true);
			break;
		}
	}

	cp2 = (char*)cData; //outgoing messag - to Client

	memcpy(cp2, (char*)G_pGame->m_cGameListenIP, 16);
	cp2 += 16;

	auto wp = (uint16_t*)cp2;
	*wp = (uint16_t)G_pGame->m_iGameListenPort;
	cp2 += 2;

	char sv_name[21] = {};
	std::snprintf(sv_name, sizeof(sv_name), "%s", WORLDNAMELS2);
	memcpy(cp2, sv_name, 20);
	cp2 += 20;

	SendLoginMsg(DEF_ENTERGAMERESTYPE_CONFIRM, DEF_ENTERGAMERESTYPE_CONFIRM, cData, 38, h);
}


void LoginServer::LocalSavePlayerData(int h)
{
	if (G_pGame->m_pClientList[h] == 0) return;

	sqlite3* db = nullptr;
	std::string dbPath;
	if (EnsureAccountDatabase(G_pGame->m_pClientList[h]->m_cAccountName, &db, dbPath)) {
		if (!SaveCharacterSnapshot(db, G_pGame->m_pClientList[h])) {
			char logMsg[256] = {};
			std::snprintf(logMsg, sizeof(logMsg),
				"(SQLITE) SaveCharacterSnapshot failed: Account(%s) Char(%s) Error(%s)",
				G_pGame->m_pClientList[h]->m_cAccountName,
				G_pGame->m_pClientList[h]->m_cCharName,
				sqlite3_errmsg(db));
			PutLogList(logMsg);
		}
		CloseAccountDatabase(db);
	} else {
		char logMsg[256] = {};
		std::snprintf(logMsg, sizeof(logMsg),
			"(SQLITE) EnsureAccountDatabase failed: Account(%s)",
			G_pGame->m_pClientList[h]->m_cAccountName);
		PutLogList(logMsg);
	}
}
