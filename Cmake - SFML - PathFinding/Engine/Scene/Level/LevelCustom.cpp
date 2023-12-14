#include "LevelCustom.h"
#include <Actor/PlayerShip/PlayerShip.h>
#include <System/Input/InputManager.h>
#include <Engine/Render/Window.h>
#include <GameObject/Graph/Graph.h>
#include <GameObject/Graph/Cell/Cell.h>
#include <Math/Vector/Vector.h>
#include <GameObject/Graph/PathFinder/WayPoint.h>

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

	CurrentIndexWaypoint = 0;
	Path.clear();
	DebugLines.clear();
	CurrentCellTypeTeleportation = nullptr;

	OnWallMode = false;
	OnPutWallMode = true;
	CurrentIndexWaypoint = 0;
	ColorOnSelected = sf::Color(255, 0, 0, 255);

	Mode = Mode::MOVE_PLAYER;

	xml_document<> doc;
	std::ifstream file("Ressources/Saves/CustomLevelSave.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	if (loadLevelFromXMLFile(doc))
	{
		// std::cout << "Last save loaded.\n";
	}
	else
		ship->SetPosition(graph->Cells[0][0]->GetPosition());

	doc.clear();

	InitButtons();

	// INPUT BINDING
	InputManager::Instance()->BindOnTriggered(InputAction::MouseL, [this]()
											  { OnGraphCellOnClick(); });

	InputManager::Instance()->BindOnDown(InputAction::MouseL, [this]()
										 { OnButtonsClick(); });
}

void LevelCustom::Update(float DeltaTime)
{
	IScene::Update(DeltaTime);

	sf::View viewport = Window::Instance()->GetView();
	sf::FloatRect windowRect(viewport.getCenter().x - viewport.getSize().x / 2, viewport.getCenter().y - viewport.getSize().y / 2, viewport.getSize().x, viewport.getSize().y);
	outerBox->UpdateRect(windowRect);
	outerBox->Update(DeltaTime);

	FollowPath(DeltaTime);
}

void LevelCustom::Destroy()
{
	delete outerBox;
	IScene::Destroy();
}

