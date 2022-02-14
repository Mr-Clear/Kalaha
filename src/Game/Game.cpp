#include "Game.h"

#include "Output/Output.h"

#include <cassert>

Game::Game(int numberOfHouses, int startSeedsPerHouse, Output &output, std::map<PlayerNumber, std::shared_ptr<IPlayer>> &players) :
    m_board{numberOfHouses, startSeedsPerHouse},
    m_output{output},
    m_players{players}
{
    m_output.output(m_board);
}

void Game::start(PlayerNumber startPlayer)
{
    std::optional<PlayerNumber> playerNumber = startPlayer;
    while(playerNumber)
    {
        std::shared_ptr<IPlayer> &player = m_players[playerNumber.value()];
        Pit house = player->selectHouse(m_board);
        assert(house.player() == playerNumber);
        playerNumber = m_board.saw(house);
        m_output.output(m_board);
    }
}
