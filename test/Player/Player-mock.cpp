#include "Player-mock.h"

#include "Game/AbstractBoard.h"

void MockPlayer::defineSequence(const std::initializer_list<int> &sequence)
{
    auto &a = EXPECT_CALL(*this, selectHouse);
    for (int i : sequence)
        a.WillOnce(::testing::Return(Pit{playerNumber(), i}));
}
