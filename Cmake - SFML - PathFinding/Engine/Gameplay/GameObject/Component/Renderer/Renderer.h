#pragma once

#include <Component/IComponent.h>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class IDrawable;
class Transform;

class Renderer : public IComponent
{
public:
	Renderer(GameObject& gameObject);

	virtual void Start() override;
	virtual void Update(float DeltaTime) override;
	virtual void Destroy() override;

	std::string GetComponentName() const override;

	template <class D>
	D* AddNewDrawable(const std::string& Name);

	template <class D>
	D* AddNewDrawable(const std::string& Name, sf::Vector2f Pos, float Angle, sf::Vector2f Scale);
	
	void Draw(sf::RenderWindow& window) const;

protected:
	std::string Name;	

	// Elements to display on window
	std::vector<IDrawable*> Drawables;

};

#include "Renderer.hxx"
