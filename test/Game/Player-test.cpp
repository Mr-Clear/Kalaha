#include "Game/Player.h"

#include <gtest/gtest.h>

TEST(PlayerTest, notOperator)
{
    Player p = Player::One;
    EXPECT_EQ(!p,  Player::Two);
    EXPECT_EQ(p,  Player::One);
    p = !p;
    EXPECT_EQ(p,  Player::Two);
    EXPECT_EQ(!p,  Player::One);
    p = !p;
    EXPECT_EQ(!p,  Player::Two);
    EXPECT_EQ(p,  Player::One);
}

TEST(PlayerTest, incrementOperator)
{
    Player p = Player::One;
    EXPECT_EQ(p,  Player::One);
    ++p;
    EXPECT_EQ(p,  Player::Two);
    ++p;
    EXPECT_EQ(p,  Player::One);
    ++p;
    EXPECT_EQ(p,  Player::Two);
    ++p;
    EXPECT_EQ(p,  Player::One);
}
