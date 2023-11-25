#include "Graph.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Cell/Cell.h"

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

//////////////////////////////////////////////////
// PROTECTED

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
