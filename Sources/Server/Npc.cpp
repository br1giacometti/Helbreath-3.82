// Npc.cpp: implementation of the CNpc class.
//
//////////////////////////////////////////////////////////////////////

#include "CommonTypes.h"
#include "Npc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNpc::CNpc(char * pName5)
{
 int i;
	std::memset(m_cName, 0, sizeof(m_cName));
	memcpy(m_cName, pName5, 5);
	
	for (i = 0; i < DEF_MAXWAYPOINTS; i++)			  
		m_iWayPointIndex[i] = -1;
	
	for (i = 0; i < DEF_MAXMAGICEFFECTS; i++) 
		m_cMagicEffectStatus[i]	= 0;

	m_bIsSummoned       = false;
	m_bIsPermAttackMode = false;

	m_dwRegenTime = 0;
	m_bIsKilled   = false;

	m_sOriginalType      = 0;
	m_iSummonControlMode = 0;
	
	m_cAttribute = 0;
	m_iAbsDamage = 0;
	m_iStatus    = 0;
	m_sAppr2     = 0;

	m_iAttackRange    = 1;
	m_cSpecialAbility = 0;
	
	m_iExp = 0;

	m_iBuildCount = 0;
	m_iManaStock  = 0;
	m_bIsUnsummoned = false;
	m_cCropType = 0;
	m_cCropSkill = 0;

	m_bIsMaster  = false;
	m_iGuildGUID = 0;
	m_iV1 = 0;

	m_iNpcItemType = 0;
	m_iNpcItemMax = 0;
	m_iDropTableId = 0;

	// OPTIMIZATION FIX #3: Initialize previous position for delta detection
	m_sPrevX = -1;
	m_sPrevY = -1;

}

CNpc::~CNpc()
{

}


/*// .text:004BAFD0
// xfers to: m_vNpcItem.at, bGetItemNameWhenDeleteNpc, sub_4BC360
void CNpc::m_vNpcItem.size()
{
 int iRet;
 class CNpcItem * pTempNpcItem;
	
	if (pTempNpcItem->m_cName == 0) {
		iRet = 0;
	}
	else {
		iRet = pTempNpcItem->8 - (pTempNpcItem->m_cName >> 5);
	}
	return iRet;

}

// .text:.text:004BB010
// xfers to: bGetItemNameWhenDeleteNpc
// xfers from: sub_4BB3D0, sub_4BB340, m_vNpcItem.size
void CNpc::m_vNpcItem.at(int iResult)
{ 
	if (iResult < m_vNpcItem.size()) {
		sub_4BB3D0();
	}
	sub_4BB340() += (iResult << 5);

}*/
