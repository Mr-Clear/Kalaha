#pragma once

#include "Game/Pit.h"
#include "Game/Player.h"

#include <array>

class Board
{
public:
    Board(int stones);

    int stoneCount(const Pit &pit);
    void incrementStoneCount(const Pit &pit);
    void clearStoneCount(const Pit &pit);

private:
    std::array<int, 14> m_stoneValues;

    int arrayIndex(const Pit &pit);
};

