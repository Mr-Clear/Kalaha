#include "Game/PlayerNumber.h"

#include <gtest/gtest.h>

using PlayerNumber::One;
using PlayerNumber::Two;

TEST(PlayerTest, notOperator)
{
    PlayerNumber p = One;
    EXPECT_EQ(!p, Two);
    EXPECT_EQ(p, One);
    p = !p;
    EXPECT_EQ(p,Two);
    EXPECT_EQ(!p, One);
    p = !p;
    EXPECT_EQ(!p, Two);
    EXPECT_EQ(p, One);
}

TEST(PlayerTest, incrementOperator)
{
    PlayerNumber p = One;
    EXPECT_EQ(p, One);
    ++p;
    EXPECT_EQ(p, Two);
    ++p;
    EXPECT_EQ(p, One);
    ++p;
    EXPECT_EQ(p, Two);
    ++p;
    EXPECT_EQ(p, One);
}
