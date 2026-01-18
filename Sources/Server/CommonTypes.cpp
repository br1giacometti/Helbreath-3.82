// CommonTypes.cpp: GameClock static storage
//////////////////////////////////////////////////////////////////////

#include "CommonTypes.h"

std::chrono::steady_clock::time_point GameClock::s_startTime;
bool GameClock::s_initialized = false;
