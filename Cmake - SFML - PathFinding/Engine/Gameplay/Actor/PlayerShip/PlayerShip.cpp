// #include "PlayerShip.h"
// #include <Component/Collider/BoxCollider.h>
// #include <Component/Renderer/Renderer.h>
// #include <Component/Transform/Transform.h>
// #include <Engine/Render/Drawable/Sprite/Sprite.h>
// #include <System/Input/InputManager.h>
// #include <Engine/GameManager/IGameManager.h>
// #include <Engine/Render/Ressource/TextureManager.h>
// #include <Engine/Render/Window.h>
// #include <Actor/PlayerShip/PlayerLaser.h>
// #include <Engine/Scene/Level/Level01.h>
// #include <Math/Vector/Vector.h>

// # define PI           3.14159265358979323846  /* pi */

// PlayerShip::PlayerShip(std::string Name) : Actor(Name)
// { 
// 	SpeedMove = 300;
// }

// PlayerShip::~PlayerShip() { 
	
// }

// void PlayerShip::Start()
// {
// 	Actor::Start();

// 	//curve.AddLine(sf::Vector2f(50, 10), sf::Vector2f(60, 10), sf::Color::Red);

// 	Ship = CRenderer->AddNewDrawable<Sprite>("Ship", sf::Vector2f(0, 0), 0, sf::Vector2f(0.3f, 0.3f));
// 	Ship->SetTexture("PlayerShip");

// 	CoverBoxColliderToSprite(TextureManager::Instance()->textures["PlayerShip"], *Ship);

// 	// Place on bottom middle
// 	//CTransform->SetWorldPosition(sf::Vector2f(Window::Instance()->GetWindow().getSize().x / 2 + (TextureManager::Instance()->textures["PlayerShip"].getSize().x * Ship->GetLocalScale().x) / 2, Window::Instance()->GetWindow().getSize().y - TextureManager::Instance()->textures["PlayerShip"].getSize().y * Ship->GetLocalScale().y - 50));
// 	CTransform->SetWorldPosition(sf::Vector2f(200, Window::Instance()->GetWindow().getSize().y - TextureManager::Instance()->textures["PlayerShip"].getSize().y * Ship->GetLocalScale().y - 200));
// }

// void PlayerShip::Update(float FDeltaTime)
// {
// 	//MotorVelocity();
// 	//PerformMovement(FDeltaTime);
// 	//LimitPosition();

// 	SpawnLaser();
// 	UpdateForce();

// 	Actor::Update(FDeltaTime);

// 	sf::Vector2f Pos = CTransform->GetWorldPosition();
// 	sf::Vector2f posPrevious;

// }

// void PlayerShip::Destroy()
// {
// 	Actor::Destroy();
// }

// void PlayerShip::UpdateForce()
// {
// 	// sf::Vector2f forceUp = sf::Vector2f(InputManager::Instance()->GetAxis(InputAxis::Horizontal), InputManager::Instance()->GetAxis(InputAxis::Vertical));
// 	// Force += forceUp;

// 	// //std::cout << Force.x << "  " << Force.y << "\n";

// 	// // get the current mouse position in the window
// 	// sf::Vector2i pixelPos = sf::Mouse::getPosition(Window::Instance()->GetWindow());

// 	// // convert it to world coordinates
// 	// sf::Vector2f worldPos = Window::Instance()->GetWindow().mapPixelToCoords(pixelPos);
// 	// sf::Vector2f PlayerPosCenter = CTransform->GetWorldPosition();
// 	// //std::cout << worldPos.x << "   " << worldPos.y << "\n";

// 	// PlayerPosCenter.x += (TextureManager::Instance()->textures["PlayerShip"].getSize().x * Ship->GetLocalScale().x) / 2;
// 	// PlayerPosCenter.y += (TextureManager::Instance()->textures["PlayerShip"].getSize().y * Ship->GetLocalScale().y) / 2;

// 	// float DistanceFromPlayer = Vector::GetDistance(worldPos, PlayerPosCenter);

// 	// sf::Vector2f VecDir = worldPos - PlayerPosCenter;
// 	// Vector::Normalized(VecDir);

