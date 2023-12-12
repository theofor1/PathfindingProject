#include "LevelCustom.h"
#include <Actor/PlayerShip/PlayerShip.h>
#include <System/Input/InputManager.h>
#include <Engine/Render/Window.h>
#include <GameObject/Graph/Graph.h>
#include <GameObject/Graph/Cell/Cell.h>
#include <Math/Vector/Vector.h>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include<rapidxml/rapidxml_print.hpp>

#include <iostream>
#include <string>
#include <sstream>

using namespace rapidxml;

LevelCustom::LevelCustom()
{
	graph = new Graph("", sf::Vector2i(10, 10));
	GraphHeightNbCells = 10;
	GraphWidthNbCells = 10;

	ship = new PlayerShip();

	AddGameObject(graph);
	AddGameObject(ship);
}

void LevelCustom::Start()
{
	IScene::Start();

	OnWallMode = false;
	OnPutWallMode = true;
	CurrentIndexWaypoint = 0;
	ColorOnSelected = sf::Color(255, 0, 0, 255);


	Mode = Mode::MOVE_PLAYER;

	// ship->SetPosition(graph->Cells[5][3]->GetPosition());
	ship->SetPosition(graph->Cells[0][0]->GetPosition());

	outerBox = new UIElement(sf::Vector2f(0.5f, 0.f), sf::Vector2f(0.1f, 0.3f));
	outerBox->SetLayout(UILayout::List, UIDirection::Vertical);

	btnPlayerMoveMode = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.1f));
	btnPlayerMoveMode->RenderRectangle.setFillColor(sf::Color(239, 239, 240));
	btnPlayerMoveMode->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	btnPlayerMoveMode->TextButton.setString("Place Move Mode");
	outerBox->AddChild(btnPlayerMoveMode);

	btnPutWallMode = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.1f));
	btnPutWallMode->RenderRectangle.setFillColor(sf::Color::White);
	btnPutWallMode->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	btnPutWallMode->TextButton.setString("Place Wall Mode");
	outerBox->AddChild(btnPutWallMode);

	btnRemoveWallMode = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.1f));
	btnRemoveWallMode->RenderRectangle.setFillColor(sf::Color::White);
	btnRemoveWallMode->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	btnRemoveWallMode->TextButton.setString("Remove Wall Mode");
	outerBox->AddChild(btnRemoveWallMode);

	graphHeightBox = new UIElement(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.1f));
	graphHeightBox->SetLayout(UILayout::List, UIDirection::Horizontal);
	outerBox->AddChild(graphHeightBox);

	btnRemoveGraphHeight = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.5f, 1.f));
	btnRemoveGraphHeight->RenderRectangle.setFillColor(sf::Color::White);
	btnRemoveGraphHeight->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	btnRemoveGraphHeight->TextButton.setString("- Height");
	graphHeightBox->AddChild(btnRemoveGraphHeight);

	btnAddGraphHeight = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.5f, 1.f));
	btnAddGraphHeight->RenderRectangle.setFillColor(sf::Color::White);
	btnAddGraphHeight->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	btnAddGraphHeight->TextButton.setString("+ Height");
	graphHeightBox->AddChild(btnAddGraphHeight);

	graphWidthBox = new UIElement(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.1f));
	graphWidthBox->SetLayout(UILayout::List, UIDirection::Horizontal);
	outerBox->AddChild(graphWidthBox);

	btnRemoveGraphWidth = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.5f, 1.f));
	btnRemoveGraphWidth->RenderRectangle.setFillColor(sf::Color::White);
	btnRemoveGraphWidth->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	btnRemoveGraphWidth->TextButton.setString("- Width");
	graphWidthBox->AddChild(btnRemoveGraphWidth);

	btnAddGraphWidth = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.5f, 1.f));
	btnAddGraphWidth->RenderRectangle.setFillColor(sf::Color::White);
	btnAddGraphWidth->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	btnAddGraphWidth->TextButton.setString("+ Width");
	graphWidthBox->AddChild(btnAddGraphWidth);

	btnSaveLevel = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.1f));
	btnSaveLevel->RenderRectangle.setFillColor(sf::Color::White);
	btnSaveLevel->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	btnSaveLevel->TextButton.setString("Save Level");
	outerBox->AddChild(btnSaveLevel);

	btnLoadLevel = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.1f));
	btnLoadLevel->RenderRectangle.setFillColor(sf::Color::White);
	btnLoadLevel->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	btnLoadLevel->TextButton.setString("Load Level");
	outerBox->AddChild(btnLoadLevel);

	outerBox->Start();

	// INPUT BINDING
	InputManager::Instance()->BindOnTriggered(InputAction::MouseL, [this]()
											  { OnGraphCellOnClick(); });

	InputManager::Instance()->BindOnDown(InputAction::MouseL, [this]()
										 { OnButtonsClick(); });

	// InputManager::Instance()->BindOnTriggered(InputAction::MouseL, [this]()
	// 										  { EventOnClick(); });
}

