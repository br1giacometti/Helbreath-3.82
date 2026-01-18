// Effect.h: interface for the CEffect class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <windows.h>
#include "CommonTypes.h"

class CEffect
{
public:
	inline CEffect()
	{
		m_sType       = 0;
		m_cFrame      = -1;
		m_cMaxFrame   = 0;
		m_dwTime      = 0;
		m_dwFrameTime = 0;
	}

	inline virtual ~CEffect()
	{

	}

	short m_sType;
	char  m_cFrame, m_cMaxFrame;
	char  m_cDir;
	uint32_t m_dwTime, m_dwFrameTime;
	int   m_sX, m_sY, m_dX, m_dY;
	int   m_mX, m_mY, m_mX2, m_mY2, m_mX3, m_mY3;
	int   m_iErr;
	int   m_rX, m_rY;
	int   m_iV1;
};
