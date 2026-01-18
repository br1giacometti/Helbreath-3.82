#include "ConfigManager.h"
#include "GlobalDef.h"
#include "json.hpp"
#include <fstream>
#include <cstring>
#include <cstdlib>

using json = nlohmann::json;

// 4:3 resolutions for validation (must match DialogBox_SysMenu)
static const struct { int w, h; } s_ValidResolutions[] = {
	{ 640, 480 },
	{ 800, 600 },
	{ 1024, 768 },
	{ 1280, 960 },
	{ 1440, 1080 }
};
static const int s_NumValidResolutions = sizeof(s_ValidResolutions) / sizeof(s_ValidResolutions[0]);

ConfigManager& ConfigManager::Get()
{
	static ConfigManager instance;
	return instance;
}

void ConfigManager::Initialize()
{
	// Only initialize once - don't reset if already initialized
	if (m_bInitialized)
		return;

	SetDefaults();
	m_bInitialized = true;
	m_bDirty = false;
}

void ConfigManager::Shutdown()
{
	// Auto-save if dirty
	if (m_bDirty)
	{
		Save();
	}
	m_bInitialized = false;
}

void ConfigManager::SetDefaults()
{
	// Server defaults from compile-time macros
	std::memset(m_serverAddress, 0, sizeof(m_serverAddress));
	std::strcpy(m_serverAddress, DEF_SERVER_IP);
	m_serverPort = DEF_SERVER_PORT;
	m_gameServerPort = DEF_GSERVER_PORT;

	// Shortcut defaults (none assigned)
	m_magicShortcut = -1;
	m_recentShortcut = -1;
	for (int i = 0; i < MAX_SHORTCUTS; i++)
	{
		m_shortcuts[i] = -1;
	}

	// Audio defaults
	m_soundVolume = 100;
	m_musicVolume = 100;
	m_bSoundEnabled = true;
	m_bMusicEnabled = true;

	// Window defaults
	m_windowWidth = 640;
	m_windowHeight = 480;

	// Display/Detail defaults
	m_bShowFPS = false;
	m_bShowLatency = false;
	m_cDetailLevel = 2;
	m_bZoomMap = true;
	m_bDialogTrans = false;
	m_bRunningMode = false;
#ifdef DEF_WINDOWED_MODE
	m_bFullscreen = false;
#else
	m_bFullscreen = true;
#endif

	m_bDirty = false;
}

int ConfigManager::Clamp(int value, int min, int max)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

