#include "Text.h"
#include <iostream>

Text::Text(const Vec2f& pos, 
	const Vec2f& size, 
	int fontSize,
	sf::Color color,
	sf::Color fillColor,
	sf::Color outlineColor,
	int outlineThickness) : UIElement(pos,size, fillColor, outlineColor, outlineThickness)
{
	text.setColor(color);
	text.setCharacterSize(fontSize);
	RenderRectangle.setOutlineThickness(2);

}

void Text::Start()
{
	if (textFont.loadFromFile("Ressources/Fonts/OpenSans-Regular.ttf"))
		text.setFont(textFont);
	else
		std::cout << "Error while loading the font, no text will appear \n";

	for (UIElement* pElem : Children)
		pElem->Start();
}

void Text::Draw(sf::RenderWindow& _window)
{
	UIElement::Draw(_window);
	_window.draw(text);
}

const sf::FloatRect& Text::UpdateRect(const sf::FloatRect& _parentRect)
{
	UIElement::UpdateRect(_parentRect);

	sf::Vector2f RenderPos = RenderRectangle.getPosition();
	sf::Vector2f RenderSize = RenderRectangle.getSize();

	float HeightOffset = RenderSize.y / 2 - text.getLocalBounds().height / 2;
	float WidthOffset = RenderSize.x / 2 - text.getLocalBounds().width / 2;
	sf::Vector2f TextPos = RenderPos + sf::Vector2f(WidthOffset, HeightOffset);
	text.setPosition(TextPos);

	return DetectionRect;
}

