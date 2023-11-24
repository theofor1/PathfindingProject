#pragma once

#include <vector>
class WayPoint;

class PathfindingAlgorithm
{
public:
    virtual std::vector<WayPoint> GetPathFinding(const std::vector<WayPoint> WayPoints, const WayPoint Start, const WayPoint End) = 0;
};
