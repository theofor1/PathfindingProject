// #include "Level01.h"
// #include <Actor/PlayerShip/PlayerShip.h>
// #include <Actor/PlayerShip/PlayerLaser.h>
// #include <Component/Transform/Transform.h>
// #include <Engine/Render/Ressource/TextureManager.h>
// #include <Engine/Render/Drawable/Sprite/Sprite.h>

// Level01::Level01()
// {
// 	AddGameObject(new PlayerShip());
// }

// void Level01::Start()
// {
// 	IScene::Start();
// }

// void Level01::Update(float fDeltaTime)
// {
// 	IScene::Update(fDeltaTime);
// }

// void Level01::Destroy()
// {
// 	IScene::Destroy();
// }

// int Level01::GetTotalCountPlayerLaser() const
// {
// 	int TotalCount = 0;
// 	for (size_t i = 0; i < GameObjects.size(); i++)
// 	{
// 		if (dynamic_cast<PlayerLaser*>(GameObjects[i]))
// 		{
// 			TotalCount++;
// 		}
// 	}
// 	return TotalCount;
// }


