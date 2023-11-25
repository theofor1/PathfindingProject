#pragma once

#include <SFML/Graphics/Transform.hpp>
#include <Component/IComponent.h>

class Transform : public IComponent
{
public:
	Transform(GameObject& gameObject);

	virtual void Start() override;
	virtual void Update(float DeltaTime) override;
	virtual void Destroy() override;

	const sf::Transform& GetTransform();

	void SetWorldPosition(sf::Vector2f NewPosition);
	void AddWorldPosition(sf::Vector2f UpPosition);
	void SetRotation(float newRotation);
	void SetScale(sf::Vector2f newScale);

	sf::Vector2f GetWorldPosition() const;
	float GetRotation() const;
	sf::Vector2f GetScale() const;
	std::string GetComponentName() const override;

private:

	sf::Transform WorldTransform;

	sf::Vector2f WorldPosition;
	sf::Vector2f PreviousWorldPosition;
	sf::Vector2f Scale;
	float Rotation;

	void UpdateTransform();



};
