#include "Pit.h"

#include "Game/Board.h"

bool Pit::operator==(const Pit &o) const
{
    return m_player == o.player() &&
           m_number == o.number();
}

Player Pit::player() const
{
    return m_player;
}

int Pit::number() const
{
    return m_number;
}

bool Pit::isHouse() const
{
    return m_number <= m_board.numberOfHouses();
}

bool Pit::isStore() const
{
    return m_number == m_board.numberOfHouses() + 1;
}

bool Pit::isOverflow() const
{
    return m_overflow;
}

Pit &Pit::operator++()
{
    m_number++;
    if (m_number > m_board.numberOfHouses() + 1)
    {
        m_number = 1;
        ++m_player;
        if (m_player == Player::One)
            m_overflow = true;
    }
    return *this;
}

Pit::Pit(const Board &board, Player player, int number) :
    m_board{board},
    m_player{player},
    m_number{number}
{ }
