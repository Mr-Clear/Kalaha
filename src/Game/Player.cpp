#include "Player.h"

Player operator!(const Player &p)
{
    return (p == Player::One) ? Player::Two : Player::One;
}

Player &operator++(Player &p)
{
    p = !p;
    return p;
}
