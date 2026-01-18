// Mineral.h: interface for the CMineral class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include "CommonTypes.h"

class CMineral
{
public:
	inline CMineral(char cType, char cMapIndex, int sX, int sY, int iRemain)
	{
		m_cType = cType;
		m_cMapIndex = cMapIndex;
		m_sX = sX;
		m_sY = sY;;
		m_iRemain = iRemain;
		m_iDifficulty = 0;
	}

	inline virtual ~CMineral()
	{

	}

	char  m_cType;

	char  m_cMapIndex;
	int   m_sX, m_sY;
	int   m_iDifficulty;
	short m_sDynamicObjectHandle;

	int   m_iRemain;
};
