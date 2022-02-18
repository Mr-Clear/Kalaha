#include "AbstractBoard.h"

#include <iomanip>
#include <iostream>

namespace {
std::string filler(const std::string &character, int width)
{
    std::string s;
    for (int i = 0; i < width + 2; ++i)
        s += character;
    return s;
}
}

void AbstractBoard::print(std::ostream &stream, int intWidth) const
{
    // Top Border
    stream << "╔" << filler("═", intWidth) << "╤";
    for (int i = 1; i <= numberOfHouses(); ++i)
        stream << filler("═", intWidth) << "╤";
    stream << filler("═", intWidth) << "╗" << std::endl;
    // Houses Player One
    stream << "║" << filler(" ", intWidth) << "│";
    for (int i = numberOfHouses(); i >= 1; --i)
        stream << format({PlayerNumber::One, i}, intWidth) << "│";
    stream << filler(" ", intWidth) << "║" << std::endl;
    // Stores
    stream << "║" << format({PlayerNumber::One, numberOfHouses() + 1}, intWidth);
    stream << "├" << filler("─", intWidth);
    for (int i = 2; i <= numberOfHouses(); ++i)
        stream << "┼" << filler("─", intWidth);
    stream << "┤" << format({PlayerNumber::Two, numberOfHouses() + 1}, intWidth) << "║" << std::endl;
    // Houses Player Two
    stream << "║" << filler(" ", intWidth) << "│";
    for (int i = 1; i <= numberOfHouses(); ++i)
        stream << format({PlayerNumber::Two, i}, intWidth) << "│";
    stream << filler(" ", intWidth) << "║" << std::endl;
    // Bottom Border
    stream << "╚" << filler("═", intWidth) << "╧";
    for (int i = 1; i <= numberOfHouses(); ++i)
        stream << filler("═", intWidth) << "╧";
    stream << filler("═", intWidth) << "╝" << std::endl;
}

std::string AbstractBoard::format(const Pit& pit, int width) const
{
    std::stringstream ss;
    std::string brackets = "  ";

    if (lastTurn())
    {
        if (lastTurn().value().selectedPit == pit)
            brackets = "[]";
        else if(lastTurn().value().changedPits.contains(pit))
            brackets = "()";
    }
    ss << brackets[0] << std::setw(width) << seedCount(pit) << brackets[1];
    return ss.str();
}
