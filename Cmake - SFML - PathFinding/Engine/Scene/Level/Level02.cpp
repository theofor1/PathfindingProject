#include "Level02.h"
#include <Actor/PlayerShip/PlayerShip.h>
#include <System/Input/InputManager.h>
#include <Engine/Render/Window.h>
#include <GameObject/Graph/Graph.h>
#include <GameObject/Graph/Cell/Cell.h>
#include <Math/Vector/Vector.h>
#include <GameManager/IGameManager.h>

#include <iostream>

Level02::Level02()
{
}

void Level02::Start()
{
	Destroy();
	
	CurrentIndexWaypoint = 0;
	WayPoints.clear();
	DebugLines.clear();
	GameObjects.clear();

	graph = new Graph("", sf::Vector2i(20, 20));
	ship = new PlayerShip();

	AddGameObject(graph);
	AddGameObject(ship);

	IScene::Start();

	ship->SetPosition(graph->Cells[5][3]->GetPosition());

	InputManager::Instance()->Bind(InputAction::MouseL, [this]()
								   { OnGraphCellOnClick(); });
}

void Level02::Update(float DeltaTime)
{
	IScene::Update(DeltaTime);

	FollowWayPoints(DeltaTime);
	// std::cout << ship->GetPosition().x << "   " << ship->GetPosition().y << "\n";
}

void Level02::Destroy()
{
	IScene::Destroy();
}

void Level02::Draw(sf::RenderWindow &window) const
{
	IScene::Draw(window);

	for (const Line line : DebugLines)
		line.Draw(window);
}

// Protected
void Level02::OnGraphCellOnClick()
{
	sf::Vector2i MouseLocation = sf::Mouse::getPosition(Window::Instance()->GetWindow());
	sf::Vector2f WorldMouseLocation = Window::Instance()->GetWindow().mapPixelToCoords(MouseLocation);


	Cell *CellEnd = graph->GetCellByPosition(WorldMouseLocation);
	if (CurrentCellEnd == CellEnd)
		return;

	CurrentCellEnd = CellEnd;

	Cell *CellStart = graph->GetCellByPosition(ship->GetPosition());

	// sf::Vector2i Coordinate = graph->GetCellCoordinateByPosition(WorldMouseLocation);

	if (CellStart == CellEnd || !CellStart || !CellEnd)
		return;

	ResetPath();

	WayPoints = graph->GetPath(CellStart, CellEnd);

	UpdateDrawDebugLines();
}

void Level02::TestUpdateGraphSize(sf::Vector2i Size)
{
	graph->UpdateSize(sf::Vector2i(8, 7));
}

void Level02::FollowWayPoints(float DeltaTime)
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

void Level02::MoveTo(float DeltaTime, const sf::Vector2f TargetPosition)
{
	sf::Vector2f Direction = Vector::GetDirection(ship->GetPosition(), TargetPosition);
	Direction *= DeltaTime * 132;
	ship->AddWorldPosition(Direction);
}

void Level02::ResetPath()
{
	CurrentIndexWaypoint = 0;
	WayPoints.clear();
	UpdateDrawDebugLines();
}

void Level02::UpdateDrawDebugLines()
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