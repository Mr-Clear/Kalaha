#pragma once

#include "Player/AbstractPlayer.h"

class ConsoleInputPlayer : public AbstractPlayer
{
public:
    explicit ConsoleInputPlayer(const std::string &name);

    [[nodiscard]] Pit selectHouse(const AbstractBoard &board, PlayerNumber playerNumber) const override;
};

