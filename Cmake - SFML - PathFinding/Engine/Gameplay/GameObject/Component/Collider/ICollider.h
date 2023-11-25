#pragma once

#include <SFML/Graphics.hpp>
#include <Component/IComponent.h>

class Transform;
class GameObject;


enum Layers {
	ALL = 1,
	STATIC = (1 << 1),
	ENNEMY = (1 << 2),
};

class ICollider : public IComponent
{
public:
	ICollider(GameObject& gameObject);

	virtual void Start();
	virtual void Update(float fDeltaTime);
	virtual void Destroy();
	virtual std::string GetComponentName() const;

	void SetColliderSize(sf::Vector2f size);
	void SetColliderPositionLocal(sf::Vector2f pos);
	void SetWasOnCollision(bool _isOnCollision);
	void CancelCollisionWith(ICollider *OtherCollider);
	void SetLayer(Layers layers);
	void AddLayer(Layers layers);
	void RemoveLayer(Layers layers);
	bool HasLayer(Layers layers);

	char GetMask() const;

	bool IsOnCollisionWidth(sf::FloatRect OtherRect);
	bool WasOnCollision();

	sf::RectangleShape m_debugRectangle;

	sf::FloatRect GetRect() const;
	bool isStatic = false;
	bool isDinamic = true;

protected:
	sf::FloatRect m_RenderRect;

	void UpdateRectPosition();

private:

	bool _WasOnCollision = false;

	unsigned char mask = Layers::ALL;

	sf::Vector2f LocalPosition;
	sf::Vector2f GetVectorMoveToCancelCollision(sf::FloatRect OtherRect);
};

