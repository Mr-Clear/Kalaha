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

std::set<Pit> IPlayer::getOptions(const IBoard &board) const
{
    std::set<Pit> options;
    for (int i = 1; i <= board.numberOfHouses(); ++i)
    {
        const Pit p = board.house(m_number, i);
        if (board.seedCount(p))
            options.insert(p);
    }
    assert(!options.empty());
    return options;
}