bool ConfigManager::Load(const char* filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		// No config file - save defaults and return success
		Save(filename);
		return true;
	}

	try
	{
		json j = json::parse(file);

		// Server settings
		if (j.contains("server"))
		{
			auto& server = j["server"];
			if (server.contains("address"))
			{
				std::string addr = server["address"].get<std::string>();
				std::strncpy(m_serverAddress, addr.c_str(), sizeof(m_serverAddress) - 1);
				m_serverAddress[sizeof(m_serverAddress) - 1] = '\0';
			}
			if (server.contains("port"))
			{
				m_serverPort = server["port"].get<int>();
			}
			if (server.contains("gamePort"))
			{
				m_gameServerPort = server["gamePort"].get<int>();
			}
		}

		// Shortcuts
		if (j.contains("shortcuts"))
		{
			auto& shortcuts = j["shortcuts"];
			if (shortcuts.contains("magic"))
			{
				int slot = shortcuts["magic"].get<int>();
				m_magicShortcut = (slot >= 0 && slot < MAX_MAGIC_SLOT) ? static_cast<short>(slot) : -1;
			}
			if (shortcuts.contains("slots") && shortcuts["slots"].is_array())
			{
				auto& slots = shortcuts["slots"];
				for (size_t i = 0; i < slots.size() && i < MAX_SHORTCUTS; i++)
				{
					int slot = slots[i].get<int>();
					m_shortcuts[i] = (slot >= 0 && slot < MAX_SHORTCUT_SLOT) ? static_cast<short>(slot) : -1;
				}
			}
		}

		// Audio settings
		if (j.contains("audio"))
		{
			auto& audio = j["audio"];
			if (audio.contains("soundVolume"))
			{
				m_soundVolume = Clamp(audio["soundVolume"].get<int>(), 0, 100);
			}
			if (audio.contains("musicVolume"))
			{
				m_musicVolume = Clamp(audio["musicVolume"].get<int>(), 0, 100);
			}
			if (audio.contains("soundEnabled"))
			{
				m_bSoundEnabled = audio["soundEnabled"].get<bool>();
			}
			if (audio.contains("musicEnabled"))
			{
				m_bMusicEnabled = audio["musicEnabled"].get<bool>();
			}
		}

		// Window settings
		if (j.contains("window"))
		{
			auto& window = j["window"];
			if (window.contains("width"))
			{
				m_windowWidth = Clamp(window["width"].get<int>(), 640, 3840);
			}
			if (window.contains("height"))
			{
				m_windowHeight = Clamp(window["height"].get<int>(), 480, 2160);
			}
		}

		// Display/Detail settings
		if (j.contains("display"))
		{
			auto& display = j["display"];
			if (display.contains("showFps"))
			{
				m_bShowFPS = display["showFps"].get<bool>();
			}
			if (display.contains("showLatency"))
			{
				m_bShowLatency = display["showLatency"].get<bool>();
			}
			if (display.contains("detailLevel"))
			{
				m_cDetailLevel = Clamp(display["detailLevel"].get<int>(), 0, 2);
			}
			if (display.contains("zoomMap"))
			{
				m_bZoomMap = display["zoomMap"].get<bool>();
			}
			if (display.contains("dialogTransparency"))
			{
				m_bDialogTrans = display["dialogTransparency"].get<bool>();
			}
			if (display.contains("runningMode"))
			{
				m_bRunningMode = display["runningMode"].get<bool>();
			}
			if (display.contains("fullscreen"))
			{
				m_bFullscreen = display["fullscreen"].get<bool>();
			}
		}

		// Validate resolution to nearest 4:3 option
		bool bValidResolution = false;
		for (int i = 0; i < s_NumValidResolutions; i++) {
			if (m_windowWidth == s_ValidResolutions[i].w && m_windowHeight == s_ValidResolutions[i].h) {
				bValidResolution = true;
				break;
			}
		}
		if (!bValidResolution) {
			// Find nearest 4:3 resolution
			int bestIndex = 0;
			int bestDiff = abs(s_ValidResolutions[0].w - m_windowWidth) + abs(s_ValidResolutions[0].h - m_windowHeight);
			for (int i = 1; i < s_NumValidResolutions; i++) {
				int diff = abs(s_ValidResolutions[i].w - m_windowWidth) + abs(s_ValidResolutions[i].h - m_windowHeight);
				if (diff < bestDiff) {
					bestDiff = diff;
					bestIndex = i;
				}
			}
			m_windowWidth = s_ValidResolutions[bestIndex].w;
			m_windowHeight = s_ValidResolutions[bestIndex].h;
			m_bDirty = true; // Mark dirty so corrected value is saved
		}
	}
	catch (const json::exception&)
	{
		// Parse error - keep defaults
		return false;
	}

	m_bDirty = false;
	return true;
}

bool ConfigManager::Save(const char* filename)
{
	json j;

	// Server settings
	j["server"]["address"] = m_serverAddress;
	j["server"]["port"] = m_serverPort;
	j["server"]["gamePort"] = m_gameServerPort;

	// Shortcuts
	j["shortcuts"]["magic"] = m_magicShortcut;
	j["shortcuts"]["slots"] = json::array();
	for (int i = 0; i < MAX_SHORTCUTS; i++)
	{
		j["shortcuts"]["slots"].push_back(m_shortcuts[i]);
	}

	// Audio settings
	j["audio"]["soundVolume"] = m_soundVolume;
	j["audio"]["musicVolume"] = m_musicVolume;
	j["audio"]["soundEnabled"] = m_bSoundEnabled;
	j["audio"]["musicEnabled"] = m_bMusicEnabled;

	// Window settings
	j["window"]["width"] = m_windowWidth;
	j["window"]["height"] = m_windowHeight;

	// Display/Detail settings
	j["display"]["showFps"] = m_bShowFPS;
	j["display"]["showLatency"] = m_bShowLatency;
	j["display"]["detailLevel"] = m_cDetailLevel;
	j["display"]["zoomMap"] = m_bZoomMap;
	j["display"]["dialogTransparency"] = m_bDialogTrans;
	j["display"]["runningMode"] = m_bRunningMode;
	j["display"]["fullscreen"] = m_bFullscreen;

	std::ofstream file(filename);
	if (!file.is_open())
	{
		return false;
	}

	file << j.dump(4); // Pretty print with 4-space indent
	m_bDirty = false;
	return true;
}

