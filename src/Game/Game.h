#pragma once

#include "Game/Board.h"
#include "Player/AbstractPlayer.h"

#include <map>
#include <memory>

class AbstractOutput;

class Game
{
public:
    Game(int numberOfHouses, int startSeedsPerHouse, AbstractOutput &output, std::map<PlayerNumber, std::shared_ptr<AbstractPlayer>> &players);

    void start(PlayerNumber startPlayer);

private:
    std::unique_ptr<AbstractBoard> m_board;
    AbstractOutput &m_output;
    std::map<PlayerNumber, std::shared_ptr<AbstractPlayer>> &m_players;

    FRIEND_TEST(GameTest, mocked);
    Game(std::unique_ptr<AbstractBoard> board, AbstractOutput &output, std::map<PlayerNumber, std::shared_ptr<AbstractPlayer>> &players);
};

