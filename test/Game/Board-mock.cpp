#include "Board-mock.h"

#include <cassert>

using PlayerNumber::One;
using PlayerNumber::Two;

using ::testing::Return;

MockBoard::MockBoard(int numberOfHouses, const std::initializer_list<int> &seedsPerPit)
{
    auto seedsI = seedsPerPit.begin();
    EXPECT_CALL(*this, numberOfHouses()).WillRepeatedly(Return(numberOfHouses));
    EXPECT_CALL(*this, storeId()).WillRepeatedly(Return(numberOfHouses + 1));
    for (PlayerNumber p : ALL_PLAYERS)
    {
        for (int i = 1; i <= numberOfHouses + 1; i++)
        {
            const Pit pit{p, i};
            if (seedsI != seedsPerPit.end())
            {
                EXPECT_CALL(*this, seedCount(pit)).WillRepeatedly(Return(*seedsI));
                seedsI++;
            }
            else
            {
                EXPECT_CALL(*this, seedCount(pit)).WillRepeatedly(Return(1));
            }
        }
    }
    EXPECT_CALL(*this, lastTurn()).WillRepeatedly(Return(AbstractBoard::Turn{PlayerNumber::One, {}, {}}));
}
