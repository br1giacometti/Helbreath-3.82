// Tile.h: interface for the CTile class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <windows.h>
#include <mmsystem.h>

class CTile
{
public:
	bool  m_bSpriteOmit;

	inline void Clear()
	{
		m_wObjectID     = 0;
		m_wDeadObjectID = 0;

		m_sOwnerType = 0;
		ZeroMemory(m_cOwnerName, sizeof(m_cOwnerName));

		m_sDeadOwnerType = 0;
		ZeroMemory(m_cDeadOwnerName, sizeof(m_cDeadOwnerName));

		m_cDeadOwnerFrame = -1;
		m_dwDeadOwnerTime = 0;

		m_cOwnerAction = 0;
		m_cDir         = 0;
		m_cOwnerFrame  = 0;

		m_sItemID = 0;
		m_dwItemAttr = 0;
		m_cItemColor       = 0;

		m_sDynamicObjectType  = 0;
		m_cDynamicObjectFrame = 0;

		m_iChatMsg     = 0;
		m_iDeadChatMsg = 0;

		m_iStatus      = 0;
		m_iDeadStatus  = 0;

		m_sV1 = 0;
		m_sV2 = 0;
		m_sV3 = 0;

		m_sAppr1 = 0;
		m_sAppr2 = 0;
		m_sAppr3 = 0;
		m_sAppr4 = 0;
		m_iApprColor = 0;

		m_iEffectType  = 0;
		m_iEffectFrame = 0;
		m_iEffectTotalFrame = 0;
		m_dwEffectTime = 0;

		m_dwOwnerTime        = 0;
	}

	inline CTile() : m_bSpriteOmit(false)
	{
		m_sOwnerType = 0;
		ZeroMemory(m_cOwnerName, sizeof(m_cOwnerName));
		m_sDeadOwnerType = 0;
		ZeroMemory(m_cDeadOwnerName, sizeof(m_cDeadOwnerName));
		m_cDeadOwnerFrame     = -1;

		m_sDynamicObjectType  = 0;
		m_cDynamicObjectFrame = 0;

		m_iChatMsg       = 0;
		m_iDeadChatMsg   = 0;

		m_wObjectID = 0;

		m_iEffectType  = 0;
		m_iEffectFrame = 0;
		m_iEffectTotalFrame = 0;
		m_dwEffectTime = 0;
	}

	inline virtual ~CTile()
	{
	}	
	DWORD m_dwOwnerTime;
	DWORD m_dwEffectTime;
	DWORD m_dwDeadOwnerTime;
	DWORD m_dwDynamicObjectTime;
	
	int   m_iChatMsg;
	int   m_cItemColor; // v1.4
	int   m_iEffectType;
	int   m_iDeadApprColor; // v1.4
	int   m_iEffectFrame, m_iEffectTotalFrame;
	int   m_iApprColor; // v1.4
	int   m_iDeadChatMsg;

	WORD  m_wDeadObjectID;
	WORD  m_wObjectID;

	short m_sOwnerType;							// +B2C
	short m_sAppr1;								// +B2E
	short m_sAppr2;								// +B30
	short m_sAppr3;								// +B32
	short m_sAppr4;								// +B34
	int m_iStatus;								// +B38
	
	short m_sDeadOwnerType;						// +B3C
	short m_sDeadAppr1;
	short m_sDeadAppr2;
	short m_sDeadAppr3;
	short m_sDeadAppr4;
	
	int m_iDeadStatus;
	short m_sV1;
	short m_sV2;					
	short m_sV3;								// +B50
	short m_sDynamicObjectType;

	short m_sItemID;
	DWORD m_dwItemAttr;

	char  m_cDeadOwnerFrame;
	char  m_cOwnerAction;						// +B59
	char  m_cOwnerFrame;						// +B5A
	char  m_cDir;
	char  m_cDeadDir;
	
	char  m_cDynamicObjectFrame;
	char  m_cDynamicObjectData1, m_cDynamicObjectData2, m_cDynamicObjectData3, m_cDynamicObjectData4;
	char  m_cOwnerName[12];
	char  m_cDeadOwnerName[12];
};
