#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <map>

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

	InputManager();

	void Update();

	void InputPressed(const sf::Keyboard::Key& key, const InputAction Action);
	void InputReleased(const sf::Keyboard::Key& key, const InputAction Action);

	float GetAxis(InputAxis Axis);
	bool GetAction(InputAction _Action);
	bool GetActionDown(InputAction _Action); // Once time while pressed

#pragma region Singleton

	static InputManager* Instance()
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

	static InputManager* instance;
#pragma endregion

private:
	void InitInputBinds();

	std::map<sf::Keyboard::Key, InputAction> InputBinds;

	struct fInput {
		float Movement = 0;
		bool IsOnMovement();
		void SetMovement(float _movement);
		void AddMovement(float Up);
		void ResetMovement();
	};
	
	struct bInput {
		bool IsOnAction = false;
		bool WaitRelease = false;
	};

	fInput AxisVertical;
	fInput AxisHorizontal;

	bInput Fire;
};

