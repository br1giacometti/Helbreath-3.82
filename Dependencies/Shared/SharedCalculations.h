#pragma once

#include <cstdint>

// SharedCalculations.h - Shared Formulas for Client and Server
//
// This file contains stat and resource calculations that must be identical
// on both client and server to ensure consistency.

// ============================================================================
// Max Resource Calculations
// ============================================================================

// Calculate maximum HP
// Formula: Vit * 3 + Level * 2 + (Str + AngelicStr) / 2
inline int CalculateMaxHP(int iVit, int iLevel, int iStr, int iAngelicStr)
{
	return iVit * 3 + iLevel * 2 + (iStr + iAngelicStr) / 2;
}

// Calculate maximum MP
// Formula: (Mag + AngelicMag) * 2 + Level * 2 + (Int + AngelicInt) / 2
inline int CalculateMaxMP(int iMag, int iAngelicMag, int iLevel, int iInt, int iAngelicInt)
{
	return (iMag + iAngelicMag) * 2 + iLevel * 2 + (iInt + iAngelicInt) / 2;
}

// Calculate maximum SP (Stamina)
// Formula: (Str + AngelicStr) * 2 + Level * 2
inline int CalculateMaxSP(int iStr, int iAngelicStr, int iLevel)
{
	return (iStr + iAngelicStr) * 2 + iLevel * 2;
}

// ============================================================================
// Carry Weight Calculations
// ============================================================================

// Calculate maximum carry weight
// Formula: (Str + AngelicStr) * 5 + Level * 5
inline int CalculateMaxLoad(int iStr, int iAngelicStr, int iLevel)
{
	return (iStr + iAngelicStr) * 5 + iLevel * 5;
}

// ============================================================================
// Max Stat Calculations
// ============================================================================

// Calculate maximum stat value based on server configuration
// Formula: BaseStatValue + CreationStatBonus + (LevelupStatGain * MaxLevel) + AngelicBonus(16)
inline int CalculateMaxStatValue(int iBaseStatValue, int iCreationStatBonus, int iLevelupStatGain, int iMaxLevel)
{
	return iBaseStatValue + iCreationStatBonus + (iLevelupStatGain * iMaxLevel) + 16;
}

// ============================================================================
// Experience Calculations
// ============================================================================

// Calculate experience required for a given level
// Formula: Recursive - GetLevelExp(Level-1) + Level * (50 + (Level * (Level/17) * (Level/17)))
// Note: This is a recursive function - for performance, server pre-caches this in m_iLevelExpTable[]
inline uint32_t CalculateLevelExp(int iLevel)
{
	if (iLevel <= 0) return 0;
	return CalculateLevelExp(iLevel - 1) + iLevel * (50 + (iLevel * (iLevel / 17) * (iLevel / 17)));
}

// ============================================================================
// Level-Up Point Pool Calculations
// ============================================================================

// Calculate level-up stat points pool (server-side storage value)
// Formula: Level * 3 - (TotalStats - 70)
// Where TotalStats = Str + Vit + Dex + Int + Mag + Charisma
inline int CalculateLevelUpPool(int iLevel, int iTotalStats)
{
	return iLevel * 3 - (iTotalStats - 70);
}

// Calculate level-up stat points for display (client-side)
// Formula: Level * 3 - (TotalStats - 70) - 3
// The -3 accounts for base starting points in display
inline int CalculateLevelUpPointsDisplay(int iLevel, int iTotalStats)
{
	return CalculateLevelUpPool(iLevel, iTotalStats) - 3;
}
