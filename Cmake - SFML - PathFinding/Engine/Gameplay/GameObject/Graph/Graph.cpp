#include "Graph.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Cell/Cell.h"
#include "./PathFinder/WayPoint.h"
#include "./PathFinder/Dijkstra.h"

#include <iostream>

Graph::Graph(std::string Name, const sf::Vector2i _NbCell, const int _CellSideSize) : GameObject(Name),
																					  CellSideSize(_CellSideSize),
																					  NbCell(_NbCell)
{
	// Init Cells
	sf::Vector2f CurrentPosition(0, 0);
	for (size_t x = 0; x < NbCell.x; x++)
	{
		for (size_t y = 0; y < NbCell.y; y++)
		{
			Cell *NewCell = new Cell("a cell", CurrentPosition, CellSideSize);
			Cells[x][y] = NewCell;
			CurrentPosition += sf::Vector2f(CellSideSize, 0);
		}
		CurrentPosition = sf::Vector2f(0, CurrentPosition.y + CellSideSize);
	}

	Cells[1][1]->SetIsAlive(false);
	Cells[1][2]->SetIsAlive(false);
	Cells[1][3]->SetIsAlive(false);

	WayPoints = GenerateWayPoints();
	LinkWayPointsToNeighbor();
}

Graph::~Graph()
{
}

void Graph::Start()
{
	GameObject::Start();
}

void Graph::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}

void Graph::Destroy()
{
	GameObject::Destroy();

	for (const auto &row : Cells)
	{
		for (const auto &cellPair : row.second)
		{
			Cell *Cell = cellPair.second;
			delete Cell;
		}
	}
}

void Graph::Draw(sf::RenderWindow &window) const
{
	GameObject::Draw(window);
	for (const auto &row : Cells)
	{
		for (const auto &cellPair : row.second)
		{
			Cell *Cell = cellPair.second;
			window.draw(Cell->GetRectangleShape());
		}
	}
}

Cell *Graph::GetCellByPosition(sf::Vector2f Position)
{
	for (const auto &row : Cells)
	{
		for (const auto &cellPair : row.second)
		{
			Cell *Cell = cellPair.second;
			if (!Cell->GetIsAlive())
				continue;
			if (Cell->GetRect().contains(Position))
			{
				return Cell;
			}
		}
	}
	return nullptr;
}

std::vector<sf::Vector2f> Graph::GetPath(Cell *CellStart, Cell *CellEnd)
{
	std::vector<sf::Vector2f> Path;

	if (!CellStart || !CellEnd)
		return Path;

	// Get Start and Tartget Wp
	WayPoint *StartWp = GetWayPointByCell(CellStart);
	WayPoint *EndWp = GetWayPointByCell(CellEnd);

	if (!StartWp || !EndWp)
		return Path;

	std::vector<WayPoint *> Wps;

	for (size_t x = 0; x < NbCell.x; x++)
	{
		for (size_t y = 0; y < NbCell.y; y++)
		{
			Cell *Cell = Cells[x][y];
			if (!Cell->GetIsAlive())
				continue;
			WayPoint *Wp = WayPoints[x][y];
			Wps.push_back(Wp);
		}
	}

	std::vector<WayPoint *> WpPath = Dijkstra::GetPathFinding(Wps, StartWp, EndWp);

	for (const WayPoint *Wp : WpPath)
		Path.push_back(sf::Vector2f(Wp->X, Wp->Y));

	return Path;
}

//////////////////////////////////////////////////
// PROTECTED

Cell *Graph::GetCell(int x, int y)
{
	auto itOuter = Cells.find(x);

	// Vérifier si la clé x existe
	if (itOuter != Cells.end())
	{
		// La clé x existe, vérifier maintenant la clé y dans la map interne
		auto itInner = itOuter->second.find(y);

		// Vérifier si la clé y existe dans la map interne
		if (itInner != itOuter->second.end())
		{
			// La clé y existe dans la map interne, renvoyer le pointeur vers la cellule
			return itInner->second;
		}
	}

	// Soit la clé x n'existe pas, soit la clé y n'existe pas dans la map interne
	return nullptr;
}

