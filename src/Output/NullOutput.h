#pragma once

#include "Output/AbstractOutput.h"

class NullOutput : public AbstractOutput
{
public:
    void showNextGame(const AbstractPlayer &, const AbstractPlayer &) override { };
    void showBoard(const AbstractBoard &) override { }
    void showTurn(int, PlayerNumber) override { }
    void showWinner(const std::optional<PlayerNumber> &) override { }
    void showTournamentEnd(const std::vector<Tournament::Outcome> &) override { };
};
