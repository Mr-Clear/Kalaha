#include "Game/Competition.h"

#include "../test/Game/Board-mock.h"
#include "../test/Player/Player-mock.h"
#include "../test/Output/Output-mock.h"

#include <gtest/gtest.h>

using PlayerNumber::One;
using PlayerNumber::Two;

TEST(CompetitionTest, twoPlayerGameWonByPlayerTwo)
{
    std::shared_ptr<MockPlayer> playerA{std::make_shared<MockPlayer>()};
    std::shared_ptr<MockPlayer> playerB{std::make_shared<MockPlayer>()};
    MockOutput o;
    EXPECT_CALL(o, showBoard(testing::_)).Times(13);
    EXPECT_CALL(o, showNextGame).Times(2);

    EXPECT_CALL(o, showTurn(1, One)).Times(2);
    EXPECT_CALL(o, showTurn(2, One));
    EXPECT_CALL(o, showWinner(std::optional<PlayerNumber>(Two)));
    EXPECT_CALL(o, showTurn(2, Two));
    EXPECT_CALL(o, showTurn(3, One));
    EXPECT_CALL(o, showTurn(4, Two));
    EXPECT_CALL(o, showTurn(5, One));
    EXPECT_CALL(o, showTurn(6, Two));
    EXPECT_CALL(o, showTurn(7, Two));
    EXPECT_CALL(o, showWinner(std::optional<PlayerNumber>()));
    Competition c{{2, 2}, {std::static_pointer_cast<AbstractPlayer>(playerA), std::static_pointer_cast<AbstractPlayer>(playerB)}, 1, o};

    playerA->defineSequence({{One, 1}, {One, 2},
                             {Two, 1}, {Two, 2}, {Two, 1}, {Two, 2}});
    playerB->defineSequence(One, {2, 1, 2});

    std::vector<Competition::Outcome> out = c.run();
    EXPECT_EQ(out[0], (Competition::Outcome{playerA, 0, 1, 1, 6}));
    EXPECT_EQ(out[1], (Competition::Outcome{playerB, 1, 0, 1, 10}));
}

TEST(CompetitionTest, threePlayerGame)
{
    std::shared_ptr<MockPlayer> playerA{std::make_shared<MockPlayer>()};
    std::shared_ptr<MockPlayer> playerB{std::make_shared<MockPlayer>()};
    std::shared_ptr<MockPlayer> playerC{std::make_shared<MockPlayer>()};
    MockOutput o;
    EXPECT_CALL(o, showBoard).Times(18);
    EXPECT_CALL(o, showNextGame).Times(6);
    EXPECT_CALL(o, showTurn(1, One)).Times(6);
    EXPECT_CALL(o, showWinner(std::optional<PlayerNumber>())).Times(6);
    Competition c{{1, 1}, {std::static_pointer_cast<AbstractPlayer>(playerA),
                           std::static_pointer_cast<AbstractPlayer>(playerB),
                           std::static_pointer_cast<AbstractPlayer>(playerC)}, 1, o};
    playerA->defineSequence({{One, 1}, {One, 1}});
    playerB->defineSequence({{One, 1}, {One, 1}});
    playerC->defineSequence({{One, 1}, {One, 1}});

    const std::vector<Competition::Outcome> out = c.run();
    EXPECT_EQ(out[0], (Competition::Outcome{playerA, 0, 0, 4, 4}));
    EXPECT_EQ(out[1], (Competition::Outcome{playerB, 0, 0, 4, 4}));
    EXPECT_EQ(out[2], (Competition::Outcome{playerC, 0, 0, 4, 4}));
}
