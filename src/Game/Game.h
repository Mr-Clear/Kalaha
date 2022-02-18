#pragma once

#include "Game/Board.h"
#include "Player/AbstractPlayer.h"

#include <map>
#include <memory>

class AbstractOutput;

class Game
{
public:
    Game(const Rules &rules, AbstractOutput &output, std::map<PlayerNumber, std::shared_ptr<AbstractPlayer>> &players);

    struct Outcome
    {
        std::pair<int, int> seeds;
        std::optional<PlayerNumber> winner;
        int playedRounds;

        friend auto operator<=>(const Outcome&, const Outcome&) = default;
    };
    Outcome start(PlayerNumber startPlayer = PlayerNumber::One);

private:
    std::unique_ptr<AbstractBoard> m_board;
    AbstractOutput &m_output;
    std::map<PlayerNumber, std::shared_ptr<AbstractPlayer>> &m_players;

    FRIEND_TEST(GameTest, mocked);
    Game(std::unique_ptr<AbstractBoard> board, AbstractOutput &output, std::map<PlayerNumber, std::shared_ptr<AbstractPlayer>> &players);
};

std::ostream &operator<<(std::ostream &os, const Game::Outcome &outcome);
std::ostream &operator<<(std::ostream &os, const std::optional<PlayerNumber> &player);
