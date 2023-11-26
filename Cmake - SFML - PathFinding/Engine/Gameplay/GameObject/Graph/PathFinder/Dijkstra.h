#include <vector>

#pragma once

class WayPoint;

struct WayPointMeeted {
    WayPoint *Wp;
    WayPoint *FromWp;
    float Cost;
};

class Dijkstra
{
public:
    static std::vector<WayPoint*> GetPathFinding(const std::vector<WayPoint *> WayPoints, WayPoint *Start, WayPoint *End);
private:

    static WayPointMeeted GetWayPointMeetedWithLowestCost(std::vector<WayPointMeeted>  WayPointsMeeted);
   
    static int GetIndexWayPoint(const std::vector<WayPoint *> WayPoints, WayPoint *WayPointToFindIndex);
   
    static bool WayPointIsTraveled(WayPoint *WayPointToCheck, std::vector<WayPoint *> TraveledWayPoints);
  
    static std::vector<WayPointMeeted> GetWayPointMeetedWithout(std::vector<WayPointMeeted>  WayPointsMeeted, WayPoint *WayPointToNotConserve);
    static std::vector<WayPoint *> GetWayPointNotParcouredConnectedTo(WayPoint *Waypoint, std::vector<WayPoint *> WayPointsParcoured);
    static std::vector<WayPoint*> GetPathFindByWayPointsParcoured(std::vector<WayPointMeeted> WpsMeetedParcoured);
   
    static WayPointMeeted GetWayPointMeeted(std::vector<WayPointMeeted> WpsMeetedParcoured, WayPoint* WpToFind);
};