void ConfigManager::SetMagicShortcut(short slot)
{
	if (slot >= -1 && slot < MAX_MAGIC_SLOT)
	{
		if (m_magicShortcut != slot)
		{
			m_magicShortcut = slot;
			m_bDirty = true;
		}
	}
}

short ConfigManager::GetShortcut(int index) const
{
	if (index >= 0 && index < MAX_SHORTCUTS)
	{
		return m_shortcuts[index];
	}
	return -1;
}

void ConfigManager::SetShortcut(int index, short slot)
{
	if (index >= 0 && index < MAX_SHORTCUTS)
	{
		if (slot >= -1 && slot < MAX_SHORTCUT_SLOT)
		{
			if (m_shortcuts[index] != slot)
			{
				m_shortcuts[index] = slot;
				m_bDirty = true;
			}
		}
	}
}

void ConfigManager::SetSoundVolume(int volume)
{
	volume = Clamp(volume, 0, 100);
	if (m_soundVolume != volume)
	{
		m_soundVolume = volume;
		m_bDirty = true;
	}
}

void ConfigManager::SetMusicVolume(int volume)
{
	volume = Clamp(volume, 0, 100);
	if (m_musicVolume != volume)
	{
		m_musicVolume = volume;
		m_bDirty = true;
	}
}

void ConfigManager::SetSoundEnabled(bool enabled)
{
	if (m_bSoundEnabled != enabled)
	{
		m_bSoundEnabled = enabled;
		m_bDirty = true;
	}
}

void ConfigManager::SetMusicEnabled(bool enabled)
{
	if (m_bMusicEnabled != enabled)
	{
		m_bMusicEnabled = enabled;
		m_bDirty = true;
	}
}

void ConfigManager::SetWindowSize(int width, int height)
{
	// Validate to nearest 4:3 resolution
	bool bValid = false;
	for (int i = 0; i < s_NumValidResolutions; i++) {
		if (width == s_ValidResolutions[i].w && height == s_ValidResolutions[i].h) {
			bValid = true;
			break;
		}
	}
	if (!bValid) {
		// Snap to nearest valid resolution
		int bestIndex = 0;
		int bestDiff = abs(s_ValidResolutions[0].w - width) + abs(s_ValidResolutions[0].h - height);
		for (int i = 1; i < s_NumValidResolutions; i++) {
			int diff = abs(s_ValidResolutions[i].w - width) + abs(s_ValidResolutions[i].h - height);
			if (diff < bestDiff) {
				bestDiff = diff;
				bestIndex = i;
			}
		}
		width = s_ValidResolutions[bestIndex].w;
		height = s_ValidResolutions[bestIndex].h;
	}

	if (m_windowWidth != width || m_windowHeight != height)
	{
		m_windowWidth = width;
		m_windowHeight = height;
		m_bDirty = true;
	}
}

void ConfigManager::SetShowFpsEnabled(bool enabled)
{
	if (m_bShowFPS != enabled)
	{
		m_bShowFPS = enabled;
		m_bDirty = true;
	}
}

void ConfigManager::SetShowLatencyEnabled(bool enabled)
{
	if (m_bShowLatency != enabled)
	{
		m_bShowLatency = enabled;
		m_bDirty = true;
	}
}

void ConfigManager::SetDetailLevel(int level)
{
	level = Clamp(level, 0, 2);
	if (m_cDetailLevel != level)
	{
		m_cDetailLevel = level;
		m_bDirty = true;
	}
}

void ConfigManager::SetZoomMapEnabled(bool enabled)
{
	if (m_bZoomMap != enabled)
	{
		m_bZoomMap = enabled;
		m_bDirty = true;
	}
}

void ConfigManager::SetDialogTransparencyEnabled(bool enabled)
{
	if (m_bDialogTrans != enabled)
	{
		m_bDialogTrans = enabled;
		m_bDirty = true;
	}
}

void ConfigManager::SetRunningModeEnabled(bool enabled)
{
	if (m_bRunningMode != enabled)
	{
		m_bRunningMode = enabled;
		m_bDirty = true;
	}
}

void ConfigManager::SetFullscreenEnabled(bool enabled)
{
	if (m_bFullscreen != enabled)
	{
		m_bFullscreen = enabled;
		m_bDirty = true;
	}
}
