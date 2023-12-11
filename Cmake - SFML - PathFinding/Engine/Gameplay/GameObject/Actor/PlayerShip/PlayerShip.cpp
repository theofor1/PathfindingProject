#include "PlayerShip.h"
#include <Component/Collider/BoxCollider.h>
#include <Component/Renderer/Renderer.h>
#include <Component/Transform/Transform.h>
#include <Engine/Render/Drawable/Sprite/Sprite.h>
#include <System/Input/InputManager.h>
#include <Engine/Render/Ressource/TextureManager.h>
#include <Engine/Render/Window.h>
#include <Engine/Math/Vector/Vector.h>

#include <iostream>

PlayerShip::PlayerShip(std::string Name) : Actor(Name)
{
	SpeedMove = 300;

	// InputManager::Instance()->Bind(InputAction::Up, [this]()
	// 							   { MoveUp(); });
	// InputManager::Instance()->Bind(InputAction::Down, [this]()
	// 							   { MoveDown(); });
	// InputManager::Instance()->Bind(InputAction::Left, [this]()
	// 							   { MoveLeft(); });
	// InputManager::Instance()->Bind(InputAction::Right, [this]()
	// 							   { MoveRight(); });

	// InputManager::Instance()->Bind(InputAction::MouseL, [this]()
	// 							   { SetCurrentDirectionByMouseLocation(); });
}

PlayerShip::~PlayerShip()
{
}

void PlayerShip::Start()
{
	Actor::Start();

	Ship = CRenderer->AddNewDrawable<Sprite>("Ship", sf::Vector2f(0, 0), 0, sf::Vector2f(0.1f, 0.1f));
	Ship->SetTexture("PlayerShip");

	// CoverBoxColliderToSprite(TextureManager::Instance()->textures["PlayerShip"], *Ship);

	CBoxCollider->SetColliderSize(sf::Vector2f(50, 50));
	Ship->SetLocalPosition(-sf::Vector2f(50 / 2, 50 / 2));
}

void PlayerShip::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);

	sf::Vector2f Move = GetDirection() * SpeedMove * DeltaTime;
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

void PlayerShip::SetCurrentDirectionByMouseLocation()
{
	sf::Vector2f EndLocation = GetMouseLocation();
	sf::Vector2f StartLocation = CTransform->GetWorldPosition();

	float Distance = Vector::GetDistance(StartLocation, EndLocation);
	float Tolerance = 3;

	if (Distance <= Tolerance)
		return;

	CurrentDirection = Vector::GetDirection(StartLocation, EndLocation);
}

sf::Vector2f PlayerShip::GetMouseLocation() const
{
	sf::Vector2i MouseLocation = sf::Mouse::getPosition(Window::Instance()->GetWindow());
	sf::Vector2f WorldMouseLocation = Window::Instance()->GetWindow().mapPixelToCoords(MouseLocation);
	return WorldMouseLocation;
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
