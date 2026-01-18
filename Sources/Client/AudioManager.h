#pragma once

#include <windows.h>
#include "miniaudio.h"
#include <string>
#include <cstdint>
#include <vector>
#include <array>

// Maximum sound effects per category
static const int AUDIO_MAX_CHARACTER_SOUNDS = 25;   // C1-C24
static const int AUDIO_MAX_MONSTER_SOUNDS = 160;    // M1-M156
static const int AUDIO_MAX_EFFECT_SOUNDS = 55;      // E1-E53

// Maximum concurrent playing sounds (active sound pool)
static const int AUDIO_MAX_ACTIVE_SOUNDS = 32;

// Sound types matching existing categories
enum class SoundType
{
	Character,  // Combat sounds (C1-C24)
	Monster,    // Magic/Monster sounds (M1-M156)
	Effect      // Environmental/Effect sounds (E1-E53)
};

class AudioManager
{
public:
	static AudioManager& Get();

	// Lifecycle
	bool Initialize(HWND hWnd);
	void Shutdown();

	// Sound loading - pre-loads all sounds into memory
	void LoadSounds();
	void UnloadSounds();
	void CleanupFinishedSounds();

	// Sound effect playback
	void PlaySound(SoundType type, int index, int distance = 0, int pan = 0);
	void PlaySoundLoop(SoundType type, int index);
	void StopSound(SoundType type, int index);
	void StopAllSounds();

	// Background music
	void PlayMusic(const char* trackName);
	void StopMusic();
	bool IsMusicPlaying() const;
	const std::string& GetCurrentMusicTrack() const { return m_currentMusicTrack; }

	// Volume control (0-100 scale)
	void SetSoundVolume(int volume);
	void SetMusicVolume(int volume);
	int GetSoundVolume() const { return m_soundVolume; }
	int GetMusicVolume() const { return m_musicVolume; }

	// Enable/disable
	void SetSoundEnabled(bool enabled);
	void SetMusicEnabled(bool enabled);
	bool IsSoundEnabled() const { return m_bSoundEnabled; }
	bool IsMusicEnabled() const { return m_bMusicEnabled; }

	// Hardware availability
	bool IsSoundAvailable() const { return m_bSoundAvailable; }

	// Listener position (for positional audio)
	void SetListenerPosition(int worldX, int worldY);
	int GetListenerX() const { return m_listenerX; }
	int GetListenerY() const { return m_listenerY; }

	// Per-frame update
	void Update(uint32_t currentTime);

private:
	AudioManager() = default;
	~AudioManager() = default;
	AudioManager(const AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;

	// Helper to build sound file path
	std::string GetSoundPath(SoundType type, int index) const;

	// Convert 0-100 volume to 0.0-1.0
	float VolumeToFloat(int volume) const;

	// Get pre-loaded sound for a type/index
	ma_sound* GetPreloadedSound(SoundType type, int index);

	// miniaudio engine
	ma_engine m_engine;
	bool m_bSoundAvailable = false;
	bool m_bInitialized = false;

	// Sound effect group (for separate volume control)
	ma_sound_group m_sfxGroup;
	bool m_bSfxGroupInitialized = false;

	// Pre-loaded sound templates (decoded into memory)
	std::array<ma_sound, AUDIO_MAX_CHARACTER_SOUNDS> m_characterSounds;
	std::array<bool, AUDIO_MAX_CHARACTER_SOUNDS> m_characterSoundsLoaded = {};

	std::array<ma_sound, AUDIO_MAX_MONSTER_SOUNDS> m_monsterSounds;
	std::array<bool, AUDIO_MAX_MONSTER_SOUNDS> m_monsterSoundsLoaded = {};

	std::array<ma_sound, AUDIO_MAX_EFFECT_SOUNDS> m_effectSounds;
	std::array<bool, AUDIO_MAX_EFFECT_SOUNDS> m_effectSoundsLoaded = {};

	// Active sound pool for concurrent playback
	struct ActiveSound {
		ma_sound sound;
		bool inUse = false;
	};
	std::array<ActiveSound, AUDIO_MAX_ACTIVE_SOUNDS> m_activeSounds;

	// Background music sound
	ma_sound m_bgmSound;
	bool m_bBgmLoaded = false;

	// Current music track name
	std::string m_currentMusicTrack;

	// Volume (0-100)
	int m_soundVolume = 100;
	int m_musicVolume = 100;

	// Enable flags
	bool m_bSoundEnabled = true;
	bool m_bMusicEnabled = true;

	// Listener position (for positional audio)
	int m_listenerX = 0;
	int m_listenerY = 0;
};
