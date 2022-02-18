#include "Game/Competition.h"

#include "../test/Game/Board-mock.h"
#include "../test/Player/Player-mock.h"
#include "../test/Output/Output-mock.h"

#include <gtest/gtest.h>

using PlayerNumber::One;
using PlayerNumber::Two;

TEST(CompetitionTest, quickGameWonByPlayerTwo)
{
    std::shared_ptr<MockPlayer> playerA{std::make_shared<MockPlayer>(One)};
    std::shared_ptr<MockPlayer> playerB{std::make_shared<MockPlayer>(Two)};
    MockOutput o;
    EXPECT_CALL(o, showNextGame(1));
    EXPECT_CALL(o, showBoard(testing::_)).Times(13);
    EXPECT_CALL(o, showTurn(1, One));
    EXPECT_CALL(o, showTurn(2, One)).Times(2);
    EXPECT_CALL(o, showWinner(std::optional<PlayerNumber>(Two)));
    EXPECT_CALL(o, showNextGame(2));
    EXPECT_CALL(o, showTurn(1, Two));
    EXPECT_CALL(o, showTurn(3, Two));
    EXPECT_CALL(o, showTurn(4, One));
    EXPECT_CALL(o, showTurn(5, Two));
    EXPECT_CALL(o, showTurn(6, One));
    EXPECT_CALL(o, showTurn(7, One));
    EXPECT_CALL(o, showWinner(std::optional<PlayerNumber>()));
    Competition c{{2, 2}, std::static_pointer_cast<AbstractPlayer>(playerA), std::static_pointer_cast<AbstractPlayer>(playerB), 2, o};

    playerA->defineSequence({1, 2, 1, 2, 1, 2});
    playerB->defineSequence({2, 1, 2});

    EXPECT_EQ(c.run(), (Competition::Outcome{{0, 1, 1}, Two}));
}
