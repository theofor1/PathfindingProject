#include "InputManager.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager()
{
	InitInputBinds();
}

void InputManager::Update()
{
	for (const auto& p : InputBinds)
	{
		const sf::Keyboard::Key& key = p.first;
		const InputAction Action = p.second;
		InputReleased(key, Action);
	}
	
	for (const auto& p : InputBinds)
	{
		const sf::Keyboard::Key& key = p.first;
		const InputAction Action = p.second;
		InputPressed(key, Action);
	}
}

void InputManager::InputPressed(const sf::Keyboard::Key& key, const InputAction Action)
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		if (Action == InputAction::Left)
			AxisHorizontal.AddMovement(-1);

		if (Action == InputAction::Right)
			AxisHorizontal.AddMovement(1);

		if (Action == InputAction::Up)
			AxisVertical.AddMovement(-1);
			
		if (Action == InputAction::Down)
			AxisVertical.AddMovement(1);	
		
		if (Action == InputAction::Fire)
			Fire.IsOnAction = true;
	}
}

void InputManager::InputReleased(const sf::Keyboard::Key& key, const InputAction Action)
{
	if (!sf::Keyboard::isKeyPressed(key))
	{
		if (Action == InputAction::Left)
			AxisHorizontal.ResetMovement();

		if (Action == InputAction::Right)
			AxisHorizontal.ResetMovement();

		if (Action == InputAction::Up)
			AxisVertical.ResetMovement();
			
		if (Action == InputAction::Down)
			AxisVertical.ResetMovement();

		if (Action == InputAction::Fire)
		{
			Fire.WaitRelease = false;
			Fire.IsOnAction = false;
		}
	}
}

float InputManager::GetAxis(InputAxis Axis)
{
	if (Axis == InputAxis::Vertical)
		return AxisVertical.Movement;
	else if (Axis == InputAxis::Horizontal)
		return AxisHorizontal.Movement;

	return 0.0f;
}

bool InputManager::GetAction(InputAction _Action)
{
	for (const auto& p : InputBinds)
	{
		const InputAction Action = p.second;
		if (_Action == Action)
		{
			if (Action == InputAction::Fire)
				return Fire.IsOnAction;
		}
	}

	return false;
}

bool InputManager::GetActionDown(InputAction _Action)
{
	for (const auto& p : InputBinds)
	{
		const InputAction Action = p.second;
		if (_Action == Action)
		{
			if (Action == InputAction::Fire && !Fire.WaitRelease)
			{
				if (Fire.IsOnAction)
				{
					Fire.WaitRelease = true;
					return Fire.IsOnAction;
				}
			}
		}
	}

	return false;
}

void InputManager::InitInputBinds()
{
#define INIT_DEFAULT_BIND(key, bind) InputBinds.insert(std::make_pair(key, bind));
	INIT_DEFAULT_BIND(sf::Keyboard::Z, InputAction::Up)
	INIT_DEFAULT_BIND(sf::Keyboard::Q, InputAction::Left)
	INIT_DEFAULT_BIND(sf::Keyboard::S, InputAction::Down)
	INIT_DEFAULT_BIND(sf::Keyboard::D, InputAction::Right)
	INIT_DEFAULT_BIND(sf::Keyboard::J, InputAction::Fire)
#undef INIT_DEFAULT_BIND

}


bool InputManager::fInput::IsOnMovement()
{
	if (Movement != 0)
		return true;

	return false;
}

void InputManager::fInput::SetMovement(float _movement)
{
	Movement = _movement;
}

void InputManager::fInput::AddMovement(float Up)
{
	Movement += Up;
	if (Movement > 1)
		Movement = 1;
	else if (Movement < -1)
		Movement = -1;
}

void InputManager::fInput::ResetMovement()
{
	Movement = 0;
}


