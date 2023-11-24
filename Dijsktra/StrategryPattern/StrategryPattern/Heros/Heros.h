#pragma once

#include <iostream>
#include <memory>

enum class E_TypeHero;

struct IWayToFight
{
    virtual ~IWayToFight() = default;
    virtual void Combat() = 0;
};

struct FigthWithSword : IWayToFight
{
    void Combat() override
    {
        std::cout << "Fight with sword\n";
    }
};

struct FigthWithStick : IWayToFight
{
    void Combat() override
    {
        std::cout << "Fight with stick\n";
    }
};

class Heros
{
public:
    Heros();
    Heros(std::unique_ptr<IWayToFight> _IWayToFight);
    // Heros(E_TypeHero _TypeHero);
    virtual ~Heros() = default;

    virtual void Combat();
    virtual void Heal();

protected:
    std::unique_ptr<IWayToFight> m_WayToFight;

private:
    E_TypeHero TypeHero;
};
