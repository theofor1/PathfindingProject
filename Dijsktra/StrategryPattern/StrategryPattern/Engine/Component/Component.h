#pragma once

#include <vector>

class Component
{
public:
    Component(Component *parent = nullptr);
    ~Component();

    void setParent(Component *parent);
    void addComponent(Component *child);
    void removeComponent(Component *componentToRemove);
    bool hasComponent(Component *componentToCheck);

private:
    std::vector<Component *> ChildsComponent;
    Component *parentComponent;
};
