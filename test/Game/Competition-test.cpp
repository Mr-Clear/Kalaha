#include "Game/Competition.h"

#include "../test/Game/Board-mock.h"
#include "../test/Player/Player-mock.h"

#include <gtest/gtest.h>

using PlayerNumber::One;
using PlayerNumber::Two;

TEST(CompetitionTest, a)
{
    MockPlayer playerA{One};
    MockPlayer playerB{Two};
    Competition c{{3, 2}, playerA, playerB};
    EXPECT_EQ(c.runOnce(), (Competition::Outcome{{5, 3}, One, 5}));
}
