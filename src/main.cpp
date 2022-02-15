#include <iostream>

#include "Game/ConsoleInputPlayer.h"
#include "Game/Game.h"
#include "Game/RandomPlayer.h"
#include "Output/ConsoleOutput.h"

#include <memory>

int main()
{
    ConsoleOutput output;
    std::shared_ptr<IPlayer> playerA{std::make_shared<ConsoleInputPlayer>(PlayerNumber::One)};
    std::shared_ptr<IPlayer> playerB{std::make_shared<RandomPlayer>(PlayerNumber::Two)};
    std::map<PlayerNumber, std::shared_ptr<IPlayer>> playerMap{{PlayerNumber::One, playerA}, {PlayerNumber::Two, playerB}};
    Game g{6, 4, output, playerMap};
    g.start(PlayerNumber::One);
    return 0;
}
