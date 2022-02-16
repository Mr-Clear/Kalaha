#pragma once

#include "PlayerNumber.h"

#include <gtest/gtest_prod.h>

class AbstractBoard;

class Pit
{
public:
    Pit(const AbstractBoard &board, PlayerNumber player, int number);
    Pit(const Pit &o);
    Pit &operator=(const Pit &o);
    bool operator==(const Pit &o) const;
    bool operator<(const Pit &o) const;

    [[nodiscard]] const AbstractBoard &board() const;
    [[nodiscard]] PlayerNumber player() const;
    [[nodiscard]] int number() const;

    [[nodiscard]] bool isHouse() const;
    [[nodiscard]] bool isStore() const;
    [[nodiscard]] bool isPlayersStore(PlayerNumber player) const;
    [[nodiscard]] Pit oppositeHouse() const;

    [[nodiscard]] bool isOverflow() const;

    Pit &operator++();
    Pit &operator--();

private:

    const AbstractBoard &m_board;
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

std::ostream& operator<<(std::ostream& os, const Pit& pit);
