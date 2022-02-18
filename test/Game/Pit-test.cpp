#include "Game/Board.h"

#include <gtest/gtest.h>

TEST(PitTest, constructorDeathTest)
{
    EXPECT_DEATH(Pit(PlayerNumber::One, 0), "");
    EXPECT_DEATH(Pit(PlayerNumber::Two, 0), "");
    EXPECT_DEATH(Pit(PlayerNumber::One, -1), "");
}
