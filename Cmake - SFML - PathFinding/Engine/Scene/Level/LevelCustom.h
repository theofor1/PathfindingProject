#pragma once

#include <Engine/Scene/IScene.h>
#include <GameObject/Graph/Line/Line.h>
#include <Engine/Render/UIElements/Button/Button.h>

class Graph;
class PlayerShip;
class Cell;
// class Live;

class LevelCustom : public IScene
{
public:
	LevelCustom();

	void Start() override;
	void Update(float DeltaTime) override;
	void Destroy() override;
	void Draw(sf::RenderWindow& window) const;


protected:
	Graph* graph;
	PlayerShip* ship;

	UIElement* outerBox;
	UIElement* graphHeightBox;
	UIElement* graphWidthBox;
	Button* addWalls;
	Button* removeGraphHeight;
	Button* addGraphHeight;
	Button* removeGraphWidth;
	Button* addGraphWidth;


	void OnGraphCellOnClick();
	void EventOnClick();
	void TestUpdateGraphSize(sf::Vector2i Size);

	void FollowWayPoints(float DeltaTime);
	void MoveTo(float DeltaTime, const sf::Vector2f TargetPosition);

	void ResetPath();
	void UpdateDrawDebugLines();

private:
	int CurrentIndexWaypoint = 0;
	std::vector<sf::Vector2f> WayPoints;


	std::vector<Line> DebugLines;
	std::vector<Button*> AllButtons;

	bool OnWallMode = false;
	int GraphHeightNbCells;
	int GraphWidthNbCells;

	float TimeSinceLastInput = 0;


};
