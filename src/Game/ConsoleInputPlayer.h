#pragma once

#include "Game/IPlayer.h"

class ConsoleInputPlayer : public IPlayer
{
public:
    ConsoleInputPlayer(PlayerNumber number);

    [[nodiscard]] Pit selectHouse(const IBoard &board) const override;
};

