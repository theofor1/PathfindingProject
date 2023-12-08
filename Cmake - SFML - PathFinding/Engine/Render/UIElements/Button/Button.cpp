#include "Button.h"

Button::Button(const Vec2f& _pos, const Vec2f& _size) : UIElement(_pos,_size)
{

}

bool Button::Clicked(sf::Vector2f _mouseLocation)
{
	return DetectionRect.contains(_mouseLocation.x, _mouseLocation.y);
}

