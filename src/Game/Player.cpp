#include "Player.h"

Player operator!(Player &p)
{
    return (p == Player::One) ? Player::Two : Player::One;
}

Player &operator++(Player &p)
{
    p = !p;
    return p;
}
