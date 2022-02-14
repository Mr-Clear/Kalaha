#include "RandomPlayer.h"

#include "Game/Board.h"
#include "Tools/Random.h"

#include <cassert>

RandomPlayer::RandomPlayer(PlayerNumber number) :
    m_number{number}
{ }

Pit RandomPlayer::selectHouse(const IBoard &board) const
{
    std::vector<int> options;
    for (int i = 1; i <= board.numberOfHouses(); ++i)
        if (board.seedCount(board.house(m_number, i)))
            options.push_back(i);
    assert(!options.empty());
    return board.house(m_number, *Tools::selectRandomItem(options.cbegin(), options.cend()));
}
