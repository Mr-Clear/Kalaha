#pragma once

#include "Output/Output.h"

#include <iostream>
#include <string>

/**
 * Output looks like:
 * ╔══╤══╤══╤══╤══╤══╤══╤══╗
 * ║  │ 4│ 4│ 4│ 4│ 4│ 4│  ║
 * ║ 0├──┼──┼──┼──┼──┼──┤ 0║
 * ║  │ 4│ 4│ 4│ 4│ 4│ 4│  ║
 * ╚══╧══╧══╧══╧══╧══╧══╧══╝
 */

class ConsoleOutput : public Output
{
public:
    ConsoleOutput(int maxCountWidth = 2, std::ostream &stream = std::cout);
    void output(const IBoard &board) override;

private:
    const int m_width;
    std::ostream &m_stream;

    std::string filler(const std::string &character);
    std::string printPit(const Pit &pit);
};
