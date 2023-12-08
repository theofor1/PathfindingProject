#pragma once

#include <Engine/Scene/IScene.h>
#include <SFML/Graphics.hpp>

class MainMenu : public IScene
{
public:
	MainMenu();

	void Start() override;
	void Update(float DeltaTime) override;
	void Destroy() override;
	void Draw(sf::RenderWindow& window) const;

private:
	sf::Font font;
	sf::Text text;
};

