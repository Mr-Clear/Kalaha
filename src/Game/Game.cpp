#include "Game.h"

#include "Output/Output.h"

Game::Game(int numberOfHouses, int startSeedsPerHouse, Output &output) :
    m_board{numberOfHouses, startSeedsPerHouse},
    m_output{output}
{
    m_output.output(m_board);
}

void Game::start()
{

}
