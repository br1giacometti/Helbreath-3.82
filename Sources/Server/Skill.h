// Skill.h: interface for the CSkill class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

// MODERNIZED: Prevent old winsock.h from loading (must be before windows.h)
#define _WINSOCKAPI_

#include <windows.h>
#include "CommonTypes.h"



#define DEF_SKILLEFFECTTYPE_GET			    1		// ��´�. �����⳪ ������ 
#define DEF_SKILLEFFECTTYPE_PRETEND			2		// ...�� ü �ϴ� 
#define DEF_SKILLEFFECTTYPE_TAMING			3		//  ����̱� �迭	


class CSkill
{
public:
	inline CSkill()
	{
		std::memset(m_cName, 0, sizeof(m_cName));
	}

	inline virtual ~CSkill()
	{
	}

	char m_cName[21];

	short m_sType;
	short m_sValue1, m_sValue2, m_sValue3, m_sValue4, m_sValue5, m_sValue6;

};
