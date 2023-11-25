#include "Level01.h"
#include <Actor/PlayerShip/PlayerShip.h>
#include <System/Input/InputManager.h>
#include <Engine/Render/Window.h>
#include <GameObject/Graph/Graph.h>
#include <GameObject/Graph/Cell/Cell.h>
#include <Math/Vector/Vector.h>

#include <iostream>

Level01::Level01()
{
	TargetCell = nullptr;
	InputManager::Instance()->Bind(InputAction::MouseL, [this]()
								   { OnGraphCellOnClick(); });
}

void Level01::Start()
{
	graph = new Graph("", sf::Vector2i(10, 10));
	// graph = new Graph("", sf::Vector2i(30, 20));
	ship = new PlayerShip();

	AddGameObject(graph);
	AddGameObject(ship);

	IScene::Start();
}

void Level01::Update(float DeltaTime)
{
	IScene::Update(DeltaTime);

	if (TargetCell)
	{
		sf::Vector2f Direction = Vector::GetDirection(ship->GetPosition(), TargetCell->GetPosition());

		Direction *= DeltaTime * 132;

		if (Vector::GetDistance(TargetCell->GetPosition(), ship->GetPosition()) > 1)
			ship->AddWorldPosition(Direction);
		else
			ship->SetPosition(TargetCell->GetPosition());
	}
}

void Level01::Destroy()
{
	IScene::Destroy();
}

// Protected
void Level01::OnGraphCellOnClick()
{
	sf::Vector2i MouseLocation = sf::Mouse::getPosition(Window::Instance()->GetWindow());
	sf::Vector2f WorldMouseLocation = Window::Instance()->GetWindow().mapPixelToCoords(MouseLocation);
	TargetCell = graph->GetCellByPosition(WorldMouseLocation);
}
