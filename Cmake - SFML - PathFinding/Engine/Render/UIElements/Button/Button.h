#pragma once

#include <Engine/Render/UIElements/UIElement.h>

class Button : public UIElement {
public:

	Button::Button(
		const Vec2f& _pos,
		const Vec2f& _size,
		sf::Color color = sf::Color::White,
		sf::Color fillColor = sf::Color::White,
		sf::Color outlineColor = sf::Color::White);

	bool Clicked(sf::Vector2f _mouseLocation) override;

	virtual void Start() override;
	virtual void Draw(sf::RenderWindow& _window);
	virtual const sf::FloatRect& UpdateRect(const sf::FloatRect& _parentRect);

	sf::Text TextButton;
	sf::Font FontTextButton;
};