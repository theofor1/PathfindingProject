#pragma once

#include "IScene.h"


class IGameManager
{
public:
	IGameManager();

	void RunGame();

	void AddLevel(IScene* NewScene);

	IScene* GetActiveScene();

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
	std::vector<IScene*> Scenes;
	int indexActiveScene = 0;

	void StartActiveScene();
	void UpdateActiveScene(float DeltaTime);
	void DrawActiveScene(sf::RenderWindow& window) const;
};

