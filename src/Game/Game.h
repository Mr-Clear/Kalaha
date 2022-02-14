#pragma once

#include "Game/Board.h"

class Output;

class Game
{
public:
    Game(int numberOfHouses, int startSeedsPerHouse, Output &output);

    void start();

private:
    Board m_board;
    Output &m_output;

};

