#pragma once

#include <SFML/Graphics.hpp>

class Window
{
public:
	Window();


	sf::RenderWindow window;

	sf::RenderWindow& GetWindow();

	int fpsMax = 60;

	#pragma region Singleton

		static Window* Instance()
		{
			if (!instance)
			{
				instance = new Window();
			}

			return instance;
		}

		static Window* DeleteInstance()
		{
			if (!instance)
			{
				delete instance;
				instance = nullptr;
			}
		}

		static Window* instance;
	#pragma endregion

};

