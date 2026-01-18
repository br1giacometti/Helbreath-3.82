#include "CmdProfile.h"
#include "Game.h"
#include "FrameTiming.h"

bool CmdProfile::Execute(CGame* pGame, const char* pArgs)
{
	(void)pArgs;

	bool enabled = FrameTiming::IsProfilingEnabled();
	FrameTiming::SetProfilingEnabled(!enabled);

	if (!enabled) {
		pGame->AddEventList("Profiling enabled - stats displayed on screen", 10);
	}
	else {
		pGame->AddEventList("Profiling disabled", 10);
	}

	return true;
}
