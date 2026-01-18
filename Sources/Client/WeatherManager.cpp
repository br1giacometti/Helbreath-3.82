#include "WeatherManager.h"

WeatherManager& WeatherManager::Get()
{
	static WeatherManager instance;
	return instance;
}

void WeatherManager::Initialize()
{
	m_currentWeather = WeatherType::Clear;
}

void WeatherManager::Shutdown()
{
}

void WeatherManager::SetWeatherImmediate(WeatherType type)
{
	m_currentWeather = type;
}

WeatherType WeatherManager::FromLegacyWeather(char weatherStatus)
{
	// Map old m_cWhetherStatus values to new enum
	// Server values: 0=Clear, 1-3=Rain, 4-6=Snow, 7-9=Storm
	if (weatherStatus == 0)
		return WeatherType::Clear;
	else if (weatherStatus >= 1 && weatherStatus <= 3)
		return WeatherType::Rain;
	else if (weatherStatus >= 4 && weatherStatus <= 6)
		return WeatherType::Snow;
	else if (weatherStatus >= 7 && weatherStatus <= 9)
		return WeatherType::Storm;
	else
		return WeatherType::Clear;
}

char WeatherManager::ToLegacyWeather(WeatherType type)
{
	// Map to middle intensity values
	switch (type)
	{
		case WeatherType::Clear: return 0;
		case WeatherType::Rain: return 2;   // Middle of 1-3
		case WeatherType::Snow: return 5;   // Middle of 4-6
		case WeatherType::Storm: return 8;  // Middle of 7-9
		default: return 0;
	}
}
