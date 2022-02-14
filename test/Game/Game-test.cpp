
#include "Game/Game.h"
#include "../test/Game/Board-mock.h"
#include "../test/Game/Player-Mock.h"
#include "../test/Output/Output-mock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using PlayerNumber::One;
using PlayerNumber::Two;

using ::testing::Return;
using ::testing::_;

TEST(GameTest, mocked)
{
    MockOutput output;
    std::unique_ptr<MockBoard> board = std::make_unique<MockBoard>();
    std::shared_ptr<MockPlayer> playerA{std::make_shared<MockPlayer>()};
    std::shared_ptr<MockPlayer> playerB{std::make_shared<MockPlayer>()};

    EXPECT_CALL(output, showBoard(_)).Times(5);
    EXPECT_CALL(output, showTurn(1, One));
    EXPECT_CALL(output, showTurn(2, Two));
    EXPECT_CALL(output, showTurn(3, One));
    EXPECT_CALL(output, showWinner(std::optional<PlayerNumber>(Two)));

    EXPECT_CALL(*board, house(One, 1)).WillRepeatedly(Return(Pit{*board, One, 1}));
    EXPECT_CALL(*board, house(One, 2)).WillRepeatedly(Return(Pit{*board, One, 2}));
    EXPECT_CALL(*board, house(Two, 1)).WillRepeatedly(Return(Pit{*board, Two, 1}));
    EXPECT_CALL(*playerA, selectHouse).WillOnce(Return(board->house(One, 1)))
                                      .WillOnce(Return(board->house(One, 2)));
    EXPECT_CALL(*playerB, selectHouse).WillOnce(Return(board->house(Two, 1)));

    EXPECT_CALL(*board, saw(board->house(One, 1))).WillOnce(Return(Two));
    EXPECT_CALL(*board, saw(board->house(Two, 1))).WillOnce(Return(One));
    EXPECT_CALL(*board, saw(board->house(One, 2))).WillOnce(Return(std::nullopt));
    EXPECT_CALL(*board, moveRemainingSeedsToStore).WillOnce(Return(Two));

    {
        std::map<PlayerNumber, std::shared_ptr<IPlayer>> playerMap{{One, playerA}, {Two, playerB}};
        Game game{std::move(board), output, playerMap};
        game.start(One);
    }
}
