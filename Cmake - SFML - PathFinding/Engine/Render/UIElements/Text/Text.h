#pragma once

#include <Engine/Render/UIElements/UIElement.h>

class Text : public UIElement {
public:

	Text(
		const Vec2f& _pos,
		const Vec2f& _size,
		sf::Color fillColor = sf::Color::Transparent);

	virtual void Start() override;
	virtual void Draw(sf::RenderWindow& _window);
	virtual const sf::FloatRect& UpdateRect(const sf::FloatRect& _parentRect);

	sf::Text text;
	sf::Font textFont;
};