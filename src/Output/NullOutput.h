#pragma once

#include "Output/AbstractOutput.h"

class NullOutput : public AbstractOutput
{
public:
    void showBoard(const AbstractBoard &board) override { }
    void showTurn(int number, PlayerNumber player) override { }
    void showWinner(const std::optional<PlayerNumber> &winner) override { }
};
