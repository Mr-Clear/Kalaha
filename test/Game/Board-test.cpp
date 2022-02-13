#include "Game/Board.h"

#include <gtest/gtest.h>

TEST(BoardTest, createPitDeathTest)
{
    Board b{5, 1};
    EXPECT_DEATH(Pit p = b.pit(Player::One, 0), "");
    EXPECT_DEATH(Pit p = b.pit(Player::One, 7), "");
    EXPECT_DEATH(Pit p = b.pit(Player::One, -1), "");
    EXPECT_DEATH(Pit p = b.pit(Player::Two, 0), "");
    EXPECT_DEATH(Pit p = b.pit(Player::Two, 7), "");
    EXPECT_DEATH(Pit p = b.pit(Player::Two, -1), "");
}

TEST(BoardTest, constructor)
{
    Board b{6, 11};
    EXPECT_EQ(b.seedCount(b.pit(Player::One, 1)), 11);
    EXPECT_EQ(b.seedCount(b.pit(Player::One, 2)), 11);
    EXPECT_EQ(b.seedCount(b.pit(Player::One, 3)), 11);
    EXPECT_EQ(b.seedCount(b.pit(Player::One, 4)), 11);
    EXPECT_EQ(b.seedCount(b.pit(Player::One, 5)), 11);
    EXPECT_EQ(b.seedCount(b.pit(Player::One, 6)), 11);
    EXPECT_EQ(b.seedCount(b.pit(Player::One, 7)), 0);
    EXPECT_EQ(b.seedCount(b.pit(Player::One, 1)), 11);
    EXPECT_EQ(b.seedCount(b.pit(Player::Two, 7)), 0);
}

TEST(BoardTest, incrementSeedCount)
{
    Board b{4, 3};
    b.incrementSeedCount(b.pit(Player::One, 1));
    EXPECT_EQ(b.seedCount(b.pit(Player::One, 1)), 4);
    b.incrementSeedCount(b.pit(Player::One, 5));
    EXPECT_EQ(b.seedCount(b.pit(Player::One, 5)), 1);
    b.incrementSeedCount(b.pit(Player::Two, 4));
    EXPECT_EQ(b.seedCount(b.pit(Player::Two, 4)), 4);
    b.incrementSeedCount(b.pit(Player::Two, 5));
    EXPECT_EQ(b.seedCount(b.pit(Player::Two, 5)), 1);
}

TEST(BoardTest, clearSeedCount)
{
    Board b{9, 3};
    b.clearSeedCount(b.pit(Player::One, 1));
    EXPECT_EQ(b.seedCount(b.pit(Player::One, 1)), 0);
    b.clearSeedCount(b.pit(Player::One, 10));
    EXPECT_EQ(b.seedCount(b.pit(Player::One, 10)), 0);
    b.clearSeedCount(b.pit(Player::Two, 7));
    EXPECT_EQ(b.seedCount(b.pit(Player::Two, 7)), 0);
    b.clearSeedCount(b.pit(Player::Two, 10));
    EXPECT_EQ(b.seedCount(b.pit(Player::Two, 10)), 0);
}
