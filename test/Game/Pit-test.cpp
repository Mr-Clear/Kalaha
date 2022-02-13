#include "Game/Board.h"

#include <gtest/gtest.h>

TEST(PitTest, isHouse)
{
    Board b{7, 2};
    EXPECT_EQ(true, b.pit(Player::One, 1).isHouse());
    EXPECT_EQ(true, b.pit(Player::One, 7).isHouse());
    EXPECT_EQ(false, b.pit(Player::One, 8).isHouse());
    EXPECT_EQ(true, b.pit(Player::Two, 2).isHouse());
    EXPECT_EQ(true, b.pit(Player::Two, 5).isHouse());
    EXPECT_EQ(false, b.pit(Player::Two, 8).isHouse());
}

TEST(PitTest, isStore)
{
    Board b{5, 2};
    EXPECT_EQ(false, b.pit(Player::One, 1).isStore());
    EXPECT_EQ(false, b.pit(Player::One, 5).isStore());
    EXPECT_EQ(true, b.pit(Player::One, 6).isStore());
    EXPECT_EQ(false, b.pit(Player::Two, 2).isStore());
    EXPECT_EQ(false, b.pit(Player::Two, 4).isStore());
    EXPECT_EQ(true, b.pit(Player::Two, 6).isStore());
}

TEST(PitTest, incrementOperator)
{
    Board b{3, 2};
    Pit a = b.pit(Player::One, 1);
    EXPECT_EQ(a, b.pit(Player::One, 1));
    ++a;
    EXPECT_EQ(a, b.pit(Player::One, 2));
    ++a;
    EXPECT_EQ(a, b.pit(Player::One, 3));
    ++a;
    EXPECT_EQ(a, b.pit(Player::One, 4));
    ++a;
    EXPECT_EQ(a, b.pit(Player::Two, 1));
    ++a;
    EXPECT_EQ(a, b.pit(Player::Two, 2));
    ++a;
    EXPECT_EQ(a, b.pit(Player::Two, 3));
    ++a;
    EXPECT_EQ(a, b.pit(Player::Two, 4));
    ++a;
    EXPECT_EQ(a, b.pit(Player::One, 1));
    ++a;
    EXPECT_EQ(a, b.pit(Player::One, 2));
}
