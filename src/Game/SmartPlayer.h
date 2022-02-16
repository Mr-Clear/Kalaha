#pragma once

#include "Game/IPlayer.h"

class SmartPlayer : public IPlayer
{
public:
    SmartPlayer(PlayerNumber playerNumber);
    [[nodiscard]] Pit selectHouse(const IBoard &board) const override;
};

