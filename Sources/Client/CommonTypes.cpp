// CommonTypes.cpp: Implementation of CommonTypes.h
//
//////////////////////////////////////////////////////////////////////

#include "CommonTypes.h"

// Static member initialization for GameClock
std::chrono::steady_clock::time_point GameClock::s_startTime;
bool GameClock::s_initialized = false;
