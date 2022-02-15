#pragma once

#include "Game/IPlayer.h"
#include "Game/Pit.h"

#include <gmock/gmock.h>

class MockPlayer : public IPlayer
{
public:
    MockPlayer(PlayerNumber number) :
        IPlayer{number}
    { }

    MOCK_METHOD(Pit, selectHouse, (const IBoard &board), (const, override));
};
