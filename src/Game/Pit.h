#pragma once

#include "PlayerNumber.h"

#include <gtest/gtest_prod.h>

class IBoard;

class Pit
{
public:
    Pit(const Pit &o);
    Pit &operator=(const Pit &o);
    bool operator==(const Pit &o) const;

    [[nodiscard]] const IBoard &board() const;
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
    FRIEND_TEST(GameTest, mocked);

    Pit(const IBoard &board, PlayerNumber player, int number);

    const IBoard &m_board;
    PlayerNumber m_player;
    int m_number;
    bool m_overflow = false;
};

namespace std {
template <> struct hash<Pit>
{
  size_t operator()(const Pit &pit) const
  {
    return static_cast<int>(pit.player()) * 31337 + pit.number();
  }
};
}

