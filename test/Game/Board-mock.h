#pragma once

#include "Game/Board.h"

#include <gmock/gmock.h>

class MockBoard : public IBoard
{
public:
    MOCK_METHOD(int, numberOfHouses, (), (const, override));
    MOCK_METHOD(Pit, pit, (PlayerNumber player, int pitNumber), (const, override));
    MOCK_METHOD(Pit, house, (PlayerNumber player, int houseNumber), (const, override));
    MOCK_METHOD(Pit, store, (PlayerNumber player), (const, override));
    MOCK_METHOD(int, seedCount, (const Pit &pit), (const, override));
    MOCK_METHOD(std::optional<PlayerNumber>, saw, (const Pit &startPit), (override));
    MOCK_METHOD(std::optional<PlayerNumber>, moveRemainingSeedsToStore, (), (override));
    MOCK_METHOD(std::optional<Turn>, lastTurn, (), (const, override));
};

void prepareMockBoard(MockBoard &board, int numberOfHouses,  const std::initializer_list<int> &seedsPerPit);
