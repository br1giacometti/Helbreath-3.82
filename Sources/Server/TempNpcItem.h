// TeleportLoc.h: interface for the CTeleportLoc class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

// MODERNIZED: Prevent old winsock.h from loading (must be before windows.h)
#define _WINSOCKAPI_
#include <windows.h>
#include "CommonTypes.h"

class CNpcItem
{
public:
	inline CNpcItem()
	{
		std::memset(m_cName, 0, sizeof(m_cName));

		m_sItemID = 0;
		m_sFirstProbability = 0;
		m_cFirstTargetValue = 0;
		m_sSecondProbability = 0;
		m_cSecondTargetValue = 0;
	}

	inline virtual ~CNpcItem()
	{
	}

	char m_cName[21];
	short m_sItemID;
	short m_sFirstProbability;
	short m_sSecondProbability;
	char m_cFirstTargetValue;
	char m_cSecondTargetValue;

};
