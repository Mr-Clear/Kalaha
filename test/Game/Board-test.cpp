#include "Game/Board.h"

#include <gtest/gtest.h>

namespace {
void verifySeeds(const Board &board, const std::vector<int> &seeds)
{
    int i = 0;
    for (Pit p = board.pit(PlayerNumber::One, 1); !p.isOverflow(); ++p)
    {
        EXPECT_EQ(seeds.at(i), board.seedCount(p)) << "Wrong numer of seeds at "
                                                   << p.player() << ", Pit " << p.number();
        ++i;
    }
}
}

TEST(BoardTest, constructor)
{
    {
        Board b{6, 11};
        EXPECT_EQ(b.seedCount(b.pit(PlayerNumber::One, 1)), 11);
        EXPECT_EQ(b.seedCount(b.pit(PlayerNumber::One, 2)), 11);
        EXPECT_EQ(b.seedCount(b.pit(PlayerNumber::One, 3)), 11);
        EXPECT_EQ(b.seedCount(b.pit(PlayerNumber::One, 4)), 11);
        EXPECT_EQ(b.seedCount(b.pit(PlayerNumber::One, 5)), 11);
        EXPECT_EQ(b.seedCount(b.pit(PlayerNumber::One, 6)), 11);
        EXPECT_EQ(b.seedCount(b.pit(PlayerNumber::One, 7)), 0);
        EXPECT_EQ(b.seedCount(b.pit(PlayerNumber::One, 1)), 11);
        EXPECT_EQ(b.seedCount(b.pit(PlayerNumber::Two, 7)), 0);

        EXPECT_EQ(b.seedCount(b.store(PlayerNumber::One)), 0);
        EXPECT_EQ(b.seedCount(b.store(PlayerNumber::Two)), 0);
    }

    {
        Board b{{1, 2, 3, 4, 5, 7}};
        EXPECT_EQ(b.numberOfHouses(), 2);
    }
}

TEST(BoardTest, getPitDeath)
{
    Board b{5, 1};
    EXPECT_DEATH(Pit p = b.pit(PlayerNumber::One, 0), "");
    EXPECT_DEATH(Pit p = b.pit(PlayerNumber::One, 7), "");
    EXPECT_DEATH(Pit p = b.pit(PlayerNumber::One, -1), "");
    EXPECT_DEATH(Pit p = b.pit(PlayerNumber::Two, 0), "");
    EXPECT_DEATH(Pit p = b.pit(PlayerNumber::Two, 7), "");
    EXPECT_DEATH(Pit p = b.pit(PlayerNumber::Two, -1), "");

    EXPECT_DEATH(Pit p = b.house(PlayerNumber::One, 0), "");
    EXPECT_DEATH(Pit p = b.house(PlayerNumber::One, 6), "");
    EXPECT_DEATH(Pit p = b.house(PlayerNumber::One, 7), "");
    EXPECT_DEATH(Pit p = b.house(PlayerNumber::One, -1), "");
    EXPECT_DEATH(Pit p = b.house(PlayerNumber::Two, 0), "");
    EXPECT_DEATH(Pit p = b.house(PlayerNumber::Two, 6), "");
    EXPECT_DEATH(Pit p = b.house(PlayerNumber::Two, 7), "");
    EXPECT_DEATH(Pit p = b.house(PlayerNumber::Two, -1), "");
}

TEST(BoardTest, saw)
{
    { // Simple Test
        Board b{{3, 1, 1, 1, 2, 2}};
        auto p = b.saw(b.house(PlayerNumber::One, 1));
        EXPECT_EQ(p, PlayerNumber::Two);
        verifySeeds(b, {0, 2, 2, 2, 2, 2});
    }
    { // Put last in store
        Board b{{1, 1, 0, 1, 1, 0}};
        auto p = b.saw(b.house(PlayerNumber::One, 2));
        EXPECT_EQ(p, PlayerNumber::One);
        verifySeeds(b, {1, 0, 1, 1, 1, 0});
    }
    { // Capture
        Board b{{1, 0, 1, 0, 1, 9, 1, 0}};
        auto p = b.saw(b.house(PlayerNumber::One, 1));
        EXPECT_EQ(p, PlayerNumber::Two);
        verifySeeds(b, {0, 0, 1, 10, 1, 0, 1, 0});
    }
    { // Nothing to capture
        Board b{{1, 0, 1, 0, 1, 0, 1, 0}};
        auto p = b.saw(b.house(PlayerNumber::One, 1));
        EXPECT_EQ(p, PlayerNumber::Two);
        verifySeeds(b, {0, 1, 1, 0, 1, 0, 1, 0});
    }
    { // Game end
        Board b{{0, 1, 0, 1, 1, 1}};
        auto p = b.saw(b.house(PlayerNumber::One, 2));
        EXPECT_EQ(p, std::nullopt);
        verifySeeds(b, {0, 0, 1, 1, 1, 1});
    }
}

TEST(BoardTest, moveRemainingSeedsToStore)
{
    { // Two wins
        Board b{{0, 0, 2, 1, 2, 0}};
        auto p = b.moveRemainingSeedsToStore();
        EXPECT_EQ(p, PlayerNumber::Two);
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
        EXPECT_EQ(p, PlayerNumber::One);
        verifySeeds(b, {0, 0, 4, 0, 0, 3});
    }
}

TEST(BoardTest, shortMatch)
{
    Board b{3, 4};
    verifySeeds(b, {4, 4, 4, 0, 4, 4, 4, 0});
    std::optional<PlayerNumber> p;

    EXPECT_DEATH(p = b.saw(b.pit(PlayerNumber::Two, 4)), "");

    p = b.saw(b.house(PlayerNumber::One, 3));
    EXPECT_EQ(p, PlayerNumber::Two);
    verifySeeds(b, {4, 4, 0, 1, 5, 5, 5, 0});

    EXPECT_DEATH(p = b.saw(b.pit(PlayerNumber::One, 3)), "");

    p = b.saw(b.house(PlayerNumber::Two, 1));
    EXPECT_EQ(p, PlayerNumber::One);
    verifySeeds(b, {5, 5, 0, 1, 0, 6, 6, 1});

    p = b.saw(b.house(PlayerNumber::One, 1));
    EXPECT_EQ(p, PlayerNumber::Two);
    verifySeeds(b, {0, 6, 1, 2, 1, 7, 6, 1});

    p = b.saw(b.house(PlayerNumber::Two, 1));
    EXPECT_EQ(p, PlayerNumber::One);
    verifySeeds(b, {0, 6, 1, 2, 0, 8, 6, 1});

    p = b.saw(b.house(PlayerNumber::One, 3));
    EXPECT_EQ(p, PlayerNumber::One);
    verifySeeds(b, {0, 6, 0, 3, 0, 8, 6, 1});

    p = b.saw(b.house(PlayerNumber::One, 2));
    EXPECT_EQ(p, PlayerNumber::Two);
    verifySeeds(b, {0, 0, 1, 12, 1, 9, 0, 1});

    p = b.saw(b.house(PlayerNumber::One, 3));
    EXPECT_EQ(p, std::nullopt);
    verifySeeds(b, {0, 0, 0, 13, 1, 9, 0, 1});

    EXPECT_DEATH(p = b.saw(b.pit(PlayerNumber::Two, 1)), "");

    b.moveRemainingSeedsToStore();
    verifySeeds(b, {0, 0, 0, 13, 0, 0, 0, 11});
}
