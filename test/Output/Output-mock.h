#pragma once

#include "Output/IOutput.h"

#include <gmock/gmock.h>

class MockOutput : public IOutput
{
public:
    MOCK_METHOD(void, showTurn, (int number, PlayerNumber player), (override));
    MOCK_METHOD(void, showBoard, (const IBoard &board), (override));
    MOCK_METHOD(void, showWinner, (const std::optional<PlayerNumber> &winner), (override));
};
