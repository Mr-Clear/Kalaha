#include "PlayerNumber.h"

using PlayerNumber::One;
using PlayerNumber::Two;

const std::vector<PlayerNumber> ALL_PLAYERS = {One, Two};

PlayerNumber operator!(const PlayerNumber &p)
{
    return (p == One) ? Two : One;
}

PlayerNumber &operator++(PlayerNumber &p)
{
    p = !p;
    return p;
}

std::ostream &operator<<(std::ostream& os, PlayerNumber player)
{
    os << (player == One ? "Player One" : "Player Two");
    return os;
}
