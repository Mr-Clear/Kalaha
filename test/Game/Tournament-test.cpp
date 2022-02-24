#include "Game/Tournament.h"

#include "../test/Game/Board-mock.h"
#include "../test/Player/Player-mock.h"
#include "../test/Output/Output-mock.h"

#include <gtest/gtest.h>

using PlayerNumber::One;
using PlayerNumber::Two;

TEST(TournamentTest, twoPlayerGameWonByPlayerTwo)
{
    std::shared_ptr<MockPlayer> playerA{std::make_shared<MockPlayer>("A")};
    std::shared_ptr<MockPlayer> playerB{std::make_shared<MockPlayer>("B")};
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
    Tournament c{{2, 2}, {std::static_pointer_cast<AbstractPlayer>(playerA), std::static_pointer_cast<AbstractPlayer>(playerB)}, 1, o};

    playerA->defineSequence({{One, 1}, {One, 2},
                             {Two, 1}, {Two, 2}, {Two, 1}, {Two, 2}});
    playerB->defineSequence(One, {2, 1, 2});

    std::vector<Tournament::Outcome> out = c.run();
    EXPECT_EQ(out[0], (Tournament::Outcome{playerA, 0, 1, 1, 6}));
    EXPECT_EQ(out[1], (Tournament::Outcome{playerB, 1, 0, 1, 10}));
}

TEST(TournamentTest, threePlayerGame)
{
    std::shared_ptr<MockPlayer> playerA{std::make_shared<MockPlayer>("A")};
    std::shared_ptr<MockPlayer> playerB{std::make_shared<MockPlayer>("B")};
    std::shared_ptr<MockPlayer> playerC{std::make_shared<MockPlayer>("C")};
    MockOutput o;
    EXPECT_CALL(o, showBoard).Times(18);
    EXPECT_CALL(o, showNextGame).Times(6);
    EXPECT_CALL(o, showTurn(1, One)).Times(6);
    EXPECT_CALL(o, showWinner(std::optional<PlayerNumber>())).Times(6);
    Tournament c{{1, 1}, {std::static_pointer_cast<AbstractPlayer>(playerA),
                           std::static_pointer_cast<AbstractPlayer>(playerB),
                           std::static_pointer_cast<AbstractPlayer>(playerC)}, 1, o};
    playerA->defineSequence({{One, 1}, {One, 1}});
    playerB->defineSequence({{One, 1}, {One, 1}});
    playerC->defineSequence({{One, 1}, {One, 1}});

    const std::vector<Tournament::Outcome> out = c.run();
    EXPECT_EQ(out[0], (Tournament::Outcome{playerA, 0, 0, 4, 4}));
    EXPECT_EQ(out[1], (Tournament::Outcome{playerB, 0, 0, 4, 4}));
    EXPECT_EQ(out[2], (Tournament::Outcome{playerC, 0, 0, 4, 4}));
}
