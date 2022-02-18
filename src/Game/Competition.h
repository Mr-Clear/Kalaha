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
        std::vector<int> winsPerPlayerAndDraw;
        std::optional<PlayerNumber> winner;

        friend auto operator<=>(const Outcome&, const Outcome&) = default;
    };

    Competition(const Rules &rules, const std::shared_ptr<AbstractPlayer> &playerOne,
                const std::shared_ptr<AbstractPlayer> &playerTwo, int rounds, AbstractOutput &output);

    const Rules m_rules;
    std::shared_ptr<AbstractPlayer> m_playerOne;
    std::shared_ptr<AbstractPlayer> m_playerTwo;
    const int m_rounds;
    AbstractOutput &m_output;

    Outcome run();
};
