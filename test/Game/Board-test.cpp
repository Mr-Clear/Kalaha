#include "Game/Board.h"

#include <gtest/gtest.h>

TEST(BoardTest, constructor)
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

TEST(BoardTest, getPitDeathTest)
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

void verifySeeds(const Board &board, const std::vector<int> &seeds)
{
    int i = 0;
    for (Pit p = board.pit(PlayerNumber::One, 1); !p.isOverflow(); ++p)
    {
        EXPECT_EQ(seeds.at(i), board.seedCount(p)) << "Wrong numer of seeds at "
                                                   << (p.player() == PlayerNumber::One ? "Player one" : "Player two")
                                                   << " Pit "
                                                   << p.number();
        ++i;
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
