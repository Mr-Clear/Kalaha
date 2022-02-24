#pragma once

#include "Output/AbstractOutput.h"

#include <gmock/gmock.h>

class MockOutput : public AbstractOutput
{
public:
    MOCK_METHOD(void, showNextGame, (const AbstractPlayer &playerA, const AbstractPlayer &playerB), (override));
    MOCK_METHOD(void, showTurn, (int number, PlayerNumber player), (override));
    MOCK_METHOD(void, showBoard, (const AbstractBoard &board), (override));
    MOCK_METHOD(void, showWinner, (const std::optional<PlayerNumber> &winner), (override));
    MOCK_METHOD(void, showCompetitionEnd, (const Competition::Outcome &outcome), (override));
};
