#include "LevelCustom.h"
#include <Actor/PlayerShip/PlayerShip.h>
#include <System/Input/InputManager.h>
#include <Engine/Render/Window.h>
#include <GameObject/Graph/Graph.h>
#include <GameObject/Graph/Cell/Cell.h>
#include <Math/Vector/Vector.h>

#include <iostream>

LevelCustom::LevelCustom()
{
	// InputManager::Instance()->Bind(InputAction::MouseL, [this]()
	// 							   { EventOnClick(); });

}

void LevelCustom::Start()
{
	// graph = new Graph("", sf::Vector2i(1, 1));
	graph = new Graph("", sf::Vector2i(10, 10));
	GraphHeightNbCells = 10;
	GraphWidthNbCells = 10;
	// graph = new Graph("", sf::Vector2i(50, 50));

	ship = new PlayerShip();
	

	AddGameObject(graph);
	AddGameObject(ship);

	IScene::Start();

	// ship->SetPosition(graph->Cells[5][3]->GetPosition());
	ship->SetPosition(graph->Cells[0][0]->GetPosition());

	outerBox = new UIElement(sf::Vector2f(0.8f, 0.f), sf::Vector2f(0.1f, 0.3f));
	outerBox->SetLayout(UILayout::List, UIDirection::Vertical);
	
	addWalls = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.1f));
	addWalls->RenderRectangle.setFillColor(sf::Color::White);
	addWalls->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	outerBox->AddChild(addWalls);

	graphHeightBox = new UIElement(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.1f));
	graphHeightBox->SetLayout(UILayout::List, UIDirection::Horizontal);
	outerBox->AddChild(graphHeightBox);
	removeGraphHeight = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.5f, 1.f));
	removeGraphHeight->RenderRectangle.setFillColor(sf::Color::White);
	removeGraphHeight->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	addGraphHeight = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.5f, 1.f));
	addGraphHeight->RenderRectangle.setFillColor(sf::Color::White);
	addGraphHeight->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	graphHeightBox->AddChild(removeGraphHeight);
	graphHeightBox->AddChild(addGraphHeight);

	graphWidthBox = new UIElement(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.1f));
	graphWidthBox->SetLayout(UILayout::List, UIDirection::Horizontal);
	outerBox->AddChild(graphWidthBox);
	removeGraphWidth = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.5f, 1.f));
	removeGraphWidth->RenderRectangle.setFillColor(sf::Color::White);
	removeGraphWidth->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	addGraphWidth = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.5f, 1.f));
	addGraphWidth->RenderRectangle.setFillColor(sf::Color::White);
	addGraphWidth->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	graphWidthBox->AddChild(removeGraphWidth);
	graphWidthBox->AddChild(addGraphWidth);
	

	outerBox->Start();
}

void LevelCustom::Update(float DeltaTime)
{
	TimeSinceLastInput += DeltaTime;
	IScene::Update(DeltaTime);
	outerBox->Update(DeltaTime);
	FollowWayPoints(DeltaTime);
	// std::cout << ship->GetPosition().x << "   " << ship->GetPosition().y << "\n";
}

void LevelCustom::Destroy()
{
	delete outerBox;
	IScene::Destroy();
}

void LevelCustom::Draw(sf::RenderWindow &window) const
{
	IScene::Draw(window);
	sf::FloatRect windowRect(0, 0, window.getSize().y, window.getSize().x);
	outerBox->UpdateRect(windowRect);
	outerBox->Draw(window);
	for (const Line line : DebugLines)
		line.Draw(window);
}

// Protected
void LevelCustom::OnGraphCellOnClick()
{
	sf::Vector2i MouseLocation = sf::Mouse::getPosition(Window::Instance()->GetWindow());
	sf::Vector2f WorldMouseLocation = Window::Instance()->GetWindow().mapPixelToCoords(MouseLocation);


	
	sf::Vector2i Coordinate = graph->GetCellCoordinateByPosition(WorldMouseLocation);
	std::cout <<Coordinate.x << "   " << Coordinate.y << "\n";
	
	
		
	if (OnWallMode) {
		Cell* CurCell = graph->GetCellByPosition(WorldMouseLocation);
		Cell* PlayerCell = graph->GetCellByPosition(ship->GetPosition());
		if (CurCell == PlayerCell || !CurCell) return;
		CurCell->SetIsAlive(!CurCell->GetIsAlive());
		graph->ReGenerateWaypoints();
	}
	else {

		ResetPath();
		Cell* CellStart = graph->GetCellByPosition(ship->GetPosition());
		Cell* CellEnd = graph->GetCellByPosition(WorldMouseLocation);

		if (CellStart == CellEnd || !CellStart || !CellEnd)
			return;

		WayPoints = graph->GetPath(CellStart, CellEnd);
		UpdateDrawDebugLines();
	}
}

void LevelCustom::EventOnClick()
{
	if (TimeSinceLastInput < 0.3) return;

	TimeSinceLastInput = 0;

	sf::Vector2i MouseLocation = sf::Mouse::getPosition(Window::Instance()->GetWindow());
	sf::Vector2f WorldMouseLocation = Window::Instance()->GetWindow().mapPixelToCoords(MouseLocation);

	if (addWalls->Clicked(WorldMouseLocation)) {
		OnWallMode = !OnWallMode;
		if (!OnWallMode) 
			addWalls->RenderRectangle.setFillColor(sf::Color::White);
		else 
			addWalls->RenderRectangle.setFillColor(sf::Color(239, 239, 240));

		return;
	}

	if (removeGraphHeight->Clicked(WorldMouseLocation)) {
		if (GraphHeightNbCells == 4) return;
		GraphHeightNbCells--;
		graph->UpdateSize(sf::Vector2i(GraphHeightNbCells, GraphWidthNbCells));
		return;
	}

	if (addGraphHeight->Clicked(WorldMouseLocation)) {
		if (GraphHeightNbCells == 14) return;
		GraphHeightNbCells++;
		graph->UpdateSize(sf::Vector2i(GraphHeightNbCells, GraphWidthNbCells));
		return;
	}

	if (removeGraphWidth->Clicked(WorldMouseLocation)) {
		if (GraphWidthNbCells == 4) return;
		GraphWidthNbCells--;
		graph->UpdateSize(sf::Vector2i(GraphHeightNbCells, GraphWidthNbCells));
		return;
	}

	if (addGraphWidth->Clicked(WorldMouseLocation)) {
		if (GraphWidthNbCells == 14) return;
		GraphWidthNbCells++;
		graph->UpdateSize(sf::Vector2i(GraphHeightNbCells, GraphWidthNbCells));
		return;
	}

	OnGraphCellOnClick();
}

void LevelCustom::TestUpdateGraphSize(sf::Vector2i Size)
{
	graph->UpdateSize(sf::Vector2i(8, 7));
}

void LevelCustom::FollowWayPoints(float DeltaTime)
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

void LevelCustom::MoveTo(float DeltaTime, const sf::Vector2f TargetPosition)
{
	sf::Vector2f Direction = Vector::GetDirection(ship->GetPosition(), TargetPosition);
	Direction *= DeltaTime * 132;
	ship->AddWorldPosition(Direction);
}

void LevelCustom::ResetPath()
{
	CurrentIndexWaypoint = 0;
	WayPoints.clear();
	UpdateDrawDebugLines();
}

void LevelCustom::UpdateDrawDebugLines()
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
