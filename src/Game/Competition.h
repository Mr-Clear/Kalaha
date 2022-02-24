#pragma once

#include "Game/Rules.h"
#include "Player/AbstractPlayer.h"

#include <memory>
#include <optional>

class AbstractOutput;

class Competition
{
public:
    struct Outcome
    {
        std::shared_ptr<AbstractPlayer> player;
        int wins = 0;
        int defeats = 0;
        int draws = 0;
        int totalSones = 0;

        friend auto operator<=>(const Outcome&, const Outcome&) = default;
    };

    Competition(const Rules &rules, const std::vector<std::shared_ptr<AbstractPlayer>> &players,
                int rounds, AbstractOutput &output);

    const Rules m_rules;
    std::vector<std::shared_ptr<AbstractPlayer>> m_players;
    const int m_rounds;
    AbstractOutput &m_output;

    std::vector<Competition::Outcome> run();
};
