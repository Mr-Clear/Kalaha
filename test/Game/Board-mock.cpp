#include "Board-mock.h"

#include <cassert>

using PlayerNumber::One;
using PlayerNumber::Two;

using ::testing::Return;

void prepareMockBoard(MockBoard &b, int numberOfHouses, const std::initializer_list<int> &seedsPerPit)
{
    auto seedsI = seedsPerPit.begin();
    EXPECT_CALL(b, numberOfHouses()).WillRepeatedly(Return(numberOfHouses));
    for (PlayerNumber p : ALL_PLAYERS)
    {
        for (int i = 1; i <= numberOfHouses + 1; i++)
        {
            const Pit pit{b, p, i};
            EXPECT_CALL(b, pit(p, i)).WillRepeatedly(Return(pit));
            if (i <= numberOfHouses)
                EXPECT_CALL(b, house(p, i)).WillRepeatedly(Return(pit));
            else
                EXPECT_CALL(b, store(p)).WillRepeatedly(Return(pit));
            if (seedsI != seedsPerPit.end())
            {
                EXPECT_CALL(b, seedCount(pit)).WillRepeatedly(Return(*seedsI));
                seedsI++;
            }
            else
            {
                EXPECT_CALL(b, seedCount(pit)).WillRepeatedly(Return(1));
            }
        }
    }
    EXPECT_CALL(b, lastTurn()).WillRepeatedly(Return(IBoard::Turn{PlayerNumber::One, {}, {}}));
}
