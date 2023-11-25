#pragma once

//#include "Vector.h"
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <iostream>


class IComponent;

namespace sf
{
	class RenderWindow;
}

class GameObject
{
public:
	GameObject(std::string _Name = "");

	virtual void Start() = 0;

	virtual void Update(float FDeltaTime) = 0;

	virtual void Destroy() = 0;

	virtual void Draw(sf::RenderWindow& window) const;

	virtual void OnCollisionEnter(GameObject* OtherGameObject);
	virtual void OnCollisionStay(GameObject* OtherGameObject);
	virtual void OnCollisionExit(GameObject* OtherGameObject);

	void SetName(std::string _Name);
	std::string GetName();

	template <typename C>
	C* AddComponent();

	template <typename C>
	C* GetComponent() const;


protected:
	std::vector<IComponent*> Components;

	std::string Name;

	sf::Vector2f WorldPosition = sf::Vector2f(0, 0);
	sf::Vector2f LocalPosition = sf::Vector2f(0, 0);
};

#include <Engine/Gameplay/GameObject/GameObject.hxx>
