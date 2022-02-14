#pragma once

#include "Game/IPlayer.h"
#include "Game/PlayerNumber.h"

class RandomPlayer : public IPlayer
{
public:
    RandomPlayer(PlayerNumber number);

    [[nodiscard]] Pit selectHouse(const IBoard &board) const override;

private:
    PlayerNumber m_number;
};

