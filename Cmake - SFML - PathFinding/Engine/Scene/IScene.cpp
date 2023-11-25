#include "IScene.h"
#include <Component/Collider/BoxCollider.h>
#include <Engine/Render/Window.h>
#include <GameObject/GameObject.h>

IScene::IScene()
{
}

IScene::~IScene()
{
}

void IScene::Start()
{
	// GameObjectsWithCollider = GetGameObjectsWidthColliders();

	for (size_t i = 0; i < GameObjects.size(); i++)
		GameObjects[i]->Start();
}

void IScene::Update(float fDeltaTime)
{
	for (size_t i = 0; i < GameObjects.size(); i++)
		GameObjects[i]->Update(fDeltaTime);

	// ExtractGameObjectsByCase();
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

// void IScene::OnCollision()
// {
// 	OnCollisionStay();
// }


// Private

// void IScene::OnCollisionStay()
// {
// 	for (size_t k = 0; k < GameObjectsByCase.size(); k++)
// 	{
// 		for (size_t i = 0; i < GameObjectsByCase[k].size(); i++)
// 		{
// 			for (size_t j = 0; j < GameObjectsByCase[k].size(); j++)
// 			{
// 				if (i != j)
// 				{
// 					if (GameObjectsByCase[k][i]->GetComponent<BoxCollider>()->GetMask() && GameObjectsByCase[k][j]->GetComponent<BoxCollider>()->GetMask())
// 					{
// 						if (GameObjectsByCase[k][i]->GetComponent<BoxCollider>()->IsOnCollisionWidth(GameObjectsByCase[k][j]->GetComponent<BoxCollider>()->GetRect()))
// 						{
// 							GameObjectsByCase[k][i]->OnCollisionStay(GameObjectsByCase[k][j]);
// 							if (GameObjectsByCase[k][j]->GetComponent<BoxCollider>()->isStatic)
// 							{
// 								GameObjectsByCase[k][i]->GetComponent<BoxCollider>()->CancelCollisionWith(GameObjectsByCase[k][j]->GetComponent<BoxCollider>());
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}

// 	}
// }

// void IScene::ExtractGameObjectsByCase()
// {
// 	GameObjectsByCase.clear();

// 	for (size_t x = 0; x < 1500; x += CaseSize.x)
// 		for (size_t y = 0; y < 1000; y += CaseSize.y)
// 		{
// 			std::vector<GameObject*> GameObjects;

// 			for (size_t i = 0; i < GameObjectsWithCollider.size(); i++)
// 			{
// 				sf::FloatRect Case;
// 				Case.width = CaseSize.x;
// 				Case.height = CaseSize.y;
// 				Case.left = x;
// 				Case.top = y;

// 				sf::FloatRect rectGameObject = GameObjectsWithCollider[i]->GetComponent<ICollider>()->GetRect();

// 				// Check collider is in Case
// 				if (Case.intersects(rectGameObject))
// 					GameObjects.push_back(GameObjectsWithCollider[i]);
// 			}

// 			GameObjectsByCase.push_back(GameObjects);
// 		}
// }


// std::vector<GameObject*> IScene::GetGameObjectsWidthColliders()
// {
// 	std::vector<GameObject*> tmp;

// 	for (size_t i = 0; i < GameObjects.size(); i++)
// 		// Check if this GameObject has a collider component
// 		if (GameObjects[i]->GetComponent<BoxCollider>())
// 			tmp.push_back(GameObjects[i]);

// 	return tmp;
// }
