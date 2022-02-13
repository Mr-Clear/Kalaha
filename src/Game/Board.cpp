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

Player Board::saw(const Pit &startPit)
{
    assert(startPit.isHouse());
    int seeds = seedCount(startPit);
    assert(seeds > 0);
    clearSeedCount(startPit);

    Pit pit = startPit;
    Player player = pit.player();
    while (seeds > 0)
    {
        ++pit;
        if (pit.isHouse() || pit.player() == player)
        {
            incrementSeedCount(pit);
            --seeds;
        }
    }

    if (pit.isHouse() && pit.player() == player && seedCount(pit) == 1)
    {
        const Pit opposite = pit.oppositeHouse();
        const int capturedSeeds = seedCount(opposite) + 1;
        clearSeedCount(pit);
        clearSeedCount(opposite);
        addSeeds(store(player), capturedSeeds);
    }

    if (pit.isStore() && pit.player() == player)
        return player;
    return !player;
}

int Board::numberOfHouses() const
{
    return m_numberOfHouses;
}

Pit Board::pit(Player player, int pitNumber) const
{
    assert(pitNumber >= 1 && pitNumber <= numberOfHouses() + 1);
    return {*this, player, pitNumber};
}

Pit Board::house(Player player, int houseNumber) const
{
    assert(houseNumber >= 1 && houseNumber <= numberOfHouses());
    return {*this, player, houseNumber};
}

Pit Board::store(Player player) const
{
    return {*this, player, m_numberOfHouses + 1};
}

int Board::arrayIndex(const Pit &pit) const
{
    return static_cast<int>(pit.player()) * (m_numberOfHouses + 1) + pit.number() - 1;
}

void Board::incrementSeedCount(const Pit &pit)
{
    m_seedNumbers.at(arrayIndex(pit))++;
}

void Board::addSeeds(const Pit &pit, int seedNumber)
{
    m_seedNumbers.at(arrayIndex(pit)) += seedNumber;
}

void Board::clearSeedCount(const Pit &pit)
{
    m_seedNumbers.at(arrayIndex(pit)) = 0;
}
