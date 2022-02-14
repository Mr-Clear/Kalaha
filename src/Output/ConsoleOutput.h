#pragma once

#include "Output/Output.h"

#include <iostream>
#include <string>

/**
 * Output looks like:
 * ╔════╤════╤════╤════╤════╤════╤════╤════╗
 * ║    │( 5)│( 5)│( 5)│[ 0]│  4 │  4 │    ║
 * ║( 1)├────┼────┼────┼────┼────┼────┤  0 ║
 * ║    │  4 │  4 │  4 │  4 │  4 │  4 │    ║
 * ╚════╧════╧════╧════╧════╧════╧════╧════╝
 */
class ConsoleOutput : public Output
{
public:
    ConsoleOutput(int maxCountWidth = 2, std::ostream &stream = std::cout);
    void showBoard(const IBoard &board) override;
    void showTurn(int number, PlayerNumber player) override;
    void showWinner(const std::optional<PlayerNumber> &winner) override;

private:
    const int m_width;
    std::ostream &m_stream;

    std::string filler(const std::string &character);
    std::string printPit(const Pit &pit);
};
