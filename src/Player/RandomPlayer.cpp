#include "RandomPlayer.h"

#include "Game/Board.h"
#include "Tools/Random.h"

#include <cassert>

RandomPlayer::RandomPlayer(const std::string &name) :
    AbstractPlayer{name}
{ }

Pit RandomPlayer::selectHouse(const AbstractBoard &board, PlayerNumber playerNumber) const
{
    const std::set<Pit> options = getOptions(board, playerNumber);
    return *Tools::selectRandomItem(options.cbegin(), options.cend());
}
