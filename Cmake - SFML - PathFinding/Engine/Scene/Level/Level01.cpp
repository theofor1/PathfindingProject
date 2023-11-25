#include "Level01.h"
#include <Actor/PlayerShip/PlayerShip.h>
#include <iostream>

Level01::Level01()
{

}

void Level01::Start()
{
	AddGameObject(new PlayerShip());
	IScene::Start();
}

void Level01::Update(float DeltaTime)
{
	IScene::Update(DeltaTime);
}

void Level01::Destroy()
{
	IScene::Destroy();
}


