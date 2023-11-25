#pragma once

#include <Engine/Scene/IScene.h>

class Graph;
class PlayerShip;
class Cell;

class Level01 : public IScene
{
public:
	Level01();

	void Start() override;
	void Update(float DeltaTime) override;
	void Destroy() override;

protected:
	Graph *graph;
	PlayerShip *ship;

	Cell* TargetCell;

	void OnGraphCellOnClick();

private:
};
