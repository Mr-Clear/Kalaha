#include "SmartPlayer.h"

#include "Game/Board.h"

#include <cassert>

Pit SmartPlayer::selectHouse(const AbstractBoard &board, PlayerNumber playerNumber) const
{
    std::vector<int> storeSeeds;
    auto options = getOptions(board, playerNumber);
    for (int i = 1; i <= board.numberOfHouses(); i++)
    {
        Pit house{playerNumber, i};
        if (board.seedCount(house))
        {
            Board copy{board};
            copy.saw(house);
            storeSeeds.emplace_back(copy.seedCount({playerNumber, copy.numberOfHouses() + 1}));
        }
        else
        {
            storeSeeds.emplace_back(0);
        }
    }
    const int maxIndex = std::max_element(storeSeeds.begin(), storeSeeds.end()) - storeSeeds.begin() + 1;
    assert(board.seedCount({playerNumber, maxIndex}));
    return {playerNumber, maxIndex};
}
