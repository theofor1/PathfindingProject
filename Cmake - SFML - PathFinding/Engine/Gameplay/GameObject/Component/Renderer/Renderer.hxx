#include <Engine/Gameplay/GameObject/Component/Renderer/Renderer.h>
#include <Engine/Render/Drawable/IDrawable.h>

template<class D>
inline D* Renderer::AddNewDrawable(const std::string& Name)
{
	for (auto& Drawable : Drawables)
		if (Drawable->GetName() == Name)
			return nullptr;

	D* drawable = new D();
	
	if (!drawable)
		return nullptr;

	Drawables.push_back(drawable);
	Drawables[Drawables.size() - 1]->SetLocalPosition(sf::Vector2f(0, 0));
	Drawables[Drawables.size() - 1]->SetLocalScale(sf::Vector2f(1, 1));
	Drawables[Drawables.size() - 1]->SetLocalRotation(0);

	return drawable;
}

template<class D>
inline D* Renderer::AddNewDrawable(const std::string& Name, sf::Vector2f Pos, float Angle, sf::Vector2f Scale)
{
	if ((Pos.x == 0.f && Pos.y == 0.f) && Angle == 0.f && (Scale.x == 1.f && Scale.y == 1.f))
		return AddNewDrawable<D>(Name);

	for (auto& Drawable : Drawables)
		if (Drawable->GetName() == Name)
			return nullptr;

	D* drawable = new D();

	if (!drawable)
		return nullptr;

	Drawables.push_back(drawable);
	Drawables[Drawables.size() - 1]->SetLocalPosition(Pos);
	Drawables[Drawables.size() - 1]->SetLocalScale(Scale);
	Drawables[Drawables.size() - 1]->SetLocalRotation(Angle);

	return drawable;
}