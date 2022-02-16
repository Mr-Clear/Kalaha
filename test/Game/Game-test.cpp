#include "Game/Game.h"

#include "../test/Game/Board-mock.h"
#include "../test/Output/Output-mock.h"
#include "../test/Player/Player-Mock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using PlayerNumber::One;
using PlayerNumber::Two;

using ::testing::Return;
using ::testing::_;

TEST(GameTest, mocked)
{
    MockOutput output;
    std::unique_ptr<MockBoard> board{new MockBoard{3, {}}};

    std::shared_ptr<MockPlayer> playerA{std::make_shared<MockPlayer>(One)};
    playerA->defineSequence({1, 2}, *board);
    std::shared_ptr<MockPlayer> playerB{std::make_shared<MockPlayer>(Two)};
    playerB->defineSequence({1}, *board);

    EXPECT_CALL(output, showBoard(_)).Times(5);
    EXPECT_CALL(output, showTurn(1, One));
    EXPECT_CALL(output, showTurn(2, Two));
    EXPECT_CALL(output, showTurn(3, One));
    EXPECT_CALL(output, showWinner(std::optional<PlayerNumber>(Two)));

    EXPECT_CALL(*board, saw(board->house(One, 1))).WillOnce(Return(Two));
    EXPECT_CALL(*board, saw(board->house(Two, 1))).WillOnce(Return(One));
    EXPECT_CALL(*board, saw(board->house(One, 2))).WillOnce(Return(std::nullopt));
    EXPECT_CALL(*board, moveRemainingSeedsToStore).WillOnce(Return(Two));

    {
        std::map<PlayerNumber, std::shared_ptr<AbstractPlayer>> playerMap{{One, playerA}, {Two, playerB}};
        Game game{std::move(board), output, playerMap};
        game.start(One);
    }
}
