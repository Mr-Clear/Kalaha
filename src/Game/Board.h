#pragma once

#include "Game/Pit.h"
#include "Game/Player.h"

#include <vector>

class Board
{
public:
    Board(int numberOfHouses, int stones);

    [[nodiscard]] int numberOfHouses() const;
    [[nodiscard]] Pit pit(Player player, int pitNumber);
    [[nodiscard]] int stoneCount(const Pit &pit) const;
    void incrementStoneCount(const Pit &pit);
    void clearStoneCount(const Pit &pit);

private:
    const int m_numberOfHouses;
    std::vector<int> m_stoneValues;

    [[nodiscard]] int arrayIndex(const Pit &pit) const;
};

