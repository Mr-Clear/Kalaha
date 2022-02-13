#include "Board.h"


Board::Board(int stones) :
    m_stoneValues()
{
    Pit p{Player::One, 1};

    for (Pit pit{Player::One, 1}; !pit.isOverflow(); ++pit)
        if (pit.isHouse())
            m_stoneValues.at(arrayIndex(pit)) = stones;
}

int Board::stoneCount(const Pit &pit)
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

int Board::arrayIndex(const Pit &pit)
{
    return static_cast<int>(pit.player()) * 7 + pit.number() - 1;
}
