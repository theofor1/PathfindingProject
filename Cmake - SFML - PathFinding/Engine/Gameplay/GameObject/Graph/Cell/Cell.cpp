#include "Cell.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <Component/Transform/Transform.h>

Cell::Cell(std::string Name, sf::Vector2f Position, int _SideSize, CellType _CellType) : GameObject(Name),
																						 SideSize(_SideSize),
																						 CurrentCellType(_CellType)
{
	SetSize(_SideSize);
	SetPosition(Position);

	UpdateColor();
	OtherCellTypeTeleportation = nullptr;
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

void Cell::SetCellType(const CellType NewCellType)
{
	CurrentCellType = NewCellType;
	UpdateColor();
}

void Cell::SetOtherCellTypeTeleportation(Cell *_OtherCellTypeTeleportation)
{
	if (!_OtherCellTypeTeleportation)
		return;

	if (!OtherCellTypeTeleportation)
	{
		OtherCellTypeTeleportation = _OtherCellTypeTeleportation;
		_OtherCellTypeTeleportation->SetOtherCellTypeTeleportation(this);
	}
}

void Cell::UnsetOtherCellTypeTeleportation()
{
	if (OtherCellTypeTeleportation)
		delete OtherCellTypeTeleportation;
}

CellType Cell::GetCellType() const
{
	return CurrentCellType;
}

void Cell::SetSize(const int _SideSize)
{
	SideSize = _SideSize;

	Size = sf::Vector2f(SideSize, SideSize);

	Rectangle.setSize(Size);
	Rectangle.setOutlineThickness(3);

	Rect.width = SideSize;
	Rect.height = SideSize;

	LocalPosition = sf::Vector2f(SideSize / 2, SideSize / 2);
}

void Cell::SetPosition(const sf::Vector2f Position)
{
	CTransform->SetWorldPosition(Position);
	Rectangle.setPosition(Position);

	Rect.left = Position.x;
	Rect.top = Position.y;
	// Rect.left = Position.x + LocalPosition.x;
	// Rect.top = Position.y  + LocalPosition.y;
}

void Cell::UpdateColor()
{
	sf::Color BackgroundColor;
	sf::Color BorderColor;

	BorderColor = sf::Color::Black;

	switch (CurrentCellType)
	{
	case CellType::NORMAL:
		BackgroundColor = sf::Color::Blue;
		break;
	case CellType::BLOCK:
		BackgroundColor = sf::Color(128, 128, 128);
		break;
	case CellType::TELEPORTATION:
		BackgroundColor = sf::Color::Green;
		break;
	default:
		BackgroundColor = sf::Color::Red;
		break;
	}

	Rectangle.setOutlineColor(BorderColor);
	Rectangle.setFillColor(BackgroundColor);
}
