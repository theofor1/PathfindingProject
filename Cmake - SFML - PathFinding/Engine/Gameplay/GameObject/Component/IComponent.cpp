#include "IComponent.h"

#include <Engine/Gameplay/GameObject/GameObject.h>

IComponent::IComponent(GameObject& gameObject) : ParentGameObject{ gameObject }, HasUpdateFunction(true)
{}

IComponent::~IComponent()
{}

bool IComponent::NeedUpdate() const
{
	return HasUpdateFunction;
}

GameObject& IComponent::GetGameObject() const
{
	return ParentGameObject;
}
