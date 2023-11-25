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


	void Start();

	void Update(float fDeltaTime);

	void Destroy();

	// virtual void Start();

	// virtual void Update(float fDeltaTime);

	// virtual void Destroy();

	void Draw(sf::RenderWindow& window) const;

	void AddGameObject(GameObject *gameObject);
	std::vector<GameObject*> GetGameObjects();

	void OnCollision();

protected:
	std::vector<GameObject*> GameObjects;

	std::vector<GameObject*> GameObjectsWithCollider;
	std::vector<std::vector<GameObject*>> GameObjectsByCase;

	// void OnCollisionStay();
	// void ExtractGameObjectsByCase();
	// std::vector<GameObject*> GetGameObjectsWidthColliders();

	//
	sf::Vector2f CaseSize = sf::Vector2f(300, 300);

	std::string Name;
};

