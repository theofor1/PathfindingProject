#pragma once

#include <GameObject/GameObject.h>
#include <vector>
#include <map>

class Cell;

class Graph : public GameObject
{
public:
	Graph(std::string Name = "ar", const sf::Vector2i _NbCell = sf::Vector2i(0, 0), const int _CellSideSize = 50);
	~Graph();

	virtual void Start() override;
	virtual void Update(float DeltaTime) override;
	virtual void Destroy() override;

	virtual void Draw(sf::RenderWindow &window) const;

	virtual Cell* GetCellByPosition(sf::Vector2f Position);

	std::map<int, std::map<int, Cell*>> Cells;
	
protected:


private:
	sf::Vector2i NbCell;
	int CellSideSize;
};