void LevelCustom::Draw(sf::RenderWindow &window) const
{
	IScene::Draw(window);
	outerBox->Draw(window);

	// Draw debug path finding
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

	// std::cout << graph->GetCellCoordinateByPosition(WorldMouseLocation).x << " " << graph->GetCellCoordinateByPosition(WorldMouseLocation).y << "\n";

	if (CurrentCellDest == CellDest)
		return;

	CurrentCellDest = CellDest;

	if (!CellStart || !CellDest || CellStart == CellDest)
		return;

	switch (Mode)
	{
	case Mode::MOVE_PLAYER:
		ResetPath();

		Path = graph->GetPath(CellStart, CellDest);
		if (CellStart->GetCellType() == CellType::TELEPORTATION && Path.size() > 0)
		{
			sf::Vector2f CurrentWayPoint = sf::Vector2f(Path[CurrentIndexWaypoint]->X, Path[CurrentIndexWaypoint]->Y);
			ship->SetPosition(CurrentWayPoint);
		}

		UpdateDrawDebugLines();
		return;
		break;
	case Mode::PUT_CELL_BLOCK:
		if (CellDest->GetCellType() == CellType::BLOCK)
			return;
		CellDest->SetCellType(CellType::BLOCK);
		break;
	case Mode::PUT_CELL_NORMAL:
		if (CellDest->GetCellType() == CellType::NORMAL)
			return;
		CellDest->SetCellType(CellType::NORMAL);
		break;
	case Mode::PUT_CELL_TELEPORTATION:
		if (CellDest->GetCellType() == CellType::TELEPORTATION)
			return;
		CellDest->SetCellType(CellType::TELEPORTATION);

		if (CurrentCellTypeTeleportation == CellDest)
			return;

		if (CurrentCellTypeTeleportation)
		{
			CurrentCellTypeTeleportation->SetOtherCellTypeTeleportation(CellDest);
			CurrentCellTypeTeleportation = nullptr;
		}
		else
		{
			CurrentCellTypeTeleportation = CellDest;
		}
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
		CancelPuttingCurrentCellTeleportation();

		Mode = Mode::MOVE_PLAYER;
		btnPlayerMoveMode->RenderRectangle.setFillColor(ColorOnSelected);
		btnPutCellTypeBlock->RenderRectangle.setFillColor(sf::Color::White);
		btnPutCellTypeNormal->RenderRectangle.setFillColor(sf::Color::White);
		btnPutCellTypeTeleportation->RenderRectangle.setFillColor(sf::Color::White);
		return;
	}

	if (btnPutCellTypeBlock->Clicked(WorldMouseLocation))
	{
		Mode = Mode::PUT_CELL_BLOCK;
		btnPutCellTypeBlock->RenderRectangle.setFillColor(ColorOnSelected);
		btnPlayerMoveMode->RenderRectangle.setFillColor(sf::Color::White);
		btnPutCellTypeNormal->RenderRectangle.setFillColor(sf::Color::White);
		btnPutCellTypeTeleportation->RenderRectangle.setFillColor(sf::Color::White);
		ResetPath();
		UpdateDrawDebugLines();
		return;
	}

	if (btnPutCellTypeNormal->Clicked(WorldMouseLocation))
	{
		CancelPuttingCurrentCellTeleportation();

		Mode = Mode::PUT_CELL_NORMAL;
		btnPutCellTypeNormal->RenderRectangle.setFillColor(ColorOnSelected);
		btnPlayerMoveMode->RenderRectangle.setFillColor(sf::Color::White);
		btnPutCellTypeBlock->RenderRectangle.setFillColor(sf::Color::White);
		btnPutCellTypeTeleportation->RenderRectangle.setFillColor(sf::Color::White);
		ResetPath();
		UpdateDrawDebugLines();
		return;
	}

	if (btnPutCellTypeTeleportation->Clicked(WorldMouseLocation))
	{
		Mode = Mode::PUT_CELL_TELEPORTATION;
		btnPutCellTypeTeleportation->RenderRectangle.setFillColor(ColorOnSelected);
		btnPlayerMoveMode->RenderRectangle.setFillColor(sf::Color::White);
		btnPutCellTypeBlock->RenderRectangle.setFillColor(sf::Color::White);
		btnPutCellTypeNormal->RenderRectangle.setFillColor(sf::Color::White);
		ResetPath();
		UpdateDrawDebugLines();
		return;
	}

	if (btnRemoveGraphHeight->Clicked(WorldMouseLocation))
	{
		CancelPuttingCurrentCellTeleportation();

		sf::Vector2i playerPos = graph->GetCellCoordinateByPosition(ship->GetPosition());

		if (GraphHeightNbCells == 1 || playerPos.y == GraphHeightNbCells - 1)
			// Do not reduce graph is player is at max to avoid OOB
			return;
		GraphHeightNbCells--;
		graph->UpdateSize(sf::Vector2i(GraphHeightNbCells, GraphWidthNbCells));
		return;
	}

	if (btnAddGraphHeight->Clicked(WorldMouseLocation))
	{
		CancelPuttingCurrentCellTeleportation();

		// if (GraphHeightNbCells == 1)
		// return;
		GraphHeightNbCells++;
		graph->UpdateSize(sf::Vector2i(GraphHeightNbCells, GraphWidthNbCells));
		return;
	}

	if (btnRemoveGraphWidth->Clicked(WorldMouseLocation))
	{
		CancelPuttingCurrentCellTeleportation();

		sf::Vector2i playerPos = graph->GetCellCoordinateByPosition(ship->GetPosition());
		if (GraphWidthNbCells == 1 || playerPos.x == GraphWidthNbCells - 1)
			return;
		GraphWidthNbCells--;
		graph->UpdateSize(sf::Vector2i(GraphHeightNbCells, GraphWidthNbCells));
		return;
	}

	if (btnAddGraphWidth->Clicked(WorldMouseLocation))
	{
		CancelPuttingCurrentCellTeleportation();

		// if (GraphWidthNbCells == 14)
		// return;
		GraphWidthNbCells++;
		graph->UpdateSize(sf::Vector2i(GraphHeightNbCells, GraphWidthNbCells));
		return;
	}

	if (btnSaveLevel->Clicked(WorldMouseLocation))
	{
		CancelPuttingCurrentCellTeleportation();

		xml_document<> doc;
		produceXMLDocForSave(doc);
		std::ofstream file("Ressources/Saves/CustomLevelSave.xml");
		if (!file)
		{
			std::cout << "Could not save level : xml file missing.\n";
			return;
		}
		file << doc;
		file.close();
		// std::cout << "Level Saved!\n";
		doc.clear();
		return;
	}

	if (btnLoadLevel->Clicked(WorldMouseLocation))
	{
		CancelPuttingCurrentCellTeleportation();
		xml_document<> doc;
		std::ifstream file("Ressources/Saves/CustomLevelSave.xml");
		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);

		loadLevelFromXMLFile(doc);

		doc.clear();

		CurrentIndexWaypoint = 0;
		Path.clear();
		DebugLines.clear();

		return;
	}

	if (btnDownWindowSpeed->Clicked(WorldMouseLocation))
	{
		if (Window::Instance()->GetViewSpeedMove() > 0)
			Window::Instance()->SetViewSpeedMove(Window::Instance()->GetViewSpeedMove() - AmountSpeed);
		return;
	}

	if (btnUpWindowSpeed->Clicked(WorldMouseLocation))
	{
		Window::Instance()->SetViewSpeedMove(Window::Instance()->GetViewSpeedMove() + AmountSpeed);
		return;
	}

	if (btnUpPlayerSpeed->Clicked(WorldMouseLocation))
	{
		if (ship->GetSpeedMove() > 1000)
			return;
		ship->SetSpeedMove(ship->GetSpeedMove() + AmountSpeed);
		return;
	}

	if (btnDownPlayerSpeed->Clicked(WorldMouseLocation))
	{
		ship->SetSpeedMove(ship->GetSpeedMove() - AmountSpeed);
		return;
	}
}

