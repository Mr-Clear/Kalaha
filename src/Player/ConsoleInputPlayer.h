#pragma once

#include "Player/AbstractPlayer.h"

class ConsoleInputPlayer : public AbstractPlayer
{
public:
    ConsoleInputPlayer(PlayerNumber number);

    [[nodiscard]] Pit selectHouse(const AbstractBoard &board) const override;
};

