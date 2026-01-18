// Fish.h: interface for the CFish class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

// MODERNIZED: Prevent old winsock.h from loading (must be before windows.h)
#define _WINSOCKAPI_

#include <windows.h>
#include "CommonTypes.h"
#include "item.h"

class CFish  
{
public:
	inline CFish(char cMapIndex, short sX, short sY, short sType, class CItem * pItem, int iDifficulty)
	{
		m_cMapIndex		= cMapIndex;
		m_sX			= sX;
		m_sY			= sY;
		m_sType			= sType;
		m_pItem			= pItem;

		m_sEngagingCount = 0;
		m_iDifficulty    = iDifficulty;

		if (m_iDifficulty <= 0)
			m_iDifficulty = 1;
	}

	inline virtual ~CFish()
	{
		if (m_pItem != 0) delete m_pItem;
	}

	char  m_cMapIndex;
	short m_sX, m_sY;			// �ʻ��� ��ġ 

	short m_sType;				// ������ ����  
	class CItem * m_pItem;		// �������� �Ҵ�Ǵ� ������(������ ���� ����)

	short m_sDynamicObjectHandle;

	short m_sEngagingCount;		// ���� �� �����⸦ �븮�� �ִ� �÷��̾� �� 
	int   m_iDifficulty;		// ���̵�. �ּ� 1�� �Ǿ�� �Ѵ�.
};

