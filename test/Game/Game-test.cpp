#include "Game/Game.h"

#include "../test/Game/Board-mock.h"
#include "../test/Output/Output-mock.h"
#include "../test/Player/Player-mock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using PlayerNumber::One;
using PlayerNumber::Two;

using ::testing::Return;
using ::testing::_;

TEST(GameTest, mocked)
{
    MockOutput output;
    std::unique_ptr<MockBoard> board{new MockBoard{3, {1, 1, 1, 4, 1, 1, 1, 6}}};

    std::shared_ptr<MockPlayer> playerA{std::make_shared<MockPlayer>()};
    playerA->defineSequence(One, {1, 2});
    std::shared_ptr<MockPlayer> playerB{std::make_shared<MockPlayer>()};
    playerB->defineSequence(Two, {1});

    EXPECT_CALL(output, showBoard(_)).Times(5);
    EXPECT_CALL(output, showTurn(1, One));
    EXPECT_CALL(output, showTurn(2, Two));
    EXPECT_CALL(output, showTurn(3, One));
    EXPECT_CALL(output, showWinner(std::optional<PlayerNumber>(Two)));

    EXPECT_CALL(*board, saw(Pit(One, 1))).WillOnce(Return(Two));
    EXPECT_CALL(*board, saw(Pit(Two, 1))).WillOnce(Return(One));
    EXPECT_CALL(*board, saw(Pit(One, 2))).WillOnce(Return(std::nullopt));
    EXPECT_CALL(*board, moveRemainingSeedsToStore).WillOnce(Return(Two));

    {
        Game game{std::move(board), output, {playerA, playerB}};
        EXPECT_EQ(game.start(), (Game::Outcome{{4, 6}, Two, 4}));
    }
}
