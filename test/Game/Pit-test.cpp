#include "Game/Pit.h"

#include <gtest/gtest.h>

TEST(PitTest, constructor)
{
    EXPECT_DEATH(Pit(Player::One, 0), "");
    EXPECT_DEATH(Pit(Player::One, 8), "");
    EXPECT_DEATH(Pit(Player::One, -1), "");
    EXPECT_DEATH(Pit(Player::Two, 0), "");
    EXPECT_DEATH(Pit(Player::Two, 8), "");
    EXPECT_DEATH(Pit(Player::Two, -1), "");
}

TEST(PitTest, isHouse)
{
    EXPECT_EQ(true, Pit(Player::One, 1).isHouse());
    EXPECT_EQ(true, Pit(Player::One, 6).isHouse());
    EXPECT_EQ(false, Pit(Player::One, 7).isHouse());
    EXPECT_EQ(true, Pit(Player::Two, 2).isHouse());
    EXPECT_EQ(true, Pit(Player::Two, 5).isHouse());
    EXPECT_EQ(false, Pit(Player::Two, 7).isHouse());
}

TEST(PitTest, isStore)
{
    EXPECT_EQ(false, Pit(Player::One, 1).isStore());
    EXPECT_EQ(false, Pit(Player::One, 6).isStore());
    EXPECT_EQ(true, Pit(Player::One, 7).isStore());
    EXPECT_EQ(false, Pit(Player::Two, 2).isStore());
    EXPECT_EQ(false, Pit(Player::Two, 5).isStore());
    EXPECT_EQ(true, Pit(Player::Two, 7).isStore());
}

TEST(PitTest, incrementOperator)
{
    Pit a{Player::One, 1};
    EXPECT_EQ(a, Pit(Player::One, 1));
    ++a;
    EXPECT_EQ(a, Pit(Player::One, 2));
    ++a;
    EXPECT_EQ(a, Pit(Player::One, 3));
    ++a;
    EXPECT_EQ(a, Pit(Player::One, 4));
    ++a;
    EXPECT_EQ(a, Pit(Player::One, 5));
    ++a;
    EXPECT_EQ(a, Pit(Player::One, 6));
    ++a;
    EXPECT_EQ(a, Pit(Player::One, 7));
    ++a;
    EXPECT_EQ(a, Pit(Player::Two, 1));
    ++a;
    EXPECT_EQ(a, Pit(Player::Two, 2));
    ++a;
    EXPECT_EQ(a, Pit(Player::Two, 3));
    ++a;
    EXPECT_EQ(a, Pit(Player::Two, 4));
    ++a;
    EXPECT_EQ(a, Pit(Player::Two, 5));
    ++a;
    EXPECT_EQ(a, Pit(Player::Two, 6));
    ++a;
    EXPECT_EQ(a, Pit(Player::Two, 7));
    ++a;
    EXPECT_EQ(a, Pit(Player::One, 1));
    ++a;
    EXPECT_EQ(a, Pit(Player::One, 2));
}
