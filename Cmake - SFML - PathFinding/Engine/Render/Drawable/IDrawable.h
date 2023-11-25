#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class IDrawable abstract
{
public:
	IDrawable(std::string _Name = "");
	virtual ~IDrawable();

	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;

	bool IsVisible() const;
	void SetVisibility(bool visible);
	void SetLocalPosition(sf::Vector2f NewPosition);
	void SetLocalScale(sf::Vector2f NewScale);
	void SetLocalRotation(float NewRotation);
	sf::Vector2f GetLocalPosition() const;
	sf::Vector2f GetLocalScale() const;
	float GetLocalRotation() const;

	const sf::Transform& GetWorldTransform() const;
	const std::string GetName() const;
	void SetWorldTransform(const sf::Transform& transform,  const sf::Vector2f Offset = sf::Vector2f(0, 0));

	void Draw(sf::RenderWindow& window) const;

protected:
	bool Visible;
	sf::Transform WorldTransform;
	sf::Drawable* Drawable;
	sf::Vector2f LocalPosition;
	sf::Vector2f LocalScale;
	float LocalRotation;

	std::string Name;

};