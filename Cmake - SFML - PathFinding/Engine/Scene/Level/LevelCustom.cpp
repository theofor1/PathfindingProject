#include "LevelCustom.h"
#include <Actor/PlayerShip/PlayerShip.h>
#include <System/Input/InputManager.h>
#include <Engine/Render/Window.h>
#include <GameObject/Graph/Graph.h>
#include <GameObject/Graph/Cell/Cell.h>
#include <Math/Vector/Vector.h>


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

		xml_document<> doc;
		produceXMLDocForSave(doc);
		std::ofstream file("Ressources/Saves/CustomLevelSave.xml");
		if (!file) {
			std::cout << "Could not save level : xml file missing.\n";
			return;
		}
		file << doc;
		file.close();
		std::cout << "Level Saved!\n";
		doc.clear();
		return;

	}

	if (btnLoadLevel->Clicked(WorldMouseLocation)) {
		xml_document<> doc;
		std::ifstream file("Ressources/Saves/CustomLevelSave.xml");
		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);

		loadLevelFromXMLFile(doc);

		doc.clear();
		return;
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

void LevelCustom::produceXMLDocForSave(xml_document<>& Doc)
{

	//root of xml doc
	xml_node<>* decl = Doc.allocate_node(node_declaration);
	decl->append_attribute(Doc.allocate_attribute("version", "1.0"));
	decl->append_attribute(Doc.allocate_attribute("encoding", "utf-8"));
	Doc.append_node(decl);

	xml_node<>* root = Doc.allocate_node(node_element, "CustomLevel");
	Doc.append_node(root);

	//player position
	xml_node<>* playerNode = Doc.allocate_node(node_element, "Player");
	root->append_node(playerNode);
	sf::Vector2i playerPos = graph->GetCellCoordinateByPosition(ship->GetPosition());

	xml_attribute<>* playerXAttr = Doc.allocate_attribute("X", Doc.allocate_string(std::to_string(playerPos.x).c_str()));
	playerNode->append_attribute(playerXAttr);

	xml_attribute<>* playerYAttr = Doc.allocate_attribute("Y", Doc.allocate_string(std::to_string(playerPos.y).c_str()));
	playerNode->append_attribute(playerYAttr);

	//graph size
	xml_node<>* graphNode = Doc.allocate_node(node_element, "Graph");
	root->append_node(graphNode);

	int height = graph->GetNbCell().x;
	int width = graph->GetNbCell().y;

	xml_attribute<>* heightAttr = Doc.allocate_attribute("Height", Doc.allocate_string(std::to_string(height).c_str()));
	graphNode->append_attribute(heightAttr);

	xml_attribute<>* widthAttr = Doc.allocate_attribute("Width", Doc.allocate_string(std::to_string(width).c_str()));
	graphNode->append_attribute(widthAttr);


	//graph walls
	for (int x = 0; x < height; ++x) {
		for (int y = 0; y < width; ++y) {
			Cell* curCell = graph->Cells[x][y];
			if (!curCell->GetIsAlive()) {
				xml_node<>* thisCell = Doc.allocate_node(node_element, "NotAliveCell");
				graphNode->append_node(thisCell);

				xml_attribute<>* xAttr = Doc.allocate_attribute("X", Doc.allocate_string(std::to_string(x).c_str()));
				thisCell->append_attribute(xAttr);

				xml_attribute<>* yAttr = Doc.allocate_attribute("Y", Doc.allocate_string(std::to_string(y).c_str()));
				thisCell->append_attribute(yAttr);
			}
		}
	}

}

void LevelCustom::loadLevelFromXMLFile(rapidxml::xml_document<>& Doc)
{
	xml_node<>* root = Doc.first_node("CustomLevel");
	if (!root) {
		std::cout << "XML file badly parsed : cannot load level.\n";
		return;
	}

	
	xml_node<>* graphNode = root->first_node("Graph");
	xml_attribute<>* graphAttr = graphNode->first_attribute("Height");
	std::cout << graphAttr->value() << std::endl;
	
	std::string strGraphX(graphAttr->value());
	std::istringstream ssGraphX(strGraphX);
	int height;
	ssGraphX >> height;
	std::cout << height << std::endl;

	graphAttr = graphAttr->next_attribute("Width");
	std::string strGraphY(graphAttr->value());
	std::cout << graphAttr->value() << std::endl;
	std::istringstream ssGraphY(strGraphY);
	int width;
	ssGraphY >> width;
	std::cout << width << std::endl;

	graph->UpdateSize(sf::Vector2i(height, width));
	GraphHeightNbCells = height;
	GraphWidthNbCells = width;
	
	xml_node<>* playerNode = root->first_node("Player");
	xml_attribute<>* playerAttr = playerNode->first_attribute("X");
	std::string strPlayerX(playerAttr->value());
	std::istringstream ssPlayerX(strPlayerX);
	int playerPosX;
	ssPlayerX >> playerPosX;
	std::cout << playerPosX << std::endl;

	playerAttr = playerAttr->next_attribute("Y");
	std::string strPlayerY(playerAttr->value());
	std::istringstream ssPlayerY(strPlayerY);
	int playerPosY;
	ssPlayerY >> playerPosY;
	std::cout << playerPosY << std::endl;

	ship->SetPosition(graph->Cells[playerPosX][playerPosY%height]->GetPosition());

	graph->ResetCells();
	
	for (xml_node<>* cellNode = graphNode->first_node("NotAliveCell"); cellNode; cellNode = cellNode->next_sibling()) {
		xml_attribute<>* cellAttr = cellNode->first_attribute("X");
		std::string strCellX(cellAttr->value());
		std::istringstream ssCellX(strCellX);
		int cellX;
		ssCellX >> cellX;
		std::cout << cellX << std::endl;

		cellAttr = cellAttr->next_attribute("Y");
		std::string strCellY(cellAttr->value());
		std::istringstream ssCellY(strCellY);
		int cellY;
		ssCellY >> cellY;
		std::cout << cellY << std::endl;

		graph->Cells[cellX][cellY]->SetIsAlive(false);
	}

	graph->ReGenerateWaypoints();

	std::cout << "Level Loaded !\n";
}
