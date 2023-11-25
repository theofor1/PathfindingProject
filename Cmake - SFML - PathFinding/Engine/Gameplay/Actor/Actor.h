// #pragma once

// #include <GameObject/GameObject.h>

// class BoxCollider;
// class Renderer;
// class Transform;
// class Sprite;

// namespace sf {
// 	class Texture;
// }

// class Actor abstract : public GameObject
// {
// public:
// 	Actor(std::string Name = "");

// 	virtual void Start() override;
// 	virtual void Update(float FDeltaTime) override;
// 	virtual void Destroy() override;
// 	virtual void Draw(sf::RenderWindow& window) const;

// protected:
// 	void SetVelocity(sf::Vector2f _v);
// 	void PerformMovement(float FDeltaTime);
// 	void CoverBoxColliderToSprite(sf::Texture &texture, Sprite &sprite);

// 	float SpeedMove = 100;
// 	sf::Vector2f Velocity;

// 	Transform* CTransform;
// 	Renderer* CRenderer;
// 	BoxCollider* CBoxCollider;


// };

