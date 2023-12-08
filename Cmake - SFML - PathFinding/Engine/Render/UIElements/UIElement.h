#pragma once
#include <SFML/Graphics.hpp>

using Vec2f = sf::Vector2f;

enum class UILayout
{
	None,
	List
};

enum class UIDirection
{
	Horizontal,
	Vertical
};

enum class UIAlignment
{
	None,
	Start,
	Center,
	End
};

class UIElement
{
protected:
	Vec2f Pos;
	Vec2f Size;

	sf::FloatRect DetectionRect;
	std::vector<UIElement*> Children;

	UILayout Layout = UILayout::None;
	UIDirection Direction = UIDirection::Horizontal;
	UIAlignment HorizontalAlign = UIAlignment::None;
	UIAlignment VerticalAlign = UIAlignment::None;


	void UpdateLayoutList();
public:

	bool bDrawDebug = true;

	UIElement(const Vec2f& _pos, const Vec2f& _size);

	const Vec2f GetPos() const;
	const Vec2f GetSize() const;

	void SetPosX(float _x);
	void SetPosY(float _y);

	UILayout GetLayout() const;
	UIDirection GetDirection() const;
	void SetLayout(UILayout _layout, UIDirection _direction);
	void SetHorizontalAlignment(UIAlignment _align);
	void SetVerticalAlignment(UIAlignment _align);

	UIAlignment GetHorizontalAlignment() const;
	UIAlignment GetVerticalAlignment() const;

	float GetTotalChildrenWidth() const;
	float GetTotalChildrenHeight() const;

	template<typename T>
	T* AddChild(T* pChild)
	{
		if (std::find(Children.begin(), Children.end(), pChild) == Children.end())
		{
			Children.push_back(pChild);
		}

		return pChild;
	}
	void RemoveChild(UIElement* _child);
	virtual void Start();
	virtual void Update(float _dTime);
	virtual const sf::FloatRect& UpdateRect(const sf::FloatRect& _parentRect);
	virtual void Draw(sf::RenderWindow& _window);
	virtual bool Clicked(sf::Vector2f _mouseLocation);

	sf::RectangleShape RenderRectangle;
};