void LevelCustom::FollowPath(float DeltaTime)
{
	if (Path.size() == 0)
		return;

	UpdateDrawDebugLines();

	sf::Vector2f CurrentWayPoint = sf::Vector2f(Path[CurrentIndexWaypoint]->X, Path[CurrentIndexWaypoint]->Y);

	float CurrentDist = Vector::GetDistance(CurrentWayPoint, ship->GetPosition());

	if (CurrentDist < 5)
	{
		if (CurrentIndexWaypoint < Path.size() - 1 && Path[CurrentIndexWaypoint]->IsNoCostWayPoint(Path[CurrentIndexWaypoint + 1]))
		{
			sf::Vector2f NextWayPoint = sf::Vector2f(Path[CurrentIndexWaypoint + 1]->X, Path[CurrentIndexWaypoint + 1]->Y);
			ship->SetPosition(NextWayPoint);
		}
		else
		{
			ship->SetPosition(CurrentWayPoint);
		}
		CurrentIndexWaypoint++;
		if (CurrentIndexWaypoint >= Path.size())
			ResetPath();
	}
	else
	{

		MoveTo(DeltaTime, CurrentWayPoint);

		float NewDist = Vector::GetDistance(CurrentWayPoint, ship->GetPosition());

		if (NewDist > CurrentDist)
			ship->SetPosition(CurrentWayPoint);
	}
}

void LevelCustom::MoveTo(float DeltaTime, const sf::Vector2f TargetPosition)
{
	sf::Vector2f Direction = Vector::GetDirection(ship->GetPosition(), TargetPosition);
	Direction *= DeltaTime * ship->GetSpeedMove();
	ship->AddWorldPosition(Direction);
}

void LevelCustom::ResetPath()
{
	CurrentIndexWaypoint = 0;
	Path.clear();
	UpdateDrawDebugLines();
}

