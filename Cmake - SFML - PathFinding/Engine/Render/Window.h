#pragma once

#include <SFML/Graphics.hpp>

class Window
{
public:
	Window(const float _speedMove = 100);

	sf::RenderWindow& GetWindow();
	sf::View& GetView();

	void Update(const float DeltaTime);
	void SetViewSpeedMove(const float _speedMove);

	void UpdateView();

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

private:
	sf::RenderWindow window;
    sf::View viewport;

	sf::Vector2f axis;
	float speedMove;

};

