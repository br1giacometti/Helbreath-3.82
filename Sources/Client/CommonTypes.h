// CommonTypes.h: Cross-platform type definitions
//
// This header replaces Windows-specific typedefs (DWORD, WORD, BYTE) with
// standard C++ types (uint32_t, uint16_t, uint8_t) for cross-platform compatibility.
//
// Windows API types (HWND, HANDLE, HRESULT) are preserved for platform-specific code.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <cstring>
#include <chrono>

// ============================================================================
// Standard C++ Type Replacements
// ============================================================================
//
// The following Windows typedefs have been replaced throughout the codebase:
//   DWORD → uint32_t (32-bit unsigned integer)
//   WORD  → uint16_t (16-bit unsigned integer)
//   BYTE  → uint8_t  (8-bit unsigned integer)
//
// Hungarian notation is preserved (e.g., dwTime remains dwTime, but type is uint32_t)
//
// ============================================================================

// Windows API types (platform-specific)
// These are used with DirectX and Windows system calls and must remain Windows-specific
#ifdef _WIN32
    #include <windows.h>
    // HWND, HANDLE, HRESULT, HINSTANCE, RECT are provided by windows.h
#endif

// ============================================================================
// Memory Operations
// ============================================================================

// Windows ZeroMemory() should be replaced with std::memset() throughout the codebase
// Old: ZeroMemory(&struct, sizeof(struct));
// New: std::memset(&struct, 0, sizeof(struct));

// ============================================================================
// Timing System
// ============================================================================

// GameClock: Cross-platform timing system
// Replaces Windows timeGetTime() with std::chrono for cross-platform compatibility
//
// Usage:
//   GameClock::Initialize();  // Call once at startup
//   uint32_t time = GameClock::GetTimeMS();  // Get current time in milliseconds
//
// Note: Time wraps around after ~49.7 days (2^32 milliseconds), same as timeGetTime().
//       Use delta time calculations for robust timing that handles wraparound.
//
class GameClock {
private:
    static std::chrono::steady_clock::time_point s_startTime;
    static bool s_initialized;

public:
    // Initialize the game clock - call once at application startup
    static void Initialize() {
        if (!s_initialized) {
            s_startTime = std::chrono::steady_clock::now();
            s_initialized = true;
        }
    }

    // Get milliseconds since initialization
    // Returns: uint32_t milliseconds (0 to 4,294,967,295, wraps after ~49.7 days)
    //
    // This replaces Windows timeGetTime() with equivalent behavior:
    //   Old: DWORD dwTime = timeGetTime();
    //   New: uint32_t dwTime = GameClock::GetTimeMS();
    //
    static uint32_t GetTimeMS() {
        if (!s_initialized) Initialize();

        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - s_startTime);
        return static_cast<uint32_t>(elapsed.count());
    }
};
