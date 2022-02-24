#include "AiPlayer.h"

#include "Game/AbstractBoard.h"

#include <cassert>

#include <limits>

AiPlayer::AiPlayer(const std::string &name, const Ai &ai) :
    AbstractPlayer{name},
    m_ai{ai}
{ }

Pit AiPlayer::selectHouse(const AbstractBoard &board, PlayerNumber playerNumber) const
{
    assert(board.numberOfHouses() == m_ai.outputSize());
    std::vector<float> input;
    input.reserve(board.numberOfHouses());

    for (int i = 1; i <= board.numberOfHouses(); ++i)
        input.emplace_back(board.seedCount({playerNumber, i}));
    auto r = m_ai.calculate(input);

    for (int i = 0; i < board.numberOfHouses(); i++)
    {
        float maxV = -std::numeric_limits<float>::infinity();
        int maxi = 0;
        {
            for (int i = 0; i < r.size(); i++)
            {
                const float v = r[i];
                if (maxV < v)
                {
                    maxV = v;
                    maxi = i;
                }
            }
        }
        Pit p{playerNumber, maxi + 1};
        if (board.seedCount(p))
            return p;
        r[maxi] = -std::numeric_limits<float>::infinity();
    }
    assert(false);
}
