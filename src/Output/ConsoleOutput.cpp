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

void ConsoleOutput::showNextGame(int gameNr)
{
    m_stream << "Game Number: " << gameNr << endl;
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

void ConsoleOutput::showCompetitionEnd(const Competition::Outcome &outcome)
{
    m_stream << "Competition ended. ";
    if (outcome.winner)
        m_stream << " Winner is " << outcome.winner.value();
    else
        m_stream << " It's a Draw";
    const int totalGames = std::accumulate(outcome.winsPerPlayerAndDraw.cbegin(), outcome.winsPerPlayerAndDraw.cend(), 0);
    m_stream << " with " << outcome.winsPerPlayerAndDraw[0] << " (" << std::round(outcome.winsPerPlayerAndDraw[0] * 100. / totalGames) << "%) wins for " << PlayerNumber::One;
    m_stream << ", " << outcome.winsPerPlayerAndDraw[1] << " (" << std::round(outcome.winsPerPlayerAndDraw[1] * 100. / totalGames) << "%) wins for " << PlayerNumber::Two;
    m_stream << " and " << outcome.winsPerPlayerAndDraw[2] << " (" << std::round(outcome.winsPerPlayerAndDraw[2] * 100. / totalGames) << "%) draws." << std::endl;
}
