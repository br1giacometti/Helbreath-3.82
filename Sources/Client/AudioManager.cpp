#include "AudioManager.h"
#include <cstdio>

AudioManager& AudioManager::Get()
{
	static AudioManager instance;
	return instance;
}

bool AudioManager::Initialize(HWND hWnd)
{
	(void)hWnd; // Not needed for miniaudio

	if (m_bInitialized)
		return m_bSoundAvailable;

	// Initialize miniaudio engine
	ma_engine_config engineConfig = ma_engine_config_init();

	ma_result result = ma_engine_init(&engineConfig, &m_engine);
	if (result != MA_SUCCESS)
	{
		m_bSoundAvailable = false;
		m_bInitialized = true;
		return false;
	}

	// Initialize sound effect group for separate volume control
	result = ma_sound_group_init(&m_engine, 0, NULL, &m_sfxGroup);
	if (result == MA_SUCCESS)
	{
		m_bSfxGroupInitialized = true;
		// Apply any volume that was set before initialization
		ma_sound_group_set_volume(&m_sfxGroup, VolumeToFloat(m_soundVolume));
	}

	m_bSoundAvailable = true;
	m_bInitialized = true;
	return true;
}

void AudioManager::LoadSounds()
{
	if (!m_bSoundAvailable)
		return;

	char filename[64];
	ma_uint32 flags = MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_NO_SPATIALIZATION;

	// Load Character sounds (C1-C24)
	for (int i = 1; i < AUDIO_MAX_CHARACTER_SOUNDS; i++)
	{
		std::sprintf(filename, "sounds\\C%d.wav", i);
		ma_result result = ma_sound_init_from_file(&m_engine, filename, flags, &m_sfxGroup, NULL, &m_characterSounds[i]);
		m_characterSoundsLoaded[i] = (result == MA_SUCCESS);
	}

	// Load Monster/Magic sounds (M1-M156)
	for (int i = 1; i < AUDIO_MAX_MONSTER_SOUNDS; i++)
	{
		std::sprintf(filename, "sounds\\M%d.wav", i);
		ma_result result = ma_sound_init_from_file(&m_engine, filename, flags, &m_sfxGroup, NULL, &m_monsterSounds[i]);
		m_monsterSoundsLoaded[i] = (result == MA_SUCCESS);
	}

	// Load Effect sounds (E1-E53)
	for (int i = 1; i < AUDIO_MAX_EFFECT_SOUNDS; i++)
	{
		std::sprintf(filename, "sounds\\E%d.wav", i);
		ma_result result = ma_sound_init_from_file(&m_engine, filename, flags, &m_sfxGroup, NULL, &m_effectSounds[i]);
		m_effectSoundsLoaded[i] = (result == MA_SUCCESS);
	}
}

void AudioManager::Shutdown()
{
	if (!m_bInitialized)
		return;

	// Stop and unload music
	StopMusic();

	// Unload all sounds
	UnloadSounds();

	// Uninitialize sound group
	if (m_bSfxGroupInitialized)
	{
		ma_sound_group_uninit(&m_sfxGroup);
		m_bSfxGroupInitialized = false;
	}

	// Uninitialize engine
	if (m_bSoundAvailable)
	{
		ma_engine_uninit(&m_engine);
	}

	m_bInitialized = false;
	m_bSoundAvailable = false;
}

void AudioManager::UnloadSounds()
{
	// Stop and uninit active sounds
	for (auto& active : m_activeSounds)
	{
		if (active.inUse)
		{
			ma_sound_uninit(&active.sound);
			active.inUse = false;
		}
	}

	// Uninit pre-loaded Character sounds
	for (int i = 0; i < AUDIO_MAX_CHARACTER_SOUNDS; i++)
	{
		if (m_characterSoundsLoaded[i])
		{
			ma_sound_uninit(&m_characterSounds[i]);
			m_characterSoundsLoaded[i] = false;
		}
	}

	// Uninit pre-loaded Monster sounds
	for (int i = 0; i < AUDIO_MAX_MONSTER_SOUNDS; i++)
	{
		if (m_monsterSoundsLoaded[i])
		{
			ma_sound_uninit(&m_monsterSounds[i]);
			m_monsterSoundsLoaded[i] = false;
		}
	}

	// Uninit pre-loaded Effect sounds
	for (int i = 0; i < AUDIO_MAX_EFFECT_SOUNDS; i++)
	{
		if (m_effectSoundsLoaded[i])
		{
			ma_sound_uninit(&m_effectSounds[i]);
			m_effectSoundsLoaded[i] = false;
		}
	}

	// Stop music
	StopMusic();
}

