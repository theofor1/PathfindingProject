#include "Sprite.h"
#include <Engine/Render/Ressource/TextureManager.h>
#include <iostream>

Sprite::Sprite() : IDrawable()
{
	sprite = new sf::Sprite();
	Drawable = sprite;
	SetActiveAnimation(false);
}

Sprite::~Sprite()
{
	IDrawable::~IDrawable();
}

void Sprite::Start()
{}

void Sprite::Update(float deltaTime)
{
	if (TextureManager::Instance()->dataXml[TextureName][AnimationName]["SpriteNum"] > 1)
	{
		if (PlayAnimation)
		{
			AnimationTimer += deltaTime;
			PerformAnimation();
		}
	}
}

void Sprite::SetTexture(const std::string& TextureName)
{
	this->TextureName = TextureName;
	sprite->setTexture(TextureManager::Instance()->textures[TextureName]);
}

void Sprite::SetAnimation(const std::string& AnimationName)
{
	this->AnimationName = AnimationName;

	Reset();

	sprite->setTextureRect(sf::IntRect
		(
			TextureManager::Instance()->dataXml[TextureName][AnimationName]["X"] + CurrentAnimationNb * (TextureManager::Instance()->dataXml[TextureName][AnimationName]["SizeX"] + TextureManager::Instance()->dataXml[TextureName][AnimationName]["OffsetX"]),
			TextureManager::Instance()->dataXml[TextureName][AnimationName]["Y"],
			TextureManager::Instance()->dataXml[TextureName][AnimationName]["SizeX"],
			TextureManager::Instance()->dataXml[TextureName][AnimationName]["SizeY"]
		)
	);
}

void Sprite::SetActiveAnimation(bool play)
{
	PlayAnimation = play;
}

void Sprite::Reset()
{
	CurrentAnimationNb = 0;
	AnimationTimer = 0.f;
}

std::string Sprite::GetTextureName() const
{
	return TextureName;
}

std::string Sprite::GetAnimationName() const
{
	return AnimationName;
}

sf::Sprite Sprite::GetSprite()
{
	return *sprite;
}

void Sprite::PerformAnimation()
{
	if (AnimationTimer >= TextureManager::Instance()->dataXml[TextureName][AnimationName]["TimeBetweenAnimation"])
	{
		int SpriteNum = TextureManager::Instance()->dataXml[TextureName][AnimationName]["SpriteNum"] - 1;
		CurrentAnimationNb++;
		CurrentAnimationNb %= SpriteNum;
		AnimationTimer = 0;

		sprite->setTextureRect(sf::IntRect
			(
				TextureManager::Instance()->dataXml[TextureName][AnimationName]["X"] + CurrentAnimationNb * (TextureManager::Instance()->dataXml[TextureName][AnimationName]["SizeX"] + TextureManager::Instance()->dataXml[TextureName][AnimationName]["OffsetX"]),
				TextureManager::Instance()->dataXml[TextureName][AnimationName]["Y"],
				TextureManager::Instance()->dataXml[TextureName][AnimationName]["SizeX"],
				TextureManager::Instance()->dataXml[TextureName][AnimationName]["SizeY"]
			)
		);


	}
}
