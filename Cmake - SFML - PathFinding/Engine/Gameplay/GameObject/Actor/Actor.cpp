#include "Actor.h"
#include <Component/Collider/BoxCollider.h>
#include <Component/Renderer/Renderer.h>
#include <Component/Transform/Transform.h>
#include <Engine/Render/Drawable/Sprite/Sprite.h>

Actor::Actor(std::string Name) : GameObject(Name)
{
	CTransform = GetComponent<Transform>();
	CRenderer = AddComponent<Renderer>();
	CBoxCollider = AddComponent<BoxCollider>();

	SpeedMove = 100;
}

void Actor::Start()
{
	GameObject::Start();
}

void Actor::Update(float DeltaTime)
{
	CTransform->Update(DeltaTime);
	GameObject::Update(DeltaTime);
}

void Actor::Destroy()
{
	GameObject::Destroy();
}

void Actor::Draw(sf::RenderWindow &window) const
{
	GameObject::Draw(window);
	// window.draw(CBoxCollider->m_debugRectangle);
}

float Actor::GetSpeedMove() const
{
	return SpeedMove;
}

void Actor::SetSpeedMove(const float _speed)
{
	SpeedMove = _speed;
	if (SpeedMove < 0)
		SpeedMove = 0;
}

// PRIVATE

void Actor::CoverBoxColliderToSprite(sf::Texture &texture, Sprite &sprite)
{
	CBoxCollider->SetColliderSize(sf::Vector2f(texture.getSize().x * sprite.GetLocalScale().x, texture.getSize().y * sprite.GetLocalScale().y));
}