void LevelCustom::UpdateDrawDebugLines()
{
	DebugLines.clear();

	if (Path.size() == 0)
		return;

	DebugLines.push_back(Line(ship->GetPosition(), sf::Vector2f(Path[CurrentIndexWaypoint]->X, Path[CurrentIndexWaypoint]->Y)));

	for (int i = CurrentIndexWaypoint; i <= Path.size(); i++)
	{
		if (i + 1 >= Path.size())
			return;

		sf::Vector2f StartLocation = sf::Vector2f(Path[i]->X, Path[i]->Y);
		sf::Vector2f EndLocation = sf::Vector2f(Path[i + 1]->X, Path[i + 1]->Y);

		DebugLines.push_back(Line(StartLocation, EndLocation));
	}
}

void LevelCustom::InitButtons()
{
	outerBox = new UIElement(sf::Vector2f(0.8f, 0.f), sf::Vector2f(0.2f, 0.4f));
	outerBox->SetLayout(UILayout::List, UIDirection::Vertical);

	btnPlayerMoveMode = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.1f));
	btnPlayerMoveMode->RenderRectangle.setFillColor(sf::Color(239, 239, 240));
	btnPlayerMoveMode->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	btnPlayerMoveMode->TextButton.setString("Place Move Mode");
	outerBox->AddChild(btnPlayerMoveMode);

	btnPutCellTypeNormal = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.1f));
	btnPutCellTypeNormal->RenderRectangle.setFillColor(sf::Color::White);
	btnPutCellTypeNormal->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	btnPutCellTypeNormal->TextButton.setString("Put Cell Type To Normal");
	outerBox->AddChild(btnPutCellTypeNormal);

	btnPutCellTypeBlock = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.1f));
	btnPutCellTypeBlock->RenderRectangle.setFillColor(sf::Color::White);
	btnPutCellTypeBlock->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	btnPutCellTypeBlock->TextButton.setString("Put Cell Type To Block");
	outerBox->AddChild(btnPutCellTypeBlock);

	btnPutCellTypeTeleportation = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.1f));
	btnPutCellTypeTeleportation->RenderRectangle.setFillColor(sf::Color::White);
	btnPutCellTypeTeleportation->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	btnPutCellTypeTeleportation->TextButton.setString("Put Cell Type To Teleportation");
	outerBox->AddChild(btnPutCellTypeTeleportation);

	windowSpeedBox = new UIElement(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.1f));
	windowSpeedBox->SetLayout(UILayout::List, UIDirection::Horizontal);
	outerBox->AddChild(windowSpeedBox);

	btnDownWindowSpeed = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.5f, 1.f));
	btnDownWindowSpeed->RenderRectangle.setFillColor(sf::Color::White);
	btnDownWindowSpeed->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	btnDownWindowSpeed->TextButton.setString("- Speed Viewport");
	windowSpeedBox->AddChild(btnDownWindowSpeed);

	btnUpWindowSpeed = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.5f, 1.f));
	btnUpWindowSpeed->RenderRectangle.setFillColor(sf::Color::White);
	btnUpWindowSpeed->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	btnUpWindowSpeed->TextButton.setString("+ Speed Viewport");
	windowSpeedBox->AddChild(btnUpWindowSpeed);

	playerSpeedBox = new UIElement(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.1f));
	playerSpeedBox->SetLayout(UILayout::List, UIDirection::Horizontal);
	outerBox->AddChild(playerSpeedBox);

	btnDownPlayerSpeed = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.5f, 1.f));
	btnDownPlayerSpeed->RenderRectangle.setFillColor(sf::Color::White);
	btnDownPlayerSpeed->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	btnDownPlayerSpeed->TextButton.setString("- Speed Player");
	playerSpeedBox->AddChild(btnDownPlayerSpeed);

	btnUpPlayerSpeed = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.5f, 1.f));
	btnUpPlayerSpeed->RenderRectangle.setFillColor(sf::Color::White);
	btnUpPlayerSpeed->RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	btnUpPlayerSpeed->TextButton.setString("+ Speed Player");
	playerSpeedBox->AddChild(btnUpPlayerSpeed);

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
}

