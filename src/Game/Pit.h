#pragma once

#include "Player.h"

class Board;

class Pit
{
public:
    bool operator==(const Pit &o) const;

    [[nodiscard]] Player player() const;
    [[nodiscard]] int number() const;

    [[nodiscard]] bool isHouse() const;
    [[nodiscard]] bool isStore() const;
    [[nodiscard]] Pit oppositeHouse() const;

    [[nodiscard]] bool isOverflow() const;

    Pit &operator++();

private:
    friend class Board;
    Pit(const Board &board, Player player, int number);

    const Board &m_board;
    Player m_player;
    int m_number;
    bool m_overflow = false;
};

