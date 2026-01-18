#pragma once

#include <cstdint>

// Maximum shortcuts matching game limits
static const int MAX_SHORTCUTS = 5;
static const int MAX_MAGIC_SLOT = 100;
static const int MAX_SHORTCUT_SLOT = 200;

class ConfigManager
{
public:
	static ConfigManager& Get();

	// Lifecycle
	void Initialize();
	void Shutdown();

	// File operations - replaces registry-based ReadSettings/WriteSettings
	bool Load(const char* filename = "settings.json");
	bool Save(const char* filename = "settings.json");

	// Server address - uses DEF_SERVER_IP/PORT macros as defaults
	const char* GetServerAddress() const { return m_serverAddress; }
	int GetServerPort() const { return m_serverPort; }
	int GetGameServerPort() const { return m_gameServerPort; }

	// Shortcuts - replaces registry storage
	// Magic shortcut: -1 = none, 0-99 = valid slot
	short GetMagicShortcut() const { return m_magicShortcut; }
	void SetMagicShortcut(short slot);

	// Item/Skill shortcuts: -1 = none, 0-199 = valid slot
	short GetShortcut(int index) const;
	void SetShortcut(int index, short slot);

	// Recent shortcut (runtime only, not persisted)
	short GetRecentShortcut() const { return m_recentShortcut; }
	void SetRecentShortcut(short slot) { m_recentShortcut = slot; }

	// Audio settings - adds persistence to existing runtime values
	int GetSoundVolume() const { return m_soundVolume; }
	int GetMusicVolume() const { return m_musicVolume; }
	bool IsSoundEnabled() const { return m_bSoundEnabled; }
	bool IsMusicEnabled() const { return m_bMusicEnabled; }

	void SetSoundVolume(int volume);
	void SetMusicVolume(int volume);
	void SetSoundEnabled(bool enabled);
	void SetMusicEnabled(bool enabled);

	// Window/Resolution settings
	int GetWindowWidth() const { return m_windowWidth; }
	int GetWindowHeight() const { return m_windowHeight; }
	void SetWindowSize(int width, int height);

	// Display/Detail settings
	bool IsShowFpsEnabled() const { return m_bShowFPS; }
	bool IsShowLatencyEnabled() const { return m_bShowLatency; }
	int GetDetailLevel() const { return m_cDetailLevel; }
	bool IsZoomMapEnabled() const { return m_bZoomMap; }
	bool IsDialogTransparencyEnabled() const { return m_bDialogTrans; }
	bool IsRunningModeEnabled() const { return m_bRunningMode; }
	bool IsFullscreenEnabled() const { return m_bFullscreen; }

	void SetShowFpsEnabled(bool enabled);
	void SetShowLatencyEnabled(bool enabled);
	void SetDetailLevel(int level);
	void SetZoomMapEnabled(bool enabled);
	void SetDialogTransparencyEnabled(bool enabled);
	void SetRunningModeEnabled(bool enabled);
	void SetFullscreenEnabled(bool enabled);

	// Dirty flag - indicates unsaved changes
	bool IsDirty() const { return m_bDirty; }
	void MarkClean() { m_bDirty = false; }

private:
	ConfigManager() = default;
	~ConfigManager() = default;
	ConfigManager(const ConfigManager&) = delete;
	ConfigManager& operator=(const ConfigManager&) = delete;

	void SetDefaults();
	int Clamp(int value, int min, int max);

	// Server connection (defaults from DEF_SERVER_IP, DEF_SERVER_PORT, DEF_GSERVER_PORT)
	char m_serverAddress[64];
	int m_serverPort;
	int m_gameServerPort;

	// Shortcuts (matches m_sMagicShortCut, m_sShortCut[5], m_sRecentShortCut)
	short m_magicShortcut;
	short m_shortcuts[MAX_SHORTCUTS];
	short m_recentShortcut;

	// Audio (matches m_cSoundVolume, m_cMusicVolume, m_bSoundStat, m_bMusicStat)
	int m_soundVolume;
	int m_musicVolume;
	bool m_bSoundEnabled;
	bool m_bMusicEnabled;

	// Window/Resolution
	int m_windowWidth;
	int m_windowHeight;

	// Display/Detail
	bool m_bShowFPS;
	bool m_bShowLatency;
	int m_cDetailLevel;
	bool m_bZoomMap;
	bool m_bDialogTrans;
	bool m_bRunningMode;
	bool m_bFullscreen;

	// State
	bool m_bDirty;
	bool m_bInitialized;
};
