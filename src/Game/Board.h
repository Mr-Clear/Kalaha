#pragma once

#include "Game/Pit.h"
#include "Game/Player.h"

#include <vector>

class Board
{
public:
    Board(int numberOfHouses, int startSeedsPerHouse);

    [[nodiscard]] int numberOfHouses() const;
    [[nodiscard]] Pit pit(Player player, int pitNumber) const;
    [[nodiscard]] Pit house(Player player, int houseNumber) const;
    [[nodiscard]] Pit store(Player player) const;
    [[nodiscard]] int seedCount(const Pit &pit) const;

    Player saw(const Pit &startPit);

private:
    const int m_numberOfHouses;
    std::vector<int> m_seedNumbers;

    [[nodiscard]] int arrayIndex(const Pit &pit) const;
    void incrementSeedCount(const Pit &pit);
    void addSeeds(const Pit &pit, int seedNumber);
    void clearSeedCount(const Pit &pit);
};

