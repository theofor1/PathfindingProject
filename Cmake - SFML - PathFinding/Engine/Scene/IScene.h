#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class GameObject;

class IScene
{
public:
	IScene();
	~IScene();

	virtual void Start();

	virtual void Update(float DeltaTime);

	virtual void Destroy();

	virtual void Draw(sf::RenderWindow& window) const;

	void AddGameObject(GameObject *gameObject);
	std::vector<GameObject*> GetGameObjects();

protected:
	std::vector<GameObject*> GameObjects;
	std::string Name;
};

