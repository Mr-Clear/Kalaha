#include <iostream>

#include "Game/Game.h"
#include "Output/ConsoleOutput.h"
#include "Player/ConsoleInputPlayer.h"
#include "Player/RandomPlayer.h"

#include <memory>

int main()
{
    ConsoleOutput output;
    std::shared_ptr<AbstractPlayer> playerA{std::make_shared<ConsoleInputPlayer>(PlayerNumber::One)};
    std::shared_ptr<AbstractPlayer> playerB{std::make_shared<RandomPlayer>(PlayerNumber::Two)};
    std::map<PlayerNumber, std::shared_ptr<AbstractPlayer>> playerMap{{PlayerNumber::One, playerA}, {PlayerNumber::Two, playerB}};
    Game g{6, 4, output, playerMap};
    g.start(PlayerNumber::One);
    return 0;
}