void LevelCustom::CancelPuttingCurrentCellTeleportation()
{
	if (CurrentCellTypeTeleportation)
	{
		CurrentCellTypeTeleportation->SetCellType(CellType::NORMAL);
		CurrentCellTypeTeleportation = nullptr;
	}
}

void LevelCustom::produceXMLDocForSave(xml_document<> &Doc)
{

	// root of xml doc
	xml_node<> *decl = Doc.allocate_node(node_declaration);
	decl->append_attribute(Doc.allocate_attribute("version", "1.0"));
	decl->append_attribute(Doc.allocate_attribute("encoding", "utf-8"));
	Doc.append_node(decl);

	xml_node<> *root = Doc.allocate_node(node_element, "CustomLevel");
	Doc.append_node(root);

	// player position
	xml_node<> *playerNode = Doc.allocate_node(node_element, "Player");
	root->append_node(playerNode);
	sf::Vector2i playerPos = graph->GetCellCoordinateByPosition(ship->GetPosition());

	xml_attribute<> *playerXAttr = Doc.allocate_attribute("X", Doc.allocate_string(std::to_string(playerPos.x).c_str()));
	playerNode->append_attribute(playerXAttr);

	xml_attribute<> *playerYAttr = Doc.allocate_attribute("Y", Doc.allocate_string(std::to_string(playerPos.y).c_str()));
	playerNode->append_attribute(playerYAttr);

	// graph size
	xml_node<> *graphNode = Doc.allocate_node(node_element, "Graph");
	root->append_node(graphNode);

	int height = graph->GetNbCell().x;
	int width = graph->GetNbCell().y;

	xml_attribute<> *heightAttr = Doc.allocate_attribute("Height", Doc.allocate_string(std::to_string(height).c_str()));
	graphNode->append_attribute(heightAttr);

	xml_attribute<> *widthAttr = Doc.allocate_attribute("Width", Doc.allocate_string(std::to_string(width).c_str()));
	graphNode->append_attribute(widthAttr);

	// graph walls
	for (int x = 0; x < height; ++x)
	{
		for (int y = 0; y < width; ++y)
		{
			Cell *curCell = graph->Cells[x][y];

			if (curCell->GetCellType() == CellType::BLOCK)
			{
				xml_node<> *thisCell = Doc.allocate_node(node_element, "NotAliveCell");
				graphNode->append_node(thisCell);

				xml_attribute<> *xAttr = Doc.allocate_attribute("X", Doc.allocate_string(std::to_string(x).c_str()));
				thisCell->append_attribute(xAttr);

				xml_attribute<> *yAttr = Doc.allocate_attribute("Y", Doc.allocate_string(std::to_string(y).c_str()));
				thisCell->append_attribute(yAttr);
			}
			if (curCell->GetCellType() == CellType::TELEPORTATION)
			{
				Cell *LinkedCell = curCell->OtherCellTypeTeleportation;
				if (!LinkedCell)
					continue;

				sf::Vector2i LinkedCellCoordinate = graph->GetCellCoordinate(LinkedCell);

				xml_node<> *thisCell = Doc.allocate_node(node_element, "CellTeleportation");
				graphNode->append_node(thisCell);

				xml_attribute<> *xAttr = Doc.allocate_attribute("X", Doc.allocate_string(std::to_string(x).c_str()));
				thisCell->append_attribute(xAttr);

				xml_attribute<> *yAttr = Doc.allocate_attribute("Y", Doc.allocate_string(std::to_string(y).c_str()));
				thisCell->append_attribute(yAttr);

				xml_attribute<> *LinkedCellXAttr = Doc.allocate_attribute("LinkedCellX", Doc.allocate_string(std::to_string(LinkedCellCoordinate.x).c_str()));
				thisCell->append_attribute(LinkedCellXAttr);

				xml_attribute<> *LinkedCellYAttr = Doc.allocate_attribute("LinkedCellY", Doc.allocate_string(std::to_string(LinkedCellCoordinate.y).c_str()));
				thisCell->append_attribute(LinkedCellYAttr);
			}
		}
	}
}

