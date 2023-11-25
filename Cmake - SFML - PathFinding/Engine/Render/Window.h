#pragma once

#include <SFML/Graphics.hpp>

class Window
{
public:
	Window();


	sf::RenderWindow window;

	sf::RenderWindow& GetWindow();

	int fpsMax = 60;
	
	int Width = 1920;
	int Height = 1080;
	std::string Title = "Path Finder";

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

