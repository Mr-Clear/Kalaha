#include "Board.h"

#include <cassert>

Board::Board(const Rules &rules) :
    m_numberOfHouses{rules.numberOfHouses}
{
    for (Pit pit = this->pit(PlayerNumber::One, 1); !pit.isOverflow(); ++pit)
        m_seedNumbers.emplace_back(static_cast<int>(pit.isHouse()) * rules.startSeedsPerHouse);
}

Board::Board(const AbstractBoard &o) :
    Board(Rules{o.numberOfHouses(), 0})
{
    m_seedNumbers.clear();
    for (Pit pit = this->pit(PlayerNumber::One, 1); !pit.isOverflow(); ++pit)
        m_seedNumbers.emplace_back(o.seedCount(pit));
}

int Board::seedCount(const Pit &pit) const
{
    return m_seedNumbers.at(arrayIndex(pit));
}

Pit Board::distributeSeeds(Pit pit, int seedCount)
{
    const PlayerNumber player = pit.player();
    while (seedCount > 0)
    {
        ++pit;
        if (!pit.isPlayersStore(!player))
        {
            incrementSeedCount(pit);
            --seedCount;
        }
    }
    return pit;
}

std::optional<PlayerNumber> Board::saw(const Pit &startPit)
{
    assert(!checkForGameEnd());

    const PlayerNumber player = startPit.player();
    assert(startPit.isHouse());
    int seeds = seedCount(startPit);
    assert(seeds > 0);

    m_lastTurn = Turn{player, startPit};

    clearSeedCount(startPit);

    const Pit endPit = distributeSeeds(startPit, seeds);

    checkAndHandleCapture(endPit, player);

    if (checkForGameEnd())
        return {};

    if (endPit.isPlayersStore(player))
        return player;
    return !player;
}

std::optional<AbstractBoard::Turn> Board::lastTurn() const
{
    return m_lastTurn;
}

std::optional<PlayerNumber> Board::moveRemainingSeedsToStore()
{
    assert(checkForGameEnd());
    m_lastTurn = Turn{};
    for (PlayerNumber player : ALL_PLAYERS)
    {
        int c = 0;
        for (Pit p = house(player, 1); p.isHouse(); ++p)
        {
            c += seedCount(p);
            clearSeedCount(p);
        }
        addSeeds(store(player), c);
    }
    if (seedCount(store(PlayerNumber::One)) > seedCount(store(PlayerNumber::Two)))
        return PlayerNumber::One;
    if (seedCount(store(PlayerNumber::One)) < seedCount(store(PlayerNumber::Two)))
        return PlayerNumber::Two;
    return {};
}

Board::Board(const std::vector<int> &seedNumbers) :
    m_numberOfHouses{static_cast<int>(seedNumbers.size()) / 2 - 1},
    m_seedNumbers{seedNumbers}
{
    assert(!(seedNumbers.size() % 2));
}

int Board::numberOfHouses() const
{
    return m_numberOfHouses;
}

Pit Board::pit(PlayerNumber player, int pitNumber) const
{
    assert(pitNumber >= 1 && pitNumber <= numberOfHouses() + 1);
    return {*this, player, pitNumber};
}

Pit Board::house(PlayerNumber player, int houseNumber) const
{
    assert(houseNumber >= 1 && houseNumber <= numberOfHouses());
    return {*this, player, houseNumber};
}

Pit Board::store(PlayerNumber player) const
{
    return {*this, player, m_numberOfHouses + 1};
}

int Board::arrayIndex(const Pit &pit) const
{
    return static_cast<int>(pit.player()) * (m_numberOfHouses + 1) + pit.number() - 1;
}

void Board::incrementSeedCount(const Pit &pit)
{
    addSeeds(pit, 1);
}

void Board::addSeeds(const Pit &pit, int seedNumber)
{
    assert(seedNumber >= 0);
    if (seedNumber)
    {
        m_seedNumbers.at(arrayIndex(pit)) += seedNumber;
        if (m_lastTurn)
            m_lastTurn.value().changedPits.insert(pit);
    }
}

void Board::clearSeedCount(const Pit &pit)
{
    if(m_seedNumbers.at(arrayIndex(pit)))
    {
        m_seedNumbers.at(arrayIndex(pit)) = 0;
        if (m_lastTurn)
            m_lastTurn.value().changedPits.insert(pit);
    }
}

void Board::checkAndHandleCapture(const Pit &pit, PlayerNumber player)
{
    if (pit.isHouse() && pit.player() == player && seedCount(pit) == 1 && seedCount(pit.oppositeHouse()))
    {
        const Pit opposite = pit.oppositeHouse();
        const int capturedSeeds = seedCount(opposite) + 1;
        clearSeedCount(pit);
        clearSeedCount(opposite);
        addSeeds(store(player), capturedSeeds);
    }
}

bool Board::checkForGameEnd() const
{
    for (PlayerNumber player : ALL_PLAYERS)
    {
        int c = 0;
        for (Pit p = house(player, 1); p.isHouse(); ++p)
            c += seedCount(p);
        if (!c)
            return true;
    }
    return false;
}
