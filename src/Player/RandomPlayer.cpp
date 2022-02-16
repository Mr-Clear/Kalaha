#include "RandomPlayer.h"

#include "Game/Board.h"
#include "Tools/Random.h"

#include <cassert>

RandomPlayer::RandomPlayer(PlayerNumber number) :
    AbstractPlayer{number}
{ }

Pit RandomPlayer::selectHouse(const AbstractBoard &board) const
{
    const std::set<Pit> options = getOptions(board);
    return *Tools::selectRandomItem(options.cbegin(), options.cend());
}
