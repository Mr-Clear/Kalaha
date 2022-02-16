#include "Game.h"

#include "Output/AbstractOutput.h"

#include <cassert>

Game::Game(int numberOfHouses, int startSeedsPerHouse, AbstractOutput &output, std::map<PlayerNumber, std::shared_ptr<AbstractPlayer>> &players) :
    Game(std::make_unique<Board>(numberOfHouses, startSeedsPerHouse), output, players)
{ }

Game::Game(std::unique_ptr<AbstractBoard> board, AbstractOutput &output, std::map<PlayerNumber, std::shared_ptr<AbstractPlayer> > &players) :
    m_board{std::move(board)},
    m_output{output},
    m_players{players}
{
    m_output.showBoard(*m_board);
}

void Game::start(PlayerNumber startPlayer)
{
    std::optional<PlayerNumber> playerNumber = startPlayer;
    int turn = 1;
    m_output.showTurn(turn, playerNumber.value());
    while(playerNumber)
    {
        std::shared_ptr<AbstractPlayer> &player = m_players[playerNumber.value()];
        Pit house = player->selectHouse(*m_board);
        assert(house.player() == playerNumber);
        playerNumber = m_board->saw(house);
        turn++;
        m_output.showBoard(*m_board);
        if (playerNumber)
        {
            m_output.showTurn(turn, playerNumber.value());
        }
        else
        {
            auto winner = m_board->moveRemainingSeedsToStore();
            m_output.showWinner(winner);
            m_output.showBoard(*m_board);
        }
    }
}
