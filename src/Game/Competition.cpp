#include "Competition.h"

#include "Game/Game.h"
#include "Output/NullOutput.h"

#include <cassert>

Competition::Competition(const Rules &rules, const std::vector<std::shared_ptr<AbstractPlayer> > &players, int rounds, AbstractOutput &output):
    m_rules{rules},
    m_players{players},
    m_rounds{rounds},
    m_output{output}
{ }

std::vector<Competition::Outcome> Competition::run()
{
    std::vector<Competition::Outcome> outcome;
    outcome.reserve(m_players.size());
    for (const auto &p : m_players)
        outcome.emplace_back(p);
    for (int i = 0; i < m_players.size(); i++)
    {
        const auto &playerOne = m_players.at(i);

        for (int j = 0; j < m_players.size(); j++)
        {
            if (i == j)
             continue;

            const auto &playerTwo = m_players.at(j);

            Game g{m_rules, m_output, std::array<std::shared_ptr<AbstractPlayer>, 2>{playerOne, playerTwo}};
            m_output.showNextGame(*playerOne, *playerTwo);
            Game::Outcome o = g.start();

            outcome[i].totalSones += o.seeds.first;
            outcome[j].totalSones += o.seeds.second;
            if (o.winner == PlayerNumber::One)
            {
                outcome[i].wins++;
                outcome[j].defeats++;
            }
            else if (o.winner == PlayerNumber::Two)
            {
                outcome[i].defeats++;
                outcome[j].wins++;
            }
            else if (!o.winner)
            {
                outcome[i].draws++;
                outcome[j].draws++;
            }
            else
                assert(false);
        }
    }

    return outcome;
}
