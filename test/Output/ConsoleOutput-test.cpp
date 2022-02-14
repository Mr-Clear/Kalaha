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
    MOCK_METHOD(Pit, pit, (Player player, int pitNumber), (const, override));
    MOCK_METHOD(Pit, house, (Player player, int houseNumber), (const, override));
    MOCK_METHOD(Pit, store, (Player player), (const, override));
    MOCK_METHOD(int, seedCount, (const Pit &pit), (const, override));
    MOCK_METHOD(std::optional<Player>, saw, (const Pit &startPit), (override));
    MOCK_METHOD(void, moveRemainingSeedsToStore, (), (override));
};

TEST(ConsoleOutputTest, mocked)
{
    std::ostringstream stream;
    ConsoleOutput o{3, stream};
    MockBoard b;
    EXPECT_CALL(b, numberOfHouses()).WillRepeatedly(Return(6));
    EXPECT_CALL(b, house(Player::One, 1)).WillRepeatedly(Return(Pit{b, Player::One, 1}));
    EXPECT_CALL(b, house(Player::One, 2)).WillRepeatedly(Return(Pit{b, Player::One, 2}));
    EXPECT_CALL(b, house(Player::One, 3)).WillRepeatedly(Return(Pit{b, Player::One, 3}));
    EXPECT_CALL(b, house(Player::One, 4)).WillRepeatedly(Return(Pit{b, Player::One, 4}));
    EXPECT_CALL(b, house(Player::One, 5)).WillRepeatedly(Return(Pit{b, Player::One, 5}));
    EXPECT_CALL(b, house(Player::One, 6)).WillRepeatedly(Return(Pit{b, Player::One, 6}));
    EXPECT_CALL(b, store(Player::One))   .WillRepeatedly(Return(Pit{b, Player::One, 7}));
    EXPECT_CALL(b, house(Player::Two, 1)).WillRepeatedly(Return(Pit{b, Player::Two, 1}));
    EXPECT_CALL(b, house(Player::Two, 2)).WillRepeatedly(Return(Pit{b, Player::Two, 2}));
    EXPECT_CALL(b, house(Player::Two, 3)).WillRepeatedly(Return(Pit{b, Player::Two, 3}));
    EXPECT_CALL(b, house(Player::Two, 4)).WillRepeatedly(Return(Pit{b, Player::Two, 4}));
    EXPECT_CALL(b, house(Player::Two, 5)).WillRepeatedly(Return(Pit{b, Player::Two, 5}));
    EXPECT_CALL(b, house(Player::Two, 6)).WillRepeatedly(Return(Pit{b, Player::Two, 6}));
    EXPECT_CALL(b, store(Player::Two))   .WillRepeatedly(Return(Pit{b, Player::Two, 7}));

    EXPECT_CALL(b, seedCount(b.house(Player::One, 1))).WillRepeatedly(Return(0));
    EXPECT_CALL(b, seedCount(b.house(Player::One, 2))).WillRepeatedly(Return(20));
    EXPECT_CALL(b, seedCount(b.house(Player::One, 3))).WillRepeatedly(Return(5));
    EXPECT_CALL(b, seedCount(b.house(Player::One, 4))).WillRepeatedly(Return(66));
    EXPECT_CALL(b, seedCount(b.house(Player::One, 5))).WillRepeatedly(Return(135));
    EXPECT_CALL(b, seedCount(b.house(Player::One, 6))).WillRepeatedly(Return(5));
    EXPECT_CALL(b, seedCount(b.store(Player::One)))   .WillRepeatedly(Return(363));
    EXPECT_CALL(b, seedCount(b.house(Player::Two, 1))).WillRepeatedly(Return(0));
    EXPECT_CALL(b, seedCount(b.house(Player::Two, 2))).WillRepeatedly(Return(0));
    EXPECT_CALL(b, seedCount(b.house(Player::Two, 3))).WillRepeatedly(Return(1));
    EXPECT_CALL(b, seedCount(b.house(Player::Two, 4))).WillRepeatedly(Return(1));
    EXPECT_CALL(b, seedCount(b.house(Player::Two, 5))).WillRepeatedly(Return(2));
    EXPECT_CALL(b, seedCount(b.house(Player::Two, 6))).WillRepeatedly(Return(2));
    EXPECT_CALL(b, seedCount(b.store(Player::Two)))   .WillRepeatedly(Return(111));

    o.output(b);
    std::string exp = "╔═══╤═══╤═══╤═══╤═══╤═══╤═══╤═══╗\n"
                      "║   │  5│135│ 66│  5│ 20│  0│   ║\n"
                      "║363├───┼───┼───┼───┼───┼───┤111║\n"
                      "║   │  0│  0│  1│  1│  2│  2│   ║\n"
                      "╚═══╧═══╧═══╧═══╧═══╧═══╧═══╧═══╝\n";
    EXPECT_EQ(exp, stream.str());
}
