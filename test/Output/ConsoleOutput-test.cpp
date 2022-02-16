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
    MockBoard b{6, {0, 20, 5, 66, 135, 5, 363, 0, 0, 1, 1, 2, 2, 111}};

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
