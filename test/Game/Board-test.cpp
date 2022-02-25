#include "Game/Board.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using PlayerNumber::One;
using PlayerNumber::Two;

using testing::ElementsAre;

namespace {
void verifySeeds(const Board &board, const std::vector<int> &seeds)
{
    int i = 0;
    for (const Pit &p : board)
    {
        EXPECT_EQ(seeds.at(i), board.seedCount(p)) << "Wrong numer of seeds at " << p;
        ++i;
    }
}
}

TEST(BoardTest, constructor)
{
    {
        Board b{Rules{6, 11}};
        EXPECT_EQ(b.seedCount({One, 1}), 11);
        EXPECT_EQ(b.seedCount({One, 2}), 11);
        EXPECT_EQ(b.seedCount({One, 3}), 11);
        EXPECT_EQ(b.seedCount({One, 4}), 11);
        EXPECT_EQ(b.seedCount({One, 5}), 11);
        EXPECT_EQ(b.seedCount({One, 6}), 11);
        EXPECT_EQ(b.seedCount({One, 7}), 0);
        EXPECT_EQ(b.seedCount({One, 1}), 11);
        EXPECT_EQ(b.seedCount({Two, 7}), 0);

        EXPECT_EQ(b.seedCount({One, b.numberOfHouses() + 1}), 0);
        EXPECT_EQ(b.seedCount({Two, b.numberOfHouses() + 1}), 0);
    }

    {
        Board b{{1, 2, 3, 4, 5, 7}};
        EXPECT_EQ(b.numberOfHouses(), 2);
    }
}

TEST(BoardTest, saw)
{
    { // Simple Test
        Board b{{3, 1, 1, 1, 2, 2}};
        auto p = b.saw({One, 1});
        EXPECT_EQ(p, Two);
        verifySeeds(b, {0, 2, 2, 2, 2, 2});
    }
    { // Put last in store
        Board b{{1, 1, 0, 1, 1, 0}};
        auto p = b.saw({One, 2});
        EXPECT_EQ(p, One);
        verifySeeds(b, {1, 0, 1, 1, 1, 0});
    }
    { // Capture
        Board b{{1, 0, 1, 0, 1, 9, 1, 0}};
        auto p = b.saw({One, 1});
        EXPECT_EQ(p, Two);
        verifySeeds(b, {0, 0, 1, 10, 1, 0, 1, 0});
    }
    { // Nothing to capture
        Board b{{1, 0, 1, 0, 1, 0, 1, 0}};
        auto p = b.saw({One, 1});
        EXPECT_EQ(p, Two);
        verifySeeds(b, {0, 1, 1, 0, 1, 0, 1, 0});
    }
    { // Game end
        Board b{{0, 1, 0, 1, 1, 1}};
        auto p = b.saw({One, 2});
        EXPECT_EQ(p, std::nullopt);
        verifySeeds(b, {0, 0, 1, 1, 1, 1});
    }
}

TEST(BoardTest, moveRemainingSeedsToStore)
{
    { // Two wins
        Board b{{0, 0, 2, 1, 2, 0}};
        auto p = b.moveRemainingSeedsToStore();
        EXPECT_EQ(p, Two);
        verifySeeds(b, {0, 0, 2, 0, 0, 3});
    }
    { // Draw
        Board b{{0, 0, 3, 1, 2, 0}};
        auto p = b.moveRemainingSeedsToStore();
        EXPECT_EQ(p, std::nullopt);
        verifySeeds(b, {0, 0, 3, 0, 0, 3});
    }
    { // One wins
        Board b{{0, 0, 4, 1, 2, 0}};
        auto p = b.moveRemainingSeedsToStore();
        EXPECT_EQ(p, One);
        verifySeeds(b, {0, 0, 4, 0, 0, 3});
    }
}

