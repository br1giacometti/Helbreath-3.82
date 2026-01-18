#include "CmdWeather.h"
#include "Game.h"
#include "WeatherManager.h"
#include <cstdlib>
#include <cstdio>

bool CmdWeather::Execute(CGame* pGame, const char* pArgs)
{
	if (pArgs == nullptr || pArgs[0] == '\0')
	{
		pGame->AddEventList("Usage: /weather <0-9> (0=Clear, 1-3=Rain, 4-6=Snow, 7-9=Storm)", 10);
		return true;
	}

	int legacyWeather = std::atoi(pArgs);

	if (legacyWeather < 0 || legacyWeather > 9)
	{
		pGame->AddEventList("Invalid weather type. Use 0-9.", 10);
		return true;
	}

	// Update the legacy weather status (used by the renderer)
	pGame->m_cWhetherStatus = static_cast<char>(legacyWeather);

	// Call the legacy SetWhetherStatus to start/stop weather effects
	if (legacyWeather != 0)
		pGame->SetWhetherStatus(true, static_cast<char>(legacyWeather));
	else
		pGame->SetWhetherStatus(false, 0);

	// Also update WeatherManager for any new systems using it
	WeatherType type = WeatherManager::FromLegacyWeather(static_cast<char>(legacyWeather));
	WeatherManager::Get().SetWeatherImmediate(type);

	const char* weatherNames[] = { "Clear", "Rain", "Rain", "Rain", "Snow", "Snow", "Snow", "Storm", "Storm", "Storm" };
	char msg[64];
	std::sprintf(msg, "Weather changed to: %s (value: %d)", weatherNames[legacyWeather], legacyWeather);
	pGame->AddEventList(msg, 10);

	return true;
}
