#pragma once

#include <Engine/Scene/IScene.h>
#include <SFML/Graphics.hpp>
#include <Engine/Render/UIElements/Button/Button.h>
#include <Engine/Render/UIElements/Text/Text.h>

class MainMenu : public IScene
{
public:
	MainMenu();

	void Start() override;
	void Update(float DeltaTime) override;
	void Destroy() override;
	void Draw(sf::RenderWindow& window) const;

protected:
	UIElement* outerBox;

	Text* title;

	Button* btnPlay;
	Button* btnExit;

	sf::Color ColorOnSelected;

	void OnButtonsClick();

private:
	sf::Font font;
	sf::Text text;









	UIElement* graphHeightBox;
	UIElement* graphWidthBox;

	Button* btnPlayerMoveMode;
	Button* btnPutWallMode;
	Button* btnRemoveWallMode;

	Button* btnRemoveGraphHeight;
	Button* btnAddGraphHeight;
	Button* btnRemoveGraphWidth;
	Button* btnAddGraphWidth;


private:
	int CurrentIndexWaypoint;
	std::vector<sf::Vector2f> WayPoints;


	std::vector<Button*> AllButtons;

	bool OnWallMode;
	bool OnPutWallMode;

	int GraphHeightNbCells;
	int GraphWidthNbCells;

	float TimeSinceLastInput = 0;

};





