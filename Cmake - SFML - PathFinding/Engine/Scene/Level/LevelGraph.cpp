#include "LevelGraph.h"
#include <Actor/PlayerShip/PlayerShip.h>
#include <System/Input/InputManager.h>
#include <Engine/Render/Window.h>
#include <GameObject/Graph/Graph.h>
#include <GameObject/Graph/Cell/Cell.h>
#include <Math/Vector/Vector.h>
#include <GameManager/IGameManager.h>

#include <iostream>

LevelGraph::LevelGraph()
{
}

void LevelGraph::Start()
{
	// graph = new Graph("", sf::Vector2i(1, 1));
	graph = new Graph("", sf::Vector2i(10, 10));
	graph->Cells[1][1]->SetIsAlive(false);
	graph->Cells[1][2]->SetIsAlive(false);
	graph->Cells[1][3]->SetIsAlive(false);

	graph->Cells[3][4]->SetIsAlive(false);
	graph->Cells[3][6]->SetIsAlive(false);
	graph->ReGenerateWaypoints();
	// graph = new Graph("", sf::Vector2i(50, 50));
	Destroy();

	CurrentIndexWaypoint = 0;
	GameObjects.clear();
	WayPoints.clear();
	DebugLines.clear();

	graph = new Graph("", sf::Vector2i(10, 10));
	ship = new PlayerShip();
	// Create a button for the level : Pos -> Start x and y in % of screen, Size -> size x and y in % of screen
	// Call Start and Update of the button in Start and Update of level. 
	// In Draw of level, call UpdateRect, then Draw of the button
	//button = new Button(sf::Vector2f(0.3, 0.3), sf::Vector2f(0.1,0.1));

	AddGameObject(graph);
	AddGameObject(ship);

	IScene::Start();
	//button->Start();
	//button->RenderRectangle.setFillColor(sf::Color::White);
	//button->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));

	// ship->SetPosition(graph->Cells[5][3]->GetPosition());
	ship->SetPosition(graph->Cells[0][0]->GetPosition());

	InputManager::Instance()->Bind(InputAction::MouseL, [this]()
								   { OnGraphCellOnClick(); });
}

void LevelGraph::Update(float DeltaTime)
{
	IScene::Update(DeltaTime);
	//button->Update(DeltaTime);
	FollowWayPoints(DeltaTime);
	// std::cout << ship->GetPosition().x << "   " << ship->GetPosition().y << "\n";
}

void LevelGraph::Destroy()
{
	IScene::Destroy();
}

void LevelGraph::Draw(sf::RenderWindow &window) const
{
	IScene::Draw(window);
	sf::FloatRect windowRect(0, 0, window.getSize().x, window.getSize().y);
	//button->UpdateRect(windowRect);
	//button->Draw(window);
	for (const Line line : DebugLines)
		line.Draw(window);
}

// Protected
void LevelGraph::OnGraphCellOnClick()
{
	sf::Vector2i MouseLocation = sf::Mouse::getPosition(Window::Instance()->GetWindow());
	sf::Vector2f WorldMouseLocation = Window::Instance()->GetWindow().mapPixelToCoords(MouseLocation);

	/*
	if (button->Clicked(WorldMouseLocation)) {
		std::cout << "Clicked" << std::endl;
	}
	*/

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

void LevelGraph::TestUpdateGraphSize(sf::Vector2i Size)
{
	graph->UpdateSize(sf::Vector2i(8, 7));
}

void LevelGraph::FollowWayPoints(float DeltaTime)
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

void LevelGraph::MoveTo(float DeltaTime, const sf::Vector2f TargetPosition)
{
	sf::Vector2f Direction = Vector::GetDirection(ship->GetPosition(), TargetPosition);
	Direction *= DeltaTime * 132;
	ship->AddWorldPosition(Direction);
}

void LevelGraph::ResetPath()
{
	CurrentIndexWaypoint = 0;
	WayPoints.clear();
	UpdateDrawDebugLines();
}

void LevelGraph::UpdateDrawDebugLines()
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