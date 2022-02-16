#include "RandomPlayer.h"

#include "Game/Board.h"
#include "Tools/Random.h"

#include <cassert>

RandomPlayer::RandomPlayer(PlayerNumber number) :
    IPlayer{number}
{ }

Pit RandomPlayer::selectHouse(const IBoard &board) const
{
    const std::set<Pit> options = getOptions(board);
    return *Tools::selectRandomItem(options.cbegin(), options.cend());
}
