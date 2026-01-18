// Skill.h: interface for the CSkill class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <windows.h>

class CSkill
{
public:
	inline CSkill()
	{
		ZeroMemory(m_cName, sizeof(m_cName));

		m_iLevel = 0;
		m_bIsUseable = false;
		m_cUseMethod = 0;
	}

	inline virtual ~CSkill()
	{
	}

	char m_cName[21];

	int  m_iLevel;
	bool m_bIsUseable;
	char m_cUseMethod;
};
