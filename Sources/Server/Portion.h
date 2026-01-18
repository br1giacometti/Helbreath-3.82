// Portion.h: interface for the CPortion class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

// MODERNIZED: Prevent old winsock.h from loading (must be before windows.h)
#define _WINSOCKAPI_
#include <windows.h>
#include "CommonTypes.h"

class CPortion
{
public:
	inline CPortion()
	{
		int i;

		std::memset(m_cName, 0, sizeof(m_cName));
		m_iSkillLimit = 0;
		m_iDifficulty = 0;

		for (i = 0; i < 12; i++)
			m_sArray[i] = -1;
	}

	inline virtual ~CPortion()
	{

	}

	char  m_cName[21];
	short m_sArray[12];

	int   m_iSkillLimit, m_iDifficulty;

};
