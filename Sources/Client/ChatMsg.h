// Msg.h: interface for the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <windows.h>
#include <string.h>
#include <winbase.h>
#include "CommonTypes.h"

class CMsg
{
public:
	inline CMsg(char cType, char * pMsg, uint32_t dwTime)
	{
		m_cType = cType;

		m_pMsg = 0;
		const size_t msgLen = (pMsg != 0) ? strlen(pMsg) : 0;
		m_pMsg = new char [msgLen + 1];
		std::memset(m_pMsg, 0, msgLen + 1);
		if (pMsg != 0) {
			std::memcpy(m_pMsg, pMsg, msgLen);
		}
		m_dwTime = dwTime;
		m_iObjectID = -1;
	}

	inline virtual ~CMsg()
	{
		if (m_pMsg != 0) delete[] m_pMsg;
	}

	char   m_cType;
	char * m_pMsg;
	short  m_sX, m_sY;
	uint32_t  m_dwTime;

	int    m_iObjectID;

};
