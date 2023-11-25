#include "InputManager.h"
#include <iostream>

InputManager *InputManager::instance = nullptr;

InputManager::InputManager()
{
	InitInputBinds();
	InitMouseButtonBinds();
}

void InputManager::Update()
{
	UpdateInputAction();
	UpdateMouseInputAction();
}

void InputManager::Bind(InputAction IA, const Callback &callback)
{
	if (IA == InputAction::MouseL || IA == InputAction::MouseR)
	{
		MouseInputActionCallbacks[IA].push_back(callback);
	}
	else
	{
		InputActionCallbacks[IA].push_back(callback);
	}
}

// Private

void InputManager::UpdateInputAction()
{
	for (const auto &pair : InputBinds)
	{
		InputAction IA = pair.first;
		sf::Keyboard::Key key = pair.second;

		if (sf::Keyboard::isKeyPressed(key))
		{
			for (const auto &callback : InputActionCallbacks[IA])
			{
				callback();
			}
		}
	}
}

void InputManager::UpdateMouseInputAction()
{
	for (const auto &pair : MouseBinds)
	{
		InputAction IA = pair.first;
		sf::Mouse::Button button = pair.second;

		if (sf::Mouse::isButtonPressed(button))
		{
			for (const auto &callback : MouseInputActionCallbacks[IA])
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
		InputActionCallbacks[IA] = std::vector<Callback>();
	}
}

void InputManager::InitMouseButtonBinds()
{
	MouseBinds[InputAction::MouseL] = sf::Mouse::Left;
	MouseBinds[InputAction::MouseR] = sf::Mouse::Right;

	for (const auto &pair : MouseBinds)
	{
		InputAction IA = pair.first;
		MouseInputActionCallbacks[IA] = std::vector<Callback>();
	}
}
