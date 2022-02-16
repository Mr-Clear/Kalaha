#pragma once

#include "Game/PlayerNumber.h"
#include "Player/AbstractPlayer.h"

class RandomPlayer : public AbstractPlayer
{
public:
    RandomPlayer(PlayerNumber number);

    [[nodiscard]] Pit selectHouse(const AbstractBoard &board) const override;
};

