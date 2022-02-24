#include "Game.h"

#include "Output/AbstractOutput.h"

#include <cassert>

Game::Game(const Rules &rules, AbstractOutput &output, const std::array<std::shared_ptr<AbstractPlayer>, 2> &players) :
    Game(std::make_unique<Board>(rules), output, players)
{ }

Game::Game(std::unique_ptr<AbstractBoard> board, AbstractOutput &output, const std::array<std::shared_ptr<AbstractPlayer>, 2> &players) :
    m_board{std::move(board)},
    m_output{output},
    m_players{players}
{
    m_output.showBoard(*m_board);
}

Game::Outcome Game::start(PlayerNumber startPlayer)
{
    std::optional<PlayerNumber> playerNumber = startPlayer;
    int turn = 1;
    m_output.showTurn(turn, playerNumber.value());
    while(playerNumber)
    {
        std::shared_ptr<AbstractPlayer> &player = m_players[static_cast<int>(playerNumber.value())];
        Pit house = player->selectHouse(*m_board, playerNumber.value());
        assert(house.player() == playerNumber);
        playerNumber = m_board->saw(house);
        ++turn;
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
            return {{m_board->seedCount({PlayerNumber::One, m_board->storeId()}), m_board->seedCount({PlayerNumber::Two, m_board->storeId()})},
                    winner, turn};
        }
    }
    assert(false);
    return{};
}

std::ostream &operator<<(std::ostream &os, const std::optional<PlayerNumber> &p)
{
    if (p)
        return os << p.value();
    return os << "None";
}

std::ostream &operator<<(std::ostream &os, const Game::Outcome &o)
{
    return os << "Outcome(Winner: " << o.winner << ", Score: (" << o.seeds.first << " - " << o.seeds.second << "), Rounds: " << o.playedRounds << ")";
}
