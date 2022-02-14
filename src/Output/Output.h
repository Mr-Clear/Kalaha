#pragma once

#include "Game/Board.h"

class Output
{
public:
    virtual ~Output() = default;

    virtual void output(const IBoard &board) = 0;
};

