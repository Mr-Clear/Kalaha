#pragma once

#include "Player/AbstractPlayer.h"

class SmartPlayer : public AbstractPlayer
{
public:
    [[nodiscard]] Pit selectHouse(const AbstractBoard &board, PlayerNumber playerNumber) const override;
};

