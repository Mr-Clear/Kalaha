#include "ConsoleInputPlayer.h"

#include "Game/Board.h"
#include "Game/Pit.h"

#include <iterator>
#include <sstream>

ConsoleInputPlayer::ConsoleInputPlayer(const std::string &name) :
    AbstractPlayer{name}
{ }

Pit ConsoleInputPlayer::selectHouse(const AbstractBoard &board, PlayerNumber playerNumber) const
{
    const std::set<Pit> options = getOptions(board, playerNumber);
    std::set<int> optionNumbers;
    for (const Pit &p : options)
        optionNumbers.insert(p.number());
    int selected = 0;
    while (!optionNumbers.contains(selected))
    {
        std::cout << playerNumber << ", select next house from ";
        bool needSeperator = false;
        for (const auto& option : options)
            std::cout << (needSeperator ? ", " : (needSeperator = true, " ")) << option;
        std::cout << ": ";
        std::cin >> selected;
    }
    return {playerNumber, selected};
}
