#include "Player/SmartPlayer.h"

#include "../test/Game/Board-mock.h"

#include <gtest/gtest.h>

using PlayerNumber::One;
using PlayerNumber::Two;

TEST(SmartPlayerTest, evaluateStoreGain)
{
    SmartPlayer player{One};
    MockBoard board{6, {1, 1, 1, 1, 1, 1, 0}};
    EXPECT_EQ(player.selectHouse(board), Pit(One, 6));
}

TEST(SmartPlayerTest, evaluateCaptureGain)
{
    SmartPlayer player{One};
    MockBoard board{6, {1, 2, 1, 0, 1, 1, 0, 5, 6, 7}};
    EXPECT_EQ(player.selectHouse(board), Pit(One, 2));
}
