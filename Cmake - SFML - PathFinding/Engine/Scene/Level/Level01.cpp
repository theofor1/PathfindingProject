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

	FollowWayPoints(DeltaTime);
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

	Cell *CellStart = graph->GetCellByPosition(ship->GetPosition());
	Cell *CellEnd = graph->GetCellByPosition(WorldMouseLocation);

	CurrentIndexWaypoint = 0;
	WayPoints.clear();

	WayPoints = graph->GetPath(CellStart, CellEnd);
	std::cout << WayPoints.size() << "\n";
}

void Level01::FollowWayPoints(float DeltaTime)
{
	if (WayPoints.size() == 0)
		return;

	sf::Vector2f CurrentWayPoint = WayPoints[CurrentIndexWaypoint];

	if (Vector::GetDistance(CurrentWayPoint, ship->GetPosition()) > 1)
	{
		MoveTo(DeltaTime, CurrentWayPoint);
	}
	else
	{
		ship->SetPosition(CurrentWayPoint);
		CurrentIndexWaypoint++;

		if (CurrentIndexWaypoint >= WayPoints.size())
		{
			CurrentIndexWaypoint = 0;
			WayPoints.clear();
		}
	}
}

void Level01::MoveTo(float DeltaTime, const sf::Vector2f TargetPosition)
{
	sf::Vector2f Direction = Vector::GetDirection(ship->GetPosition(), TargetPosition);
	Direction *= DeltaTime * 132;
	ship->AddWorldPosition(Direction);
}