void LevelCustom::Update(float DeltaTime)
{
	TimeSinceLastInput += DeltaTime;
	IScene::Update(DeltaTime);
	outerBox->Update(DeltaTime);
	FollowWayPoints(DeltaTime);
}

void LevelCustom::Destroy()
{
	delete outerBox;
	IScene::Destroy();
}

void LevelCustom::Draw(sf::RenderWindow &window) const
{
	IScene::Draw(window);
	sf::Vector2u windowSize = window.getSize();
	sf::FloatRect windowRect(0, 0, windowSize.x, windowSize.y);
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

	Cell *CellDest = graph->GetCellByPosition(WorldMouseLocation);
	Cell *CellStart = graph->GetCellByPosition(ship->GetPosition());

	if (CurrentCellDest == CellDest)
		return;

	CurrentCellDest = CellDest;

	if (!CellStart || !CellDest || CellStart == CellDest)
		return;

	switch (Mode)
	{
	case Mode::MOVE_PLAYER:
		ResetPath();
		WayPoints = graph->GetPath(CellStart, CellDest);
		UpdateDrawDebugLines();
		break;
	case Mode::PUT_WALL:
		if (!CellDest->GetIsAlive())
			return;
		CellDest->SetIsAlive(false);
		break;
	case Mode::REMOVE_WALL:
		if (CellDest->GetIsAlive())
			return;
		CellDest->SetIsAlive(true);
		break;
	default:
		return;
	}

	graph->ReGenerateWaypoints();
}

