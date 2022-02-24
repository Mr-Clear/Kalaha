#pragma once

#include "Player/AbstractPlayer.h"

class SmartPlayer : public AbstractPlayer
{
public:
    explicit SmartPlayer(const std::string &name);

    [[nodiscard]] Pit selectHouse(const AbstractBoard &board, PlayerNumber playerNumber) const override;
};

