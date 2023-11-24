#include <iostream>
#include <memory>

template<typename DerivedType>
struct IWayToFight
{
    virtual ~IWayToFight() = default;
    void fight()
    {
        auto& derived = static_cast<DerivedType&>(*this);
        derived.fight();
    }
};

struct FightWithSword : IWayToFight<FightWithSword>
{
    void fight()
    {
        std::cout << "Fight with sword" << std::endl;
    }
};

struct BaseHero
{
    virtual ~BaseHero() = default;
};

template<typename... Behaviors>
struct Hero : public Behaviors..., BaseHero
{
};

int main()
{
    using Warrior = Hero<FightWithSword>;
    Warrior w;
    w.fight();

    return 0;
}