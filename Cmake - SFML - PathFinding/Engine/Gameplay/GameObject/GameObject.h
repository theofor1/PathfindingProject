#pragma once

// #include "Vector.h"
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <iostream>


class IComponent;
class Renderer;
class Transform;

namespace sf
{
	class RenderWindow;
}

class GameObject
{
public:
	GameObject(std::string _Name = "");

	virtual void Start() = 0;

	virtual void Update(float DeltaTime) = 0;

	virtual void Destroy() = 0;

	virtual void Draw(sf::RenderWindow &window) const;

	virtual sf::Vector2f GetPosition() const;

	virtual void SetPosition(const sf::Vector2f NewPosition);
	virtual void AddWorldPosition(sf::Vector2f UpPosition);

	virtual void OnCollisionEnter(GameObject *OtherGameObject);
	virtual void OnCollisionStay(GameObject *OtherGameObject);
	virtual void OnCollisionExit(GameObject *OtherGameObject);

	void SetName(std::string _Name);
	std::string GetName();

	template <typename C>
	C *AddComponent();

	template <typename C>
	C *GetComponent() const;

protected:
	std::vector<IComponent *> Components;

	Transform *CTransform;

	std::string Name;

};

#include <Engine/Gameplay/GameObject/GameObject.hxx>