void AudioManager::CleanupFinishedSounds()
{
	for (auto& active : m_activeSounds)
	{
		if (active.inUse && !ma_sound_is_playing(&active.sound))
		{
			ma_sound_uninit(&active.sound);
			active.inUse = false;
		}
	}
}

std::string AudioManager::GetSoundPath(SoundType type, int index) const
{
	char filename[64];
	switch (type)
	{
	case SoundType::Character:
		std::sprintf(filename, "sounds\\C%d.wav", index);
		break;
	case SoundType::Monster:
		std::sprintf(filename, "sounds\\M%d.wav", index);
		break;
	case SoundType::Effect:
		std::sprintf(filename, "sounds\\E%d.wav", index);
		break;
	default:
		return "";
	}
	return filename;
}

float AudioManager::VolumeToFloat(int volume) const
{
	// Convert 0-100 to 0.0-1.0
	if (volume <= 0) return 0.0f;
	if (volume >= 100) return 1.0f;
	return volume / 100.0f;
}

ma_sound* AudioManager::GetPreloadedSound(SoundType type, int index)
{
	switch (type)
	{
	case SoundType::Character:
		if (index >= 0 && index < AUDIO_MAX_CHARACTER_SOUNDS && m_characterSoundsLoaded[index])
			return &m_characterSounds[index];
		break;
	case SoundType::Monster:
		if (index >= 0 && index < AUDIO_MAX_MONSTER_SOUNDS && m_monsterSoundsLoaded[index])
			return &m_monsterSounds[index];
		break;
	case SoundType::Effect:
		if (index >= 0 && index < AUDIO_MAX_EFFECT_SOUNDS && m_effectSoundsLoaded[index])
			return &m_effectSounds[index];
		break;
	}
	return nullptr;
}

void AudioManager::PlaySound(SoundType type, int index, int distance, int pan)
{
	if (!m_bSoundAvailable || !m_bSoundEnabled)
		return;

	// Clean up finished sounds first
	CleanupFinishedSounds();

	// Get the pre-loaded sound template
	ma_sound* pTemplate = GetPreloadedSound(type, index);
	if (pTemplate == nullptr)
		return;

	// Calculate volume based on distance
	float volume = 1.0f;  // Base volume (group volume handles overall level)

	// Distance attenuation (reduce by 10% per distance unit, max 10 units)
	if (distance > 0)
	{
		if (distance > 10) distance = 10;
		volume *= (1.0f - (distance * 0.1f));
	}

	// Don't play if too quiet
	if (volume < 0.01f)
		return;

	// Find a free slot in the active sound pool
	ActiveSound* pSlot = nullptr;
	for (auto& active : m_activeSounds)
	{
		if (!active.inUse)
		{
			pSlot = &active;
			break;
		}
	}

	// No free slot - try to reclaim a finished one
	if (pSlot == nullptr)
	{
		for (auto& active : m_activeSounds)
		{
			if (!ma_sound_is_playing(&active.sound))
			{
				ma_sound_uninit(&active.sound);
				active.inUse = false;
				pSlot = &active;
				break;
			}
		}
	}

	// Still no slot available - skip this sound
	if (pSlot == nullptr)
		return;

	// Create a copy of the pre-loaded sound for playback
	ma_result result = ma_sound_init_copy(&m_engine, pTemplate, 0, &m_sfxGroup, &pSlot->sound);
	if (result != MA_SUCCESS)
		return;

	pSlot->inUse = true;

	// Set volume for this instance
	ma_sound_set_volume(&pSlot->sound, volume);

	// Apply panning (-100 to 100 maps to -1.0 to 1.0)
	if (pan != 0)
	{
		float panValue = pan / 100.0f;
		if (panValue < -1.0f) panValue = -1.0f;
		if (panValue > 1.0f) panValue = 1.0f;
		ma_sound_set_pan(&pSlot->sound, panValue);
	}

	// Start playback
	ma_sound_start(&pSlot->sound);
}

