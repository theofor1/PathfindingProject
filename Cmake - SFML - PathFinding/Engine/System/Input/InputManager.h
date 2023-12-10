#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <string>
#include <map>
#include <functional>

enum class InputAction
{
	Left,
	Right,
	Up,
	Down,
	MouseL,
	MouseR,
};

class InputManager
{
public:
	using Callback = std::function<void()>;

	InputManager();

	void Update();

	void Bind(InputAction IA, const Callback& callback);
	void ResetBind();

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
	void InitMouseButtonBinds();

	void UpdateInputAction();
	void UpdateMouseInputAction();

	bool IsBinded(const std::vector<Callback> &Callbacks, const Callback &CallbackToCheck) const;

	std::map<InputAction, sf::Keyboard::Key> InputBinds;
	std::map<InputAction, sf::Mouse::Button> MouseBinds;


	std::map<InputAction, std::vector<Callback>> InputActionCallbacks;
	std::map<InputAction, std::vector<Callback>> MouseInputActionCallbacks;
};
