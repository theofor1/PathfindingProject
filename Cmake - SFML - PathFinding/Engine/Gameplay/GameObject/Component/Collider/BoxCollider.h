#pragma once

#include <SFML/Graphics.hpp>
#include <Component/Collider/ICollider.h>

class Transform;
class GameOjbect;

class BoxCollider : public ICollider
{
public:
	BoxCollider(GameObject& gameObject);

	virtual void Start() override;
	virtual void Update(float fDeltaTime) override;
	virtual void Destroy() override;

	void SetColliderSize(sf::Vector2f size);

protected:
};

