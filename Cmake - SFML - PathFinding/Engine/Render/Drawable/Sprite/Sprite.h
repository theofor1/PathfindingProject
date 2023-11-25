#pragma once

#include <Engine/Render/Drawable/IDrawable.h>
#include <SFML/Graphics/Sprite.hpp>

class Sprite : public IDrawable
{
public:
	Sprite();
	~Sprite();

	virtual void Start() override;
	virtual void Update(float deltaTime) override;

	void SetTexture(const std::string& TextureName);
	void SetAnimation(const std::string& AnimationName);
	void SetActiveAnimation(bool play);
	void Reset();


	std::string GetTextureName() const;
	std::string GetAnimationName() const;
	sf::Sprite GetSprite();

protected:
	void PerformAnimation();

	sf::Sprite* sprite;
	std::string TextureName;
	std::string AnimationName;

	unsigned CurrentAnimationNb = 0;
	float AnimationTimer = 0.f;
	bool PlayAnimation;
};