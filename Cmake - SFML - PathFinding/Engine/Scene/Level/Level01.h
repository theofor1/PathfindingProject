#pragma once

#include <Engine/Scene/IScene.h>

class Level01 : public IScene
{
public:
	Level01();

	void Start() override;
	void Update(float DeltaTime) override;
	void Destroy() override;


private:

};

