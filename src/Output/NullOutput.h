#pragma once

#include "Output/AbstractOutput.h"

class NullOutput : public AbstractOutput
{
public:
    void showNextGame(int gameNr) override { };
    void showBoard(const AbstractBoard &board) override { }
    void showTurn(int number, PlayerNumber player) override { }
    void showWinner(const std::optional<PlayerNumber> &winner) override { }
    void showCompetitionEnd(const Competition::Outcome &outcome) override { };
};
