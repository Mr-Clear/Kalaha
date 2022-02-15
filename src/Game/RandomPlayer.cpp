#include "RandomPlayer.h"

#include "Game/Board.h"
#include "Tools/Random.h"

#include <cassert>

RandomPlayer::RandomPlayer(PlayerNumber number) :
    IPlayer{number}
{ }

Pit RandomPlayer::selectHouse(const IBoard &board) const
{
    const std::set<int> options = getOptions(board);
    return board.house(playerNumber(), *Tools::selectRandomItem(options.cbegin(), options.cend()));
}
