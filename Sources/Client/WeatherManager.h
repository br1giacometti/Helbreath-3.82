#pragma once

#include <cstdint>

enum class WeatherType
{
	Clear = 0,
	Rain,
	Snow,
	Storm
};

class WeatherManager
{
public:
	static WeatherManager& Get();

	// Lifecycle
	void Initialize();
	void Shutdown();

	// Weather state
	WeatherType GetCurrentWeather() const { return m_currentWeather; }
	void SetWeatherImmediate(WeatherType type);

	// Legacy compatibility (maps old char-based weather to new enum)
	static WeatherType FromLegacyWeather(char weatherStatus);
	static char ToLegacyWeather(WeatherType type);

private:
	WeatherManager() = default;
	~WeatherManager() = default;
	WeatherManager(const WeatherManager&) = delete;
	WeatherManager& operator=(const WeatherManager&) = delete;

	WeatherType m_currentWeather = WeatherType::Clear;
};
