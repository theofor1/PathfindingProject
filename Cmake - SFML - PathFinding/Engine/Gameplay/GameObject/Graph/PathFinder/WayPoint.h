#pragma once

#include <vector>

class WayPoint
{
public:
    WayPoint();
    WayPoint(int _X, int _Y);

    void SetCoordinate(int _X, int _Y);
    void LinkWayPoint(WayPoint *AnotherWayPoint, bool NoCost = false);
    
    std::vector<WayPoint*> GetLinkedWayPoints();
    WayPoint* GetWayPointWithLowestCost();
    bool IsLinkedTo(WayPoint *AnotherWayPoint);
    virtual bool IsNoCostWayPoint(WayPoint *WayPointToCheck) const;
    virtual float GetCost(WayPoint *WpDest) const;
    virtual void AddLinkedWayPointsWithNoCost(WayPoint* AnotherWayPoint);
    
    int X;
    int Y;

protected:

private:
    std::vector<WayPoint*> LinkedWayPoints;
    std::vector<WayPoint*> LinkedWayPointsWithNoCost;
};
