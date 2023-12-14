#pragma once

#include <Engine/Render/UIElements/UIElement.h>

class Text : public UIElement {
public:

	Text(
		const Vec2f& pos,
		const Vec2f& size,
		int fontSize = 10,
		sf::Color color = sf::Color::Black,
		sf::Color fillColor = sf::Color::White,
		sf::Color outlineColor = sf::Color::Transparent,
		int outlineThickness = 0);

	virtual void Start() override;
	virtual void Draw(sf::RenderWindow& _window);
	virtual const sf::FloatRect& UpdateRect(const sf::FloatRect& _parentRect);

	sf::Text text;
	sf::Font textFont;
};