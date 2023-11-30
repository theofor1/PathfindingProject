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
	// graph = new Graph("", sf::Vector2i(1, 1));
	// graph = new Graph("", sf::Vector2i(10, 10));
	graph = new Graph("", sf::Vector2i(50, 50));
	ship = new PlayerShip();

	AddGameObject(graph);
	AddGameObject(ship);

	IScene::Start();

	// ship->SetPosition(graph->Cells[5][3]->GetPosition());
	ship->SetPosition(graph->Cells[0][0]->GetPosition());
}

void Level01::Update(float DeltaTime)
{
	IScene::Update(DeltaTime);

	FollowWayPoints(DeltaTime);
	// std::cout << ship->GetPosition().x << "   " << ship->GetPosition().y << "\n";
}

void Level01::Destroy()
{
	IScene::Destroy();
}

void Level01::Draw(sf::RenderWindow &window) const
{
	IScene::Draw(window);

	for (const Line line : DebugLines)
		line.Draw(window);
}

// Protected
void Level01::OnGraphCellOnClick()
{
	sf::Vector2i MouseLocation = sf::Mouse::getPosition(Window::Instance()->GetWindow());
	sf::Vector2f WorldMouseLocation = Window::Instance()->GetWindow().mapPixelToCoords(MouseLocation);

	Cell *CellStart = graph->GetCellByPosition(ship->GetPosition());
	Cell *CellEnd = graph->GetCellByPosition(WorldMouseLocation);
	// Cell *CellEnd = graph->Cells[0][0];

	// std::cout << ship->GetPosition().x << "   " << ship->GetPosition().y << "\n";

	if (CellStart == CellEnd || !CellStart || !CellEnd)
	{
		ResetPath();
		return;
	}

	// std::cout << CellEnd->GetPosition().x << "   " << CellEnd->GetPosition().y << "\n";

	// ship->SetPosition(sf::Vector2f(75, 25));
	// ship->SetPosition(CellEnd->GetPosition());
	// ship->SetPosition(graph->Cells[0][6]->GetPosition());

	// ship->SetPosition(CellEnd->GetPosition() - ship->LocalPosition);
	ResetPath();

	WayPoints = graph->GetPath(CellStart, CellEnd);
	UpdateDrawDebugLines();
}

void Level01::FollowWayPoints(float DeltaTime)
{
	if (WayPoints.size() == 0)
		return;

	UpdateDrawDebugLines();

	sf::Vector2f CurrentWayPoint = WayPoints[CurrentIndexWaypoint];

	if (Vector::GetDistance(CurrentWayPoint, ship->GetPosition()) > 5)
	{
		MoveTo(DeltaTime, CurrentWayPoint);
	}
	else
	{
		ship->SetPosition(CurrentWayPoint);
		CurrentIndexWaypoint++;

		if (CurrentIndexWaypoint >= WayPoints.size())
		{
			ResetPath();
		}
	}
}

void Level01::MoveTo(float DeltaTime, const sf::Vector2f TargetPosition)
{
	sf::Vector2f Direction = Vector::GetDirection(ship->GetPosition(), TargetPosition);
	Direction *= DeltaTime * 132;
	ship->AddWorldPosition(Direction);
}

void Level01::ResetPath()
{
	CurrentIndexWaypoint = 0;
	WayPoints.clear();
	UpdateDrawDebugLines();
}

void Level01::UpdateDrawDebugLines()
{
	DebugLines.clear();

	if (WayPoints.size() == 0)
		return;

	DebugLines.push_back(Line(ship->GetPosition(), sf::Vector2f(WayPoints[CurrentIndexWaypoint])));

	for (int i = CurrentIndexWaypoint; i <= WayPoints.size(); i++)
	{
		if (i + 1 >= WayPoints.size())
			return;

		sf::Vector2f StartLocation = WayPoints[i];
		sf::Vector2f EndLocation = WayPoints[i + 1];

		DebugLines.push_back(Line(StartLocation, EndLocation));
	}
}