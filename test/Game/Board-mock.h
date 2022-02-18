#pragma once

#include "Game/Board.h"

#include <gmock/gmock.h>

class MockBoard : public AbstractBoard
{
public:
    MockBoard(int numberOfHouses,  const std::initializer_list<int> &seedsPerPit);

    MOCK_METHOD(int, numberOfHouses, (), (const, override));
    MOCK_METHOD(int, storeId, (), (const, override));
    MOCK_METHOD(int, seedCount, (const Pit &pit), (const, override));
    MOCK_METHOD(std::optional<PlayerNumber>, saw, (const Pit &startPit), (override));
    MOCK_METHOD(std::optional<PlayerNumber>, moveRemainingSeedsToStore, (), (override));
    MOCK_METHOD(std::optional<Turn>, lastTurn, (), (const, override));
};