void AudioManager::PlaySoundLoop(SoundType type, int index)
{
	if (!m_bSoundAvailable || !m_bSoundEnabled)
		return;

	// Get the pre-loaded sound template
	ma_sound* pTemplate = GetPreloadedSound(type, index);
	if (pTemplate == nullptr)
		return;

	// Clean up finished sounds first
	CleanupFinishedSounds();

	// Find a free slot
	ActiveSound* pSlot = nullptr;
	for (auto& active : m_activeSounds)
	{
		if (!active.inUse)
		{
			pSlot = &active;
			break;
		}
	}

	if (pSlot == nullptr)
		return;

	// Create a copy for looping playback
	ma_result result = ma_sound_init_copy(&m_engine, pTemplate, 0, &m_sfxGroup, &pSlot->sound);
	if (result != MA_SUCCESS)
		return;

	pSlot->inUse = true;
	ma_sound_set_looping(&pSlot->sound, MA_TRUE);
	ma_sound_start(&pSlot->sound);
}

void AudioManager::StopSound(SoundType type, int index)
{
	// With the copy-based system, we can't easily identify which active sound
	// corresponds to a specific type/index. This would require additional tracking.
	(void)type;
	(void)index;
}

void AudioManager::StopAllSounds()
{
	// Stop and uninit all active sounds
	for (auto& active : m_activeSounds)
	{
		if (active.inUse)
		{
			ma_sound_stop(&active.sound);
			ma_sound_uninit(&active.sound);
			active.inUse = false;
		}
	}
}

void AudioManager::PlayMusic(const char* trackName)
{
	if (!m_bSoundAvailable)
		return;

	if (trackName == nullptr || trackName[0] == '\0')
		return;

	// Check if already playing this track
	if (m_bBgmLoaded && m_currentMusicTrack == trackName)
		return;

	// Stop existing music
	StopMusic();

	// Don't play if music is disabled
	if (!m_bMusicEnabled)
		return;

	// Build full path
	std::string filename = std::string("music\\") + trackName + ".wav";

	// Initialize the music sound - stream from disk (music files are large)
	ma_uint32 flags = MA_SOUND_FLAG_STREAM;
	ma_result result = ma_sound_init_from_file(&m_engine, filename.c_str(), flags, NULL, NULL, &m_bgmSound);

	if (result != MA_SUCCESS)
	{
		m_bBgmLoaded = false;
		return;
	}

	m_bBgmLoaded = true;
	m_currentMusicTrack = trackName;

	// Set volume and looping
	ma_sound_set_volume(&m_bgmSound, VolumeToFloat(m_musicVolume));
	ma_sound_set_looping(&m_bgmSound, MA_TRUE);

	// Start playback
	ma_sound_start(&m_bgmSound);
}

void AudioManager::StopMusic()
{
	if (m_bBgmLoaded)
	{
		ma_sound_stop(&m_bgmSound);
		ma_sound_uninit(&m_bgmSound);
		m_bBgmLoaded = false;
	}
	m_currentMusicTrack.clear();
}

bool AudioManager::IsMusicPlaying() const
{
	if (!m_bBgmLoaded)
		return false;

	return ma_sound_is_playing(&m_bgmSound) == MA_TRUE;
}

void AudioManager::SetSoundVolume(int volume)
{
	if (volume < 0) volume = 0;
	if (volume > 100) volume = 100;
	m_soundVolume = volume;

	// Set sound group volume (affects all sounds in the group)
	if (m_bSfxGroupInitialized)
	{
		ma_sound_group_set_volume(&m_sfxGroup, VolumeToFloat(volume));
	}
}

void AudioManager::SetMusicVolume(int volume)
{
	if (volume < 0) volume = 0;
	if (volume > 100) volume = 100;
	m_musicVolume = volume;

	// Update currently playing music volume
	if (m_bBgmLoaded)
	{
		ma_sound_set_volume(&m_bgmSound, VolumeToFloat(volume));
	}
}

void AudioManager::SetSoundEnabled(bool enabled)
{
	m_bSoundEnabled = enabled;

	// Stop all sounds if disabling
	if (!enabled)
	{
		StopAllSounds();
	}
}

void AudioManager::SetMusicEnabled(bool enabled)
{
	bool wasEnabled = m_bMusicEnabled;
	m_bMusicEnabled = enabled;

	// Stop music if disabling
	if (wasEnabled && !enabled)
	{
		StopMusic();
	}
}

void AudioManager::SetListenerPosition(int worldX, int worldY)
{
	m_listenerX = worldX;
	m_listenerY = worldY;
}

void AudioManager::Update(uint32_t currentTime)
{
	(void)currentTime;
	// Periodically clean up finished sounds
	CleanupFinishedSounds();
}
