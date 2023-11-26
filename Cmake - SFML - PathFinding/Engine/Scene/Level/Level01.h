#pragma once

#include <Engine/Scene/IScene.h>
#include <GameObject/Graph/Line/Line.h>

class Graph;
class PlayerShip;
class Cell;
// class Live;

class Level01 : public IScene
{
public:
	Level01();

	void Start() override;
	void Update(float DeltaTime) override;
	void Destroy() override;
	void Draw(sf::RenderWindow& window) const;


protected:
	Graph *graph;
	PlayerShip *ship;

	void OnGraphCellOnClick();

	void FollowWayPoints(float DeltaTime);
	void MoveTo(float DeltaTime, const sf::Vector2f TargetPosition);

	void ResetPath();
	void UpdateDrawDebugLines();

private:
	int CurrentIndexWaypoint = 0;
	std::vector<sf::Vector2f> WayPoints;


	std::vector<Line> DebugLines;



};
