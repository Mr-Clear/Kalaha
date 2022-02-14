#include "ConsoleOutput.h"

#include <cassert>
#include <iomanip>
#include <iostream>

using std::endl, std::setw;


namespace {
std::ostream &operator<<(std::ostream& os, const Pit& pit)
{
    const int width = os.width();
    os.width(0);
    std::string brackets = "  ";

    const IBoard &board = pit.board();
    if (board.lastTurn())
    {
        if (board.lastTurn().value().selectedPit == pit)
            brackets = "[]";
        else if(board.lastTurn().value().changedPits.contains(pit))
            brackets = "()";
    }
    os << brackets[0] << setw(width) << board.seedCount(pit) << brackets[1];
    return os;
}
} // namespace

ConsoleOutput::ConsoleOutput(int maxCountWidth, std::ostream &stream) :
    m_width{maxCountWidth},
    m_stream{stream}
{
    assert(m_width >= 0);
}

void ConsoleOutput::showBoard(const IBoard &board)
{
    // Top Border
    m_stream << "╔" << filler("═") << "╤";
    for (int i = 1; i <= board.numberOfHouses(); ++i)
        m_stream << filler("═") << "╤";
    m_stream << filler("═") << "╗" << endl;
    // Houses Player One
    m_stream << "║" << filler(" ") << "│";
    for (int i = board.numberOfHouses(); i >= 1; --i)
        m_stream << setw(m_width) << board.house(PlayerNumber::One, i) << "│";
    m_stream << filler(" ") << "║" << endl;
    // Stores
    m_stream << "║" << setw(m_width) << board.store(PlayerNumber::One);
    m_stream << "├" << filler("─");
    for (int i = 2; i <= board.numberOfHouses(); ++i)
        m_stream << "┼" << filler("─");
    m_stream << "┤" << setw(m_width) << board.store(PlayerNumber::Two) << "║" << endl;
    // Houses Player Two
    m_stream << "║" << filler(" ") << "│";
    for (int i = 1; i <= board.numberOfHouses(); ++i)
        m_stream << setw(m_width) << board.house(PlayerNumber::Two, i) << "│";
    m_stream << filler(" ") << "║" << endl;
    // Bottom Border
    m_stream << "╚" << filler("═") << "╧";
    for (int i = 1; i <= board.numberOfHouses(); ++i)
        m_stream << filler("═") << "╧";
    m_stream << filler("═") << "╝" << endl;
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

std::string ConsoleOutput::filler(const std::string &character)
{
    std::string s;
    for (int i = 0; i < m_width + 2; ++i)
        s += character;
    return s;
}