bool LevelCustom::loadLevelFromXMLFile(rapidxml::xml_document<> &Doc)
{
	xml_node<> *root = Doc.first_node("CustomLevel");
	if (!root)
	{
		std::cout << "XML file badly parsed : cannot load level.\n";
		return false;
	}

	xml_node<> *graphNode = root->first_node("Graph");
	xml_attribute<> *graphAttr = graphNode->first_attribute("Height");

	std::string strGraphX(graphAttr->value());
	std::istringstream ssGraphX(strGraphX);
	int height;
	ssGraphX >> height;

	graphAttr = graphAttr->next_attribute("Width");
	std::string strGraphY(graphAttr->value());
	std::istringstream ssGraphY(strGraphY);
	int width;
	ssGraphY >> width;

	graph->UpdateSize(sf::Vector2i(height, width));
	GraphHeightNbCells = height;
	GraphWidthNbCells = width;

	graph->ResetCells();

	for (xml_node<> *cellNode = graphNode->first_node("NotAliveCell"); cellNode; cellNode = cellNode->next_sibling("NotAliveCell"))
	{
		xml_attribute<> *cellAttr = cellNode->first_attribute("X");
		std::string strCellX(cellAttr->value());
		std::istringstream ssCellX(strCellX);
		int cellX;
		ssCellX >> cellX;

		cellAttr = cellAttr->next_attribute("Y");
		std::string strCellY(cellAttr->value());
		std::istringstream ssCellY(strCellY);
		int cellY;
		ssCellY >> cellY;

		graph->Cells[cellX][cellY]->SetCellType(CellType::BLOCK);
	}

	for (xml_node<> *cellNode = graphNode->first_node("CellTeleportation"); cellNode; cellNode = cellNode->next_sibling("CellTeleportation"))
	{
		xml_attribute<> *cellAttr = cellNode->first_attribute("X");
		std::string strCellX(cellAttr->value());
		std::istringstream ssCellX(strCellX);
		int cellX;
		ssCellX >> cellX;

		cellAttr = cellAttr->next_attribute("Y");
		std::string strCellY(cellAttr->value());
		std::istringstream ssCellY(strCellY);
		int cellY;
		ssCellY >> cellY;

		cellAttr = cellAttr->next_attribute("LinkedCellX");
		std::string strLinkedCellX(cellAttr->value());
		std::istringstream ssLinkedCellX(strLinkedCellX);
		int LinkedCellX;
		ssLinkedCellX >> LinkedCellX;

		cellAttr = cellAttr->next_attribute("LinkedCellY");
		std::string strLinkedCellY(cellAttr->value());
		std::istringstream ssLinkedCellY(strLinkedCellY);
		int LinkedCellY;
		ssLinkedCellY >> LinkedCellY;

		graph->Cells[cellX][cellY]->SetCellType(CellType::TELEPORTATION);

		Cell *LinkedCell = graph->Cells[LinkedCellX][LinkedCellY];

		if (!LinkedCell)
			continue;

		graph->Cells[cellX][cellY]->SetOtherCellTypeTeleportation(LinkedCell);
	}

	graph->ReGenerateWaypoints();

	xml_node<> *playerNode = root->first_node("Player");
	xml_attribute<> *playerAttr = playerNode->first_attribute("X");
	std::string strPlayerX(playerAttr->value());
	std::istringstream ssPlayerX(strPlayerX);
	int playerPosX;
	ssPlayerX >> playerPosX;

	playerAttr = playerAttr->next_attribute("Y");
	std::string strPlayerY(playerAttr->value());
	std::istringstream ssPlayerY(strPlayerY);
	int playerPosY;
	ssPlayerY >> playerPosY;

	if (playerPosX <= graph->GetNbCell().y - 1 && playerPosY <= graph->GetNbCell().x - 1)
		ship->SetPosition(graph->Cells[playerPosY][playerPosX]->GetPosition());
	else
		ship->SetPosition(graph->Cells[0][0]->GetPosition());

	// std::cout << "Level Loaded !\n";
	return true;
}
