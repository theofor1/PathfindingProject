// #pragma once

// #include <Actor/Actor.h>

// #include "PlayerLaser.h"

// class PlayerShip : public Actor
// {
// public:
// 	PlayerShip(std::string Name = "");
// 	~PlayerShip();

// 	virtual void Start() override;
// 	virtual void Update(float FDeltaTime) override;
// 	virtual void Destroy() override;

// 	void UpdateForce();

// 	Sprite *GetSpriteShip() const;

// protected:
// 	void MotorVelocity();
// 	void LimitPosition();

// 	void SpawnLaser();

// private:
// 	Sprite *Ship;

// 	sf::Vector2f Force = sf::Vector2f(4, 30);
// 	float Speed = 1;
// };
