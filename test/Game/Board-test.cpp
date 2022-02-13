#include "Game/Board.h"

#include <gtest/gtest.h>

TEST(BoardTest, constructor)
{
    Board b{11};
    EXPECT_EQ(b.stoneCount(Pit(Player::One, 1)), 11);
    EXPECT_EQ(b.stoneCount(Pit(Player::One, 2)), 11);
    EXPECT_EQ(b.stoneCount(Pit(Player::One, 3)), 11);
    EXPECT_EQ(b.stoneCount(Pit(Player::One, 4)), 11);
    EXPECT_EQ(b.stoneCount(Pit(Player::One, 5)), 11);
    EXPECT_EQ(b.stoneCount(Pit(Player::One, 6)), 11);
    EXPECT_EQ(b.stoneCount(Pit(Player::One, 7)), 0);
    EXPECT_EQ(b.stoneCount(Pit(Player::One, 1)), 11);
    EXPECT_EQ(b.stoneCount(Pit(Player::Two, 7)), 0);
}

TEST(BoardTest, incrementStoneCount)
{
    Board b{3};
    b.incrementStoneCount({Player::One, 1});
    EXPECT_EQ(b.stoneCount(Pit(Player::One, 1)), 4);
    b.incrementStoneCount({Player::One, 7});
    EXPECT_EQ(b.stoneCount(Pit(Player::One, 7)), 1);
    b.incrementStoneCount({Player::Two, 4});
    EXPECT_EQ(b.stoneCount(Pit(Player::Two, 4)), 4);
    b.incrementStoneCount({Player::Two, 7});
    EXPECT_EQ(b.stoneCount(Pit(Player::Two, 7)), 1);
}

TEST(BoardTest, clearStoneCount)
{
    Board b{3};
    b.clearStoneCount({Player::One, 1});
    EXPECT_EQ(b.stoneCount(Pit(Player::One, 1)), 0);
    b.clearStoneCount({Player::One, 7});
    EXPECT_EQ(b.stoneCount(Pit(Player::One, 7)), 0);
    b.clearStoneCount({Player::Two, 4});
    EXPECT_EQ(b.stoneCount(Pit(Player::Two, 4)), 0);
    b.clearStoneCount({Player::Two, 7});
    EXPECT_EQ(b.stoneCount(Pit(Player::Two, 7)), 0);
}
