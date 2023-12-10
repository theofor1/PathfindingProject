#pragma once

#include <GameObject/GameObject.h>
#include <vector>
#include <map>

class Cell;
class WayPoint;

class Graph : public GameObject
{
public:
	Graph(std::string Name = "", const sf::Vector2i _NbCell = sf::Vector2i(0, 0), const int _CellSideSize = 50);
	~Graph();

	virtual void Start() override;
	virtual void Update(float DeltaTime) override;
	virtual void Destroy() override;

	virtual void Draw(sf::RenderWindow &window) const;

	virtual void UpdateSize(const sf::Vector2i Size);

	virtual Cell *GetCellByPosition(sf::Vector2f Position);
	virtual sf::Vector2i GetCellCoordinateByPosition(sf::Vector2f Position) const;
	virtual std::vector<sf::Vector2f> GetPath(Cell *CellStart, Cell *CellEnd);
	virtual sf::Vector2i GetNbCell() const;
	//To call when cells Alive state is updated (adding walls in custom level)
	void ReGenerateWaypoints();

	std::map<int, std::map<int, Cell *>> Cells;

protected:
	Cell *GetCell(int x, int y);
	WayPoint *GetWayPoint(int x, int y);

	std::map<int, std::map<int, WayPoint *>> GenerateWayPoints();
	virtual void LinkWayPointsToNeighbor();
	virtual std::vector<WayPoint *> GetWayPointArroundWayPoint(const int x, const int y);
	virtual  WayPoint * GetWayPointByCell(Cell* CellToGetWp);

private:
	sf::Vector2i NbCell;
	int CellSideSize;

	std::map<int, std::map<int, WayPoint *>> WayPoints;
};
