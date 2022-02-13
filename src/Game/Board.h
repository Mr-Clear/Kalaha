#pragma once

#include "Game/Pit.h"
#include "Game/Player.h"

#include <vector>

class Board
{
public:
    Board(int numberOfHouses, int startSeedsPerHouse);

    [[nodiscard]] int numberOfHouses() const;
    [[nodiscard]] Pit pit(Player player, int pitNumber);
    [[nodiscard]] int seedCount(const Pit &pit) const;
    void incrementSeedCount(const Pit &pit);
    void clearSeedCount(const Pit &pit);

private:
    const int m_numberOfHouses;
    std::vector<int> m_seedNumbers;

    [[nodiscard]] int arrayIndex(const Pit &pit) const;
};

