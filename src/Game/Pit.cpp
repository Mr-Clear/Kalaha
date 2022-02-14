#include "Pit.h"

#include "Game/Board.h"

#include <cassert>

Pit::Pit(const Pit &o) = default;

Pit &Pit::operator=(const Pit &o)
{
    assert(&m_board == &o.m_board);
    m_player = o.m_player;
    m_number = o.m_number;
    m_overflow = o.m_overflow;
    return *this;
}

bool Pit::operator==(const Pit &o) const
{
    return m_player == o.player() &&
            m_number == o.number();
}

const IBoard &Pit::board() const
{
    return m_board;
}

PlayerNumber Pit::player() const
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

bool Pit::isPlayersStore(PlayerNumber p) const
{
    return isStore() && p == player();
}

Pit Pit::oppositeHouse() const
{
    assert(isHouse());
    return m_board.house(!m_player, m_board.numberOfHouses() - m_number + 1);
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
        if (m_player == PlayerNumber::One)
            m_overflow = true;
    }
    return *this;
}

Pit::Pit(const IBoard &board, PlayerNumber player, int number) :
    m_board{board},
    m_player{player},
    m_number{number}
{ }
