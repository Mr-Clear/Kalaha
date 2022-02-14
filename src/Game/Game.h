#pragma once

#include "Game/Board.h"
#include "Game/IPlayer.h"

#include <map>
#include <memory>

class Output;

class Game
{
public:
    Game(int numberOfHouses, int startSeedsPerHouse, Output &output, std::map<PlayerNumber, std::shared_ptr<IPlayer>> &players);

    void start(PlayerNumber startPlayer);

private:
    Board m_board;
    Output &m_output;
    std::map<PlayerNumber, std::shared_ptr<IPlayer>> &m_players;
};

