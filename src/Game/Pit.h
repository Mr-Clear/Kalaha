#pragma once

#include "Player.h"

class Pit
{
public:
    Pit(Player player, char number);

    bool operator==(const Pit &o) const;

    [[nodiscard]] Player player() const;
    [[nodiscard]] char number() const;

    [[nodiscard]] bool isHouse() const;
    [[nodiscard]] bool isStore() const;

    [[nodiscard]] bool isOverflow() const;

    Pit &operator++();

private:
    Player m_player;
    char m_number;
    bool m_overflow = false;
};

