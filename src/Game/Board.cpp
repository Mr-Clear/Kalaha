#include "Board.h"

#include <cassert>

Board::Board(const Rules &rules) :
    m_numberOfHouses{rules.numberOfHouses}
{
    for (const Pit &pit : *this)
    {
        m_seedNumbers.emplace_back(static_cast<int>(isHouse(pit)) * rules.startSeedsPerHouse);
    }
}

Board::Board(const AbstractBoard &o) :
    Board(Rules{o.numberOfHouses(), 0})
{
    m_seedNumbers.clear();
    for (const Pit &pit : *this)
        m_seedNumbers.emplace_back(o.seedCount(pit));
}

int Board::seedCount(const Pit &pit) const
{
    return m_seedNumbers.at(arrayIndex(pit));
}

bool Board::isHouse(const Pit &pit) const
{
    return pit.number() <= numberOfHouses();
}

bool Board::isStore(const Pit &pit) const
{
    return pit.number() == numberOfHouses() + 1;
}

bool Board::isPlayersStore(const Pit &pit, PlayerNumber player) const
{
    return isStore(pit) && player == pit.player();
}

Pit Board::oppositeHouse(const Pit &pit) const
{
    assert(isHouse(pit));
    return {!pit.player(), numberOfHouses() - pit.number() + 1};
}

Pit Board::nextPit(const Pit &pit) const
{
    int nr = pit.number() + 1;
    PlayerNumber p = pit.player();
    if (nr > m_numberOfHouses + 1)
    {
        nr = 1;
        ++p;
    }
    return {p, nr};
}

Pit Board::previousPit(const Pit &pit) const
{
    int nr = pit.number() - 1;
    PlayerNumber p = pit.player();
    if (nr < 1)
    {
        nr = numberOfHouses() + 1;
        ++p;
    }
    return {p, nr};
}

Pit Board::distributeSeeds(Pit pit, int seedCount)
{
    const PlayerNumber player = pit.player();
    while (seedCount > 0)
    {
        pit = nextPit(pit);
        if (!isPlayersStore(pit, !player))
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
    assert(isHouse(startPit));
    int seeds = seedCount(startPit);
    assert(seeds > 0);

    m_lastTurn = Turn{player, startPit, {}};

    clearSeedCount(startPit);

    const Pit endPit = distributeSeeds(startPit, seeds);

    checkAndHandleCapture(endPit, player);

    if (checkForGameEnd())
        return {};

    if (isPlayersStore(endPit, player))
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
        for (Pit p{player, 1}; isHouse(p); p = nextPit(p))
        {
            c += seedCount(p);
            clearSeedCount(p);
        }
        addSeeds({player, numberOfHouses() + 1}, c);
    }
    const auto result = seedCount({PlayerNumber::One, numberOfHouses() + 1}) <=> seedCount({PlayerNumber::Two, numberOfHouses() + 1});
    if (result > nullptr)
        return PlayerNumber::One;
    if (result < nullptr)
        return PlayerNumber::Two;
    return {};
}

Board::Iterator Board::begin() const
{
    return Iterator{numberOfHouses(), Pit{PlayerNumber::One, 1}, false};
}

Board::Iterator Board::end() const
{
    return Iterator{numberOfHouses(), Pit{PlayerNumber::Two, numberOfHouses() + 1}, true};
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

int Board::storeId() const
{
    return numberOfHouses() + 1;
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
    if (isHouse(pit) && pit.player() == player && seedCount(pit) == 1 && seedCount(oppositeHouse(pit)))
    {
        const Pit opposite = oppositeHouse(pit);
        const int capturedSeeds = seedCount(opposite) + 1;
        clearSeedCount(pit);
        clearSeedCount(opposite);
        addSeeds({player, numberOfHouses() + 1}, capturedSeeds);
    }
}

bool Board::checkForGameEnd() const
{
    for (PlayerNumber player : ALL_PLAYERS)
    {
        int c = 0;
        for (Pit p{player, 1}; isHouse(p); p = nextPit(p))
            c += seedCount(p);
        if (!c)
            return true;
    }
    return false;
}

Board::Iterator::Iterator(int numberOfHouses, const Pit &currentPit, bool end) :
    m_numberOfHouses{numberOfHouses},
    m_currentPit{currentPit},
    m_end{end}
{ }

Board::Iterator &Board::Iterator::operator++()
{
    if (m_currentPit == Pit{PlayerNumber::Two, m_numberOfHouses + 1})
    {
        m_end = true;
    }
    else
    {
        int nr = m_currentPit.number() + 1;
        PlayerNumber p = m_currentPit.player();
        if (nr > m_numberOfHouses + 1)
        {
            nr = 1;
            ++p;
        }
        m_currentPit = {p, nr};
    }

    return *this;
}

const Pit &Board::Iterator::operator*() const
{
    return m_currentPit;
}
