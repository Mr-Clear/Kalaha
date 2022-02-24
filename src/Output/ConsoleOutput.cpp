#include "ConsoleOutput.h"

#include <cassert>
#include <cmath>
#include <numeric>

using std::endl;

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

void ConsoleOutput::showCompetitionEnd(const std::vector<Competition::Outcome> &outcome)
{
    auto sorted = outcome;
    std::sort(sorted.begin(), sorted.end(), [ ] (const Competition::Outcome &a, const Competition::Outcome &b) {
        return std::make_pair(a.wins, a.totalSones) > std::make_pair(b.wins, b.totalSones);
    });
    m_stream << "Competition ended. " << " Winner is " << sorted.at(0).player->name() << std::endl;
}
