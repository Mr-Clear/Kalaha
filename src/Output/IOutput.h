#pragma once

#include "Game/Board.h"

class IOutput
{
public:
    virtual ~IOutput() = default;

    virtual void showTurn(int number, PlayerNumber player) = 0;
    virtual void showBoard(const IBoard &board) = 0;
    virtual void showWinner(const std::optional<PlayerNumber> &winner) = 0;
};

