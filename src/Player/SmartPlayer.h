#pragma once

#include "Player/AbstractPlayer.h"

class SmartPlayer : public AbstractPlayer
{
public:
    SmartPlayer(PlayerNumber playerNumber);

    [[nodiscard]] Pit selectHouse(const AbstractBoard &board) const override;
};

