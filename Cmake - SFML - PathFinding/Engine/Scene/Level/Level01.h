#pragma once

#include <Engine/Scene/IScene.h>

class Graph;
class PlayerShip;
class Cell;

class Level01 : public IScene
{
public:
	Level01();

	void Start() override;
	void Update(float DeltaTime) override;
	void Destroy() override;

protected:
	Graph *graph;
	PlayerShip *ship;

	void OnGraphCellOnClick();

	void FollowWayPoints(float DeltaTime);
	void MoveTo(float DeltaTime, const sf::Vector2f TargetPosition);

private:
	int CurrentIndexWaypoint = 0;
	std::vector<sf::Vector2f> WayPoints;
};
