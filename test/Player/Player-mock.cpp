#include "Player-mock.h"

#include "Game/AbstractBoard.h"

MockPlayer::MockPlayer(const std::string &name) :
    AbstractPlayer{name}
{ }

void MockPlayer::defineSequence(PlayerNumber playerNumber, const std::initializer_list<int> &sequence)
{
    auto &a = EXPECT_CALL(*this, selectHouse);
    for (int i : sequence)
        a.WillOnce(::testing::Return(Pit{playerNumber, i}));
}

void MockPlayer::defineSequence(const std::initializer_list<std::pair<PlayerNumber, int> > &sequence)
{
    auto &a = EXPECT_CALL(*this, selectHouse);
    for (auto i : sequence)
        a.WillOnce(::testing::Return(Pit{i.first, i.second}));
}
