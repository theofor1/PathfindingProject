#pragma once

//#include <SFML/Graphics.hpp>
//#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

//#include <InputMgr.h>
//#include "IScene.h"
//#include "MyLevel.h"
#include <Engine/Scene/IScene.h>

class IGameManager
{
public:
	IGameManager();

	void RunGame();

	void AddLevel(IScene NewScene);

	IScene& GetActiveScene();

	#pragma region Singleton

		static IGameManager* Instance()
		{
			if (!instance)
			{
				instance = new IGameManager();
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

		static IGameManager* instance;
	#pragma endregion

private:
	std::vector<IScene> Scenes;
	int indexActiveScene = 0;

	void StartActiveScene();
	void UpdateActiveScene(float fDeltaTime);
	void DrawActiveScene(sf::RenderWindow& window) const;
};