void LevelCustom::OnButtonsClick()
{
	sf::Vector2i MouseLocation = sf::Mouse::getPosition(Window::Instance()->GetWindow());
	sf::Vector2f WorldMouseLocation = Window::Instance()->GetWindow().mapPixelToCoords(MouseLocation);

	if (btnPlayerMoveMode->Clicked(WorldMouseLocation))
	{
		Mode = Mode::MOVE_PLAYER;
		btnPlayerMoveMode->RenderRectangle.setFillColor(ColorOnSelected);
		btnPutWallMode->RenderRectangle.setFillColor(sf::Color::White);
		btnRemoveWallMode->RenderRectangle.setFillColor(sf::Color::White);
		return;
	}

	if (btnPutWallMode->Clicked(WorldMouseLocation))
	{
		Mode = Mode::PUT_WALL;
		btnPutWallMode->RenderRectangle.setFillColor(ColorOnSelected);
		btnPlayerMoveMode->RenderRectangle.setFillColor(sf::Color::White);
		btnRemoveWallMode->RenderRectangle.setFillColor(sf::Color::White);
		ResetPath();
		UpdateDrawDebugLines();
		return;
	}

	if (btnRemoveWallMode->Clicked(WorldMouseLocation))
	{
		Mode = Mode::REMOVE_WALL;
		btnRemoveWallMode->RenderRectangle.setFillColor(ColorOnSelected);
		btnPlayerMoveMode->RenderRectangle.setFillColor(sf::Color::White);
		btnPutWallMode->RenderRectangle.setFillColor(sf::Color::White);
		ResetPath();
		UpdateDrawDebugLines();
		return;
	}

	if (btnRemoveGraphHeight->Clicked(WorldMouseLocation))
	{
		if (GraphHeightNbCells == 4)
			return;
		GraphHeightNbCells--;
		graph->UpdateSize(sf::Vector2i(GraphHeightNbCells, GraphWidthNbCells));
		return;
	}

	if (btnAddGraphHeight->Clicked(WorldMouseLocation))
	{
		if (GraphHeightNbCells == 14)
			return;
		GraphHeightNbCells++;
		graph->UpdateSize(sf::Vector2i(GraphHeightNbCells, GraphWidthNbCells));
		return;
	}

	if (btnRemoveGraphWidth->Clicked(WorldMouseLocation))
	{
		if (GraphWidthNbCells == 4)
			return;
		GraphWidthNbCells--;
		graph->UpdateSize(sf::Vector2i(GraphHeightNbCells, GraphWidthNbCells));
		return;
	}

	if (btnAddGraphWidth->Clicked(WorldMouseLocation))
	{
		if (GraphWidthNbCells == 14)
			return;
		GraphWidthNbCells++;
		graph->UpdateSize(sf::Vector2i(GraphHeightNbCells, GraphWidthNbCells));
		return;
	}

	if (btnSaveLevel->Clicked(WorldMouseLocation)) {
		char buffer[5+sizeof(char)];

		xml_document<> doc;

		xml_node<>* decl = doc.allocate_node(node_declaration);
		decl->append_attribute(doc.allocate_attribute("version", "1.0"));
		decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
		doc.append_node(decl);

		xml_node<>* root = doc.allocate_node(node_element, "CustomLevel");
		doc.append_node(root);

		xml_node<>* playerNode = doc.allocate_node(node_element, "Player");
		root->append_node(playerNode);
		sf::Vector2i playerPos = graph->GetCellCoordinateByPosition(ship->GetPosition());

		sprintf(buffer, "%i", playerPos.x);
		xml_attribute<>* playerXAttr = doc.allocate_attribute("X", buffer);
		playerNode->append_attribute(playerXAttr);

		sprintf(buffer, "%i", playerPos.y);
		xml_attribute<>* playerYAttr = doc.allocate_attribute("Y", buffer);
		playerNode->append_attribute(playerYAttr);

		xml_node<> *graphNode = doc.allocate_node(node_element, "Graph");
		root->append_node(graphNode);

		int height = graph->GetNbCell().x;
		int width = graph->GetNbCell().y;

		//itoa(height, buffer, 10);
		sprintf(buffer, "%i", height);
		
		xml_attribute<>* heightAttr = doc.allocate_attribute("Height",buffer);
		graphNode->append_attribute(heightAttr);

		//itoa(width, buffer, 10);
		sprintf(buffer, "%i", width);
		xml_attribute<>* widthAttr = doc.allocate_attribute("Width",buffer);
		graphNode->append_attribute(widthAttr);

		for (int x = 0; x < height; ++x) {
			for (int y = 0; y < width; ++y) {
				Cell* curCell = graph->Cells[x][y];
				if (!curCell->GetIsAlive()) {
					xml_node<>* thisCell = doc.allocate_node(node_element, "NotAliveCell");
					graphNode->append_node(thisCell);

					itoa(x, buffer, 10);
					xml_attribute<>* xAttr = doc.allocate_attribute("X", buffer);
					thisCell->append_attribute(xAttr);

					itoa(y, buffer, 10);
					xml_attribute<>* yAttr = doc.allocate_attribute("Y", buffer);
					thisCell->append_attribute(yAttr);
				}
			}
		}

		std::ofstream file("Ressources/Saves/CustomLevelSave.xml");
		file << doc;
		file.close();
		doc.clear();
		return;

	}

	if (btnLoadLevel->Clicked(WorldMouseLocation)) {

	}
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
