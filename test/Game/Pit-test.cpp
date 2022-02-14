#include "Game/Board.h"

#include <gtest/gtest.h>

TEST(PitTest, isHouse)
{
    Board b{7, 2};
    EXPECT_EQ(true, b.pit(PlayerNumber::One, 1).isHouse());
    EXPECT_EQ(true, b.pit(PlayerNumber::One, 7).isHouse());
    EXPECT_EQ(false, b.pit(PlayerNumber::One, 8).isHouse());
    EXPECT_EQ(true, b.pit(PlayerNumber::Two, 2).isHouse());
    EXPECT_EQ(true, b.pit(PlayerNumber::Two, 5).isHouse());
    EXPECT_EQ(false, b.pit(PlayerNumber::Two, 8).isHouse());

    EXPECT_EQ(false, b.store(PlayerNumber::One).isHouse());
    EXPECT_EQ(false, b.store(PlayerNumber::Two).isHouse());
}

TEST(PitTest, isStore)
{
    Board b{5, 2};
    EXPECT_EQ(false, b.pit(PlayerNumber::One, 1).isStore());
    EXPECT_EQ(false, b.pit(PlayerNumber::One, 5).isStore());
    EXPECT_EQ(true, b.pit(PlayerNumber::One, 6).isStore());
    EXPECT_EQ(false, b.pit(PlayerNumber::Two, 2).isStore());
    EXPECT_EQ(false, b.pit(PlayerNumber::Two, 4).isStore());
    EXPECT_EQ(true, b.pit(PlayerNumber::Two, 6).isStore());

    EXPECT_EQ(true, b.store(PlayerNumber::One).isStore());
    EXPECT_EQ(true, b.store(PlayerNumber::Two).isStore());
}

TEST(PitTest, oppositeHouse)
{
    Board b{7, 6};
    EXPECT_EQ(b.house(PlayerNumber::One, 1), b.house(PlayerNumber::Two, 7).oppositeHouse());
    EXPECT_EQ(b.house(PlayerNumber::One, 7), b.house(PlayerNumber::Two, 1).oppositeHouse());
    EXPECT_EQ(b.house(PlayerNumber::One, 4), b.house(PlayerNumber::Two, 4).oppositeHouse());
}

TEST(PitTest, incrementOperator)
{
    Board b{3, 2};
    Pit a = b.house(PlayerNumber::One, 1);
    EXPECT_EQ(a, b.house(PlayerNumber::One, 1));
    ++a;
    EXPECT_EQ(a, b.house(PlayerNumber::One, 2));
    ++a;
    EXPECT_EQ(a, b.house(PlayerNumber::One, 3));
    ++a;
    EXPECT_EQ(a, b.store(PlayerNumber::One));
    ++a;
    EXPECT_EQ(a, b.house(PlayerNumber::Two, 1));
    ++a;
    EXPECT_EQ(a, b.house(PlayerNumber::Two, 2));
    ++a;
    EXPECT_EQ(a, b.house(PlayerNumber::Two, 3));
    ++a;
    EXPECT_EQ(a, b.store(PlayerNumber::Two));
    ++a;
    EXPECT_EQ(a, b.house(PlayerNumber::One, 1));
    ++a;
    EXPECT_EQ(a, b.house(PlayerNumber::One, 2));
}
