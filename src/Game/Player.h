#pragma once

#include <cstdint>

enum class Player : char
{
    One,
    Two
};

Player operator!(Player &p);
Player &operator++(Player &p);
