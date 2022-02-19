#pragma once

#include "Output/AbstractOutput.h"

class NullOutput : public AbstractOutput
{
public:
    void showNextGame(int) override { };
    void showBoard(const AbstractBoard &) override { }
    void showTurn(int, PlayerNumber) override { }
    void showWinner(const std::optional<PlayerNumber> &) override { }
    void showCompetitionEnd(const Competition::Outcome &) override { };
};
