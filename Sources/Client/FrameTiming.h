#pragma once

#include <chrono>
#include <stdint.h>

// Profiling stage IDs - add new stages here
enum class ProfileStage {
	Update,           // UpdateScreen logic
	ClearBuffer,      // ClearBackB4
	DrawBackground,   // Map tiles
	DrawEffectLights, // Lighting effects
	DrawObjects,      // Characters, NPCs, items
	DrawEffects,      // Particle effects
	DrawWeather,      // Weather effects
	DrawChat,         // Chat messages
	DrawDialogs,      // Dialog boxes/UI
	DrawMisc,         // Misc rendering (tooltips, cursor, etc.)
	Flip,             // iFlip to display
	FrameTotal,       // Total frame time
	COUNT             // Must be last
};

// FrameTiming: Per-frame timing metrics and profiling
//
// Works alongside GameClock to provide frame-specific timing:
//   - Delta time between frames
//   - Accurate FPS calculation
//   - Frame counting
//   - Per-stage profiling
//
// GameClock provides: GetTimeMS() for general elapsed time
// FrameTiming provides: Per-frame delta, FPS metrics, and profiling
//
// Usage:
//   FrameTiming::Initialize();  // Call once at startup (after GameClock::Initialize)
//
//   // In game loop:
//   FrameTiming::BeginFrame();
//   // ... update and render ...
//   FrameTiming::EndFrame();
//
//   double dt = FrameTiming::GetDeltaTime();  // Seconds since last frame
//   uint32_t fps = FrameTiming::GetFPS();     // Current FPS
//
// Profiling Usage:
//   FrameTiming::BeginProfile(ProfileStage::DrawObjects);
//   DrawObjects();
//   FrameTiming::EndProfile(ProfileStage::DrawObjects);
//
//   double ms = FrameTiming::GetProfileTimeMS(ProfileStage::DrawObjects);
//
class FrameTiming
{
public:
	static void Initialize();
	static void BeginFrame();
	static void EndFrame();
	static void CountDisplayedFrame();   // Call only when frame is actually flipped

	// Accessors
	static double GetDeltaTime();        // Seconds since last frame
	static double GetDeltaTimeMS();      // Milliseconds since last frame
	static uint32_t GetFPS();            // Displayed frames per second
	static uint64_t GetFrameCount();     // Total displayed frames

	// Profiling
	static void SetProfilingEnabled(bool enabled);
	static bool IsProfilingEnabled();
	static void BeginProfile(ProfileStage stage);
	static void EndProfile(ProfileStage stage);
	static double GetProfileTimeMS(ProfileStage stage);     // Current frame time
	static double GetProfileAvgTimeMS(ProfileStage stage);  // Averaged over ~1 second
	static const char* GetStageName(ProfileStage stage);

private:
	using Clock = std::chrono::steady_clock;
	using TimePoint = std::chrono::steady_clock::time_point;

	static TimePoint s_frameStart;        // Frame start time
	static TimePoint s_lastFrame;         // Previous frame start

	static double s_deltaTime;            // Current delta in seconds
	static double s_accumulator;          // Time accumulator for FPS calc
	static uint32_t s_displayedThisSecond; // Displayed frames in current second
	static uint32_t s_fps;                // Last calculated FPS (displayed)
	static uint64_t s_totalDisplayed;     // Total displayed frame count

	// Profiling data
	static constexpr int STAGE_COUNT = static_cast<int>(ProfileStage::COUNT);
	static bool s_profilingEnabled;
	static TimePoint s_stageStart[STAGE_COUNT];
	static double s_stageTimeMS[STAGE_COUNT];     // Current frame timing
	static double s_stageAccumMS[STAGE_COUNT];    // Accumulated for averaging
	static double s_stageAvgMS[STAGE_COUNT];      // Averaged timing (updated each second)
	static uint32_t s_profileFrameCount;          // Frames accumulated for averaging
};
