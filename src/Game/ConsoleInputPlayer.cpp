#include "ConsoleInputPlayer.h"

#include "Board.h"
#include "Pit.h"

#include <iterator>
#include <sstream>

ConsoleInputPlayer::ConsoleInputPlayer(PlayerNumber number) :
    IPlayer{number}
{ }

Pit ConsoleInputPlayer::selectHouse(const IBoard &board) const
{
    const std::set<Pit> options = getOptions(board);
    std::set<int> optionNumbers;
    for (const Pit &p : options)
        optionNumbers.insert(p.number());
    int selected = 0;
    while (!optionNumbers.contains(selected))
    {
        std::cout << playerNumber() << ", select next house from ";
        bool needSeperator = false;
        for (const auto& option : options)
            std::cout << (needSeperator ? ", " : (needSeperator = true, " ")) << option;
        std::cout << ": ";
        std::cin >> selected;
    }
    return board.house(playerNumber(), selected);
}
