#include "Board.h"

#include <cassert>

Board::Board(int numberOfHouses, int startStonesPerHouse) :
    m_numberOfHouses{numberOfHouses},
    m_stoneValues{}
{
    for (Pit pit = this->pit(Player::One, 1); !pit.isOverflow(); ++pit)
        m_stoneValues.emplace_back(static_cast<int>(pit.isHouse()) * startStonesPerHouse);
}

int Board::stoneCount(const Pit &pit) const
{
    return m_stoneValues.at(arrayIndex(pit));
}

void Board::incrementStoneCount(const Pit &pit)
{
    m_stoneValues.at(arrayIndex(pit))++;
}

void Board::clearStoneCount(const Pit &pit)
{
    m_stoneValues.at(arrayIndex(pit)) = 0;
}

int Board::numberOfHouses() const
{
    return m_numberOfHouses;
}

Pit Board::pit(Player player, int pitNumber)
{
    assert(pitNumber >= 1 && pitNumber <= numberOfHouses() + 1);
    return {*this, player, pitNumber};
}

int Board::arrayIndex(const Pit &pit) const
{
    return static_cast<int>(pit.player()) * (m_numberOfHouses + 1) + pit.number() - 1;
}
