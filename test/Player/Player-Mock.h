#pragma once

#include "Game/Pit.h"
#include "Player/AbstractPlayer.h"

#include <gmock/gmock.h>

class MockPlayer : public AbstractPlayer
{
public:
    MockPlayer(PlayerNumber number) :
        AbstractPlayer{number}
    { }

    MOCK_METHOD(Pit, selectHouse, (const AbstractBoard &board), (const, override));

    void defineSequence(const std::initializer_list<int> &sequence, AbstractBoard &board);
};
