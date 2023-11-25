//#include "Alien.h"
//#include "AlienLaser.h"
//#include <Engine/Gameplay/Levels/PlayField.h>
//#include "ConsoleRenderer.h"
//#include <Engine/Math/Random/RandomNumber.h>
//#include <Engine/Gameplay/GameObject/GameObject.h>
//
//Alien::Alien() { 
//	m_objType = new char[64]; 
//	strcpy(m_objType, "AlienShip"); 
//	sprite = RS_Alien; 
//}
//
//Alien::~Alien() {
//	delete m_objType; 
//}
//
//bool Alien::DecreaseHealth() { 
//	health -= 1.f; 
//	return health <= 0;
//}
//
//void Alien::Update(PlayField& world)
//{
//	pos.x += direction * velocity;
//	// Border check
//	if (pos.x < 0 || pos.x >= world.bounds.x - 1)
//	{
//		direction = -direction;
//		pos.y += 1;
//	}
//
//	// Border check vertical:
//	if (pos.y >= world.bounds.y - 1)
//	{
//		// kill player
//		GameObject* player = world.GetPlayerObject();
//		if (player)
//			if (pos.IntCmp(player->pos))
//				world.RemoveObject(player);
//	}
//
//	if (RandomNumber::RandomFloat(0, 1) < 0.2 && world.AlienLasers > 0)
//	{
//		//Spawn laser
//		GameObject& newLaser = *(new AlienLaser);
//		newLaser.pos = pos;
//		world.SpawnLaser(&newLaser);
//	}
//}
