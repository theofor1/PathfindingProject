#include "IDrawable.h"
#include <SFML/Graphics.hpp>

IDrawable::IDrawable(std::string _Name)
{
	Name = _Name;
	Visible = true;
	WorldTransform = sf::Transform::Identity;
	Drawable = nullptr;
	LocalPosition = sf::Vector2f(0, 0);
	LocalScale = sf::Vector2f(0, 0);
	LocalRotation = 0.f;
}

IDrawable::~IDrawable()
{
	if (Drawable)
	{
		delete Drawable;
		Drawable = nullptr;
	}
}

bool IDrawable::IsVisible() const
{
	return Visible;
}

void IDrawable::SetVisibility(bool visible)
{
	Visible = visible;
}

void IDrawable::SetLocalPosition(sf::Vector2f NewPosition)
{
	LocalPosition = NewPosition;
}

void IDrawable::SetLocalScale(sf::Vector2f NewScale)
{
	LocalScale = NewScale;
}

void IDrawable::SetLocalRotation(float NewRotation)
{
	LocalRotation = NewRotation;
}

sf::Vector2f IDrawable::GetLocalPosition() const
{
	return LocalPosition;
}

sf::Vector2f IDrawable::GetLocalScale() const
{
	return LocalScale;
}

float IDrawable::GetLocalRotation() const
{
	return LocalRotation;
}

const sf::Transform& IDrawable::GetWorldTransform() const
{
	return WorldTransform;
}

const std::string IDrawable::GetName() const
{
	return Name;
}

void IDrawable::SetWorldTransform(const sf::Transform& transform)
{
	WorldTransform = transform;
	WorldTransform.translate(LocalPosition);
	WorldTransform.rotate(LocalRotation);
	WorldTransform.scale(LocalScale);
}

void IDrawable::Draw(sf::RenderWindow& window) const
{
	if (!Drawable)
		return;

	sf::RenderStates states = sf::RenderStates::Default;
	states.transform = WorldTransform;
	window.draw(*Drawable, states);
}
