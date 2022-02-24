#include "AbstractPlayer.h"

#include "Game/Board.h"

#include <cassert>

std::set<Pit> AbstractPlayer::getOptions(const AbstractBoard &board, PlayerNumber playerNumber) const
{
    std::set<Pit> options;
    for (int i = 1; i <= board.numberOfHouses(); ++i)
    {
        const Pit p{playerNumber, i};
        if (board.seedCount(p))
            options.insert(p);
    }
    assert(!options.empty());
    return options;
}
