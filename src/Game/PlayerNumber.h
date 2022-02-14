#pragma once

#include <cstdint>
#include <vector>

enum class PlayerNumber : char
{
    One,
    Two
};

extern const std::vector<PlayerNumber> ALL_PLAYERS;

PlayerNumber operator!(const PlayerNumber &p);
PlayerNumber &operator++(PlayerNumber &p);