WayPoint *Graph::GetWayPoint(int x, int y)
{
	auto itOuter = WayPoints.find(x);

	// Vérifier si la clé x existe
	if (itOuter != WayPoints.end())
	{
		// La clé x existe, vérifier maintenant la clé y dans la map interne
		auto itInner = itOuter->second.find(y);

		// Vérifier si la clé y existe dans la map interne
		if (itInner != itOuter->second.end())
		{
			// La clé y existe dans la map interne, renvoyer le pointeur vers la cellule
			return itInner->second;
		}
	}

	// Soit la clé x n'existe pas, soit la clé y n'existe pas dans la map interne
	return nullptr;
}

std::map<int, std::map<int, WayPoint *>> Graph::GenerateWayPoints()
{
	std::map<int, std::map<int, WayPoint *>> WayPoints;

	for (size_t x = 0; x < NbCell.x; x++)
	{
		for (size_t y = 0; y < NbCell.y; y++)
		{
			Cell *Cell = Cells[x][y];
			if (!Cell->GetIsAlive())
				continue;
			WayPoint *Wp = new WayPoint(Cell->GetPosition().x, Cell->GetPosition().y);
			WayPoints[x][y] = Wp;
		}
	}

	return WayPoints;
}

void Graph::LinkWayPointsToNeighbor()
{
	for (size_t x = 0; x < NbCell.x; x++)
	{
		for (size_t y = 0; y < NbCell.y; y++)
		{
			WayPoint *CurrentWp = WayPoints[x][y];

			// Link to waypoint arround current wp
			std::vector<WayPoint *> ArroundWps = GetWayPointArroundWayPoint(x, y);
			for (WayPoint *Wp : ArroundWps)
				if (Wp)
					CurrentWp->LinkWayPoint(Wp);
		}
	}
}

std::vector<WayPoint *> Graph::GetWayPointArroundWayPoint(const int x, const int y)
{
	std::vector<WayPoint *> Wps;

	WayPoint *Wp = GetWayPoint(x, y);

	if (!Wp)
		return Wps;

	WayPoint *WpUp = GetWayPoint(x, y - 1);
	WayPoint *WpDown = GetWayPoint(x, y + 1);
	WayPoint *WpLeft = GetWayPoint(x + 1, y);
	WayPoint *WpRight = GetWayPoint(x - 1, y);
	WayPoint *WpDownLeft = GetWayPoint(x, y + 1);
	WayPoint *WpDownRight = GetWayPoint(x, y + 1);
	WayPoint *WpUpLeft = GetWayPoint(x + 1, y - 1);
	WayPoint *WpUpRight = GetWayPoint(x - 1, y - 1);

	Wps.push_back(WpUp);
	Wps.push_back(WpLeft);
	Wps.push_back(WpRight);
	Wps.push_back(WpDownLeft);
	Wps.push_back(WpDownRight);
	Wps.push_back(WpUpLeft);
	Wps.push_back(WpUpRight);

	return Wps;
}

WayPoint *Graph::GetWayPointByCell(Cell *CellToGetWp)
{
	if (!CellToGetWp)
		return nullptr;

	for (size_t x = 0; x < NbCell.x; x++)
	{
		for (size_t y = 0; y < NbCell.y; y++)
		{

			Cell *CurrentCell = Cells[x][y];
			if (!CurrentCell->GetIsAlive())
				continue;

			WayPoint *Wp = WayPoints[x][y];

			if (!Wp)
				return nullptr;

			sf::Vector2f WpPosition = sf::Vector2f(Wp->X, Wp->Y);
			sf::Vector2f CellPosition = CellToGetWp->GetPosition();

			if (WpPosition == CellPosition)
				return Wp;
		}
	}

	return nullptr;
}
