#include "Board.h"

#include <cassert>

Board::Board(int numberOfHouses, int startSeedsPerHouse) :
    m_numberOfHouses{numberOfHouses},
    m_seedNumbers{}
{
    for (Pit pit = this->pit(Player::One, 1); !pit.isOverflow(); ++pit)
        m_seedNumbers.emplace_back(static_cast<int>(pit.isHouse()) * startSeedsPerHouse);
}

int Board::seedCount(const Pit &pit) const
{
    return m_seedNumbers.at(arrayIndex(pit));
}

void Board::incrementSeedCount(const Pit &pit)
{
    m_seedNumbers.at(arrayIndex(pit))++;
}

void Board::clearSeedCount(const Pit &pit)
{
    m_seedNumbers.at(arrayIndex(pit)) = 0;
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
