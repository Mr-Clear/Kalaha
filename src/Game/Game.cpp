#include "Game.h"

#include "Output/Output.h"

#include <cassert>

Game::Game(int numberOfHouses, int startSeedsPerHouse, Output &output, std::map<PlayerNumber, std::shared_ptr<IPlayer>> &players) :
    m_board{numberOfHouses, startSeedsPerHouse},
    m_output{output},
    m_players{players}
{
    m_output.showBoard(m_board);
}

void Game::start(PlayerNumber startPlayer)
{
    std::optional<PlayerNumber> playerNumber = startPlayer;
    int turn = 1;
    m_output.showTurn(turn, playerNumber.value());
    while(playerNumber)
    {
        std::shared_ptr<IPlayer> &player = m_players[playerNumber.value()];
        Pit house = player->selectHouse(m_board);
        assert(house.player() == playerNumber);
        playerNumber = m_board.saw(house);
        turn++;
        m_output.showBoard(m_board);
        if (playerNumber)
        {
            m_output.showTurn(turn, playerNumber.value());
        }
        else
        {
            auto winner = m_board.moveRemainingSeedsToStore();
            m_output.showWinner(winner);
            m_output.showBoard(m_board);
        }
    }
}
