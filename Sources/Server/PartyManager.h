// PartyManager.h: interface for the PartyManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

// MODERNIZED: Prevent old winsock.h from loading (must be before windows.h)
#define _WINSOCKAPI_

#include <windows.h>
#include "CommonTypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "Game.h"

#define DEF_MAXPARTY		5000
#define DEF_MAXPARTYMEMBER	100


class PartyManager
{
public:
	void CheckMemberActivity();
	void SetServerChangeStatus(char* pName, int iPartyID);
	void GameServerDown();
	bool bGetPartyInfo(int iGSCH, char* pName, int iPartyID);
	bool bCheckPartyMember(int iGSCH, int iPartyID, char* pName);
	bool bRemoveMember(int iPartyID, char* pMemberName);
	bool bAddMember(int iPartyID, char* pMemberName);
	bool bDeleteParty(int iPartyID);
	int iCreateNewParty(char* pMasterName);
	PartyManager(class CGame* pGame);
	virtual ~PartyManager();

	int m_iMemberNumList[DEF_MAXPARTY];

	struct {
		int  m_iPartyID, m_iIndex;
		char m_cName[12];
		uint32_t m_dwServerChangeTime;
	} m_stMemberNameList[DEF_MAXPARTY];

	class CGame* m_pGame;
	uint32_t m_dwCheckMemberActTime;
};
