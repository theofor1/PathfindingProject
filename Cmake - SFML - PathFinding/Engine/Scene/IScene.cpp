#include "IScene.h"
#include <Component/Collider/BoxCollider.h>
#include <Engine/Render/Window.h>
#include <GameObject/GameObject.h>
#include <iostream>

IScene::IScene()
{
}

IScene::~IScene()
{
}

void IScene::Start()
{
	for (size_t i = 0; i < GameObjects.size(); i++)
		GameObjects[i]->Start();
}

void IScene::Update(float DeltaTime)
{
	for (size_t i = 0; i < GameObjects.size(); i++)
		GameObjects[i]->Update(DeltaTime);
}

void IScene::Destroy()
{
	for (size_t i = 0; i < GameObjects.size(); i++)
		GameObjects[i]->Destroy();
}

void IScene::Draw(sf::RenderWindow& window) const
{
	for (size_t i = 0; i < GameObjects.size(); i++)
		GameObjects[i]->Draw(window);
}

void IScene::AddGameObject(GameObject* gameObject)
{
	GameObjects.push_back(gameObject);
}

std::vector<GameObject*> IScene::GetGameObjects()
{
	return GameObjects;
}
