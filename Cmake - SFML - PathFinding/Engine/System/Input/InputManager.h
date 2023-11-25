#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <map>
#include <functional>

enum class InputAction
{
	Left,
	Right,
	Up,
	Down,
	Fire,
};

enum class InputAxis
{
	Vertical,
	Horizontal
};

class InputManager
{
public:
	using Callback = std::function<void()>;

	InputManager();

	void Update();

	void Bind(InputAction IA, const Callback& callback);

#pragma region Singleton

	static InputManager *Instance()
	{
		if (!instance)
		{
			instance = new InputManager();
		}

		return instance;
	}

	static void DeleteInstance()
	{
		if (!instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	static InputManager *instance;
#pragma endregion

private:
	void InitInputBinds();

	std::map<InputAction, sf::Keyboard::Key> InputBinds;
	std::map<InputAction, std::vector<Callback>> InputActionCallbacks;
};
