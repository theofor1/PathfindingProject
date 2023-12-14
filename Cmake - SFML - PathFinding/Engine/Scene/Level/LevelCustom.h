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
	PUT_CELL_BLOCK,
	PUT_CELL_NORMAL,
	PUT_CELL_TELEPORTATION
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
	UIElement* windowSpeedBox;
	UIElement* playerSpeedBox;

	Button* btnPlayerMoveMode;
	Button* btnPutCellTypeBlock;
	Button* btnPutCellTypeNormal;
	Button* btnPutCellTypeTeleportation;

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

	void FollowPath(float DeltaTime);
	void MoveTo(float DeltaTime, const sf::Vector2f TargetPosition);

	void ResetPath();
	void UpdateDrawDebugLines();
	void InitButtons();

	void CancelPuttingCurrentCellTeleportation();

	void produceXMLDocForSave(rapidxml::xml_document<>& Doc);
	bool loadLevelFromXMLFile(rapidxml::xml_document<>& Doc);

private:
	int CurrentIndexWaypoint;
	std::vector<sf::Vector2f> Path;
	Cell *CurrentCellDest;
	Cell *CurrentCellTypeTeleportation;

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
