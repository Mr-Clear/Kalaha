#include "PlayerNumber.h"

const std::vector<PlayerNumber> ALL_PLAYERS = {PlayerNumber::One, PlayerNumber::Two};

PlayerNumber operator!(const PlayerNumber &p)
{
    return (p == PlayerNumber::One) ? PlayerNumber::Two : PlayerNumber::One;
}

PlayerNumber &operator++(PlayerNumber &p)
{
    p = !p;
    return p;
}
