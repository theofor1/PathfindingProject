#pragma once

#include <string>

class GameObject;

class IComponent
{
public:
	IComponent() = delete;
	IComponent(GameObject& gameObject);

	virtual ~IComponent();

	virtual void Start() = 0;

	virtual void Update(float DeltaTime) = 0;

	virtual void Destroy() = 0;

	virtual std::string GetComponentName() const = 0;

	bool NeedUpdate() const;

protected:
	GameObject& GetGameObject() const;
	bool HasUpdateFunction;

private:
	GameObject& ParentGameObject;
};
