#pragma once

#include "Output/AbstractOutput.h"

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
class ConsoleOutput : public AbstractOutput
{
public:
    ConsoleOutput(int maxCountWidth = 2, std::ostream &stream = std::cout);
    void showNextGame(const AbstractPlayer &playerA, const AbstractPlayer &playerB) override;
    void showBoard(const AbstractBoard &board) override;
    void showTurn(int number, PlayerNumber player) override;
    void showWinner(const std::optional<PlayerNumber> &winner) override;
    void showTournamentEnd(const std::vector<Tournament::Outcome> &outcome) override;

private:
    const int m_width;
    std::ostream &m_stream;

    std::string printPit(const Pit &pit);
    std::string rep(int n, const std::string &s);
};
