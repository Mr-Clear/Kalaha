#include "SmartPlayer.h"

#include "Game/Board.h"

SmartPlayer::SmartPlayer(PlayerNumber playerNumber) : AbstractPlayer(playerNumber)
{ }

Pit SmartPlayer::selectHouse(const AbstractBoard &board) const
{
    std::vector<int> storeSeeds;
    for (const Pit &p : getOptions(board))
    {
        Board copy{board};
        copy.saw(p);
        storeSeeds.emplace_back(copy.seedCount({playerNumber(), copy.numberOfHouses() + 1}));
    }
    const int maxIndex = std::max_element(storeSeeds.begin(), storeSeeds.end()) - storeSeeds.begin() + 1;
    return {playerNumber(), maxIndex};
}
