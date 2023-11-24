#include "Dijkstra.h"
#include "WayPoint.h"
#include <iostream>

std::vector<WayPoint *> Dijkstra::GetPathFinding(const std::vector<WayPoint *> WayPoints, WayPoint *Start, WayPoint *End)
{
    std::vector<WayPoint *> WayPointsPathFinding;

    if (!Start || !End || WayPoints.size() == 0)
        return WayPointsPathFinding;

    // Declare variable
    std::vector<WayPoint *> WayPointsRemaining = WayPoints;
    std::vector<WayPointMeeted> WpsMeeted;
    std::vector<WayPointMeeted> WpsMeetedParcoured;
    std::vector<WayPoint *> WayPointsParcoured;

    // std::vector<WayPointMeeted> WpsMeeted;

    // Start from Start waypoint
    WayPoint *CurrentWayPoint = Start;
    WayPointsParcoured.push_back(Start);

    WayPointMeeted FirstWpMeeted;
    FirstWpMeeted.Cost = 0;
    FirstWpMeeted.Wp = Start;
    FirstWpMeeted.FromWp = nullptr;
    WpsMeetedParcoured.push_back(FirstWpMeeted);

    // Remove Start
    int Index = GetIndexWayPoint(WayPointsRemaining, Start);
    
    if (Index == -1)
        return WayPointsPathFinding;

    WayPointsRemaining.erase(WayPointsRemaining.begin() + Index);

    float CostFromBeginning = 0;

    // Get the shortest Path
    for (int index = 0; index < WayPointsRemaining.size(); index++)
    {
        // Get All Wp not parcoured connected to current WP
        std::vector<WayPoint *> LinkedWayPointsNoParcoured = GetWayPointNotParcouredConnectedTo(CurrentWayPoint, WayPointsParcoured);

        // Stock Parcours distance from beginning
        for (WayPoint *LinkedWp : LinkedWayPointsNoParcoured)
        {
            WayPointMeeted WpMeeted;
            WpMeeted.Wp = LinkedWp;

            // Get Cost from beginning to
            WpMeeted.Cost = LinkedWp->GetCost(CurrentWayPoint) + CostFromBeginning;
            WpMeeted.FromWp = CurrentWayPoint;
            WpsMeeted.push_back(WpMeeted);
        }

        // Get WP with nearest distance parcours since begenning
        WayPointMeeted LowestCostWayPointMeeted = GetWayPointMeetedWithLowestCost(WpsMeeted);

        if (CurrentWayPoint->IsLinkedTo(LowestCostWayPointMeeted.Wp))
            CostFromBeginning += CurrentWayPoint->GetCost(LowestCostWayPointMeeted.Wp);
        else
            CostFromBeginning = LowestCostWayPointMeeted.Cost;

        CurrentWayPoint = LowestCostWayPointMeeted.Wp;

        WayPointsParcoured.push_back(CurrentWayPoint);
        WpsMeetedParcoured.push_back(LowestCostWayPointMeeted);

        if (CurrentWayPoint == End)
            break;

        // Remove from WpsMeeted the new current waypoint
        WpsMeeted = GetWayPointMeetedWithout(WpsMeeted, CurrentWayPoint);
    }

    WayPointsPathFinding = GetPathFindByWayPointsParcoured(WpsMeetedParcoured);
    return WayPointsPathFinding;
}

// Private

int Dijkstra::GetIndexWayPoint(const std::vector<WayPoint *> WayPoints, WayPoint *WayPointToFindIndex)
{
    int Index = 0;
    for (const WayPoint *Wp : WayPoints)
    {
        if (Wp == WayPointToFindIndex)
        {
            return Index;
        }
        Index++;
    }
    return -1;
}

WayPointMeeted Dijkstra::GetWayPointMeetedWithLowestCost(std::vector<WayPointMeeted> WayPointsMeeted)
{
    WayPointMeeted WpMeetedWithLowestCost = WayPointMeeted();

    if (WayPointsMeeted.size() == 0)
        return WpMeetedWithLowestCost;

    WpMeetedWithLowestCost = WayPointsMeeted[0];
    float LowestCost = WayPointsMeeted[0].Cost;

    for (WayPointMeeted WpMeeted : WayPointsMeeted)
    {
        float CurrentCost = WpMeeted.Cost;
        if (LowestCost > CurrentCost)
        {
            LowestCost = CurrentCost;
            WpMeetedWithLowestCost = WpMeeted;
        }
    }
    return WpMeetedWithLowestCost;
}

std::vector<WayPointMeeted> Dijkstra::GetWayPointMeetedWithout(std::vector<WayPointMeeted> WayPointsMeeted, WayPoint *WayPointToNotConserve)
{
    std::vector<WayPointMeeted> WpsMeeted;

    for (WayPointMeeted WpMeeted : WayPointsMeeted)
    {
        if (WpMeeted.Wp != WayPointToNotConserve)
            WpsMeeted.push_back(WpMeeted);
    }

    return WpsMeeted;
}

bool Dijkstra::WayPointIsTraveled(WayPoint *WayPointToCheck, std::vector<WayPoint *> WayPointsMeeted)
{
    for (WayPoint *Wp : WayPointsMeeted)
        if (WayPointToCheck == Wp)
            return true;
    return false;
}

std::vector<WayPoint *> Dijkstra::GetWayPointNotParcouredConnectedTo(WayPoint *Waypoint, std::vector<WayPoint *> WayPointsParcoured)
{
    std::vector<WayPoint *> Wps;

    // Get All Wp connected to Current WP
    std::vector<WayPoint *> LinkedWayPoints = Waypoint->GetLinkedWayPoints();

    for (WayPoint *LinkedWp : LinkedWayPoints)
    {
        // Add wp if its not parcoured
        if (WayPointIsTraveled(LinkedWp, WayPointsParcoured))
            continue;
        Wps.push_back(LinkedWp);
    }
    return Wps;
}

std::vector<WayPoint *> Dijkstra::GetPathFindByWayPointsParcoured(std::vector<WayPointMeeted> WpsMeetedParcoured)
{
    std::vector<WayPoint *> Path;

    if (WpsMeetedParcoured.size() == 0)
        return Path;

    // Get last one
    WayPointMeeted CurrentWpMeeted = WpsMeetedParcoured[WpsMeetedParcoured.size() - 1];
    Path.push_back(CurrentWpMeeted.Wp);

    for (int index = WpsMeetedParcoured.size() - 1; index >= 0; index--)
    {
        if (!CurrentWpMeeted.FromWp)
            break;
        CurrentWpMeeted = GetWayPointMeeted(WpsMeetedParcoured, CurrentWpMeeted.FromWp);
        Path.push_back(CurrentWpMeeted.Wp);
    }

    // Path is from the last to the start
    // Inverse Path
    std::vector<WayPoint *> PathInverse;

    for (int index = Path.size() - 1; index >= 0; index--)
        PathInverse.push_back(Path[index]);

    Path = PathInverse;

    return Path;
}

WayPointMeeted Dijkstra::GetWayPointMeeted(std::vector<WayPointMeeted> WpsMeetedParcoured, WayPoint *WpToFind)
{
    for (WayPointMeeted WpMeeted : WpsMeetedParcoured)
    {
        if (WpMeeted.Wp == WpToFind)
            return WpMeeted;
    }
    return WayPointMeeted();
}
