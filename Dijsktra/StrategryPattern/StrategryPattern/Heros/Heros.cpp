#include "Heros.h"
#include "TypeHero.h"

Heros::Heros() : m_WayToFight(nullptr)
{
    // TypeHero = E_TypeHero::WARRIOR;
}

Heros::Heros(std::unique_ptr<IWayToFight> _IWayToFight)
{
    //m_WayToFight = _IWayToFight;
    // TypeHero = _TypeHero;
}
// Heros::Heros(E_TypeHero _TypeHero)
// {
//     // TypeHero = _TypeHero;
// }

// Heros::~Heros() {
// }

void Heros::Combat()
{
    m_WayToFight->Combat();
}

void Heros::Heal()
{
}