TEST(BoardTest, shortMatch)
{
    Board b{Rules{3, 4}};
    verifySeeds(b, {4, 4, 4, 0, 4, 4, 4, 0});
    std::optional<PlayerNumber> p;

    EXPECT_DEATH(p = b.saw({Two, 4}), "");

    p = b.saw({One, 3});
    EXPECT_EQ(p, Two);
    verifySeeds(b, {4, 4, 0, 1, 5, 5, 5, 0});

    EXPECT_DEATH(p = b.saw({One, 3}), "");

    p = b.saw({Two, 1});
    EXPECT_EQ(p, One);
    verifySeeds(b, {5, 5, 0, 1, 0, 6, 6, 1});

    p = b.saw({One, 1});
    EXPECT_EQ(p, Two);
    verifySeeds(b, {0, 6, 1, 2, 1, 7, 6, 1});

    p = b.saw({Two, 1});
    EXPECT_EQ(p, One);
    verifySeeds(b, {0, 6, 1, 2, 0, 8, 6, 1});

    p = b.saw({One, 3});
    EXPECT_EQ(p, One);
    verifySeeds(b, {0, 6, 0, 3, 0, 8, 6, 1});

    p = b.saw({One, 2});
    EXPECT_EQ(p, Two);
    verifySeeds(b, {0, 0, 1, 12, 1, 9, 0, 1});

    p = b.saw({One, 3});
    EXPECT_EQ(p, std::nullopt);
    verifySeeds(b, {0, 0, 0, 13, 1, 9, 0, 1});

    EXPECT_DEATH(p = b.saw({Two, 1}), "");

    b.moveRemainingSeedsToStore();
    verifySeeds(b, {0, 0, 0, 13, 0, 0, 0, 11});
}

TEST(BoardTest, isHouse)
{
    Board b{Rules{7, 2}};
    EXPECT_EQ(true, b.isHouse(Pit(One, 1)));
    EXPECT_EQ(true, b.isHouse(Pit(One, 7)));
    EXPECT_EQ(false, b.isHouse(Pit(One, 8)));
    EXPECT_EQ(true, b.isHouse(Pit(Two, 2)));
    EXPECT_EQ(true, b.isHouse(Pit(Two, 5)));
    EXPECT_EQ(false, b.isHouse(Pit(Two, 8)));
}

TEST(BoardTest, isStore)
{
    Board b{Rules{5, 2}};
    EXPECT_EQ(false, b.isStore(Pit(One, 1)));
    EXPECT_EQ(false, b.isStore(Pit(One, 5)));
    EXPECT_EQ(true, b.isStore(Pit(One, 6)));
    EXPECT_EQ(false, b.isStore(Pit(Two, 2)));
    EXPECT_EQ(false, b.isStore(Pit(Two, 4)));
    EXPECT_EQ(true, b.isStore(Pit(Two, 6)));
}

TEST(BoardTest, oppositeHouse)
{
    Board b{Rules{7, 6}};
    EXPECT_EQ(Pit(One, 1), b.oppositeHouse(Pit(Two, 7)));
    EXPECT_EQ(Pit(One, 7), b.oppositeHouse(Pit(Two, 1)));
    EXPECT_EQ(Pit(One, 4), b.oppositeHouse(Pit(Two, 4)));
}

TEST(BoardTest, nextPit)
{
    Board b{Rules{3, 2}};
    Pit a = Pit(One, 1);
    EXPECT_EQ(a, Pit(One, 1));
    a = b.nextPit(a);
    EXPECT_EQ(a, Pit(One, 2));
    a = b.nextPit(a);
    EXPECT_EQ(a, Pit(One, 3));
    a = b.nextPit(a);
    EXPECT_EQ(a, Pit(One, 4));
    a = b.nextPit(a);
    EXPECT_EQ(a, Pit(Two, 1));
    a = b.nextPit(a);
    EXPECT_EQ(a, Pit(Two, 2));
    a = b.nextPit(a);
    EXPECT_EQ(a, Pit(Two, 3));
    a = b.nextPit(a);
    EXPECT_EQ(a, Pit(Two, 4));
    a = b.nextPit(a);
    EXPECT_EQ(a, Pit(One, 1));
    a = b.nextPit(a);
    EXPECT_EQ(a, Pit(One, 2));
}

TEST(BoardTest, previousPit)
{
    Board b{Rules{3, 2}};
    Pit a = Pit(One, 1);
    EXPECT_EQ(a, Pit(One, 1));
    a = b.previousPit(a);
    EXPECT_EQ(a, Pit(Two, b.numberOfHouses() + 1));
    a = b.previousPit(a);
    EXPECT_EQ(a, Pit(Two, 3));
    a = b.previousPit(a);
    EXPECT_EQ(a, Pit(Two, 2));
    a = b.previousPit(a);
    EXPECT_EQ(a, Pit(Two, 1));
    a = b.previousPit(a);
    EXPECT_EQ(a, Pit(One, 4));
    a = b.previousPit(a);
    EXPECT_EQ(a, Pit(One, 3));
    a = b.previousPit(a);
    EXPECT_EQ(a, Pit(One, 2));
    a = b.previousPit(a);
    EXPECT_EQ(a, Pit(One, 1));
    a = b.previousPit(a);
    EXPECT_EQ(a, Pit(Two, 4));
    a = b.previousPit(a);
    EXPECT_EQ(a, Pit(Two, 3));
    a = b.previousPit(a);
    EXPECT_EQ(a, Pit(Two, 2));
}
