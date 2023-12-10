#include "Button.h"

Button::Button(const Vec2f& _pos, const Vec2f& _size) : UIElement(_pos,_size)
{

}

bool Button::Clicked(sf::Vector2f _mouseLocation)
{
	return DetectionRect.contains(_mouseLocation.x, _mouseLocation.y);
}

void Button::Start()
{
	RenderRectangle.setFillColor(sf::Color::White);
	RenderRectangle.setOutlineColor(sf::Color(239, 239, 240));
	RenderRectangle.setOutlineThickness(2);

	for (UIElement* pElem : Children)
		pElem->Start();
}

