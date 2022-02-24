#pragma once

#include "AI/Ai.h"
#include "Player/AbstractPlayer.h"

class AiPlayer : public AbstractPlayer
{
public:
    explicit AiPlayer(const std::string &name, const Ai &ai);

    [[nodiscard]] Pit selectHouse(const AbstractBoard &board, PlayerNumber playerNumber) const override;

private:
    Ai m_ai;
};
