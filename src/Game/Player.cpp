#include "Player.h"

const std::vector<Player> ALL_PLAYERS = {Player::One, Player::Two};

Player operator!(const Player &p)
{
    return (p == Player::One) ? Player::Two : Player::One;
}

Player &operator++(Player &p)
{
    p = !p;
    return p;
}
