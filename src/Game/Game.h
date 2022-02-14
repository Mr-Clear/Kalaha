#pragma once

#include "Game/Board.h"
#include "Game/IPlayer.h"

#include <map>
#include <memory>

class IOutput;

class Game
{
public:
    Game(int numberOfHouses, int startSeedsPerHouse, IOutput &output, std::map<PlayerNumber, std::shared_ptr<IPlayer>> &players);

    void start(PlayerNumber startPlayer);

private:
    std::unique_ptr<IBoard> m_board;
    IOutput &m_output;
    std::map<PlayerNumber, std::shared_ptr<IPlayer>> &m_players;

    FRIEND_TEST(GameTest, mocked);
    Game(std::unique_ptr<IBoard> board, IOutput &output, std::map<PlayerNumber, std::shared_ptr<IPlayer>> &players);
};

