#include "FrameTiming.h"
#include <cstring>

// Static member initialization
FrameTiming::TimePoint FrameTiming::s_frameStart;
FrameTiming::TimePoint FrameTiming::s_lastFrame;

double FrameTiming::s_deltaTime = 0.0;
double FrameTiming::s_accumulator = 0.0;
uint32_t FrameTiming::s_displayedThisSecond = 0;
uint32_t FrameTiming::s_fps = 0;
uint64_t FrameTiming::s_totalDisplayed = 0;

// Profiling static members
bool FrameTiming::s_profilingEnabled = false;
FrameTiming::TimePoint FrameTiming::s_stageStart[FrameTiming::STAGE_COUNT];
double FrameTiming::s_stageTimeMS[FrameTiming::STAGE_COUNT] = { 0 };
double FrameTiming::s_stageAccumMS[FrameTiming::STAGE_COUNT] = { 0 };
double FrameTiming::s_stageAvgMS[FrameTiming::STAGE_COUNT] = { 0 };
uint32_t FrameTiming::s_profileFrameCount = 0;

void FrameTiming::Initialize()
{
	s_lastFrame = Clock::now();
	s_deltaTime = 0.0;
	s_accumulator = 0.0;
	s_displayedThisSecond = 0;
	s_fps = 0;
	s_totalDisplayed = 0;

	// Initialize profiling
	s_profilingEnabled = false;
	s_profileFrameCount = 0;
	std::memset(s_stageTimeMS, 0, sizeof(s_stageTimeMS));
	std::memset(s_stageAccumMS, 0, sizeof(s_stageAccumMS));
	std::memset(s_stageAvgMS, 0, sizeof(s_stageAvgMS));
}

void FrameTiming::BeginFrame()
{
	s_frameStart = Clock::now();

	// Calculate delta time in seconds
	auto elapsed = std::chrono::duration<double>(s_frameStart - s_lastFrame);
	s_deltaTime = elapsed.count();

	// Clamp delta to prevent spiral of death (e.g., debugger pause)
	if (s_deltaTime > 0.25) s_deltaTime = 0.25;

	// Reset per-frame profiling times
	if (s_profilingEnabled)
	{
		std::memset(s_stageTimeMS, 0, sizeof(s_stageTimeMS));
		BeginProfile(ProfileStage::FrameTotal);
	}
}

void FrameTiming::EndFrame()
{
	// End total frame profiling
	if (s_profilingEnabled)
	{
		EndProfile(ProfileStage::FrameTotal);

		// Accumulate for averaging
		for (int i = 0; i < STAGE_COUNT; i++)
		{
			s_stageAccumMS[i] += s_stageTimeMS[i];
		}
		s_profileFrameCount++;
	}

	s_lastFrame = s_frameStart;
	s_accumulator += s_deltaTime;

	// Update FPS and profile averages every second
	if (s_accumulator >= 1.0)
	{
		s_fps = s_displayedThisSecond;
		s_displayedThisSecond = 0;
		s_accumulator -= 1.0;  // Preserve remainder for accuracy

		// Calculate profile averages
		if (s_profilingEnabled && s_profileFrameCount > 0)
		{
			for (int i = 0; i < STAGE_COUNT; i++)
			{
				s_stageAvgMS[i] = s_stageAccumMS[i] / s_profileFrameCount;
				s_stageAccumMS[i] = 0.0;
			}
			s_profileFrameCount = 0;
		}
	}
}

void FrameTiming::CountDisplayedFrame()
{
	// Called only when a frame is actually flipped/displayed
	s_totalDisplayed++;
	s_displayedThisSecond++;
}

double FrameTiming::GetDeltaTime()
{
	return s_deltaTime;
}

double FrameTiming::GetDeltaTimeMS()
{
	return s_deltaTime * 1000.0;
}

uint32_t FrameTiming::GetFPS()
{
	return s_fps;
}

uint64_t FrameTiming::GetFrameCount()
{
	return s_totalDisplayed;
}

// Profiling implementation
void FrameTiming::SetProfilingEnabled(bool enabled)
{
	if (enabled && !s_profilingEnabled)
	{
		// Reset when enabling
		s_profileFrameCount = 0;
		std::memset(s_stageTimeMS, 0, sizeof(s_stageTimeMS));
		std::memset(s_stageAccumMS, 0, sizeof(s_stageAccumMS));
		std::memset(s_stageAvgMS, 0, sizeof(s_stageAvgMS));
	}
	s_profilingEnabled = enabled;
}

bool FrameTiming::IsProfilingEnabled()
{
	return s_profilingEnabled;
}

void FrameTiming::BeginProfile(ProfileStage stage)
{
	if (!s_profilingEnabled) return;
	int idx = static_cast<int>(stage);
	if (idx >= 0 && idx < STAGE_COUNT)
	{
		s_stageStart[idx] = Clock::now();
	}
}

void FrameTiming::EndProfile(ProfileStage stage)
{
	if (!s_profilingEnabled) return;
	int idx = static_cast<int>(stage);
	if (idx >= 0 && idx < STAGE_COUNT)
	{
		auto now = Clock::now();
		auto elapsed = std::chrono::duration<double, std::milli>(now - s_stageStart[idx]);
		s_stageTimeMS[idx] += elapsed.count();  // += allows nested/multiple calls
	}
}

double FrameTiming::GetProfileTimeMS(ProfileStage stage)
{
	int idx = static_cast<int>(stage);
	if (idx >= 0 && idx < STAGE_COUNT)
		return s_stageTimeMS[idx];
	return 0.0;
}

double FrameTiming::GetProfileAvgTimeMS(ProfileStage stage)
{
	int idx = static_cast<int>(stage);
	if (idx >= 0 && idx < STAGE_COUNT)
		return s_stageAvgMS[idx];
	return 0.0;
}

const char* FrameTiming::GetStageName(ProfileStage stage)
{
	switch (stage)
	{
	case ProfileStage::Update:           return "Update";
	case ProfileStage::ClearBuffer:      return "ClearBuf";
	case ProfileStage::DrawBackground:   return "Background";
	case ProfileStage::DrawEffectLights: return "Lights";
	case ProfileStage::DrawObjects:      return "Objects";
	case ProfileStage::DrawEffects:      return "Effects";
	case ProfileStage::DrawWeather:      return "Weather";
	case ProfileStage::DrawChat:         return "Chat";
	case ProfileStage::DrawDialogs:      return "Dialogs";
	case ProfileStage::DrawMisc:         return "Misc";
	case ProfileStage::Flip:             return "Flip";
	case ProfileStage::FrameTotal:       return "Total";
	default:                             return "Unknown";
	}
}
