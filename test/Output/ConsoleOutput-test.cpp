#include "Game/Board.h"
#include "Output/ConsoleOutput.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>

using ::testing::Return;

class MockBoard : public IBoard
{
public:
    MOCK_METHOD(int, numberOfHouses, (), (const, override));
    MOCK_METHOD(Pit, pit, (PlayerNumber player, int pitNumber), (const, override));
    MOCK_METHOD(Pit, house, (PlayerNumber player, int houseNumber), (const, override));
    MOCK_METHOD(Pit, store, (PlayerNumber player), (const, override));
    MOCK_METHOD(int, seedCount, (const Pit &pit), (const, override));
    MOCK_METHOD(std::optional<PlayerNumber>, saw, (const Pit &startPit), (override));
    MOCK_METHOD(std::optional<PlayerNumber>, moveRemainingSeedsToStore, (), (override));
    MOCK_METHOD(std::optional<Turn>, lastTurn, (), (const, override));
};

TEST(ConsoleOutputTest, mocked)
{
    std::ostringstream stream;
    ConsoleOutput o{3, stream};
    MockBoard b;
    EXPECT_CALL(b, numberOfHouses()).WillRepeatedly(Return(6));
    EXPECT_CALL(b, house(PlayerNumber::One, 1)).WillRepeatedly(Return(Pit{b, PlayerNumber::One, 1}));
    EXPECT_CALL(b, house(PlayerNumber::One, 2)).WillRepeatedly(Return(Pit{b, PlayerNumber::One, 2}));
    EXPECT_CALL(b, house(PlayerNumber::One, 3)).WillRepeatedly(Return(Pit{b, PlayerNumber::One, 3}));
    EXPECT_CALL(b, house(PlayerNumber::One, 4)).WillRepeatedly(Return(Pit{b, PlayerNumber::One, 4}));
    EXPECT_CALL(b, house(PlayerNumber::One, 5)).WillRepeatedly(Return(Pit{b, PlayerNumber::One, 5}));
    EXPECT_CALL(b, house(PlayerNumber::One, 6)).WillRepeatedly(Return(Pit{b, PlayerNumber::One, 6}));
    EXPECT_CALL(b, store(PlayerNumber::One))   .WillRepeatedly(Return(Pit{b, PlayerNumber::One, 7}));
    EXPECT_CALL(b, house(PlayerNumber::Two, 1)).WillRepeatedly(Return(Pit{b, PlayerNumber::Two, 1}));
    EXPECT_CALL(b, house(PlayerNumber::Two, 2)).WillRepeatedly(Return(Pit{b, PlayerNumber::Two, 2}));
    EXPECT_CALL(b, house(PlayerNumber::Two, 3)).WillRepeatedly(Return(Pit{b, PlayerNumber::Two, 3}));
    EXPECT_CALL(b, house(PlayerNumber::Two, 4)).WillRepeatedly(Return(Pit{b, PlayerNumber::Two, 4}));
    EXPECT_CALL(b, house(PlayerNumber::Two, 5)).WillRepeatedly(Return(Pit{b, PlayerNumber::Two, 5}));
    EXPECT_CALL(b, house(PlayerNumber::Two, 6)).WillRepeatedly(Return(Pit{b, PlayerNumber::Two, 6}));
    EXPECT_CALL(b, store(PlayerNumber::Two))   .WillRepeatedly(Return(Pit{b, PlayerNumber::Two, 7}));

    EXPECT_CALL(b, seedCount(b.house(PlayerNumber::One, 1))).WillRepeatedly(Return(0));
    EXPECT_CALL(b, seedCount(b.house(PlayerNumber::One, 2))).WillRepeatedly(Return(20));
    EXPECT_CALL(b, seedCount(b.house(PlayerNumber::One, 3))).WillRepeatedly(Return(5));
    EXPECT_CALL(b, seedCount(b.house(PlayerNumber::One, 4))).WillRepeatedly(Return(66));
    EXPECT_CALL(b, seedCount(b.house(PlayerNumber::One, 5))).WillRepeatedly(Return(135));
    EXPECT_CALL(b, seedCount(b.house(PlayerNumber::One, 6))).WillRepeatedly(Return(5));
    EXPECT_CALL(b, seedCount(b.store(PlayerNumber::One)))   .WillRepeatedly(Return(363));
    EXPECT_CALL(b, seedCount(b.house(PlayerNumber::Two, 1))).WillRepeatedly(Return(0));
    EXPECT_CALL(b, seedCount(b.house(PlayerNumber::Two, 2))).WillRepeatedly(Return(0));
    EXPECT_CALL(b, seedCount(b.house(PlayerNumber::Two, 3))).WillRepeatedly(Return(1));
    EXPECT_CALL(b, seedCount(b.house(PlayerNumber::Two, 4))).WillRepeatedly(Return(1));
    EXPECT_CALL(b, seedCount(b.house(PlayerNumber::Two, 5))).WillRepeatedly(Return(2));
    EXPECT_CALL(b, seedCount(b.house(PlayerNumber::Two, 6))).WillRepeatedly(Return(2));
    EXPECT_CALL(b, seedCount(b.store(PlayerNumber::Two)))   .WillRepeatedly(Return(111));

    EXPECT_CALL(b, lastTurn())   .WillRepeatedly(Return(Board::Turn{PlayerNumber::One, b.house(PlayerNumber::Two, 2),
                                                                    {b.house(PlayerNumber::Two, 3),
                                                                     b.house(PlayerNumber::Two, 4)}}));

    o.showBoard(b);
    std::string exp = "╔═════╤═════╤═════╤═════╤═════╤═════╤═════╤═════╗\n"
                      "║     │   5 │ 135 │  66 │   5 │  20 │   0 │     ║\n"
                      "║ 363 ├─────┼─────┼─────┼─────┼─────┼─────┤ 111 ║\n"
                      "║     │   0 │[  0]│(  1)│(  1)│   2 │   2 │     ║\n"
                      "╚═════╧═════╧═════╧═════╧═════╧═════╧═════╧═════╝\n";
    EXPECT_EQ(exp, stream.str());
}
