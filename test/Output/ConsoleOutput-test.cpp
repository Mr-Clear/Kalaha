#include "Game/Board.h"
#include "../test/Game/Board-mock.h"
#include "Output/ConsoleOutput.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>

using PlayerNumber::One;
using PlayerNumber::Two;

using ::testing::Return;

TEST(ConsoleOutputTest, mocked)
{
    std::ostringstream stream;
    ConsoleOutput o{3, stream};
    MockBoard b;
    EXPECT_CALL(b, numberOfHouses()).WillRepeatedly(Return(6));
    EXPECT_CALL(b, house(One, 1)).WillRepeatedly(Return(Pit{b, One, 1}));
    EXPECT_CALL(b, house(One, 2)).WillRepeatedly(Return(Pit{b, One, 2}));
    EXPECT_CALL(b, house(One, 3)).WillRepeatedly(Return(Pit{b, One, 3}));
    EXPECT_CALL(b, house(One, 4)).WillRepeatedly(Return(Pit{b, One, 4}));
    EXPECT_CALL(b, house(One, 5)).WillRepeatedly(Return(Pit{b, One, 5}));
    EXPECT_CALL(b, house(One, 6)).WillRepeatedly(Return(Pit{b, One, 6}));
    EXPECT_CALL(b, store(One))   .WillRepeatedly(Return(Pit{b, One, 7}));
    EXPECT_CALL(b, house(Two, 1)).WillRepeatedly(Return(Pit{b, Two, 1}));
    EXPECT_CALL(b, house(Two, 2)).WillRepeatedly(Return(Pit{b, Two, 2}));
    EXPECT_CALL(b, house(Two, 3)).WillRepeatedly(Return(Pit{b, Two, 3}));
    EXPECT_CALL(b, house(Two, 4)).WillRepeatedly(Return(Pit{b, Two, 4}));
    EXPECT_CALL(b, house(Two, 5)).WillRepeatedly(Return(Pit{b, Two, 5}));
    EXPECT_CALL(b, house(Two, 6)).WillRepeatedly(Return(Pit{b, Two, 6}));
    EXPECT_CALL(b, store(Two))   .WillRepeatedly(Return(Pit{b, Two, 7}));

    EXPECT_CALL(b, seedCount(b.house(One, 1))).WillRepeatedly(Return(0));
    EXPECT_CALL(b, seedCount(b.house(One, 2))).WillRepeatedly(Return(20));
    EXPECT_CALL(b, seedCount(b.house(One, 3))).WillRepeatedly(Return(5));
    EXPECT_CALL(b, seedCount(b.house(One, 4))).WillRepeatedly(Return(66));
    EXPECT_CALL(b, seedCount(b.house(One, 5))).WillRepeatedly(Return(135));
    EXPECT_CALL(b, seedCount(b.house(One, 6))).WillRepeatedly(Return(5));
    EXPECT_CALL(b, seedCount(b.store(One)))   .WillRepeatedly(Return(363));
    EXPECT_CALL(b, seedCount(b.house(Two, 1))).WillRepeatedly(Return(0));
    EXPECT_CALL(b, seedCount(b.house(Two, 2))).WillRepeatedly(Return(0));
    EXPECT_CALL(b, seedCount(b.house(Two, 3))).WillRepeatedly(Return(1));
    EXPECT_CALL(b, seedCount(b.house(Two, 4))).WillRepeatedly(Return(1));
    EXPECT_CALL(b, seedCount(b.house(Two, 5))).WillRepeatedly(Return(2));
    EXPECT_CALL(b, seedCount(b.house(Two, 6))).WillRepeatedly(Return(2));
    EXPECT_CALL(b, seedCount(b.store(Two)))   .WillRepeatedly(Return(111));

    EXPECT_CALL(b, lastTurn())   .WillRepeatedly(Return(Board::Turn{One, b.house(Two, 2),
                                                                    {b.house(Two, 3),
                                                                     b.house(Two, 4)}}));

    o.showBoard(b);
    std::string exp = "╔═════╤═════╤═════╤═════╤═════╤═════╤═════╤═════╗\n"
                      "║     │   5 │ 135 │  66 │   5 │  20 │   0 │     ║\n"
                      "║ 363 ├─────┼─────┼─────┼─────┼─────┼─────┤ 111 ║\n"
                      "║     │   0 │[  0]│(  1)│(  1)│   2 │   2 │     ║\n"
                      "╚═════╧═════╧═════╧═════╧═════╧═════╧═════╧═════╝\n";
    EXPECT_EQ(exp, stream.str());
}
