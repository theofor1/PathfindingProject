#include "InputManager.h"
#include <iostream>

InputManager *InputManager::instance = nullptr;

InputManager::InputManager()
{
	InitInputBinds();

	for (const auto &pair : InputBinds)
	{
		InputAction IA = pair.first;
		InputActionCallbacks[IA] = std::vector<Callback>();
	}

}

void InputManager::Update()
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

void InputManager::Bind(InputAction IA, const Callback &callback)
{
	InputActionCallbacks[IA].push_back(callback);
}

void InputManager::InitInputBinds()
{
	InputBinds[InputAction::Up] = sf::Keyboard::Z;
	InputBinds[InputAction::Down] = sf::Keyboard::S;
	InputBinds[InputAction::Left] = sf::Keyboard::Q;
	InputBinds[InputAction::Right] = sf::Keyboard::D;
}
