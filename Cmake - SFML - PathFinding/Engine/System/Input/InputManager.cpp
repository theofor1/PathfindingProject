#include "InputManager.h"
#include <iostream>

InputManager *InputManager::instance = nullptr;

InputManager::InputManager()
{
	InitInputBinds();
	InitMouseButtonBinds();

	for (int i = 0; i < static_cast<int>(InputAction::Count); ++i)
	{
		InputAction action = static_cast<InputAction>(i);
		InputActionIsDown[action] = false;
		InputActionIsUp[action] = true;
	}
}

void InputManager::Update()
{
	UpdateInputActionOnTriggered();
	UpdateInputActionOnDown();
	UpdateInputActionOnUp();

	UpdateMouseInputActionOnTriggered();
	UpdateMouseInputActionOnUp();
	UpdateMouseInputActionOnDown();
}

void InputManager::BindOnTriggered(InputAction IA, const Callback &callback)
{
	if (IA == InputAction::MouseL || IA == InputAction::MouseR)
	{
		if (!IsBinded(OnTriggeredMouseInputActionCallbacks[IA], callback))
			OnTriggeredMouseInputActionCallbacks[IA].push_back(callback);
	}
	else
	{
		if (!IsBinded(OnTringgeredInputActionCallbacks[IA], callback))
			OnTringgeredInputActionCallbacks[IA].push_back(callback);
	}
}

void InputManager::BindOnDown(InputAction IA, const Callback &callback)
{
	if (IA == InputAction::MouseL || IA == InputAction::MouseR)
	{
		if (!IsBinded(OnDownMouseInputActionCallbacks[IA], callback))
			OnDownMouseInputActionCallbacks[IA].push_back(callback);
	}
	else
	{
		if (!IsBinded(OnDownInputActionCallbacks[IA], callback))
			OnDownInputActionCallbacks[IA].push_back(callback);
	}
}

void InputManager::BindOnUp(InputAction IA, const Callback &callback)
{
	if (IA == InputAction::MouseL || IA == InputAction::MouseR)
	{
		if (!IsBinded(OnUpMouseInputActionCallbacks[IA], callback))
			OnUpMouseInputActionCallbacks[IA].push_back(callback);
	}
	else
	{
		if (!IsBinded(OnUpInputActionCallbacks[IA], callback))
			OnUpInputActionCallbacks[IA].push_back(callback);
	}
}

void InputManager::ResetBind()
{
	// for (auto &pair : InputActionCallbacks)
	// {
	// 	InputAction IA = pair.first;
	// 	InputActionCallbacks[IA].clear();
	// }
	// for (auto &pair : MouseInputActionCallbacks)
	// {
	// 	InputAction IA = pair.first;
	// 	MouseInputActionCallbacks[IA].clear();
	// }
}

// Private

void InputManager::UpdateInputActionOnTriggered()
{
	for (const auto &pair : InputBinds)
	{
		InputAction IA = pair.first;
		sf::Keyboard::Key key = pair.second;

		if (sf::Keyboard::isKeyPressed(key))
		{
			for (const auto &callback : OnTringgeredInputActionCallbacks[IA])
			{
				callback();
			}
		}
	}
}
void InputManager::UpdateInputActionOnDown()
{
	for (const auto &pair : InputBinds)
	{
		InputAction IA = pair.first;
		sf::Keyboard::Key key = pair.second;

		if (sf::Keyboard::isKeyPressed(key) && InputActionIsUp[IA])
		{
			InputActionIsUp[IA] = false;
			InputActionIsDown[IA] = true;

			for (const auto &callback : OnDownInputActionCallbacks[IA])
			{
				callback();
			}
		}
	}
}
void InputManager::UpdateInputActionOnUp()
{
	for (const auto &pair : InputBinds)
	{
		InputAction IA = pair.first;
		sf::Keyboard::Key key = pair.second;

		if (!sf::Keyboard::isKeyPressed(key) && InputActionIsDown[IA])
		{
			InputActionIsUp[IA] = true;
			InputActionIsDown[IA] = false;
			for (const auto &callback : OnUpInputActionCallbacks[IA])
			{
				callback();
			}
		}
	}
}

void InputManager::UpdateMouseInputActionOnTriggered()
{
	for (const auto &pair : MouseBinds)
	{
		InputAction IA = pair.first;
		sf::Mouse::Button button = pair.second;

		if (sf::Mouse::isButtonPressed(button))
		{
			for (const auto &callback : OnTriggeredMouseInputActionCallbacks[IA])
			{
				callback();
			}
		}
	}
}
void InputManager::UpdateMouseInputActionOnDown()
{
	for (const auto &pair : MouseBinds)
	{
		InputAction IA = pair.first;
		sf::Mouse::Button button = pair.second;

		if (sf::Mouse::isButtonPressed(button) && InputActionIsUp[IA])
		{
			std::cout << "toto\n";

			InputActionIsUp[IA] = false;
			InputActionIsDown[IA] = true;
			for (const auto &callback : OnDownMouseInputActionCallbacks[IA])
			{
				callback();
			}
		}
	}
}
void InputManager::UpdateMouseInputActionOnUp()
{
	for (const auto &pair : MouseBinds)
	{
		InputAction IA = pair.first;
		sf::Mouse::Button button = pair.second;

		if (!sf::Mouse::isButtonPressed(button) && InputActionIsDown[IA])
		{
			InputActionIsUp[IA] = true;
			InputActionIsDown[IA] = false;
			for (const auto &callback : OnUpMouseInputActionCallbacks[IA])
			{
				callback();
			}
		}
	}
}

void InputManager::InitInputBinds()
{
	InputBinds[InputAction::Up] = sf::Keyboard::Z;
	InputBinds[InputAction::Down] = sf::Keyboard::S;
	InputBinds[InputAction::Left] = sf::Keyboard::Q;
	InputBinds[InputAction::Right] = sf::Keyboard::D;

	for (const auto &pair : InputBinds)
	{
		InputAction IA = pair.first;
		OnTringgeredInputActionCallbacks[IA] = std::vector<Callback>();
		OnDownInputActionCallbacks[IA] = std::vector<Callback>();
		OnUpInputActionCallbacks[IA] = std::vector<Callback>();
	}
}

void InputManager::InitMouseButtonBinds()
{
	MouseBinds[InputAction::MouseL] = sf::Mouse::Left;
	MouseBinds[InputAction::MouseR] = sf::Mouse::Right;

	for (const auto &pair : MouseBinds)
	{
		InputAction IA = pair.first;
		OnTriggeredMouseInputActionCallbacks[IA] = std::vector<Callback>();
		OnDownMouseInputActionCallbacks[IA] = std::vector<Callback>();
		OnUpMouseInputActionCallbacks[IA] = std::vector<Callback>();
	}
}

bool InputManager::IsBinded(const std::vector<Callback> &Callbacks, const Callback &CallbackToCheck) const
{
	for (const auto &callback : Callbacks)
	{
		if (callback.target<void()>() == CallbackToCheck.target<void()>())
			return true;
	}
	return false;
}