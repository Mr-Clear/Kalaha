#include "Game/Board.h"

#include <gtest/gtest.h>

using PlayerNumber::One;
using PlayerNumber::Two;

TEST(PitTest, isHouse)
{
    Board b{7, 2};
    EXPECT_EQ(true, b.pit(One, 1).isHouse());
    EXPECT_EQ(true, b.pit(One, 7).isHouse());
    EXPECT_EQ(false, b.pit(One, 8).isHouse());
    EXPECT_EQ(true, b.pit(Two, 2).isHouse());
    EXPECT_EQ(true, b.pit(Two, 5).isHouse());
    EXPECT_EQ(false, b.pit(Two, 8).isHouse());

    EXPECT_EQ(false, b.store(One).isHouse());
    EXPECT_EQ(false, b.store(Two).isHouse());
}

TEST(PitTest, isStore)
{
    Board b{5, 2};
    EXPECT_EQ(false, b.pit(One, 1).isStore());
    EXPECT_EQ(false, b.pit(One, 5).isStore());
    EXPECT_EQ(true, b.pit(One, 6).isStore());
    EXPECT_EQ(false, b.pit(Two, 2).isStore());
    EXPECT_EQ(false, b.pit(Two, 4).isStore());
    EXPECT_EQ(true, b.pit(Two, 6).isStore());

    EXPECT_EQ(true, b.store(One).isStore());
    EXPECT_EQ(true, b.store(Two).isStore());
}

TEST(PitTest, oppositeHouse)
{
    Board b{7, 6};
    EXPECT_EQ(b.house(One, 1), b.house(Two, 7).oppositeHouse());
    EXPECT_EQ(b.house(One, 7), b.house(Two, 1).oppositeHouse());
    EXPECT_EQ(b.house(One, 4), b.house(Two, 4).oppositeHouse());
}

TEST(PitTest, incrementOperator)
{
    Board b{3, 2};
    Pit a = b.house(One, 1);
    EXPECT_EQ(a, b.house(One, 1));
    ++a;
    EXPECT_EQ(a, b.house(One, 2));
    ++a;
    EXPECT_EQ(a, b.house(One, 3));
    ++a;
    EXPECT_EQ(a, b.store(One));
    ++a;
    EXPECT_EQ(a, b.house(Two, 1));
    ++a;
    EXPECT_EQ(a, b.house(Two, 2));
    ++a;
    EXPECT_EQ(a, b.house(Two, 3));
    ++a;
    EXPECT_EQ(a, b.store(Two));
    ++a;
    EXPECT_EQ(a, b.house(One, 1));
    ++a;
    EXPECT_EQ(a, b.house(One, 2));
}
