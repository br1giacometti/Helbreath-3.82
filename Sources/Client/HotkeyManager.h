#pragma once

#include <functional>
#include <vector>

class HotkeyManager
{
public:
	static HotkeyManager& Get();

	enum class Trigger
	{
		KeyDown,
		KeyUp
	};

	struct KeyCombo
	{
		int vk;
		bool ctrl;
		bool shift;
		bool alt;
	};

	void Clear();
	void Register(const KeyCombo& combo, Trigger trigger, std::function<void()> callback);
	bool HandleKeyDown(int vk);
	bool HandleKeyUp(int vk);

private:
	HotkeyManager() = default;
	~HotkeyManager() = default;
	HotkeyManager(const HotkeyManager&) = delete;
	HotkeyManager& operator=(const HotkeyManager&) = delete;

	struct Entry
	{
		KeyCombo combo;
		Trigger trigger;
		std::function<void()> callback;
	};

	bool HandleKey(int vk, Trigger trigger);

	std::vector<Entry> m_entries;
};