// 	// //VecDir.x *= -1;
// 	// VecDir.y *= -1;
// 	// pme.SetDir(VecDir);

// 	// if (DistanceFromPlayer > 500)
// 	// 	DistanceFromPlayer = 500;

// 	// pme.SetSpeed(DistanceFromPlayer / 20);

// 	// float degCos = acos(VecDir.x) * 180 / PI;
// 	// float degSin = asin(VecDir.y) * 180 / PI;

// 	// float deg = abs(degCos);

// 	// if (degCos < 0 || degSin < 0)
// 	// 	deg = 360 - deg;

// 	// //std::cout << VecDir.x << "   " << VecDir.y << "\n";
// 	// //std::cout << deg << "\n";
// 	// //std::cout << pme.angle << "\n";
// 	// pme.angle = deg;
// }

// Sprite* PlayerShip::GetSpriteShip() const
// {
// 	return Ship;
// }

// void PlayerShip::MotorVelocity()
// {
// 	// The player can only move horizontal
// 	Velocity.x = InputManager::Instance()->GetAxis(InputAxis::Horizontal);
// }

// void PlayerShip::LimitPosition()
// {
// 	float bottom = Window::Instance()->GetWindow().getSize().y - TextureManager::Instance()->textures["PlayerShip"].getSize().y * Ship->GetLocalScale().y - 50;
// 	if (CTransform->GetWorldPosition().x > Window::Instance()->GetWindow().getSize().x - (TextureManager::Instance()->textures["PlayerShip"].getSize().x * Ship->GetLocalScale().x))
// 		CTransform->SetWorldPosition(sf::Vector2f(Window::Instance()->GetWindow().getSize().x - (TextureManager::Instance()->textures["PlayerShip"].getSize().x * Ship->GetLocalScale().x), bottom));
// 	else if (CTransform->GetWorldPosition().x < 0)
// 		CTransform->SetWorldPosition(sf::Vector2f(0, bottom));
// }

// void PlayerShip::SpawnLaser()
// {
// 	if (InputManager::Instance()->GetActionDown(InputAction::Fire)) {
// 		PlayerLaser* laser = new PlayerLaser();
// 		laser->Start();


// 		sf::Vector2f Pos;
// 		Pos.x = GetComponent<Transform>()->GetWorldPosition().x + (TextureManager::Instance()->textures["PlayerShip"].getSize().x * Ship->GetLocalScale().x) / 2 - (TextureManager::Instance()->textures[laser->GetSpriteLaser()->GetTextureName()].getSize().x * laser->GetSpriteLaser()->GetLocalScale().x) / 2;
// 		Pos.y = GetComponent<Transform>()->GetWorldPosition().y - (TextureManager::Instance()->textures[laser->GetSpriteLaser()->GetTextureName()].getSize().y * laser->GetSpriteLaser()->GetLocalScale().y) / 2;
		
// 		laser->GetComponent<Transform>()->SetWorldPosition(Pos);


// 		// get the current mouse position in the window
// 		sf::Vector2i pixelPos = sf::Mouse::getPosition(Window::Instance()->GetWindow());

// 		// convert it to world coordinates
// 		sf::Vector2f worldPos = Window::Instance()->GetWindow().mapPixelToCoords(pixelPos);
// 		sf::Vector2f PlayerPosCenter = CTransform->GetWorldPosition();
// 		PlayerPosCenter.x += (TextureManager::Instance()->textures["PlayerShip"].getSize().x * Ship->GetLocalScale().x) / 2;
// 		PlayerPosCenter.y += (TextureManager::Instance()->textures["PlayerShip"].getSize().y * Ship->GetLocalScale().y) / 2;

// 		float DistanceFromPlayer = Vector::GetDistance(worldPos, PlayerPosCenter);

// 		sf::Vector2f VecDir = worldPos - PlayerPosCenter;
// 		Vector::Normalized(VecDir);

// 		VecDir.x *= -1;
// 		VecDir.y *= -1;

// 		laser->Start();

// 		IGameManager::Instance()->GetActiveScene().AddGameObject(laser);
// 	}
// }


