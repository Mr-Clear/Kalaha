#pragma once

#include "PlayerNumber.h"

#include <gtest/gtest_prod.h>

class IBoard;

class Pit
{
public:
    bool operator==(const Pit &o) const;

    [[nodiscard]] PlayerNumber player() const;
    [[nodiscard]] int number() const;

    [[nodiscard]] bool isHouse() const;
    [[nodiscard]] bool isStore() const;
    [[nodiscard]] bool isPlayersStore(PlayerNumber player) const;
    [[nodiscard]] Pit oppositeHouse() const;

    [[nodiscard]] bool isOverflow() const;

    Pit &operator++();

private:
    friend class Board;
    FRIEND_TEST(ConsoleOutputTest, mocked);
    Pit(const IBoard &board, PlayerNumber player, int number);

    const IBoard &m_board;
    PlayerNumber m_player;
    int m_number;
    bool m_overflow = false;
};

