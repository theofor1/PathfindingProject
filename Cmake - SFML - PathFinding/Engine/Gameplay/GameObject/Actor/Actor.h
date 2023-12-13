#pragma once

#include <GameObject/GameObject.h>

class BoxCollider;
class Renderer;
class Transform;
class Sprite;

namespace sf {
	class Texture;
}

class Actor abstract : public GameObject
{
public:
	Actor(std::string Name = "");

	virtual void Start() override;
	virtual void Update(float DeltaTime) override;
	virtual void Destroy() override;
	virtual void Draw(sf::RenderWindow& window) const;
	
	virtual float GetSpeedMove() const;
	virtual void SetSpeedMove(const float _speed);

protected:
	Renderer *CRenderer;

	void CoverBoxColliderToSprite(sf::Texture &texture, Sprite &sprite);

	float SpeedMove;

	BoxCollider* CBoxCollider;
};

