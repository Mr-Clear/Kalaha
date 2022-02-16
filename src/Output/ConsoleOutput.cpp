#include "ConsoleOutput.h"

#include <cassert>

using std::endl;

ConsoleOutput::ConsoleOutput(int maxCountWidth, std::ostream &stream) :
    m_width{maxCountWidth},
    m_stream{stream}
{
    assert(m_width >= 0);
}

void ConsoleOutput::showBoard(const IBoard &board)
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
