#include "AbstractPlayer.h"

#include "Game/Board.h"

#include <cassert>

AbstractPlayer::AbstractPlayer(PlayerNumber number) :
    m_number{number}
{ }

PlayerNumber AbstractPlayer::playerNumber() const
{
    return m_number;
}

std::set<Pit> AbstractPlayer::getOptions(const AbstractBoard &board) const
{
    std::set<Pit> options;
    for (int i = 1; i <= board.numberOfHouses(); ++i)
    {
        const Pit p{m_number, i};
        if (board.seedCount(p))
            options.insert(p);
    }
    assert(!options.empty());
    return options;
}
