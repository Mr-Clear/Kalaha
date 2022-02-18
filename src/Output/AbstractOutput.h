#pragma once

#include "Game/Board.h"
#include "Game/Competition.h"

class AbstractOutput
{
public:
    virtual ~AbstractOutput() = default;

    virtual void showNextGame(int gameNr) = 0;
    virtual void showTurn(int number, PlayerNumber player) = 0;
    virtual void showBoard(const AbstractBoard &board) = 0;
    virtual void showWinner(const std::optional<PlayerNumber> &winner) = 0;
    virtual void showCompetitionEnd(const Competition::Outcome &outcome) = 0;
};

