#include "Button.h"
#include <iostream>

Button::Button(
	const Vec2f& pos,
	const Vec2f& size, 
	int fontSize,
	sf::Color fillColor,
	sf::Color outlineColor,
	int outlineThickness) : UIElement(pos, size, fillColor, outlineColor, outlineThickness)
{
	
}

bool Button::Clicked(sf::Vector2f _mouseLocation)
{
	return DetectionRect.contains(_mouseLocation.x, _mouseLocation.y);
}

void Button::Start()
{
	TextButton.setColor(sf::Color::Black);
	TextButton.setFillColor(sf::Color::Black);
	TextButton.setOutlineColor(sf::Color::Black);
	TextButton.setCharacterSize(10);
	if (FontTextButton.loadFromFile("Ressources/Fonts/OpenSans-Regular.ttf"))
		TextButton.setFont(FontTextButton);
	else
		std::cout << "Error while loading the front, no text will appear \n";

	for (UIElement* pElem : Children)
		pElem->Start();
}

void Button::Draw(sf::RenderWindow& _window)
{
	UIElement::Draw(_window);
	_window.draw(TextButton);
}

const sf::FloatRect& Button::UpdateRect(const sf::FloatRect& _parentRect)
{
	UIElement::UpdateRect(_parentRect);

	sf::Vector2f RenderPos = RenderRectangle.getPosition();
	sf::Vector2f RenderSize = RenderRectangle.getSize();

	float HeightOffset = RenderSize.y / 2 - TextButton.getLocalBounds().height / 2;
	float WidthOffset = RenderSize.x / 2 - TextButton.getLocalBounds().width / 2;
	sf::Vector2f TextPos = RenderPos + sf::Vector2f(WidthOffset, HeightOffset);
	TextButton.setPosition(TextPos);

	return DetectionRect;
}

