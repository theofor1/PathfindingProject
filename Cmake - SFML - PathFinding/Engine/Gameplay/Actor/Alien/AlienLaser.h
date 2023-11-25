#pragma once

#include <Engine/Gameplay/GameObject/GameObject.h>

class AlienLaser : public GameObject
{
public:
	AlienLaser();
	~AlienLaser();

	void Update(PlayField& world);
};

