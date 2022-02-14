#pragma once

#include <cstdint>
#include <vector>

enum class Player : char
{
    One,
    Two
};

extern const std::vector<Player> ALL_PLAYERS;

Player operator!(const Player &p);
Player &operator++(Player &p);
