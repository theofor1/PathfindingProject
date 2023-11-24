#include "Component.h"

Component::Component(Component *parent) : parentComponent(nullptr)
{
    setParent(parent);
}

Component::~Component()
{
    setParent(nullptr);

    for (const auto *component : ChildsComponent)
    {
        delete component;
    }
    ChildsComponent.clear();
}

void Component::setParent(Component *parent)
{
    if (parentComponent)
        parentComponent->removeComponent(this);

    parentComponent = parent;

    if (!parentComponent)
        return;

    parent->ChildsComponent.push_back(this);
}

void Component::addComponent(Component *component)
{
    if (!component)
        return;

    if (hasComponent(component))
        return;

    ChildsComponent.push_back(component);
}

void Component::removeComponent(Component *componentToRemove)
{
    if (!componentToRemove)
        return;

    if (!hasComponent(componentToRemove))
        return;

    int index = 0;

    for (const auto *component : ChildsComponent)
    {
        if (componentToRemove == component)
        {
            break;
        }
        index++;
    }
    ChildsComponent.erase(ChildsComponent.begin() + index);
}

bool Component::hasComponent(Component *componentToCheck)
{
    if (!componentToCheck)
        return true;

    for (const Component *component : ChildsComponent)
    {
        if (componentToCheck == component)
        {
            return true;
        }
    }
    return false;
}
