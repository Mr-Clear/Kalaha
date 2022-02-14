#include "ConsoleOutput.h"

#include <cassert>
#include <iomanip>
#include <iostream>

using std::endl, std::setw;

ConsoleOutput::ConsoleOutput(int maxCountWidth, std::ostream &stream) :
    m_width{maxCountWidth},
    m_stream{stream}
{
    assert(m_width >= 0);
}

void ConsoleOutput::output(const IBoard &board)
{
    // Top Border
    m_stream << "╔" << filler("═") << "╤";
    for (int i = 1; i <= board.numberOfHouses(); ++i)
        m_stream << filler("═") << "╤";
    m_stream << filler("═") << "╗" << endl;
    // Houses Player One
    m_stream << "║" << filler(" ") << "│";
    for (int i = board.numberOfHouses(); i >= 1; --i)
        m_stream << setw(m_width) << board.seedCount(board.house(Player::One, i)) << "│";
    m_stream << filler(" ") << "║" << endl;
    // Stores
    m_stream << "║" << setw(m_width) << board.seedCount(board.store(Player::One));
    m_stream << "├" << filler("─");
    for (int i = 2; i <= board.numberOfHouses(); ++i)
        m_stream << "┼" << filler("─");
    m_stream << "┤" << setw(m_width) << board.seedCount(board.store(Player::Two)) << "║" << endl;
    // Houses Player Two
    m_stream << "║" << filler(" ") << "│";
    for (int i = 1; i <= board.numberOfHouses(); ++i)
        m_stream << setw(m_width) << board.seedCount(board.house(Player::Two, i)) << "│";
    m_stream << filler(" ") << "║" << endl;
    // Bottom Border
    m_stream << "╚" << filler("═") << "╧";
    for (int i = 1; i <= board.numberOfHouses(); ++i)
        m_stream << filler("═") << "╧";
    m_stream << filler("═") << "╝" << endl;
}

std::string ConsoleOutput::filler(const std::string &character)
{
    std::string s;
    for (int i = 0; i < m_width; ++i)
        s += character;
    return s;
}
