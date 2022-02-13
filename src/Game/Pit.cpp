#include "Pit.h"

#include <cassert>

Pit::Pit(Player player, char number) :
    m_player{player},
    m_number{number}
{
    assert(number >= 1 && number <= 7);
}

bool Pit::operator==(const Pit &o) const
{
    return m_player == o.player() &&
           m_number == o.number();
}

Player Pit::player() const
{
    return m_player;
}

char Pit::number() const
{
    return m_number;
}

bool Pit::isHouse() const
{
    return m_number < 7;
}

bool Pit::isStore() const
{
    return m_number == 7;
}

bool Pit::isOverflow() const
{
    return m_overflow;
}

Pit &Pit::operator++()
{
    m_number++;
    if (m_number > 7)
    {
        m_number = 1;
        ++m_player;
        if (m_player == Player::One)
            m_overflow = true;
    }
    return *this;
}
