#pragma once

#include "Game/Rules.h"
#include "Player/AbstractPlayer.h"

class Competition
{
public:
    struct Outcome
    {
        std::pair<int, int> seeds;
        PlayerNumber winner;
        int playedRounds;

        friend auto operator<=>(const Outcome&, const Outcome&) = default;
    };

    Competition(const Rules &rules, AbstractPlayer &playerOne, AbstractPlayer &playerTwo);

    Outcome runOnce();
};

std::ostream &operator<<(std::ostream &os, const Competition::Outcome &outcome);
