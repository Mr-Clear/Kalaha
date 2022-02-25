#include "ConsoleOutput.h"

#include <cassert>
#include <cmath>
#include <iomanip>
#include <numeric>

using std::endl;
using std::setw;

ConsoleOutput::ConsoleOutput(int maxCountWidth, std::ostream &stream) :
    m_width{maxCountWidth},
    m_stream{stream}
{
    assert(m_width >= 0);
}

void ConsoleOutput::showNextGame(const AbstractPlayer &playerA, const AbstractPlayer &playerB)
{
    m_stream << "Game " << &playerA << " vs. " << &playerB << endl;
}

void ConsoleOutput::showBoard(const AbstractBoard &board)
{
    board.print(m_stream, m_width);
}

void ConsoleOutput::showTurn(int number, PlayerNumber player)
{
    m_stream << "Turn " << number << ", Player " << player << ":" << endl;
}

void ConsoleOutput::showWinner(const std::optional<PlayerNumber> &winner)
{
    m_stream << "Game Over!";
    if (winner)
        m_stream << " Winner is: " << winner.value() << endl;
    else
        m_stream << " It's a Draw!" << endl;
}

void ConsoleOutput::showTournamentEnd(const std::vector<Tournament::Outcome> &outcome)
{
    auto sorted = outcome;
    std::sort(sorted.begin(), sorted.end(), [ ] (const Tournament::Outcome &a, const Tournament::Outcome &b) {
        return std::make_pair(a.wins, a.totalSones) > std::make_pair(b.wins, b.totalSones);
    });
    int maxName = 6; // "Player"
    for (auto & i : sorted)
    {
        const int len = i.player->name().size();
        if (maxName < len)
            maxName = len;
    }
    m_stream << "Tournament ended. Winner is " << sorted.at(0).player->name() << "." << std::endl;
    m_stream << "╔" << rep(maxName, "═") << "╤═══════╤═══════╤═══════╤═══════╗" << endl;
    m_stream << "║" << rep(maxName - 6, " ") << "Player│   Wins│Defeats│  Draws│ Stones║" << endl;
    m_stream << "╟" << rep(maxName, "─") << "┼───────┼───────┼───────┼───────╢" << endl;
    for (const auto &o : sorted)
        m_stream << "║" << std::left << std::setw(maxName) << o.player->name() << std::right
                 << "│" << std::setw(7) << o.wins
                 << "│" << std::setw(7) << o.defeats
                 << "│" << std::setw(7) << o.draws
                 << "│" << std::setw(7) << o.totalSones << "║" << std::endl;
    m_stream << "╚" << rep(maxName, "═") << "╧═══════╧═══════╧═══════╧═══════╝" << endl;
}

std::string ConsoleOutput::rep(int n, const std::string &s)
{
    std::string out;
    for (int i = 0; i < n; ++i)
        out += s;
    return out;
}
