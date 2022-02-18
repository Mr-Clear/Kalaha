#include "Competition.h"

#include "Game/Game.h"
#include "Output/NullOutput.h"

#include <cassert>

Competition::Competition(const Rules &rules, const std::shared_ptr<AbstractPlayer> &playerOne,
                         const std::shared_ptr<AbstractPlayer> &playerTwo, int rounds, AbstractOutput &output):
    m_rules{rules},
    m_playerOne{playerOne},
    m_playerTwo{playerTwo},
    m_rounds{rounds},
    m_output{output}
{ }

Competition::Outcome Competition::run()
{
    PlayerNumber p = PlayerNumber::One;
    std::vector<int> wins{0, 0, 0};
    for (int i = 1; i <= m_rounds; i++)
    {
        Board b{m_rules};
        std::map<PlayerNumber, std::shared_ptr<AbstractPlayer>> m{{m_playerOne->playerNumber(), m_playerOne}, {m_playerTwo->playerNumber(), m_playerTwo}};
        Game g{m_rules, m_output, m};
        m_output.showNextGame(i);
        Game::Outcome o = g.start(p);
        if (o.winner == PlayerNumber::One)
            wins[0]++;
        else if (o.winner == PlayerNumber::Two)
            wins[1]++;
        else if (!o.winner)
            wins[2]++;
        else
            assert(false);
        ++p;
    }

    std::optional<PlayerNumber> winner;
    if (wins[0] > wins[1])
        winner = PlayerNumber::One;
    else if (wins[0] < wins[1])
        winner = PlayerNumber::Two;
    else
        winner = std::nullopt;

    const Competition::Outcome outcome{wins, winner};
    return outcome;
}
