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
	Count,
};

class InputManager
{
public:
	using Callback = std::function<void()>;

	InputManager();

	void Update();

	void BindOnTriggered(InputAction IA, const Callback& callback);
	void BindOnDown(InputAction IA, const Callback& callback);
	void BindOnUp(InputAction IA, const Callback& callback);
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

	void UpdateInputActionOnTriggered();
	void UpdateInputActionOnUp();
	void UpdateInputActionOnDown();

	void UpdateMouseInputActionOnTriggered();
	void UpdateMouseInputActionOnUp();
	void UpdateMouseInputActionOnDown();

	bool IsBinded(const std::vector<Callback> &Callbacks, const Callback &CallbackToCheck) const;

	std::map<InputAction, sf::Keyboard::Key> InputBinds;
	std::map<InputAction, sf::Mouse::Button> MouseBinds;


	std::map<InputAction, std::vector<Callback>> OnTringgeredInputActionCallbacks;
	std::map<InputAction, std::vector<Callback>> OnDownInputActionCallbacks;
	std::map<InputAction, std::vector<Callback>> OnUpInputActionCallbacks;

	std::map<InputAction, std::vector<Callback>> OnTriggeredMouseInputActionCallbacks;
	std::map<InputAction, std::vector<Callback>> OnDownMouseInputActionCallbacks;
	std::map<InputAction, std::vector<Callback>> OnUpMouseInputActionCallbacks;

	std::map<InputAction, bool> InputActionIsUp;
	std::map<InputAction, bool> InputActionIsDown;


};
