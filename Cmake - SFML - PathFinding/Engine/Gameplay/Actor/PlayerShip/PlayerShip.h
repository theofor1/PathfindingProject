#pragma once

#include <Actor/Actor.h>

class PlayerShip : public Actor
{
public:
	PlayerShip(std::string Name = "");
	~PlayerShip();

	virtual void Start() override;
	virtual void Update(float DeltaTime) override;
	virtual void Destroy() override;

	Sprite *GetSpriteShip() const;

protected:

private:
	Sprite *Ship;

	sf::Vector2f CurrentDirection = sf::Vector2f(0, 0);
	float Speed = 300;

	virtual sf::Vector2f GetDirection() const;

	virtual void MoveDown();
	virtual void MoveUp();
	virtual void MoveLeft();
	virtual void MoveRight();




};
