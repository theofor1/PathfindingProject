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
	virtual sf::Vector2i GetCellCoordinate(Cell* CellToFind) const;
	virtual sf::Vector2i GetCellCoordinateByPosition(sf::Vector2f Position) const;
	virtual std::vector<sf::Vector2f> GetPath(Cell *CellStart, Cell *CellEnd);
	virtual sf::Vector2i GetNbCell() const;
	
	//To call when cells Alive state is updated (adding walls in custom level)
	void ReGenerateWaypoints();

	//To set all Cells alive, called when loading level
	void ResetCells();

	std::map<int, std::map<int, Cell *>> Cells;

	Cell *GetCell(int x, int y);
	WayPoint *GetWayPoint(int x, int y);
	virtual  WayPoint * GetWayPointByCell(Cell* CellToGetWp);

protected:


	std::map<int, std::map<int, WayPoint *>> GenerateWayPoints();
	virtual void LinkWayPointsToNeighbor();
	virtual void LinkWayPointsTeleportation();
	virtual void LinkWayPointsToAnotherOne(WayPoint *Waypoint, WayPoint *OtherWayPoint, bool NoCost = false);

	virtual std::vector<WayPoint *> GetWayPointArroundWayPoint(const int x, const int y);

	virtual std::vector<Cell *> GetCellsTypeTeleportation();



private:
	sf::Vector2i NbCell;
	int CellSideSize;

	std::map<int, std::map<int, WayPoint *>> WayPoints;
};
