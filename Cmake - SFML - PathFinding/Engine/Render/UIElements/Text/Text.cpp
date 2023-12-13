#include "Text.h"
#include <iostream>

Text::Text(const Vec2f& _pos, const Vec2f& _size) : UIElement(_pos,_size)
{


}

void Text::Start()
{
	RenderRectangle.setFillColor(sf::Color::White);
	RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	RenderRectangle.setOutlineThickness(2);

	//text.setColor(sf::Color::Black);
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::Black);
	text.setCharacterSize(10);
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

