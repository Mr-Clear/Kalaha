#pragma once

#include "Game/Pit.h"
#include "Player/AbstractPlayer.h"

#include <gmock/gmock.h>

class MockPlayer : public AbstractPlayer
{
public:
    MOCK_METHOD(Pit, selectHouse, (const AbstractBoard &board, PlayerNumber playerNumber), (const, override));

    void defineSequence(PlayerNumber playerNumber, const std::initializer_list<int> &sequence);
    void defineSequence(const std::initializer_list<std::pair<PlayerNumber, int>> &sequence);
};
