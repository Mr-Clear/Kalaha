#include "Game/PlayerNumber.h"

#include <gtest/gtest.h>

TEST(PlayerTest, notOperator)
{
    PlayerNumber p = PlayerNumber::One;
    EXPECT_EQ(!p,  PlayerNumber::Two);
    EXPECT_EQ(p,  PlayerNumber::One);
    p = !p;
    EXPECT_EQ(p,  PlayerNumber::Two);
    EXPECT_EQ(!p,  PlayerNumber::One);
    p = !p;
    EXPECT_EQ(!p,  PlayerNumber::Two);
    EXPECT_EQ(p,  PlayerNumber::One);
}

TEST(PlayerTest, incrementOperator)
{
    PlayerNumber p = PlayerNumber::One;
    EXPECT_EQ(p,  PlayerNumber::One);
    ++p;
    EXPECT_EQ(p,  PlayerNumber::Two);
    ++p;
    EXPECT_EQ(p,  PlayerNumber::One);
    ++p;
    EXPECT_EQ(p,  PlayerNumber::Two);
    ++p;
    EXPECT_EQ(p,  PlayerNumber::One);
}
