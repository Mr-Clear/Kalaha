#include "Game/Board.h"

#include <gtest/gtest.h>


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

    EXPECT_EQ(b.seedCount(b.store(Player::One)), 0);
    EXPECT_EQ(b.seedCount(b.store(Player::Two)), 0);
}

TEST(BoardTest, getPitDeathTest)
{
    Board b{5, 1};
    EXPECT_DEATH(Pit p = b.pit(Player::One, 0), "");
    EXPECT_DEATH(Pit p = b.pit(Player::One, 7), "");
    EXPECT_DEATH(Pit p = b.pit(Player::One, -1), "");
    EXPECT_DEATH(Pit p = b.pit(Player::Two, 0), "");
    EXPECT_DEATH(Pit p = b.pit(Player::Two, 7), "");
    EXPECT_DEATH(Pit p = b.pit(Player::Two, -1), "");

    EXPECT_DEATH(Pit p = b.house(Player::One, 0), "");
    EXPECT_DEATH(Pit p = b.house(Player::One, 6), "");
    EXPECT_DEATH(Pit p = b.house(Player::One, 7), "");
    EXPECT_DEATH(Pit p = b.house(Player::One, -1), "");
    EXPECT_DEATH(Pit p = b.house(Player::Two, 0), "");
    EXPECT_DEATH(Pit p = b.house(Player::Two, 6), "");
    EXPECT_DEATH(Pit p = b.house(Player::Two, 7), "");
    EXPECT_DEATH(Pit p = b.house(Player::Two, -1), "");
}

void verifySeeds(const Board &board, const std::vector<int> &seeds)
{
    int i = 0;
    for (Pit p = board.pit(Player::One, 1); !p.isOverflow(); ++p)
    {
        EXPECT_EQ(seeds.at(i), board.seedCount(p)) << "Wrong numer of seeds at "
                                                   << (p.player() == Player::One ? "Player one" : "Player two")
                                                   << " Pit "
                                                   << p.number();
        ++i;
    }
}

TEST(BoardTest, shortMatch)
{
    Board b{3, 4};
    verifySeeds(b, {4, 4, 4, 0, 4, 4, 4, 0});
    std::optional<Player> p;

    EXPECT_DEATH(p = b.saw(b.pit(Player::Two, 4)), "");

    p = b.saw(b.house(Player::One, 3));
    EXPECT_EQ(p, Player::Two);
    verifySeeds(b, {4, 4, 0, 1, 5, 5, 5, 0});

    EXPECT_DEATH(p = b.saw(b.pit(Player::One, 3)), "");

    p = b.saw(b.house(Player::Two, 1));
    EXPECT_EQ(p, Player::One);
    verifySeeds(b, {5, 5, 0, 1, 0, 6, 6, 1});

    p = b.saw(b.house(Player::One, 1));
    EXPECT_EQ(p, Player::Two);
    verifySeeds(b, {0, 6, 1, 2, 1, 7, 6, 1});

    p = b.saw(b.house(Player::Two, 1));
    EXPECT_EQ(p, Player::One);
    verifySeeds(b, {0, 6, 1, 2, 0, 8, 6, 1});

    p = b.saw(b.house(Player::One, 3));
    EXPECT_EQ(p, Player::One);
    verifySeeds(b, {0, 6, 0, 3, 0, 8, 6, 1});

    p = b.saw(b.house(Player::One, 2));
    EXPECT_EQ(p, Player::Two);
    verifySeeds(b, {0, 0, 1, 12, 1, 9, 0, 1});

    p = b.saw(b.house(Player::One, 3));
    EXPECT_EQ(p, std::nullopt);
    verifySeeds(b, {0, 0, 0, 13, 1, 9, 0, 1});

    EXPECT_DEATH(p = b.saw(b.pit(Player::Two, 1)), "");

    b.moveRemainingSeedsToStore();
    verifySeeds(b, {0, 0, 0, 13, 0, 0, 0, 11});
}
