#include "WayPoint.h"
#include <iostream>

WayPoint::WayPoint()
{
}

WayPoint::WayPoint(int _X, int _Y)
{
    SetCoordinate(_X, _Y);
}

void WayPoint::SetCoordinate(int _X, int _Y)
{
    this->X = _X;
    this->Y = _Y;
}

void WayPoint::LinkWayPoint(WayPoint *AnotherWayPoint, bool NoCost)
{
    if (AnotherWayPoint == this)
        return;

    bool exists = false;
    for (const WayPoint *Wp : LinkedWayPoints)
    {
        if (Wp == AnotherWayPoint)
        {
            if (NoCost)
                AddLinkedWayPointsWithNoCost(AnotherWayPoint);

            exists = true;
            break;
        }
    }

    if (!exists)
    {
        LinkedWayPoints.push_back(AnotherWayPoint);
        if (NoCost)
            AddLinkedWayPointsWithNoCost(AnotherWayPoint);
        AnotherWayPoint->LinkWayPoint(this, NoCost);
    }
}

std::vector<WayPoint *> WayPoint::GetLinkedWayPoints()
{
    return LinkedWayPoints;
}

WayPoint *WayPoint::GetWayPointWithLowestCost()
{
    if (LinkedWayPoints.size() == 0)
        return nullptr;

    WayPoint *Wp;
    float LowestCost = GetCost(LinkedWayPoints[0]);
    Wp = LinkedWayPoints[0];

    for (WayPoint *LinkedWayPoint : LinkedWayPoints)
    {
        float CurrentCost = GetCost(LinkedWayPoint);
        if (LowestCost > CurrentCost)
        {
            LowestCost = CurrentCost;
            Wp = LinkedWayPoint;
        }
    }
    return Wp;
}

bool WayPoint::IsLinkedTo(WayPoint *AnotherWayPoint)
{
    std::vector<WayPoint *> LinkedWayPoints = GetLinkedWayPoints();
    for (WayPoint *Wp : LinkedWayPoints)
    {
        if (Wp == AnotherWayPoint)
            return true;
    }
    return false;
}

// Protected

float WayPoint::GetCost(WayPoint *WpDest) const
{
    if (IsNoCostWayPoint(WpDest))
        return 0;
    float Cost = sqrt(pow(this->X - WpDest->X, 2) + pow(this->Y - WpDest->Y, 2));
    return Cost;
}

bool WayPoint::IsNoCostWayPoint(WayPoint *WayPointToCheck) const
{
    // std::cout << LinkedWayPointsWithNoCost.size() << "\n";
    for (const WayPoint *Wp : LinkedWayPointsWithNoCost)
        if (Wp == WayPointToCheck)
            return true;
    return false;
}

void WayPoint::AddLinkedWayPointsWithNoCost(WayPoint *AnotherWayPoint)
{
    LinkedWayPointsWithNoCost.erase(std::remove_if(LinkedWayPointsWithNoCost.begin(), LinkedWayPointsWithNoCost.end(),
                                                   [AnotherWayPoint](const WayPoint *wp)
                                                   { return wp == AnotherWayPoint; }),
                                    LinkedWayPointsWithNoCost.end());
    LinkedWayPointsWithNoCost.push_back(AnotherWayPoint);
}
