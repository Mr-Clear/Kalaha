#pragma once

#include "Game/Board.h"

class AbstractOutput
{
public:
    virtual ~AbstractOutput() = default;

    virtual void showTurn(int number, PlayerNumber player) = 0;
    virtual void showBoard(const AbstractBoard &board) = 0;
    virtual void showWinner(const std::optional<PlayerNumber> &winner) = 0;
};

