#pragma once

#include <Engine/Scene/IScene.h>
#include <GameObject/Graph/Line/Line.h>
#include <Engine/Render/UIElements/Button/Button.h>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <rapidxml/rapidxml_print.hpp>

class Graph;
class PlayerShip;
class Cell;

enum class Mode
{
	MOVE_PLAYER,
	PUT_WALL,
	REMOVE_WALL
};

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

	Button* btnPlayerMoveMode;
	Button* btnPutWallMode;
	Button* btnRemoveWallMode;

	Button* btnUpWindowSpeed;
	Button* btnDownWindowSpeed;

	Button* btnUpPlayerSpeed;
	Button* btnDownPlayerSpeed;

	Button* btnRemoveGraphHeight;
	Button* btnAddGraphHeight;
	Button* btnRemoveGraphWidth;
	Button* btnAddGraphWidth;

	Button* btnSaveLevel;
	Button* btnLoadLevel;

	sf::Color ColorOnSelected;


	void OnGraphCellOnClick();
	void OnButtonsClick();

	void FollowWayPoints(float DeltaTime);
	void MoveTo(float DeltaTime, const sf::Vector2f TargetPosition);

	void ResetPath();
	void UpdateDrawDebugLines();

	void produceXMLDocForSave(rapidxml::xml_document<>& Doc);
	bool loadLevelFromXMLFile(rapidxml::xml_document<>& Doc);

private:
	int CurrentIndexWaypoint;
	std::vector<sf::Vector2f> WayPoints;
	Cell *CurrentCellDest;


	std::vector<Line> DebugLines;
	std::vector<Button*> AllButtons;

	bool OnWallMode;
	bool OnPutWallMode;

	Mode Mode;


	int GraphHeightNbCells;
	int GraphWidthNbCells;

	float TimeSinceLastInput = 0;

	float AmountSpeed = 20;


};
