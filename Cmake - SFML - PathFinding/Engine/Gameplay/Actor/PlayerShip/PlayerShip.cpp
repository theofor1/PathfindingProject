#include "PlayerShip.h"
#include <Component/Collider/BoxCollider.h>
#include <Component/Renderer/Renderer.h>
#include <Component/Transform/Transform.h>
#include <Engine/Render/Drawable/Sprite/Sprite.h>
#include <System/Input/InputManager.h>
#include <Engine/GameManager/IGameManager.h>
#include <Engine/Render/Ressource/TextureManager.h>
#include <Engine/Render/Window.h>
#include <Engine/Scene/Level/Level01.h>

#include <iostream>

PlayerShip::PlayerShip(std::string Name) : Actor(Name)
{
	SpeedMove = 300;

	InputManager::Instance()->Bind(InputAction::Up, [this]()
								   { MoveUp(); });
	InputManager::Instance()->Bind(InputAction::Down, [this]()
								   { MoveDown(); });
	InputManager::Instance()->Bind(InputAction::Left, [this]()
								   { MoveLeft(); });
	InputManager::Instance()->Bind(InputAction::Right, [this]()
								   { MoveRight(); });
}

PlayerShip::~PlayerShip()
{
}

void PlayerShip::Start()
{
	Actor::Start();

	Ship = CRenderer->AddNewDrawable<Sprite>("Ship", sf::Vector2f(0, 0), 0, sf::Vector2f(0.3f, 0.3f));
	Ship->SetTexture("PlayerShip");

	CoverBoxColliderToSprite(TextureManager::Instance()->textures["PlayerShip"], *Ship);

	CTransform->SetWorldPosition(sf::Vector2f(200, 500));
}

void PlayerShip::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);

	sf::Vector2f Move = GetDirection() * Speed * DeltaTime;
	CTransform->AddWorldPosition(Move);

	CurrentDirection = sf::Vector2f(0, 0);
}

void PlayerShip::Destroy()
{
	Actor::Destroy();
}

Sprite *PlayerShip::GetSpriteShip() const
{
	return Ship;
}


//////////////////////////////////////////////////
// PROTECTED 

sf::Vector2f PlayerShip::GetDirection() const
{
	sf::Vector2f Direction = CurrentDirection;

	// Normalize the vector
	if (Direction.x != 0 && Direction.y != 0)
		Direction = Direction / std::sqrt(Direction.x * Direction.x + Direction.y * Direction.y);

	return Direction;
}


void PlayerShip::MoveDown()
{
	CurrentDirection.y = 1;
}

void PlayerShip::MoveUp()
{
	CurrentDirection.y = -1;
}

void PlayerShip::MoveRight()
{
	CurrentDirection.x = 1;
}

void PlayerShip::MoveLeft()
{
	CurrentDirection.x = -1;
}
