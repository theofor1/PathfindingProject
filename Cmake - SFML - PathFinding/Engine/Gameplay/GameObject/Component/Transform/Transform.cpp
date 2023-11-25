#include "Transform.h"
#include <Engine/Gameplay/GameObject/GameObject.h>

Transform::Transform(GameObject& gameObject) : IComponent(gameObject)
{
	HasUpdateFunction = false;

	WorldPosition = sf::Vector2f();
	Rotation = 0.f;
	Scale = sf::Vector2f(1.f, 1.f);
	UpdateTransform();
}

void Transform::Start()
{}

void Transform::Update(float DeltaTime)
{
	if (WorldPosition != PreviousWorldPosition)
	{
		PreviousWorldPosition = WorldPosition;
		UpdateTransform();
	}
}

void Transform::Destroy()
{}

const sf::Transform& Transform::GetTransform()
{
	return WorldTransform;
}

void Transform::SetWorldPosition(sf::Vector2f NewPosition)
{
	PreviousWorldPosition = WorldPosition;
	WorldPosition = NewPosition;
}

void Transform::AddWorldPosition(sf::Vector2f UpPosition)
{
	WorldPosition += UpPosition;
}

void Transform::SetRotation(float newRotation)
{
	Rotation = newRotation;
}

void Transform::SetScale(sf::Vector2f newScale)
{
	Scale = newScale;
}

sf::Vector2f Transform::GetWorldPosition() const
{
	return WorldPosition;
}

float Transform::GetRotation() const
{
	return Rotation;
}

sf::Vector2f Transform::GetScale() const
{
	return Scale;
}

std::string Transform::GetComponentName() const
{
	return "Transform";
}

void Transform::UpdateTransform()
{
	WorldTransform = sf::Transform::Identity;
	WorldTransform.translate(WorldPosition);
	WorldTransform.rotate(Rotation);
	WorldTransform.scale(Scale);
}


