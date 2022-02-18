#include "Pit.h"

#include "Game/Board.h"

#include <cassert>

Pit::Pit(PlayerNumber player, int number) :
    m_player{player},
    m_number{number}
{
    assert(number > 0);
}

PlayerNumber Pit::player() const
{
    return m_player;
}

int Pit::number() const
{
    return m_number;
}

std::size_t std::hash<Pit>::operator()(const Pit &pit) const
{
    return static_cast<int>(pit.player()) * 31337 + pit.number();
}

std::ostream& operator<<(std::ostream& os, const Pit& pit)
{
    return os << "Pit(" << pit.player() << ", " << pit.number() << ")";
}
