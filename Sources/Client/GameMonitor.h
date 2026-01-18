// GameMonitor.h: interface for the CGameMonitor class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include "ChatMsg.h"

#define DEF_MAXBADWORD		500

class CGameMonitor  
{
public:
	bool bCheckBadWord(char * pWord);
	int iReadBadWordFileList(char * pFn);
	CGameMonitor();
	virtual ~CGameMonitor();

	class CMsg * m_pWordList[DEF_MAXBADWORD];

};
