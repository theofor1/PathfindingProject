#include "UIElement.h"
#include <algorithm>
#include <iostream>

UIElement::UIElement(const Vec2f& _pos, const Vec2f& _size) : Pos(_pos), Size(_size) {

}

const Vec2f UIElement::GetPos() const
{
	return Pos;
}

const Vec2f UIElement::GetSize() const
{
	return Size;
}

void UIElement::SetPosX(float _x)
{
	Pos.x = _x;
}

void UIElement::SetPosY(float _y)
{
	Pos.y = _y;
}

UILayout UIElement::GetLayout() const
{
	return Layout;
}

UIDirection UIElement::GetDirection() const
{
	return Direction;
}

void UIElement::Start()
{
	RenderRectangle.setOutlineColor(sf::Color::Red);
	RenderRectangle.setOutlineThickness(2);
	RenderRectangle.setFillColor(sf::Color::Transparent);

	for (UIElement* pElem : Children)
		pElem->Start();
}

bool UIElement::Clicked(sf::Vector2f _mouseLocation)
{
	return false;
}

void UIElement::RemoveChild(UIElement* _child)
{
	auto found = std::find(Children.begin(), Children.end(), _child);
	if (found != Children.end())
	{
		Children.erase(found);
	}
}

void UIElement::Update(float _dTime)
{
	for (UIElement* pElem : Children)
		pElem->Update(_dTime);
}

const sf::FloatRect& UIElement::UpdateRect(const sf::FloatRect& _parentRect)
{
	Vec2f vPos = Vec2f(_parentRect.left, _parentRect.top) + Vec2f(Pos.x * _parentRect.width, Pos.y * _parentRect.height);
	Vec2f vSize = Vec2f(_parentRect.width * Size.x, _parentRect.height * Size.y);

	DetectionRect.left = vPos.x;
	DetectionRect.top = vPos.y;

	DetectionRect.width = vSize.x;
	DetectionRect.height = vSize.y;

	if (bDrawDebug)
	{
		RenderRectangle.setPosition(DetectionRect.left, DetectionRect.top);
		RenderRectangle.setSize(sf::Vector2f(DetectionRect.width, DetectionRect.height));
	}


	switch (Layout)
	{
	case UILayout::List:
	{
		UpdateLayoutList();
		break;
	}
	}

	for (UIElement* pElem : Children)
		pElem->UpdateRect(DetectionRect);

	return DetectionRect;
}


void UIElement::SetLayout(UILayout _layout, UIDirection _direction)
{
	 Layout = _layout; 
	 Direction = _direction; 
}

void UIElement::SetHorizontalAlignment(UIAlignment _align)
{
	HorizontalAlign = _align;
}

void UIElement::SetVerticalAlignment(UIAlignment _align)
{
	VerticalAlign = _align;
}

UIAlignment UIElement::GetHorizontalAlignment() const
{
	return HorizontalAlign;
}

UIAlignment UIElement::GetVerticalAlignment() const
{
	return VerticalAlign;
}

float UIElement::GetTotalChildrenWidth() const
{
	float total = 0;
	for (UIElement* pElem : Children)
	{
		total += pElem->GetSize().x;
	}
	return total;
}
float UIElement::GetTotalChildrenHeight() const
{
	float total = 0;
	for (UIElement* pElem : Children)
	{
		total += pElem->GetSize().y;
	}

	return total;
}



void UIElement::UpdateLayoutList()
{
	float fStart = 0;

	float fTotalWidth = GetTotalChildrenWidth();;
	float ftotalHeight = GetTotalChildrenHeight();
	if (Direction == UIDirection::Vertical)
	{
		switch (VerticalAlign)
		{
		case UIAlignment::Start:fStart = 0; break;
		case UIAlignment::Center: fStart = 0.5 - ftotalHeight * 0.5; break;
		case UIAlignment::End: fStart = 1 - ftotalHeight; break;
		}
	}
	else if (Direction == UIDirection::Horizontal)
	{
		switch (HorizontalAlign)
		{
		case UIAlignment::Start: fStart = 0; break;
		case UIAlignment::Center:fStart = 0.5 - fTotalWidth * 0.5; break;
		case UIAlignment::End: fStart = 1 - fTotalWidth; break;
		}
	}

	float fCurrentInDir = fStart;
	float fCurrentLineHeight = 0;
	float fCurrentLineWidth = 0;
	float fCurrentCrossDir = 0;

	for (UIElement* pElem : Children)
	{
		switch (VerticalAlign)
		{
		case UIAlignment::Start: pElem->SetPosY(0); break;
		case UIAlignment::End: pElem->SetPosY(1 - pElem->GetSize().y); break;
		case UIAlignment::Center: pElem->SetPosY(0.5 - pElem->GetSize().y * 0.5);
		}
		switch (HorizontalAlign)
		{
		case UIAlignment::Start: pElem->SetPosX(0); break;
		case UIAlignment::End: pElem->SetPosX(1 - pElem->GetSize().x); break;
		case UIAlignment::Center: pElem->SetPosX(0.5 - pElem->GetSize().x * 0.5);
		}


		switch (Direction)
		{
		case  UIDirection::Horizontal:
		{
			pElem->SetPosX(fCurrentInDir);

			fCurrentInDir += pElem->GetSize().x;
			fCurrentLineHeight = std::max(fCurrentLineHeight, pElem->GetPos().y + pElem->GetSize().y);


			break;
		}
		case UIDirection::Vertical:
		{
			pElem->SetPosY(fCurrentInDir);
			fCurrentInDir += pElem->GetSize().y;
			fCurrentLineWidth = std::max(fCurrentLineWidth, pElem->GetPos().x + pElem->GetSize().x);


			break;
		}
		}
	}

}
void UIElement::Draw(sf::RenderWindow& _window)
{
	for (UIElement* pElem : Children)
		pElem->Draw(_window);

	if (bDrawDebug)
	{
		_window.draw(RenderRectangle);
	}
}
