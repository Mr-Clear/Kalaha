#include "IPlayer.h"

#include "Game/Board.h"

#include <cassert>

IPlayer::IPlayer(PlayerNumber number) :
    m_number{number}
{ }

PlayerNumber IPlayer::playerNumber() const
{
    return m_number;
}

std::set<int> IPlayer::getOptions(const IBoard &board) const
{
    std::set<int> options;
    for (int i = 1; i <= board.numberOfHouses(); ++i)
        if (board.seedCount(board.house(m_number, i)))
    options.insert(i);
    assert(!options.empty());
    return options;
}
