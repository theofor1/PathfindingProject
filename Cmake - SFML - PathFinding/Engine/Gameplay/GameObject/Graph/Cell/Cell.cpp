#include "Cell.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <Component/Transform/Transform.h>

Cell::Cell(std::string Name, sf::Vector2f Position, int _SideSize, const bool _IsAlive) : GameObject(Name),
																						  SideSize(_SideSize),
																						  IsAlive(_IsAlive)
{
	SetSize(_SideSize);
	SetPosition(Position);

	UpdateColor();

	IsAlive = _IsAlive;
}

Cell::~Cell()
{
}

void Cell::Start()
{
	GameObject::Start();
}

void Cell::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}

void Cell::Destroy()
{
	GameObject::Destroy();
}

void Cell::Draw(sf::RenderWindow &window) const
{
	window.draw(Rectangle);
}

sf::RectangleShape Cell::GetRectangleShape() const
{
	return Rectangle;
}

sf::FloatRect Cell::GetRect() const
{
	return Rect;
}

void Cell::SetIsAlive(const bool _IsAlive)
{
	IsAlive = _IsAlive;
	UpdateColor();
}

bool Cell::GetIsAlive() const
{
	return IsAlive;
}

void Cell::SetSize(const int _SideSize)
{
	SideSize = _SideSize;

	Size = sf::Vector2f(SideSize, SideSize);

	Rectangle.setSize(Size);
	Rectangle.setOutlineThickness(1);

	Rect.width = SideSize;
	Rect.height = SideSize;
}

void Cell::SetPosition(const sf::Vector2f Position)
{
	CTransform->SetWorldPosition(Position);
	Rectangle.setPosition(Position);

	Rect.left = Position.x;
	Rect.top = Position.y;
}

void Cell::UpdateColor()
{
	Rectangle.setOutlineColor(sf::Color::Red);
	Rectangle.setFillColor(IsAlive ? ColorOnAlive : ColorOnDead);
}
