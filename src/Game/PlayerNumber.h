#pragma once

#include <cstdint>
#include <iostream>
#include <vector>

enum class PlayerNumber : char
{
    One,
    Two
};

extern const std::vector<PlayerNumber> ALL_PLAYERS;

PlayerNumber operator!(const PlayerNumber &p);
PlayerNumber &operator++(PlayerNumber &p);

std::ostream &operator<<(std::ostream& os, PlayerNumber player);
