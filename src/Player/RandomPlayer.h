#pragma once

#include "Game/PlayerNumber.h"
#include "Player/AbstractPlayer.h"

class RandomPlayer : public AbstractPlayer
{
public:
    explicit RandomPlayer(const std::string &name);

    [[nodiscard]] Pit selectHouse(const AbstractBoard &board, PlayerNumber playerNumber) const override;
};

