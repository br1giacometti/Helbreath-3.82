#pragma once

#include <cstdint>

struct DialogBoxInfo
{
	int sV1, sV2, sV3, sV4, sV5, sV6, sV7, sV8, sV9, sV10, sV11, sV12, sV13, sV14;
	uint32_t dwV1, dwV2, dwT1;
	bool bFlag;
	short sX, sY;
	short sSizeX, sSizeY;
	short sView;
	char cStr[32], cStr2[32], cStr3[32], cStr4[32];
	char cMode;
	bool bIsScrollSelected;
};
